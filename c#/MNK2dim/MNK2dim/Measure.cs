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
        private double meas;

        public Measure(double time, double meas)
        {
            this.time = time;
            this.meas = meas;
        }

        public double getTime()
        {
            return time;
        }

        public double getMeasure()
        {
            return meas;
        }
     }
}
