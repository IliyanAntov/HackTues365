﻿using System;
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
            InitializeComponent();  // begin the Forms App
            port = new SerialPort("COM3", 9600);  // define a serial connection on COM3 @ 9600 baud rate
            port.Open();  // open the serial connection

            button1.Text = "Generate";  // Initialize the text for the button and label
            label1.Text = "Click \"Generate\" to begin";
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
                string currentRow = hc[i].ToString();
                port.Write(currentRow);

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

        private string ButtonGameRows(RandomizeButtonGame bg, RandomizeMorseCodeGame mcg, RandomizeSimonSaysGame ssg) {  // format button game instructions
            StringBuilder sb = new StringBuilder();
            string ButtonGameHeading = "Button Game \n\n";
            string MorseCodeGameHeading = "Morse Code Game \n\n";
            string SimonSaysGameHeading = "Simon Says Game \n\n";

            // <----- Button Game -----> //

            sb.Append(ButtonGameHeading);

            for (int i = 0; i < colors.Length; i++) {
                string currentColor = Converter.CharToStr(colors[i]);
                int currentTimeValue = bg.TimeValues[i];

                sb.Append($"{currentColor} Color -> {currentTimeValue} \n");
            }

            // <----- Morse Code -----> //

            sb.Append("\n");
            sb.Append(MorseCodeGameHeading);

            for (int i = 0; i < mcg.Words.Count; i++) {
                string word = mcg.Words[i].ToUpper();
                int index = mcg.Indexes[i];

                sb.Append($"{word} -> {index} \n");
            }

            // <------ Simon Says -----> //

            sb.Append("\n");
            sb.Append(SimonSaysGameHeading);

            for (int i = 0; i < ssg.Nums.Count; i++) {
                string currentLED = Converter.CharToStr(colors[i]);
                string currentButton = Converter.CharToStr(colors[ssg.Nums[i]]);

                sb.Append($"{currentLED} LED -> {currentButton} Button\n");
            }

            sb.Append(String.Join(",", ssg.Sequence));

            return sb.ToString();
        }

        private void Form1_Load(object sender, EventArgs e) {

        }
    }
}

// Button Game
// row1 -> RGB Color
// row2 -> Wanted Digit
// 
// Morse Code Game
//
// row3 -> Word index
// row4-row6 -> word
//
// Simon Says Game
//
// row7-row10 -> button order
// row11-row16 -> sequence
