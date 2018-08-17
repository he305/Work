#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ui->verticalLayout_5 ;
    initByDefaults();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initByDefaults(void)  /* инициализация всего значениями по умолчанию из полей ввода, файлов */
{
    IsInit=true; /* находимся ли мы в состоянии автоматического изменения значений в полях ввода, например - начальный рассчет, перерассчет.
     * Слоты обработки сигналов не будут обрабатывать изменение каждой ячейки ввода */
    myChangeValueAccepted=false; /* true - значение выходит за диапазон, но принято. Значение изменилось - нужен пересчет */

    myEps=1.0e-6; /* погрешность 1.0E-6 - одна на всё , отдельно есть такая же в классах myPlot и myGauss */

    minV=0.4;  /* границы диапазонов для ввода без подтверждения */
    maxV=7200.0;
    minH=0.01;
    maxH=62.0;
    minEPR=0.01;
    maxEPR=500.0;
    minDP=0.01;
    maxDP=90.0;
//    minFP=0.01;
//    maxFP=90.0;
    minPhi=-180.0;
    maxPhi=180.0;
    minSP=0.1;
    maxSP=5.0;  /* границы диапазонов для ввода без подтверждения */

//    for(int i =0 ; i < QCoreApplication::arguments().length() ; ++i)
//        qDebug() << i << " = " << QCoreApplication::arguments().at(i) << endl;

// Заготовка под аргументы командной строки
    if( QCoreApplication::arguments().length() > 1 )
    {
        inFile = QCoreApplication::applicationDirPath()+"/" + QCoreApplication::arguments().at(1);
    }
    else
    {
        inFile = QCoreApplication::applicationDirPath() + QString("/default.in");
    }

//    qDebug() << QDir::current().absolutePath() << endl;
//    qDebug() << QCoreApplication::applicationDirPath() << endl;
//    qDebug() << inFile << endl;


    if(ui->radioButton_L3->isChecked())
    {
        L3 = true; // установили диапазон L3
    }
    else
    {
        L3 = false; // установили диапазон L2
    }

    myPoint.setX(ui->lineEdit_V->text().toDouble()); /* =600 км/ч Инициализация значения скорости (точка в пространстве VH) из поля ввода главного окна */
    myPoint.setY(ui->lineEdit_H->text().toDouble()); /* =0,5 км Инициализация значения высоты (точка в пространстве VH) из поля ввода главного окна */
    Phi = ui->lineEdit_Phi->text().toDouble(); /* =0 градусов Инициализация значения ракурса из поля ввода главного окна */
    mEPR = ui->lineEdit_S->text().toDouble(); /* =2,5 м^2 Инициализация значения ЭПР из поля ввода главного окна */
    mEPRd = ui->lineEdit_dS->text().toDouble(); /* =0,8 м^2 Инициализация значения ошибки ЭПР из поля ввода главного окна */
    mDP = ui->lineEdit_DP->text().toDouble(); /* =2 м Инициализация значения ДП из поля ввода главного окна */
    mDPd = ui->lineEdit_dDP->text().toDouble(); /* =0,5 м Инициализация значения ошибки ДП из поля ввода главного окна */
    // mFP = ui->lineEdit_FP->text().toDouble(); /* =2 м Инициализация значения ЧП из поля ввода главного окна */
    // mFPd = ui->lineEdit_dFP->text().toDouble(); /* =0,5 м Инициализация значения ошибки ЧП из поля ввода главного окна */
    mSP_1 = ui->lineEdit_SP_1->text().toDouble(); /* =0,1 Инициализация значения СП из поля ввода главного окна */
    mSP_2 = ui->lineEdit_SP_2->text().toDouble(); /* =0,1 Инициализация значения СП из поля ввода главного окна */

    BegName = ui->lineEdit_BegName->text(); /* ="4_VRT_" Инициализация значения "НАЧАЛО ИМЕНИ СОХРАНЯЕМЫХ ФАЙЛОВ" из поля ввода главного окна */

    // di 09.11.16
    // если существует входной файл - прочитать все или некоторые параметры из него
    // qDebug() << " if(!QFile::exists(inFile)) , inFile = " << inFile;
    if(QFile::exists(inFile))
    {
        myOpenDirFileInData(inFile);
        // открыть , прочитать, попытаться присвоить, отчитаться о результате
    }
    else
    {
        // присвоить дефолтные параметры, выдать сообщение о входных парметрах
    }

    mySetCurDir(); /* Устанавливает myInDir и myOutDir на папку с исполняемым файлом */

    myFileName = QString("./data_in/VH2_1_SA.txt");    /* Читаем из четырехколоночного файла соответствующего класса */
    myOpenFile4x4read(myFileName, Poly1SA_0, Poly1SA_1); /* в вектора многоугольника_0 и многоугольника_1 пространства VH */
    myFileName = QString("./data_in/VH2_2_SAB2.txt");
    myOpenFile4x4read(myFileName, Poly2SAB2_0, Poly2SAB2_1);
    myFileName = QString("./data_in/VH2_3_TA.txt");
    myOpenFile4x4read(myFileName, Poly3TA_0, Poly3TA_1);
    myFileName = QString("./data_in/VH2_4_VRT.txt");
    myOpenFile4x4read(myFileName, Poly4VRT_0, Poly4VRT_1);
    myFileName = QString("./data_in/VH2_5_GZLA.txt");
    myOpenFile4x4read(myFileName, Poly5GZ_0, Poly5GZ_1);
    myFileName = QString("./data_in/VH2_6_KR.txt");
    myOpenFile4x4read(myFileName, Poly6KR_0, Poly6KR_1);
    myFileName = QString("./data_in/VH2_7_ADA.txt");
    myOpenFile4x4read(myFileName, Poly7ADA_0, Poly7ADA_1);

    setVHtable(1); /* В главном окне -> Траекторные характеристики -> Таблица -> B2 */

    // myReCalcAll();
    myFillMatrVH(); /* Заполнить матрицу mVH_b[5][5] */
    myPointInVH(); /* Заполнить вектор gVH[5]  */
    myFillMatrVHg(); /* Заполнить матрицу mVH_g[5][5] */
    myFillMatrVHp(); /* Заполнить матрицу mVH_p[5][5] */

    myLoadEPR(); /* Загрузить таблицу ЭПР и ошибок из файла в соответствии с ракурсом и диапазоном волн */
    myFillMatrEPR(); /* Заполнить матрицу mS_b[5][5] */
    myPointInEPR(); /* Заполнить вектор gS[5]  */
    myFillMatrEPRg(); /* Заполнить матрицу mS_g[5][5] */
    myFillMatrEPRp(); /* Заполнить матрицу mS_p[5][5] */
    setEPRtable(); /*  Заполнить в главном окне -> ЭПР -> Таблица */

    myLoadDP( ); /* Загрузить файл и создать таблицу ДП и ошибок в соответствии с ракурсом и диапазоном волн */
    myFillMatrDP(); /* Заполнить матрицу mDP_b[5][5] */
    myPointInDP(); /* Заполнить вектор gDP[5]  */
    myFillMatrDPg(); /* Заполнить матрицу mDP_g[5][5] */
    myFillMatrDPp(); /* Заполнить матрицу mDP_p[5][5] */
    setDPtable();  /* Заполнить в главном окне -> ДП -> Таблица */

//    qDebug() << "EPRg[1][1] = " << mS_g[1][1] << " EPRp[1][1] =   " << mS_p[1][1];
//    qDebug() << "DPg[1][1] = " << mDP_g[1][1] << " DPp[1][1] =   " << mDP_p[1][1];

//    myFillMatrFP(); /* Заполнить матрицу mFP_b[5][5] */
//    myPointInFP(); /* Заполнить вектор gFP[5]  */
//    myFillMatrFPg(); /* Заполнить матрицу mFP_g[5][5] */
//    myFillMatrFPp(); /* Заполнить матрицу mFP_p[5][5] */
//    setFPtable();  /* Заполнить в главном окне -> ЧП -> Таблица */

    myFillMatrSPp(); /* Заполнить матрицу mSP_p[5][5] */

    myFillMatrVH_S_g(); /* Заполнить матрицу mVH_S_g[5][5] */
    myFillMatrVH_S_p(); /* Заполнить матрицу mVH_S_p[5][5] */

    myFillMatrVH_DP_g(); /* Заполнить матрицу mVH_DP_g[5][5] */
    myFillMatrVH_DP_p(); /* Заполнить матрицу mVH_DP_p[5][5] */

//    myFillMatrVH_DP_FP_g(); /* Заполнить матрицу mVH_DP_FP_g[5][5] */
//    myFillMatrVH_DP_FP_p(); /* Заполнить матрицу mVH_DP_FP_p[5][5] */

    myFillMatrVH_S_DP_g(); /* Заполнить матрицу mVH_S_DP_g[5][5] */
    myFillMatrVH_S_DP_p(); /* Заполнить матрицу mVH_S_DP_p[5][5] */

    myFillMatrVH_DP_S_g(); /* Заполнить матрицу mVH_DP_S_g[5][5] */
    myFillMatrVH_DP_S_p(); /* Заполнить матрицу mVH_DP_S_p[5][5] */

    myFillMatrVH_S_SP_g(); /* Заполнить матрицу mVH_S_SP_g[5][5] */
    myFillMatrVH_S_SP_p(); /* Заполнить матрицу mVH_S_SP_p[5][5] */

    myFillMatrVH_S_DP_SP_g(); /* Заполнить матрицу mVH_S_DP_SP_g[5][5] */
    myFillMatrVH_S_DP_SP_p(); /* Заполнить матрицу mVH_S_DP_SP_p[5][5] */

    myFillMatrVHg_Sg_g();
    myFillMatrVHg_Sg_p();
    // myFillMatrVHg_DPg_g();
    // myFillMatrVHg_DPg_p();
    myFillMatrVHg_Sg_DPg_g();
    myFillMatrVHg_Sg_DPg_p();

    myFillMatrVHg_Sg_G_SP_g();
    myFillMatrVHg_Sg_G_SP_p();
    myFillMatrVHg_Sg_P_SP_g();
    myFillMatrVHg_Sg_P_SP_p();
    myFillMatrVHg_Sg_DPg_G_SP_g();
    myFillMatrVHg_Sg_DPg_G_SP_p();
    myFillMatrVHg_Sg_DPg_P_SP_g();
    myFillMatrVHg_Sg_DPg_P_SP_p();

    IsInit=false; /* Управляющие элементы снова управляют - сигналы обрабатываются */

    ui->listWidget->setCurrentRow(13); /* выбрать в списке строку про матрицу mVHg_Sg_DPg_p()[5][5] */
    setPtable(13);
//    setPtable(2); /* показать матрицу mVH_p[5][5] */
    myShowResultDialog(false);
}

/* void Widget::mySetCurDir(void) устанавливает текущей папку с исполняемым файлом,
 * сохраняет ее в myInDir и myOutDir; путь ко входным файлам ./data_in/ */
void Widget::mySetCurDir(void)
{
    QString str = QCoreApplication::applicationFilePath(); // Полное имя нашего файла с путем в строку
    QFileInfo fi(str); // файлинфо по файлу
    myInDir.setPath(fi.absolutePath()); // устанавливаем путь к EXE-файлу как путь поиска входных файлов по умолчанию
    QDir::setCurrent(myInDir.absolutePath()); // делаем папку с EXE-файлом текущей
//    myOutDir=myInDir; // устанавливаем путь к EXE-файлу как путь поиска выходных файлов по умолчанию
//    myOutResDir=myOutDir;
    myOutDir.setPath(str); // устанавливаем путь к EXE-файлу как путь поиска выходных файлов по умолчанию
    myOutResDir.setPath(str);// устанавливаем путь к EXE-файлу как путь поиска выходных файлов по умолчанию
}

/* int myOpenFile2x4read(QString &fileName, QPolygonF &Poly);  записывает содержимое двухколоночного файла fileName в вектор Poly.
 * Используется для чтения из файла (без интерактивного выбора файла) таблиц ЭПР и ДП. Возвращает число удачно преобразованных строк */
int Widget::myOpenFile2x4read(QString &fileName, QPolygonF &Poly)
{
    int i=0;
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream in(&inputFile);
       Poly.clear();
       while (!in.atEnd())
       {
          QString line = in.readLine();
          line.replace(	QChar(','), QChar('.'));
          QStringList temp = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

          double x = QString(temp[0]).toDouble();
          double y = QString(temp[1]).toDouble();
          Poly << QPointF(x,y);
          ++i;
       }
       inputFile.close();
    }
    return i;
}

/* int myOpenFile4x4read(QString &fileName, QPolygonF &Poly_0, QPolygonF &Poly_1) записывает содержимое четырехколоночного файла fileName
 * в два вектора - Poly_0 и Poly_1. Используется для чтения из файла (без интерактивного выбора файла) многоугольников пространства VH,
 * ограничивающих области с вероятностью 0 и 1 соответственно. Возвращает число удачно преобразованных строк */
int Widget::myOpenFile4x4read(QString &fileName, QPolygonF &Poly_0, QPolygonF &Poly_1)
{
    int i=0;
    double x, y;
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream in(&inputFile);
       Poly_0.clear();
       Poly_1.clear();
       while (!in.atEnd())
       {
          QString line = in.readLine();
          line.replace(	QChar(','), QChar('.'));
          QStringList temp = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

          x = QString(temp[0]).toDouble();
          y = QString(temp[1]).toDouble();
          Poly_0 << QPointF(x,y);

          x = QString(temp[2]).toDouble();
          y = QString(temp[3]).toDouble();
          Poly_1 << QPointF(x,y);
          ++i;
       }
       inputFile.close();
    }
    return i;
}

/* int myOpenDirFile2x4read(QString &fileName, QPolygonF &Poly) записывает содержимое двухколоночного файла fileName в вектор Poly.
 * Используется для чтения из файла (с интерактивным выбором) файла таблиц ЭПР и ДП. Возвращает число удачно преобразованных строк */
int Widget::myOpenDirFile2x4read(QString &fileName, QPolygonF &Poly)
{
    int i=0;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open VH polygon"), ".", tr("Polygon Files (*.txt)"));
    if(fileName.isNull()) return -1;

    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream in(&inputFile);
       // qDebug() << fileName << " после QTextStream in(&inputFile) " ;
       Poly.clear();
       // qDebug() << fileName << " после Poly.clear() " ;
       while (!in.atEnd())
       {
          QString line = in.readLine();
          line.replace(	QChar(','), QChar('.'));
          // qDebug() << line ;
          QStringList temp = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

          double x = QString(temp[0]).toDouble();
          double y = QString(temp[1]).toDouble();
          Poly << QPointF(x,y);
          // qDebug() << Poly ;
          ++i;
       }
       inputFile.close();
    }
    // qDebug() << "Число строк" << i ;
    return i;
}

/* int myOpenDirFile4x4read(QString &fileName, QPolygonF &Poly_0, QPolygonF &Poly_1) записывает содержимое четырехколоночного файла fileName
 * в два вектора - Poly_0 и Poly_1. Используется для чтения из файла (с интерактивным выбором файла) многоугольников пространства VH,
 * ограничивающих области с вероятностью 0 и 1 соответственно. Возвращает число удачно преобразованных строк */
int Widget::myOpenDirFile4x4read(QString &fileName, QPolygonF &Poly_0, QPolygonF &Poly_1)
{
    int i=0;
    double x, y;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open VH polygon"), ".", tr("Polygon Files (*.txt)"));
    if(fileName.isNull()) return -1;

    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream in(&inputFile);
       Poly_0.clear();
       Poly_1.clear();
       while (!in.atEnd())
       {
          QString line = in.readLine();
          line.replace(	QChar(','), QChar('.'));
           QStringList temp = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

          x = QString(temp[0]).toDouble();
          y = QString(temp[1]).toDouble();
          Poly_0 << QPointF(x,y);

          x = QString(temp[2]).toDouble();
          y = QString(temp[3]).toDouble();
          Poly_1 << QPointF(x,y);

          // qDebug() << Poly ;
          ++i;
       }
       inputFile.close();
    }
    // qDebug() << "Число строк" << i ;
    return i;
}

// 03.11.2016 di
/* int myOpenDirFileInData(QString &fileName) записывает содержимое двухколоночного файла fileName в вектор Poly.
 * Используется для чтения из файла (с интерактивным выбором) файла таблиц ЭПР и ДП. Возвращает число удачно преобразованных строк */
int Widget::myOpenDirFileInData(QString fileName)
{
    /*
    quint16 state = 0,
            st_diap = 1,
            st_phi = 2,
            st_sp1 = 4,
            st_sp2 = 8,
            st_v = 16,
            st_h = 32,
            st_s = 64,
            st_ds = 128,
            st_dp = 256,
            st_ddp =512;
    */

    int i=0;
    double tmp;
    // qDebug() << "int Widget::myOpenDirFileInData(QString fileName) \n input file = " << fileName;
//    fileName = QFileDialog::getOpenFileName(this,
//                                            tr("Загрузить новые данные"),
//                                            myOutResDir,
//                                            tr("Файлы данных (*.txt *.in)"));
    if(fileName.isNull()) return -1;
    myInDir.setPath(fileName); // Запомнить путь, где лежат входные файлы
//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
//                                                      "/home",
//                                                      tr("Images (*.png *.xpm *.jpg)"));
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream in(&inputFile);
       QString line="";
       bool ok;
       myParamText.clear();
       // qDebug() << fileName << " после QTextStream in(&inputFile) " ;
       // Poly.clear();
       // qDebug() << fileName << " после Poly.clear() " ;
       while (!in.atEnd())
       {
          line.clear();
          line = in.readLine();
          myParamText += line + QString("\n");

          // qDebug() << "while (!in.atEnd()) , i = " << i << "\n   line = " << line.left(20);

          // в прочитанной строке меняем запятые на точки для чтения цифр
          line.replace(	QChar(','), QChar('.'));
          // qDebug() << line ;
          QStringList temp = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

          if(temp.isEmpty())
          {
              continue; // Если строка пустая (только пробелы и т.п.) - читаем следующую (переходим к следующей итерации цикла)
          }

          QString paramName = temp[0].toUpper();
// startsWith(QChar c, Qt::CaseSensitivity cs = Qt::CaseSensitive)

          // if( (paramName ==  QString("/")) | (paramName ==  QString("#")) | (paramName ==  QString(";")) | (paramName ==  QString(":")) )
          if( paramName.startsWith(QChar('/')) | paramName.startsWith(QChar('#')) | paramName.startsWith(QChar(';')) | paramName.startsWith(QChar(':')) )
          {
              continue; // Если строка комментарий - читаем следующую (переходим к следующему витку цикла)
          }

          // далее пытаемся прочитать название параметра и его значение
          // описание идет комментарием где-то рядом в человеко-читаемом виде
          // параметры по-умолчанию заданы в строках ~ 57 - 80 файла widget.cpp

          if( paramName ==  QString("DIAPAZON") )
          {
              if( temp[1].toUpper() == QString("L3") )
              {
                  if( L3 == false )
                  {
                      myLoadEPR();
                      // myLoadDP( );
                  }
                  L3 = true;
                  ui->radioButton_L3->setChecked(true);
                  ui->radioButton_L2->setChecked(false);
              }
              else if( temp[1].toUpper() == QString("L2") )
              {
                  if( L3 == true )
                  {
                      myLoadEPR();
                      // myLoadDP( );
                  }
                  L3 = false;
                  ui->radioButton_L3->setChecked(false);
                  ui->radioButton_L2->setChecked(true);
              }
              // qDebug() << "DIAPAZON = " << L3 ;
              ++i; continue;
          } // если строка DIAPAZON не содержит значения L3 или L2 в явном виде, оставляем то, что было


          if( paramName ==  QString("RAKURS") )
          {
              tmp = temp[1].toDouble(&ok);
              if( ok )
              {
                  // myMsg(tr("RAKURS : всё хорошо!  Phi is changed"));
                  if( fabs(tmp - Phi) < myEps ) continue; // Если строка не поменялась - ничего не делаем, переходим на следующую строку
                  Phi = tmp;
                  ui->lineEdit_Phi->setText(QString("%1").arg(Phi, 0, 'G', 6));
                  myLoadEPR();
                  myLoadDP( );

              }
              else
              {
                  myMsg(tr("RAKURS : ошибка при чтении из файла!\n  Параметр не изменён"));
                  // qDebug() << "RAKURS : error in conversion!  Phi is not changed ";
              }
              // qDebug() << "RAKURS = " << Phi ;
              ++i; continue;
          } // если строка DIAPAZON не содержит значения L3 или L2 в явном виде, оставляем то, что было


          if( paramName ==  QString("SP") )
          {
              tmp = temp[1].toDouble(&ok);
              if( ok )
              {
                  if( fabs(tmp - mSP_1) < myEps ) continue; // Если строка не поменялась - ничего не делаем, переходим на следующую строку
                  mSP_1 = tmp;
                  ui->lineEdit_SP_1->setText(QString("%1").arg(mSP_1, 0, 'G', 6));
              }
              else
              {
                  myMsg(tr("SP_1 : ошибка при чтении из файла!\n  Параметр не изменён"));
                  // qDebug() << "SP_1 : error in conversion!  SP_1 is not changed ";
              }

              tmp = temp[2].toDouble(&ok);
              if( ok )
              {
                  if( fabs(tmp - mSP_2) < myEps ) continue; // Если строка не поменялась - ничего не делаем, переходим на следующую строку
                  mSP_2 = tmp;
                  ui->lineEdit_SP_2->setText(QString("%1").arg(mSP_2, 0, 'G', 6));
              }
              else
              {
                  myMsg(tr("SP_2 : ошибка при чтении из файла!\n  Параметр не изменён"));
                  //qDebug() << "SP_2 : error in conversion!  SP_1 is not changed ";
              }
              // qDebug() << "SP_1 = " << mSP_1 << "   SP_2 = " << mSP_2 ;
              ++i; continue;
          } // если строка DIAPAZON не содержит значения L3 или L2 в явном виде, оставляем то, что было

          if( paramName ==  QString("VH") )
          {
              tmp = temp[1].toDouble(&ok);
              if( ok )
              {
                  if( fabs(tmp - myPoint.x()) < myEps ) continue; // Если строка не поменялась - ничего не делаем, переходим на следующую строку
                  myPoint.setX(tmp);
                  ui->lineEdit_V->setText(QString("%1").arg(tmp, 0, 'G', 6));
              }
              else
              {
                  myMsg(tr("V : ошибка при чтении из файла!\n  Параметр не изменён"));
                  // qDebug() << "V : error in conversion!  V is not changed ";
              }

              tmp = temp[2].toDouble(&ok);
              if( ok )
              {
                  if( fabs(tmp - myPoint.y()) < myEps ) continue; // Если строка не поменялась - ничего не делаем, переходим на следующую строку
                  myPoint.setY(tmp);
                  ui->lineEdit_H->setText(QString("%1").arg(tmp, 0, 'G', 6));
              }
              else
              {
                  myMsg(tr("H : ошибка при чтении из файла!\n  Параметр не изменён"));
                  // qDebug() << "H : error in conversion!  H is not changed ";
              }
              // qDebug() << "V = " << myPoint.x() << "   H = " << myPoint.y() ;
              ++i;
              if(i > 0) inFile = fileName;
              continue;
          } // если строка VH не содержит значения V или H в явном виде, оставляем то, что было

          if( paramName ==  QString("EPR") )
          {
              tmp = temp[1].toDouble(&ok);
              if( ok )
              {
                  if( fabs(tmp - mEPR) < myEps ) continue; // Если строка не поменялась - ничего не делаем, переходим на следующую строку
                  mEPR = tmp;
                  ui->lineEdit_S->setText(QString("%1").arg(mEPR, 0, 'G', 6));
                  myLoadEPR();
              }
              else
              {
                  myMsg(tr("EPR : ошибка при чтении из файла!\n  Параметр не изменён"));
                  // qDebug() << "EPR : error in conversion!  EPR is not changed ";
              }

              tmp = temp[2].toDouble(&ok);
              if( ok )
              {
                  if( fabs(tmp - mEPRd) < myEps ) continue; // Если строка не поменялась - ничего не делаем, переходим на следующую строку
                  mEPRd = tmp;
                  ui->lineEdit_dS->setText(QString("%1").arg(mEPRd, 0, 'G', 6));
              }
              else
              {
                  myMsg(tr("delta EPR : ошибка при чтении из файла!\n  Параметр не изменён"));
                  // qDebug() << "delta EPR : error in conversion!  dEPR is not changed ";
              }
              // qDebug() << "EPR = " << mEPR << "   delta EPR = " << mEPRd ;
              ++i; continue;
          } // если строка EPR не содержит значения EPR или dEPR в явном виде, оставляем то, что было

          if( paramName ==  QString("DP") )
          {
              tmp = temp[1].toDouble(&ok);
              if( ok )
              {
                  if( fabs(tmp - mDP) < myEps ) continue; // Если строка не поменялась - ничего не делаем, переходим на следующую строку
                  mDP = tmp;
                  ui->lineEdit_DP->setText(QString("%1").arg(mDP, 0, 'G', 2));
                  myLoadDP( );
              }
              else
              {
                  myMsg(tr("DP : ошибка при чтении из файла!\n  Параметр не изменён"));
                  // qDebug() << "DP : error in conversion!  DP is not changed ";
              }

              tmp = temp[2].toDouble(&ok);
              if( ok )
              {
                  if( fabs(tmp - mDPd) < myEps ) continue; // Если строка не поменялась - ничего не делаем, переходим на следующую строку
                  mDPd = tmp;
                  ui->lineEdit_dDP->setText(QString("%1").arg(mDPd, 0, 'G', 2));
              }
              else
              {
                  myMsg(tr("delta DP : ошибка при чтении из файла!\n  Параметр не изменён"));
                  // qDebug() << "delta DP : error in conversion!  delta DP is not changed ";
              }
              // qDebug() << "DP = " << mDP << "   delta DP = " << mDPd ;
              ++i; continue;
          } // если строка DP не содержит значения DP или delta DP в явном виде, оставляем то, что было

          // ++i;
       }
       inputFile.close();

       if(ui->checkBox_ResName->isChecked())
       {
           QFileInfo fi(fileName);
           BegName = fi.baseName() + "_";
           ui->lineEdit_BegName->setText(BegName);
       }
    }
    // qDebug() << "Число строк с параметрами = " << i ;
    myReCalcAll();
    return i;
}

