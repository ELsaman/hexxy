using SharpDX.XInput;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace HexxyXboxController_Bluetooth
{

    public partial class Form1 : Form
    {
        SerialHandler serial;
        ControllerHandler controller;

        public Form1()
        {
            InitializeComponent();

            serial = new SerialHandler("COM40");

            controller = new ControllerHandler();

            Timer updateTimer = new Timer();
            updateTimer.Tick += OnUpdate;
            updateTimer.Interval = 20;
            updateTimer.Start();

        }

        Gamepad curState;
        String updateState;

        int mode = 1;

        private int MapAngle(short val, int range = 40)
        {
            return (int)Utils.Map(val, -32768, 32767, -range / 2, range / 2);
        }
        private int MapController(short val, int min, int max)
        {
            return (int)Utils.Map(val, -32768, 32767, min, max);
        }

        private void OnUpdate(object sender, EventArgs e)
        {
            if (!controller.GetCurrentState(out curState))
                return;

            object[] data;

            // angles
            if (mode == 0)
            {
                data = new object[5];

                data[0] = (float)MapAngle(curState.LeftThumbX) / 57.2957795f;
                data[1] = (float)MapAngle(curState.LeftThumbY, 60) / 57.2957795f;
                data[2] = (float)MapAngle(curState.RightThumbY) / 57.2957795f;
                //data[0] = 0;
                //data[2] = 0;
                data[3] = 0;
                data[4] = 0;

                serial.WriteSerialCommand("DCTP", data);
            }
            else if (mode == 1)
            {
                // speedX speedY speedR
                data = new object[4];

                data[0] = (float)MapController(curState.LeftThumbX, -100, 100);
                data[1] = (float)MapController(curState.LeftThumbY, -100, 100);

                
                data[2] = (ushort)0;
//                data[3] = (float)MapAngle(curState.RightThumbX) / 57.2957795f;

                serial.WriteSerialCommand("DCTA", data);
            }


        }
    }
    public static class Utils
    {
        public static decimal Map(this decimal value, decimal fromSource, decimal toSource, decimal fromTarget, decimal toTarget)
        {
            return (value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget;
        }
    }
}
