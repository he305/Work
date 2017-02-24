using Microsoft.Office.Interop.Excel;
using System;
using System.Linq;
using System.Collections.Generic;

namespace MNK2dim
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(AppDomain.CurrentDomain.BaseDirectory);
            string filenameLocal = AppDomain.CurrentDomain.BaseDirectory + "radio.xlsx";
            string filenameOptic = AppDomain.CurrentDomain.BaseDirectory + "optic.xlsx";
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
            double[] timeLocalVector = timeLocalArr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();

            Range rangeColumn = ws.UsedRange.Columns[8];
            Array rangeArr = (Array)rangeColumn.Cells.Value;
            double[] rangeVector = rangeArr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();

            Range azimutLocalColumn = ws.UsedRange.Columns[9];
            Array azimutLocalArr = (Array)azimutLocalColumn.Cells.Value;
            double[] azimutLocalVector = azimutLocalArr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();
            
            for (int i = 0; i < azimutLocalVector.Length; i++)
            {
                azimutLocalVector[i] = azimutLocalVector[i] * Math.PI / 180;
                Console.WriteLine(timeLocalVector[i] + " " + azimutLocalVector[i]);
            }

            wb = xlsApp.Workbooks.Open(filenameLocal,
                0, true, 5, "", "", true, XlPlatform.xlWindows, "\t", false, false, 0, true);
            sheets = wb.Worksheets;
            ws = (Worksheet)sheets.get_Item(1);

            Range timeOpticColumn = ws.UsedRange.Columns[2];
            Array timeOpticArr = (Array)timeOpticColumn.Cells.Value;
            double[] timeOpticVector = timeOpticArr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();

            Range azimutOpticColumn = ws.UsedRange.Columns[9];
            Array azimutOpticArr = (Array)azimutOpticColumn.Cells.Value;
            double[] azimutOpticVector = azimutOpticArr.OfType<object>().Skip(1).Select(Convert.ToDouble).Where(o => o != 0).ToArray();

            ////////////////////
            int sizeLocal = 5;
            double[] targetAzimutLocal = new double[sizeLocal];
            double[] targetTimeLocal = new double[sizeLocal];
            for (int i = azimutLocalVector.Length - 1, j = 0; i >= azimutLocalVector.Length - 5; i--, j++)
            {
                targetAzimutLocal[j] = azimutLocalVector[i];
                targetTimeLocal[j] = timeLocalVector[i];
            }
            ////////////////////

            ///
            MNK mnkLocal = new MNK(targetTimeLocal, targetAzimutLocal, sizeLocal);
            double[] answerLocal = mnkLocal.Calculate();
            for (int i = 1; i >= 0; i--)
            {
                Console.WriteLine(answerLocal[i]);
            }


            int sizeOptic = 100;
            //////////////////////

            double[] targetAzimutOptic = new double[sizeOptic];
            double[] targetTimeOptic = new double[sizeOptic];
            for (int i = azimutOpticVector.Length - 1, j = 0; i >= azimutOpticVector.Length - 100; i--, j++)
            {
                targetAzimutOptic[j] = azimutOpticVector[i];
                targetTimeOptic[j] = timeOpticVector[i];
            }
            //////////////////////

            MNK mnkOptic = new MNK(targetTimeOptic, targetAzimutOptic, sizeOptic);
            double[] answerOptic = mnkOptic.Calculate();
            for (int i = 1; i >= 0; i--)
            {
                Console.WriteLine(answerOptic[i]);
            }

            Console.ReadKey();
        }
    }
}
