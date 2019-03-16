using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Generator {
    public class Randomize {
        public Randomize() {

        }

        protected int RandomNumber(int min, int max) {
            Random random = new Random();
            return random.Next(min, max);
        }

        protected bool CheckRepeatingDigits(int num) {
            List<int> digits = ReturnDigits(num);

            return digits.GroupBy(n => n).Any(c => c.Count() > 1);
        }

        protected List<int> ReturnDigits(int n) {
            List<int> digits = new List<int>();

            while (n > 0) {
                digits.Add(n % 10);
                n /= 10;
            }

            return digits;
        }
    }
}