#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QFileDevice>
#include <QTextStream>
#include <QFileDialog>
#include <QRegExp>
#include <QBrush>
#include <cmath>        // fabs()
#include <algorithm>    // std::min()
// #include <iostream>  // in & out
#include <QInputDialog>
#include "myplot.h"     // моё окно VH-графиков
#include "qcustomplot.h"    // библиотека QCP для 2Д-графиков
#include "resdialog.h"      // моё окно отчета о принятом решении
#include "myinputerrordialog.h"     // моё окно про ошибку ввода - "не цифра"
#include "myinputwarningdialog.h"   // моё окно про подтверждение ввода - "диапазон"
#include "mygauss.h"    // мои окна графиков ЭПР и ДП
#include <QtWidgets>    // QMessageBox
#include <QCoreApplication>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
//    QFile outputMsgFile; // Файл для сохранения отладочных сообщений, доступный по всему проекту
//    QTextStream myOutMsg; // Поток, связанный с этим файлом ( myOutMsg << "сообщение"; )

private slots:
    void on_radioButton_VH1_clicked();  // переключиться на таблицу VH для СА
    void on_radioButton_VH2_clicked();  // переключиться на таблицу VH для САБ2
    void on_radioButton_VH3_clicked();  // переключиться на таблицу VH для ТА
    void on_radioButton_VH4_clicked();  // переключиться на таблицу VH для ВРТ
    void on_radioButton_VH5_clicked();  // переключиться на таблицу VH для ГЗЛА
    void on_radioButton_VH6_clicked();  // переключиться на таблицу VH для КР
    void on_radioButton_VH7_clicked();  // переключиться на таблицу VH для АДА

    void on_listWidget_currentRowChanged(int currentRow); // переключиться на матрицу 5х5 под номером currentRow

    void on_pushButton_VHreadFile_clicked(); // запустить функцию чтения таблицы VH из файла в ТЕКУЩУЮ таблицу
    void on_pushButton_VHwriteFile_clicked(); // запустить функцию записи ТЕКУЩЕЙ таблицы VH в файл
    void on_tableWidget_VH_cellChanged(int row, int column); // ячейка (row, column) ТЕКУЩЕЙ таблицы VH изменилась: проверить, сохранить, пересчитать

    void on_pushButton__EPRreadFile_clicked(); // запустить функцию чтения таблицы ЭПР из файла
    void on_pushButton__EPRwriteFile_clicked(); // запустить функцию записи таблицы в файл
    void on_tableWidget_EPR_cellChanged(int row, int column); // ячейка (row, column) таблицы ЭПР изменилась: проверить, сохранить, пересчитать

    void on_pushButton__DPreadFile_clicked(); // запустить функцию чтения таблицы ДП из файла
    void on_pushButton__DPwriteFile_clicked(); // запустить функцию записи таблицы ДП в файл
    void on_tableWidget_DP_cellChanged(int row, int column); // ячейка (row, column) таблицы ДП изменилась: проверить, сохранить, пересчитать

//    void on_pushButton__FPreadFile_clicked();
//    void on_pushButton__FPwriteFile_clicked();
//    void on_tableWidget_FP_cellChanged(int row, int column);

    void on_lineEdit_V_editingFinished(void); // изменилось значение скорости: проверить, сохранить, пересчитать
    void on_lineEdit_H_editingFinished(); // изменилось значение высоты: проверить, сохранить, пересчитать
    void on_lineEdit_Phi_editingFinished(); // изменилось значение ракурса: проверить, сохранить, пересчитать
    void on_radioButton_L2_clicked();  // изменился диапазон на L2: пересчитать
    void on_radioButton_L3_clicked();  // изменился диапазон на L3: пересчитать
    void on_lineEdit_S_editingFinished(); // изменилось значение ЭПР: проверить, сохранить, пересчитать
    void on_lineEdit_dS_editingFinished(); // изменилось значение ошибки ЭПР: проверить, сохранить, пересчитать
    void on_lineEdit_DP_editingFinished(); // изменилось значение ДП: проверить, сохранить, пересчитать
    void on_lineEdit_dDP_editingFinished(); // изменилось значение ошибки ДП: проверить, сохранить, пересчитать
