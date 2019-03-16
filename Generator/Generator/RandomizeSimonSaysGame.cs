using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Generator {
    public class RandomizeSimonSaysGame : Randomize {
        private List<int> nums = new List<int>();
        private List<int> sequence = new List<int>();

        public RandomizeSimonSaysGame() {
            nums = CreateUniqueList(0, 4, 4);
            sequence = GenerateRandomNumbers();
        }

        public List<int> Nums {
            get { return nums; }
        }

        public List<int> Sequence {
            get { return sequence; }
        }

        public List<int> GenerateRandomNumbers() {  // non-unique
            Random random = new Random();
            int num = random.Next(100000, 1000000);

            return ReturnDigits(num, 4);
        }
    }
}
