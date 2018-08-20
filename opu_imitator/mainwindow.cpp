#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dMaxPAN = 40320.0;
    dMaxTILT = 23625.0;
    zeroX = 20160.0;
    zeroY = 15750.0;
    dStepPAN = 112.0;
    dStepTILT = 175.0;

    azimutZero = 0.0;
    azZeNew = azimutZero;

    sp = quint8(0); // Скорости движения SP (pan - X), ST (tilt - Y).
    st = quint8(0); // Диапазон от 1 до 3F (1 - 63). 0 - максимальная

    // Направление на север относительно нуля ОПУ в градусах

    oldX = 0;
    oldY = 0;

    socket = new QUdpSocket(this);
    port = 6000;
    socket->bind(QHostAddress::Any, port);
    connect(socket, SIGNAL(readyRead()), SLOT(read()));
    curPoint.dx = 0;
    curPoint.dy = 0;
    gradus2Steps(curPoint);

    xSpeed = 0;
    ySpeed = 0;
    setPoint.dx = 90;
    setPoint.dy = 0;

    gradus2Steps(setPoint);
    steps2Gradus(setPoint);
    //qDebug() << setPoint.ix;

    QByteArray tx;
    tx = QByteArray::number((quint16)setPoint.ix, 16);
    QString panRequest = "ff ad 00 81";
    panRequest.append(tx.rightJustified(4, '0')).remove(' ');
    QByteArray panTest = QByteArray::fromHex(panRequest.toLocal8Bit());
    qDebug() << panTest.toHex();

    QByteArray ty;
    ty = QByteArray::number((quint16)setPoint.iy, 16);
    QString tiltRequest = "ff ad 00 83";
    tiltRequest.append(ty.rightJustified(4, '0')).remove(' ');
    QByteArray tiltTest = QByteArray::fromHex(tiltRequest.toLocal8Bit());
    qDebug() << tiltTest.toHex();

    QByteArray runTest = QByteArray::fromHex("ff ad 00 87 3f 3f ss");
    send(panTest);
    send(tiltTest);
    send(runTest);

    QByteArray timeTestX = QByteArray::fromHex("ff ad 00 51");
    send(timeTestX);

    QByteArray timeTestY = QByteArray::fromHex("ff ad 00 53");
    send(timeTestY);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
}

void MainWindow::send(QByteArray data) {
  socket->writeDatagram(data, QHostAddress::Broadcast, port);
}

void MainWindow::read()
{
    QHostAddress sender;
    quint16 senderPort;
    QByteArray PelcoCommand;
    while(socket->hasPendingDatagrams())
    {
        PelcoCommand.clear();
        PelcoCommand.resize(socket->pendingDatagramSize());
        socket->readDatagram(PelcoCommand.data(), PelcoCommand.size(), &sender, &senderPort);

        QByteArray ba = PelcoCommand.mid(3, 3);
        QDataStream ds(&ba, QIODevice::ReadOnly);
        //std::vector<quint8> bytes(PelcoCommand.size());
        ds.setVersion(QDataStream::Qt_4_8);

        quint8 type;
        quint16 result;

        ds >> type >> result;

        switch (type) {
        case 0x51: // get pan
        {

            getCurrentPoint();

            QByteArray tx = QByteArray::number((quint16)curPoint.ix, 16);
            QString panRequest = "ff ad 00 61";
            panRequest.append(tx.rightJustified(4, '0')).remove(' ');
            QByteArray PelcoCommandOut = QByteArray::fromHex(panRequest.toLocal8Bit());
            findPelcoCS(PelcoCommandOut);
            qDebug() << hex << PelcoCommandOut;
            send(PelcoCommandOut);
        }
            break;

        case 0x53: // get tilt
        {
            getCurrentPoint();
            QByteArray tx = QByteArray::number((quint16)curPoint.iy, 16);
            QString panRequest = "ff ad 00 63";
            panRequest.append(tx.rightJustified(4, '0')).remove(' ');
            QByteArray PelcoCommandOut = QByteArray::fromHex(panRequest.toLocal8Bit());
            findPelcoCS(PelcoCommandOut);
            qDebug() << hex << PelcoCommandOut;
            send(PelcoCommandOut);
        }
            break;
        case 0x81: //Set pan
            setPoint.ix = result;
            if (sp == 0)
                return;

            steps2Gradus(setPoint);
            calcTimeOPU(setPoint);
            qDebug() << result;
            break;
        case 0x83:
            setPoint.iy = result;
            if (st == 0)
                return;

            steps2Gradus(setPoint);
            calcTimeOPU(setPoint);
            qDebug() << result;
            break;
        case 0x87:
        {
            st = ((quint8*)&result)[0];
            sp = ((quint8*)&result)[1];
            //qDebug() << st << " " << sp;
            setSpeedXY(sp, st);
            steps2Gradus(setPoint);
            if (curPoint.dx == setPoint.dx && curPoint.dy == setPoint.dy)
                return;
            int time = calcTimeOPU(setPoint);
            qDebug() << time;

            qDebug() << curPoint.ix << " " << curPoint.iy;
            qDebug() << setPoint.ix << " " << setPoint.iy;
        }
            break;
        case 0x61:
            qDebug() << result;
            break;
        case 0x63:
            qDebug() << result;
            break;
        default:
            break;
        }
    }
}

