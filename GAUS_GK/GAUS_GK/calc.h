#ifndef CALC_H
#define CALC_H

/*Функция пересчета геодезических координат в гаусса крюгера, м*/
int gauss(double b,double l, double h, double *x,double *y, double *z);
/* b - широта, l - долгота, h  - высота над уровнем моря
   *x - координата X в ГК, *y - координата Y в ГК, *z - высота над уровнем моря
*/

// Расчет геодезичесиех координат по коордианатам в проекции ГК, в градусах
void Gauss_Geo(double x, double y, double Z, double *B, double *L, double *h);

/* Расчет горизонтальной дальности, азимута и угла места цели
 * относительно Начала Координат (камеры)
 * На входе координаты камеры(x2,y2,Z2), координаты ориентира (x1,y1,Z1) в проекции Гаусса Крюгера.
 * На выходе дальность, азимут и угол места с учетом схождения меридианаов и
 * кривизны земли */
int CalcDist(double x1, double y1, double Z1,
             double x2, double y2, double Z2,
             double *D, double *P, double *eps);


// Перевод сферических координат в МПТСКи
void CalcMPTSKi(double R, double B, double E,
               double *x, double *y, double *z);

// Расчет координат камеры

void CalcGEOKAM(double Xprl, double Yprl, double Zprl, double Bprl,
                double x_kam, double y_kam, double z_kam,
                double *X_KAM, double *Y_KAM, double *Z_KAM,
                double *B_kam, double *L_kam, double *H_kam);

void FormationTagetOPU(double ceilX, double ceilY, double ceilZ, // Координаты целеуказания, м
                       double BopuCur,                           // Текущий  азимут ОПУ, радианы
                       double velX, double velY,                 // Скорости в горизонтальной плоскости, м/с
                       double *Bopu, double *Eopu, double *dT);  // Требуемй азимут и угол места ОПУ, радианы, треб время поворота

// Пересчет оптических коордиант из пикселей в в азимут и угол места

void formationResult  (double Bos, double Eos, double Gkam,     // Азимут и угол места оптическо оси и крен кадра
                       double PixInB, double PixInE,            // Количество пикселей в радиане по горизонтали и по вертикали
                       double Bkam, double Ekam, double Tintegr,// Углы поля зрения камеры по горизонтали и по вертикали, время интеграции кадра
                       double Hoi, double Voi, double Toi,      // Координаты полученные по кадру по вертикали и горизонтали и время из кадра
                       double *Bz, double *Ez, double *Tz);      // Азимут и угол места ОИ им время замера


#endif // CALC_H
