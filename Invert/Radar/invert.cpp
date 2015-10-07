#include "Invert.h"
#include "typematrix.h"
#include "Log.h"
#include <iostream>
#include <math.h>
#include <QString>
#include <QDebug>

using namespace std;

Invert::Invert(int size){

    ///Допустимая погрешность
    EPS = 1E-10;
    //EPS = 0;
    N = size;

    /*---------------------Loger------------------------*/
    Log::getInstanse()->write("Размер: ");
    Log::getInstanse()->writeln(N);
    Log::getInstanse()->write("Погрешность: ");
    Log::getInstanse()->writeln(EPS);
    /*--------------------------------------------------*/
}

double **Invert::invert(double **matrix){

    double norma = getNorma(matrix);
    cout << "Norma: " << norma << endl;
    double tr = getTr(matrix);
    cout << "Tr: " << tr << endl;
    /////////////////////////////

    clock_t start = clock();
    inverted = pseudoInverse(matrix);
    str = "Псевдообратная матрица";

    Log::getInstanse()->write("Время на обращение: ");
    Log::getInstanse()->writeln(clock()-start);

    double **temp = getMult(matrix, inverted);
    temp = getMult(temp, matrix);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            Log::getInstanse()->write(temp[i][j]);
            Log::getInstanse()->write("\t");
        }
        Log::getInstanse()->write("\n");
    }

    for (int i = 0; i < N; i++){
        delete[] temp[i];
    }
    delete[] temp;

    return inverted;
}

/*!
 * \brief Получение обратной матрицы.
 * \param[in] matrix Матрица, которую нужно обратить.
 * \param[in] N Размер матрицы.
 * \return Обратная матрица.
 */

double** Invert::invertMatrix(double **matrix){

    //При определителе = 0, обратной матрицы не существует
    double det = getDet(matrix, N);

    double **inv = new double *[N];
    double **soyuz = new double *[N];
    for (int i = 0; i < N; i++){
        soyuz[i] = new double[N];
        inv[i] = new double[N];
    }

    //Инициализация матрицы алгебраических дополнений

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            soyuz[i][j] = pow(-1, i + j) * getMinor(matrix, N - 1, i, j);
        }
    }

    //Инвертирование матрицы и умножение элементов на 1/det
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            inv[i][j] = soyuz[j][i] * (1/(double)det);
        }
    }

    for (int i = 0; i < N; i++)
        delete[] soyuz[i];
    delete[] soyuz;

    soyuz = nullptr;

    return inv;
}


/*!
 * \brief Функция используется для вычисления определителя.
 *
 * Принцип работы: вычисление производится путём метода Крамера.
 * Матрица делится на минорные вплоть до матрицы 1х1.
 *
 * \param[in] matrix Матрица, определитель которой требуется получить double**.
 * \param[in] N  Размер матрицы int.
 *
 * \param[out] det Определитель матрицы double.
 *
 * Медленная скорость работы - время работы увеличивается экспоненциально с увеличением
 *                             размера матрицы.
 */

double Invert::getDet(double **matrix, int size){

    /*
        Определитель находится методом разложения по первой строке, деление
        на минорные матрицы происходит вплоть до матрицы 1х1
    */

    double det = 0;

    if (size == 1){
        return **matrix;
    }
    else{
        //Цикл по первой строке
        for (int i = 0; i < size; i++){
            //Инициализация минорной матрицы N-1 размера
            double **minor = new double *[size-1];
            for (int j = 0; j < size-1; j++){
                minor[j] = new double[size-1];
            }

            //Определение минорной матрицы для каждого элемента первой строки
            int kj = 0;
            for (int j = 1; j < size; j++){
                for (int k = 0, kk = 0; k < size; k++){
                    if (k == i) continue;
                    minor[kj][kk] = matrix[j][k];
                    kk++;
                }
                kj++;
            }

            //Рекурсия вплоть до матрицы 1х1
            if (i % 2)
                det -= matrix[0][i] * getDet(minor, size - 1);
            else
                det += matrix[0][i] * getDet(minor, size - 1);


            for (int i = 0; i < size - 1; i++){
                delete[] minor[i];
            }
            delete[] minor;
        }
        return det;
    }
}

