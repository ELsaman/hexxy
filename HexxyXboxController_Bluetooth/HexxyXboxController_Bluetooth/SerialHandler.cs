using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;

namespace HexxyXboxController_Bluetooth
{
    class SerialHandler
    {
        private SerialPort serial;

        public SerialHandler(string comPort)
        {
            serial = new SerialPort(comPort);
            serial.StopBits = StopBits.One;
            serial.Parity = Parity.None;
            serial.BaudRate = 38400;
            serial.DataReceived += OnDataReceived;
            serial.Open();
        }

        private void OnDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Console.Write(serial.ReadLine());
            //throw new NotImplementedException();
        }

        // e.g. DCTA 12 22 DCTA\r

        string oldState = "";
        public void WriteSerialCommand(String command, object[] array)
        {
            String serialData;

            string data = "";

            foreach (var item in array)
            {
                data += "" + item + " ";
            }

            serialData = String.Format("{0} {1} {0}\r", command, data);
            //serialData = "DCTP 0 0 0 0 DCTP";
            if (serialData == oldState)
                return;

            serial.Write(serialData);
            Console.WriteLine(serialData);
            oldState = serialData;

        }


    }
}