//    void on_lineEdit_FP_editingFinished();
//    void on_lineEdit_dFP_editingFinished();
    void on_lineEdit_SP_1_editingFinished(); // изменилось значение СП-1: проверить, сохранить, пересчитать
    void on_lineEdit_SP_2_editingFinished(); // изменилось значение СП-2: проверить, сохранить, пересчитать

    void on_pushButton_SaveAllMatr_clicked(); // кнопка в главном окне "СОХРАНИТЬ МАТРИЦЫ"
    void on_pushButton_SaveDir_clicked(); // кнопка в главном окне "КУДА СОХРАНЯТЬ" . Путь для сохранения матриц записывается в myOutDir
    void on_lineEdit_BegName_editingFinished();     // поле ввода "Начало имени файлов"  в главном окне

    void on_pushButton_DPgra_clicked(); // кнопка "Показать на графике" на вкладке "Дальностный портрет"
    void on_pushButton_VHgra_clicked(); // кнопка "Показать на графике" на вкладке "График" вкладки "Траекторные характеристики"
    void on_pushButton_EPRgra_clicked(); // кнопка "Показать на графике" на вкладке "ЭПР"
//    void on_pushButton_FPgra_clicked();

    void on_radioButton_GC_Sq_toggled(bool); //  checked Выбор в главном окне "Пересечение Гауссов"

    void on_pushButton_ShowResult_clicked(); // кнопка в главном окне "Показать результат"

    int myOpenDirFileInData(QString fileName);

    void on_pushButton_InDataRead_clicked();
    void on_pushButton_InDataWrite_clicked();
    void on_pushButton_InDataEdit_clicked();

    void on_pushButton_SaveRes_clicked();

private:
    Ui::Widget *ui;
    myPlot *addPlotVH; // Указатель на окно VH (объект класса myPlot)
    myGauss *addPlotEPR, *addPlotDP; //, *addPlotFP Указатели на окна ЭПР и ДП  (форму класса myGauss)
    ResDialog *FinResult; // Указатель на окно результата (объект класса ResDialog)
    myInputWarningDialog *myInputWarn;   // Указатель на окно "Выход за диапазон" (объект класса myInputWarningDialog)
    myInputErrorDialog *myInputErr;   // Указатель на окно "Не цифра" (объект класса myInputErrorDialog)

    bool L3, /* диапазон L3 - да, L2 - нет */
            IsInit, /*, находимся ли мы в состоянии автоматического изменения значений в полях ввода, например - начальный рассчет, перерассчет
            * если да - то внутри СЛОТОВ в начале проверяем эту переменную и сразу выходим, если IsInit=true */
            myChangeValueAccepted; /* значение выходит за диапазон, но принято , */
            /* myWait находимся в состоянии ожидания действий пользователя*/
    QPolygonF myPoly, myPoly1, myPoly2, myPoly_0, myPoly_1, myPoly1_0, myPoly1_1, /* Многоугольники для временного хранения и передачи в функции*/
            Poly1SA_0, Poly1SA_1, /* многоугольники в пространстве VH для СА, ограничивающие области с вероятностями 0 и 1 соответственно */
            Poly2SAB2_0, Poly2SAB2_1, /* многоугольники в пространстве VH для САБ2, ограничивающие области с вероятностями 0 и 1 соответственно */
            Poly3TA_0, Poly3TA_1, /* многоугольники в пространстве VH для ТА, ограничивающие области с вероятностями 0 и 1 соответственно */
            Poly4VRT_0, Poly4VRT_1, /* многоугольники в пространстве VH для ВРТ, ограничивающие области с вероятностями 0 и 1 соответственно */
            Poly5GZ_0, Poly5GZ_1, /* многоугольники в пространстве VH для ГЗЛА, ограничивающие области с вероятностями 0 и 1 соответственно */
            Poly6KR_0, Poly6KR_1, /* многоугольники в пространстве VH для КР, ограничивающие области с вероятностями 0 и 1 соответственно */
            Poly7ADA_0, Poly7ADA_1, /* многоугольники в пространстве VH для АДА, ограничивающие области с вероятностями 0 и 1 соответственно */
            PolyEPR, /* таблица (ЭПР и Ошибка ЭПР) для 7 классов */
            PolyDP; /* таблица (ДП и Ошибка ДП) для 7 классов */
            // PolyFP; /* таблица (ЧП и Ошибка ЧП) для 7 классов */


    QPointF myPoint, /* заданные координаты (V,H) как точка (x,y) */
            cMyPoly, /* координаты (V,H) центра текущего полигона */
            cPoly1SA, cPoly2SAB2, cPoly3TA, cPoly4VRT, cPoly5GZ, cPoly6KR, cPoly7ADA; /* координаты (V,H) центра соответствующего полигона с вероятностью 1 */