//void Widget::on_pushButton_SaveDir_clicked() // кнопка в главном окне "КУДА СОХРАНЯТЬ" . Путь для сохранения матриц записывается в myOutDir
//{
//    QStringList filters;
//    filters << "Text files (*.txt)" << "Any files (*)";

//    QFileDialog dialog(this);
//    dialog.setNameFilters(filters);
//    dialog.setFileMode(QFileDialog::Directory);
//    if(dialog.exec()) myOutDir=dialog.directory();
//}


/* int myPoly2xToTab(QPolygonF &Poly, int num, QTableWidget *myTab) берет num цифр двухколоночного вектора Poly и заполняет таблицу myTab.
 * Возвращает число удачно записанных строк. Используется для таблиц ЭПР и ДП. */
int Widget::myPoly2xToTab(QPolygonF &Poly, int num, QTableWidget *myTab)
{
    IsInit=true;
    int Rows=0;
    QString s;
    QTableWidgetItem *tiw;
    myTab->setRowCount(num);
    for(int row=0; row < num; ++row)
    {
        s= QString("%1").arg( Poly.at(row).x(), 0, 'G', 6);
        // qDebug() << "hello, int Widget::myPoly2xToTab(...)\n s = "  << s << "\t ";
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 0, tiw);
        s= QString("%1").arg( Poly.at(row).y(), 0, 'G', 6);
        // qDebug() << "hello, int Widget::myPoly2xToTab(...)\n s = " << s << "\n";
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 1, tiw);
        // qDebug() << "hello, myWrite Poly2Tab\n Point[" << i << "] = " << p.at(i) ;

        ++Rows;
    }
    IsInit=false;
    return Rows;
}

/* int myPoly4xToTab(QPolygonF &Poly_0, QPolygonF &Poly_1, int num, QTableWidget *myTab) берет num цифр из двух двухколоночных векторов
 * Poly_0 и Poly_1 и заполняет таблицу myTab. В строках - x0, y0, x1, y1.
 * Возвращает число удачно записанных строк. Используется для таблиц VH. */
