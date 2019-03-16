using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Generator {
    public class RandomizeButtonGame : Randomize {      
        private int index;
        private List<int> timeValues;

        public RandomizeButtonGame() {
            TimeValues = GenerateRandomNumbers();

            Index = RandomNumber(0, 4);
        }

        public int Index {
            get { return index; }
            private set { index = value; }
        }

        public List<int> TimeValues {
            get { return timeValues; }
            private set { timeValues = value; }
        }

        public List<int> GenerateRandomNumbers() {  // unique
            Random random = new Random();
            int num = 11111;

            while (CheckRepeatingDigits(num, 10)) {
                num = random.Next(1000, 10000);
            }

            return ReturnDigits(num, 10);
        }
    }
}
