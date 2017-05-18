using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MNK2dim
{
    public partial class Graph : Form
    {
        private double[] answer;
        private double[] targetTimeOptic;
        private double[] targetMeasureOptic;
        public Graph(double[] answer, double[] targetTimeOptic, double[] targetMeasureOptic)
        {
            InitializeComponent();
            
            this.answer = answer;
            this.targetTimeOptic = targetTimeOptic;
            this.targetMeasureOptic = targetMeasureOptic;
            DrawGraph();
        }

        public void DrawGraph()
        {
            for (int i = 0; i < targetTimeOptic.Length; i++)
            {
                Console.WriteLine(targetTimeOptic[i] + "\t" + targetMeasureOptic[i]);

            }

            chart.Series[0].Points.Clear();
            chart.ResetAutoValues();
            //chart.ChartAreas[0].AxisX.Minimum = targetTimeOptic[0];
            //chart.ChartAreas[0].AxisX.Maximum = targetTimeOptic[targetTimeOptic.Length - 1];
            
            //double[] x = { 0, 1, 2, 3 };
            //double[] y = { 0, 1, 2, 3 };

            for (int i = 0; i < targetTimeOptic.Length; i++)
            {
                chart.Series[0].Points.AddXY(targetTimeOptic[i], targetMeasureOptic[i]);
            }
            chart.Series[0].Points.RemoveAt(chart.Series[0].Points.Count - 1);

            double[] y = new double[targetTimeOptic.Length];

            for (int i = 0; i < y.Length; i++)
            {
                y[i] = answer[1] * targetTimeOptic[i] + answer[0];

                chart.Series[1].Points.AddXY(targetTimeOptic[i], y[i]);
            }
            chart.Series[1].Points.RemoveAt(chart.Series[1].Points.Count - 1);
        }
    }
}