int Widget::myPoly4xToTab(QPolygonF &Poly_0, QPolygonF &Poly_1, int num, QTableWidget *myTab)
{
    IsInit=true;
    int Rows=0;
    QString s;
    QTableWidgetItem *tiw;
    myTab->setRowCount(num);
    for(int row=0; row < num; ++row)
    {
        s= QString("%1").arg( Poly_0.at(row).x(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 0, tiw);

        s= QString("%1").arg( Poly_0.at(row).y(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 1, tiw);

        s= QString("%1").arg( Poly_1.at(row).x(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 2, tiw);

        s= QString("%1").arg( Poly_1.at(row).y(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 3, tiw);

        ++Rows;
    }
    IsInit=false;
    return Rows;
}

/* int myChangeTab2Poly(QTableWidget *myTab, QPolygonF &Poly, int row, int column) При изменении значения в таблице ЭПР или ДП,
 * запускается обработка сигнала void Widget::on_tableWidget_EPR_cellChanged(int row, int column) или ..._DP_... соответственно,
 * которая задает myTab, Poly и вызывает эту функцию. Новое значение проходит проверку на ошибки (является ли числом и попадает ли в диапазон).
 * возвращает 0 если хорошо и 1 если таблица не определена */
int Widget::myChangeTab2Poly(QTableWidget *myTab, QPolygonF &Poly, int row, int column)
{
    double myMin, myMax;
    QString str;
    if(myTab == ui->tableWidget_EPR)
    {
        myMin=minEPR; myMax=maxEPR;
        str="Эффективная Площадь Рассеяния (ЭПР),Эффективной Площади Рассеяния";
    }
    else if(myTab == ui->tableWidget_DP)
    {
        myMin=minDP; myMax=maxDP;
        str="Дальностный Портрет (ДП),Дальностного Портрета";
    }
    else return 1;

    switch(column)
    {
    case 0:
        myCheckNewValueTab(myTab, row, column, str, Poly[row].rx(), myMin, myMax );
        break;
    case 1:
        myCheckNewValueTab(myTab, row, column, str, Poly[row].ry(), myMin, myMax );
        break;
    default:
        break;
    }
    return 0;
}

/* int myChangeTab4Poly(QTableWidget *myTab, QPolygonF &Poly_0, QPolygonF &Poly_1, int row, int column) При изменении значения в таблице VH,
 * запускается обработка сигнала void Widget::on_tableWidget_VH_cellChanged(int row, int column),
 * которая задает myTab, Poly_0, Poly_1 и вызывает эту функцию. Новое значение проходит проверку на ошибки
 * (является ли числом и попадает ли в диапазон). возвращает 0 если хорошо и 1 если таблица не определена */
int Widget::myChangeTab4Poly(QTableWidget *myTab, QPolygonF &Poly_0, QPolygonF &Poly_1, int row, int column)
{
    switch(column)
    {
    case 0:
        myCheckNewValueTab(myTab, row, column, "СКОРОСТЬ,СКОРОСТИ", Poly_0[row].rx(), minV, maxV );
        break;
    case 1:
        myCheckNewValueTab(myTab, row, column, "ВЫСОТА,ВЫСОТЫ", Poly_0[row].ry(), minH, maxH );
        break;
    case 2:
        myCheckNewValueTab(myTab, row, column, "СКОРОСТЬ,СКОРОСТИ", Poly_1[row].rx(), minV, maxV );
        break;
    case 3:
        myCheckNewValueTab(myTab, row, column, "ВЫСОТА,ВЫСОТЫ", Poly_1[row].ry(), minH, maxH );
        break;
    default:
        return 1;
    }
    return 0;
}

/* bool myCheckNewValue(QLineEdit *line, QString str, double &Val, double myMin, double myMax);
 * Проверяет значение параметра Val, введенное в строке line, на "НЕ ЦИФРУ" и на границы диапазона myMin - myMax */
bool Widget::myCheckNewValue(QLineEdit *line, QString str, double &Val, double myMin, double myMax )// QString("СКОРОСТЬ,СКОРОСТИ")
{
    if(IsInit) return false;
    IsInit = true;
    bool ok;

    QStringList lst = str.split(QChar(','), QString::SkipEmptyParts);
    QString text, myQString = line->text();

    myQString.replace( QChar(','), QChar('.'));
    myQString.remove( QRegExp("\\s+") ); // , Qt::CaseSensitive

    double oldX=Val, newX = myQString.toDouble(&ok);
    QTextStream myWarn(&text);

    if(!ok)
        {
            myWarn << tr(" ==   ")  << lst[0] << " = " << myQString << tr("   == \n Это не число ! ") ;
            QMessageBox::warning(this, tr("Ошибка редактирования"), text);
            line->setText( QString("%1").arg( oldX, 0, 'G', 8) );
            Val=oldX;
            IsInit = false;
            myChangeValueAccepted=false;
            return false;
        }
    else if( (newX==0.0) && (line != ui->lineEdit_Phi) )  // проверить
    {
        myWarn << tr(" Значение ") << lst[1] << tr(" равно НУЛЮ ! \n == ") << lst[0] << tr("  = ")
              << myQString << tr("   == \n Диапазон [ ") << myMin << tr(" - ") << myMax
              << tr(" ] \n ПОДТВЕРДИТЕ правильность введенного значения ! ") ;
        QMessageBox::StandardButton myRepl = QMessageBox::question(this, tr("Подтвердите ввод"), text,
                                                                   QMessageBox::StandardButtons( QMessageBox::Yes | QMessageBox::No ),
                                                                   QMessageBox::No );
        if(myRepl == QMessageBox::Yes)
        {
            Val=newX;
            line->setText( QString("%1").arg( Val, 0, 'G', 8) );
            IsInit=false;
            myChangeValueAccepted=true;
            return true;
        }
        else
        {
            line->setText( QString("%1").arg( oldX, 0, 'G', 8) );
            Val=oldX;
            IsInit = false;
            myChangeValueAccepted=false;
            return false;
        }
    }
    else if( (newX < myMin) || (newX > myMax) )
    {
        myWarn << tr(" Значение ") << lst[1] << tr(" выходит за диапазон ПО УМОЛЧАНИЮ ! \n == ") << lst[0] << tr("  = ")
              << myQString << tr("   == \n Диапазон [ ") << myMin << tr(" - ") << myMax
              << tr(" ] \n ПОДТВЕРДИТЕ правильность введенного значения ! ") ;
        QMessageBox::StandardButton myRepl = QMessageBox::question(this, tr("Подтвердите ввод"), text,
                                                                   QMessageBox::StandardButtons( QMessageBox::Yes | QMessageBox::No ),
                                                                   QMessageBox::No );
        if(myRepl == QMessageBox::Yes)
        {
            Val=newX;
            line->setText( QString("%1").arg( Val, 0, 'G', 8) );
            IsInit=false;
            myChangeValueAccepted=true;
            return true;
        }
        else
        {
            line->setText( QString("%1").arg( oldX, 0, 'G', 8) );
            Val = oldX;
            IsInit = false;
            myChangeValueAccepted=false;
            return false;
        }
    }
    else
    {
        if(newX == oldX)
        {
            IsInit=false;
            myChangeValueAccepted=false;
            return false;
        }
        Val = newX;
        line->setText( QString("%1").arg( Val, 0, 'G', 8) );
        myChangeValueAccepted=true;
        IsInit=false;
        return true;
    }
    IsInit=false;
    return false;
}

/* bool myCheckNewValueTab(QTableWidget *tab, int row, int column, QString str, double &Val, double myMin, double myMax);
 * Проверяет значение параметра Val, введенное в ячейке [row, column] таблицы tab, на "НЕ ЦИФРУ" и на границы диапазона myMin - myMax */
bool Widget::myCheckNewValueTab(QTableWidget *tab, int row, int column, QString str, double &Val, double myMin, double myMax )// QString("СКОРОСТЬ СКОРОСТИ")
{
    if(IsInit) return false;
    IsInit = true;
    bool ok;
    QTableWidgetItem *tiw=tab->item(row, column);
    QStringList lst = str.split(QChar(','), QString::SkipEmptyParts);
    QString valStr, text, myQString=tiw->text();

    myQString.replace( QChar(','), QChar('.'));
    myQString.remove( QRegExp("\\s+") ); // , Qt::CaseSensitive

    double oldX=Val, newX = myQString.toDouble(&ok);
    QTextStream myWarn(&text);

    if(!ok)
        {
            myWarn << tr(" ==   ")  << lst[0] << " = " << myQString << tr("   == \n Это не число ! ") ;
            QMessageBox::warning(this, tr("Ошибка редактирования"), text);
            valStr = QString("%1").arg( oldX, 0, 'G', 8);
            tiw=new QTableWidgetItem(valStr);
            tab->setItem(row, column, tiw);
            Val=oldX;
            IsInit = false;
            myChangeValueAccepted=false;
            return false;
        }
    else if( newX==0.0 )
    {
        myWarn << tr(" Значение ") << lst[1] << tr(" равно НУЛЮ ! \n == ") << lst[0] << tr("  = ")
              << myQString << tr("   == \n Диапазон [ ") << myMin << tr(" - ") << myMax
              << tr(" ] \n ПОДТВЕРДИТЕ правильность введенного значения ! ") ;
        QMessageBox::StandardButton myRepl = QMessageBox::question(this, tr("Подтвердите ввод"), text,
                                                                   QMessageBox::StandardButtons( QMessageBox::Yes | QMessageBox::No ),
                                                                   QMessageBox::No );
        if(myRepl == QMessageBox::Yes)
        {
            Val=newX;
            valStr = QString("%1").arg( Val, 0, 'G', 8);
            tiw=new QTableWidgetItem(valStr);
            tab->setItem(row, column, tiw);
            // myReCalcAll();
            IsInit=false;
            myChangeValueAccepted=true;
            return true;
        }
        else
        {
            valStr= QString("%1").arg( oldX, 0, 'G', 8);
            tiw=new QTableWidgetItem(valStr);
            tab->setItem(row, column, tiw);
            Val=oldX;
            IsInit = false;
            myChangeValueAccepted=false;
            return false;
        }
    }
    else if( (newX < myMin) || (newX > myMax) )
    {
        myWarn << tr(" Значение ") << lst[1] << tr(" выходит за диапазон ПО УМОЛЧАНИЮ ! \n == ") << lst[0] << tr("  = ")
              << myQString << tr("   == \n Диапазон [ ") << myMin << tr(" - ") << myMax
              << tr(" ] \n ПОДТВЕРДИТЕ правильность введенного значения ! ") ;
        QMessageBox::StandardButton myRepl = QMessageBox::question(this, tr("Подтвердите ввод"), text,
                                                                   QMessageBox::StandardButtons( QMessageBox::Yes | QMessageBox::No ),
                                                                   QMessageBox::No );
        if(myRepl == QMessageBox::Yes)
        {
            Val=newX;
            valStr= QString("%1").arg( Val, 0, 'G', 8);
            tiw=new QTableWidgetItem(valStr);
            tab->setItem(row, column, tiw);
            IsInit=false;
            myChangeValueAccepted=true;
            return true;
        }
        else
        {
            valStr = QString("%1").arg( oldX, 0, 'G', 8);
            tiw=new QTableWidgetItem(valStr);
            tab->setItem(row, column, tiw);
            Val = oldX;
            IsInit = false;
            myChangeValueAccepted=false;
            return false;
        }
    }
    else
    {
        if(newX == oldX)
        {
            IsInit=false;
            myChangeValueAccepted=false;
            return false;
        }
        Val = newX;
        valStr = QString("%1").arg( Val, 0, 'G', 8);
        tiw=new QTableWidgetItem(valStr);
        tab->setItem(row, column, tiw);
        myChangeValueAccepted=true;
        IsInit=false;
       return true;
    }
    IsInit=false;
    return false;
}

/* int myOpenFile2x4write(QString &fileName, QPolygonF &Poly) Записывает многоугольник Poly (ЭПР или ДП) в файл (выбирается интерактивно).
 * Имя по умолчанию - fileName. Возвращает число строк, если хорошо и -1 если файл не открыли */
int Widget::myOpenFile2x4write(QString &fileName, QPolygonF &Poly)
{
    int i=-1, num=Poly.size();
    QFileDialog filedialog(this);
    filedialog.setFileMode(QFileDialog::AnyFile);
    fileName = filedialog.getSaveFileName(
                this, tr("Open VH polygon"), fileName, tr("Polygon Files (*.txt)"));
    if(fileName.isNull()) return -1;

    QFile outputFile(fileName);
    QString s;
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        i=0;
        QTextStream myOut(&outputFile);
        for(int j=0; j < num ; ++j)
        {
            s= QString("%1 %2").arg( Poly[j].x(), 0, 'G', 6).arg( Poly[j].y(), 0, 'G', 6);
            myOut << s << "\n";
            ++i;
        }
        outputFile.close();
    }
    return i;
}

/* int myOpenFile4x4write(QString &fileName, QPolygonF &Poly_0, QPolygonF &Poly_1) Записывает многоугольники Poly_0 и Poly_1 (VH) в файл (интерактивно).
 * Имя по умолчанию - fileName. Возвращает число строк, если хорошо и -1 если файл не открыли */
int Widget::myOpenFile4x4write(QString &fileName, QPolygonF &Poly_0, QPolygonF &Poly_1)
{
    int i=-1, num=Poly_0.size();
    QFileDialog filedialog(this);
    filedialog.setFileMode(QFileDialog::AnyFile);
    fileName = filedialog.getSaveFileName(
                this, tr("Open VH polygon"), fileName, tr("Polygon Files (*.txt)"));
    if(fileName.isNull()) return -1;

    QFile outputFile(fileName);
    QString s;
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        i=0;
        QTextStream myOut(&outputFile);
        for(int j=0; j < num ; ++j)
        {
            s= QString("%1 %2 %3 %4").arg( Poly_0[j].x(), 0, 'G', 6).arg( Poly_0[j].y(), 0, 'G', 6).arg( Poly_1[j].x(), 0, 'G', 6).arg( Poly_1[j].y(), 0, 'G', 6);
            myOut << s << "\n";
            ++i;
        }
        outputFile.close();
    }
    return i;
}

/* void myFillMatrVH(void) Заполняет матрицу VH_b по площадям пересечений многоугольников с нулевой вероятностью */
void Widget::myFillMatrVH(void)
{
    double t, S;
    for(int col=0; col < 7; ++col)
    {
        setMyPoly(col, myPoly_0, myPoly_1);
        S=myPolyArea(myPoly_0);
        for(int row=0; row < 7; ++row)
        {
            setMyPoly(row, myPoly1_0, myPoly1_1);
            myPoly2=QPolygonF(myPoly_0.intersected(myPoly1_0));
            if(myPoly2.isEmpty()) mVH_b[row][col]=0.01;
            else
            {
                t = myPolyArea(myPoly2)/S;
                t > 0.01 ? mVH_b[row][col]=t : mVH_b[row][col]=0.01;
            }
        }
    }
}

/* double myPolyArea(QPolygonF &Poly) Возвращает площадь многоугольника */
double Widget::myPolyArea(QPolygonF &Poly)
{
    int k, Num=Poly.size();
    double S=0.0;
    for(int i=0; i<Num; ++i)
    {
        k= i+1<Num ? i+1 : 0;
        S+=0.5*(Poly.at(k).y()+Poly.at(i).y())*(Poly.at(k).x()-Poly.at(i).x());
    }
    return S;
}

/* void setMyPoly(int myPolyNum, QPolygonF &Poly_0, QPolygonF &Poly_1) Определяет Poly_0 и Poly_1 по номеру myPolyNum
 * (0 - СА, 1 - ТА, 2 - ВРТ, 3 - ГЗЛА, 4 - КР) */
void Widget::setMyPoly(int myPolyNum, QPolygonF &Poly_0, QPolygonF &Poly_1)
{
    switch (myPolyNum) {
    case 0:
        Poly_0 = QPolygonF(Poly1SA_0);
        Poly_1 = QPolygonF(Poly1SA_1);
        break;
    case 1:
        Poly_0 = QPolygonF(Poly2SAB2_0);
        Poly_1 = QPolygonF(Poly2SAB2_1);
        break;
    case 2:
        Poly_0 = QPolygonF(Poly3TA_0);
        Poly_1 = QPolygonF(Poly3TA_1);
        break;
    case 3:
        Poly_0 = QPolygonF(Poly4VRT_0);
        Poly_1 = QPolygonF(Poly4VRT_1);
        break;
    case 4:
        Poly_0 = QPolygonF(Poly5GZ_0);
        Poly_1 = QPolygonF(Poly5GZ_1);
        break;
    case 5:
        Poly_0 = QPolygonF(Poly6KR_0);
        Poly_1 = QPolygonF(Poly6KR_1);
        break;
    case 6:
        Poly_0 = QPolygonF(Poly7ADA_0);
        Poly_1 = QPolygonF(Poly7ADA_1);
        break;
    default:
        break;
    }
    return ;
}

/* int setVHtable(int myPolyNum) Отображает таблицу VH по номеру myPolyNum (0 - СА, 1 - ТА, 2 - ВРТ, 3 - ГЗЛА, 4 - КР).
 * Возвращает число строк */
int Widget::setVHtable(int myPolyNum)
{
    IsInit=true;
    int num, Rows=0;
    QString s;
    QTableWidget *myTab=ui->tableWidget_VH;
    QTableWidgetItem *tiw;
    setMyPoly(myPolyNum, myPoly_0, myPoly_1);
    num=myPoly_0.size();
    myTab->setRowCount(num);
    for(int row=0; row < num; ++row)
    {
        s= QString("%1").arg( myPoly_0.at(row).x(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 0, tiw);

        s= QString("%1").arg( myPoly_0.at(row).y(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 1, tiw);

        s= QString("%1").arg( myPoly_1.at(row).x(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 2, tiw);

        s= QString("%1").arg( myPoly_1.at(row).y(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 3, tiw);

        ++Rows;
    }
    IsInit=false;
    return Rows;
}

/* void setMyPtab(int myPTabNum) Устанавливает указатель pm5x5 на матрицу, которую отобразит функция void setPtable(int myPTabNum) */
void Widget::setMyPtab(int myPTabNum)
{
    switch (myPTabNum) {
    case 0:
        pm5x5=&mVH_b;
        break;
    case 1:
        pm5x5=&mVH_g;
        break;
    case 2:
        pm5x5=&mVH_p;
        break;
    case 3:
        pm5x5=&mS_b;
        break;
    case 4:
        pm5x5=&mS_g;
        break;
    case 5:
        pm5x5=&mS_p;
        break;
    case 6:
        pm5x5=&mDP_b;
        break;
    case 7:
        pm5x5=&mDP_g;
        break;
    case 8:
        pm5x5=&mDP_p;
        break;
    case 9:
        pm5x5=&mSP_p;
        break;
    case 10:
        pm5x5=&mVHg_Sg_g;
        break;
    case 11:
        pm5x5=&mVHg_Sg_p;
        break;
    case 12:
        pm5x5=&mVHg_Sg_DPg_g;
        break;
    case 13:
        pm5x5=&mVHg_Sg_DPg_p;
        break;
    case 14:
        pm5x5=&mVHg_Sg_G_SP_g;
        break;
    case 15:
        pm5x5=&mVHg_Sg_G_SP_p;
        break;
    case 16:
        pm5x5=&mVHg_Sg_P_SP_g;
        break;
    case 17:
        pm5x5=&mVHg_Sg_P_SP_p;
        break;
    case 18:
        pm5x5=&mVHg_Sg_DPg_G_SP_g;
        break;
    case 19:
        pm5x5=&mVHg_Sg_DPg_G_SP_p;
        break;
    case 20:
        pm5x5=&mVHg_Sg_DPg_P_SP_g;
        break;
    case 21:
        pm5x5=&mVHg_Sg_DPg_P_SP_p;
        break;
    case 22:
        pm5x5=&mVH_S_g;
        break;
    case 23:
        pm5x5=&mVH_S_p;
        break;
    case 24:
        pm5x5=&mVH_DP_g;
        break;
    case 25:
        pm5x5=&mVH_DP_p;
        break;
    case 26:
        pm5x5=&mVH_DP_S_g;
        break;
    case 27:
        pm5x5=&mVH_DP_S_p;
        break;
    case 28:
        pm5x5=&mVH_S_DP_g;
        break;
    case 29:
        pm5x5=&mVH_S_DP_p;
        break;
    case 30:
        pm5x5=&mVH_S_SP_g;
        break;
    case 31:
        pm5x5=&mVH_S_SP_p;
        break;
    case 32:
        pm5x5=&mVH_S_DP_SP_g;
        break;
    case 33:
        pm5x5=&mVH_S_DP_SP_p;
        break;

    default:
        break;
    }
}

/* void setPtable(int myPTabNum) Вызывает void setMyPtab(int myPTabNum) для получения указателя pm5x5 на матрицу вероятностей.
 * Отображает матрицу в таблице главного окна, выделяет цветом значения */
void Widget::setPtable(int myPTabNum)
{
    QString s;
    QBrush myBrush00= QBrush(QColor::fromRgb(0,0,0,255), Qt::NoBrush);
    QBrush myBrush05= QBrush(Qt::cyan, Qt::SolidPattern);
    QBrush myBrush10= QBrush(Qt::green, Qt::SolidPattern);

    QTableWidget *myTab=ui->tableWidget_P;
    QTableWidgetItem *tiw;
    setMyPtab(myPTabNum);
    for(int row=0; row < 7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            s= QString("%1").arg( (*pm5x5)[row][col], 0, 'G', 3);
            tiw=new QTableWidgetItem(s);
            if((*pm5x5)[row][col]<0.15) tiw->setBackground(myBrush00);
                           else if((*pm5x5)[row][col]<0.8) tiw->setBackground(myBrush05);
                               else tiw->setBackground(myBrush10);
            myTab->setItem(row, col, tiw);
        }
    }
}

/* void myPointInVH(void); Читает поля ввода V и H главного окна. Заполняет значения gVH[i]. Вероятности находит,
 * вызывая функцию double Widget::myPointInVHnum(QPolygonF &Poly_0, QPolygonF &Poly_1, double x, double y)*/
void Widget::myPointInVH(void)
{
    double t;
    QString myQString=ui->lineEdit_V->text();
    myPoint.setX(myQString.toDouble());
    myQString=ui->lineEdit_H->text();
    myPoint.setY(myQString.toDouble());
    for(int i=0; i < 7; ++i)
    {
        setMyPoly(i, myPoly_0, myPoly_1);
        t = myPointInVHnum(myPoly_0, myPoly_1, myPoint.x(), myPoint.y() );
        t < 0.01 ? gVH[i]=0.01 : gVH[i]=t;
    }
}

/* void myFillMatrVHg(void); Заполняет mVH_g[row][column]= gVH[row]*mVH_b[row][column] по стандартному алгоритму . */
void Widget::myFillMatrVHg(void)
{
    double t, S, Smax=0.0;
    for(int row=0; row<7; ++row)
    {
        t=0.0;
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVH_b[row][col] * gVH[col];
            t= t <0.01 ? 0.01 : t;
            S+=t;
            mVH_g[row][col]=t;
        }
        Sm[row]=S;
        Smax = std::max(Smax, S);
        if(Sm[row]>=0.99) tNVO[row]=0.01;
        else tNVO[row]=1.0-Sm[row];
    }
}

/* void myFillMatrVHp(void) Заполняет mVH_p[row][column]= mVH_b[row][column]/(сумма[row] + НВО[row] ) по стандартному алгоритму . */
void Widget::myFillMatrVHp(void)
{
    double t, S, Smax=0.0;
    for(int row=0; row<7; ++row)
    {
        t=0.0;
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVH_g[row][col] / (Sm[row] + tNVO[row]);
            t= t <0.01 ? 0.01 : t;
            S+=t;
            mVH_p[row][col]=t;
        }
        Smax = std::max(Smax, S);
    }

    if(Smax>=0.99)  mNVO=0.01;
    else mNVO=1.0-Smax;
}

/* void myLoadEPR(void); Формирует запрос  к функции myOpenFile2x4read(myFileName, PolyEPR)
 * на чтение файла типа :/data_in/EPR_L3_00.txt в зависимости от угла и диапазона и запись его в вектор ЭПР */
void Widget::myLoadEPR(void)
{
    QString myQString=ui->lineEdit_Phi->text();
    Phi=myQString.toDouble();
    L3 = ui->radioButton_L3->isChecked();
    if(L3)
    {
        if( fabs(Phi) <= 45.0 ) myFileName = QString("./data_in/EPR_L3_00.txt");
        if( fabs(Phi) > 45.0 && fabs(Phi) <= 135.0 ) myFileName = QString("./data_in/EPR_L3_90.txt");
        if( fabs(Phi) > 135.0 && fabs(Phi) <= 225.0 ) myFileName = QString("./data_in/EPR_L3_180.txt");
    }
    else
    {
        if( fabs(Phi) <= 45.0 ) myFileName = QString("./data_in/EPR_L2_00.txt");
        if( fabs(Phi) > 45.0 && fabs(Phi) <= 135.0 ) myFileName = QString("./data_in/EPR_L2_90.txt");
        if( fabs(Phi) > 135.0 && fabs(Phi) <= 225.0 ) myFileName = QString("./data_in/EPR_L2_180.txt");
    }
    myOpenFile2x4read(myFileName, PolyEPR);
}

/* void myFillMatrEPR(void); По данным PolyEPR строит матрицу mS_b[row][column] */
void Widget::myFillMatrEPR()
{
    double t;
    for(int row=0; row < 7; ++row)
    {
        for(int column=0; column < 7; ++column)
        {
            if(row == column) t=1.0;
            else t=myIntegral(PolyEPR[row].x(), PolyEPR[row].y(), PolyEPR[column].x(), PolyEPR[column].y());
            mS_b[row][column]= (t>0.01 ? t : 0.01);
        }
    }
}

/* void myPointInEPR(void) Читает поле ввода ЭПР главного окна. Заполняет значения gS[i]. Вероятности находит,
 * вызывая функцию double Widget::myIntegral( mEPR, mEPRd, PolyEPR[column].x(), PolyEPR[column].y() ) */
void Widget::myPointInEPR()
{
    double t;
    QString myQString=ui->lineEdit_S->text();
    mEPR=myQString.toDouble();

    myQString=ui->lineEdit_dS->text();
    mEPRd=myQString.toDouble();
    for(int column=0; column < 7; ++column)
    {
        t=myIntegral(mEPR, mEPRd, PolyEPR[column].x(), PolyEPR[column].y());
        gS[column]= (t>0.01 ? t : 0.01);
    }
}

/* double myGaussFn(double x0, double sigma, double x) Возвращает значение Гамма-функции с центром в x0 шириной sigma для значения x */
double Widget::myGaussFn(double x0, double sigma, double x)
{
    double res;
    res=exp(-(x-x0)*(x-x0)/(2.0*sigma*sigma))/(sigma*sqrt(2*3.141592653));
    return res>myEps/1000.0 ? res : 0.0;
}

/* double myFunc(double x1, double sigma1, double x2, double sigma2, double x) Возвращает значение произведения Гамма-функций
 * или min(Gamma1, Gamma2) для (x1, sigma1) и (x2, sigma2) для значения x */
double Widget::myFunc(double x1, double sigma1, double x2, double sigma2, double x)
{
    double res;
    if(ui->radioButton_GC_Sq->isChecked())
        res = sqrt(myGaussFn(x1, sigma1, x))*sqrt(myGaussFn(x2, sigma2, x));
    else res = std::min(myGaussFn(x1, sigma1, x), myGaussFn(x2, sigma2, x));
    return res > myEps/1000.0 ? res : 0.0;
}

/* double myIntegral(double x1, double sigma1, double x2, double sigma2) Возвращает значение интеграла от произведения Гамма-функций
 * или min(Gamma1, Gamma2) для (x1, sigma1) и (x2, sigma2) */
double Widget::myIntegral(double x1, double sigma1, double x2, double sigma2)
{   // методом Симпсона
    int i=0, N=320;
    double x, xMin, xMax, step, res;

    xMin=std::max(x1-5.0*sigma1,x2-5.0*sigma2); //-5.0*s
    xMax=std::min(x1+5.0*sigma1,x2+5.0*sigma2); //+5.0*s

    step=(xMax-xMin)/N;
    if(step < myEps) return 0.0;
    x=xMin;
    res=myFunc(x1, sigma1, x2, sigma2, x);
    do{
        if(i!=0){
            ++i;  x=xMin+step*i;
            res+=2.0*myFunc(x1, sigma1, x2, sigma2, x);
        }
        ++i;  x=xMin+step*i;
        res+=4.0*myFunc(x1, sigma1, x2, sigma2, x);
    } while(i<N);  //(x<=xMax)
    res+=myFunc(x1, sigma1, x2, sigma2, xMax);
    return res*step/3.0;
}

/* void myFillMatrEPRg(void) Заполняет mS_g[row][column]= gS[row]*mS_b[row][column] по стандартному алгоритму . */
void Widget::myFillMatrEPRg()
{
    double t, S, Smax=0.0;
    for(int row=0; row<7; ++row)
    {
        t=0.0;
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mS_b[row][col] * gS[col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mS_g[row][col]=t;
        }
        Sm[row]=S;
        Smax = std::max(Smax, S);
        if(Sm[row]>=0.99) tNVO[row]=0.01;
        else tNVO[row]=1.0-Sm[row];
    }
    if(Smax>=0.99)  mNVO=0.01;
    else mNVO=std::min(mNVO, 1.0 - Smax);
}

/* void myFillMatrEPRp(void) Заполняет mS_p[row][column]= mS_b[row][column]/(сумма[row] + НВО[row] ) по стандартному алгоритму . */
void Widget::myFillMatrEPRp()
{
    double t, S, Smax=0.0;
    for(int row=0; row<7; ++row)
    {
        t=0.0;
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mS_g[row][col]/(Sm[row] + tNVO[row]);
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mS_p[row][col]=t;
        }
        Smax = std::max(Smax, S);
    }
}

/* void setEPRtable(void) Заполняет таблицу ЭПР */
void Widget::setEPRtable(void)
{
    IsInit=true; // Включаем "режим автоматического изменения", чтобы СЛОТЫ не пытались обработать программные изменения таблицы
    int num;
    QString s;
    QTableWidget *myTab=ui->tableWidget_EPR;
    QTableWidgetItem *tiw;
    num=PolyEPR.size();
    myTab->setRowCount(num);
    for(int row=0; row < num; ++row)
    {
        s= QString("%1").arg( PolyEPR.at(row).x(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 0, tiw);

        s= QString("%1").arg( PolyEPR.at(row).y(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 1, tiw);
    }
    IsInit=false;
}

/* void myLoadDP(void) Читает из файла :/data_in/DP_All.txt пары длина-ширина для всех классов, находит максимальную проекцию вдоль ракурса,
 * для каждой пары в зависимости от угла и записывает среднюю величину и ошибку для каждого класса целей в вектор ДП */
void Widget::myLoadDP(void)
{
    int i=0;
    double L, W, mL[7], sL = 0.0, dL, mW[7], sW = 0.0, dW, tPhi;
    QString str = "";
    QString myFileName = QString("./data_in/DP_All.txt");
    QString myQString=ui->lineEdit_Phi->text();
    QStringList temp;

    Phi=myQString.toDouble();
    tPhi=Phi*3.141592653/180.0;

    QFile inputFile(myFileName);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&inputFile);
        PolyDP.clear();
        // PolyFP.clear();
        while (!in.atEnd())
        {
            QString line = in.readLine();
            line.replace(	QChar(','), QChar('.'));
            temp = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

            L = QString(temp[0]).toDouble();
            W = QString(temp[1]).toDouble();
            if(str == temp[2]) // продолжаем класс целей
            {
                mL[i] = std::max(L*fabs(cos(tPhi)), W*fabs(sin(tPhi)));
                mW[i] = std::max(L*fabs(sin(tPhi)), W*fabs(cos(tPhi)));
                sL+=mL[i];
                sW+=mW[i];
                ++i;
            }
            else if( sL == 0.0 )  // начинаем файл с классами целей
            {
                i=0;
                str = temp[2];
                mL[i] = std::max(L*fabs(cos(tPhi)), W*fabs(sin(tPhi)));
                mW[i] = std::max(L*fabs(sin(tPhi)), W*fabs(cos(tPhi)));
                sL=mL[i];
                sW=mW[i];
                ++i;
            }
            else // сменился класс цели
            {
                // заканчиваем текущий класс
                sL /= i;
                sW /= i;
                dL = 0.0;
                dW = 0.0;
                for(int j=0; j<i; ++j)
                {
                    dL += (mL[j]-sL)*(mL[j]-sL);
                    dW += (mW[j]-sW)*(mW[j]-sW);
                }

                if(i==1) //если в классе только один ЛА
                {
                    dL=sL/4.0;
                    dW=sW/4.0;
                }
                else
                {
                    dL = sqrt(dL/double(i-1));
                    dW = sqrt(dW/double(i-1));
                }
                PolyDP << QPointF(sL, dL);
                // PolyFP << QPointF(sW, dW);
                // qDebug() << PolyFP;


                // новый класс
                str = temp[2];
                i=0;
                mL[i] = std::max(L*fabs(cos(tPhi)), W*fabs(sin(tPhi)));
                sL=mL[i];
                mW[i] = std::max(L*fabs(sin(tPhi)), W*fabs(cos(tPhi)));
                sW=mW[i];
                ++i;
            }
        }
        // заканчиваем последний класс
        sL /= i;
        dL = 0.0;
        sW /= i;
        dW = 0.0;
        for(int j=0; j<i; ++j)
        {
            dL += (mL[j]-sL)*(mL[j]-sL);
            dW += (mW[j]-sW)*(mW[j]-sW);
        }
        dL /= double(i-1);
        dW /= double(i-1);

        PolyDP << QPointF(sL, std::max( sL/4.0, sqrt(dL) ) );
        // PolyFP << QPointF(sW, std::max( sW/4.0, sqrt(dW) ) );
        inputFile.close();
    }
}

/* void myFillMatrDP(void) По данным PolyDP строит матрицу mDP_b[row][column] */
void Widget::myFillMatrDP(void)
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int column=0; column<7; ++column)
        {
            if(row == column) t=1.0;
            else t=myIntegral(PolyDP[row].x(), PolyDP[row].y(), PolyDP[column].x(), PolyDP[column].y());
            mDP_b[row][column]= (t>0.01 ? t : 0.01);
        }
    }
}

/* void myPointInDP(void) Читает поле ввода ДП главного окна. Заполняет значения gDP[i]. Вероятности находит,
 * вызывая функцию double Widget::myIntegral( PolyDP[row].x(), PolyDP[row].y(), PolyDP[column].x(), PolyDP[column].y() ) */
void Widget::myPointInDP()
{
    double t;
    QString myQString=ui->lineEdit_DP->text();
    mDP=myQString.toDouble();

    myQString=ui->lineEdit_dDP->text();
    mDPd=myQString.toDouble();
    for(int column=0; column<7; ++column)
    {
        t=myIntegral(mDP, mDPd, PolyDP[column].x(), PolyDP[column].y());
        gDP[column]= (t>0.01 ? t : 0.01);
    }
}

/* void myFillMatrDPg(void) Заполняет mDP_g[row][column]= gDP[row]*mDP_b[row][column] по стандартному алгоритму . */
void Widget::myFillMatrDPg()
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mDP_b[row][col] * gDP[col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mDP_g[row][col]=t;
        }
        Sm[row]=S;
        if(Sm[row]>=0.99) tNVO[row]=0.01;
        else tNVO[row]=1.0-Sm[row];
    }

    // этот текст из myFillMatrEPRg()
    //Sm[row]=S;
    //Smax = std::max(Smax, S);
    //if(Sm[row]>=0.99) tNVO[row]=0.01;
    //else tNVO[row]=1.0-Sm[row];
    //}
    //if(Smax>=0.99)  mNVO=0.01;
    //else mNVO=std::min(mNVO, 1.0 - Smax);
}

