using System;
using System.Windows.Forms;

namespace DFT
{
    public partial class Graph : Form
    {
        Complex[] x;
        Complex[] y;
        private int N;

        public Graph()
        {
            InitializeComponent();
        }

        private void DrawGraph_Click(object sender, EventArgs e)
        {
            var a = Double.Parse(a_textBox.Text);
            var f = Double.Parse(f_textBox.Text);
            
            var fi = Double.Parse(fi_textBox.Text) * Math.PI / 180;
            N = Int32.Parse(n_textBox.Text);

            ComputeX(a, f, fi);
            computeDFT();
            DrawGraph();
            //MessageBox.Show(y[0].Show() + '\n' + y[0].GetModule().ToString());
        }

        private void DrawGraph()
        {
            Graphic.Series["DFT"].Points.Clear();
            
            
            double max = 0;
            
            for (int i = 0; i < N; i++)
            {
                if (y[i].GetModule() > max)
                {
                    max = y[i].GetModule();
                }
            }
            
            Graphic.ChartAreas[0].AxisY.Maximum = max;
            

            for (int i = 0; i < N; i++)
            {
                Graphic.Series["DFT"].Points.AddXY(i, y[i].GetModule());
            }
        }

        private void ComputeX(double a, double f, double fi)
        {
            Complex E = new Complex();
            Random random = new Random();

            x = new Complex[N];
            y = new Complex[N];

            for (int i = 0; i < N; i++)
            {
                if (noise_yes.Checked)
                {
                    E.Re = random.NextDouble();
                    E.Im = random.NextDouble();
                }

                else if (noise_no.Checked)
                {   
                    E.Re = 0;
                    E.Im = 0;
                }

                x[i] = new Complex();

                double angle = (2 * Math.PI * f * i)/N + fi;
                
                x[i].Re = a * Math.Cos(angle) + E.Re;
                x[i].Im = a * Math.Sin(angle) + E.Im;
            }
        }

        private void computeDFT()
        {
            for (int k = 0; k < N; k++)
            {
                double sumreal = 0;
                double sumimag = 0;
                y[k] = new Complex();

                for (int n = 0; n < N; n++)
                {
                    double angle = (2 * Math.PI * n * k) / N;
                    sumreal += x[n].Re * Math.Cos(angle) + x[n].Im * Math.Sin(angle);
                    sumimag += -x[n].Re * Math.Sin(angle) + x[n].Im * Math.Cos(angle);
                }
                y[k].Re = sumreal;
                y[k].Im = sumimag;
            }
            
        }
    }
}
