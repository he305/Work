#include "calc.h"
#include <iostream>
using namespace std ;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <QDebug>

/*Функция пересчета геодезических координат в гаусса крюгера, м*/
int gauss(double b,double l, double h, double *x,double *y, double *z)
/* b - широта, l - долгота, h  - высота над уровнем моря
   *x - координата X в ГК, *y - координата Y в ГК, *z - высота над уровнем моря
*/
{
    double s0,c0,a0,a3,a4,a5,r1,nd,r,al,lm,lm2,cc0; //

double pi=3.14159265358979323846,kd=9.549296585513721;

int nzone =int(l/6)+1;

b = b*pi/180;
l = l*pi/180;

if(b > pi/2 || b < -pi/2) return 2;// Широта вне существующего диапазона

if(l > pi+0.01 || l < -pi-0.01) return 3;// Долгота вне существующего диапазона

s0=sin(b);

c0=cos(b);

cc0=c0*c0;

a0=(0.7*cc0-0.1353e+3)*cc0+(0.321404e+5);

a3=(0.11e-2*cc0+0.3333)*cc0-0.1667;

a4=(0.25*cc0)-0.42e-1;

a5=(0.2*cc0-0.17)*cc0;

r1=sqrt(1.+0.673853e-2*cc0);

nd=(0.63996989e+7)/r1;

r=l*kd+1.;

al=r-nzone;

lm=(al-0.5)/kd;

if(lm>pi)    lm=lm-2.*pi;

if(lm<(-pi)) lm=lm+2.*pi;

lm2=lm*lm;

*x=((a4*lm2+0.5)*nd*lm2-a0)*(s0*c0)+0.63675585e+7*b;

*y=((a5*lm2+a3)*lm2+1.)*(lm*nd*c0);

*y=*y+(10.*nzone+5.)*0.1e+6;

*z = h;

return 0;

}

// Расчет геодезичесиех координат по коордианатам в проекции ГК, в градусах
void Gauss_Geo(double x, double y, double Z, double *B, double *L, double *h)
{
  double alpha, n, L0;
  double beta, cos_beta, sin_beta, cos_2beta;
  double Bx, cos_Bx, sin_Bx, cos_2Bx;
  double z, z2, b, a, b2, b4, b3, b5;
  double pi=3.14159265358979323846;
// e=sqrt(a*a-b*b)/a;  // эксцентриситет
 a=6378245;
 b=6356863;       // малая полуось
 double _e=sqrt(a*a-b*b)/b; // второй эксцентриситет
 double _e2=_e*_e;          // квадрат второго эксцентриситета

  alpha = y*0.000001;
  n = floor(alpha);

  alpha = alpha - n;

  L0 = (n - 0.5)/9.5492966;

  beta = x/6367558.5;

  cos_beta = cos(beta);
  sin_beta = sin(beta);
  cos_2beta = cos_beta*cos_beta;

  Bx = (502217.0 + (2936.0 + 24.0*cos_2beta)*cos_2beta)*
    sin_beta*cos_beta*1.0e-8 + beta;

  cos_Bx = cos(Bx);
  sin_Bx = sin(Bx);
  cos_2Bx = cos_Bx*cos_Bx;

  z = (alpha - 0.5)*sqrt(1.0 + _e2*cos_2Bx)/(6.3996989*cos_Bx);
  z2 = z*z;

  b2 = (0.00337*cos_2Bx + 0.5)*sin_Bx*cos_Bx;
  b4 = 0.162*cos_2Bx + 0.25;
  b3 = (0.0011*cos_2Bx - 0.1667)*cos_2Bx + 0.3333;
  b5 = 0.17*cos_2Bx - 0.2;
  *B = ((b4*z2 - 1.0)*b2*z2 + Bx)*180/pi;
  *L = ((1.0 - (b5*z2 + b3)*z2)*z + L0)*180/pi;
  *h = Z;
 }

