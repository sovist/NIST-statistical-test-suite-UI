using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using Microsoft.Office.Interop.Excel;

namespace txtReportInExcel
{
    public class TxtInExcel
    {
        private _Application _excellApp;
        private Workbook _excellWorkBook;
        private Worksheet _excellWorkSheet;

        public TxtInExcel()
        { }

        public TxtInExcel(string openFileName, string saveDir, string saveFileName)
        {
            Open(openFileName, saveDir, saveFileName);
        }

        ~TxtInExcel()
        {
            Dispose_();
        }

        public void Dispose_()
        {
            try
            {
                if (_excellApp != null)
                {
                    _excellApp.Quit();
                    ReleaseObject(_excellApp);
                }

                if (_excellWorkSheet != null)
                    ReleaseObject(_excellWorkSheet);

                if (_excellWorkBook != null)
                {
                    _excellWorkBook.Close(true, Missing.Value, Missing.Value);
                    ReleaseObject(_excellWorkBook);
                }
            }

            catch
            {
                //throw new Exception("File occupied by another process");
            }
        }

        public void Open(string openFileName, string saveDir, string saveFileName)
        {
            _excellApp = new Application();
            _excellWorkBook = _excellApp.Workbooks.Add(Missing.Value);
            _excellWorkSheet = (Worksheet)_excellWorkBook.Worksheets.Item[1];

            int numbersSel = AddDataFromFile(openFileName, _excellWorkSheet);
            AddChart(_excellWorkSheet, "L8", "L" + (numbersSel + 7));

            SaveExcelFile(saveDir + saveFileName, _excellWorkBook);
            CloseQuitAndRelease(_excellApp, _excellWorkSheet, _excellWorkBook);

            OpenExcel(saveDir + saveFileName);
        }

        private static void AddChart(_Worksheet excellWorkSheet, string startSel, string endSel)
        {
            ChartObjects xlCharts = (ChartObjects)excellWorkSheet.ChartObjects(Type.Missing);
            ChartObject myChart = xlCharts.Add(10, 80, 600, 400);
            Chart chartPage = myChart.Chart;
            Range chartRange = excellWorkSheet.Range[startSel, endSel];

            chartPage.SetSourceData(chartRange, Type.Missing);
            chartPage.ChartType = XlChartType.xlXYScatter;

            var seriesCollection = (SeriesCollection)chartPage.SeriesCollection();
            seriesCollection.Item(1).Name = "PROPORTION";
        }

        private static int AddDataFromFile(string fileName, _Worksheet excellWorkSheet)
        {
            if (excellWorkSheet == null)
                throw new ArgumentNullException("excellWorkSheet");

            var lines = File.ReadAllLines(fileName, Encoding.Default);

            int selRengeCounter = 0;
            bool flag = true;
            int rowCounter = 1;
            foreach (string line in lines)
            {
                int columnCounter = 1;

                string[] values = Regex.Replace(line.TrimStart(' '), @"\s+", " ").Split(' ');
               
                if (rowCounter == 4) //ім"я файлу в одній клітинці
                {
                    string[] temp = new string[3];
                    temp[0] = values[0];//generator
                    temp[1] = values[1];//is
                    temp[2] = (new Regex("<(.*)>", RegexOptions.IgnoreCase)).Match(line).ToString();//file name
                    values = temp;
                }

                foreach (string value in values)
                {
                    excellWorkSheet.Cells[rowCounter, columnCounter] = value;
                    columnCounter++;
                }

                rowCounter++;

                if (rowCounter <= 8 || !flag)
                    continue;
                if (values[0] != "")
                    selRengeCounter++;
                else
                    flag = false;
            }

            return selRengeCounter;
        }

        private static void OpenExcel(string fileName)
        {
            _Application excelapp = new Application { Visible = true };

            excelapp.Workbooks.Open(fileName,
                Type.Missing, Type.Missing, Type.Missing, Type.Missing,
                Type.Missing, Type.Missing, Type.Missing, Type.Missing,
                Type.Missing, Type.Missing, Type.Missing, Type.Missing,
                Type.Missing, Type.Missing);
        }

        private static void SaveExcelFile(string excellfilename, _Workbook excellWorkBook)
        {
            try
            {
                if (File.Exists(excellfilename))
                    File.Delete(excellfilename);

                object misValue = Missing.Value;
                excellWorkBook.SaveAs(
                    excellfilename,
                    XlFileFormat.xlWorkbookNormal,
                    misValue,
                    misValue,
                    misValue,
                    misValue,
                    XlSaveAsAccessMode.xlExclusive,
                    misValue,
                    misValue,
                    misValue,
                    misValue,
                    misValue);
            }
            catch (Exception)
            {
                throw new Exception("File occupied by another process");
            }
        }

        private static void CloseQuitAndRelease(_Application excellApp, _Worksheet excellWorkSheet, _Workbook excellWorkBook)
        {
            object misValue = Missing.Value;

            excellWorkBook.Close(true, misValue, misValue);
            excellApp.Quit();
            ReleaseObject(excellApp);
            ReleaseObject(excellWorkBook);
            ReleaseObject(excellWorkSheet);
        }

        private static void ReleaseObject(object obj)
        {
            try
            {
                Marshal.ReleaseComObject(obj);
                obj = null;
            }
            catch (Exception ex)
            {
                obj = null;
                throw new Exception(@"Exception Occured while releasing object " + ex.ToString());
            }
            finally
            {
                GC.Collect();
            }
        }
    }
}
