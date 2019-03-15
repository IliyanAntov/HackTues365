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
            InitializeComponent();
            port = new SerialPort("COM3", 9600);
            port.Open();

            button1.Text = "Generate";
            label1.Text = "";
        }

        private void button1_Click(object sender, EventArgs e) {
            List<char> rows = new List<char>();

            //port.Write("1");

            ButtonGameValues = new RandomizeButtonGame();

            rows.AddRange(FormatData(ButtonGameValues));

            for (int i = 0; i < rows.Count; i++) {
                port.Write(rows[i].ToString());

                while (port.ReadExisting() != "1") {
                    Thread.Sleep(10);
                }
            }     

            label1.Text = ButtonGameRows(ButtonGameValues) + rows[0] + rows[1];
        }

        private void label1_Click(object sender, EventArgs e) {

        }

        private List<char> FormatData(RandomizeButtonGame bg) { // format data for Arduino
            List<char> rows = new List<char>();

            rows.Add(colors[bg.Index]); // pick the chosen color
            rows.Add((char) (bg.TimeValues[bg.Index] + '0')); // pick the chosen digit

            return rows;
        }

        private string ButtonGameRows(RandomizeButtonGame bg) {
            StringBuilder sb = new StringBuilder();

            for (int i = 0; i < 4; i++) {
                sb.Append(colors[i] + " -> " + bg.TimeValues[i] + '\n');
            }
      
            return sb.ToString();
        }
    }
}