void MainWindow::getCurrentPoint()
{
    int curTime = QDateTime::currentDateTime().toTime_t();
    if (curTime >= endTime)
    {
        curPoint.ix = setPoint.ix;
        curPoint.iy = setPoint.iy;
        steps2Gradus(curPoint);
        return;
    }

    int deltaTime = endTime - curTime;
    qDebug() << deltaTime;
    if (curPoint.ix >= setPoint.ix)
        curPoint.ix -= floor(xSpeed * deltaTime);
    else curPoint.ix += floor(xSpeed * deltaTime);

    //qDebug() << deltaTime << " " << x0pan << " " << y0pan;
    if (curPoint.iy >= setPoint.iy)
        curPoint.iy -= floor(ySpeed * deltaTime);
    else curPoint.iy += floor(ySpeed * deltaTime);

    steps2Gradus(curPoint);
}

void MainWindow::findPelcoCS(QByteArray& command)
{   // вставляет в исходящую команду сонтрольную сумму
    quint8 cs = 0;
    cs += (quint8)command[5];
    cs += (quint8)command[4];
    cs += (quint8)command[3];
    cs += (quint8)command[2];
    cs += (quint8)command[1];
    command.append(cs);
}

int MainWindow::calcTimeOPU(Point &mP)
{
    double azt, umt; // абсолютное значение угла поворота по азимуту
    int Tx, Ty; // время поворота по x и y в миллисуекундах

    azt = fabs(mP.dx-curPoint.dx);
    if(azt > 360.0) azt -= 360.0*floor(azt/360.0);
    if(azt > 180.0) azt = 360.0 - azt;

    if(azt < x0pan)
    {
        if(azt < 0.10307) Tx = int(452.00929);
        else Tx = int(452.00929 + 262.79859 * pow(azt - 0.10307, 0.40181));
    } else
    {
        Tx = int(y0pan + Kpan * (azt - x0pan));
    }

    umt = fabs(mP.dy-curPoint.dy);
    if(umt < x0tilt)
    {
        if(umt < 0.06964) Ty = int(441.29801);
        else Ty = int(441.29801 + 382.06815 * pow(umt - 0.06964, 0.40485));
    } else
    {
        Ty = int(y0tilt + Ktilt * (umt - x0tilt));
    }

    startTime = QDateTime::currentDateTime().toTime_t();
    endTime = startTime + (Tx > Ty ? Tx: Ty);

    //Нужно пересчитать в тики из градусов, иначе некорректный результат (больше 100 по тикам)
    qDebug() << "check: " << fabs(mP.dx - curPoint.dx);
    xSpeed = Tx > 0 ? fabs(mP.ix - curPoint.ix) / Tx : 0;

    ySpeed = Ty > 0 ? fabs(mP.iy - curPoint.iy) / Ty : 0;

    qDebug() << "speed: " << xSpeed << " " << ySpeed;

    return Tx > Ty ? Tx : Ty ;
}

