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

        protected bool CheckRepeatingDigits(int num, int p) {
            List<int> digits = ReturnDigits(num, p);

            return digits.GroupBy(n => n).Any(c => c.Count() > 1);
        }

        protected List<int> ReturnDigits(int n, int p) {
            List<int> digits = new List<int>();

            while (n > 0) {
                digits.Add(n % p);
                n /= 10;
            }

            return digits;
        }

        protected List<int> CreateUniqueList(int min, int max, int length) {
            List<int> nums = new List<int>();

            int temp = RandomNumber(min, max);

            for (int i = 0; i < length; i++) {
                while (nums.Contains(temp)) {
                    temp = RandomNumber(min, max);
                }

                nums.Add(temp);
            }

            return nums;
        }
    }
}