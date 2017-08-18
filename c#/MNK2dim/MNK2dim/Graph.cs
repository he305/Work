using System.Windows.Forms;

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