//---------------------------------------------------------------------------
/* Расчет горизонтальной дальности, азимута и угла места цели
 * относительно Начала Координат (камеры)
 * На входе координаты камеры(x2,y2,Z2), координаты ориентира (x1,y1,Z1) в проекции Гаусса Крюгера.
 * На выходе дальность, азимут и угол места с учетом схождения меридианаов и
 * кривизны земли */
int CalcDist(double x1, double y1, double Z1,
             double x2, double y2, double Z2,
             double *D, double *P, double *eps)
{
     double pi=3.14159265358979323846;
     double dx1,dy1,dx2,dy2;
     float n1,l0,bet,sbet,cbet,r1,bx,sbx,cbx,r2,r3,z,b2,b4,b3,b5,b,l,c1,z1,zz,rr1,rr2; //al,
     float s0,c0,a0,a3,a4,a5,r1g,nd,rg,alg,lm,lm2,cc0,xn,yn;
     double kd=9.549296585513721;
     int m1,m2,dn;
     double B_Kam, L_Kam, h_Kam, Qcx, alpha, n, L0;; // Переменные для расчета поправки к азимуту на схождение меридианов

     /*Расчет поправки к азимуту, обусловленной схождением меридианов*/

     // Расчет геодезических кордиант камеры по коордианатам ГК, в градусах
     Gauss_Geo(x2, y2, Z2, &B_Kam, &L_Kam, &h_Kam);
     // Расчет LO зоны, в радианах
     alpha = y2*0.000001;
     n = floor(alpha);
     alpha = alpha - n;
     L0 = (n - 0.5)/9.5492966;
     // Расчет поправки к азимуту полученному по координатам ГК, в радианах
     if (89.99<=B_Kam&&B_Kam<90.01) Qcx = 0;
     else  Qcx =2*atan(sin(B_Kam*pi/180)*tan((L_Kam*pi/180-L0)/2));
     //расчет смещения первой точки относительно второй
     dx1=0;dy1=0;
     rr1=y1*(0.1e-5);
     m1=(int)rr1;
     rr2=y2*(0.1e-5);
     m2=(int)rr2;
     if(m1==m2)
     { dx2=x1-x2+dx1; dy2=y1-y2+dy1;
       goto vix;
     }
      if(m1 > 60 || m1 < 1) {printf("error");return 1;}
     if(m2 > 60 || m2 < 1) {printf("error");return 1;}
     if(m2 == 1 && (m1 > 2 || m1 < 60)) {printf("error");return 1;}
     if(m2 ==60 && (m1 > 1 || m1 < 59)) {printf("error");return 1;}
     dn=abs(m2-m1);
     if(dn!=1 && dn!=59) {printf("error");return 1;}
     n1=m1;
     l0=(n1-0.5)/kd;
     bet=(x1+dx1)/(0.63675585e+7);
     sbet=sin(bet);
     cbet=cos(bet);
     c1=cbet*cbet;
     r1=(0.502217e+6)+((0.2936e+4)+(0.24e+2)*c1)*c1;
     bx=(r1*sbet*cbet*(0.1e-7))+bet;
     sbx=sin(bx);
     cbx=cos(bx);
     z1=cbx*cbx;
     r2=((0.673853e-2)*z1)+1.;
     r3=sqrt(r2);
     z=(y1+dy1-(10.*m1+5.)*1.e+5)*1.e-6*r3/(6.3996989*cbx);
     //printf("z=%f\n",z);
     b2=((0.337e-2)*z1+0.5)*sbx*cbx;
     b4=(0.162*z1)+0.25;
     b3=((0.11e-2)*z1-0.1667)*z1+0.3333;
     b5=(0.17)*z1-0.2;
     zz=z*z;
     b=(b4*zz-1.)*b2*zz+bx;
     l=(1.-(b5*zz+b3)*zz)*z;
     l=l+l0;
     s0=sin(b);
     c0=cos(b);
     cc0=c0*c0;
     a0=(0.7*cc0-0.1353e+3)*cc0+(0.321404e+5);
     a3=(0.11e-2*cc0+0.3333)*cc0-0.1667;
     a4=(0.25*cc0)-0.42e-1;
     a5=(0.2*cc0-0.17)*cc0;
     r1g=sqrt(1.+0.673853e-2*cc0);
     nd=(0.63996989e+7)/r1g;
     rg=l*kd+1.;
     //printf("dx\n");

     alg=rg-m2;
     lm=(alg-0.5)/kd;
     if(lm>pi)    lm=lm-2.*pi;
     if(lm<(-pi)) lm=lm+2.*pi;
     lm2=lm*lm;
     xn=((a4*lm2+0.5)*nd*lm2-a0)*(s0*c0)+0.63675585e+7*b;
     //printf("dx\n");

     yn=((a5*lm2+a3)*lm2+1.)*(lm*nd*c0);
     //printf("xn=%f x2=%f\n",xn,x2);

     dx2=xn-x2;
     //printf("dx\n");

     dy2=yn-y2+(10.*m2+5.)*0.1e+6;
     vix: //printf("dx2=%f dy2=%f\n",dx2,dy2);

     /* Расчет азимута без поправки на схождение меридианаов, в радианах */
     if ((dx2 > 0) && (dy2 > 0))
          bet = atan(dy2/dx2);
     else
     if ((dx2 > 0) && (dy2 < 0))
          bet = 2*pi + atan(dy2/dx2);
     else
     if ((dx2 < 0) && (dy2 != 0))
         bet = pi + atan(dy2/dx2);
     else
     if ((dx2 > 0) && (dy2 == 0))
          bet = 0;
     else
     if ((dx2 < 0) && (dy2 == 0))
          bet = pi;
     else
     if ((dx2 == 0) && (dy2 > 0))
          bet = pi/2;
     else
     if ((dx2 == 0) && (dy2 < 0))
          bet = 3*pi/2;
   /* Расчет азимута с поправкой на схождение меридианаов, в радианах */
     if(bet+Qcx>=2*pi)
        {
          bet=2*pi-bet-Qcx;
        }
     else if(bet+Qcx<0)
       bet = 2*pi+bet+Qcx;
     else bet = bet+Qcx;

     *P=bet*180/pi;
     *D=sqrt(dx2*dx2+dy2*dy2);
     if (*D == 0)
        {
         if(Z1>Z2){*eps = 90 ; return 0;}
         if(Z2>Z1){*eps = -90 ; return 0;}
         if(Z2==Z1){*eps = 0 ; return 0;}
        }
     *eps = atan((Z1-Z2-6366707.1*(1-cos(*D/6366707.1)))/ *D)*180/pi;
     return 0;
}

