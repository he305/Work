using Microsoft.Office.Interop.Excel;
using System;
using System.Linq;
using System.Collections.Generic;

namespace MNK2dim
{
    class Program
    {
        //Radio
        static double[] timeLocalVector;
        static double[] azimutLocalVector;
        //Optic
        static double[] timeOpticVector;
        static double[] azimutOpticVector;
        //Расстояние
        static double[] rangeVector;

        static void Main(string[] args)
        {
            string filenameLocal = AppDomain.CurrentDomain.BaseDirectory + "../../radio.xlsx";
            string filenameOptic = AppDomain.CurrentDomain.BaseDirectory + "../../optic.xlsx";
            Application xlsApp = new Application();

            if (xlsApp == null)
            {
                Console.WriteLine("EXCEL could not be started. Check that your office installation and project references are correct.");
                return;
            }

            //Displays Excel so you can see what is happening
            //xlsApp.Visible = true;

            Workbook wb = xlsApp.Workbooks.Open(filenameLocal,
                0, true, 5, "", "", true, XlPlatform.xlWindows, "\t", false, false, 0, true);
            Sheets sheets = wb.Worksheets;
            Worksheet ws = (Worksheet)sheets.get_Item(1);

            Range timeLocalColumn = ws.UsedRange.Columns[2];
            Array timeLocalArr = (Array)timeLocalColumn.Cells.Value;
            timeLocalVector = timeLocalArr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();

            Range rangeColumn = ws.UsedRange.Columns[8];
            Array rangeArr = (Array)rangeColumn.Cells.Value;
            rangeVector = rangeArr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();

            Range azimutLocalColumn = ws.UsedRange.Columns[9];
            Array azimutLocalArr = (Array)azimutLocalColumn.Cells.Value;
            azimutLocalVector = azimutLocalArr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();
            
            for (int i = 0; i < azimutLocalVector.Length; i++)
            {
                azimutLocalVector[i] = azimutLocalVector[i] * Math.PI / 180;
                timeLocalVector[i] = Math.Round(timeLocalVector[i]);
            }

            wb = xlsApp.Workbooks.Open(filenameOptic,
                0, true, 5, "", "", true, XlPlatform.xlWindows, "\t", false, false, 0, true);
            sheets = wb.Worksheets;
            ws = (Worksheet)sheets.get_Item(1);

            Range timeOpticColumn = ws.UsedRange.Columns[2];
            Array timeOpticArr = (Array)timeOpticColumn.Cells.Value;
            timeOpticVector = timeOpticArr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();

            Range azimutOpticColumn = ws.UsedRange.Columns[6];
            Array azimutOpticArr = (Array)azimutOpticColumn.Cells.Value;
            azimutOpticVector = azimutOpticArr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();

            CalculateByRange(20000);
            CalculateByRange(10000);
            CalculateByRange(5000);
            CalculateByRange(3000);
            //CalculateByRange(2000);


            Console.ReadKey();
        }

        static void CalculateByRange(double rang)
        {
            Console.WriteLine("Расстояние = " + rang);
            int sizeLocal = 5;
            double[] targetAzimutLocal = new double[sizeLocal];
            double[] targetTimeLocal = new double[sizeLocal];


            int targetTimeStart = 0;
            int targetTimeEnd = 0;
            for (int i = 0; i < azimutLocalVector.Length; i++)
            {
                if (rangeVector[i] == rang)
                {
                    targetTimeStart = (int)timeLocalVector[i];
                    if (azimutLocalVector.Length - 1 - i <= sizeLocal)
                    {
                        sizeLocal = azimutLocalVector.Length - i - 1;
                        targetAzimutLocal = new double[sizeLocal];
                        targetTimeLocal = new double[sizeLocal];
                    }
                    for (int j = 0; j < sizeLocal; j++)
                    {
                        try
                        {
                            targetTimeLocal[j] = timeLocalVector[i++];
                            targetAzimutLocal[j] = azimutLocalVector[i++];
                        }
                        catch (IndexOutOfRangeException ex)
                        {

                        }
                        if (targetAzimutLocal[j] > 6.25)
                        {
                            targetAzimutLocal[j] = targetAzimutLocal[j] - (360 * Math.PI / 180);
                        }
                        
                    }
                    targetTimeEnd = (int)targetTimeLocal[targetTimeLocal.Length - 1];
                    break;
                }
            }
            
            MNK mnkLocal = new MNK(targetTimeLocal, targetAzimutLocal, sizeLocal);
            double[] answerLocal = mnkLocal.Calculate();

            Console.WriteLine("Radio");
            for (int i = 1; i >= 0; i--)
            {
                Console.WriteLine(answerLocal[i]);
            }


            int sizeOptic = 100;
            int indexStart = 0;
            int indexEnd = 0;
            bool found = false;
            for (int i = 0; i < timeOpticVector.Length; i++)
            {
                if (Math.Round(timeOpticVector[i]) == targetTimeStart && !found)
                {
                    indexStart = i;
                    found = true;
                }
                if (Math.Round(timeOpticVector[i]) == targetTimeEnd)
                {
                    indexEnd = i;
                    sizeOptic = indexEnd - indexStart + 1;
                    break;
                }
            }
            if (indexEnd == 0)
            {
                indexEnd = timeOpticVector.Length - 1;
                sizeOptic = indexEnd - indexStart + 1;
            }

            Console.WriteLine("Start {0}, End {1}", indexStart, indexEnd);

            double[] targetAzimutOptic = new double[sizeOptic];
            double[] targetTimeOptic = new double[sizeOptic];
            for (int i = indexStart, j = 0; i < indexEnd; i++, j++)
            {
                targetAzimutOptic[j] = azimutOpticVector[i];
                targetTimeOptic[j] = timeOpticVector[i];

                if (targetAzimutOptic[j] > 6.25)
                {
                    targetAzimutOptic[j] = targetAzimutOptic[j] - (360 * Math.PI / 180);
                }
            }

            MNK mnkOptic = new MNK(targetTimeOptic, targetAzimutOptic, sizeOptic);
            double[] answerOptic = mnkOptic.Calculate();
            Console.WriteLine("Optic");
            for (int i = 1; i >= 0; i--)
            {
                Console.WriteLine(answerOptic[i]);
            }

            double matOjidDelta = 0;
            double matOjidDeltaPower2 = 0;
            double dispersia;
            Console.WriteLine("DELTA");
            double[] deltaVector = new double[sizeOptic];
            for (int i = 0; i < sizeOptic; i++)
            {
                deltaVector[i] = (answerLocal[1] * timeOpticVector[i] + answerLocal[0]) -
                    (answerOptic[1] * timeOpticVector[i] + answerOptic[0]);
                matOjidDelta += deltaVector[i];
                matOjidDeltaPower2 += Math.Pow(deltaVector[i], 2);
            }
            matOjidDelta /= sizeOptic;
            matOjidDeltaPower2 /= sizeOptic;
            Console.WriteLine("Мат ожидание: " + matOjidDelta);
            Console.WriteLine("Дисперсия: " + (matOjidDeltaPower2 - Math.Pow(matOjidDelta, 2)));

            Console.WriteLine("/////////////////////////////////////////////////");
        }
    }
}
