using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MNK2dim
{
    class Measure
    {
        private double time;
        private double azimut;
        private double ugolMesta;
        private double range;

        public Measure(double time, double azimut, double ugolMesta)
        {
            this.time = time;
            this.azimut = azimut;
            this.ugolMesta = ugolMesta;
        }

        public Measure(double time, double azimut, double ugolMesta, double range)
        {
            this.time = time;
            this.azimut = azimut;
            this.ugolMesta = ugolMesta;
            this.range = range;
        }

        public double getTime()
        {
            return time;
        }

        public double getAzimut()
        {
            return azimut;
        }

        public double getUgolMesta()
        {
            return ugolMesta;
        }

        public double getRange()
        { 
            return range;
        }
     }
}
