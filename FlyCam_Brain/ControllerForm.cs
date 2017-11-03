using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using _6_ArduinoController;

namespace ArduinoController
{
    public partial class ControllerForm : Form
    {
        private readonly ArduinoController _arduinoController;
        private double _ledFrequency;

        public ControllerForm()
        {
            InitializeComponent();
            _arduinoController = new ArduinoController();
            _arduinoController.Setup(this);
            _arduinoController.CallOut += _arduinoController_CallOut;
            WPFControl1.Child = list;
        }
        FootSelectionList list = new FootSelectionList();
        private void _arduinoController_CallOut(ArduinoController a, float b, float c, EventArgs e)
        {
           
            list.SetXY(b,c);
        }

        // Update arduinoController on value checkbox checked/unchecked
        private void EnableLedCheckBoxCheckedChanged(object sender, EventArgs e)
        {
          //  _arduinoController.SetLedState(true);
        }

        // Update value label and arduinoController on value changed using slider
        private void LedFrequencyTrackBarScroll(object sender, EventArgs e)
        {
            //LedFrequencyValue.Text = _ledFrequency.ToString(CultureInfo.InvariantCulture);
            _arduinoController.SetLedFrequency(10, (float)2, (float) 1);
        }

//        // Set ledState checkbox
//        public void SetFoot(int foot)
//        {
//          //  EnableLedCheckBox.Checked = ledState;
//        }

//        // Set frequency slider
//        public void SetMode(double ledFrequency)
//        {
////            LedFrequencyLabelTrackBar.Value = (int) ((ledFrequency - 0.4)*2.5);
//        }

        // Update value label and arduinoController on value changed
        private void LedFrequencyLabelTrackBarValueChanged(object sender, EventArgs e)
        {
            LedFrequencyTrackBarScroll(sender,e);
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing )
            {
                _arduinoController.Exit();
                if (components!=null)
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void elementHost1_ChildChanged(object sender, System.Windows.Forms.Integration.ChildChangedEventArgs e)
        {
           
        }


    }
}
