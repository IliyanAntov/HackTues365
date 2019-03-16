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

            ButtonGameValues = new RandomizeButtonGame();  // create a new set of random values

            rows.AddRange(FormatData(ButtonGameValues));  // pick the ones needed for the arduino

            for (int i = 0; i < rows.Count; i++) {
                port.Write(rows[i].ToString());

                while (port.ReadExisting() != "1") {
                    Thread.Sleep(10);
                }
            }     

            label1.Text = ButtonGameRows(ButtonGameValues) + rows[0] + " " + rows[1];
        }

        private void label1_Click(object sender, EventArgs e) {

        }

        private List<char> FormatData(RandomizeButtonGame bg) {  // format data for Arduino
            List<char> rows = new List<char>();

            rows.Add(colors[bg.Index]);  // pick the chosen color
            rows.Add((char) (bg.TimeValues[bg.Index] + '0'));  // pick the chosen digit

            return rows;
        }

        private string ButtonGameRows(RandomizeButtonGame bg) {  // format button game instructions
            StringBuilder sb = new StringBuilder();
            string ButtonGameHeading = "Button Game \n\n";  // Beggining line
            sb.Append(ButtonGameHeading);

            for (int i = 0; i < colors.Length; i++) {  // creating a semi-table for all colors and their corresponing time-values
                sb.Append(colors[i] + " -> " + bg.TimeValues[i] + '\n');
            }
      
            return sb.ToString();  
        }
    }
}
