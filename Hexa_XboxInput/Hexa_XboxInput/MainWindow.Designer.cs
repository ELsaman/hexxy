namespace Hexa_XboxInput
{
    partial class MainWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.leftStickYBar = new System.Windows.Forms.ProgressBar();
            this.leftStickXBar = new System.Windows.Forms.ProgressBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.leftStickYLabel = new System.Windows.Forms.Label();
            this.leftStickXLabel = new System.Windows.Forms.Label();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.rightStickYBar = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();
            // 
            // leftStickYBar
            // 
            this.leftStickYBar.Location = new System.Drawing.Point(244, 41);
            this.leftStickYBar.Maximum = 65535;
            this.leftStickYBar.Name = "leftStickYBar";
            this.leftStickYBar.Size = new System.Drawing.Size(380, 23);
            this.leftStickYBar.TabIndex = 0;
            this.leftStickYBar.Click += new System.EventHandler(this.progressBar1_Click);
            // 
            // leftStickXBar
            // 
            this.leftStickXBar.Location = new System.Drawing.Point(244, 111);
            this.leftStickXBar.Maximum = 65535;
            this.leftStickXBar.Name = "leftStickXBar";
            this.leftStickXBar.Size = new System.Drawing.Size(380, 23);
            this.leftStickXBar.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(241, 81);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(25, 17);
            this.label1.TabIndex = 2;
            this.label1.Text = "X: ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(241, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(21, 17);
            this.label2.TabIndex = 3;
            this.label2.Text = "Y:";
            // 
            // leftStickYLabel
            // 
            this.leftStickYLabel.AutoSize = true;
            this.leftStickYLabel.Location = new System.Drawing.Point(269, 8);
            this.leftStickYLabel.Name = "leftStickYLabel";
            this.leftStickYLabel.Size = new System.Drawing.Size(46, 17);
            this.leftStickYLabel.TabIndex = 4;
            this.leftStickYLabel.Text = "label3";
            // 
            // leftStickXLabel
            // 
            this.leftStickXLabel.AutoSize = true;
            this.leftStickXLabel.Location = new System.Drawing.Point(269, 81);
            this.leftStickXLabel.Name = "leftStickXLabel";
            this.leftStickXLabel.Size = new System.Drawing.Size(46, 17);
            this.leftStickXLabel.TabIndex = 5;
            this.leftStickXLabel.Text = "label4";
            // 
            // richTextBox1
            // 
            this.richTextBox1.HideSelection = false;
            this.richTextBox1.Location = new System.Drawing.Point(22, 241);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(883, 290);
            this.richTextBox1.TabIndex = 6;
            this.richTextBox1.Text = "";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(269, 157);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 17);
            this.label3.TabIndex = 9;
            this.label3.Text = "label4";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(241, 157);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(25, 17);
            this.label4.TabIndex = 8;
            this.label4.Text = "X: ";
            // 
            // rightStickYBar
            // 
            this.rightStickYBar.Location = new System.Drawing.Point(244, 187);
            this.rightStickYBar.Maximum = 65535;
            this.rightStickYBar.Name = "rightStickYBar";
            this.rightStickYBar.Size = new System.Drawing.Size(380, 23);
            this.rightStickYBar.TabIndex = 7;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(931, 543);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.rightStickYBar);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.leftStickXLabel);
            this.Controls.Add(this.leftStickYLabel);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.leftStickXBar);
            this.Controls.Add(this.leftStickYBar);
            this.Name = "MainWindow";
            this.Text = "MainWindow";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ProgressBar leftStickYBar;
        private System.Windows.Forms.ProgressBar leftStickXBar;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label leftStickYLabel;
        private System.Windows.Forms.Label leftStickXLabel;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ProgressBar rightStickYBar;
    }
}