//            (*pCPoly)[5];
    double  mNVO, /* вероятность НВО, сейчас это значение плохо определено */
            /* !!! как определять - загадка !!! */
            tNVO[7], /* столбец вероятностей НВО для каждой строки матриц G,
                    пердает значения НВО в строках из функции для G в функцию для P */
            Sm[7], /* 7 сумм вероятностей в строке, используется для определения tNVO[7] */
            (*pm5x5)[7][7],  /* указатель на матрицу вероятностей 5х5, в основном для передачи функциям */
            mVH_b[7][7], mVH_g[7][7], mVH_p[7][7], gVH[7], /* матрицы  B, G, P и множитель g для перехода от столбцов матрицы _B к _G для VH */
            myEps, /* погрешность 1.0E-6 - одна на всё */
            Phi, /* ракурс, градусы: от -180 до +180 */
            mS_b[7][7], mS_g[7][7], mS_p[7][7], gS[7], /* матрицы  B, G, P и множитель g для перехода от столбцов матрицы _B к _G для ЭПР */
            mEPR, mEPRd,  /* заданные ЭПР и ошибка */
            mDP_b[7][7], mDP_g[7][7], mDP_p[7][7], gDP[7], /* матрицы  B, G, P и множитель g для перехода от столбцов матрицы _B к _G для ДП */
            mDP, mDPd,  /* заданные ДП и ошибка */
//            mFP_b[7][7], mFP_g[7][7], mFP_p[7][7], gFP[7], /* матрицы  B, G, P и множитель g для перехода от столбцов матрицы _B к _G для ЧП */
//            mFP, mFPd,  /* заданные ЧП и ошибка */
            mSP_p[7][7], /* матрица P для СП */
            mSP_1, mSP_2,   /* заданные значения СП (превышение над порогом) */
            // **** Новые ****
            mVHg_Sg_g[7][7], mVHg_Sg_p[7][7],  /* матрицы  G, P по VHg и ЭПРg */
            mVHg_Sg_DPg_g[7][7], mVHg_Sg_DPg_p[7][7], /* матрицы  G, P по VHg, ЭПРg и ДПg  */

            mVHg_Sg_G_SP_g[7][7], mVHg_Sg_G_SP_p[7][7],  /* матрицы  G, P по (VHg + ЭПРg)g и СП */
            mVHg_Sg_P_SP_g[7][7], mVHg_Sg_P_SP_p[7][7], /* матрицы  G, P по (VHg + ЭПРg)p и СП */

            mVHg_Sg_DPg_G_SP_g[7][7], mVHg_Sg_DPg_G_SP_p[7][7],  /* матрицы  G, P по (VHg + ЭПРg)g и СП */
            mVHg_Sg_DPg_P_SP_g[7][7], mVHg_Sg_DPg_P_SP_p[7][7], /* матрицы  G, P по (VHg + ЭПРg)p и СП */

            // **** Старые ***
            mVH_S_g[7][7], mVH_S_p[7][7],  /* матрицы  G, P по VH и ЭПР */
            mVH_DP_g[7][7], mVH_DP_p[7][7],  /* матрицы  G, P по VH и ДП */
            mVH_DP_S_g[7][7], mVH_DP_S_p[7][7],  /* матрицы  G, P по VH и ДП */
            mVH_S_DP_g[7][7], mVH_S_DP_p[7][7], /* матрицы  G, P по VH, ЭПР и ДП */
