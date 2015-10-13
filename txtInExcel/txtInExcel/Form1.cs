using System;
using System.IO;
using System.Windows.Forms;
using txtReportInExcel;

namespace txtInExcel
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
           OpenFileDialog openFileDialog = new OpenFileDialog();
           TxtInExcel txtInExcel = new TxtInExcel();

            try
            {
                
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                  txtInExcel.Open(textBox1.Text = openFileDialog.FileName, 
                                 (new FileInfo(openFileDialog.FileName)).DirectoryName, 
                                  "finalAnalysisReport.xls");
                }
            }
            catch (Exception ex)
            {
                txtInExcel.Dispose_();
                MessageBox.Show(ex.Message);
            }
        }


    }
}
