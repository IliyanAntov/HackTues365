using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace Generator {
    public partial class Form1 : Form {
        SerialPort port;
        RandomizeButtonGame ButtonGameValues;
        RandomizeMorseCodeGame MorseCodeGameValues;
        RandomizeSimonSaysGame SimonSaysGameValues;

        char[] colors = new char[] { 'r', 'g', 'b', 'y' };

        public Form1() {
            InitializeComponent();                // begin the Forms App
            port = new SerialPort("COM3", 9600);  // define a serial connection on COM3 @ 9600 baud rate
            port.Open();                          // open the serial connection

            button1.Text = "Generate";            // Initialize the text for the button and label
            label1.Text = "";
            label2.Text = "";
            label3.Text = "Click \"Generate\" to begin";
            label4.Text = "";
        }

        private List<char> FormatData(RandomizeButtonGame bg, RandomizeMorseCodeGame mcg, RandomizeSimonSaysGame ssg) {  // format data for Arduino
            List<char> rows = new List<char>();
            char[] word = mcg.Word.ToArray();

            // <----- Button Game -----> //

            char color = colors[bg.Index];
            char digit = Converter.DecToHex(bg.TimeValues[bg.Index]);

            rows.Add(color);  // pick the chosen color
            rows.Add(digit);  // pick the chosen digit

            // <------ Morse Code -----> //

            char index = Converter.DecToHex(mcg.Indexes[mcg.IntIndex]);
            rows.Add(index);  // add MCG index of the word

            for (int i = 0; i < word.Length; i++) {  // add MCG word as seperate rows
                rows.Add(word[i]);
            }

            // <------ Simon Says -----> //

            for (int i = 0; i < ssg.Nums.Count; i++) {
                char currentNum = Converter.DecToHex(ssg.Nums[i]);
                rows.Add(currentNum);
            }

            for (int i = 0; i < ssg.Sequence.Count; i++) {
                char currentElement = Converter.DecToHex(ssg.Sequence[i]);
                rows.Add(currentElement);
            }

            return rows;
        }

        private string ButtonGameRows(RandomizeButtonGame bg) {         // format button game instructions
            StringBuilder ButtonGamesb = new StringBuilder();           
            string ButtonGameHeading = "Button Game \n\n";              
            string ButtonGameHead = "{LED} -> {Release on digit}\n";

            ButtonGamesb.Append(ButtonGameHeading);
            ButtonGamesb.Append(ButtonGameHead);

            for (int i = 0; i < colors.Length; i++) {
                string currentColor = Converter.CharToStr(colors[i]);
                int currentTimeValue = bg.TimeValues[i];

                ButtonGamesb.Append($"{currentColor} Color -> {currentTimeValue} \n");
            }     

            return ButtonGamesb.ToString();
        }

        private string MorseCodeGameRows(RandomizeMorseCodeGame mcg) {
            StringBuilder MorseCodeGamesb = new StringBuilder();
            string MorseCodeGameHeading = "Morse Code Game \n\n";
            string MorseCodeGameHead = "{Word} -> {Character to enter}\n";

            MorseCodeGamesb.Append("\n");
            MorseCodeGamesb.Append(MorseCodeGameHeading);
            MorseCodeGamesb.Append(MorseCodeGameHead);

            for (int i = 0; i < mcg.Words.Count; i++) {
                string word = mcg.Words[i].ToUpper();
                int index = mcg.Indexes[i];

                MorseCodeGamesb.Append($"{word} -> {Converter.DecToHex(index)} \n");
            }

            return MorseCodeGamesb.ToString();
        }

        private string SimonSaysGameRows(RandomizeSimonSaysGame ssg) {
            StringBuilder SimonSaysGamesb = new StringBuilder();
            string SimonSaysGameHeading = "Simon Says Game \n\n";
            string SimonSaysGameHead = "{Blinking LED} -> {Button to press}\n";

            SimonSaysGamesb.Append(SimonSaysGameHeading);
            SimonSaysGamesb.Append(SimonSaysGameHead);

            for (int i = 0; i < ssg.Nums.Count; i++) {
                string currentLED = Converter.CharToStr(colors[i]);
                string currentButton = Converter.CharToStr(colors[ssg.Nums[i]]);

                SimonSaysGamesb.Append($"{currentLED} LED -> {currentButton} Button\n");
            }

            SimonSaysGamesb.Append(String.Join(",", ssg.Sequence));

            return SimonSaysGamesb.ToString();
        }

        private void Generate() {
            char[] values = new char[16] { 'r', '2', '3', 'f', 'o', 'x', '0', '1', '2', '3', '2', '1', '3', '0', '1', '2' };
            List<char> hc = new List<char>(values.ToList());
            List<char> rows = new List<char>();  // collection of all rows for the arduino

            // <----- Create sets of values -----> //

            ButtonGameValues = new RandomizeButtonGame();
            MorseCodeGameValues = new RandomizeMorseCodeGame();
            SimonSaysGameValues = new RandomizeSimonSaysGame();

            // <----- Copy data ------> //

            rows.AddRange(FormatData(ButtonGameValues, MorseCodeGameValues, SimonSaysGameValues));

            // <----- Send data ------> //

            for (int i = 0; i < rows.Count; i++) {
                string currentRow = values[i].ToString();
                port.Write(currentRow);

                while (port.ReadExisting() != "1") {
                    Thread.Sleep(10);
                }
            }

            // <----- Display text -----> //

            label1.Text = ButtonGameRows(ButtonGameValues);
            label2.Text = SimonSaysGameRows(SimonSaysGameValues);
            label3.Text = MorseCodeGameRows(MorseCodeGameValues);
            label4.Text = String.Join(", ", rows);
        }

        private void Form1_Load(object sender, EventArgs e) {

        }

        private void button1_Click(object sender, EventArgs e) {  // button click event listener
            Generate();
        }

        private void label1_Click(object sender, EventArgs e) {

        }

        private void label3_Click(object sender, EventArgs e) {

        }

        private void label4_Click(object sender, EventArgs e) {

        }
    }
}

// <----- Button Game ----->
// row1 -> RGB Color
// row2 -> Wanted Digit
// 
// <----- Morse Code Game ----->
//
// row3 -> Word index
// row4-row6 -> word
//
// <----- Simon Says Game ----->
//
// row7-row10 -> button order
// row11-row16 -> sequence
