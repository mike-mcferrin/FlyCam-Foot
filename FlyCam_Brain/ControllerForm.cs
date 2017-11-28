﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.Integration;
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
            WPFControl1.Child = wpfControl;

            FootControls.Add(new FootControl() { Text = "Foot D", Status = "Offline"});
            FootControls.Add(new FootControl() { Text = "Foot C", Status = "Offline" });
            FootControls.Add(new FootControl() { Text = "Foot B", Status = "Online" });
            FootControls.Add(new FootControl() { Text = "Foot A", Status = "Offline" });

            foreach (var foot in FootControls)
            {
                foot.Width = 60;
                foot.CallOut += (control, command, value, args) =>
                {
                    var controlName = control.Text;

                    listView2.Items.Insert(0,string.Format("control: {0} \n value: {1}", control.Text, value));
                };
                
                ElementHost H1 = new ElementHost();
                H1.Width = 70;
                H1.Child = foot;
                H1.Dock = DockStyle.Left;
                PanelFootList.Controls.Add(H1);
            }

        }
        FootSelectionList wpfControl = new FootSelectionList();
        List<FootControl> FootControls = new  List<FootControl>();
      
        private void _arduinoController_CallOut(ArduinoController a, float b, float c, EventArgs e)
        {
            _arduinoController.SetLedFrequency(1, b, c);
            listView2.Items.Insert(0, string.Format("control: {0} \n value: {1}", b, c));
            wpfControl.SetXY(b,c);
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
