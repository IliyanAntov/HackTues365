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

        public RandomizeMorseCodeGame() {
            IntIndex = RandomNumber(0, Words.Count);
            Word = Words[IntIndex];
        }
            
        public int IntIndex {
            get { return intIndex; }
            private set { intIndex = value; }
        }

        public char Index {
            get {
                switch(intIndex) {
                    case 10:
                        return 'a';
                    case 11:
                        return 'b';
                    case 12:
                        return 'c';
                    case 13:
                        return 'd';
                    case 14:
                        return 'e';
                    case 15:
                        return 'f';
                    default:
                        return (char)(IntIndex + '0');
                }
            }
            private set { index = value; }
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
