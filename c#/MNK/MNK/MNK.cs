using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MNK
{
    class MNK
    {
        private List<double> xVector;
        private List<double> yVector;
        private List<double> zVector;
        private List<double> wVector;
        private int size;
        private int[] polynomeSize;

        public MNK(double[] x, 
                   double[] y, 
                   double[] z,
                   double[] w, 
                   int size, 
                   int[] polynomeSize)
        {
            this.xVector = new List<double>(size);
            this.yVector = new List<double>(size);
            this.zVector = new List<double>(size);
            this.wVector = new List<double>(size);

            this.xVector.AddRange(x);
            this.yVector.AddRange(y);
            this.zVector.AddRange(z);
            this.wVector.AddRange(w);

            this.size = size;
            this.polynomeSize = polynomeSize;
        }

        public double[] Calculate()
        {
            const int rows = 4;
            double[,] coords = new double[size, size+1];

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    switch (i)
                    {
                        case (0):
                            coords[i, j] = xVector[j];
                            break;
                        case (1):
                            coords[i, j] = yVector[j];
                            break;
                        case (2):
                            coords[i, j] = 1;
                            break;
                        case (3):
                            coords[i, j] = zVector[j];
                            break;
                    }
                }
            }

            coords[0, size] = polynomeSize[0];
            coords[1, size] = polynomeSize[1];
            coords[2, size] = 1;
            coords[3, size] = 1;

            double[,] a;
            const int matSize = 3;
            a = new double[matSize, matSize];

            int indexFromBehind = rows - 2;
            for (int i = 0; i < matSize; i++)
            {
                for (int j = 0; j < matSize; j++)
                {
                    double sum = 0;
                    for (int k = 0; k < size; k++)
                    {
                        sum += Math.Pow(coords[j, k], coords[j, size])
                            * Math.Pow(coords[indexFromBehind, k], coords[indexFromBehind, size])
                            * wVector[k];
                    }
                    a[i, j] = sum;
                }
                indexFromBehind--;
            }

            indexFromBehind = rows - 2;

            double[] z = new double[matSize];

            for (int i = 0; i < matSize; i++)
            {
                double sum = 0;
                for (int j = 0; j < size; j++)
                {
                    sum += coords[3, j] * Math.Pow(coords[indexFromBehind, j], coords[indexFromBehind, size]);
                }
                z[i] = sum;
                indexFromBehind--;
            }

            LUDecompose lu = new LUDecompose(a, z, matSize);
            double[] answer = lu.luSolve();
            
            for (int i = 0; i < matSize; i++)
            {
                
                if (Math.Abs(answer[i] - Math.Round(answer[i])) <= 0.00001)
                {
                    answer[i] = Math.Round(answer[i]);
                }
                Console.WriteLine(answer[i]);
            }

            return answer;
            
        }
    }
}