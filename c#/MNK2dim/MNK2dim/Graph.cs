using System.Windows.Forms;
using System;
using System.Linq;

namespace MNK2dim
{
    public partial class Graph : Form
    {
        private double[] answer;
        private double[] targetTimeOptic;
        private double[] targetMeasureOptic;

        private double[] targetTimeLocal;
        private double[] targetMeasureLocal;
 
        public Graph(double[] answer, double[] targetTimeOptic, double[] targetMeasureOptic)
        {
            InitializeComponent();
            
            this.answer = answer;
            this.targetTimeOptic = targetTimeOptic;
            this.targetMeasureOptic = targetMeasureOptic;
            chart.ChartAreas[0].AxisY.Minimum = targetMeasureOptic[0] - 0.004;
            chart.ChartAreas[0].AxisY.Maximum = targetMeasureOptic[0] + 0.004;
            chart.ChartAreas[0].AxisY.Interval = 0.001;
            DrawGraph(false);
        }

        public Graph(double[] answer, double[] targetTimeOptic, double[] targetMeasureOptic, double[] targetTimeLocal, double[] targetMeasureLocal)
        {
            InitializeComponent();
            this.answer = answer;
            this.targetMeasureOptic = targetMeasureOptic;
            this.targetTimeOptic = targetTimeOptic;
            this.targetTimeLocal = targetTimeLocal;
            this.targetMeasureLocal = targetMeasureLocal;

            targetMeasureOptic = targetMeasureOptic.Where(val => val != 0).ToArray();

            double max = targetMeasureOptic.Max();

            if (max < targetMeasureLocal.Max())
                max = targetMeasureLocal.Max();

            double min = targetMeasureOptic.Min();

            if (min > targetMeasureLocal.Min())
                min = targetMeasureLocal.Min();

            chart.ChartAreas[0].AxisY.Minimum = min;
            chart.ChartAreas[0].AxisY.Maximum = max;

            chart.ChartAreas[0].AxisX.Minimum = 0;
            chart.ChartAreas[0].AxisX.Maximum = targetTimeLocal.Max();

            DrawGraph(true);
        }

        public void DrawGraph(bool full)
        {
            chart.Series[0].Points.Clear();
            chart.ResetAutoValues();
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
            chart.Series[1].BorderWidth = 5;
            chart.Series[1].Points.RemoveAt(chart.Series[1].Points.Count - 1);

            if (full)
            {
                chart.Series[2].Points.Clear();
                for (int i = 0; i < targetTimeLocal.Length; i++)
                {
                    chart.Series[2].Points.AddXY(targetTimeLocal[i], targetMeasureLocal[i]);
                }
            }
        }
    }
}
