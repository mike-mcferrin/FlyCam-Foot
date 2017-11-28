namespace ArduinoController
{
    partial class ControllerForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;



        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label2 = new System.Windows.Forms.Label();
            this.listView2 = new System.Windows.Forms.ListView();
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.WPFControl1 = new System.Windows.Forms.Integration.ElementHost();
            this.PanelFootList = new System.Windows.Forms.Panel();
            this.btn_ReConnect_Serial = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Arial Black", 48F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.label2.Location = new System.Drawing.Point(30, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(325, 90);
            this.label2.TabIndex = 7;
            this.label2.Text = "EVENTS";
            // 
            // listView2
            // 
            this.listView2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.listView2.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader4,
            this.columnHeader5,
            this.columnHeader6});
            this.listView2.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listView2.FullRowSelect = true;
            this.listView2.GridLines = true;
            this.listView2.HideSelection = false;
            this.listView2.Location = new System.Drawing.Point(69, 62);
            this.listView2.Margin = new System.Windows.Forms.Padding(2);
            this.listView2.MultiSelect = false;
            this.listView2.Name = "listView2";
            this.listView2.Size = new System.Drawing.Size(1172, 244);
            this.listView2.TabIndex = 9;
            this.listView2.UseCompatibleStateImageBehavior = false;
            this.listView2.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "Source";
            this.columnHeader4.Width = 719;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Text = "Event Type";
            this.columnHeader5.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader5.Width = 237;
            // 
            // columnHeader6
            // 
            this.columnHeader6.Text = "Details";
            this.columnHeader6.Width = 390;
            // 
            // WPFControl1
            // 
            this.WPFControl1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.WPFControl1.Location = new System.Drawing.Point(0, 327);
            this.WPFControl1.Margin = new System.Windows.Forms.Padding(2);
            this.WPFControl1.Name = "WPFControl1";
            this.WPFControl1.Size = new System.Drawing.Size(1629, 400);
            this.WPFControl1.TabIndex = 10;
            this.WPFControl1.Text = "elementHost1";
            this.WPFControl1.ChildChanged += new System.EventHandler<System.Windows.Forms.Integration.ChildChangedEventArgs>(this.elementHost1_ChildChanged);
            this.WPFControl1.Child = null;
            // 
            // PanelFootList
            // 
            this.PanelFootList.Dock = System.Windows.Forms.DockStyle.Right;
            this.PanelFootList.Location = new System.Drawing.Point(1268, 0);
            this.PanelFootList.Name = "PanelFootList";
            this.PanelFootList.Size = new System.Drawing.Size(361, 327);
            this.PanelFootList.TabIndex = 12;
            // 
            // btn_ReConnect_Serial
            // 
            this.btn_ReConnect_Serial.Location = new System.Drawing.Point(442, 13);
            this.btn_ReConnect_Serial.Name = "btn_ReConnect_Serial";
            this.btn_ReConnect_Serial.Size = new System.Drawing.Size(75, 23);
            this.btn_ReConnect_Serial.TabIndex = 13;
            this.btn_ReConnect_Serial.Text = "Reconnect";
            this.btn_ReConnect_Serial.UseVisualStyleBackColor = true;
            this.btn_ReConnect_Serial.Click += new System.EventHandler(this.btn_ReConnect_Serial_Click);
            // 
            // ControllerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1629, 727);
            this.Controls.Add(this.btn_ReConnect_Serial);
            this.Controls.Add(this.PanelFootList);
            this.Controls.Add(this.WPFControl1);
            this.Controls.Add(this.listView2);
            this.Controls.Add(this.label2);
            this.Name = "ControllerForm";
            this.Text = "Arduino Controller";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListView listView2;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.ColumnHeader columnHeader6;
        private System.Windows.Forms.Integration.ElementHost WPFControl1;
        private System.Windows.Forms.Panel PanelFootList;
        private System.Windows.Forms.Button btn_ReConnect_Serial;
    }
}