/*!
 * Функция используется для получения алгебраического дополнения
 * выбранного элемента путём вычисления определителя минорной матрицы этого
 * элемента, используя функцию Invert::getMinor(...);
 *
 * @param:
 *          1. double **matrix: входная начальная матрица.
 *          2. int N: размер матрицы.
 *          3. int trwI: строка выбранного элемента.
 *          4. int trwJ: столбец выбранногоо элемента.
 *
 *@return:
 *          double: определитель матрицы.
 */

double Invert::getMinor(double **matrix, int size, int trwI, int trwJ){
    double det = 0;
    double **minor = new double *[size];
    for (int i = 0; i < size; i++)
        minor[i] = new double[size];

    int ki = 0;
    for (int i = 0; i < size + 1; i++){
        if (i == trwI) continue;
        for (int j = 0, kj = 0; j < size + 1; j++){
            if (j == trwJ) continue;
            minor[ki][kj] = matrix[i][j];
            kj++;
        }
        ki++;
    }

    det = getDet(minor, size);

    for (int i = 0; i < size; i++)
        delete[] minor[i];
    delete[] minor;
    minor = nullptr;

    return det;
}

/*!
 * Функция возвращает псевдообратную матрицу Мура-Пенроуза.
 * Формула: A+ = lim(aE + Ат*A)^-1 * Aт
 *               a->0
 *
 * Порядок решения:
 * 1. Инициализация единичной матрицы и умножение её на число,
 *    близкое к нулю.
 * 2. Нахождение транспонированной матрицы от начальной, их умножение
 *    и прибавление к ней единичной матрицы.
 * 3. Нахождение обратной матрицы от полученной матрицы.
 * 4. Умножение получившейся матрицы на ранее полученную
 *    транспонированную матрицу.
 *
 * @param
 *          double **matrix: матрица, псевдообратную матрицу которой нужно найти.
 *          int N: размер матрицы.
 * @return
 *          double **: псевдообратная матрица.
 */

double** Invert::pseudoInverse(double **matrix){
    double **edin = new double *[N];
    double **pseudo = new double *[N];
    for (int i = 0; i < N; i++){
        edin[i] = new double[N];
        pseudo[i] = new double[N];
        for (int j = 0; j < N; j++){
            if (i == j)
                edin[i][j] = EPS;
            else
                edin[i][j] = 0;
        }
    }

    double **trans = getTransp(matrix);
    pseudo = getMult(trans, matrix);

    for(int i=0; i < N; i++){
        for(int j=0; j < N; j++){
            pseudo[i][j] += edin[i][j];
        }
    }

    double **temp = shultsMethod(pseudo);

    pseudo = getMult(temp, trans);

    for (int i = 0; i < N; i++){
        delete[] edin[i];
        delete[] trans[i];
        delete[] temp[i];
    }

    delete[] edin;
    delete[] trans;
    delete[] temp;

    return pseudo;
}

/*!
 * Функция возвращает транспонированную матрицу.
 *
 * @param
 *          double **matrix: матрица, которую необходимо транспонировать.
 *          int N: размер матрицы.
 *
 * @return
 *          double **: транспонированная матрица.
 */

double **Invert::getTransp(double **matrix){
    double **trans = new double *[N];
    for (int i = 0; i < N; i++){
        trans[i] = new double[N];
        for (int j = 0; j < N; j++){
            trans[i][j] = matrix[j][i];
        }
    }
    return trans;
}

/**
 * Функция возвращает произведение двух матриц.
 *
 * @param
 *          double **matrix1: левая матрица.
 *          double **matrix2: правая матрица.
 *          int N: размер матрицы.
 *
 * @return
 *          double **: результат произведения.
 */