/* void myFillMatrDPp(void) Заполняет mDP_p[row][column]= mDP_g[row][column]/(сумма[row] + НВО[row] ) по стандартному алгоритму . */
void Widget::myFillMatrDPp()
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mDP_g[row][col] / (Sm[row] + tNVO[row]);
            t= t <0.01 ? 0.01 : t;
            mDP_p[row][col]=t;
        }
    }
}

/* void setDPtable(void) Заполняет таблицу ДП */
void Widget::setDPtable()
{
    IsInit=true;
    int num;
    QString s;
    QTableWidget *myTab=ui->tableWidget_DP;
    QTableWidgetItem *tiw;
    num=PolyDP.size();
    myTab->setRowCount(num);
    for(int row=0; row < num; ++row)
    {
        s= QString("%1").arg( PolyDP.at(row).x(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 0, tiw);
        s= QString("%1").arg( PolyDP.at(row).y(), 0, 'G', 6);
        tiw=new QTableWidgetItem(s);
        myTab->setItem(row, 1, tiw);
    }
    IsInit=false;
}

/* void myFillMatrFP(void) По данным PolyFP строит матрицу mFP_b[row][column] */
//void Widget::myFillMatrFP(void)
//{
//    double t;
//    for(int row=0; row<7; ++row)
//    {
//        for(int column=0; column<7; ++column)
//        {
//            if(row == column) t=1.0;
//            else t=myIntegral(PolyFP[row].x(), PolyFP[row].y(), PolyFP[column].x(), PolyFP[column].y());
//            mFP_b[row][column]= (t>0.01 ? t : 0.01);
//        }
//    }
//}

/* void myPointInFP(void) Читает поле ввода ЧП главного окна. Заполняет значения gFP[i]. Вероятности находит,
 * вызывая функцию double Widget::myIntegral( PolyFP[row].x(), PolyFP[row].y(), PolyFP[column].x(), PolyFP[column].y() ) */
//void Widget::myPointInFP()
//{
//    double t;
//    QString myQString=ui->lineEdit_FP->text();
//    mFP=myQString.toDouble();

//    myQString=ui->lineEdit_dFP->text();
//    mFPd=myQString.toDouble();
//    for(int column=0; column<7; ++column)
//    {
//        t=myIntegral(mFP, mFPd, PolyFP[column].x(), PolyFP[column].y());
//        gFP[column]= (t>0.01 ? t : 0.01);
//    }
//}

/* void myFillMatrFPg(void) Заполняет mFP_g[row][column]= gFP[row]*mFP_b[row][column] по стандартному алгоритму . */
//void Widget::myFillMatrFPg()
//{
//    double t, S;
//    for(int row=0; row<7; ++row)
//    {
//        S=0.0;
//        for(int col=0; col<7; ++col)
//        {
//            t=mFP_b[row][col] * gFP[col];
//            t= t < 0.01 ? 0.01 : t;
//            S+=t;
//            mFP_g[row][col]=t;
//        }
//        Sm[row]=S;
//        if(Sm[row]>=0.99) tNVO[row]=0.01;
//        else tNVO[row]=1.0-Sm[row];
//    }
//}

/* void myFillMatrFPp(void) Заполняет mFP_p[row][column]= mFP_g[row][column]/(сумма[row] + НВО[row] ) по стандартному алгоритму . */
//void Widget::myFillMatrFPp()
//{
//    double t, S;
//    for(int row=0; row<7; ++row)
//    {
//        S=0.0;
//        for(int col=0; col<7; ++col)
//        {
//            t=mFP_g[row][col] / (Sm[row] + tNVO[row]);
//            t= t <0.01 ? 0.01 : t;
//            S+=t;
//            mFP_p[row][col]=t;
//        }
//        // Smax = std::max(Smax, S);
//    }
//}

/* void setFPtable(void) Заполняет таблицу ЧП */
//void Widget::setFPtable()
//{
//    IsInit=true;
//    int num;
//    QString s;
//    QTableWidget *myTab=ui->tableWidget_FP;
//    QTableWidgetItem *tiw;
//    num=PolyFP.size();
//    myTab->setRowCount(num);
//    for(int row=0; row < num; ++row)
//    {
//        s= QString("%1").arg( PolyFP.at(row).x(), 0, 'G', 6);
//        tiw=new QTableWidgetItem(s);
//        myTab->setItem(row, 0, tiw);
//        s= QString("%1").arg( PolyFP.at(row).y(), 0, 'G', 6);
//        tiw=new QTableWidgetItem(s);
//        myTab->setItem(row, 1, tiw);
//    }
//    IsInit=false;
//}

/* *********************************************************************************************************/

/* void myFillMatrSPp(void) Заполняет mSP_p[row][column] по стандартному алгоритму . */
void Widget::myFillMatrSPp(void)
{
    double t1, t2, zSP;
    QString myQString=ui->lineEdit_SP_1->text();
    mSP_1 = myQString.toDouble();

    myQString=ui->lineEdit_SP_2->text();
    mSP_2 = myQString.toDouble();
    // qDebug() << t1 << t2;
    zSP=(mSP_1 + mSP_2)/2.0;
    if(zSP<1.12) t2=0.1;
    else if(zSP<=2.5) t2=1.0-1.0/zSP;
    else t2=0.6;
    t1=(1.0-t2)/6.0;

    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            if(col==3) mSP_p[row][col]=t2; // col(3) - вертолет
            else mSP_p[row][col]=t1;
        }
    }
}

// void Widget::setSPtable(void){}

void Widget::myFillMatrVH_S_g() /* Заполняет mVH_S_g[row][column]= mVH_p[row][column] * mS_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVH_p[row][col] * mS_p[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVH_S_g[row][col]=t;
        }
        Sm[row]=S;
        if(Sm[row]>=0.99) tNVO[row]=0.01;
        else tNVO[row]=1.0-Sm[row];
    }
}

void Widget::myFillMatrVH_S_p() /* Заполняет mVH_S_p[row][column]= mVH_S_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVH_S_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVH_S_p[row][col]=t;
        }
    }
}

// *****************************************************************************
void Widget::myFillMatrVHg_Sg_g() /* Заполняет mVHg_Sg_g[row][column]= mVH_g[row][column] * mS_g[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVH_g[row][col] * mS_g[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVHg_Sg_g[row][col]=t;
        }
        Sm[row]=S;
//        qDebug() << " 1 myFillMatrVHg_Sg_g() row = " << row << "Sm= " << Sm[row];
//        if(Sm[row]>=0.99) tNVO[row]=0.01;
//        else tNVO[row]=1.0-Sm[row];
    }
}

void Widget::myFillMatrVHg_Sg_p() /* Заполняет mVHg_Sg_p[row][column]= mVHg_Sg_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVHg_Sg_p[row][col]=t;
        }
//        qDebug() << " 2 myFillMatrVHg_Sg_p() row = " << row << "Sm= " << Sm[row];
    }
}
// *****************************************************************************

void Widget::myFillMatrVH_S_DP_g() /* Заполняет mVH_S_DP_g[row][column]= mVH_S_p[row][column] * mDP_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVH_S_p[row][col] * mDP_p[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVH_S_DP_g[row][col]=t;
        }
        Sm[row]=S;
        if(Sm[row]>=0.99) tNVO[row]=0.01;
        else tNVO[row]=1.0-Sm[row];
    }
}

void Widget::myFillMatrVH_S_DP_p() /* Заполняет mVH_S_DP_p[row][column]= mVH_S_DP_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVH_S_DP_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVH_S_DP_p[row][col]=t;
        }
    }
}

void Widget::myFillMatrVHg_Sg_DPg_g() /* Заполняет mVHg_Sg_DPg_g[row][column]= mVHg_Sg_p[row][column] * mDP_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_g[row][col] * mDP_g[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVHg_Sg_DPg_g[row][col]=t;
        }
        Sm[row]=S;
        if(Sm[row]>=0.99) tNVO[row]=0.01;
        else tNVO[row]=1.0-Sm[row];
    }
}

void Widget::myFillMatrVHg_Sg_DPg_p() /* Заполняет mVHg_Sg_DPg_p[row][column]= mVHg_Sg_DPg_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_DPg_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVHg_Sg_DPg_p[row][col]=t;
        }
    }
}

/* ************************************************** */
//            mVHg_Sg_G_SP_g[7][7], mVHg_Sg_G_SP_p[7][7],  /* матрицы  G, P по (VHg + ЭПРg)g и СП */
void Widget::myFillMatrVHg_Sg_G_SP_g() /* Заполняет mVHg_Sg_G_SP_g[row][column]= mVHg_Sg_g[row][column] * mSP_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_g[row][col] * mSP_p[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVHg_Sg_G_SP_g[row][col]=t;
        }
        Sm[row]=S;
        if(Sm[row]>=0.99) tNVO[row]=0.01;
        else tNVO[row]=1.0-Sm[row];
    }
}

void Widget::myFillMatrVHg_Sg_G_SP_p() /* Заполняет mVHg_Sg_G_SP_p[row][column]= mVHg_Sg_G_SP_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_G_SP_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVHg_Sg_G_SP_p[row][col]=t;
        }
    }
}

//            mVHg_Sg_P_SP_g[7][7], mVHg_Sg_P_SP_p[7][7], /* матрицы  G, P по (VHg + ЭПРg)p и СП */
void Widget::myFillMatrVHg_Sg_P_SP_g() /* Заполняет mVHg_Sg_P_SP_g[row][column]= mVHg_Sg_p[row][column] * mSP_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_p[row][col] * mSP_p[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVHg_Sg_P_SP_g[row][col]=t;
        }
        Sm[row]=S;
        if(Sm[row]>=0.99) tNVO[row]=0.01;
        else tNVO[row]=1.0-Sm[row];
    }
}

void Widget::myFillMatrVHg_Sg_P_SP_p() /* Заполняет mVHg_Sg_G_SP_p[row][column]= mVHg_Sg_G_SP_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_P_SP_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVHg_Sg_P_SP_p[row][col]=t;
        }
    }
}

//            mVHg_Sg_DPg_G_SP_g[7][7], mVHg_Sg_DPg_G_SP_p[7][7],  /* матрицы  G, P по (VHg + ЭПРg)g и СП */
void Widget::myFillMatrVHg_Sg_DPg_G_SP_g() /* Заполняет mVHg_Sg_DPg_G_SP_g[row][column]= mVHg_Sg_DPg_g[row][column] * mSP_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_DPg_g[row][col] * mSP_p[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVHg_Sg_DPg_G_SP_g[row][col]=t;
        }
        Sm[row]=S;
        if(Sm[row]>=0.99) tNVO[row]=0.01;
        else tNVO[row]=1.0-Sm[row];
    }
}

void Widget::myFillMatrVHg_Sg_DPg_G_SP_p() /* Заполняет mVHg_Sg_DPg_G_SP_p[row][column]= mVHg_Sg_DPg_G_SP_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_DPg_G_SP_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVHg_Sg_DPg_G_SP_p[row][col]=t;
        }
    }
}


//            mVHg_Sg_DPg_P_SP_g[7][7], mVHg_Sg_DPg_P_SP_p[7][7], /* матрицы  G, P по (VHg + ЭПРg)p и СП */
void Widget::myFillMatrVHg_Sg_DPg_P_SP_g() /* Заполняет mVHg_Sg_DPg_P_SP_g[row][column]= mVHg_Sg_DPg_p[row][column] * mSP_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_DPg_p[row][col] * mSP_p[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVHg_Sg_DPg_P_SP_g[row][col]=t;
        }
        Sm[row]=S;
        if(Sm[row]>=0.99) tNVO[row]=0.01;
        else tNVO[row]=1.0-Sm[row];
    }
}

void Widget::myFillMatrVHg_Sg_DPg_P_SP_p() /* Заполняет mVHg_Sg_DPg_P_SP_p[row][column]= mVHg_Sg_DPg_P_SP_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVHg_Sg_DPg_P_SP_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVHg_Sg_DPg_P_SP_p[row][col]=t;
        }
    }
}

/* ************************************************** */



// ************************************** Ниже - новое для VH_DP_S *************************************************
void Widget::myFillMatrVH_DP_g(void) /* Заполняет mVH_DP_g[row][column]= mVH_p[row][column] * mDP_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVH_p[row][col] * mDP_p[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVH_DP_g[row][col]=t;
        }
        Sm[row]=S;
    }
}

void Widget::myFillMatrVH_DP_p(void) /* Заполняет mVH_DP_p[row][column]= mVH_DP_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVH_DP_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVH_DP_p[row][col]=t;
        }
    }
}


// ddd - см. widget.h - нах mVHg_DPg_g[7][7], mVHg_DPg_p[7][7],  /* матрицы  G, P по VH и ДП */
// ************************************** Ниже - новое для VH_DP_S *************************************************
//void Widget::myFillMatrVHg_DPg_g(void) /* Заполняет mVHg_DPg_g[row][column]= mVH_g[row][column] * mDP_g[row][column] по стандартному алгоритму . */
//{
//    double t, S;
//    for(int row=0; row<7; ++row)
//    {
//        S=0.0;
//        for(int col=0; col<7; ++col)
//        {
//            t=mVH_g[row][col] * mDP_g[row][col];
//            t= t < 0.01 ? 0.01 : t;
//            S+=t;
//            mVHg_DPg_g[row][col]=t;
//        }
//        Sm[row]=S;
//    }
//}

//void Widget::myFillMatrVHg_DPg_p(void) /* Заполняет mVHg_DPg_p[row][column]= mVHg_DPg_g[row][column] / сумма[row] по стандартному алгоритму . */
//{
//    double t;
//    for(int row=0; row<7; ++row)
//    {
//        for(int col=0; col<7; ++col)
//        {
//            t=mVHg_DPg_g[row][col] / Sm[row];
//            t= t <0.01 ? 0.01 : t;
//            mVHg_DPg_p[row][col]=t;
//        }
//    }
//}

void Widget::myFillMatrVH_DP_S_g(void) /* Заполняет mVH_DP_S_g[row][column]= mVH_DP_p[row][column] * mS_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVH_DP_p[row][col] * mS_p[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVH_DP_S_g[row][col]=t;
        }
        Sm[row]=S;
    }
}

void Widget::myFillMatrVH_DP_S_p(void) /* Заполняет mVH_DP_S_p[row][column]= mVH_DP_S_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVH_DP_S_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVH_DP_S_p[row][col]=t;
        }
    }
}
// ************************************** Выше - новое для VH_DP_S *************************************************

void Widget::myFillMatrVH_S_SP_g(void) /* Заполняет mVH_S_SP_g[row][column]= mVH_S_p[row][column] * mSP_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVH_S_p[row][col] * mSP_p[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVH_S_SP_g[row][col]=t;
        }
        Sm[row]=S;
    }
}

void Widget::myFillMatrVH_S_SP_p(void) /* Заполняет mVH_S_SP_p[row][column]= mVH_S_SP_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVH_S_SP_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVH_S_SP_p[row][col]=t;
        }
    }
}

void Widget::myFillMatrVH_S_DP_SP_g(void) /* Заполняет mVH_S_DP_SP_g[row][column]= mVH_S_DP_p[row][column] * mSP_p[row][column] по стандартному алгоритму . */
{
    double t, S;
    for(int row=0; row<7; ++row)
    {
        S=0.0;
        for(int col=0; col<7; ++col)
        {
            t=mVH_S_DP_p[row][col] * mSP_p[row][col];
            t= t < 0.01 ? 0.01 : t;
            S+=t;
            mVH_S_DP_SP_g[row][col]=t;
        }
        Sm[row]=S;
//        if(Sm[row]>=0.99) tNVO[row]=0.01;
//        else tNVO[row]=1.0-Sm[row];
    }
}

void Widget::myFillMatrVH_S_DP_SP_p(void) /* Заполняет mVH_S_DP_SP_p[row][column]= mVH_S_DP_SP_g[row][column] / сумма[row] по стандартному алгоритму . */
{
    double t;
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            t=mVH_S_DP_SP_g[row][col] / Sm[row];
            t= t <0.01 ? 0.01 : t;
            mVH_S_DP_SP_p[row][col]=t;
        }
    }
}

//void Widget::myFillMatrVH_DP_FP_g(void) /* Заполняет mVH_DP_FP_g[row][column]= mVH_DP_p[row][column] * mFP_p[row][column] по стандартному алгоритму . */
//{
//    double t, S;
//    for(int row=0; row<7; ++row)
//    {
//        S=0.0;
//        for(int col=0; col<7; ++col)
//        {
//            t=mVH_DP_p[row][col] * mFP_p[row][col];
//            t= t < 0.01 ? 0.01 : t;
//            S+=t;
//            mVH_DP_FP_g[row][col]=t;
//        }
//        Sm[row]=S;
//    }
//}

//void Widget::myFillMatrVH_DP_FP_p(void) /* Заполняет mVH_DP_FP_p[row][column]= mVH_DP_FP_g[row][column] / сумма[row] по стандартному алгоритму . */
//{
//    double t;
//    for(int row=0; row<7; ++row)
//    {
//        for(int col=0; col<7; ++col)
//        {
//            t=mVH_DP_FP_g[row][col] / Sm[row];
//            t= t <0.01 ? 0.01 : t;
//            mVH_DP_FP_p[row][col]=t;
//        }
//    }
//}

void Widget::myReCalcAll(void) /* Выполняет запуск последовательного пересчета всех матриц и векторов. Запускается после изменения входных данных */
{
    // IsInit=true;
    myFillMatrVH();
    myPointInVH();
    myFillMatrVHg();
    myFillMatrVHp();
    setPtable(11);

    myFillMatrEPR();
    myPointInEPR();
    myFillMatrEPRg();
    myFillMatrEPRp();
    setEPRtable();

    myFillMatrDP();
    myPointInDP();
    myFillMatrDPg();
    myFillMatrDPp();
    setDPtable();

//    qDebug() << "EPRg[1][1] = " << mS_g[1][1] << " EPRp[1][1] =   " << mS_p[1][1];
//    qDebug() << "DPg[1][1] = " << mDP_g[1][1] << " DPp[1][1] =   " << mDP_p[1][1];

//    myFillMatrFP(); /* Заполнить матрицу mFP_b[5][5] */
//    myPointInFP(); /* Заполнить вектор gFP[5]  */
//    myFillMatrFPg(); /* Заполнить матрицу mFP_g[5][5] */
//    myFillMatrFPp(); /* Заполнить матрицу mFP_p[5][5] */
//    setFPtable();  /* Заполнить в главном окне -> ЧП -> Таблица */


    myFillMatrSPp();
    // showNVO();

    myFillMatrVH_S_g();
    myFillMatrVH_S_p();

    myFillMatrVH_DP_g();
    myFillMatrVH_DP_p();

//    myFillMatrVH_DP_FP_g(); /* Заполнить матрицу mVH_DP_FP_g[5][5] */
//    myFillMatrVH_DP_FP_p(); /* Заполнить матрицу mVH_DP_FP_p[5][5] */

    myFillMatrVH_S_DP_g();
    myFillMatrVH_S_DP_p();

    myFillMatrVH_DP_S_g();
    myFillMatrVH_DP_S_p();

    myFillMatrVH_S_SP_g();
    myFillMatrVH_S_SP_p();

    myFillMatrVH_S_DP_SP_g();
    myFillMatrVH_S_DP_SP_p();

    myFillMatrVHg_Sg_g();
    myFillMatrVHg_Sg_p();
    // myFillMatrVHg_DPg_g();
    // myFillMatrVHg_DPg_p();
    myFillMatrVHg_Sg_DPg_g();
    myFillMatrVHg_Sg_DPg_p();

    myFillMatrVHg_Sg_G_SP_g();
    myFillMatrVHg_Sg_G_SP_p();
    myFillMatrVHg_Sg_P_SP_g();
    myFillMatrVHg_Sg_P_SP_p();
    myFillMatrVHg_Sg_DPg_G_SP_g();
    myFillMatrVHg_Sg_DPg_G_SP_p();
    myFillMatrVHg_Sg_DPg_P_SP_g();
    myFillMatrVHg_Sg_DPg_P_SP_p();

    // if(ui->checkBox_Result->isChecked()) myShowResultDialog();

    // setPtable(11);

    if( (mSP_p[3][3] > 1.0/7.0) & (mVH_p[4][4] < 0.15) )
    {
        ui->listWidget->setCurrentRow(21);
        setPtable(21);
    }
    else
    {
        ui->listWidget->setCurrentRow(13);
        setPtable(13);
    }
    myShowResultDialog(false);
}

void Widget::myOpenFile5x4write(void) /* Записать в файл матрицу 5х5, по указателю (*pm5x5)  */
{
    QString s=QString("%1\\%2").arg(myOutDir.absolutePath()).arg(myFileName);
    QFile outputFile(s);
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream myOut(&outputFile);

        for(int row=0; row<7; ++row)
        {
            for(int col=0; col<7; ++col)
            {
                s= QString("%1").arg( (*pm5x5)[row][col], 0, 'f', 3);
                if(myDelimInNum != QChar('.')) s.replace(QChar('.'), myDelimInNum, Qt::CaseSensitive);
                myOut << s;
                col<6 ? (myOut << myDelimBetwNum) : (myOut << "\n") ;
            }
        }
        outputFile.close();
    }
}

