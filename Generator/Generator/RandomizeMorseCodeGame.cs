using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Generator {
    class RandomizeMorseCodeGame : Randomize {
        private int index;
        private string word;

        public int Index {
            get { return index; }
            private set { index = value; }
        }

        public string Word {
            get { return word; }
            private set { word = value; }
        }

        public List<string> Words {
            get { return base.Words; }
        }

        public RandomizeMorseCodeGame() {
            Index = RandomNumber(0, Words.Count);
            Word = Words[Index];
        }
    }
}