// Перевод сферических координат в МПТСКи
void CalcMPTSKi(double R, double B, double E,
               double *x, double *y, double *z)
{
    double pi=3.14159265358979323846;
    *x = R*cos(B*pi/180);
    *y = R*sin(B*pi/180);
    *z = R*tan(E*pi/180);
}

// Расчет координат камеры

void CalcGEOKAM(double Xprl, double Yprl, double Zprl, double Bprl,
                double x_kam, double y_kam, double z_kam,
                double *X_KAM, double *Y_KAM, double *Z_KAM,
                double *B_kam, double *L_kam, double *H_kam)
{
    double a_prl, Qcx, Yprl_sm; // Азимут ПРЛ в МПТСКо, поправка для пеервода из МПТСКи в МПТСКо,Yprl без номера зоны (ст. разряда)
    double pi=3.14159265358979323846;
    // Вычитание номера зона из коордианты Y
    Yprl_sm = Yprl - int(Yprl*0.000001)*1000000;
    // Поправка к азиумту Bprl для перевода в МПТСКо из МПТСКи, радианы
    Qcx = 2*asin((Yprl_sm-500000)/2/(10002137.5-Xprl));
    a_prl = Bprl*pi/180 - Qcx;
     // Пересчет координат камеры из системы ПРЛ в систему на местности
        *X_KAM=x_kam * cos(a_prl) + y_kam * sin(a_prl)+Xprl;
        *Y_KAM=y_kam * cos(a_prl) - x_kam * sin(a_prl)+Yprl;
        *Z_KAM=Zprl+z_kam;
    // Расчет геодезических коордиант камеры
      Gauss_Geo(*X_KAM, *Y_KAM, *Z_KAM, B_kam, L_kam, H_kam);
}