//            mVH_DP_FP_g[7][7], mVH_DP_FP_p[7][7], /* матрицы  G, P по VH, ДП и ЭПР ПОМЕНЯЛИСЬ МЕСТАМИ МНОЖИТЕЛИ */
            mVH_S_SP_g[7][7], mVH_S_SP_p[7][7], /* матрицы  G, P по VH, ЭПР и СП */
            mVH_S_DP_SP_g[7][7], mVH_S_DP_SP_p[7][7], /* матрицы  G, P по VH, ЭПР, ДП и СП */
            // нах mVHg_DPg_g[7][7], mVHg_DPg_p[7][7],  /* матрицы  G, P по VH и ДП */

            minV, maxV, minH, maxH, minEPR, maxEPR, minDP, maxDP, minPhi, maxPhi, minSP, maxSP;  /*, minFP, maxFP границы диапазонов для ввода без подтверждения */

    QString inFile, /* имя входного файла = argv[1] */
            myFileName, /* хранит полные имена файлов */
            BegName, /* хранит начало имён файлов */
            myDirName, /* полный путь ко входным данным */
            myResText, /* текст результата для вывода в файл результата */
            myParamText,  /* текст входных данных для вывода в файл результата */
            myMatrText;  /* текст матриц для вывода в файл результата */

    QChar   myDelimInNum, /* разделитель целойи дробной части числа для сохранения матриц в файлы (для Excel) */
                    // =QChar(',');
            myDelimBetwNum; /* разделитель чисел в стоке для сохранения матриц в файлы (для Excel) */
                    // =QChar('\t');

    QDir    myInDir, /* полный путь до исполняемого файла - нужен для поиска входных файлов по умолчанию*/
            myOutDir,  /* полный путь до папки для сохранения матриц */
            myOutResDir; /* полный путь до папки для сохранения отчетов */
    int myRowsNum; /* число строк в векторе */
    void initByDefaults(void); /* инициализация всего значениями по умолчанию из полей ввода, файлов */
    void mySetCurDir(void); /* устанавливает текущей папку с исполняемым файлом, сохраняет ее в myInDir и myOutDir; путь ко входным файлам ./data_in/ */
    int myOpenFile2x4read(QString &fileName, QPolygonF &Poly); /* записывает содержимое двухколоночного файла fileName в вектор Poly.
     * Используется для чтения из файла (без интерактивного выбора файла) таблиц ЭПР и ДП. Возвращает число удачно преобразованных строк */
    int myOpenFile4x4read(QString &fileName, QPolygonF &Poly_0, QPolygonF &Poly_1); /* записывает содержимое четырехколоночного файла fileName
     * в два вектора - Poly_0 и Poly_1. Используется для чтения из файла (без интерактивного выбора файла) многоугольников пространства VH,
     * ограничивающих области с вероятностью 0 и 1 соответственно. Возвращает число удачно преобразованных строк */
    int myOpenDirFile2x4read(QString &fileName, QPolygonF &Poly); /* записывает содержимое двухколоночного файла fileName в вектор Poly.
     * Используется для чтения из файла (с интерактивным выбором) файла таблиц ЭПР и ДП. Возвращает число удачно преобразованных строк */
    int myOpenDirFile4x4read(QString &fileName, QPolygonF &Poly_0, QPolygonF &Poly_1); /* записывает содержимое четырехколоночного файла fileName
     * в два вектора - Poly_0 и Poly_1. Используется для чтения из файла (с интерактивным выбором файла) многоугольников пространства VH,
     * ограничивающих области с вероятностью 0 и 1 соответственно. Возвращает число удачно преобразованных строк */
    int myPoly2xToTab(QPolygonF &Poly, int num, QTableWidget *myTab); /* берет num цифр двухколоночного вектора Poly и заполняет таблицу myTab.
     * Возвращает число удачно записанных строк. Используется для таблиц ЭПР и ДП. */
    int myPoly4xToTab(QPolygonF &Poly_0, QPolygonF &Poly_1, int num, QTableWidget *myTab); /* берет num цифр из двух двухколоночных векторов
     * Poly_0 и Poly_1 и заполняет таблицу myTab. В строках - x0, y0, x1, y1.
     * Возвращает число удачно записанных строк. Используется для таблиц ЭПР и ДП. */
    int myChangeTab2Poly(QTableWidget *myTab, QPolygonF &Poly, int row, int column); /* При изменении значения в таблице ЭПР или ДП,
     * запускается обработка сигнала void Widget::on_tableWidget_EPR_cellChanged(int row, int column) или ..._DP_... соответственно,
     * которая задает myTab, Poly и вызывает эту функцию. Новое значение проходит проверку на ошибки (является ли числом и попадает ли в диапазон).
     * возвращает 0 если хорошо и 1 если таблица не определена */
    int myChangeTab4Poly(QTableWidget *myTab, QPolygonF &Poly_0, QPolygonF &Poly_1, int row, int column); /* При изменении значения в таблице VH,
     * запускается обработка сигнала void Widget::on_tableWidget_VH_cellChanged(int row, int column),
     * которая задает myTab, Poly_0, Poly_1 и вызывает эту функцию. Новое значение проходит проверку на ошибки (является ли числом и попадает ли в диапазон).
     * возвращает 0 если хорошо и 1 если таблица не определена */
    bool myCheckNewValue(QLineEdit *line, QString str, double &Val, double myMin, double myMax); // QString("СКОРОСТЬ,СКОРОСТИ")
    /* Проверяет значение параметра Val, введенное в строке line, на "НЕ ЦИФРУ" и на границы диапазона myMin - myMax */
    bool myCheckNewValueTab(QTableWidget *tab, int row, int column, QString str, double &Val, double myMin, double myMax);
    /* Проверяет значение параметра Val, введенное в ячейке [row, column] таблицы tab, на "НЕ ЦИФРУ" и на границы диапазона myMin - myMax */
    int myOpenFile2x4write(QString &fileName, QPolygonF &Poly); /* Записывает многоугольник Poly (ЭПР или ДП) в файл (интерактивно).
     * Имя по умолчанию - fileName. Возвращает число строк */
    int myOpenFile4x4write(QString &fileName, QPolygonF &Poly_0, QPolygonF &Poly_1); /* Записывает многоугольники Poly_0 и Poly_1 (VH) в файл (интерактивно).
     * Имя по умолчанию - fileName. Возвращает число строк */
