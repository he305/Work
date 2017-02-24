using MNK;
using System;
using System.Collections.Generic;

namespace MNK2dim
{
    class MNK
    {
        private List<double> xVector;
        private List<double> yVector;
        private List<double> wVector;
        private int size;

        public MNK(double[] x,
                   double[] y,
                   double[] w,
                   int size)
        {
            this.xVector = new List<double>(size);
            this.yVector = new List<double>(size);
            this.wVector = new List<double>(size);

            this.xVector.AddRange(x);
            this.yVector.AddRange(y);
            this.wVector.AddRange(w);

            this.size = size;
        }

        public MNK(double[] x,
                   double[] y,
                   int size)
        {
            this.xVector = new List<double>(size);
            this.yVector = new List<double>(size);
            this.wVector = new List<double>(size);

            this.xVector.AddRange(x);
            this.yVector.AddRange(y);
            
            for (int i = 0; i < size; i++)
            {
                wVector.Add(1);
            }

            this.size = size;
        }

        public double[] Calculate()
        {
            //2 = polynomeSize + 1
            double[,] a = new double[2, 2];
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    double sum = 0;
                    for (int k = 0; k < size; k++)
                    {
                        sum += Math.Pow(xVector[k], i + j) * wVector[k];
                    }
                    a[i, j] = sum;
                }
            }

            double[] z = new double[2];

            for (int i = 0; i < 2; i++)
            {
                double sum = 0;
                for (int j = 0; j < size; j++)
                {
                    sum += Math.Pow(xVector[j], i) * yVector[j] * wVector[j];
                }
                z[i] = sum;
            }

            LUDecompose lu = new LUDecompose(a, z, 2);
            double[] answer = lu.luSolve();

            for (int i = 1; i >= 0; i--)
            {
                if (Math.Abs(answer[i]) < 0.00001)
                {
                    answer[i] = 0;
                }
            }

            return answer;
            /////// MAYBE EASIER START FROM ZERO USING CPP FILE FROM 11.07
            //    const int rows = 3;
            //    double[,] coords = new double[size, size + 1];

            //    for (int i = 0; i < size; i++)
            //    {
            //        for (int j = 0; j < size; j++)
            //        {
            //            switch (i)
            //            {
            //                case (0):
            //                    coords[i, j] = xVector[j];
            //                    break;
            //                case (1):
            //                    coords[i, j] = yVector[j];
            //                    break;
            //                case (2):
            //                    coords[i, j] = 1;
            //                    break;
            //            }
            //        }
            //    }

            //    coords[0, size] = polynomeSize[0];
            //    coords[1, size] = polynomeSize[1];
            //    coords[2, size] = 1;
            //    coords[3, size] = 1;

            //    double[,] a;
            //    const int matSize = 3;
            //    a = new double[matSize, matSize];

            //    int indexFromBehind = rows - 2;
            //    for (int i = 0; i < matSize; i++)
            //    {
            //        for (int j = 0; j < matSize; j++)
            //        {
            //            double sum = 0;
            //            for (int k = 0; k < size; k++)
            //            {
            //                sum += Math.Pow(coords[j, k], coords[j, size])
            //                    * Math.Pow(coords[indexFromBehind, k], coords[indexFromBehind, size])
            //                    * wVector[k];
            //            }
            //            a[i, j] = sum;
            //        }
            //        indexFromBehind--;
            //    }

            //    indexFromBehind = rows - 2;

            //    double[] z = new double[matSize];

            //    for (int i = 0; i < matSize; i++)
            //    {
            //        double sum = 0;
            //        for (int j = 0; j < size; j++)
            //        {
            //            sum += coords[3, j] * Math.Pow(coords[indexFromBehind, j], coords[indexFromBehind, size]);
            //        }
            //        z[i] = sum;
            //        indexFromBehind--;
            //    }

            //    LUDecompose lu = new LUDecompose(a, z, matSize);
            //    double[] answer = lu.luSolve();

            //    for (int i = 0; i < matSize; i++)
            //    {

            //        if (Math.Abs(answer[i] - Math.Round(answer[i])) <= 0.00001)
            //        {
            //            answer[i] = Math.Round(answer[i]);
            //        }
            //        else
            //        {
            //            answer[i] = Math.Round(answer[i], 4);
            //        }
            //    }

            //    return answer;

            //
        }
    }
}