// Пересчет прямоугольных координат целеуказания в азимут и угол места для ОПУ

void FormationTagetOPU(double ceilX, double ceilY, double ceilZ, // Координаты целеуказания, м
                                        double BopuCur,                           // Текущий  азимут ОПУ, радианы
                                        double velX, double velY,                 // Скорости в горизонтальной плоскости, м/с
                                        double *Bopu, double *Eopu, double *dT)   // Требуемй азимут и угол места ОПУ, радианы, требуемое время для поворота на подвижную цель
{
    double Rc, Bc, dt;         // Дальноcть до цели (для расчета угла места) , азимут на цель, время поворота ОПУ на цель без учета сксортви цели
    double Vx, Vy;             // Координаты вектора скорости цели в МПТСК, где направлении оси X совпадает с напраелением от ОПРУ на цель
    double ModVt, Vt, Wc;      // Модуль скорости, тангенциальнапя и угловая скороть цели
    double Wopu = 40*M_PI/180; // Модуль скорости движения ОПУ по азиумту в устоявшемся режиме, рад/с
    double dBcOpu, dBopu;      // Угол между азимутом на цель и текущим азимутом ОПУ, угол между текщим и требуемым азимутом ОПУ, радианы


    /* Расчет азимута цели в радианах */
    if ((ceilX > 0) && (ceilY > 0))
         Bc = atan((ceilY )/(ceilX));
    else
    if ((ceilX > 0) && (ceilY < 0))
         Bc = 2*M_PI +
                      atan((ceilY )/(ceilX));
    else
    if ((ceilX < 0) && (ceilY != 0))
        Bc = M_PI +
                     atan((ceilY )/(ceilX));
    else
    if ((ceilX > 0) && (ceilY == 0))
         Bc = 0;
    else
    if ((ceilX < 0) && (ceilY == 0))
         Bc = M_PI;
    else
    if ((ceilX == 0) && (ceilY > 0))
        Bc = M_PI/2;
    else
    if ((ceilX == 0) && (ceilY < 0))
         Bc = 3*M_PI/2;

    /* Расчет угла места в радианах */
    /*Расчет дальности до цели (для расчета угла места)*/
    Rc = sqrt(ceilX * ceilX + ceilY * ceilY + ceilZ * ceilZ);
    /*Собсвенно расчет угла места*/
    if (Rc == 0)
    {
        *Eopu = M_PI/2;
    }
    else
    *Eopu = asin(ceilZ/Rc);

    /* Рассчитывается угол между текущим азимутом ОПУ и азимутом Цели в диапазоне +- пи*/
    if (Bc - BopuCur > M_PI)
        dBcOpu = Bc - BopuCur - 2* M_PI;
    else
    if ((Bc - BopuCur >= -M_PI) && (Bc - BopuCur <= M_PI))
        dBcOpu = Bc - BopuCur;
    else
    if (Bc - BopuCur < -M_PI)
        dBcOpu = Bc - BopuCur + 2*M_PI;
    
    /* Рассчитывается угловая скорость поворота ОПУ в зависимости от модуля угла между аз. на цель и аз. на ОПУ dBcOpu*/
   /// Wopu = ... Не забыть поставить формулу зависисмости средней угловой скорости ОПУ от угла поворота dBcOpu
    /*  Рассчитывается время поворота ОПУ на положение цели в целеуказании */
    dt = fabs(dBcOpu)/Wopu;
    ModVt = sqrt(velX*velX + velY*velY);
    if (ModVt != 0)
    {
        // Пересчет координат вектора скорости цели в МПТСК, где X совпадает с направлением от ОПУ на цель
           Vx= velX * cos(Bc) + velY * sin(Bc);
           Vy= velY * cos(Bc) - velX * sin(Bc);
        /* Рассчитывается тангенциальная скорость ВО с позиции камеры */
           Vt = Vy;
        /* Рассчитывается угловая скорость движения цели в горизонтальной плоскости */
           Wc = Vt/(sqrt(ceilX * ceilX + ceilY * ceilY)+Vx*dt); // В знаменателе дальность в момент встречи оси ОПУ с целью с учетом движения цели
    } else Wc = 0; // Конец блока расчета угловой скорости цели

  /* Рассчитывается угол между текущим и требуемым азимутом ОПУ*/
    if (fabs(dBcOpu) < 0.3*M_PI/180) dBopu = dBcOpu; // чтобы не получился вдруг 0 в знаменателе дальнейших формул
    else
    if ((dBcOpu > 0) && (Wc >= 0))
        dBopu = dBcOpu/(1-Wc/Wopu);
    else
    if ((dBcOpu < 0) && (Wc <= 0))
       dBopu = dBcOpu/(1+Wc/Wopu);
    else
    if (((dBcOpu > 0) && (Wc <= 0)) || ((dBcOpu < 0) && (Wc >= 0)))
       dBopu = dBcOpu*Wopu/(fabs(Wc)+Wopu);
    /* Рассчитывается требуемый азимут ОПУ*/
    double bOPU = BopuCur + dBopu;
    if (bOPU >= 2*M_PI)
    {
        *Bopu = bOPU - 2*M_PI;
    }
    else if (bOPU < 0)
    {
       *Bopu =  bOPU + 2*M_PI;
    }
    else *Bopu = bOPU;

   /* Расчет времени необходимого для повророта ОПУ*/

    *dT = fabs(dBopu)/Wopu;
}

