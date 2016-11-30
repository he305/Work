using System;

namespace MatrixLib
{
    public class Matrix
    {
        #region Vars
        public double[,] matrix { get; }
        private int row, col;
        #endregion

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

        public Matrix sum(Matrix b)
        {
            double[,] newMat = new double[this.row, this.col];
            for (int i = 0; i < this.row; i++)
            {
                for (int j = 0; j < this.col; j++)
                {
                    newMat[i, j] = this.matrix[i, j] + b.matrix[i, j];
                }
            }

            return new Matrix(newMat, this.row, this.col);
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
    }
}
