#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define EPS 0.001

float** createMatrix(int size)
{
    int i;
    float** matrix = (float**)malloc(sizeof(float*)*size);
    for(i = 0; i < size; i++)
    {
        matrix[i] = (float*)malloc(sizeof(float)*size);
    }
    return matrix;
}

void copyMatrix(float** a, float** b, int size)
{
    int i, j;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            b[i][j] = a[i][j];
        }
    }
}

//вычисления для lup-разложения
int maxInColumn(float** a, int i, int size)
{
    int j = i + 1, k = i;
    float max = fabs(a[i][i]);
    for (; j < size; j++)
    {
        if(fabs(a[j][i]) > max)
        {
            max = fabs(a[j][i]);
            k = j;
        }
    }
    if (max < EPS)
    {
        printf("virozhdennaya matrix!");
        exit(0);
    }
    return k;
}

void swapRow(float** a, int size1, int size2)
{
    float* tmp;
    tmp = (float*)a[size1];
    a[size1] = (float*)a[size2];
    a[size2] = (float*)tmp;
}

// прямая подстановка
float* forwardSub(float** a, float* b, int* p, int size)
{
    int i, j;
    float* y = (float*)malloc(sizeof(float)*size);
    for (i = 0; i < size; i++)
    {
        y[i]=b[p[i]];

        for(j=0; j<i; j++)
          y[i]-=a[i][j]*y[j];
    }

    return y;
}

//обратная подстановка
float* backSub(float** a, float* y, int size)
{
    float* x = (float*)malloc(sizeof(float)*size);
    int i, j;
    for(i = 0; i < size; i++)
    {
        x[size-1-i] = y[size-1-i];
        for(j = 0; j < i; j++)
        {
            x[size-1-i] -= (a[size-1-i][size-1-j]*x[size-1-j]);
        }
        x[size-1-i] /= a[size-1-i][size-1-i];
    }
    return x;
}

float** readFile(char* name)
{
    FILE* f = fopen(name, "r");
    int size;
    int i,j;

    fscanf(f, "%d", &size);
    float** a = createMatrix(size);
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
            fscanf(f, "%f ", &a[i][j]);
    }
    return a;
}

void randomMatrix(FILE *f, int size)
{
    int i,j;
    fprintf(f, "%d\n", size);
    srand(time(0));

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            fprintf(f, "%d ", rand()%100);
        }
        fprintf(f,"\n");
    }
}

void randomArray(FILE *f, int size)
{
  int i;
  fprintf(f, "%d\n", size);
  srand(time(0));

  for(i = 0; i < size; i++)
  {
    fprintf(f, "%d ", rand()%100);
  }
}

float** scanfMatrix()
{
  int size, i, j;

  printf("Введите размер матрицы: ");
  scanf("%d", &size);

  float** a = createMatrix(size);

  for(i = 0; i < size; i++)
  {
    for(j = 0; j < size; j++)
    {
      printf("Введите a[%d][%d]:", i, j);
      scanf("%f", &a[i][j]);
    }
  }
  return a;
}

int* lupDecomposition(float** a, int size)
{
    int i, j, k;
    int* p = (int*)malloc(sizeof(int)*size);

    for(i = 0; i < size; i++)
     p[i] = i;
    for(i = 0; i < size; i++)
    {
        j = maxInColumn(a, i, size);
        if(i != j)
        {
             swapRow(a, i, j);
             k = p[i];
             p[i] = p[j];
             p[j] = k;
         }

        for(j = i, j++; j < size; j++)
        {
            a[j][i] /= a[i][i];
        }
        for(j = i, j++; j < size; j++)
        {
            for(k = i, k++; k < size; k++)
            {
                a[j][k] -= (a[i][k]*a[j][i]);
            }
        }
    }
    return p;
}

//решение через lup-разложение
float* lupSolve(float** a, float* b, int size)
{
    float** a1, *x, *y;
    int* p;
    int i, j;

    a1 = createMatrix(size);

    copyMatrix(a, a1, size);

    p = lupDecomposition(a1, size);
    y = forwardSub(a1, b, p, size);
    x = backSub(a1, y, size);

    //Выводим Р
    printf("\nP: \n");
    for (i = 0; i < size; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");

    //Выводим L
    printf("\nL:\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (i == j)
                printf("1 ");
            else if (i > j)
                printf("%f ", a1[i][j]);
            else
                printf("0 ");
        }
        printf("\n");
    }

    //Выводим U
    printf("\nU:\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (i <= j)
                printf("%f ", a1[i][j]);
            else
                printf("0 ");
        }
        printf("\n");
    }

    return x;
}

//проверка АХ=В
void check(float** a, float* b, float* x, int size)
{
  int i,j;
  float sum = 0;

    printf("\nCHECK:\n");
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
            sum += a[i][j]*x[j];
        printf("A*X: %f = B: %f\n", sum,b[i]); //Проверка
        if (fabs(sum - b[i]) > EPS)
            printf("ERROR %f != %f \n", sum, b[i]);
        sum = 0;
    }
    printf("\n");
}

int main()
{
    int size = 3;
    float** a = createMatrix(size);
    float b[size];
    float* x;
    clock_t time;
    int i, j;

    // //---------Задаем рандомные матрицы в файл-----------------//
    // FILE* f1 = fopen("A.txt", "w");
    // randomMatrix(f1, size);
    // fclose(f1);
    //
    // FILE* f2 = fopen("B.txt", "w");
    // randomArray(f2, size);
    // fclose(f2);

    //---------Ввод матриц вручную----------------------------//
      a = scanfMatrix();

      printf("Введите размер массива: ");
      scanf("%d", &size);
    for(i = 0; i < size; i++)
    {
       printf("Введите b[%d]:", i);
       scanf("%f", &b[i]);
    }

    // //----------Считывание матрицы и массива-----------------//
    // a = readFile("A.txt");//read a
    //
    // FILE* f = fopen("B.txt", "r");//read b
    // fscanf(f, "%d", &size);
    //     for(j = 0; j < size; j++)
    //         fscanf(f, "%f ", &b[i]);

    time = clock();
    x = lupSolve(a, b, size);
    time = clock() - time;

    printf("\nMatrix A:\n");
    for (i = 0; i < size; i++)
    {
        for (j=0; j<size; j++)
          printf("%3.3f ", a[i][j]);
        printf("\n");
    }

    printf("\nMatrix B: \n");
    for (i = 0; i < size; i++)
      printf("%3.3f ", b[i]);
    printf("\n");


    printf("\nMatrix x: ");
    for (i = 0; i < size; i++)
      printf("%3.3f ", x[i]);

    check(a, b, x, size);

    printf("\n\nLUP-decomposition completed in %f sec.\n", ((double)time/CLOCKS_PER_SEC));
    printf("\n");



    return 0;
}