void Widget::myFindKC0(bool showRes)  /* Автоматически определяет класс цели по алгоритму 0 */
{
    int num0, num1;
    bool VRT = false;
    double  myMaxP0,
            myMaxP1 = 0.0;
            // NeedSP = 9.0 ;
    QString text;
    QTextStream myOut(&text);
    myOut << tr("Результат работы программы: \n");

    // std::sort();


    myMaxP0 = mVHg_Sg_DPg_p[0][0];
    num0 = 0;

    for(int i=1; i<7; ++i) // находим максимальное значение на диагонали
    {
        if(myMaxP0 < mVHg_Sg_DPg_p[i][i])
        {
            myMaxP0 = mVHg_Sg_DPg_p[i][i];
            num0 = i;
        }
    }

    for(int i=0; i<7; ++i) // находим следующее максимальное значение на диагонали, меньшее предыдущего
    {
        if( (i!=num0) && (myMaxP1 < mVHg_Sg_DPg_p[i][i]) )
        {
            myMaxP1 = mVHg_Sg_DPg_p[i][i];
            num1 = i;
        }
    }

    if( (mSP_p[3][3] > 1.0/7.0) & (mVH_p[3][3] > 0.05) )
    //    if(myMaxP0/mVHg_Sg_DPg_p[3][3] < NeedSP)
    {
        VRT = true;
        myMaxP0 = mVHg_Sg_DPg_P_SP_p[0][0];
        num0 = 0;
        num1 = 0;

        for(int i=1; i<7; ++i) // находим максимальное значение на диагонали
        {
            if(myMaxP0 < mVHg_Sg_DPg_P_SP_p[i][i])
            {
                myMaxP0 = mVHg_Sg_DPg_P_SP_p[i][i];
                num0 = i;
            }
        }

        for(int i=0; i<7; ++i) // находим следующее максимальное значение на диагонали, меньшее предыдущего
        {
            if( (i!=num0) && (myMaxP1 < mVHg_Sg_DPg_P_SP_p[i][i]) )
            {
                myMaxP1 = mVHg_Sg_DPg_P_SP_p[i][i];
                num1 = i;
            }
        }

    }

    if( (myMaxP0 > 0.8) && (myMaxP0 - myMaxP1 > myEps) )
    {
        myOut << tr("\n Определён класс цели - ");
        switch(num0)
        {
        case 0:
            myOut << tr("САМ СА");
            break;
        case 1:
            myOut << tr("САМ СА-Б2");
            break;
        case 2:
            myOut << tr("САМ ТА");
            break;
        case 3:
            myOut << tr("ВРТ");
            break;
        case 4:
            myOut << tr("ГЗЛА");
            break;
        case 5:
            myOut << tr("КР");
            break;
        case 6:
            myOut << tr("АДА");
            break;
        default:
            myOut << tr("ОШИБКА");
            break;
        }
        myOut << tr("\n");
    }
    else if( (myMaxP0 > 0.8) && (myMaxP0 - myMaxP1 <= myEps) )
    {
        myOut << tr(" \n Класс цели однозначно не опредделен.\n\n Наиболее вероятный класс цели - ");

        switch(num0)
        {
        case 0:
            myOut << tr("САМ СА");
            break;
        case 1:
            myOut << tr("САМ СА-Б2");
            break;
        case 2:
            myOut << tr("САМ ТА");
            break;
        case 3:
            myOut << tr("ВРТ");
            break;
        case 4:
            myOut << tr("ГЗЛА");
            break;
        case 5:
            myOut << tr("КР");
            break;
        case 6:
            myOut << tr("АДА");
            break;
        default:
            myOut << tr("ОШИБКА");
            break;
        }

        myOut << tr("  c вероятностью  ") << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[num0][num0] : mVHg_Sg_DPg_p[num0][num0]), 5, 'F', 1);

        myOut << tr(" \n По крайней мере ещё один класс имеет близкую вероятность: \n");
        switch(num1)
        {
        case 0:
            myOut << tr("САМ СА");
            break;
        case 1:
            myOut << tr("САМ СА-Б2");
            break;
        case 2:
            myOut << tr("САМ ТА");
            break;
        case 3:
            myOut << tr("ВРТ");
            break;
        case 4:
            myOut << tr("ГЗЛА");
            break;
        case 5:
            myOut << tr("КР");
            break;
        case 6:
            myOut << tr("АДА");
            break;
        default:
            myOut << tr(" !!! ОШИБКА !!! ");
            break;
        }
        myOut << tr("  c вероятностью  ") << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[num1][num1] : mVHg_Sg_DPg_p[num1][num1]), 5, 'F', 1);
    }
    else
    {
        myOut << tr(" \n Класс цели не опредделен. \n");
        myOut << tr(" \n Вероятности для классов ");
        myOut << ( VRT ? tr("по матрице (VHg + ЭПРg + ДПg)p + СПp следующие :\n") : tr("по матрице (VHg + ЭПРg + ДПg)p следующие :\n") );
        myOut << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[0][0] : mVHg_Sg_DPg_p[0][0]), 5, 'F', 1) << tr("  САМ СА\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[1][1] : mVHg_Sg_DPg_p[1][1]), 5, 'F', 1) << tr("  САМ СА-Б2\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[2][2] : mVHg_Sg_DPg_p[2][2]), 5, 'F', 1) << tr("  САМ ТА\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[3][3] : mVHg_Sg_DPg_p[3][3]), 5, 'F', 1) << tr("  ВРТ\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[4][4] : mVHg_Sg_DPg_p[4][4]), 5, 'F', 1) << tr("  ГЗЛА\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[5][5] : mVHg_Sg_DPg_p[5][5]), 5, 'F', 1) << tr("  КР\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[6][6] : mVHg_Sg_DPg_p[6][6]), 5, 'F', 1) << tr("  АДА\n") ;
    }

    // myOut << tr(" \n Продолжить ?");

    myResText += text;
    if(showRes)
    {
        FinResult = new ResDialog(this);
        FinResult->mySetText( text );
        FinResult->setWindowTitle( QString("ММ РКЦ Результат работы программы") );
        FinResult->show();
    }
}

QString Widget::myNum2Class(int myClassNum) /* Переводит номер класса в название ( 0 -> СА, 1 -> САБ2, 3 -> ВРТ,...)  */
{
    QString text;
    QTextStream myOut(&text);

    switch(myClassNum)
    {
    case 0:
        myOut << tr("САМ СА");
        break;
    case 1:
        myOut << tr("САМ СА-Б2");
        break;
    case 2:
        myOut << tr("САМ ТА");
        break;
    case 3:
        myOut << tr("ВРТ");
        break;
    case 4:
        myOut << tr("ГЗЛА");
        break;
    case 5:
        myOut << tr("КР");
        break;
    case 6:
        myOut << tr("АДА");
        break;
    default:
        myOut << tr("ОШИБКА");
        break;
    }
    return text;
}

void Widget::myShowResultDialog(bool showRes)  /* Показывает окно с автоматически определенным классом цели. Запускается по кнопке */
{
    int ti, ind[7]={0,1,2,3,4,5,6}; // int num0, num1;
    bool VRT = false;
    double td, myDiag[7]; // double  myMaxP0, myMaxP1 = 0.0;
            // NeedSP = 9.0 ;
    QString text;
    QTextStream myOut(&text);
    myOut << tr("Результат работы программы: \n по VH и ЭПР ");

// Sort myDiag[ind]
//    int ti, ind[7]={0,1,2,3,4,5,6};
//    double td, myDiag[7];

    for (int i = 0; i < 7; ++i) {
        myDiag[i]=mVHg_Sg_p[i][i];
    }

    for(int i1=0; i1<6; ++i1)
    {
        for(int i2=i1+1; i2<7; ++i2)
        {
            if(myDiag[i1] < myDiag[i2])
            {
                td = myDiag[i2];
                myDiag[i2] = myDiag[i1];
                myDiag[i1] = td;
                ti = ind[i2];
                ind[i2] = ind[i1];
                ind[i1] = ti;
            }
        }
    }

    if( (myDiag[0] >= double(0.8)) && (myDiag[0] - myDiag[1] > myEps) )
    {
        myOut << tr("Определен класс цели : ") << myNum2Class(ind[0])  << tr(" \n Значения главной диагонали :\n");
        for(int i =0; i<7 ; ++i)
        {
            myOut << tr(" %1 ").arg(myNum2Class(ind[i]))
                  << QString(" %1 \% \n").arg(myDiag[i]*100.0, 5, 'f', 1);
        }

        myResText = text;
        if(showRes)
        {
            FinResult = new ResDialog(this);
            FinResult->mySetText( text );
            FinResult->setWindowTitle( QString("ММ РКЦ Результат работы программы") );
            FinResult->show();
        }
        return;
    }

    myOut << tr("Класс цели не определен. \n Значения главной диагонали :\n");
    for(int i =0; i<7 ; ++i)
    {
        myOut << tr(" %1 ").arg(myNum2Class(ind[i]))
              << QString(" %1 \% \n").arg(myDiag[i]*100.0, 5, 'f', 1);
    }
    myOut << tr("\n Проверяем, входит ли ВРТ в тройку лидеров (классы с максимальной вероятностью). \n");

    if( (ind[0]==3) || (ind[1]==3) || (ind[2]==3) )
    {
        VRT = true;
        myOut << tr("Класс ВРТ входит в тройку лидеров. \n Запрашиваем спектральный портрет\n");

        for (int i = 0; i < 7; ++i)
        {
            ind[i]=i;
            myDiag[i]=mVHg_Sg_G_SP_p[i][i];
        }

        for(int i1=0; i1<6; ++i1)
        {
            for(int i2=i1+1; i2<7; ++i2)
            {
                if(myDiag[i1] < myDiag[i2])
                {
                    td = myDiag[i2];
                    myDiag[i2] = myDiag[i1];
                    myDiag[i1] = td;
                    ti = ind[i2];
                    ind[i2] = ind[i1];
                    ind[i1] = ti;
                }
            }
        }

        if( (myDiag[0] >= double(0.8)) && (myDiag[0] - myDiag[1] > myEps) )
        {
            myOut << tr("Определен класс цели : ") << myNum2Class(ind[0])  << tr(" \n Значения главной диагонали :\n");
            for(int i =0; i<7 ; ++i)
            {
                myOut << tr(" %1 ").arg(myNum2Class(ind[i]))
                      << QString(" %1 \% \n").arg(myDiag[i]*100.0, 5, 'f', 1);
            }

            myResText = text;
            if(showRes)
            {
                FinResult = new ResDialog(this);
                FinResult->mySetText( text );
                FinResult->setWindowTitle( QString("ММ РКЦ Результат работы программы") );
                FinResult->show();
            }
            return;
        }
    }

    myOut << tr("Класс ВРТ не входит в тройку лидеров. \n Запрашиваем дальностный портрет\n");


    for (int i = 0; i < 7; ++i)
    {
        ind[i]=i;
        if(VRT) myDiag[i]=mVHg_Sg_DPg_G_SP_p[i][i];
        else myDiag[i]=mVHg_Sg_DPg_p[i][i];
    }

    for(int i1=0; i1<6; ++i1)
    {
        for(int i2=i1+1; i2<7; ++i2)
        {
            if(myDiag[i1] < myDiag[i2])
            {
                td = myDiag[i2];
                myDiag[i2] = myDiag[i1];
                myDiag[i1] = td;
                ti = ind[i2];
                ind[i2] = ind[i1];
                ind[i1] = ti;
            }
        }
    }

    if( (myDiag[0] >= double(0.8)) && (myDiag[0] - myDiag[1] > myEps) )
    {
        myOut << tr("По VH, ЭПР(, СП), ДП определен класс цели : ") << myNum2Class(ind[0])  << tr(" \n Значения главной диагонали :\n");
        for(int i =0; i<7 ; ++i)
        {
            myOut << tr(" %1 ").arg(myNum2Class(ind[i]))
                  << QString(" %1 \% \n").arg(myDiag[i]*100.0, 5, 'f', 1);
        }

        myResText = text;
        if(showRes)
        {
            FinResult = new ResDialog(this);
            FinResult->mySetText( text );
            FinResult->setWindowTitle( QString("ММ РКЦ Результат работы программы") );
            FinResult->show();
        }
        return;
    }

    myOut << tr("Класс цели не определен. \n Значения главной диагонали :\n");
    for(int i =0; i<7 ; ++i)
    {
        myOut << tr(" %1 ").arg(myNum2Class(ind[i]))
              << QString(" %1 \% \n").arg(myDiag[i]*100.0, 5, 'f', 1);
    }

    myResText = text;
    if(showRes)
    {
        FinResult = new ResDialog(this);
        FinResult->mySetText( text );
        FinResult->setWindowTitle( QString("ММ РКЦ Результат работы программы") );
        FinResult->show();
    }
    return;
}

//    myMaxP0 = mVHg_Sg_DPg_p[0][0];
//    num0 = 0;

//    for(int i=1; i<7; ++i) // находим максимальное значение на диагонали
//    {
//        if(myMaxP0 < mVHg_Sg_DPg_p[i][i])
//        {
//            myMaxP0 = mVHg_Sg_DPg_p[i][i];
//            num0 = i;
//        }
//    }

//    for(int i=0; i<7; ++i) // находим следующее максимальное значение на диагонали, меньшее предыдущего
//    {
//        if( (i!=num0) && (myMaxP1 < mVHg_Sg_DPg_p[i][i]) )
//        {
//            myMaxP1 = mVHg_Sg_DPg_p[i][i];
//            num1 = i;
//        }
//    }

//    if( (mSP_p[3][3] > 1.0/7.0) & (mVH_p[3][3] > 0.05) )
//    //    if(myMaxP0/mVHg_Sg_DPg_p[3][3] < NeedSP)
//    {
//        VRT = true;
//        myMaxP0 = mVHg_Sg_DPg_P_SP_p[0][0];
//        num0 = 0;
//        num1 = 0;

//        for(int i=1; i<7; ++i) // находим максимальное значение на диагонали
//        {
//            if(myMaxP0 < mVHg_Sg_DPg_P_SP_p[i][i])
//            {
//                myMaxP0 = mVHg_Sg_DPg_P_SP_p[i][i];
//                num0 = i;
//            }
//        }

//        for(int i=0; i<7; ++i) // находим следующее максимальное значение на диагонали, меньшее предыдущего
//        {
//            if( (i!=num0) && (myMaxP1 < mVHg_Sg_DPg_P_SP_p[i][i]) )
//            {
//                myMaxP1 = mVHg_Sg_DPg_P_SP_p[i][i];
//                num1 = i;
//            }
//        }

//    }

//    if( (myMaxP0 > 0.8) && (myMaxP0 - myMaxP1 > myEps) )
//    {
//        myOut << tr("\n Определён класс цели - ");
//        switch(num0)
//        {
//        case 0:
//            myOut << tr("САМ СА");
//            break;
//        case 1:
//            myOut << tr("САМ СА-Б2");
//            break;
//        case 2:
//            myOut << tr("САМ ТА");
//            break;
//        case 3:
//            myOut << tr("ВРТ");
//            break;
//        case 4:
//            myOut << tr("ГЗЛА");
//            break;
//        case 5:
//            myOut << tr("КР");
//            break;
//        case 6:
//            myOut << tr("АДА");
//            break;
//        default:
//            myOut << tr("ОШИБКА");
//            break;
//        }
//        myOut << tr("\n");
//    }
//    else if( (myMaxP0 > 0.8) && (myMaxP0 - myMaxP1 <= myEps) )
//    {
//        myOut << tr(" \n Класс цели однозначно не опредделен.\n\n Наиболее вероятный класс цели - ");

//        switch(num0)
//        {
//        case 0:
//            myOut << tr("САМ СА");
//            break;
//        case 1:
//            myOut << tr("САМ СА-Б2");
//            break;
//        case 2:
//            myOut << tr("САМ ТА");
//            break;
//        case 3:
//            myOut << tr("ВРТ");
//            break;
//        case 4:
//            myOut << tr("ГЗЛА");
//            break;
//        case 5:
//            myOut << tr("КР");
//            break;
//        case 6:
//            myOut << tr("АДА");
//            break;
//        default:
//            myOut << tr("ОШИБКА");
//            break;
//        }

//        myOut << tr("  c вероятностью  ") << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[num0][num0] : mVHg_Sg_DPg_p[num0][num0]), 5, 'f', 1);

//        myOut << tr(" \n По крайней мере ещё один класс имеет близкую вероятность: \n");
//        switch(num1)
//        {
//        case 0:
//            myOut << tr("САМ СА");
//            break;
//        case 1:
//            myOut << tr("САМ СА-Б2");
//            break;
//        case 2:
//            myOut << tr("САМ ТА");
//            break;
//        case 3:
//            myOut << tr("ВРТ");
//            break;
//        case 4:
//            myOut << tr("ГЗЛА");
//            break;
//        case 5:
//            myOut << tr("КР");
//            break;
//        case 6:
//            myOut << tr("АДА");
//            break;
//        default:
//            myOut << tr(" !!! ОШИБКА !!! ");
//            break;
//        }
//        myOut << tr("  c вероятностью  ") << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[num1][num1] : mVHg_Sg_DPg_p[num1][num1]), 5, 'F', 1);
//    }
//    else
//    {
//        myOut << tr(" \n Класс цели не опредделен. \n");
//        myOut << tr(" \n Вероятности для классов ");
//        myOut << ( VRT ? tr("по матрице (VHg + ЭПРg + ДПg)p + СПp следующие :\n") : tr("по матрице (VHg + ЭПРg + ДПg)p следующие :\n") );
//        myOut << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[0][0] : mVHg_Sg_DPg_p[0][0]), 5, 'F', 1) << tr("  САМ СА\n")
//             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[1][1] : mVHg_Sg_DPg_p[1][1]), 5, 'F', 1) << tr("  САМ СА-Б2\n")
//             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[2][2] : mVHg_Sg_DPg_p[2][2]), 5, 'F', 1) << tr("  САМ ТА\n")
//             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[3][3] : mVHg_Sg_DPg_p[3][3]), 5, 'F', 1) << tr("  ВРТ\n")
//             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[4][4] : mVHg_Sg_DPg_p[4][4]), 5, 'F', 1) << tr("  ГЗЛА\n")
//             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[5][5] : mVHg_Sg_DPg_p[5][5]), 5, 'F', 1) << tr("  КР\n")
//             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[6][6] : mVHg_Sg_DPg_p[6][6]), 5, 'F', 1) << tr("  АДА\n") ;
//    }

//    // myOut << tr(" \n Продолжить ?");

//    myResText = text;
//    if(showRes)
//    {
//        FinResult = new ResDialog(this);
//        FinResult->mySetText( text );
//        FinResult->setWindowTitle( QString("ММ РКЦ Результат работы программы") );
//        FinResult->show();
//    }
// }

