using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Generator {
    class RandomizeMorseCodeGame : Randomize {
        private int intIndex;
        private char index;
        private string word;

        private string[] words = new string[] {"joy", "zip", "jog", "fox", "max",
                                               "cup", "gym", "car", "fax", "axe",
                                               "dog", "pit", "red", "awe", "bed"};

        private List<int> indexes = new List<int>();

        public RandomizeMorseCodeGame() {
            IntIndex = RandomNumber(0, Words.Count);
            Word = Words[IntIndex];
            Indexes = CreateUniqueList(0, 16, 15);
        }
            
        public int IntIndex {
            get { return intIndex; }
            private set { intIndex = value; }
        }

        public char Index {
            get { return Converter.DecToHex(index); }
            private set { index = value; }
        }

        public List<int> Indexes {
            get { return indexes; }
            private set { indexes = value; }
        }

        public string Word {
            get { return word; }
            private set { word = value; }
        }

        public List<string> Words {
            get { return words.ToList(); }
        }
    }
}
