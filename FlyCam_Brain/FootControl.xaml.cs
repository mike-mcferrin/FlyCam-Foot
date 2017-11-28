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

        private void Rectangle_MouseDown(object sender, MouseButtonEventArgs e)
        {
       //     MessageBox.Show(string.Format("Rectangle MouseDown Y:{0}", e.GetPosition(this).Y));
        }

        private void Canvas_MouseDown(object sender, MouseButtonEventArgs e)
        {
            //   MessageBox.Show(string.Format("Canvas MouseDown Y:{0}", e.GetPosition(this).Y));
            SetSliderValue(e.GetPosition(this).Y - 10);
        }

        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                SetSliderValue(e.GetPosition(this).Y - 10);
            }
        }

        private void SetSliderValue(double newValue)
        {
            newValue = newValue < 0 ? 0 : newValue;
            newValue = newValue > SliderBox.Height - 4 ? SliderBox.Height - 4 : newValue;
            SliderValue.Height = newValue;
        }
    }
}