/*  VH  */
    void myFillMatrVH(void); /* Заполняет матрицу VH_b по площадям пересечений многоугольников с нулевой вероятностью */
    double myPolyArea(QPolygonF &Poly); /* Возвращает площадь многоугольника */
    void setMyPoly(int myPolyNum, QPolygonF &Poly_0, QPolygonF &Poly_1); /* Определяет Poly_0 и Poly_1 по номеру myPolyNum
     * (0 - СА, 1 - ТА, 2 - ВРТ, 3 - ГЗЛА, 4 - КР) */
    int setVHtable(int myPolyNum); /* Отображает таблицу VH по номеру myPolyNum (0 - СА, 1 - ТА, 2 - ВРТ, 3 - ГЗЛА, 4 - КР) */
    void setMyPtab(int myPTabNum); /* Устанавливает указатель pm5x5 на матрицу, которую отобразит функция void setPtable(int myPTabNum) */
    void setPtable(int myPTabNum); /* Вызывает void setMyPtab(int myPTabNum) для получения указателя pm5x5 на матрицу вероятностей.
     * Отображает матрицу в таблице главного окна, выделяет цветом значения */
    void myPointInVH(void); /* Читает поля ввода V и H главного окна. Заполняет значения gVH[i]. Вероятности находит,
     * вызывая функцию double Widget::myPointInVHnum(QPolygonF &Poly_0, QPolygonF &Poly_1, double x, double y)*/
    void myFillMatrVHg(void); /* Заполняет mVH_g[row][column]= gVH[row]*mVH_b[row][column] по стандартному алгоритму . */
    void myFillMatrVHp(void); /* Заполняет mVH_p[row][column]= mVH_b[row][column]/(сумма[row] + НВО[row] ) по стандартному алгоритму . */
//    void showNVO(void);
/*  ЭПР  */
    void myLoadEPR(void); /* Формирует запрос  к функции myOpenFile2x4read(myFileName, PolyEPR)
     * на чтение файла типа .\\data_in\\EPR_L3_00.txt в зависимости от угла и диапазона и запись его в вектор ЭПР */
    void myFillMatrEPR(void); /* По данным PolyEPR строит матрицу mS_b[row][column] */
    void myPointInEPR(void); /* Читает поле ввода ЭПР главного окна. Заполняет значения gS[i]. Вероятности находит,
     * вызывая функцию double Widget::myIntegral( mEPR, mEPRd, PolyEPR[column].x(), PolyEPR[column].y() ) */
    double myGaussFn(double x0, double sigma, double x); /* Возвращает значение Гамма-функции с центром в x0 шириной sigma для значения x */
    double myFunc(double x1, double sigma1, double x2, double sigma2, double x); /* Возвращает значение произведения Гамма-функций
     * или min(Gamma1, Gamma2) для (x1, sigma1) и (x2, sigma2) для значения x */
    double myIntegral(double x1, double sigma1, double x2, double sigma2); /* Возвращает значение интеграла от произведения Гамма-функций
     * или min(Gamma1, Gamma2) для (x1, sigma1) и (x2, sigma2) */
    void myFillMatrEPRg(void); /* Заполняет mS_g[row][column]= gS[row]*mS_b[row][column] по стандартному алгоритму . */
    void myFillMatrEPRp(void); /* Заполняет mS_p[row][column]= mS_b[row][column]/(сумма[row] + НВО[row] ) по стандартному алгоритму . */
    void setEPRtable(void); /* Заполняет таблицу ЭПР */
