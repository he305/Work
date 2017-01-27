using System;

namespace MatrixLib
{
    public class Matrix
    {
        #region Vars
        public double[,] matrix { get; }
        private int row, col;
        #endregion

        private const double EPS = 0.001;

        #region Constructions
        public Matrix()
        {

        }

        public Matrix(double[,] mat, int row, int col)
        {
            this.matrix = mat;
            this.row = row;
            this.col = col;
        }

        public Matrix(double[] vec, int size)
        {
            double[,] mat = new double[1, size];

            for (int i = 0; i < size; i++)
            {
                mat[0, i] = vec[i];
            }

            this.matrix = mat;
            this.row = 1;
            this.col = size;
        }
        #endregion

        public void printMatrix()
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    Console.Write(matrix[i, j] + "\t");
                }
                Console.WriteLine();
            }
        }

        public static Matrix operator +(Matrix a, Matrix b)
        {
            double[,] newMat = new double[a.row, a.col];
            for (int i = 0; i < a.row; i++)
            {
                for (int j = 0; j < a.col; j++)
                {
                    newMat[i, j] = a.matrix[i, j] + b.matrix[i, j];
                }
            }

            return new Matrix(newMat, a.row, a.col);
        }

        public static Matrix operator -(Matrix a, Matrix b)
        {
            double[,] newMat = new double[a.row, a.col];
            for (int i = 0; i < a.row; i++)
            {
                for (int j = 0; j < a.col; j++)
                {
                    newMat[i, j] = a.matrix[i, j] - b.matrix[i, j];
                }
            }

            return new Matrix(newMat, a.row, a.col);
        }

        public static Matrix operator *(Matrix a, Matrix b)
        {
            double[,] newMat = new double[a.row, a.col];

            for (int i = 0; i < a.row; i++)
            {
                for (int j = 0; j < a.col; j++)
                {
                    newMat[i, j] = 0;
                    for (int k = 0; k < a.row; k++)
                    {
                        newMat[i, j] += a.matrix[i, k] * b.matrix[k, j];
                    }
                    if (Math.Abs(newMat[i, j]) < EPS)
                        newMat[i, j] = 0;
                }
            }

            return new Matrix(newMat, a.row, a.col);
        }

        public Matrix GetMultiplication(Matrix a, Matrix b)
        {
            double[,] newMat = new double[a.row, a.col];

            for (int i = 0; i < a.row; i++)
            {
                for (int j = 0; j < a.col; j++)
                {
                    newMat[i, j] = 0;
                    for (int k = 0; k < a.row; k++)
                    {
                        newMat[i, j] += a.matrix[i, k] * b.matrix[k, j];
                    }
                    if (Math.Abs(newMat[i, j]) < EPS)
                        newMat[i, j] = 0;
                }
            }

            return new Matrix(newMat, a.row, a.col);
        }

        public Matrix kroneckerProduct(Matrix b)
        {
            int tempRow = this.row * b.row;
            int tempCol = this.col * b.col;

            int nBlocks = this.row * b.col;

            double[,,] blockMatrix = new double[nBlocks, b.row, this.col];

            int k, l;
            int block = 0;
            for (l = 0; l < nBlocks / this.row; l++)
            {
                for (k = 0; k < nBlocks / this.row; k++)
                {
                    for (int i = 0; i < b.row; i++)
                    {
                        for (int j = 0; j < b.col; j++)
                        {
                            blockMatrix[block, i, j] = this.matrix[l, k] * b.matrix[i, j];
                        }
                    }
                    block++;
                }
            }

            double[,] tempMatrix = new double[tempRow, tempCol];

            l = 0;
            k = 0;
            block = 0;
            for (int i = 0; i < tempRow; i++)
            {
                if (k >= b.row && i != tempRow - 1)
                {
                    k = 0;
                    block += 2;
                }

                l = 0;
                for (int j = 0; j < tempCol; j++)
                {
                    if (l >= b.col && j != tempCol - 1)
                    {
                        l = 0;
                        block++;
                    }
                    tempMatrix[i, j] = blockMatrix[block, k, l];
                    l++;
                }
                block--;
                k++;
            }

            return new Matrix(tempMatrix, tempRow, tempCol);
        }

        public Matrix invert()
        {
            Matrix mat = clone();
            Matrix edin = Matrix.GetE2Matrix(row);

            double N1 = 0, NInf = 0;
            Matrix inv = clone();


            for (int i = 0; i < row; i++)
            {
                double colsum = 0, rowsum = 0;
                for (int j = 0; j < col; j++)
                {
                    rowsum += Math.Abs(inv.matrix[i, j]);
                    colsum += Math.Abs(inv.matrix[j, i]);
                }
                N1 = Math.Max(colsum, N1);
                NInf = Math.Max(rowsum, NInf);
            }

            inv = inv.transpose();
            inv = inv.productNumber(1 / (N1 * NInf));
            
            while (Math.Abs((mat*inv).getGaussDet() - 1) >= EPS)
            {
                Matrix prev = inv.clone();
                inv = mat * prev;
                inv = inv.productNumber(-1);
                inv = inv + edin;
                inv = prev * inv;
            }

            return inv;
        }

        public static Matrix GetE2Matrix(int size)
        {
            double[,] edin = new double[size, size];
            for(int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (i == j)
                        edin[i, j] = 2;
                    else
                        edin[i, j] = 0;
                }
            }

            return new Matrix(edin, size, size);
        }

        public Matrix transpose()
        {
            double[,] tempMatrix = new double[this.col, this.row];
            for (int i = 0; i < this.col; i++)
            {
                for (int j = 0; j < this.row; j++)
                {
                    tempMatrix[i, j] = this.matrix[j, i];
                }
            }
            return new Matrix(tempMatrix, this.col, this.row);
        }

        public Matrix productNumber(double num)
        {
            double[,] tempMatrix = this.matrix;
            for (int i = 0; i < this.row; i++)
            {
                for (int j = 0; j < this.col; j++)
                {
                    tempMatrix[i, j] *= num;
                }
            }
            return new Matrix(tempMatrix, this.row, this.col);
        }

        public double getGaussDet()
        {
            double det = 1;
            for (int i = 0; i < this.row; i++)
            {
                det *= this.matrix[i, i];
            }
            return det;
        }

        public Matrix clone()
        {
            double[,] mat = new double[row, col];

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    mat[i, j] = matrix[i, j];
                }
            }

            return new Matrix(mat, row, col);
        }
    }
}
