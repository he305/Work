using Microsoft.Office.Interop.Excel;
using System;
using System.Linq;
using System.Collections.Generic;
using System.Diagnostics;

namespace MNK2dim
{
    class Program
    {
        //Radio
        static List<Measure> radio = new List<Measure>();
        //Optic
        static List<Measure> optic = new List<Measure>();

        static String pythonScriptString = @"/../graph.py";

        static double[] getExcelColumn(Worksheet ws, int i, bool skipZero)
        {
            Range range = ws.UsedRange.Columns[i];
            Array arr = (Array)range.Cells.Value;

            double[] vector; 
            if (skipZero)
                vector = arr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();
            else
                vector = arr.OfType<object>().Skip(1).Select(Convert.ToDouble).ToArray();
            return vector;
        }

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

            double[] timeLocalVector = getExcelColumn(ws, 2, true);
            double[] rangeVector = getExcelColumn(ws, 8, true);
            double[] azimutLocalVector = getExcelColumn(ws, 9, true);
            double[] ugolMestaLocalVector = getExcelColumn(ws, 10, true);

            for (int i = 0; i < azimutLocalVector.Length; i++)
            {
                azimutLocalVector[i] = azimutLocalVector[i] * Math.PI / 180;
                ugolMestaLocalVector[i] = ugolMestaLocalVector[i] * Math.PI / 180;
                timeLocalVector[i] = Math.Round(timeLocalVector[i]);

                radio.Add(new Measure(timeLocalVector[i], azimutLocalVector[i], ugolMestaLocalVector[i], rangeVector[i]));    
            }
            

            wb = xlsApp.Workbooks.Open(filenameOptic,
                0, true, 5, "", "", true, XlPlatform.xlWindows, "\t", false, false, 0, true);
            sheets = wb.Worksheets;
            ws = (Worksheet)sheets.get_Item(1);

            double[] timeOpticVector = getExcelColumn(ws, 2, false);
            double[] azimutOpticVector = getExcelColumn(ws, 6, false);
            double[] ugolMestaOpticVector = getExcelColumn(ws, 7, false);

            for (int i = 0; i < timeOpticVector.Length; i++)
            {
                optic.Add(new Measure(timeOpticVector[i], azimutOpticVector[i], ugolMestaOpticVector[i]));
            }

            CalculateByRange(20000);
            CalculateByRange(10000);
            CalculateByRange(5000);
            CalculateByRange(3000);
            CalculateByRange(2000);


            Console.ReadKey();
        }
            
