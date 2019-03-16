using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Generator {
    public class RandomizeButtonGame : Randomize {
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

            return ReturnDigits(num);
        }
    }
}
