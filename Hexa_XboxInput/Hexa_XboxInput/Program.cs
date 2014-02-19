using J2i.Net.XInputWrapper;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hexa_XboxInput
{
    public partial class Program
    {
        /// <summary>
        /// Der Haupteinstiegspunkt für die Anwendung.
        /// </summary>
        [STAThread]
        private static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainWindow());
            //_selectedController = XboxController.RetrieveController(0);
            //_selectedController.StateChanged += _selectedController_StateChanged;
            //XboxController.StartPolling();
        }

        //protected override void OnClosing(CancelEventArgs e)
        //{
        //    XboxController.StopPolling();
        //    //base.OnClosing(e);
        //}
    }
}
