using Microsoft.Office.Interop.Excel;
using System;
using System.Linq;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;

namespace MNK2dim
{
    class Program
    {

        //const

        const int sizeLocal = 5;
        const int e = 2; //Для округления времени
        const int minTime = 3; //Для нахождения ближайшего по времени измерения


        //Radio
        static List<Measure> radioAzimut = new List<Measure>();
        static List<Measure> radioUgolMesta = new List<Measure>();

        static List<Measure> range = new List<Measure>();
        //Optic
        static List<Measure> opticAzimut = new List<Measure>();
        static List<Measure> opticUgolMesta = new List<Measure>();

        static String pythonScriptString = @"/../graph.py";

        /// <summary>
        /// Возвращет требуемую колонну таблицы
        /// </summary>
        /// <param name="ws">Имя листа</param>
        /// <param name="i">Номер колонны</param>
        /// <param name="skipZero">Пропуск нулевых значений</param>
        /// <returns></returns>
        static double[] getExcelColumn(Worksheet ws, int i, bool skipZero)
        {
            Range range = ws.UsedRange.Columns[i];
            Array arr = (Array)range.Cells.Value;

            List<Measure> measures = new List<Measure>();

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
            var xlsApp = new Microsoft.Office.Interop.Excel.Application();

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


            double[] azimutLocalVector = getExcelColumn(ws, 9, false);
            double[] timeLocalVector = getExcelColumn(ws, 2, false);
            double[] rangeVector = getExcelColumn(ws, 23, false);

            for (int i = 0; i < azimutLocalVector.Length; i++)
            {
                if (azimutLocalVector[i] != 0)
                {
                    azimutLocalVector[i] = azimutLocalVector[i] * Math.PI / 180;
                    radioAzimut.Add(new Measure(Math.Round(timeLocalVector[i], e), azimutLocalVector[i]));
                    
                }
            }

            double[] ugolMestaLocalVector = getExcelColumn(ws, 10, false);

            for (int i = 0; i < ugolMestaLocalVector.Length; i++)
            {
                if (ugolMestaLocalVector[i] != 0)
                {
                    ugolMestaLocalVector[i] = ugolMestaLocalVector[i] * Math.PI / 180;
                    radioUgolMesta.Add(new Measure(Math.Round(timeLocalVector[i], e), ugolMestaLocalVector[i]));
                }
            }

            for (int i = 0; i < rangeVector.Length; i++)
            {
                if (rangeVector[i] != 0)
                    range.Add(new Measure(Math.Round(timeLocalVector[i], e), rangeVector[i]));
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
                opticAzimut.Add(new Measure(timeOpticVector[i], azimutOpticVector[i]));
                opticUgolMesta.Add(new Measure(timeOpticVector[i], ugolMestaOpticVector[i]));
            }

            CalculateByRange(20000);
            CalculateByRange(10000);
            CalculateByRange(5000);
            CalculateByRange(3000);
            CalculateByRange(2000);
            CalculateByRange(1200);

            //getSkolz(20000, 5);

            Console.ReadKey();
        }

        private static void getSkolz(double rang, int steps)
        {
            int stepCount = 0;
            int sizeLocal = 5;
            List<double> timeArr = new List<double>();
            List<double> azimutArr = new List<double>();
            double targetTimeStart;

            int temp = 0;
            for (int i = 0; i < range.Count; i++)
            {
                if (range[i].getMeasure() == rang)
                {
                    targetTimeStart = range[i].getMeasure();
                
                    temp = getNearest(radioAzimut, range[i].getTime());
                    for (int j = 0; j < sizeLocal; j++)
                    {

                        timeArr.Add(radioAzimut[temp].getTime());
                        azimutArr.Add(radioAzimut[temp].getMeasure());

                        temp++;
                        if (azimutArr[j] > 6)
                        {
                            azimutArr[j] = azimutArr[j] - (360 * Math.PI / 180);
                        }
                    }
                    
                }
            }

            for (int i = 0; i < steps; i++)
            {
                MNK mnkLocalAzimut = new MNK(timeArr.ToArray(), azimutArr.ToArray(), sizeLocal);
                double[] answerLocalAzimut = mnkLocalAzimut.Calculate();

                //Console.WriteLine(answerLocalAzimut[1] + "\t" + answerLocalAzimut[0]);
                Console.WriteLine("{0:E}\t{1:E}", answerLocalAzimut[1], answerLocalAzimut[0]);
                timeArr.RemoveAt(0);
                timeArr.Add(radioAzimut[temp].getTime());

                azimutArr.RemoveAt(0);
                azimutArr.Add(radioAzimut[temp].getMeasure());

                temp++;
            }
        }
        