// Пересчет оптических коордиант из пикселей в в азимут и угол места

void formationResult  (double Bos, double Eos, double Gkam,     // Азимут и угол места оптическо оси и крен кадра
                                 double PixInB, double PixInE,            // Количество пикселей в радиане по горизонтали и по вертикали
                                 double Bkam, double Ekam, double Tintegr,// Углы поля зрения камеры по горизонтали и по вертикали, время интеграции кадра
                                 double Hoi , double Voi, double Toi,      // Координаты полученные по кадру по вертикали и горизонтали и время из кадра
                                 double *Bz, double *Ez, double *Tz)      // Азимут и угол места ОИ им время замера
{
    int par;
    double Bohk, Eohk, Boh, Eoh;
    /* Горизонтальный и вертикальный углы положения ВО          */
    /* относительно положения оптической оси и горизонта камеры */
    Bohk = Hoi/PixInB - Bkam/2;
    Eohk = Ekam/2 - Voi/PixInE;
    /* Горизонтальный и вертикальный углы положения ВО относительно */
    /* положения оптической оси камеры и истиного горизонта         */
//    Boh = Bohk*cos(Gkam) + Eohk*sin(Gkam);
//    Eoh = Eohk*cos(Gkam) - Bohk*sin(Gkam);
    Boh = Bohk;
    Eoh = Eohk;
    /* Расчет времени привязки оценок ОИ */
      *Tz = Toi - Tintegr;

    /* Расчет азимута ВО относительно БОЭС в градусах */
        if (Boh + Bos > 2*M_PI) par = 1;
        else par = 0;
        *Bz = 180/M_PI*(Boh + Bos) - 360*par;
        /* Расчет угла места ВО относительно БОЭС, в градусах */
        *Ez = 180/M_PI*(Eos + Eoh);

}




