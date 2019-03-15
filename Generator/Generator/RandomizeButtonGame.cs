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
            List<int> digits = new List<int>();

            Random random = new Random();
            int num = random.Next(0, 10000);

            for (int i = 0; i < 4; i++) {
                digits.Add(num % 10);
                num /= 10;
            }

            return digits;
        }

        public int RandomNumber(int min, int max) {
            Random random = new Random();
            return random.Next(min, max);
        }
    }
}
