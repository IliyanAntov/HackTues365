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

        char[] colors = new char[] { 'r', 'g', 'b', 'y' };

        public Form1() {
            InitializeComponent();  // begin the Forms App
            port = new SerialPort("COM3", 9600);  // define a serial connection on COM3 @ 9600 baud rate
            port.Open();  // open the serial connection

            button1.Text = "Generate";  // Initialize the text for the button and label
            label1.Text = "";
        }

        private void button1_Click(object sender, EventArgs e) {  // button click event listener
            List<char> rows = new List<char>();  // collection of all rows for the arduino

            // <----- Create sets of values -----> //

            ButtonGameValues = new RandomizeButtonGame();  
            MorseCodeGameValues = new RandomizeMorseCodeGame();

            // <----- Copy data ------> //

            rows.AddRange(FormatData(ButtonGameValues, MorseCodeGameValues));

            // <----- Send data ------> //

            for (int i = 0; i < rows.Count; i++) {
                port.Write(rows[i].ToString());

                while (port.ReadExisting() != "1") {
                    Thread.Sleep(10);
                }
            }

            // <----- Display text -----> //

            label1.Text = ButtonGameRows(ButtonGameValues, MorseCodeGameValues) + $" \n {rows[0]} {rows[1]}   {rows[2]} {rows[3]}{rows[4]}{rows[5]}";
        }

        private void label1_Click(object sender, EventArgs e) {

        }

        private List<char> FormatData(RandomizeButtonGame bg, RandomizeMorseCodeGame mcg) {  // format data for Arduino
            List<char> rows = new List<char>();
            char[] word = mcg.Word.ToArray();

            // <----- Button Game -----> //

            rows.Add(colors[bg.Index]);  // pick the chosen color
            rows.Add((char)(bg.TimeValues[bg.Index] + '0'));  // pick the chosen digit

            // <------ Morse Code -----> //

            rows.Add(mcg.Index);

            for (int i = 0; i < word.Length; i++) {  // add MCG word as seperate rows
                rows.Add(word[i]);
            }

            return rows;
        }

        private string ButtonGameRows(RandomizeButtonGame bg, RandomizeMorseCodeGame mcg) {  // format button game instructions
            StringBuilder sb = new StringBuilder();
            string ButtonGameHeading = "Button Game \n\n";
            string MorseCodeGameHeading = "Morse Code Game \n\n";

            // <----- Button Game -----> //

            sb.Append(ButtonGameHeading);

            for (int i = 0; i < colors.Length; i++) {
                sb.Append($"{colors[i]} -> {bg.TimeValues[i]} \n");
            }

            // <----- Morse Code -----> //

            sb.Append("\n");
            sb.Append(MorseCodeGameHeading);

            for (int i = 0; i < mcg.Words.Count; i++) {
                sb.Append($"{i} -> {mcg.Words[i]} \n");
            }

            return sb.ToString();
        }
    }
}