        /// <summary>
        /// Класс нахождения номера элемента списка list с ближайшем временем относительно параметра targetTime
        /// </summary>
        /// <param name="list">Список, требующий нахождения ближайшего коэффициента</param>
        /// <param name="targetTime">Целевое время</param>
        /// <returns>Возвращает номер элемента списка с ближайшим времение, иначе возвращает 0</returns>
        static int getNearest(List<Measure> list, double targetTime)
        {
            double MAX = Double.MaxValue;

            for (int i = 0; i < list.Count; i++)
            {
                if (Math.Abs(targetTime - list[i].getTime()) < minTime)
                {
                    if (MAX >= Math.Abs(targetTime - list[i].getTime()))
                    {
                        MAX = Math.Abs(targetTime - list[i].getTime());
                        
                    }
                    else
                    {
                        return i - 1;
                    }
                }
            }

            //Hope never return
            return 0;
        }

        /// <summary>
        /// Собирает и выводит статистику по заданному расстоянию
        /// </summary>
        /// <param name="rang">Целевое расстояние</param>
        /// 
        static void CalculateByRange(double rang)
        {
            Console.WriteLine("Расстояние = " + rang);
            int sizeLocal = 5;
            
            double[] targetAzimutLocal = new double[sizeLocal];
            double[] targetUgolMestaLocal = new double[sizeLocal];
            double[] targetTimeAzimutLocal = new double[sizeLocal];
            double[] targetTimeUgolMestaLocal = new double[sizeLocal];

            double targetTimeStart = 0;
            double targetTimeEnd = 0;
            for (int i = 0; i < range.Count; i++)
            {
                if (range[i].getMeasure() == rang)
                {
                    targetTimeStart = range[i].getTime();
                    if (range.Count - 1 - i <= sizeLocal)
                    {
                        sizeLocal = range.Count - i - 1;
                        targetAzimutLocal = new double[sizeLocal];
                        targetUgolMestaLocal = new double[sizeLocal];
                        targetTimeAzimutLocal = new double[sizeLocal];
                    }

                    //int tempI = i;
                    int temp = getNearest(radioAzimut, range[i].getTime());
                    for (int j = 0; j < sizeLocal; j++)
                    {
                        targetTimeAzimutLocal[j] = radioAzimut[temp].getTime() - targetTimeStart;
                        targetAzimutLocal[j] = radioAzimut[temp].getMeasure();
                        temp++;

                        if (targetAzimutLocal[j] > 6)
                        {
                            targetAzimutLocal[j] = targetAzimutLocal[j] - (360 * Math.PI / 180);
                        }
                    }

                    targetTimeEnd = Math.Round(Math.Max(targetTimeEnd, targetTimeAzimutLocal[sizeLocal - 1] + targetTimeStart), 2);


                    temp = getNearest(radioUgolMesta, range[i].getTime());

                    //Если temp = 0 => не нашлись измерения в диапазоне < minTime секунд
                    if (temp == 0)
                    {
                        Console.WriteLine("ИЗМЕРЕНИЯ УГЛА МЕСТА ОТСУТСТВУЮТ");
                    }
                    //
                    for (int j = 0; j < sizeLocal; j++)
                    {
                        targetTimeUgolMestaLocal[j] = radioUgolMesta[temp].getTime() - targetTimeStart;
                        targetUgolMestaLocal[j] = radioUgolMesta[temp].getMeasure();
                        temp++;
                    }
                
                    targetTimeEnd = Math.Round(Math.Max(targetTimeEnd, targetTimeUgolMestaLocal[sizeLocal - 1] + targetTimeStart), 2);
             

                    break;
                }
            }

            for (int i = 0; i < targetAzimutLocal.Length; i++)
            {
                //Console.WriteLine(targetAzimutLocal[i]);
            }

            int sizeOptic = 100;
            int indexStart = 0;
            int indexEnd = 0;
            indexStart = getNearest(opticAzimut, targetTimeStart);
            indexEnd = getNearest(opticAzimut, targetTimeEnd);
            sizeOptic = indexEnd - indexStart + 1;
            

            Console.WriteLine("Start {0}, End {1}", indexStart, indexEnd);

            double[] targetAzimutOptic = new double[sizeOptic];
            double[] targetUgolMestaOptic = new double[sizeOptic];
            double[] targetTimeOptic = new double[sizeOptic];

            for (int i = indexStart, j = 0; i < indexEnd; i++, j++)
            {
                targetAzimutOptic[j] = opticAzimut[i].getMeasure();
                targetUgolMestaOptic[j] = opticUgolMesta[i].getMeasure();
                targetTimeOptic[j] = opticAzimut[i].getTime() - targetTimeStart;

                if (targetAzimutOptic[j] > 6)
                {
                    targetAzimutOptic[j] = targetAzimutOptic[j] - (360 * Math.PI / 180);
                }
            }

            MNK mnkLocalAzimut = new MNK(targetTimeAzimutLocal, targetAzimutLocal, sizeLocal);
            double[] answerLocalAzimut = mnkLocalAzimut.Calculate();

            MNK mnkLocalUgolMesta = new MNK(targetTimeUgolMestaLocal, targetUgolMestaLocal, sizeLocal);
            double[] answerLocalUgolMesta = mnkLocalUgolMesta.Calculate();

            Console.WriteLine("Radio");
            for (int i = 1; i >= 0; i--)
            {
                Console.WriteLine(answerLocalAzimut[i] + "\t" + answerLocalUgolMesta[i]);
            }

            MNK mnkOpticAzimut = new MNK(targetTimeOptic, targetAzimutOptic, sizeOptic);
            double[] answerOpticAzimut = mnkOpticAzimut.Calculate();

            MNK mnkOpticUgolMesta = new MNK(targetTimeOptic, targetUgolMestaOptic, sizeOptic);
            double[] answerOpticUgolMesta = mnkOpticUgolMesta.Calculate();

            Console.WriteLine("//////////////////////////////////////////////\n");
            for (int i = 0; i < targetAzimutLocal.Length; i++)
            {
                Console.WriteLine(targetAzimutLocal[i]);
            }
            Console.WriteLine("\n///////////////////////////////////////////////");

            Console.WriteLine("DELTA");


            double[] statisticAzimut = getStatistic(answerLocalAzimut, targetAzimutOptic, targetTimeOptic, sizeOptic);
            double[] statisticUgolMesta = getStatistic(answerLocalUgolMesta, targetUgolMestaOptic, targetTimeOptic, sizeOptic);

            Console.WriteLine("Мат. ожидание\t{0}\t{1}", statisticAzimut[0], statisticUgolMesta[0]);
            Console.WriteLine("Отклонение\t{0}\t{1}", statisticAzimut[1], statisticUgolMesta[1]);

            Console.WriteLine("\n///////////////////////////////////////////////\n");

            //ProcessStartInfo start = new ProcessStartInfo();
            //start.FileName = pythonScriptString;


            ShowGraph(answerLocalAzimut, targetTimeOptic, targetAzimutOptic, targetTimeAzimutLocal, targetAzimutLocal);
            Console.ReadKey();
        }