void MainWindow::setSpeedXY(quint8 x, quint8 y)
{
    if(x<64) sp = x; // if(x>=0 && x<64)
    else sp = 0;
    if(y<64) st = y; // if(x>=0 && x<64)
    else st = 0;

//    --PAN x0
//    parA=0.0717;
//    parB=-2.32855;
//    parC=0.05583;
//    xVal = parA+10^(parB+parC*dVal)
    double panSpeed = sp > 0 ? double(sp) : double(64);
    x0pan = 0.0717 + pow(10.0, -2.32855 + panSpeed * 0.05583);

//    --PAN Fun2
//    parA=452.00929;
//    parB=262.79859;
//    parC=0.10307;
//    parD=0.40181;
//    xVal = parA+parB*(dVal-parC)^parD
    if(x0pan < 0.10307) y0pan = 452.00929;
    else y0pan = 452.00929 + 262.79859 * pow(x0pan - 0.10307, 0.40181);

//    --PAN k
//    parA=1.13543;
//    parB=3.952;
//    parC=-0.04202;
//    xVal = parA+10^(parB+parC*dVal)
    Kpan = 1.13543 + pow(10.0, 3.952 - panSpeed * 0.04202);

//    --TILT x0
//    parA=0.10143;
//    parB=-3.34565;
//    parC=0.07174;
//    xVal = parA+10^(parB+parC*dVal)
    double tiltSpeed = st > 0 ? double(st) : double(64.0);
    x0tilt = 0.10143 + pow(10.0, -3.34565 + tiltSpeed * 0.07174);

//    --TILT Fun2
//    parA=441.29801;
//    parB=382.06815;
//    parC=0.06964;
//    parD=0.40485;
//    xVal = parA+parB*(dVal-parC)^parD
    if(x0tilt < 0.06964) y0tilt = 441.29801;
    else y0tilt = 441.29801 + 382.06815 * pow(x0tilt - 0.06964, 0.40485);

//    --TILT k
//    parA=2.41736;
//    parB=4.14612;
//    parC=-0.04062;
//    xVal = parA+10^(parB+parC*dVal)
    Ktilt = 2.41736 + pow(10.0, 4.14612 - tiltSpeed * 0.04062);
}


void MainWindow::gradus2Steps(Point &mP)
{
    double tx;
    mP.dx -= 360.0*floor(mP.dx/360.0);
//    if(mP.dx > 360.0) mP.dx -= 360.0;
//    if(mP.dx < 0.0) mP.dx += 360.0;
    tx = mP.dx - azimutZero;
    tx -= 360.0*floor(tx/360.0);
    tx = zeroX + dStepPAN * tx; //
    tx -= dMaxPAN * floor(tx/dMaxPAN);
//    if(dx > dMaxPAN) dx -= dMaxPAN;
//    if(dx < 0.0) dx += dMaxPAN;
    mP.ix = (quint16)(tx); // (tx+0.5)

    if(mP.dy > 90.0) mP.dy = (double)(90.0);
    if(mP.dy < -45.0) mP.dy = (double)(-45.0);
    mP.iy = (quint16)( int(zeroY - dStepTILT * mP.dy + 0.5) );
}

void MainWindow::steps2Gradus(Point &mP)
{
    double tx = int(mP.ix);
    tx = 180.0 + tx/dStepPAN + azimutZero;
    tx -= 360.0*floor(tx/360.0);
    mP.dx = tx;
    // mP.dx -= 360.0*int((azimutZero - double(180.0) + double(mP.ix)/dStepPAN)/360.0);

    mP.dy = double(mP.iy);
    mP.dy = 90.0 - mP.dy/dStepTILT;
    // mP.dy = 90.0 - double(mP.iy)/dStepTILT;
}
