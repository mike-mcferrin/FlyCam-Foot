using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace _6_ArduinoController
{
    /// <summary>
    /// Interaction logic for FootControl.xaml
    /// </summary>
    public partial class FootControl : UserControl
    {
        public FootControl()
        {
            InitializeComponent();
        }

        public delegate void CallOutHandler(FootControl footControl, int id, int command, int sub, double value, EventArgs e);
        public event CallOutHandler CallOut;

        private void Rectangle_MouseDown(object sender, MouseButtonEventArgs e)
        {
        }

        private int update_slider_position;

        private void Canvas_MouseDown(object sender, MouseButtonEventArgs e)
        {
            var pos = e.GetPosition(this);
            if (pos.X < SliderBox.Width + 10)
            {
                SetSliderValue(pos.Y - 12);
            }
        }

        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                var pos = e.GetPosition(this);
                if (pos.X < SliderBox.Width + 10)
                {
                    update_slider_position = (int) pos.Y - 12;
                    SetSliderValue(pos.Y - 12);
                }
            }
        }

        private void Canvas_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (update_slider_position > 0)
            {
                //CallOut(this, this.ID, 101, 2, 0, new EventArgs());
                //System.Threading.Thread.Sleep(500);
                CallOut(this, this.ID, 104, update_slider_position, 0, new EventArgs());
                System.Threading.Thread.Sleep(100);
                CallOut(this, this.ID, 104, update_slider_position, 0, new EventArgs());
                System.Threading.Thread.Sleep(100);
                CallOut(this, this.ID, 104, update_slider_position, 0, new EventArgs());
                System.Threading.Thread.Sleep(100);
                CallOut(this, this.ID, 104, update_slider_position, 0, new EventArgs());
                update_slider_position = 0;

                //System.Threading.Thread.Sleep(500);
                //CallOut(this, this.ID, 101, 1, 0, new EventArgs());
            }
        }

        public FootControl SetSliderValue(double newValue, bool log = true)
        {
            try
            {
                newValue = newValue < 0 ? 0 : newValue;
                newValue = newValue > SliderBox.Height - 6 ? SliderBox.Height - 6 : newValue;
                SliderValue.Height = newValue;
                Counter = (int)newValue;
                if (log)
                    CallOut(this, 12, 0, (int)newValue, newValue, new EventArgs());
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
            return this;
        }

        public string Text
        {
            get { return UIText_Description.Content.ToString(); }
            set { UIText_Description.Content = value; }
        }

        public string Status
        {
            get { return UIText_Status.Content.ToString(); }
            set
            {
                UIText_Status.Content = value;
                if (value.ToLower() == "online")
                {
                    UIText_Status.Foreground = Brushes.White;
                }
                else
                {
                    UIText_Status.Foreground = Brushes.Black;

                }

            }
        }

        public int Counter
        {
            get { return Int32.Parse(UIText_Status2.Content.ToString()); }
            set
            {
                UIText_Status2.Content = value.ToString();
            }
        }

        public int ID { get; set; }

        private void ButtonSendCommand_Click(object sender, RoutedEventArgs e)
        {
            SendCommand(this.ID);
        }

        private void ButtonSendCommand_To_All_Click(object sender, RoutedEventArgs e)
        {
            SendCommand(0);
        }

        private void SendCommand(int audience)
        {
            int d2 = Int32.Parse(TextBoxSend1.Text);
            int d3 = Int32.Parse(TextBoxSend2.Text);
            int d4 = Int32.Parse(TextBoxSend3.Text);
            CallOut(this, audience, d2, d3, d4, new EventArgs());
        }

        private void TextBoxSend_GotFocus(object sender, RoutedEventArgs e)
        {
            ((TextBox)sender).SelectAll();
        }

    
    }
}
