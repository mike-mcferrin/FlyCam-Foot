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

        private float currentX = 128;
        private float currentY = 128;
        private float currentX2 = 128;
        private float currentY2 = 128;


        /***** SetXY Usage *******************
         *   A   Value
         *  --- -----------------------------
         *   1   Sets X value for Left XY Graph
         *   2   Sets Y value for Left XY Graph
         *   3   Sets X value for Right XY Graph
         *   4   Sets Y value for Right XY Graph
         *   6   (-) value => Selects previous menu item in [Mode List]
         *   6   (+) value => Selects next menu item in [Mode List]
        **************************************/
        public void SetXY(float a, float val)
        {
            switch (a)
            {
                case 1:
                case 2:

                    if (a == 1)
                        currentX = val;
                    if (a == 2)
                        currentY = -val;
                    Line1.X1 = currentX + (Line1.Width / 2);
                    Line1.X2 = currentX + (Line1.Width / 2);
                    Line1.Y1 = currentY + (Line1.Height / 2);
                    Line1.Y2 = currentY + (Line1.Height / 2) + 20;

                    break;

                case 3:
                case 4:

                    if (a == 3)
                        currentX2 = val;
                    if (a == 4)
                        currentY2 = -val;
                    Line2.X1 = currentX2 + (Line2.Width / 2);
                    Line2.X2 = currentX2 + (Line2.Width / 2);
                    Line2.Y1 = currentY2 + (Line2.Height / 2);
                    Line2.Y2 = currentY2 + (Line2.Height / 2) + 20;

                    break;


                case 6:

                    var selectedItem = ListBox_Mode.SelectedItems[0];

                    if (val < 0)
                    {
                        for (var x = 0; x < ListBox_Mode.Items.Count; x++)
                        {
                            var currentItem = (ListBoxItem) ListBox_Mode.Items.GetItemAt(x);
                            if (currentItem == selectedItem)
                            {
                                ((ListBoxItem)ListBox_Mode.Items.GetItemAt(Math.Min(ListBox_Mode.Items.Count - 1, x + 1))).IsSelected = true;
                            }
                        }
                    }
                    if (val > 0)
                    {
                        for (var x = ListBox_Mode.Items.Count - 1; x >= 0; x--)
                        {
                            var currentItem = (ListBoxItem)ListBox_Mode.Items.GetItemAt(x);
                            if (currentItem == selectedItem)
                            {
                              (  (ListBoxItem)ListBox_Mode.Items.GetItemAt(Math.Max(0, x - 1) )).IsSelected = true;
                            }
                        }
                    }
                    break;
            }
        }

     
    }
}
