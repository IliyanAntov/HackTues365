using System;
using System.IO.Ports;

namespace ConsoleApp1 {
    class Program {
        static void Main(string[] args) {
            SerialPort port;

            port = new SerialPort("COM7", 9600);
            port.Open();

            port.Write("1");
        }
    }
}
