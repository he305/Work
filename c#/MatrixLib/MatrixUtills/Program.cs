using MatrixLib;
using System;

namespace MatrixUtills
{
    class Program
    {
        static void Main(string[] args)
        {
            int N = 3;
            double[,] aMat = new double[N, N];
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    aMat[i, j] = double.Parse(Console.ReadLine());
                }
            }
            Matrix a = new Matrix(aMat, N, N);

            (a.invert()).printMatrix();
            Console.ReadKey();
        }
    }
}
