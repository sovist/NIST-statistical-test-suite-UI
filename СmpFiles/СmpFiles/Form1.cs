using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using  System.IO;

namespace СmpFiles
{
    public partial class Form1 : Form
    {
        private string _file1;
        private string _file2;

        public Form1()
        {
            InitializeComponent();
        }

        private void buttonFile1_Click(object sender, EventArgs e)
        {
            richTextBoxCMP.Clear();
            OpenFileDialog openFileDialog = new OpenFileDialog();

            if (openFileDialog.ShowDialog() == DialogResult.OK)
                _file1 = textBoxFile1.Text = openFileDialog.FileName;
        }

        private void buttonFile2_Click(object sender, EventArgs e)
        {
            richTextBoxCMP.Clear();
            OpenFileDialog openFileDialog = new OpenFileDialog();

            if (openFileDialog.ShowDialog() == DialogResult.OK)
                _file2 = textBoxFile2.Text = openFileDialog.FileName;
        }

        private void buttonCMP_Click(object sender, EventArgs e)
        {
            string[] file1Lines = File.ReadAllLines(_file1);
            string[] file2Lines = File.ReadAllLines(_file2);

            richTextBoxCMP.Clear();
            for (int i = 0; i < file1Lines.Length && i < file2Lines.Length; i++)
            {
                if (file1Lines[i] != file2Lines[i])
                {
                    richTextBoxCMP.Text += @"Line: №" + (i + 1) + "\n";
                    richTextBoxCMP.Text += @"File 1: " + file1Lines[i] + "\n";
                    richTextBoxCMP.Text += @"File 2: " + file2Lines[i] + "\n\n";
                }
            }
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            richTextBoxCMP.Width = Width - 40;
            richTextBoxCMP.Height = Height - richTextBoxCMP.Top - 50;
        }
    }
}