void Widget::myShowResultDialogOldK(bool showRes)  /* Показывает окно с автоматически определенным классом цели. Запускается по кнопке */
{
    int num0, num1;
    bool VRT = false;
    double  myMaxP0,
            myMaxP1 = 0.0;
            // NeedSP = 9.0 ;
    QString text;
    QTextStream myOut(&text);
    myOut << tr("Результат работы программы: \n");

    myMaxP0 = mVHg_Sg_DPg_p[0][0];
    num0 = 0;

    for(int i=1; i<7; ++i) // находим максимальное значение на диагонали
    {
        if(myMaxP0 < mVHg_Sg_DPg_p[i][i])
        {
            myMaxP0 = mVHg_Sg_DPg_p[i][i];
            num0 = i;
        }
    }

    for(int i=0; i<7; ++i) // находим следующее максимальное значение на диагонали, меньшее предыдущего
    {
        if( (i!=num0) && (myMaxP1 < mVHg_Sg_DPg_p[i][i]) )
        {
            myMaxP1 = mVHg_Sg_DPg_p[i][i];
            num1 = i;
        }
    }

    if( (mSP_p[3][3] > 1.0/7.0) & (mVH_p[3][3] > 0.05) )
    //    if(myMaxP0/mVHg_Sg_DPg_p[3][3] < NeedSP)
    {
        VRT = true;
        myMaxP0 = mVHg_Sg_DPg_P_SP_p[0][0];
        num0 = 0;
        num1 = 0;

        for(int i=1; i<7; ++i) // находим максимальное значение на диагонали
        {
            if(myMaxP0 < mVHg_Sg_DPg_P_SP_p[i][i])
            {
                myMaxP0 = mVHg_Sg_DPg_P_SP_p[i][i];
                num0 = i;
            }
        }

        for(int i=0; i<7; ++i) // находим следующее максимальное значение на диагонали, меньшее предыдущего
        {
            if( (i!=num0) && (myMaxP1 < mVHg_Sg_DPg_P_SP_p[i][i]) )
            {
                myMaxP1 = mVHg_Sg_DPg_P_SP_p[i][i];
                num1 = i;
            }
        }

    }

    if( (myMaxP0 > 0.8) && (myMaxP0 - myMaxP1 > myEps) )
    {
        myOut << tr("\n Определён класс цели - ");
        switch(num0)
        {
        case 0:
            myOut << tr("САМ СА");
            break;
        case 1:
            myOut << tr("САМ СА-Б2");
            break;
        case 2:
            myOut << tr("САМ ТА");
            break;
        case 3:
            myOut << tr("ВРТ");
            break;
        case 4:
            myOut << tr("ГЗЛА");
            break;
        case 5:
            myOut << tr("КР");
            break;
        case 6:
            myOut << tr("АДА");
            break;
        default:
            myOut << tr("ОШИБКА");
            break;
        }
        myOut << tr("\n");
    }
    else if( (myMaxP0 > 0.8) && (myMaxP0 - myMaxP1 <= myEps) )
    {
        myOut << tr(" \n Класс цели однозначно не опредделен.\n\n Наиболее вероятный класс цели - ");

        switch(num0)
        {
        case 0:
            myOut << tr("САМ СА");
            break;
        case 1:
            myOut << tr("САМ СА-Б2");
            break;
        case 2:
            myOut << tr("САМ ТА");
            break;
        case 3:
            myOut << tr("ВРТ");
            break;
        case 4:
            myOut << tr("ГЗЛА");
            break;
        case 5:
            myOut << tr("КР");
            break;
        case 6:
            myOut << tr("АДА");
            break;
        default:
            myOut << tr("ОШИБКА");
            break;
        }

        myOut << tr("  c вероятностью  ") << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[num0][num0] : mVHg_Sg_DPg_p[num0][num0]), 5, 'F', 1);

        myOut << tr(" \n По крайней мере ещё один класс имеет близкую вероятность: \n");
        switch(num1)
        {
        case 0:
            myOut << tr("САМ СА");
            break;
        case 1:
            myOut << tr("САМ СА-Б2");
            break;
        case 2:
            myOut << tr("САМ ТА");
            break;
        case 3:
            myOut << tr("ВРТ");
            break;
        case 4:
            myOut << tr("ГЗЛА");
            break;
        case 5:
            myOut << tr("КР");
            break;
        case 6:
            myOut << tr("АДА");
            break;
        default:
            myOut << tr(" !!! ОШИБКА !!! ");
            break;
        }
        myOut << tr("  c вероятностью  ") << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[num1][num1] : mVHg_Sg_DPg_p[num1][num1]), 5, 'F', 1);
    }
    else
    {
        myOut << tr(" \n Класс цели не опредделен. \n");
        myOut << tr(" \n Вероятности для классов ");
        myOut << ( VRT ? tr("по матрице (VHg + ЭПРg + ДПg)p + СПp следующие :\n") : tr("по матрице (VHg + ЭПРg + ДПg)p следующие :\n") );
        myOut << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[0][0] : mVHg_Sg_DPg_p[0][0]), 5, 'F', 1) << tr("  САМ СА\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[1][1] : mVHg_Sg_DPg_p[1][1]), 5, 'F', 1) << tr("  САМ СА-Б2\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[2][2] : mVHg_Sg_DPg_p[2][2]), 5, 'F', 1) << tr("  САМ ТА\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[3][3] : mVHg_Sg_DPg_p[3][3]), 5, 'F', 1) << tr("  ВРТ\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[4][4] : mVHg_Sg_DPg_p[4][4]), 5, 'F', 1) << tr("  ГЗЛА\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[5][5] : mVHg_Sg_DPg_p[5][5]), 5, 'F', 1) << tr("  КР\n")
             << QString("%1\%").arg( 100.0*(VRT ? mVHg_Sg_DPg_P_SP_p[6][6] : mVHg_Sg_DPg_p[6][6]), 5, 'F', 1) << tr("  АДА\n") ;
    }

    // myOut << tr(" \n Продолжить ?");

    myResText = text;
    if(showRes)
    {
        FinResult = new ResDialog(this);
        FinResult->mySetText( text );
        FinResult->setWindowTitle( QString("ММ РКЦ Результат работы программы") );
        FinResult->show();
    }
}

// old
//void Widget::myShowResultDialog(void)  /* Показывает окно с автоматически определенным классом цели. Запускается по кнопке */
//{
//    bool Pereputal;
//    int num=0;
//    double myMaxP=0.0, myMaxP1=0.0;
//    QString text;
//    QTextStream myOut(&text);
//    myOut << tr("Результат работы программы: \n");
//    for(int i=0; i<7; ++i) // находим максимальное значение на диагонали
//    {
//        if(myMaxP < mVH_S_p[i][i])
//        {
//            myMaxP = mVH_S_p[i][i];
//            num = i;
//        }
//    }
//    for(int i=0; i<7; ++i) // находим следующее максимальное значение на диагонали, меньшее предыдущего
//    {
//        if( (i!=num) && (myMaxP1 < mVH_S_p[i][i]) )
//        {
//            myMaxP1 = mVH_S_p[i][i];
//        }
//    }
//    Pereputal=false;
//    for(int i=0; i<7; ++i) // есть ли в строке с максимальнымзначением числа больше 0,15
//    {
//        if( (i!=num) && (mVH_S_p[num][i] > 0.15) ) Pereputal=true;
//    }
//    if( (myMaxP > 0.8) && (myMaxP - myMaxP1 > myEps)  && !Pereputal)
//    {
//        myOut << tr("Определён класс цели - ");
//        switch(num)
//        {
//        case 0:
//            myOut << tr("САМ СА");
//            break;
//        case 1:
//            myOut << tr("САМ СА-Б2");
//            break;
//        case 2:
//            myOut << tr("САМ ТА");
//            break;
//        case 3:
//            myOut << tr("ВРТ");
//            break;
//        case 4:
//            myOut << tr("ГЗЛА");
//            break;
//        case 5:
//            myOut << tr("КР");
//            break;
//        case 6:
//            myOut << tr("АДА");
//            break;
//        default:
//            myOut << tr("ОШИБКА");
//            break;
//        }
//    }
//    else myOut << tr(" \n Класс цели однозначно не опредделен. ");
//    myOut << tr(" \n Вероятность НВО = ") << mNVO;
//    myOut << tr(" \n Продолжить ?");

//    FinResult = new ResDialog(this);
//    FinResult->mySetText( text );
//    FinResult->setWindowTitle( QString("ММ РКЦ Результат работы программы") );
//    FinResult->show();
//}

//void Widget::myShowResultDialogOld(void)  /* Показывает окно с автоматически определенным классом цели. Запускается по кнопке */
//{
//    bool Pereputal;
//    int num=0;
//    double myMaxP=0.0, myMaxP1=0.0;
//    QString text;
//    QTextStream myOut(&text);
//    myOut << tr("Результат работы программы: \n");
//    for(int i=0; i<7; ++i) // находим максимальное значение на диагонали
//    {
//        if(myMaxP < mVH_S_p[i][i])
//        {
//            myMaxP = mVH_S_p[i][i];
//            num = i;
//        }
//    }
//    for(int i=0; i<7; ++i) // находим следующее максимальное значение на диагонали, меньшее предыдущего
//    {
//        if( (i!=num) && (myMaxP1 < mVH_S_p[i][i]) )
//        {
//            myMaxP1 = mVH_S_p[i][i];
//        }
//    }
//    Pereputal=false;
//    for(int i=0; i<7; ++i) // есть ли в строке с максимальнымзначением числа больше 0,15
//    {
//        if( (i!=num) && (mVH_S_p[num][i] > 0.15) ) Pereputal=true;
//    }
//    if( (myMaxP > 0.8) && (myMaxP - myMaxP1 > myEps)  && !Pereputal)
//    {
//        myOut << tr("Определён класс цели - ");
//        switch(num)
//        {
//        case 0:
//            myOut << tr("САМ СА");
//            break;
//        case 1:
//            myOut << tr("САМ СА-Б2");
//            break;
//        case 2:
//            myOut << tr("САМ ТА");
//            break;
//        case 3:
//            myOut << tr("ВРТ");
//            break;
//        case 4:
//            myOut << tr("ГЗЛА");
//            break;
//        case 5:
//            myOut << tr("КР");
//            break;
//        case 6:
//            myOut << tr("АДА");
//            break;
//        default:
//            myOut << tr("ОШИБКА");
//            break;
//        }
//    }
//    else myOut << tr(" \n Класс цели однозначно не опредделен. ");
//    myOut << tr(" \n Вероятность НВО = ") << mNVO;
//    myOut << tr(" \n Продолжить ?");

//    FinResult = new ResDialog(this);
//    FinResult->mySetText( text );
//    FinResult->setWindowTitle( QString("ММ РКЦ Результат работы программы") );
//    FinResult->show();
//}

/* double myPointInVHnum(QPolygonF &Poly_0, QPolygonF &Poly_1, double x, double y) Проверяет, лежит ли точка
 * внутри Poly_1 - возвращает 1.0, вне Poly_0 - возвращает 0.0, в полосе между Poly_0 и Poly_1  - проводит прямую через точку и
 * центр Poly_1 и выдает удаленность от границы Poly_1 (от 1.0 до 0.0) */
double Widget::myPointInVHnum(QPolygonF &Poly_0, QPolygonF &Poly_1, double x, double y)
{
    int N=Poly_0.size();
    double Res=0.0;
    QPointF Point = QPointF(x, y);
    QPointF Center=QPointF();
    QPointF PointCross0, PointCross1;
    QPolygonF PolySide = QPolygonF();
    if(!Poly_0.containsPoint(Point, Qt::OddEvenFill)) return 0.0;
    if(Poly_1.containsPoint(Point, Qt::OddEvenFill)) return 1.0;
    for(int i=0; i<N; ++i)
    {
        Center+=Poly_1[i];
    }
    Center/=N;
    QLineF mySide0, mySide1, myRadius=QLineF(Point, Center);
    for(int i=0; i<N; ++i)
    {
        if(i < N-1) PolySide << Poly_0[i] << Poly_0[i+1] << Poly_1[i+1] << Poly_1[i];
        else PolySide << Poly_0[i] << Poly_0[0] << Poly_1[0] << Poly_1[i];
        if(PolySide.containsPoint(Point, Qt::OddEvenFill))
        {
            if(i < N-1)
            {
                mySide0=QLineF(Poly_0[i], Poly_0[i+1]);
                mySide1=QLineF(Poly_1[i], Poly_1[i+1]);
            }
            else
            {
                mySide0=QLineF(Poly_0[i], Poly_0[0]);
                mySide1=QLineF(Poly_1[i], Poly_1[0]);
            }
            mySide0.intersect(myRadius, &PointCross0);
            mySide1.intersect(myRadius, &PointCross1);
            Res = QLineF(Point, PointCross0).length()/QLineF(PointCross0, PointCross1).length();
            break;
        }

    }
    return Res;
}

double Widget::Reley(double H) /* Функция Релея - множитель к вероятности VH, зависящий от высоты */
{
    double sigma2= 0.10 * 0.10;
    return H/(6.0653066*sigma2)*exp( -H*H/(2.0*sigma2) );
}

/* double myPolyIntegral(int P1, int P2) Интеграл по VH с учетом вероятностей для "усеченных пирамид"
 * (т.е. пар векторов Poly_0 и Poly_1) P1 и P2 */
double Widget::myPolyIntegral(int P1, int P2)
{
    int N=32;
    double t, x, xi, w, dx, y, yi, h, dy, S=0;
    QPolygonF Poly1_0, Poly1_1, Poly2_0, Poly2_1;

    switch (P1) {
    case 0:
        Poly1_0=Poly1SA_0;
        Poly1_1=Poly1SA_1;
        break;
    case 1:
        Poly1_0=Poly2SAB2_0;
        Poly1_1=Poly2SAB2_1;
        break;
    case 2:
        Poly1_0=Poly3TA_0;
        Poly1_1=Poly3TA_1;
        break;
    case 3:
        Poly1_0=Poly4VRT_0;
        Poly1_1=Poly4VRT_1;
        break;
    case 4:
        Poly1_0=Poly5GZ_0;
        Poly1_1=Poly5GZ_1;
        break;
    case 5:
        Poly1_0=Poly6KR_0;
        Poly1_1=Poly6KR_1;
        break;
    case 6:
        Poly1_0=Poly7ADA_0;
        Poly1_1=Poly7ADA_1;
        break;
    default:
        Poly1_0=QPolygonF();
        Poly1_1=QPolygonF();

        break;
    }

    switch (P2) {
    case 0:
        Poly2_0=Poly1SA_0;
        Poly2_1=Poly1SA_1;
        break;
    case 1:
        Poly2_0=Poly2SAB2_0;
        Poly2_1=Poly2SAB2_1;
        break;
    case 2:
        Poly2_0=Poly3TA_0;
        Poly2_1=Poly3TA_1;
        break;
    case 3:
        Poly2_0=Poly4VRT_0;
        Poly2_1=Poly4VRT_1;
        break;
    case 4:
        Poly2_0=Poly5GZ_0;
        Poly2_1=Poly5GZ_1;
        break;
    case 5:
        Poly2_0=Poly6KR_0;
        Poly2_1=Poly6KR_1;
        break;
    case 6:
        Poly2_0=Poly7ADA_0;
        Poly2_1=Poly7ADA_1;
        break;
    default:
        Poly2_0=QPolygonF();
        Poly2_1=QPolygonF();
        break;
    }

    QPolygonF intPoly = Poly1_0.intersected(Poly2_0);
    if(intPoly.isEmpty()) return 0.01 ;
    QRectF myRect = intPoly.boundingRect();
    myRect.getRect(&x, &y, &w, &h);
    dx=w/N;
    dy=h/N;
    for(int row=1; row<N; row+=2)
    {
        xi=x+dx*row;
        for(int col=1; col<N; col+=2)
        {
            yi=y+dy*col;
            t=1;
            if(P1 == 5) t *= Reley(yi);
            if(P2 == 5) t *= Reley(yi);
            S += 16.0 * t * myPointInVHnum(Poly1_0, Poly1_1, xi, yi) * myPointInVHnum(Poly2_0, Poly2_1, xi, yi);

            t=1;
            if(P1 == 5) t *= Reley(yi-dy);
            if(P2 == 5) t *= Reley(yi-dy);
            S += 5.0 * t * myPointInVHnum(Poly1_0, Poly1_1, xi-dx, yi-dy) * myPointInVHnum(Poly2_0, Poly2_1, xi-dx, yi-dy);

            t=1;
            if(P1 == 5) t *= Reley(yi-dy);
            if(P2 == 5) t *= Reley(yi-dy);
            S += 5.0 * t * myPointInVHnum(Poly1_0, Poly1_1, xi+dx, yi-dy) * myPointInVHnum(Poly2_0, Poly2_1, xi+dx, yi-dy);

            t=1;
            if(P1 == 5) t *= Reley(yi+dy);
            if(P2 == 5) t *= Reley(yi+dy);
            S += 5.0 * t * myPointInVHnum(Poly1_0, Poly1_1, xi-dx, yi+dy) * myPointInVHnum(Poly2_0, Poly2_1, xi-dx, yi-dy);

            t=1;
            if(P1 == 5) t *= Reley(yi+dy);
            if(P2 == 5) t *= Reley(yi+dy);
            S += 5.0 * t * myPointInVHnum(Poly1_0, Poly1_1, xi+dx, yi+dy) * myPointInVHnum(Poly2_0, Poly2_1, xi+dx, yi-dy);
        }
    }
    return S/9.0;
}

void Widget::on_radioButton_VH1_clicked()  // переключиться на таблицу VH для СА
{
    setVHtable(0);
}

void Widget::on_radioButton_VH2_clicked()  // переключиться на таблицу VH для ТА
{
    setVHtable(1);
}

void Widget::on_radioButton_VH3_clicked()  // переключиться на таблицу VH для ВРТ
{
    setVHtable(2);
}

void Widget::on_radioButton_VH4_clicked()  // переключиться на таблицу VH для ГЗЛА
{
    setVHtable(3);
}

void Widget::on_radioButton_VH5_clicked()  // переключиться на таблицу VH для КР
{
    setVHtable(4);
}

void Widget::on_radioButton_VH6_clicked()
{
    setVHtable(5);
}

void Widget::on_radioButton_VH7_clicked()
{
    setVHtable(6);
}

void Widget::on_listWidget_currentRowChanged(int currentRow) // переключиться на матрицу 5х5 под номером currentRow
{
    setPtable(currentRow);
}

void Widget::on_pushButton_VHreadFile_clicked() // запустить функцию чтения таблицы VH из файла в ТЕКУЩУЮ таблицу
{
    int num;
    QString str;
    if(	ui->radioButton_VH1->isChecked() )
    {
        str = QString("VH2_1_SA.txt");
        num = myOpenDirFile4x4read( str, Poly1SA_0, Poly1SA_1 );
        myPoly4xToTab(Poly1SA_0, Poly1SA_1, num , ui->tableWidget_VH);
    }
    else if( ui->radioButton_VH2->isChecked() )
    {
        str = QString("VH2_2_SAB2.txt");
        num = myOpenDirFile4x4read( str, Poly2SAB2_0, Poly2SAB2_1 );
        myPoly4xToTab(Poly2SAB2_0, Poly2SAB2_1, num , ui->tableWidget_VH);
    }
    else if( ui->radioButton_VH3->isChecked() )
    {
        str = QString("VH2_3_TA.txt");
        num = myOpenDirFile4x4read( str, Poly3TA_0, Poly3TA_1 );
        myPoly4xToTab(Poly3TA_0, Poly3TA_1, num , ui->tableWidget_VH);
    }
    else if( ui->radioButton_VH4->isChecked() )
    {
        str = QString("VH2_4_VRT.txt");
        num = myOpenDirFile4x4read( str, Poly4VRT_0, Poly4VRT_1 );
        myPoly4xToTab(Poly4VRT_0, Poly4VRT_1, num , ui->tableWidget_VH);
    }
    else if( ui->radioButton_VH5->isChecked() )
    {
        str = QString("VH2_5_GZLA.txt");
        num = myOpenDirFile4x4read( str, Poly5GZ_0, Poly5GZ_1 );
        myPoly4xToTab(Poly5GZ_0, Poly5GZ_1, num , ui->tableWidget_VH);
    }
    else if( ui->radioButton_VH6->isChecked() )
    {
        str = QString("VH2_6_KR.txt");
        num = myOpenDirFile4x4read( str, Poly6KR_0, Poly6KR_1 );
        myPoly4xToTab(Poly6KR_0, Poly6KR_1, num , ui->tableWidget_VH);
    }
    else if( ui->radioButton_VH7->isChecked() )
    {
        str = QString("VH2_7_ADA.txt");
        num = myOpenDirFile4x4read( str, Poly7ADA_0, Poly7ADA_1 );
        myPoly4xToTab(Poly7ADA_0, Poly7ADA_1, num , ui->tableWidget_VH);
    }
    myReCalcAll();
}

void Widget::on_pushButton_VHwriteFile_clicked() // запустить функцию записи ТЕКУЩЕЙ таблицы VH в файл
{
    QString str;
    if(	ui->radioButton_VH1->isChecked() )
    {
        str = QString("VH2_1_SA.txt");
        myOpenFile4x4write( str, Poly1SA_0, Poly1SA_1 );
    }
    else if( ui->radioButton_VH2->isChecked() )
    {
        str = QString("VH2_2_SAB2.txt");
        myOpenFile4x4write( str, Poly2SAB2_0, Poly2SAB2_1 );
    }
    else if( ui->radioButton_VH3->isChecked() )
    {
        str = QString("VH2_3_TA.txt");
        myOpenFile4x4write( str, Poly3TA_0, Poly3TA_1 );
    }
    else if( ui->radioButton_VH4->isChecked() )
    {
        str = QString("VH2_4_VRT.txt");
        myOpenFile4x4write( str, Poly4VRT_0, Poly4VRT_1 );
    }
    else if( ui->radioButton_VH5->isChecked() )
    {
        str = QString("VH2_5_GZLA.txt");
        myOpenFile4x4write( str, Poly5GZ_0, Poly5GZ_1 );
    }
    else if( ui->radioButton_VH6->isChecked() )
    {
        str = QString("VH2_6_KR.txt");
        myOpenFile4x4write( str, Poly6KR_0, Poly6KR_1 );
    }
    else if( ui->radioButton_VH7->isChecked() )
    {
        str = QString("VH2_7_ADA.txt");
        myOpenFile4x4write( str, Poly7ADA_0, Poly7ADA_1 );
    }
}

void Widget::on_tableWidget_VH_cellChanged(int row, int column) // ячейка (row, column) ТЕКУЩЕЙ таблицы VH изменилась: проверить, сохранить, пересчитать
{
    if(IsInit) return;
    if(	ui->radioButton_VH1->isChecked() ) myChangeTab4Poly(ui->tableWidget_VH, Poly1SA_0, Poly1SA_1, row, column);
    else if( ui->radioButton_VH2->isChecked() ) myChangeTab4Poly(ui->tableWidget_VH, Poly2SAB2_0, Poly2SAB2_1, row, column);
    else if( ui->radioButton_VH3->isChecked() ) myChangeTab4Poly(ui->tableWidget_VH, Poly3TA_0, Poly3TA_1, row, column);
    else if( ui->radioButton_VH4->isChecked() ) myChangeTab4Poly(ui->tableWidget_VH, Poly4VRT_0, Poly4VRT_1, row, column);
    else if( ui->radioButton_VH5->isChecked() ) myChangeTab4Poly(ui->tableWidget_VH, Poly5GZ_0, Poly5GZ_1, row, column);
    else if( ui->radioButton_VH6->isChecked() ) myChangeTab4Poly(ui->tableWidget_VH, Poly6KR_0, Poly6KR_1, row, column);
    else if( ui->radioButton_VH7->isChecked() ) myChangeTab4Poly(ui->tableWidget_VH, Poly7ADA_0, Poly7ADA_1, row, column);

    myReCalcAll();
}

