using System;
using System.Collections.Generic; 

namespace MNK
{   
    class LUDecompose
    {
        private int size;
        private double[] vector;
        private double[,] matrix;

        public LUDecompose(double[,] matrix, double[] vector, int size)
        {
            this.size = size;
            this.vector = vector;
            this.matrix = matrix;
        }

        public double[] luSolve()
        {
            double[,] a1;
            double[] y;
            double[] x;

            int[] p;

            a1 = copyMatrix(matrix);




            //for (int i = 0; i < 2; i++)
            //{
            //    for (int j = 0; j < 2; j++)
            //    {
            //        Console.Write(a1[i, j] + " ");
            //    }
            //    Console.WriteLine();
            //}

            p = lupDecompose(ref a1);

            //for (int i = 0; i < 2; i++)
            //{
            //    for (int j = 0; j < 2; j++)
            //    {
            //        Console.Write(a1[i, j] + " ");
            //    }
            //    Console.WriteLine();
            //}
            y = forwardSub(a1, vector, p);
            for (int i = 0; i < y.Length; i++ )
            {
                Console.WriteLine(this.vector[i]);
            }
            x = backSub(a1, y);

            return x;
        }

        private int[] lupDecompose(ref double[,] mat)
        {
            int j, k;
            int[] p = new int[size];

            for (int i = 0; i < size; i++)
            {
                p[i] = i;
            }

            for (int i = 0; i < size; i++)
            {
                j = maxInColumn(mat, i);
                if (i != j)
                {
                    swapRow(mat, i, j);
                    k = p[i];
                    p[i] = p[j];
                    p[j] = k;
                }
                for (j = i+1; j < size; j++)
                {
                    mat[j, i] /= mat[i, i];
                }
                for (j = i+1; j < size; j++)
                {
                    for (k = i + 1; k < size; k++)
                    {
                        mat[j, k] -= (mat[i, k] * mat[j, i]);
                    }
                }
            }

            return p;
        }

        private int maxInColumn(double[,] mat, int i)
        {
            int j = i + 1, k = i;
            double max = Math.Abs(mat[i, i]);
            for (; j < size; j++)
            {
                if (Math.Abs(mat[j, i]) > max)
                {
                    max = Math.Abs(mat[j, i]);
                    k = j;
                }
            }
            return k;
        }

        public void swapRow(double[,] mat, int size1, int size2)
        {
            for (int i = 0; i < size; i++)
            {
                var row = mat[size1, i];
                mat[size1, i] = mat[size2, i];
                mat[size2, i] = row;
            }
        }

        private double[] backSub(double[,] mat, double[] y)
        {
            double[] x = new double[size];

            for (int i = 0; i < size; i++)
            {
                x[size - 1 - i] = y[size - 1 - i];
                for (int j = 0; j < i; j++)
                {
                    x[size - 1 - i] -= (mat[size - 1 - i, size - 1 - j] * x[size - 1 - j]);
                }
                x[size - 1 - i] /= mat[size - 1 - i, size - 1 - i];
            }
            return x;
        }

        private double[] forwardSub(double[,] mat, double[] vec, int[] p)
        { 
            double[] y = new double[size];
            for (int i = 0; i < size; i++)
            {
                y[i] = vec[p[i]];
                for (int j = 0; j < i; j++)
                {
                    y[i] -= mat[i, j] * y[j];
                }
            }
            return y;
        }

        private double[,] copyMatrix(double[,] from)
        {
            double[,] to = new double[from.GetLength(0), from.GetLength(1)];
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    to[i, j] = from[i, j];
                }
            }
            return to;
        }
    }
}
