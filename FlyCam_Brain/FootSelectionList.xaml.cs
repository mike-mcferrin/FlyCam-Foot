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
    /// Interaction logic for FootSelectionList.xaml
    /// </summary>
    public partial class FootSelectionList : UserControl
    {
        public FootSelectionList()
        {
            InitializeComponent();
        }

        private void Foot_1_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Foot_2_Click(object sender, RoutedEventArgs e)
        {

        }

        private float currentX = 0;
        private float currentY = 0;
        public void SetXY(float a, float val)
        {
            if (a == 1)
                currentX = val;
            if (a == 2)
                currentY = - val;
            Line1.X1 = currentX + (Line1.Width / 2);
            Line1.X2 = currentX + (Line1.Width / 2);
            Line1.Y1 = currentY + (Line1.Height / 2);
            Line1.Y2 = currentY + (Line1.Height / 2) + 20;
        }

     
    }
}
