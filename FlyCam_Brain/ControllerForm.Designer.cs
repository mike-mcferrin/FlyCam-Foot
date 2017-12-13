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
            this.WPFControl1 = new System.Windows.Forms.Integration.ElementHost();
            this.PanelFootList = new System.Windows.Forms.Panel();
            this.btn_ReConnect_Serial = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.listView2 = new System.Windows.Forms.ListView();
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label2.Font = new System.Drawing.Font("Arial Black", 48F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.label2.Location = new System.Drawing.Point(-7, 647);
            this.label2.Name = "label2";
            this.label2.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.label2.Size = new System.Drawing.Size(867, 90);
            this.label2.TabIndex = 7;
            this.label2.Text = "SKYCAM CONTROLLER";
            // 
            // WPFControl1
            // 
            this.WPFControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.WPFControl1.Location = new System.Drawing.Point(10, 10);
            this.WPFControl1.Margin = new System.Windows.Forms.Padding(2);
            this.WPFControl1.Name = "WPFControl1";
            this.WPFControl1.Size = new System.Drawing.Size(1505, 600);
            this.WPFControl1.TabIndex = 10;
            this.WPFControl1.Text = "elementHost1";
            this.WPFControl1.ChildChanged += new System.EventHandler<System.Windows.Forms.Integration.ChildChangedEventArgs>(this.elementHost1_ChildChanged);
            this.WPFControl1.Child = null;
            // 
            // PanelFootList
            // 
            this.PanelFootList.AutoScroll = true;
            this.PanelFootList.BackColor = System.Drawing.SystemColors.ControlDark;
            this.PanelFootList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PanelFootList.Location = new System.Drawing.Point(10, 10);
            this.PanelFootList.Margin = new System.Windows.Forms.Padding(10);
            this.PanelFootList.Name = "PanelFootList";
            this.PanelFootList.Padding = new System.Windows.Forms.Padding(10);
            this.PanelFootList.Size = new System.Drawing.Size(1505, 600);
            this.PanelFootList.TabIndex = 12;
            this.PanelFootList.Paint += new System.Windows.Forms.PaintEventHandler(this.PanelFootList_Paint);
            // 
            // btn_ReConnect_Serial
            // 
            this.btn_ReConnect_Serial.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_ReConnect_Serial.Location = new System.Drawing.Point(25, 26);
            this.btn_ReConnect_Serial.Name = "btn_ReConnect_Serial";
            this.btn_ReConnect_Serial.Size = new System.Drawing.Size(296, 44);
            this.btn_ReConnect_Serial.TabIndex = 13;
            this.btn_ReConnect_Serial.Text = "Reconnect Serial";
            this.btn_ReConnect_Serial.UseVisualStyleBackColor = true;
            this.btn_ReConnect_Serial.Click += new System.EventHandler(this.btn_ReConnect_Serial_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.tabControl1.ItemSize = new System.Drawing.Size(200, 30);
            this.tabControl1.Location = new System.Drawing.Point(0, 2);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.Padding = new System.Drawing.Point(20, 5);
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1533, 658);
            this.tabControl1.TabIndex = 14;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.PanelFootList);
            this.tabPage1.Location = new System.Drawing.Point(4, 34);
            this.tabPage1.Margin = new System.Windows.Forms.Padding(10);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(10);
            this.tabPage1.Size = new System.Drawing.Size(1525, 620);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Connected Feet";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.listView2);
            this.tabPage2.Location = new System.Drawing.Point(4, 34);
            this.tabPage2.Margin = new System.Windows.Forms.Padding(10);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(10);
            this.tabPage2.Size = new System.Drawing.Size(1525, 531);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Event Log";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // listView2
            // 
            this.listView2.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader4,
            this.columnHeader5,
            this.columnHeader6});
            this.listView2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView2.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listView2.FullRowSelect = true;
            this.listView2.GridLines = true;
            this.listView2.HideSelection = false;
            this.listView2.Location = new System.Drawing.Point(10, 10);
            this.listView2.Margin = new System.Windows.Forms.Padding(2);
            this.listView2.MultiSelect = false;
            this.listView2.Name = "listView2";
            this.listView2.Size = new System.Drawing.Size(1505, 511);
            this.listView2.TabIndex = 10;
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
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.btn_ReConnect_Serial);
            this.tabPage3.Location = new System.Drawing.Point(4, 34);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(10);
            this.tabPage3.Size = new System.Drawing.Size(1525, 531);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Settings";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.WPFControl1);
            this.tabPage4.Location = new System.Drawing.Point(4, 34);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new System.Windows.Forms.Padding(10);
            this.tabPage4.Size = new System.Drawing.Size(1525, 620);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "PS2 Controller Interface";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // ControllerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1532, 727);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.label2);
            this.DoubleBuffered = true;
            this.Name = "ControllerForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "SkyCam Controller";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            this.tabPage4.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Integration.ElementHost WPFControl1;
        private System.Windows.Forms.Panel PanelFootList;
        private System.Windows.Forms.Button btn_ReConnect_Serial;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.ListView listView2;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.ColumnHeader columnHeader6;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
    }
}

