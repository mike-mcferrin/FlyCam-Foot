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

        public delegate void CallOutHandler(FootControl footControl, int command, double value, EventArgs e);
        public event CallOutHandler CallOut;

        private void Rectangle_MouseDown(object sender, MouseButtonEventArgs e)
        {
        }

        private void Canvas_MouseDown(object sender, MouseButtonEventArgs e)
        {
            SetSliderValue(e.GetPosition(this).Y - 12);
        }

        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                SetSliderValue(e.GetPosition(this).Y - 12);
            }
        }

        private void SetSliderValue(double newValue)
        {
            newValue = newValue < 0 ? 0 : newValue;
            newValue = newValue > SliderBox.Height - 6 ? SliderBox.Height - 6 : newValue;
            SliderValue.Height = newValue;
            CallOut(this, 12, newValue, new EventArgs());
        }

        public string Text
        {
            get { return UIText_Description.Content.ToString(); }
            set { UIText_Description.Content = value; }
        }

        public string Status
        {
            get { return UIText_Status.Content.ToString();  }
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

    }
}
