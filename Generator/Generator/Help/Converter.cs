using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Generator {
    public static class Converter {
        public static char DecToHex(int n) {
            switch (n) {
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
                    return (char)(n + '0');
            }
        }

        public static string CharToStr(char input) {
            switch (input) {
                case 'r':
                    return "Red";
                case 'g':
                    return "Green";
                case 'b':
                    return "Blue";
                case 'y':
                    return "Yellow";
                default:
                    return "Error";
            }
        }
    }
}