using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SharpDX.XInput;

namespace HexxyXboxController_Bluetooth
{
    class ControllerHandler
    {
        Controller controller;

        public ControllerHandler()
        {
            controller = new Controller(0);
            if (controller.IsConnected)
                System.Console.WriteLine("Controller 0 connected");
        }

        public bool GetCurrentState(out Gamepad gamepad)
        {
            if (controller.IsConnected)
            {
                gamepad = controller.GetState().Gamepad;
                return true;
            }
            else
            {
                gamepad = new Gamepad();
                return false;
            }
        }

        public bool HasController()
        {
            return controller.IsConnected;
        }
    }
}
