using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MNK
{
    public partial class MNKform : Form
    {
        public MNKform()
        {
            InitializeComponent();

            //int size = 4;

            //double[] xVector = new double[size];
            //double[] yVector = new double[size];
            //double[] zVector = new double[size];
            //double[] wVector = new double[size];

            //Console.WriteLine("XVector");
            //for(int i = 0; i < size; i++)
            //{
            //    xVector[i] = double.Parse(Console.ReadLine());
            //    wVector[i] = 1;
            //}

            //Console.WriteLine("YVector");
            //for (int i = 0; i < size; i++)
            //{
            //    yVector[i] = double.Parse(Console.ReadLine());
            //}

            //Console.WriteLine("ZVector");
            //for (int i = 0; i < size; i++)
            //{
            //    zVector[i] = double.Parse(Console.ReadLine());
            //}

            //int[] polynomeSize = new int[2];
            //polynomeSize[0] = 1;
            //polynomeSize[1] = 1;

            //Console.WriteLine("Answer");
            //MNK mnk = new MNK(xVector, yVector, zVector, wVector, size, polynomeSize);
            //mnk.Calculate();
        }

        private void MNKform_Load(object sender, EventArgs e)
        {

        }

        private void EditCount_TextChanged(object sender, EventArgs e)
        {
            if (XLayoutPanel.Controls.Count != 0)
            {
                XLayoutPanel.Controls.Clear();
                YLayoutPanel.Controls.Clear();
                ZLayoutPanel.Controls.Clear();
                WLayoutPanel.Controls.Clear();
            }

            int size;
            try
            {
                size = int.Parse(EditCount.Text);
            }
            catch(Exception)
            {
                return;
            }

            for (int i = 0; i < size; i++)
            {
                TextBox Xtext = new TextBox();
                TextBox Ytext = new TextBox();
                TextBox Ztext = new TextBox();
                TextBox Wtext = new TextBox();

                Xtext.Text = 0.ToString();
                Xtext.TextAlign = HorizontalAlignment.Center;
                Ytext.Text = 0.ToString();
                Ytext.TextAlign = HorizontalAlignment.Center;
                Ztext.Text = 0.ToString();
                Ztext.TextAlign = HorizontalAlignment.Center;
                Wtext.Text = 1.ToString();
                Wtext.TextAlign = HorizontalAlignment.Center;

                XLayoutPanel.Controls.Add(Xtext);
                YLayoutPanel.Controls.Add(Ytext);
                ZLayoutPanel.Controls.Add(Ztext);
                WLayoutPanel.Controls.Add(Wtext);
            }


            TableLayoutRowStyleCollection[] styles = new TableLayoutRowStyleCollection[4];
            styles[0] = XLayoutPanel.RowStyles;
            styles[1] = YLayoutPanel.RowStyles;
            styles[2] = ZLayoutPanel.RowStyles;
            styles[3] = WLayoutPanel.RowStyles;

            for (int i = 0; i < 4; i++)
            {
                foreach(RowStyle style in styles[i])
                {
                    style.SizeType = SizeType.Percent;
                    style.Height = 1.0f / size;
                }
            }
        }

        private void MNK_button_Click(object sender, EventArgs e)
        {
            if (answerLayout.Controls.Count != 0)
                answerLayout.Controls.Clear();

            int size = int.Parse(EditCount.Text);
            double[] x = new double[size];
            double[] y = new double[size];
            double[] z = new double[size];
            double[] w = new double[size];

            for (int i = 0; i < size; i++)
            {
                try
                {
                    x[i] = double.Parse(XLayoutPanel.Controls[i].Text);
                    y[i] = double.Parse(YLayoutPanel.Controls[i].Text);
                    z[i] = double.Parse(ZLayoutPanel.Controls[i].Text);
                    w[i] = double.Parse(WLayoutPanel.Controls[i].Text);
                }
                catch(Exception)
                {
                    return;
                }
            }

            int[] polynomeSize = new int[2];
            polynomeSize[0] = 1;
            polynomeSize[1] = 1;

            MNK mnk = new MNK(x, y, z, w, size, polynomeSize);
            double[] answer = mnk.Calculate();

            var results = new TextBox[3];
            for (int i = 0; i < 3; i++)
            {
                results[i] = new TextBox();
                results[i].MaxLength = 5;
                results[i].Text = answer[i].ToString();
                results[i].TextAlign = HorizontalAlignment.Center;
            }

            answerLayout.Controls.AddRange(results);
        }
    }
}
