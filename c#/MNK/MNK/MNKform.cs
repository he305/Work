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

            int size = 4;

            double[] xVector = new double[size];
            double[] yVector = new double[size];
            double[] zVector = new double[size];
            double[] wVector = new double[size];

            Console.WriteLine("XVector");
            for(int i = 0; i < size; i++)
            {
                xVector[i] = double.Parse(Console.ReadLine());
                wVector[i] = 1;
            }

            Console.WriteLine("YVector");
            for (int i = 0; i < size; i++)
            {
                yVector[i] = double.Parse(Console.ReadLine());
            }

            Console.WriteLine("ZVector");
            for (int i = 0; i < size; i++)
            {
                zVector[i] = double.Parse(Console.ReadLine());
            }

            int[] polynomeSize = new int[2];
            polynomeSize[0] = 1;
            polynomeSize[1] = 1;

            Console.WriteLine("Answer");
            MNK mnk = new MNK(xVector, yVector, zVector, wVector, size, polynomeSize);
            mnk.Calculate();
        }

        private void button1_Click(object sender, EventArgs e)
        {
        }
    }
}