        static void CalculateByRange(double rang)
        {
            Console.WriteLine("Расстояние = " + rang);
            int sizeLocal = 5;
            double[] targetAzimutLocal = new double[sizeLocal];
            double[] targetUgolMestaLocal = new double[sizeLocal];
            double[] targetTimeLocal = new double[sizeLocal];


            int targetTimeStart = 0;
            int targetTimeEnd = 0;
            for (int i = 0; i < radio.Count; i++)
            {
                if (radio[i].getRange() == rang)
                {
                    targetTimeStart = (int)radio[i].getTime();
                    if (radio.Count - 1 - i <= sizeLocal)
                    {
                        sizeLocal = radio.Count - i - 1;
                        targetAzimutLocal = new double[sizeLocal];
                        targetUgolMestaLocal = new double[sizeLocal];
                        targetTimeLocal = new double[sizeLocal];
                    }
                    for (int j = 0; j < sizeLocal; j++)
                    {
                        try
                        {
                            targetTimeLocal[j] = radio[i++].getTime();
                            targetAzimutLocal[j] = radio[i++].getAzimut();
                            targetUgolMestaLocal[j] = radio[i++].getUgolMesta();
                        }
                        catch (ArgumentOutOfRangeException ex)
                        {
                            targetTimeLocal[j] = radio[i - 3].getTime();
                            targetAzimutLocal[j] = radio[i - 3].getAzimut();
                            targetUgolMestaLocal[j] = radio[i - 3].getUgolMesta();
                            //Console.WriteLine(ex.StackTrace);
                            break;
                        }
                        finally
                        {
                            if (targetAzimutLocal[j] > 6.25)
                            {
                                targetAzimutLocal[j] = targetAzimutLocal[j] - (360 * Math.PI / 180);
                            }
                        }
                        
                    }
                    targetTimeEnd = (int)targetTimeLocal[targetTimeLocal.Length - 1];
                    break;
                }
            }
                
            MNK mnkLocalAzimut = new MNK(targetTimeLocal, targetAzimutLocal, sizeLocal);
            double[] answerLocalAzimut = mnkLocalAzimut.Calculate();

            MNK mnkLocalUgolMesta = new MNK(targetTimeLocal, targetUgolMestaLocal, sizeLocal);
            double[] answerLocalUgolMesta = mnkLocalUgolMesta.Calculate();

            Console.WriteLine("Radio");
            for (int i = 1; i >= 0; i--)
            {
                Console.WriteLine(answerLocalAzimut[i] + "\t" + answerLocalUgolMesta[i]);
            }


            int sizeOptic = 100;
            int indexStart = 0;
            int indexEnd = 0;
            bool found = false;
            for (int i = 0; i < optic.Count; i++)
            {
                if (Math.Round(optic[i].getTime()) == targetTimeStart && !found)
                {
                    indexStart = i;
                    found = true;
                }
                if (Math.Round(optic[i].getTime()) == targetTimeEnd)
                {
                    indexEnd = i;
                    sizeOptic = indexEnd - indexStart + 1;
                    break;
                }
            }
            if (indexEnd == 0)
            {
                indexEnd = optic.Count - 1;
                sizeOptic = indexEnd - indexStart + 1;
            }

            Console.WriteLine("Start {0}, End {1}", indexStart, indexEnd);

            double[] targetAzimutOptic = new double[sizeOptic];
            double[] targetUgolMestaOptic = new double[sizeOptic];
            double[] targetTimeOptic = new double[sizeOptic];
            for (int i = indexStart, j = 0; i < indexEnd; i++, j++)
            {
                targetAzimutOptic[j] = optic[i].getAzimut();
                targetUgolMestaOptic[j] = optic[i].getUgolMesta();
                targetTimeOptic[j] = optic[i].getTime();

                if (targetAzimutOptic[j] > 6)
                {
                    targetAzimutOptic[j] = targetAzimutOptic[j] - (360 * Math.PI / 180);
                }
            }

            MNK mnkOpticAzimut = new MNK(targetTimeOptic, targetAzimutOptic, sizeOptic);
            double[] answerOpticAzimut = mnkOpticAzimut.Calculate();

            MNK mnkOpticUgolMesta = new MNK(targetTimeOptic, targetUgolMestaOptic, sizeOptic);
            double[] answerOpticUgolMesta = mnkOpticUgolMesta.Calculate();
            Console.WriteLine("Optic");
            for (int i = 1; i >= 0; i--)
            {
                Console.WriteLine(answerOpticAzimut[i] + "\t" + answerOpticUgolMesta[i]);
            }

            Console.WriteLine("DELTA");

            double[] statisticAzimut = getStatistic(answerLocalAzimut, targetAzimutOptic, targetTimeOptic, sizeOptic);
            double[] statisticUgolMesta = getStatistic(answerLocalUgolMesta,targetUgolMestaOptic, targetTimeOptic, sizeOptic);

            Console.WriteLine("Мат. ожидание\t{0}\t{1}", statisticAzimut[0], statisticUgolMesta[0]);
            Console.WriteLine("Отклонение\t{0}\t{1}", statisticAzimut[1], statisticUgolMesta[1]);

            Console.WriteLine("\n/////////////////////////////////////////////////\n");

            ProcessStartInfo start = new ProcessStartInfo();
            start.FileName = pythonScriptString;

        }

        private static double[] getStatistic(double[] answerLocal, double[] targetOptic, double[] targetTime, int size)
        {
            /*
             * statistic[0] = matOjid; 
             * statistic[1] = dispersia;
             * 
             */
            double[] statistic = new double[2];
            double matOjidDeltaPower2 = 0;

            double[] deltaVectorAzimut = new double[size];

            for (int i = 0; i < size; i++)
            {
                deltaVectorAzimut[i] = (answerLocal[1] * targetTime[i] + answerLocal[0]) - targetOptic[i];
                statistic[0] += deltaVectorAzimut[i];
                matOjidDeltaPower2 += Math.Pow(deltaVectorAzimut[i], 2);
            }

            statistic[0] /= size;
            matOjidDeltaPower2 /= size;

            statistic[1] = Math.Sqrt(matOjidDeltaPower2 - Math.Pow(statistic[0], 2));

            return statistic;
        }
    }
}
