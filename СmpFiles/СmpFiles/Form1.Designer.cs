namespace СmpFiles
{
    partial class Form1
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
            this.buttonFile1 = new System.Windows.Forms.Button();
            this.buttonFile2 = new System.Windows.Forms.Button();
            this.textBoxFile1 = new System.Windows.Forms.TextBox();
            this.textBoxFile2 = new System.Windows.Forms.TextBox();
            this.buttonCMP = new System.Windows.Forms.Button();
            this.richTextBoxCMP = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonFile1
            // 
            this.buttonFile1.Location = new System.Drawing.Point(692, 10);
            this.buttonFile1.Name = "buttonFile1";
            this.buttonFile1.Size = new System.Drawing.Size(40, 23);
            this.buttonFile1.TabIndex = 0;
            this.buttonFile1.Text = "...";
            this.buttonFile1.UseVisualStyleBackColor = true;
            this.buttonFile1.Click += new System.EventHandler(this.buttonFile1_Click);
            // 
            // buttonFile2
            // 
            this.buttonFile2.Location = new System.Drawing.Point(692, 36);
            this.buttonFile2.Name = "buttonFile2";
            this.buttonFile2.Size = new System.Drawing.Size(40, 23);
            this.buttonFile2.TabIndex = 1;
            this.buttonFile2.Text = "...";
            this.buttonFile2.UseVisualStyleBackColor = true;
            this.buttonFile2.Click += new System.EventHandler(this.buttonFile2_Click);
            // 
            // textBoxFile1
            // 
            this.textBoxFile1.Location = new System.Drawing.Point(50, 12);
            this.textBoxFile1.Name = "textBoxFile1";
            this.textBoxFile1.ReadOnly = true;
            this.textBoxFile1.Size = new System.Drawing.Size(636, 20);
            this.textBoxFile1.TabIndex = 2;
            // 
            // textBoxFile2
            // 
            this.textBoxFile2.Location = new System.Drawing.Point(50, 38);
            this.textBoxFile2.Name = "textBoxFile2";
            this.textBoxFile2.ReadOnly = true;
            this.textBoxFile2.Size = new System.Drawing.Size(636, 20);
            this.textBoxFile2.TabIndex = 3;
            // 
            // buttonCMP
            // 
            this.buttonCMP.Location = new System.Drawing.Point(12, 64);
            this.buttonCMP.Name = "buttonCMP";
            this.buttonCMP.Size = new System.Drawing.Size(75, 23);
            this.buttonCMP.TabIndex = 4;
            this.buttonCMP.Text = "Compare";
            this.buttonCMP.UseVisualStyleBackColor = true;
            this.buttonCMP.Click += new System.EventHandler(this.buttonCMP_Click);
            // 
            // richTextBoxCMP
            // 
            this.richTextBoxCMP.Location = new System.Drawing.Point(12, 93);
            this.richTextBoxCMP.Name = "richTextBoxCMP";
            this.richTextBoxCMP.Size = new System.Drawing.Size(720, 169);
            this.richTextBoxCMP.TabIndex = 5;
            this.richTextBoxCMP.Text = "";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "File 1:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 41);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "File 2:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(744, 274);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.richTextBoxCMP);
            this.Controls.Add(this.buttonCMP);
            this.Controls.Add(this.textBoxFile2);
            this.Controls.Add(this.textBoxFile1);
            this.Controls.Add(this.buttonFile2);
            this.Controls.Add(this.buttonFile1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonFile1;
        private System.Windows.Forms.Button buttonFile2;
        private System.Windows.Forms.TextBox textBoxFile1;
        private System.Windows.Forms.TextBox textBoxFile2;
        private System.Windows.Forms.Button buttonCMP;
        private System.Windows.Forms.RichTextBox richTextBoxCMP;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

