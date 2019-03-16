using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
            InitializeComponent();  // begin the Forms App
            port = new SerialPort("COM3", 9600);  // define a serial connection on COM3 @ 9600 baud rate
            port.Open();  // open the serial connection

            button1.Text = "Generate";  // Initialize the text for the button and label
            label1.Text = "";
        }

        private void button1_Click(object sender, EventArgs e) {  // button click event listener
            char[] values = new char[16] { 'r', '2', '3', 'f', 'o', 'x',  '0', '1', '2', '3', '2', '1', '3', '0', '1', '2'};
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
                port.Write(hc[i].ToString());

                while (port.ReadExisting() != "1") {
                    Thread.Sleep(10);
                }
            }

            // <----- Display text -----> //

            label1.Text = ButtonGameRows(ButtonGameValues, MorseCodeGameValues, SimonSaysGameValues) + $" \n {rows[0]} {rows[1]}   {rows[2]} {rows[3]}{rows[4]}{rows[5]}";
        }

        private void label1_Click(object sender, EventArgs e) {

        }

        private List<char> FormatData(RandomizeButtonGame bg, RandomizeMorseCodeGame mcg, RandomizeSimonSaysGame ssg) {  // format data for Arduino
            List<char> rows = new List<char>();
            char[] word = mcg.Word.ToArray();

            // <----- Button Game -----> //

            rows.Add(colors[bg.Index]);  // pick the chosen color
            rows.Add((char)(bg.TimeValues[bg.Index] + '0'));  // pick the chosen digit

            // <------ Morse Code -----> //
            
            rows.Add(Converter.DecToHex(mcg.Indexes[mcg.IntIndex]));

            for (int i = 0; i < word.Length; i++) {  // add MCG word as seperate rows
                rows.Add(word[i]);
            }

            // <------ Simon Says -----> //

            for (int i = 0; i < ssg.Nums.Count; i++) {
                rows.Add((char) (ssg.Nums[i] + '0'));
            }

            for (int i = 0; i < ssg.Sequence.Count; i++) {
                rows.Add((char) (ssg.Sequence[i] + '0'));
            }

            return rows;
        }

        private string ButtonGameRows(RandomizeButtonGame bg, RandomizeMorseCodeGame mcg, RandomizeSimonSaysGame ssg) {  // format button game instructions
            StringBuilder sb = new StringBuilder();
            string ButtonGameHeading = "Button Game \n\n";
            string MorseCodeGameHeading = "Morse Code Game \n\n";
            string SimonSaysGameHeading = "Simon Says Game \n\n";

            // <----- Button Game -----> //

            sb.Append(ButtonGameHeading);

            for (int i = 0; i < colors.Length; i++) {
                sb.Append($"{colors[i]} -> {bg.TimeValues[i]} \n");
            }

            // <----- Morse Code -----> //

            sb.Append("\n");
            sb.Append(MorseCodeGameHeading);

            for (int i = 0; i < mcg.Words.Count; i++) {
                sb.Append($"{mcg.Indexes[i]} -> {mcg.Words[i]} \n");
            }

            // <------ Simon Says -----> //

            sb.Append("\n");
            sb.Append(SimonSaysGameHeading);

            for (int i = 0; i < ssg.Nums.Count; i++) {
                sb.Append($"{colors[i]} -> {ssg.Nums[i]}\n");
            }

            sb.Append(String.Join(",", ssg.Sequence));

            return sb.ToString();
        }
    }
}

// Button Game
// row1 -> RGB Color
// row2 -> Wanted Digit
// 
// Morse Code Game
//
// row3 -> 