        [STAThread]
        private static void ShowGraph(double[] answer, double[] targetTimeOptic, double[] targetMeasureOptic, double[] targetTimeLocal, double[] targetMeasureLocal)
        {
            //Graph
            System.Windows.Forms.Application.EnableVisualStyles();
            System.Windows.Forms.Application.Run(new Graph(answer, targetTimeOptic, targetMeasureOptic, targetTimeLocal, targetMeasureLocal));
            //graph.DrawGraph();
        }

        private static double[] getStatistic(double[] answerLocal, double[] targetOptic, double[] targetTime, int size)
        {
            /*
             * statistic[0] = matOjid; 
             * statistic[1] = dispersia
             */
            double[] statistic = new double[2];
            double matOjidDeltaPower2 = 0;

            double[] deltaVectorAzimut = new double[size];

            for (int i = 0; i < size; i++)
            {
                //Console.WriteLine(answerLocal[1] * targetTime[i] + answerLocal[0] + "\t" + targetOptic[i] + "\t" + i);
                deltaVectorAzimut[i] = (answerLocal[1] * targetTime[i] + answerLocal[0]) - targetOptic[i];
                statistic[0] += deltaVectorAzimut[i];
                matOjidDeltaPower2 += Math.Pow(deltaVectorAzimut[i], 2);
            }

            //Console.WriteLine();
            for (int i = 0; i < size; i++)
            {
                //Console.WriteLine(deltaVectorAzimut[i] + "\t" + i);
            }


            statistic[0] /= size;
            matOjidDeltaPower2 /= size;

            statistic[1] = Math.Sqrt(matOjidDeltaPower2 - Math.Pow(statistic[0], 2));

            return statistic;
        }
    }
}