double **Invert::getMult(double **matrix1, double** matrix2){
    double **mult = new double *[N];

    for(int i=0; i < N; i++){
        mult[i] = new double[N];
        for(int j=0; j < N; j++){
            mult[i][j]=0;
            for(int k=0; k < N; k++){
                mult[i][j]+=matrix1[i][k]*matrix2[k][j];
            }
            if (fabs(mult[i][j]) < EPS)
                mult[i][j] = 0;
        }
    }

    return mult;
}

double **Invert::shultsMethod(double** matrix){
    double **edin = new double *[N];
    double **prev = new double *[N];
    for (int i = 0; i < N; i++){
        edin[i] = new double[N];
        prev[i] = new double[N];
        for (int j = 0; j < N; j++){
            edin[i][j] = 0;
        }
        edin[i][i] = 2;
    }

    double N1 = 0, Ninf = 0; //норма матрицы по столбцам и по строкам
    double **inv = clone(matrix);       //инициализация начального приближения
    for (int row = 0; row < N; row++){
        double colsum = 0, rowsum = 0;
        for(int col = 0; col < N; col++){
            rowsum += fabs(inv[row][col]);
            colsum += fabs(inv[col][row]);
        }
        N1 = std::max(colsum, N1);
        Ninf = std::max(rowsum, Ninf);
    }

    inv = getTransp(inv);

    inv = numOnMatrix(inv, (1 / (N1 * Ninf)));

    cout << "Norma: " << getNorma(inv) << endl;
    while (fabs(getGaussDet(getMult(matrix, inv)) - 1) >= EPS){
        double **prev = clone(inv);
        inv = getMult(matrix, prev);
        inv = numOnMatrix(inv, -1);
        addMatrix(inv, edin);
        inv = getMult(prev, inv);
        for (int i = 0; i < N; i++){
            delete[] prev[i];
        }
        delete[] prev;
    }

    for (int i = 0; i < N; i++){
        delete[] edin[i];
    }
    delete[] edin;
    return inv;

}

/**
 * Функция возвращает определитель, вычисленный методом Гаусса.
 *
 * @param
 *          double **matrix1: искомая матрицы.
 *
 * @return
 *          double **: определитель.
 */
double Invert::getGaussDet(double **matrix)
{
    double det = 1;
    for (int i = 0; i < N; i++)
    {
        det *= matrix[i][i];
    }
    return det;
}

double** Invert::clone(double **matrix)
{
    double **temp = new double*[N];
    for(int i = 0; i < N; i++)
    {
        temp[i] = new double[N];
        for(int j = 0; j < N; j++)
            temp[i][j] = matrix[i][j];
    }
    return temp;
}

double **Invert::numOnMatrix(double** matrix, double number){
    double **temp = new double *[N];
    for (int i = 0; i < N; i++){
        temp[i] = new double[N];
        for (int j = 0; j < N; j++){
            temp[i][j] = matrix[i][j];
            temp[i][j] *= number;
        }
    }
    return temp;
}

void Invert::addMatrix(double** matrix1, double** matrix2){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            matrix1[i][j] += matrix2[i][j];
        }
    }
}

double Invert::getTr(double **matrix){
    double tr = 0;
    for (int i = 0; i < N; i++){
        tr += matrix[i][i];
    }

    return tr;
}

double Invert::getNorma(double **matrix){
    double norma = 0;
    double max = 0;
    for (int i = 0; i < N; i++){
        norma = 0;
        for (int j = 0; j < N; j++){
            norma += matrix[i][j];
        }
        max = std::max(max, norma);
    }

    return max;
}

Invert::~Invert(){
    for (int i = 0; i < N; i++){
        delete[] inverted[i];
    }
    delete[] inverted;
    inverted = nullptr;
}

double **Invert::getInvertedMatrix(){
    return inverted;
}

QString Invert::getMatrixType(){
    return str;
}

void Invert::printMatrix(double **matrix){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}