void Widget::on_pushButton__EPRreadFile_clicked() // запустить функцию чтения таблицы ЭПР из файла
{
    int num;
    if(L3)
    {
        if( fabs(Phi) <= 45.0 ) myFileName = QString("EPR_L3_00.txt");
        if( fabs(Phi) > 45.0 && fabs(Phi) <= 135.0 ) myFileName = QString("EPR_L3_90.txt");
        if( fabs(Phi) > 135.0 && fabs(Phi) < 225.0 ) myFileName = QString("EPR_L3_180.txt");
    }
    else
    {
        if( fabs(Phi) <= 45.0 ) myFileName = QString("EPR_L2_00.txt");
        if( fabs(Phi) > 45.0 && fabs(Phi) <= 135.0 ) myFileName = QString("EPR_L2_90.txt");
        if( fabs(Phi) > 135.0 && fabs(Phi) < 225.0 ) myFileName = QString("EPR_L2_180.txt");
    }

    num = myOpenDirFile2x4read(myFileName, PolyEPR);
    myPoly2xToTab(PolyEPR, num , ui->tableWidget_EPR);
    myReCalcAll();
}

void Widget::on_pushButton__EPRwriteFile_clicked() // запустить функцию записи таблицы в файл
{
    QString str;
    if(L3)
    {
        if( fabs(Phi) <= 45.0 ) str = QString("EPR_L3_00_NEW.txt");
        else if( fabs(Phi) > 45.0 && fabs(Phi) <= 135.0 ) str = QString("EPR_L3_90_NEW.txt");
        else if( fabs(Phi) > 135.0 && fabs(Phi) < 225.0 ) str = QString("EPR_L3_180_NEW.txt");
    }
    else
    {
        if( fabs(Phi) <= 45.0 ) str = QString("EPR_L2_00_NEW.txt");
        else if( fabs(Phi) > 45.0 && fabs(Phi) <= 135.0 ) str = QString("EPR_L2_90_NEW.txt");
        else if( fabs(Phi) > 135.0 && fabs(Phi) < 225.0 ) str = QString("EPR_L2_180_NEW.txt");
    }
    myOpenFile2x4write( str, PolyEPR );
}

void Widget::on_tableWidget_EPR_cellChanged(int row, int column) // ячейка (row, column) таблицы ЭПР изменилась: проверить, сохранить, пересчитать
{
    if(IsInit) return;
    myChangeTab2Poly(ui->tableWidget_EPR, PolyEPR, row, column);
    myReCalcAll();
}

void Widget::on_pushButton__DPreadFile_clicked() // запустить функцию чтения таблицы ДП из файла
{
    // if(IsInit) return;
    int num;
    if( fabs(Phi) <= 45.0 ) myFileName = QString("DP_00.txt");
    else if( fabs(Phi) > 45.0 && fabs(Phi) <= 135.0 ) myFileName = QString("DP_90.txt");
    else if( fabs(Phi) > 135.0 && fabs(Phi) < 225.0 ) myFileName = QString("DP_180.txt");
    num = myOpenDirFile2x4read(myFileName, PolyDP);
    myPoly2xToTab(PolyDP, num , ui->tableWidget_DP);
    myReCalcAll();
}

void Widget::on_pushButton__DPwriteFile_clicked() // запустить функцию записи таблицы ДП в файл
{
    // if(IsInit) return;
    // int num;
    QString str;
    if( fabs(Phi) <= 30.0 ) str = QString("DP_00_NEW.txt");
    else if( fabs(Phi) >= 60.0 && fabs(Phi) < 120.0 ) str = QString("DP_90_NEW.txt");
        // qDebug() << "L3 checked";
    // num =
    myOpenFile2x4write( str, PolyDP );
}

//void Widget::on_pushButton__FPreadFile_clicked() // запустить функцию чтения таблицы ЧП из файла
//{
//    // if(IsInit) return;
//    int num;
//    if( fabs(Phi) <= 45.0 ) myFileName = QString("FP_00.txt");
//    else if( fabs(Phi) > 45.0 && fabs(Phi) <= 135.0 ) myFileName = QString("FP_90.txt");
//    else if( fabs(Phi) > 135.0 && fabs(Phi) < 225.0 ) myFileName = QString("FP_180.txt");
//    num = myOpenDirFile2x4read(myFileName, PolyFP);
//    myPoly2xToTab(PolyFP, num , ui->tableWidget_FP);
//    myReCalcAll();
//}

//void Widget::on_pushButton__FPwriteFile_clicked() // запустить функцию записи таблицы ЧП в файл
//{
//    // if(IsInit) return;
//    // int num;
//    QString str;
//    if( fabs(Phi) <= 30.0 ) str = QString("FP_00_NEW.txt");
//    else if( fabs(Phi) >= 60.0 && fabs(Phi) < 120.0 ) str = QString("FP_90_NEW.txt");
//        // qDebug() << "L3 checked";
//    // num =
//    myOpenFile2x4write( str, PolyFP );
//}

void Widget::on_tableWidget_DP_cellChanged(int row, int column) // ячейка (row, column) таблицы ДП изменилась: проверить, сохранить, пересчитать
{
    if(IsInit) return;
    myChangeTab2Poly(ui->tableWidget_DP, PolyDP, row, column);
    myReCalcAll();
}

//void Widget::on_tableWidget_FP_cellChanged(int row, int column) // ячейка (row, column) таблицы ЧП изменилась: проверить, сохранить, пересчитать
//{
//    if(IsInit) return;
//    myChangeTab2Poly(ui->tableWidget_FP, PolyFP, row, column);
//    myReCalcAll();
//}

void Widget::on_lineEdit_V_editingFinished() // изменилось значение скорости: проверить, сохранить, пересчитать
{
    myCheckNewValue(ui->lineEdit_V, "СКОРОСТЬ,СКОРОСТИ", myPoint.rx(), minV, maxV ); // QString("СКОРОСТЬ СКОРОСТИ")
    if( myChangeValueAccepted )
    {
        myChangeValueAccepted=false;
        myReCalcAll();
    }
}

void Widget::on_lineEdit_H_editingFinished() // изменилось значение высоты: проверить, сохранить, пересчитать
{
    myCheckNewValue(ui->lineEdit_H, "ВЫСОТА,ВЫСОТЫ", myPoint.ry(), minH, maxH );
    if( myChangeValueAccepted )
    {
        myChangeValueAccepted=false;
        myReCalcAll();
    }
}

void Widget::on_lineEdit_Phi_editingFinished() // изменилось значение ракурса: проверить, сохранить, пересчитать
{
    myCheckNewValue(ui->lineEdit_Phi, "РАКУРС,РАКУРСА", Phi, minPhi, maxPhi );
    if( myChangeValueAccepted )
    {
        myChangeValueAccepted=false;
        myLoadEPR();
        myLoadDP();
        myReCalcAll();
    }
}

void Widget::on_radioButton_L2_clicked()  // изменился диапазон на L2: пересчитать
{
    L3=false;
    // ui->radioButton_L2->checkStateSet();
    myLoadEPR();
    myReCalcAll();
}

void Widget::on_radioButton_L3_clicked()  // изменился диапазон на L3: пересчитать
{
    L3=true;
    myLoadEPR();
    myReCalcAll();
}

void Widget::on_lineEdit_S_editingFinished() // изменилось значение ЭПР: проверить, сохранить, пересчитать
{
    myCheckNewValue(ui->lineEdit_S, "Эффективная Площадь Рассеяния (ЭПР),Эффективной Площади Рассеяния", mEPR, minEPR, maxEPR );
    if( myChangeValueAccepted )
    {
        myChangeValueAccepted=false;
        myReCalcAll();
    }
}

void Widget::on_lineEdit_dS_editingFinished() // изменилось значение ошибки ЭПР: проверить, сохранить, пересчитать
{
    myCheckNewValue(ui->lineEdit_dS, "Ошибка ЭПР,Ощибки ЭПР", mEPRd, minEPR, maxEPR );
    if( myChangeValueAccepted )
    {
        myChangeValueAccepted=false;
        myReCalcAll();
    }
}

void Widget::on_lineEdit_DP_editingFinished() // изменилось значение ДП: проверить, сохранить, пересчитать
{
    myCheckNewValue(ui->lineEdit_DP, "Дальностный Портрет (ДП),Дальностного Портрета", mDP, minDP, maxDP );
    if( myChangeValueAccepted )
    {
        myChangeValueAccepted=false;
        myReCalcAll();
    }
}

void Widget::on_lineEdit_dDP_editingFinished() // изменилось значение ошибки ДП: проверить, сохранить, пересчитать
{
    myCheckNewValue(ui->lineEdit_dDP, "Ошибка Дальностного Портрета,Ошибки Дальностного Портрета", mDPd, minDP, maxDP );
    if( myChangeValueAccepted )
    {
        myChangeValueAccepted=false;
        myReCalcAll();
    }
}

//void Widget::on_lineEdit_FP_editingFinished() // изменилось значение ЧП: проверить, сохранить, пересчитать
//{
//    myCheckNewValue(ui->lineEdit_FP, "Частотный Портрет (ЧП),Частотного Портрета", mFP, minFP, maxFP );
//    if( myChangeValueAccepted )
//    {
//        myChangeValueAccepted=false;
//        myReCalcAll();
//    }
//}

//void Widget::on_lineEdit_dFP_editingFinished() // изменилось значение ошибки ЧП: проверить, сохранить, пересчитать
//{
//    myCheckNewValue(ui->lineEdit_dFP, "Ошибка Частотного Портрета,Ошибки Частотного Портрета", mFPd, minFP, maxFP );
//    if( myChangeValueAccepted )
//    {
//        myChangeValueAccepted=false;
//        myReCalcAll();
//    }
//}

void Widget::on_lineEdit_SP_1_editingFinished() // изменилось значение СП-1: проверить, сохранить, пересчитать
{
    myCheckNewValue(ui->lineEdit_SP_1, "Спектральный Портрет 1 (СП),Спектрального Портрета 1", mSP_1, minSP, maxSP );
    if( myChangeValueAccepted )
    {
        myChangeValueAccepted=false;
        myReCalcAll();
    }
}

void Widget::on_lineEdit_SP_2_editingFinished() // изменилось значение СП-2: проверить, сохранить, пересчитать
{
    myCheckNewValue(ui->lineEdit_SP_2, "Спектральный Портрет 2 (СП),Спектрального Портрета 2", mSP_2, minSP, maxSP );
    if( myChangeValueAccepted )
    {
        myChangeValueAccepted=false;
        myReCalcAll();
    }
}

void Widget::on_pushButton_SaveAllMatr_clicked() // кнопка в главном окне "СОХРАНИТЬ МАТРИЦЫ"
{
    QString str;
    // myMatrText.clear();

    if(ui->radioButton_DelimIsZPT->isChecked()) myDelimInNum = QChar(',');
        else myDelimInNum = QChar('.');

    if(ui->radioButton_DelimIsSEMI->isChecked()) myDelimBetwNum=QChar(';');
        else if(ui->radioButton_DelimIsPRO->isChecked()) myDelimBetwNum=QChar(' ');
            else myDelimBetwNum=QChar('\t');
    // myOutDir.current();

    if(ui->checkBox_VH_b->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VH_b").arg(".txt");
        pm5x5=&mVH_b;
        myOpenFile5x4write();
    }

    if(ui->checkBox_VH_g->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VH_g").arg(".txt");
        pm5x5=&mVH_g;
        myOpenFile5x4write();
    }

    if(ui->checkBox_VH_p->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VH_p").arg(".txt");
        pm5x5=&mVH_p;
        myOpenFile5x4write();
    }

    if(ui->checkBox_S_b->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("EPR_b").arg(".txt");
        pm5x5=&mS_b;
        myOpenFile5x4write();
    }

    if(ui->checkBox_S_g->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("EPR_g").arg(".txt");
        pm5x5=&mS_g;
        myOpenFile5x4write();
    }

    if(ui->checkBox_S_p->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("EPR_p").arg(".txt");
        pm5x5=&mS_p;
        myOpenFile5x4write();
    }

    if(ui->checkBox_DP_b->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("DP_b").arg(".txt");
        pm5x5=&mDP_b;
        myOpenFile5x4write();
    }

    if(ui->checkBox_DP_g->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("DP_g").arg(".txt");
        pm5x5=&mDP_g;
        myOpenFile5x4write();
    }

    if(ui->checkBox_DP_p->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("DP_p").arg(".txt");
        pm5x5=&mDP_p;
        myOpenFile5x4write();
    }

//    if(ui->checkBox_FP_b->isChecked())
//    {
//        // myFileName.clear();
//        myFileName = QString("%1%2%3").arg(BegName).arg("FP_b").arg(".txt");
//        pm5x5=&mFP_b;
//        myOpenFile5x4write();
//    }

//    if(ui->checkBox_FP_g->isChecked())
//    {
//        // myFileName.clear();
//        myFileName = QString("%1%2%3").arg(BegName).arg("FP_g").arg(".txt");
//        pm5x5=&mFP_g;
//        myOpenFile5x4write();
//    }

//    if(ui->checkBox_FP_p->isChecked())
//    {
//        // myFileName.clear();
//        myFileName = QString("%1%2%3").arg(BegName).arg("FP_p").arg(".txt");
//        pm5x5=&mFP_p;
//        myOpenFile5x4write();
//    }

    if(ui->checkBox_SP_p->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("SP_p").arg(".txt");
        pm5x5=&mSP_p;
        myOpenFile5x4write();
    }

// ************  Новый способ  ****************************************************
    //
    // checkBox_VHg_Sg_g
    if(ui->checkBox_VHg_Sg_g->isChecked())
    {
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_EPRg_g").arg(".txt");
        pm5x5=&mVHg_Sg_g;
        myOpenFile5x4write();
    }

    // checkBox_VHg_Sg_p
    if(ui->checkBox_VHg_Sg_p->isChecked())
    {
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_EPRg_p").arg(".txt");
        pm5x5=&mVHg_Sg_p;
        myOpenFile5x4write();
    }

    // checkBox_VHg_Sg_DPg_g
    if(ui->checkBox_VHg_Sg_DPg_g->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_EPRg_DPg_g").arg(".txt");
        pm5x5=&mVHg_Sg_DPg_g;
        myOpenFile5x4write();
    }

    // checkBox_VHg_Sg_DPg_p
    if(ui->checkBox_VHg_Sg_DPg_p->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_EPRg_DPg_p").arg(".txt");
        pm5x5=&mVHg_Sg_DPg_p;
        myOpenFile5x4write();
    }

    // checkBox_VHg_Sg_G_SP_g
    if(ui->checkBox_VHg_Sg_G_SP_g->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_Sg_G_SP_g").arg(".txt");
        pm5x5=&mVHg_Sg_G_SP_g;
        myOpenFile5x4write();
    }

    // checkBox_VHg_Sg_G_SP_p
    if(ui->checkBox_VHg_Sg_G_SP_p->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_Sg_G_SP_p").arg(".txt");
        pm5x5=&mVHg_Sg_G_SP_p;
        myOpenFile5x4write();
    }

    // checkBox_VHg_Sg_DPg_G_SP_g
    if(ui->checkBox_VHg_Sg_DPg_G_SP_g->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_Sg_DPg_G_SP_g").arg(".txt");
        pm5x5=&mVHg_Sg_DPg_G_SP_g;
        myOpenFile5x4write();
    }

    // checkBox_VHg_Sg_DPg_G_SP_p
    if(ui->checkBox_VHg_Sg_DPg_G_SP_p->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_Sg_DPg_G_SP_p").arg(".txt");
        pm5x5=&mVHg_Sg_DPg_G_SP_p;
        myOpenFile5x4write();
    }


    // checkBox_VHg_Sg_P_SP_g
    if(ui->checkBox_VHg_Sg_P_SP_g->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_Sg_P_SP_g").arg(".txt");
        pm5x5=&mVHg_Sg_P_SP_g;
        myOpenFile5x4write();
    }

    // checkBox_VHg_Sg_P_SP_p
    if(ui->checkBox_VHg_Sg_P_SP_p->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_Sg_P_SP_p").arg(".txt");
        pm5x5=&mVHg_Sg_P_SP_p;
        myOpenFile5x4write();
    }

    // checkBox_VHg_Sg_DPg_P_SP_g
    if(ui->checkBox_VHg_Sg_DPg_P_SP_g->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_Sg_DPg_P_SP_g").arg(".txt");
        pm5x5=&mVHg_Sg_DPg_P_SP_g;
        myOpenFile5x4write();
    }

    // checkBox_VHg_Sg_DPg_P_SP_p
    if(ui->checkBox_VHg_Sg_DPg_P_SP_p->isChecked())
    {
        // myFileName.clear();
        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_Sg_DPg_P_SP_p").arg(".txt");
        pm5x5=&mVHg_Sg_DPg_P_SP_p;
        myOpenFile5x4write();
    }



    // *****
// ************  Старый способ  ***************************************************
    // *** Отмечаем всё оптом !!! *********************
    // checkBox_Old_g
    // checkBox_Old_p
    if(ui->checkBox_Old_g->isChecked())
    {
        // ***** Осмысленное   **********************
        myFileName = QString("%1%2%3").arg(BegName).arg("VH_EPR_g").arg(".txt");
        pm5x5=&mVH_S_g;
        myOpenFile5x4write();

        myFileName = QString("%1%2%3").arg(BegName).arg("VH_EPR_DP_g").arg(".txt");
        pm5x5=&mVH_S_DP_g;
        myOpenFile5x4write();

        myFileName = QString("%1%2%3").arg(BegName).arg("VH_EPR_SP_g").arg(".txt");
        pm5x5=&mVH_S_SP_g;
        myOpenFile5x4write();

        myFileName = QString("%1%2%3").arg(BegName).arg("VH_EPR_DP_SP_g").arg(".txt");
        pm5x5=&mVH_S_DP_SP_g;
        myOpenFile5x4write();

        // ***** Мусорное   **********************
        myFileName = QString("%1%2%3").arg(BegName).arg("VH_DP_g").arg(".txt");
        pm5x5=&mVH_DP_g;
        myOpenFile5x4write();

//        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_DPg_g").arg(".txt");
//        pm5x5=&mVHg_DPg_g;
//        myOpenFile5x4write();

        myFileName = QString("%1%2%3").arg(BegName).arg("VH_DP_EPR_g").arg(".txt");
        pm5x5=&mVH_DP_S_g;
        myOpenFile5x4write();

    }

    if(ui->checkBox_Old_p->isChecked())
    {
        // ***** Осмысленное   **********************
        myFileName = QString("%1%2%3").arg(BegName).arg("VH_EPR_p").arg(".txt");
        pm5x5=&mVH_S_p;
        myOpenFile5x4write();

        myFileName = QString("%1%2%3").arg(BegName).arg("VH_EPR_DP_p").arg(".txt");
        pm5x5=&mVH_S_DP_p;
        myOpenFile5x4write();

        myFileName = QString("%1%2%3").arg(BegName).arg("VH_EPR_SP_p").arg(".txt");
        pm5x5=&mVH_S_SP_p;
        myOpenFile5x4write();

        myFileName = QString("%1%2%3").arg(BegName).arg("VH_EPR_DP_SP_p").arg(".txt");
        pm5x5=&mVH_S_DP_SP_p;
        myOpenFile5x4write();

        // ***** Мусорное   **********************
        myFileName = QString("%1%2%3").arg(BegName).arg("VH_DP_p").arg(".txt");
        pm5x5=&mVH_DP_p;
        myOpenFile5x4write();

//        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_DPg_p").arg(".txt");
//        pm5x5=&mVHg_DPg_p;
//        myOpenFile5x4write();

        myFileName = QString("%1%2%3").arg(BegName).arg("VH_DP_EPR_p").arg(".txt");
        pm5x5=&mVH_DP_S_p;
        myOpenFile5x4write();
    }

    myFileName = QString("%1%2%3").arg(BegName).arg("NVO").arg(".txt");
    str = QString("%1\\%2").arg(myOutDir.absolutePath()).arg(myFileName);
    QFile outputFile(str);
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream myOut(&outputFile);

        str= QString("%1").arg( mNVO, 0, 'f', 4);
                if(myDelimInNum != QChar('.')) str.replace(QChar('.'), myDelimInNum, Qt::CaseSensitive);
        myOut << str ;
    }
    outputFile.close();
}


void Widget::on_pushButton_SaveDir_clicked() // кнопка в главном окне "КУДА СОХРАНЯТЬ" . Путь для сохранения матриц записывается в myOutDir
{
    QStringList filters;
    filters << "Text files (*.txt)" << "Any files (*)";

    QFileDialog dialog(this);
    dialog.setNameFilters(filters);
    dialog.setFileMode(QFileDialog::Directory);
    if(dialog.exec()) myOutDir=dialog.directory();
}

void Widget::on_lineEdit_BegName_editingFinished() // поле ввода "Начало имени файлов"  в главном окне сохраняется в BegName
{
    BegName = ui->lineEdit_BegName->text();
}

