using J2i.Net.XInputWrapper;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Hexa_XboxInput
{
    public partial class MainWindow : Form
    {
        private XboxController _selectedController;
        private int[] oldVals = { 90, 0, 0 };
        private int[] newVals = { 90, 0, 0 };

        private int _shutdown = -1;
        
        private int[] offset = { 0, 0, 0 };
        private bool _offsetChanged = false;
        private int offsetStep = 0;
        //private int oldX = 90;
        //private int oldY = 90;
        //private int X = 90;
        //private int Y = 90;

        private void ChangeOffset(bool up, bool reset = false)
        {
            int step = 15; // 15 degree
            if (reset)
                offsetStep = 0;
            else
                offsetStep += up ? 1 : -1;
            Console.Out.WriteLine(String.Format("Offset: {0}", offsetStep));
            _offsetChanged = true;

            offset[1] = offsetStep * step;
            offset[2] = offsetStep * step * -1;
        }

        public MainWindow()
        {
            InitializeComponent();

            _selectedController = XboxController.RetrieveController(0);
            _selectedController.StateChanged += _selectedController_StateChanged;
            XboxController.StartPolling();

            InitSerial();
        }

        SerialPort serial;

        void InitSerial()
        {
            serial = new SerialPort("COM10", 115200);
            //serial.NewLine = "\r";
            serial.DataReceived += serial_DataReceived;
            serial.Open();

            System.Windows.Forms.Timer t = new System.Windows.Forms.Timer();
            t.Interval = 200;
            t.Tick += t_Tick;
            t.Start();
        }

        bool updated = false;

        private void t_Tick(object sender, EventArgs e)
        {


            updated = true;

            bool greater = _offsetChanged;
            _offsetChanged = false;

            int[] targ = { 0, 0, 0 };

            if (_shutdown == 1)
                return;
            else if (_shutdown == 0)
            {
                ++_shutdown;
                targ[0] = 90;
                targ[1] = 0;
                targ[2] = 0;
                ChangeOffset(false, true);
            }
            else if (_shutdown == -2)
            {
                ++_shutdown;
                greater = true;
            }

            if (!_offsetChanged)
            {
                for (int i = 0; i < 3; ++i)
                {
                    var val = offset[i] + newVals[i];
                    targ[i] = Math.Max(val, 0);
                    targ[i] = Math.Min(targ[i], 180);

                    if (Math.Abs(oldVals[i] - newVals[i]) >= 5)
                        greater = true;
                }

                if (!greater)
                    return;
            }

            if (targ[2] > 120)
                targ[2] = 120;

            string line = targ[0].ToString() + ' ' + targ[1].ToString() + ' ' + targ[2].ToString() + ' ' + '\r';
//            string line = String.Format("COMM_BEGIN:{0}:{1}:90:COMM_END:\r", X, Y);

            for (int i = 0; i < 3; ++i)
                oldVals[i] = newVals[i];
            //line = line.Insert(0, line.Length.ToString());
            serial.WriteLine(line);
            WriteSerial(line);
        }

        void WriteSerial(string data)
        {
            string line = String.Format("[{0}].[Serial -> Arduino] {1}", DateTime.Now.ToUniversalTime(), data);
            if (richTextBox1.InvokeRequired)
            {
                richTextBox1.Invoke(new MethodInvoker(delegate { richTextBox1.Text += line; richTextBox1.SelectionStart = richTextBox1.Text.Length; richTextBox1.ScrollToCaret(); }));
            }
            else
            {
                richTextBox1.Text += line;
                richTextBox1.SelectionStart = richTextBox1.Text.Length;
                richTextBox1.ScrollToCaret();
            }

            
        }

        void ReadData(string data)
        {
            string line = String.Format("[{0}].[Arduino -> Serial] {1}", DateTime.Now.ToUniversalTime(), data);
            if (richTextBox1.InvokeRequired)
            {
                richTextBox1.Invoke(new MethodInvoker(delegate { richTextBox1.Text += line; richTextBox1.SelectionStart = richTextBox1.Text.Length; richTextBox1.ScrollToCaret(); }));
            }
        }



        private void serial_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            var serial = (SerialPort)sender;

            string orig = serial.ReadLine();
            while (orig != null)
            {
                ReadData(orig);
                orig = serial.ReadLine();
            }
            //if (orig == "DEBUG MODE\r")
                //WriteSerial("TEST_STRING");
        }


        private void _selectedController_StateChanged(object sender, XboxControllerStateChangedEventArgs e)
        {
            MethodInvoker mi = delegate
            {
                leftStickXBar.Value = normalizeValue(_selectedController.LeftThumbStick.X, 32768);
                leftStickYBar.Value = normalizeValue(_selectedController.RightThumbStick.X, 32768);
                rightStickYBar.Value = normalizeValue(_selectedController.RightThumbStick.Y, 32768);
                leftStickXLabel.Text = _selectedController.LeftThumbStick.X.ToString();
                leftStickYLabel.Text = _selectedController.LeftThumbStick.Y.ToString();
                if (_selectedController.IsDPadDownPressed)
                    ChangeOffset(false);
                if (_selectedController.IsDPadUpPressed)
                    ChangeOffset(true);
                if (_selectedController.IsStartPressed)
                    _shutdown = _shutdown == -1 ? 0 : -2;
                label3.Text = _selectedController.RightThumbStick.Y.ToString();
            };
            if (InvokeRequired)
                this.Invoke(mi);
            //OnPropertyChanged("SelectedController");
            if (updated)
            {
                for (int i = 0; i < 3; ++i)
                    oldVals[i] = newVals[i];
                updated = false;
                
            }

            newVals[0] = (int)ExtensionMethods.Map(leftStickXBar.Value, 0, 65536, 45, 135);
            newVals[1] = (int)ExtensionMethods.Map(leftStickYBar.Value, 0, 65536, 45, 135);
            newVals[2] = (int)ExtensionMethods.Map(rightStickYBar.Value, 0, 65536, 0, 180);
        }

        private int normalizeValue(int val, int _base)
        {
            if (val < 5000 && val > -5000)
                return _base;
            return val + _base;
        }

        private void progressBar1_Click(object sender, EventArgs e)
        {
        }
    }

    public static class ExtensionMethods
    {
        public static decimal Map(this decimal value, decimal fromSource, decimal toSource, decimal fromTarget, decimal toTarget)
        {
            return (value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget;
        }
    }
}
