using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Generator {
    public class RandomizeButtonGame {
        private List<int> timeValues;
        private int index;

        public RandomizeButtonGame() {
            TimeValues = GenerateRandomNumbers();

            Index = RandomNumber(0, 4);
        }
           
        public List<int> TimeValues {
            get { return timeValues; }
            private set { timeValues = value; }
        }

        public int Index {
            get { return index; }
            private set { index = value; }
        }

        public List<int> GenerateRandomNumbers() {
            Random random = new Random();
            int num = 11111;

            while (CheckRepeatingDigits(num)) {
                num = random.Next(1000, 10000);
            }

            return IntToList(num);
        }

        public int RandomNumber(int min, int max) {
            Random random = new Random();
            return random.Next(min, max);
        }

        private bool CheckRepeatingDigits(int num) {
            List<int> digits = IntToList(num);

            return digits.GroupBy(n => n).Any(c => c.Count() > 1);
        }

        private List<int> IntToList(int n) {
            List<int> digits = new List<int>();

            while (n > 0) {
                digits.Add(n % 10);
                n /= 10;
            }

            return digits;
        }
    }
}
