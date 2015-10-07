using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DFT
{
    class Complex
    {
        public double Re;
        public double Im;

        public double GetModule()
        {
            return Math.Sqrt(this.Re*this.Re + this.Im*this.Im);
        }

        public String Show()
        {
            return Re + " + " + Im + "i";
        }      
    }
}