/*  ДП  */
    void myLoadDP(void); /* Читает из файла .\\data_in\\DP_All.txt пары длина-ширина для всех классов, находит максимальную проекцию вдоль ракурса,
     * для каждой пары в зависимости от угла и записывает среднюю величину и ошибку для каждого класса целей в вектор ДП */
    void myFillMatrDP(void); /* По данным PolyDP строит матрицу mDP_b[row][column] */
    void myPointInDP(void); /* Читает поле ввода ДП главного окна. Заполняет значения gDP[i]. Вероятности находит,
     * вызывая функцию double Widget::myIntegral( PolyDP[row].x(), PolyDP[row].y(), PolyDP[column].x(), PolyDP[column].y() ) */
    void myFillMatrDPg(void); /* Заполняет mDP_g[row][column]= gDP[row]*mDP_b[row][column] по стандартному алгоритму . */
    void myFillMatrDPp(void); /* Заполняет mDP_p[row][column]= mDP_g[row][column]/(сумма[row] + НВО[row] ) по стандартному алгоритму . */
    void setDPtable(void); /* Заполняет таблицу ДП */
/*  ЧП  */
    // void myLoadDP(void); Читаем одновременно с ДП
    /* Читает из файла .\\data_in\\FP_All.txt пары длина-ширина для всех классов, находит максимальную проекцию вдоль ракурса,
     * для каждой пары в зависимости от угла и записывает среднюю величину и ошибку для каждого класса целей в вектор ЧП */
//    void myFillMatrFP(void); /* По данным PolyFP строит матрицу mFP_b[row][column] */
//    void myPointInFP(void); /* Читает поле ввода ЧП главного окна. Заполняет значения gFP[i]. Вероятности находит,
//         * вызывая функцию double Widget::myIntegral( PolyFP[row].x(), PolyFP[row].y(), PolyFP[column].x(), PolyFP[column].y() ) */
//    void myFillMatrFPg(void); /* Заполняет mFP_g[row][column]= gFP[row]*mFP_b[row][column] по стандартному алгоритму . */
//    void myFillMatrFPp(void); /* Заполняет mFP_p[row][column]= mFP_g[row][column]/(сумма[row] + НВО[row] ) по стандартному алгоритму . */
//    void setFPtable(void); /* Заполняет таблицу ЧП */
/*  СП  */
    void myFillMatrSPp(void); /* Заполняет mS_p[row][column] по стандартному алгоритму . */
//    void setSPtable(void);
/*  VH + ЭПР */
    void myFillMatrVH_S_g(void); /* Заполняет mVH_S_g[row][column]= mVH_p[row][column] * mS_p[row][column] по стандартному алгоритму . */
    void myFillMatrVH_S_p(void); /* Заполняет mVH_S_p[row][column]= mVH_S_g[row][column] / сумма[row] по стандартному алгоритму . */
/*  VH + ЭПР + ДП  */
    void myFillMatrVH_S_DP_g(void); /* Заполняет mVH_S_DP_g[row][column]= mVH_S_p[row][column] * mDP_p[row][column] по стандартному алгоритму . */
    void myFillMatrVH_S_DP_p(void); /* Заполняет mVH_S_DP_p[row][column]= mVH_S_DP_g[row][column] / сумма[row] по стандартному алгоритму . */
/*  VH + ДП */
    void myFillMatrVH_DP_g(void); /* Заполняет mVH_DP_g[row][column]= mVH_p[row][column] * mDP_p[row][column] по стандартному алгоритму . */
    void myFillMatrVH_DP_p(void); /* Заполняет mVH_DP_p[row][column]= mVH_DP_g[row][column] / сумма[row] по стандартному алгоритму . */