void Widget::on_pushButton_DPgra_clicked() // кнопка "Показать на графике" на вкладке "Дальностный портрет"
{
    addPlotDP = new myGauss();
    if(ui->checkBox_SA_DP->isChecked()) addPlotDP->addMyGauss2Graphs(PolyDP[0], QString("SA"), QColor(Qt::darkGreen));
    if(ui->checkBox_SAB2_DP->isChecked()) addPlotDP->addMyGauss2Graphs(PolyDP[1], QString("SA-B2"), QColor(Qt::darkBlue));
    if(ui->checkBox_TA_DP->isChecked()) addPlotDP->addMyGauss2Graphs(PolyDP[2], QString("TA"), QColor(Qt::green));
    if(ui->checkBox_VRT_DP->isChecked()) addPlotDP->addMyGauss2Graphs(PolyDP[3], QString("VRT"), QColor(Qt::magenta));
    if(ui->checkBox_GZLA_DP->isChecked()) addPlotDP->addMyGauss2Graphs(PolyDP[4], QString("GZLA"), QColor(Qt::cyan));
    if(ui->checkBox_KR_DP->isChecked()) addPlotDP->addMyGauss2Graphs(PolyDP[5], QString("KR"), QColor(Qt::black));
    if(ui->checkBox_ADA_DP->isChecked()) addPlotDP->addMyGauss2Graphs(PolyDP[6], QString("ADA"), QColor(Qt::darkCyan));
    if(ui->checkBox_mP_DP->isChecked())
    {
        QPointF PointDP=QPointF(mDP,mDPd);
        addPlotDP->addMyGauss2Graphs(PointDP, QString("Точка ДП"), QColor(Qt::red));
    }
    addPlotDP->setWindowTitle( QString("DP Дальностный портрет") );
    addPlotDP->addMyTitle( QString("DP  Дальностный портрет") );
    addPlotDP->addMyLabels( QString("Положение максимума, ширина ( м )"), QString("Плотность вероятности") );

    addPlotDP->show();
}

//void Widget::on_pushButton_FPgra_clicked() // кнопка "Показать на графике" на вкладке "Частотный портрет"
//{
//    addPlotFP = new myGauss();
//    if(ui->checkBox_SA_FP->isChecked()) addPlotFP->addMyGauss2Graphs(PolyFP[0], QString("SA"), QColor(Qt::darkGreen));
//    if(ui->checkBox_SAB2_FP->isChecked()) addPlotFP->addMyGauss2Graphs(PolyFP[1], QString("SA-B2"), QColor(Qt::darkBlue));
//    if(ui->checkBox_TA_FP->isChecked()) addPlotFP->addMyGauss2Graphs(PolyFP[2], QString("TA"), QColor(Qt::green));
//    if(ui->checkBox_VRT_FP->isChecked()) addPlotFP->addMyGauss2Graphs(PolyFP[3], QString("VRT"), QColor(Qt::magenta));
//    if(ui->checkBox_GZLA_FP->isChecked()) addPlotFP->addMyGauss2Graphs(PolyFP[4], QString("GZLA"), QColor(Qt::cyan));
//    if(ui->checkBox_KR_FP->isChecked()) addPlotFP->addMyGauss2Graphs(PolyFP[5], QString("KR"), QColor(Qt::black));
//    if(ui->checkBox_ADA_FP->isChecked()) addPlotFP->addMyGauss2Graphs(PolyFP[6], QString("ADA"), QColor(Qt::darkCyan));
//    if(ui->checkBox_mP_FP->isChecked())
//    {
//        QPointF PointFP=QPointF(mFP,mFPd);
//        addPlotFP->addMyGauss2Graphs(PointFP, QString("Точка ЧП"), QColor(Qt::red));
//    }
//    addPlotFP->setWindowTitle( QString("FP Частотный портрет") );
//    addPlotFP->addMyTitle( QString("FP  Частотный портрет") );
//    addPlotFP->addMyLabels( QString("Положение максимума, ширина ( м )"), QString("Плотность вероятности") );

//    addPlotFP->show();
//}

void Widget::on_pushButton_VHgra_clicked() // кнопка "Показать на графике" на вкладке "График" вкладки "Траекторные характеристики"
{
    addPlotVH = new myPlot();
    if(ui->checkBox_SA->isChecked()) addPlotVH->addMyPoly2Graphs(Poly1SA_0, Poly1SA_1, QString("SA"), QColor(Qt::darkGreen));
    if(ui->checkBox_SAB2->isChecked()) addPlotVH->addMyPoly2Graphs(Poly2SAB2_0, Poly2SAB2_1, QString("SA-B2"), QColor(Qt::darkBlue));
    if(ui->checkBox_TA->isChecked()) addPlotVH->addMyPoly2Graphs(Poly3TA_0, Poly3TA_1, QString("TA"), QColor(Qt::green));
    if(ui->checkBox_VRT->isChecked()) addPlotVH->addMyPoly2Graphs(Poly4VRT_0, Poly4VRT_1, QString("VRT"), QColor(Qt::magenta));
    if(ui->checkBox_GZLA->isChecked()) addPlotVH->addMyPoly2Graphs(Poly5GZ_0, Poly5GZ_1, QString("GZLA"), QColor(Qt::cyan));
    if(ui->checkBox_KR->isChecked()) addPlotVH->addMyPoly2Graphs(Poly6KR_0, Poly6KR_1, QString("KR"), QColor(Qt::black));
    if(ui->checkBox_ADA->isChecked()) addPlotVH->addMyPoly2Graphs(Poly7ADA_0, Poly7ADA_1, QString("ADA"), QColor(Qt::darkCyan));
    if(ui->checkBox_mP->isChecked()) addPlotVH->addMyPoint2Graphs(myPoint, QString("Точка"), QColor(Qt::red));

    addPlotVH->setWindowTitle( QString("ММ РКЦ    VH  Пространство скорость-высота") );
    addPlotVH->addMyTitle( QString("VH  Пространство скорость-высота") );
    addPlotVH->addMyLabels( QString("V Скорость (км/ч) "), QString("H Высота (км) ") );
    addPlotVH->show();
}

void Widget::on_pushButton_EPRgra_clicked() // кнопка "Показать на графике" на вкладке "ЭПР"
{
    addPlotEPR = new myGauss();

    if(ui->checkBox_SA_EPR->isChecked()) addPlotEPR->addMyGauss2Graphs(PolyEPR[0], QString("SA"), QColor(Qt::darkGreen));
    if(ui->checkBox_SAB2_EPR->isChecked()) addPlotEPR->addMyGauss2Graphs(PolyEPR[1], QString("SA-B2"), QColor(Qt::darkBlue));
    if(ui->checkBox_TA_EPR->isChecked()) addPlotEPR->addMyGauss2Graphs(PolyEPR[2], QString("TA"), QColor(Qt::green));
    if(ui->checkBox_VRT_EPR->isChecked()) addPlotEPR->addMyGauss2Graphs(PolyEPR[3], QString("VRT"), QColor(Qt::magenta));
    if(ui->checkBox_GZLA_EPR->isChecked()) addPlotEPR->addMyGauss2Graphs(PolyEPR[4], QString("GZLA"), QColor(Qt::cyan));
    if(ui->checkBox_KR_EPR->isChecked()) addPlotEPR->addMyGauss2Graphs(PolyEPR[5], QString("KR"), QColor(Qt::black));
    if(ui->checkBox_ADA_EPR->isChecked()) addPlotEPR->addMyGauss2Graphs(PolyEPR[6], QString("ADA"), QColor(Qt::darkCyan));
    if(ui->checkBox_mP_EPR->isChecked())
    {
        QPointF PointEPR=QPointF(mEPR,mEPRd);
        addPlotEPR->addMyGauss2Graphs(PointEPR, QString("Точка ЭПР"), QColor(Qt::red));
    }

    addPlotEPR->setWindowTitle( QString("ММ РКЦ    ЭПР  Эффективная площадь рассеяния") );
    addPlotEPR->addMyTitle( QString("EPR  Эффективная площадь рассеяния") );
    addPlotEPR->addMyLabels( QString("Положение максимума, ширина (кв.м)"), QString("Плотность вероятности") );

    addPlotEPR->show();
}

void Widget::on_pushButton_ShowResult_clicked()  // кнопка в главном окне "Показать результат"
{
    myShowResultDialog(true);
}

void Widget::on_radioButton_GC_Sq_toggled(bool)   //  checked Выбор в главном окне "Пересечение Гауссов"
{
    myReCalcAll();
}

void Widget::on_pushButton_InDataRead_clicked()
{
    // qDebug() << "void Widget::on_pushButton_InDataRead_clicked()";
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Загрузить новые данные"),
                                            myInDir.absolutePath(),
                                            tr("Файлы данных (*.txt *.in)"));
    if(fileName.isNull())
    {
        myMsg("Файл не прочитался");
    }
    else
    {
        myInDir.setPath(fileName);
        myOpenDirFileInData(fileName);
    }
}

void Widget::myMsg(const QString inText)
{
    QMessageBox msgBox;
    msgBox.setText(inText);
    msgBox.exec();
}

void Widget::on_pushButton_InDataWrite_clicked()
{
    // qDebug() << "void Widget::on_pushButton_InDataRead_clicked()";

    QString fileName = QFileDialog::getSaveFileName(this,
                                            tr("Сохранить отредактированные данные"),
                                            myInDir.absolutePath(),
                                            tr("Файлы данных (*.txt *.in)"));
    if(fileName.isNull())
    {
        myMsg("Файл не найден");
    }
    else
    {
        myInDir.setPath(fileName);
        myOpenDirFileOutData(fileName);
    }
}

void Widget::myOpenDirFileOutData(QString &fileName)
{
    QString text;

//    QFile outFile(fileName);
//    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
//              return;
    QTextStream out(&text);
    // out.setCodec("Windows-1251");   - то тоже работает, но UTF-8 универсальнее
    out.setCodec("UTF-8");

    out << tr("// Это файл входных параметров \n")
        << tr("# / : ; - на эти символы начинаются строки комментариев \n\n")
        << tr("# Диапазон L2 или L3  \n")
        << tr("Diapazon ");

    if(ui->radioButton_L3->isChecked())
    {
        out << tr("L3"); // установили диапазон L3
    }
    else
    {
        out << tr("L2"); // установили диапазон L2
    }

    out << tr("\n\n; Ракурс в градусах \nRAKURS ")
        << QString("%1").arg(Phi, 0, 'G', 6)
        << tr(" // запятые преобразуются в точки при чтении параметров\n\n")
        << tr(": Спектральный портрет - два числа\nSP ")
        << QString("%1 %2\n\n").arg(mSP_1, 0, 'G', 6).arg(mSP_2, 0, 'G', 6)
        << tr("// VH - скорость в км/ч и высота в км\nVH ")
        << QString("%1 %2\n\n").arg(myPoint.x(), 0, 'G', 6).arg(myPoint.y(), 0, 'G', 6)
        << tr("// ЭПР - эффективная площадь рассеяния и её дисперсия в кв.м\nepr ")
        << QString("%1 %2\n\n").arg(mEPR, 0, 'G', 6).arg(mEPRd, 0, 'G', 6)
        << tr("// ДП - дальностный портрет и его дисперсия в метрах\ndp ")
        << QString("%1 %2\n\n").arg(mDP, 0, 'G', 6).arg(mDPd, 0, 'G', 6)
        << tr("# все строки, кроме комментариев, пустых строк и параметров увеличивают возвращаемый счетчик,\n")
        << tr("# но ничего не меняют. Так что писать можно всё, но избегать ключевых слов\n")
        << tr("# Diapazon, RAKURS, SP, EPR и DP в начале строки.\n")
        << tr(": при чтении файла первое слово в строке переводится в ВЕРХНИЙ РЕГИСТР и сравнивается с ключевыми\n")
        << tr(": Файл читается до конца. Присваиваются все найденные значения.\n")
        << tr(": Рабочим будет последнее правильно прочитанное");

    myParamText.clear();
    myParamText = text;

//    BegName = ui->lineEdit_BegName->text();
    /* ="4_VRT_" Инициализация значения "НАЧАЛО ИМЕНИ СОХРАНЯЕМЫХ ФАЙЛОВ" из поля ввода главного окна */
    QFile outFile(fileName);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
              return;
    QTextStream fout(&outFile);
    // fout.setCodec("Windows-1251");   - то тоже работает, но UTF-8 универсальнее
    fout.setCodec("UTF-8");

    fout << text;
    if(ui->checkBox_ResName->isChecked())
    {
        QFileInfo fi(outFile.fileName());
        QString BegName = fi.baseName()+"_";
        ui->lineEdit_BegName->setText(BegName);
    }
    outFile.close();

    return;
}

void Widget::on_pushButton_InDataEdit_clicked()
{
    QString str = QCoreApplication::applicationDirPath() + "/" + QString("qtedit.exe ");
    if(!inFile.isEmpty()) str += inFile;

    QProcess *editor = new QProcess(this);
    editor->start(str);
}

void Widget::on_pushButton_SaveRes_clicked()
{
    QString text, name, str;
    if(ui->checkBox_ResName) name = myOutDir.absolutePath() + "/" + BegName + "_res.txt";
    else name = myOutDir.absolutePath() + "/default_res.txt";

    QFile outFile(name);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
              return;
    QTextStream out(&outFile);
    // out.setCodec("Windows-1251");   - то тоже работает, но UTF-8 универсальнее
    out.setCodec("UTF-8");

    out << myResText ;

    if(ui->checkBox_ResInput)
        out << tr("\n *********************** Начало файла входных данных ***********************\n")
            << inFile
            << "\n\n"
            << myParamText
            << tr("\n *********************** Конец файла входных данных ***********************\n") ;

    if(ui->checkBox_ResTab)
    {
        SaveMatr2Res();
        out << tr("\n *********************** Начало таблиц вероятностей ***********************\n\n")
            << myMatrText
            << tr("\n *********************** Конец таблиц вероятностей ***********************\n") ;
    }

    outFile.close();
    return;

}

void Widget::SaveMatr2Res(void) // кнопка в главном окне "СОХРАНИТЬ МАТРИЦЫ"
{
    myMatrText.clear();

    if(ui->radioButton_DelimIsZPT->isChecked()) myDelimInNum = QChar(',');
        else myDelimInNum = QChar('.');

    if(ui->radioButton_DelimIsSEMI->isChecked()) myDelimBetwNum=QChar(';');
        else if(ui->radioButton_DelimIsPRO->isChecked()) myDelimBetwNum=QChar(' ');
            else myDelimBetwNum=QChar('\t');
    // myOutDir.current();

//     void myMatr2res(bool , QString );

    // pm5x5=&mVH_b;
    myMatr2res(ui->checkBox_VH_b->isChecked() || ui->radioButton_AllTab->isChecked(), mVH_b, QString("VH_b") );

    myMatr2res(ui->checkBox_VH_g->isChecked() || ui->radioButton_AllTab->isChecked(), mVH_g, QString("VH_g") );

    myMatr2res(ui->checkBox_VH_p->isChecked() || ui->radioButton_AllTab->isChecked(), mVH_p, QString("VH_p") );

    myMatr2res(ui->checkBox_S_b->isChecked() || ui->radioButton_AllTab->isChecked(), mS_b, QString("EPR_b") );

    myMatr2res(ui->checkBox_S_g->isChecked() || ui->radioButton_AllTab->isChecked(), mS_g, QString("EPR_g") );

    myMatr2res(ui->checkBox_S_p->isChecked() || ui->radioButton_AllTab->isChecked(), mS_p, QString("EPR_p") );

    myMatr2res(ui->checkBox_DP_b->isChecked() || ui->radioButton_AllTab->isChecked(), mDP_b, QString("DP_b") );

    myMatr2res(ui->checkBox_DP_g->isChecked() || ui->radioButton_AllTab->isChecked(), mDP_g, QString("DP_g") );

    myMatr2res(ui->checkBox_DP_p->isChecked() || ui->radioButton_AllTab->isChecked(), mDP_p, QString("DP_p") );


    myMatr2res(ui->checkBox_SP_p->isChecked() || ui->radioButton_AllTab->isChecked(), mSP_p, QString("SP_p") );

// ************  Новый способ  ****************************************************
    //
    // checkBox_VHg_EPRg_g
    myMatr2res(ui->checkBox_VHg_Sg_g->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_g, QString("VHg_EPRg_g") );

    // checkBox_VHg_Sg_p
    myMatr2res(ui->checkBox_VHg_Sg_p->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_p, QString("VHg_EPRg_p") );

    // checkBox_VHg_Sg_DPg_g
    myMatr2res(ui->checkBox_VHg_Sg_DPg_g->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_DPg_g, QString("VHg_EPRg_DPg_g") );

    // checkBox_VHg_Sg_DPg_p
    myMatr2res(ui->checkBox_VHg_Sg_DPg_p->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_DPg_p, QString("VHg_EPRg_DPg_p") );

    // checkBox_VHg_Sg_G_SP_g
    myMatr2res(ui->checkBox_VHg_Sg_G_SP_g->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_G_SP_g, QString("VHg_EPRg_G_SP_g") );

    // checkBox_VHg_Sg_G_SP_p
    myMatr2res(ui->checkBox_VHg_Sg_G_SP_p->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_G_SP_p, QString("VHg_EPRg_G_SP_p") );

    // checkBox_VHg_Sg_DPg_G_SP_g
    myMatr2res(ui->checkBox_VHg_Sg_DPg_G_SP_g->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_DPg_G_SP_g, QString("VHg_EPRg_DPg_G_SP_g") );

    // checkBox_VHg_Sg_DPg_G_SP_p
    myMatr2res(ui->checkBox_VHg_Sg_DPg_G_SP_p->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_DPg_G_SP_p, QString("VHg_EPRg_DPg_G_SP_p") );

    // checkBox_VHg_Sg_P_SP_g
    myMatr2res(ui->checkBox_VHg_Sg_P_SP_g->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_P_SP_g, QString("VHg_EPRg_P_SP_g") );

    // checkBox_VHg_Sg_P_SP_p
    myMatr2res(ui->checkBox_VHg_Sg_P_SP_p->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_P_SP_p, QString("VHg_EPRg_P_SP_p") );

    // checkBox_VHg_Sg_DPg_P_SP_g
    myMatr2res(ui->checkBox_VHg_Sg_DPg_P_SP_g->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_DPg_P_SP_g, QString("VHg_EPRg_DPg_P_SP_g") );

    // checkBox_VHg_Sg_DPg_P_SP_p
    myMatr2res(ui->checkBox_VHg_Sg_DPg_P_SP_p->isChecked() || ui->radioButton_AllTab->isChecked(), mVHg_Sg_DPg_P_SP_p, QString("VHg_EPRg_DPg_P_SP_p") );

    // *****
// ************  Старый способ  ***************************************************
    // *** Отмечаем всё оптом !!! *********************
    // checkBox_Old_g
    // checkBox_Old_p
    if(ui->checkBox_Old_g->isChecked() || ui->checkBox_Old_p->isChecked() || ui->radioButton_AllTab->isChecked())
        myMatrText += QString("------ по-старому ------\n");
    if(ui->checkBox_Old_g->isChecked() || ui->radioButton_AllTab->isChecked())
    {
        // myMatrText += QString("------ по-старому ------\n");
        // ***** Осмысленное   **********************
        myMatr2res(true, mVH_S_g, QString("VH_EPR_g") );

        myMatr2res(true, mVH_S_DP_g, QString("VH_EPR_DP_g") );

        myMatr2res(true, mVH_S_SP_g, QString("VH_EPR_SP_g") );

        myMatr2res(true, mVH_S_DP_SP_g, QString("VH_EPR_DP_SP_g") );

        // ***** Мусорное   **********************
        myMatr2res(true, mVH_DP_g, QString("VH_DP_g") );

//        myFileName = QString("%1%2%3").arg(BegName).arg("VHg_DPg_g").arg(".txt");
//        pm5x5=&mVHg_DPg_g;
//        myOpenFile5x4write();

        myMatr2res(true, mVH_DP_S_g, QString("VH_DP_EPR_g") );
    }

    if(ui->checkBox_Old_p->isChecked() || ui->radioButton_AllTab->isChecked())
    {
        // ***** Осмысленное   **********************
        myMatr2res(true, mVH_S_p, QString("VH_EPR_p") );

        myMatr2res(true, mVH_S_DP_p, QString("VH_EPR_DP_p") );

        myMatr2res(true, mVH_S_SP_p, QString("VH_EPR_SP_p") );

        myMatr2res(true, mVH_S_DP_SP_p, QString("VH_EPR_DP_SP_p") );

        // ***** Мусорное   **********************
        myMatr2res(true, mVH_DP_p, QString("VH_DP_p") );

        myMatr2res(true, mVH_DP_S_p, QString("VH_DP_EPR_p") );
    }
}

void Widget::save1Matr2res(double p[][7])
{
    for(int row=0; row<7; ++row)
    {
        for(int col=0; col<7; ++col)
        {
            QString s= QString("%1").arg( p[row][col], 0, 'f', 3);
            if(myDelimInNum != QChar('.')) s.replace(QChar('.'), myDelimInNum, Qt::CaseSensitive);
            myMatrText += s;
            col<6 ? (myMatrText += myDelimBetwNum) : (myMatrText += "\n") ;
        }
    }
    // myMatrText += "";
}

void Widget::myMatr2res(bool isChe, double p[][7], QString myMatrName)
{
    if( !isChe) return;
    myMatrText += ">>> Начало матрицы " + myMatrName + " \n";
    // pm5x5 = p;
    save1Matr2res(p);
    myMatrText += "<<< Конец матрицы " + myMatrName + " \n\n";
}

//void Widget::mySortMatr(double p[][7], int i[7])
//{
//    int ti, ind[7]={0,1,2,3,4,5,6};
//    double td, myDiag[7];

//    for (int i = 0; i < 7; ++i) {
//        myDiag[i]=p[i][i];
//    }

//    for(int i1=0; i1<7; ++i1)
//    {
//        for(int i2=1; i2<7; ++i2)
//        {
//            if(myDiag[i1] < myDiag[i2])
//            {
//                td = myDiag[i2];
//                myDiag[i2] = myDiag[i1];
//                myDiag[i1] = td;
//                ti = ind[i2];
//                ind[i2] = ind[i1];
//                ind[i1] = ti;
//            }
//        }
//    }


//}
