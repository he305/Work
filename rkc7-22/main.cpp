#include "widget.h"
// #include "myplot.h"
#include <iostream>  // in & out
#include <QApplication>

int main(int argc, char *argv[])
{
//    std::cout << "rkc7-XXXX.exe input_parameters_file.in\n" << std::endl;
//    if( argc < 2 )
//    {
//        if( !QFile::exists("default.in") )
//        {
////            std::cout << "rkc7-XXXX.exe input_parameters_file.in\n"
////                      << "if exist input_parameters_file.in or\n"
////                      << "rkc7-XXXX.exe\n"
////                      << "to use default.in parameters file\n"
////                      << "file default.in should be in the working directory\n"
////                      << "and contains the following strings (digits are for example):\n"
////                      << "fi 0 \/\/ Ракурс\n"
////                      << "V 600 \/\/ скорость км/ч\n"
////                      << "H 5.5 \/\/ высота км\n"

////                      << "H 5.5 \/\/ высота км\n"
////                      << "H 5.5 \/\/ высота км\n"
////                      << "H 5.5 \/\/ высота км\n"
////                      << "H 5.5 \/\/ высота км\n"
////                      << "H 5.5 \/\/ высота км\n"

////                      << std::endl;
//        } else
//        {
//            argc = 2 ;
//            argv[1] = "default.in" ;
//        }
//    } else if( !QFile::exists( argv[1]) )
//    {
////        std::cout << "rkc7-XXXX.exe input_parameters_file.in\n"
////                  << "if exist input_parameters_file.in or\n"
////                  << "rkc7-XXXX.exe\n"
////                  << "to use default.in parameters file\n"
////                  << "file default.in should be in the working directory\n"
////                  << "and contains the following strings (digits are for example):\n"
////                  << "fi 0 \/\/ Ракурс\n"
////                  << "V 600 \/\/ скорость км/ч\n"
////                  << "H 5.5 \/\/ высота км\n"

////// !!                  << "H 5.5 // высота км\n"
////                  << "H 5.5 \/\/ высота км\n"
////                  << "H 5.5 \/\/ высота км\n"
////                  << "H 5.5 \/\/ высота км\n"
////                  << "H 5.5 \/\/ высота км\n"

////                  << std::endl;
//    }

    // QApplication::setAttribute(Qt::AA_Use96Dpi);
    QApplication a(argc, argv);
    // QApplication::setAttribute(Qt::AA_Use96Dpi);

//    QFont font = qApp->font();
//    font.setPixelSize(12);
//    qApp->setFont(font);

    Widget w;
//    w.setFont(font);
    w.show();

    return a.exec();
}