/*  VH + ДП + ЧП */
//    void myFillMatrVH_DP_FP_g();
//    void myFillMatrVH_DP_FP_p();
/*  VH + ДП + ЭПР */
    void myFillMatrVH_DP_S_g(void); /* Заполняет mVH_DP_S_g[row][column]= mVH_DP_p[row][column] * mS_p[row][column] по стандартному алгоритму . */
    void myFillMatrVH_DP_S_p(void); /* Заполняет mVH_DP_S_p[row][column]= mVH_DP_S_g[row][column] / сумма[row] по стандартному алгоритму . */
/*  VH + ЭПР + СП  */
    void myFillMatrVH_S_SP_g(void); /* Заполняет mVH_S_SP_g[row][column]= mVH_S_p[row][column] * mSP_p[row][column] по стандартному алгоритму . */
    void myFillMatrVH_S_SP_p(void); /* Заполняет mVH_S_SP_p[row][column]= mVH_S_SP_g[row][column] / сумма[row] по стандартному алгоритму . */
/*  VH + ЭПР + ДП + СП  */
    void myFillMatrVH_S_DP_SP_g(void); /* Заполняет mVH_S_DP_SP_g[row][column]= mVH_S_DP_p[row][column] * mSP_p[row][column] по стандартному алгоритму . */
    void myFillMatrVH_S_DP_SP_p(void); /* Заполняет mVH_S_DP_SP_p[row][column]= mVH_S_DP_SP_g[row][column] / сумма[row] по стандартному алгоритму . */

    void myReCalcAll(void); /* Выполняет запуск последовательного пересчета всех матриц и векторов. Запускается после изменения входных данных */

    void myOpenFile5x4write(void); /* Записать в файл матрицу 5х5, по указателю (*pm5x5)  */
    void myShowResultDialog(bool showRes); /* Новое Показывает окно с автоматически определенным классом цели */
    void myShowResultDialogOldK(bool showRes); /* Новое Показывает окно с автоматически определенным классом цели */

//    void myShowResultDialogOld(void); /* старое - скопировано, работает. Показывает окно с автоматически определенным классом цели */
    double myPointInVHnum(QPolygonF &Poly_0, QPolygonF &Poly_1, double x, double y); /*  Проверяет, лежит ли точка
         * внутри Poly_1 - возвращает 1.0, вне Poly_0 - возвращает 0.0, в полосе между Poly_0 и Poly_1  - проводит прямую через точку и
         * центр Poly_1 и выдает удаленность от границы Poly_1 (от 1.0 до 0.0)*/
    double Reley(double H); /* Функция Релея - множитель к вероятности VH, зависящий от высоты */
    double myPolyIntegral(int P1, int P2); /* Интеграл по VH с учетом вероятностей для "усеченных пирамид"
                                            * (т.е. пар векторов Poly_0 и Poly_1) P1 и P2 */
//    void myShowWarningDialog(QString &text);
    //    void myShowErrorDialog(QString &text);
    void myFillMatrVHg_Sg_g();
    void myFillMatrVHg_Sg_p();
    void myFillMatrVHg_DPg_g();
    void myFillMatrVHg_DPg_p();
    void myFillMatrVHg_Sg_DPg_g();
    void myFillMatrVHg_Sg_DPg_p();

    /* все новые матрицы G и P в комбинации с SP */
    void myFillMatrVHg_Sg_G_SP_g();
    void myFillMatrVHg_Sg_G_SP_p();
    void myFillMatrVHg_Sg_P_SP_g();
    void myFillMatrVHg_Sg_P_SP_p();
    void myFillMatrVHg_Sg_DPg_G_SP_g();
    void myFillMatrVHg_Sg_DPg_G_SP_p();
    void myFillMatrVHg_Sg_DPg_P_SP_g();
    void myFillMatrVHg_Sg_DPg_P_SP_p();
    /*          */
    void myMsg(const QString inText);
    void myOpenDirFileOutData(QString &fileName);
    void SaveMatr2Res(void);
    void save1Matr2res(double p[][7]);
    void myMatr2res(bool isChe, double p[][7], QString myMatrName);
    void myFindKC0(bool showRes);  /* Автоматически определяет класс цели по алгоритму 0 */
    QString myNum2Class(int myClassNum); /* По номеру(0-6) выдает название класса(САМ СА - АДА) */
};

#endif // WIDGET_H
