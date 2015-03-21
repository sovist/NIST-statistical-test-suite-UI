#pragma once

#using <mscorlib.dll>

#include "assess.h"
#include <Windows.h>
#include <typeinfo> 
#include <string>
#include <tchar.h>
#include <cstddef> // for std::size_t
#include <shellapi.h>
#include "FormAboutNIST.h"
#pragma comment(lib,"shell32.lib")
static HWND hBut; 

namespace NIST_UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading;
	using namespace System::IO;
	using namespace System::Globalization;
	using namespace System::Resources;
	using namespace System::Reflection;
	using namespace txtReportInExcel;

	/// <summary>
	/// Summary for MyForm
	/// </summary>

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public: static MyForm^ _form; // ссилка на поточну форму, щоб її закривати
	public: static String^ _newCulture; // для відкриття нової форми з іншою мовою

	public:
		MyForm(String^ culture)
		{
			InitializeComponent();
			this -> Text = "NIST Statistical Test Suite 2.1.2";
			this -> Width = 603;
			_standartWidth = this -> Width;
			_optionsWidth = _standartWidth + groupBoxOptions ->Width + 15;
			_optionsButtonClick = false;

			_initNISTParam = new InitNISTParam();

			showMessageNISTErrLock = false;

			toolStripDropDownButton1->DropDownItems[0]->Text = (gcnew CultureInfo(L"uk-UA"))->NativeName;
			toolStripDropDownButton1->DropDownItems[1]->Text = (gcnew CultureInfo(L"ru-RU"))->NativeName;
			toolStripDropDownButton1->DropDownItems[2]->Text = (gcnew CultureInfo(L"en-US"))->NativeName;
			ChangeFormLanguage(culture);

			textBoxBitStream->Text = "100";		
			checkBoxSelectAll->Checked = true;

			//додавати лише в такому порядку!
			comboBoxReadFormat->Items->Clear();
			comboBoxReadFormat->Items->Add(GetResourceManagerFildName("ReadFormatASCII"));
			comboBoxReadFormat->Items->Add(GetResourceManagerFildName("ReadFormatBinary"));
			comboBoxReadFormat ->SelectedIndex = 1;

			toolTip1->SetToolTip(buttonTest, GetResourceManagerFildName("toolTipbuttonTest"));
			toolTip1->SetToolTip(buttonTestStop, GetResourceManagerFildName("toolTipbuttonTestStop"));
			toolTip1->SetToolTip(buttonFileOfAnalysis, GetResourceManagerFildName("toolTipbuttonFileOfAnalysis"));
			toolTip1->SetToolTip(buttonOpenInExcel, GetResourceManagerFildName("toolTipbuttonOpenInExcel"));
			toolTip1->SetToolTip(buttonOpenDirectoryOfExperiments, GetResourceManagerFildName("toolTipbuttonOpenDirectoryOfExperiments"));
			toolTip1->SetToolTip(progressBar1, GetResourceManagerFildName("toolTipprogressBar1"));
			toolTip1->SetToolTip(statusStrip1, GetResourceManagerFildName("toolTiptoolStripDropDownButton1"));
			toolTip1->SetToolTip(buttonSelectFile, GetResourceManagerFildName("toolTipbuttonSelectFile"));
			toolTip1->SetToolTip(comboBoxReadFormat, GetResourceManagerFildName("toolTipcomboBoxReadFormat"));
			toolTip1->SetToolTip(radioButtonInputFile, GetResourceManagerFildName("toolTipradioButtonInputFile"));
			toolTip1->SetToolTip(labelFileSize, GetResourceManagerFildName("toolTiplabelFileSize"));
			toolTip1->SetToolTip(labelMinFileSize, GetResourceManagerFildName("toolTiplabelFileSize"));
			toolTip1->SetToolTip(textBoxN, GetResourceManagerFildName("toolTiptextBoxN"));
			toolTip1->SetToolTip(textBoxBitStream, GetResourceManagerFildName("toolTiptextBoxBitStream"));
			toolTip1->SetToolTip(checkBoxSelectAll, GetResourceManagerFildName("toolTipcheckBoxSelectAll"));
			toolTip1->SetToolTip(buttonOptions, GetResourceManagerFildName("toolTipbuttonOptions"));
			toolTip1->SetToolTip(textBoxBlockFrequency, GetResourceManagerFildName("BlockLengthForTest") + " " + labelBlockFrequency->Text);
			toolTip1->SetToolTip(textBoxNonOverlappingTemplateMatching, GetResourceManagerFildName("BlockLengthForTest") + " " + labelNonOverlappingTemplateMatching->Text);
			toolTip1->SetToolTip(textBoxOverlappingTemplateMatchinds, GetResourceManagerFildName("BlockLengthForTest") + " " + labelOverlappingTemplateMatchinds->Text);
			toolTip1->SetToolTip(textBoxApproximateEntropy, GetResourceManagerFildName("BlockLengthForTest") + " " + labelApproximateEntropy->Text);
			toolTip1->SetToolTip(textBoxSerial, GetResourceManagerFildName("BlockLengthForTest") + " " + labelSerial->Text);
			toolTip1->SetToolTip(textBoxLinearComplexity, GetResourceManagerFildName("BlockLengthForTest") + " " + labelLinearComplexity->Text);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if(Progresstrd != nullptr)
				if (Progresstrd->IsAlive)
					Progresstrd->Abort();

			if(NISTtrd != nullptr)
				if (NISTtrd->IsAlive)
					NISTtrd->Abort();

			if (components)
				delete components;

			if(_experimentDirectory != NULL)
				delete _experimentDirectory;
		}

	private: System::Windows::Forms::Button^  buttonTest;
	private: System::Windows::Forms::GroupBox^  groupBoxGeneratorSelection;
	private: System::Windows::Forms::Label^  labelMinFileSize;
	private: System::Windows::Forms::Label^  labelFileSize;

	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::Button^  buttonSelectFile;
	private: System::Windows::Forms::TextBox^  textBoxFileFullPath;
	private: System::Windows::Forms::RadioButton^  radioButtonInputFile;

	private: System::Windows::Forms::RadioButton^  radioButton10;
	private: System::Windows::Forms::RadioButton^  radioButton9;
	private: System::Windows::Forms::RadioButton^  radioButton8;
	private: System::Windows::Forms::RadioButton^  radioButton7;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::RadioButton^  radioButton4;

	private: System::Windows::Forms::GroupBox^  groupBoxStatisticalTest;

	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox7;
	private: System::Windows::Forms::CheckBox^  checkBox6;
	private: System::Windows::Forms::CheckBox^  checkBox5;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::CheckBox^  checkBoxSelectAll;

	private: System::Windows::Forms::CheckBox^  checkBox15;
	private: System::Windows::Forms::CheckBox^  checkBox14;
	private: System::Windows::Forms::CheckBox^  checkBox13;
	private: System::Windows::Forms::CheckBox^  checkBox12;
	private: System::Windows::Forms::CheckBox^  checkBox11;
	private: System::Windows::Forms::CheckBox^  checkBox10;
	private: System::Windows::Forms::CheckBox^  checkBox9;
	private: System::Windows::Forms::CheckBox^  checkBox8;
	private: System::Windows::Forms::Button^  buttonOptions;
	private: System::Windows::Forms::GroupBox^  groupBoxOptions;
	private: System::Windows::Forms::TextBox^  textBoxLinearComplexity;

	private: System::Windows::Forms::TextBox^  textBoxSerial;
	private: System::Windows::Forms::TextBox^  textBoxApproximateEntropy;
	private: System::Windows::Forms::TextBox^  textBoxOverlappingTemplateMatchinds;
	private: System::Windows::Forms::TextBox^  textBoxNonOverlappingTemplateMatching;

	private: System::Windows::Forms::TextBox^  textBoxBlockFrequency;
	private: System::Windows::Forms::Label^  labelLinearComplexity;

	private: System::Windows::Forms::Label^  labelSerial;
	private: System::Windows::Forms::Label^  labelApproximateEntropy;
	private: System::Windows::Forms::Label^  labelOverlappingTemplateMatchinds;
	private: System::Windows::Forms::Label^  labelNonOverlappingTemplateMatching;

	private: System::Windows::Forms::Label^  labelBlockFrequency;

	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Label^  labelReadFormat;

	private: System::Windows::Forms::ComboBox^  comboBoxReadFormat;
	private: System::Windows::Forms::GroupBox^  groupBoxStream;
	private: System::Windows::Forms::TextBox^  textBoxBitStream;
	private: System::Windows::Forms::TextBox^  textBoxN;

	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::GroupBox^  groupBoxReport;
	private: System::Windows::Forms::Button^  buttonFileOfAnalysis;

	private: System::Windows::Forms::Button^  buttonOpenDirectoryOfExperiments;
	private: System::Windows::Forms::Button^  buttonTestStop;
	private: System::Windows::Forms::Button^  buttonOpenInExcel;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton1;
	private: System::Windows::Forms::ToolStripMenuItem^  UA;
	private: System::Windows::Forms::ToolStripMenuItem^  Rus;
	private: System::Windows::Forms::ToolStripMenuItem^  Eng;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemViewHelp;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemAboutNIST;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::ComponentModel::IContainer^  components;

	protected: 
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->buttonTest = (gcnew System::Windows::Forms::Button());
			this->groupBoxGeneratorSelection = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonInputFile = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton8 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton9 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton10 = (gcnew System::Windows::Forms::RadioButton());
			this->labelFileSize = (gcnew System::Windows::Forms::Label());
			this->textBoxFileFullPath = (gcnew System::Windows::Forms::TextBox());
			this->labelReadFormat = (gcnew System::Windows::Forms::Label());
			this->comboBoxReadFormat = (gcnew System::Windows::Forms::ComboBox());
			this->buttonSelectFile = (gcnew System::Windows::Forms::Button());
			this->groupBoxStatisticalTest = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxSelectAll = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox8 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox9 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox10 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox11 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox12 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox13 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox14 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox15 = (gcnew System::Windows::Forms::CheckBox());
			this->buttonOptions = (gcnew System::Windows::Forms::Button());
			this->groupBoxOptions = (gcnew System::Windows::Forms::GroupBox());
			this->labelLinearComplexity = (gcnew System::Windows::Forms::Label());
			this->labelSerial = (gcnew System::Windows::Forms::Label());
			this->labelApproximateEntropy = (gcnew System::Windows::Forms::Label());
			this->labelOverlappingTemplateMatchinds = (gcnew System::Windows::Forms::Label());
			this->labelNonOverlappingTemplateMatching = (gcnew System::Windows::Forms::Label());
			this->labelBlockFrequency = (gcnew System::Windows::Forms::Label());
			this->textBoxLinearComplexity = (gcnew System::Windows::Forms::TextBox());
			this->textBoxSerial = (gcnew System::Windows::Forms::TextBox());
			this->textBoxApproximateEntropy = (gcnew System::Windows::Forms::TextBox());
			this->textBoxOverlappingTemplateMatchinds = (gcnew System::Windows::Forms::TextBox());
			this->textBoxNonOverlappingTemplateMatching = (gcnew System::Windows::Forms::TextBox());
			this->textBoxBlockFrequency = (gcnew System::Windows::Forms::TextBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->groupBoxStream = (gcnew System::Windows::Forms::GroupBox());
			this->labelMinFileSize = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBoxBitStream = (gcnew System::Windows::Forms::TextBox());
			this->textBoxN = (gcnew System::Windows::Forms::TextBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->buttonOpenInExcel = (gcnew System::Windows::Forms::Button());
			this->buttonFileOfAnalysis = (gcnew System::Windows::Forms::Button());
			this->buttonOpenDirectoryOfExperiments = (gcnew System::Windows::Forms::Button());
			this->buttonTestStop = (gcnew System::Windows::Forms::Button());
			this->groupBoxReport = (gcnew System::Windows::Forms::GroupBox());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripDropDownButton1 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->UA = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Rus = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Eng = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItemViewHelp = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripMenuItemAboutNIST = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBoxGeneratorSelection->SuspendLayout();
			this->groupBoxStatisticalTest->SuspendLayout();
			this->groupBoxOptions->SuspendLayout();
			this->groupBoxStream->SuspendLayout();
			this->groupBoxReport->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// buttonTest
			// 
			resources->ApplyResources(this->buttonTest, L"buttonTest");
			this->buttonTest->Name = L"buttonTest";
			this->buttonTest->UseVisualStyleBackColor = true;
			this->buttonTest->Click += gcnew System::EventHandler(this, &MyForm::buttonTest_Click);
			// 
			// groupBoxGeneratorSelection
			// 
			this->groupBoxGeneratorSelection->Controls->Add(this->radioButtonInputFile);
			this->groupBoxGeneratorSelection->Controls->Add(this->radioButton2);
			this->groupBoxGeneratorSelection->Controls->Add(this->radioButton3);
			this->groupBoxGeneratorSelection->Controls->Add(this->radioButton4);
			this->groupBoxGeneratorSelection->Controls->Add(this->radioButton5);
			this->groupBoxGeneratorSelection->Controls->Add(this->radioButton6);
			this->groupBoxGeneratorSelection->Controls->Add(this->radioButton7);
			this->groupBoxGeneratorSelection->Controls->Add(this->radioButton8);
			this->groupBoxGeneratorSelection->Controls->Add(this->radioButton9);
			this->groupBoxGeneratorSelection->Controls->Add(this->radioButton10);
			this->groupBoxGeneratorSelection->Controls->Add(this->labelFileSize);
			this->groupBoxGeneratorSelection->Controls->Add(this->textBoxFileFullPath);
			this->groupBoxGeneratorSelection->Controls->Add(this->labelReadFormat);
			this->groupBoxGeneratorSelection->Controls->Add(this->comboBoxReadFormat);
			this->groupBoxGeneratorSelection->Controls->Add(this->buttonSelectFile);
			resources->ApplyResources(this->groupBoxGeneratorSelection, L"groupBoxGeneratorSelection");
			this->groupBoxGeneratorSelection->Name = L"groupBoxGeneratorSelection";
			this->groupBoxGeneratorSelection->TabStop = false;
			// 
			// radioButtonInputFile
			// 
			resources->ApplyResources(this->radioButtonInputFile, L"radioButtonInputFile");
			this->radioButtonInputFile->Name = L"radioButtonInputFile";
			this->radioButtonInputFile->UseVisualStyleBackColor = true;
			this->radioButtonInputFile->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButtonInputFile_CheckedChanged);
			// 
			// radioButton2
			// 
			resources->ApplyResources(this->radioButton2, L"radioButton2");
			this->radioButton2->Checked = true;
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->TabStop = true;
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			resources->ApplyResources(this->radioButton3, L"radioButton3");
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			resources->ApplyResources(this->radioButton4, L"radioButton4");
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// radioButton5
			// 
			resources->ApplyResources(this->radioButton5, L"radioButton5");
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// radioButton6
			// 
			resources->ApplyResources(this->radioButton6, L"radioButton6");
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->UseVisualStyleBackColor = true;
			// 
			// radioButton7
			// 
			resources->ApplyResources(this->radioButton7, L"radioButton7");
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->UseVisualStyleBackColor = true;
			// 
			// radioButton8
			// 
			resources->ApplyResources(this->radioButton8, L"radioButton8");
			this->radioButton8->Name = L"radioButton8";
			this->radioButton8->UseVisualStyleBackColor = true;
			// 
			// radioButton9
			// 
			resources->ApplyResources(this->radioButton9, L"radioButton9");
			this->radioButton9->Name = L"radioButton9";
			this->radioButton9->UseVisualStyleBackColor = true;
			// 
			// radioButton10
			// 
			resources->ApplyResources(this->radioButton10, L"radioButton10");
			this->radioButton10->Name = L"radioButton10";
			this->radioButton10->UseVisualStyleBackColor = true;
			// 
			// labelFileSize
			// 
			resources->ApplyResources(this->labelFileSize, L"labelFileSize");
			this->labelFileSize->BackColor = System::Drawing::SystemColors::Control;
			this->labelFileSize->Name = L"labelFileSize";
			// 
			// textBoxFileFullPath
			// 
			resources->ApplyResources(this->textBoxFileFullPath, L"textBoxFileFullPath");
			this->textBoxFileFullPath->Name = L"textBoxFileFullPath";
			this->textBoxFileFullPath->ReadOnly = true;
			// 
			// labelReadFormat
			// 
			resources->ApplyResources(this->labelReadFormat, L"labelReadFormat");
			this->labelReadFormat->Name = L"labelReadFormat";
			// 
			// comboBoxReadFormat
			// 
			this->comboBoxReadFormat->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			resources->ApplyResources(this->comboBoxReadFormat, L"comboBoxReadFormat");
			this->comboBoxReadFormat->FormattingEnabled = true;
			this->comboBoxReadFormat->Name = L"comboBoxReadFormat";
			this->toolTip1->SetToolTip(this->comboBoxReadFormat, resources->GetString(L"comboBoxReadFormat.ToolTip"));
			this->comboBoxReadFormat->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBoxReadFormat_SelectedIndexChanged);
			// 
			// buttonSelectFile
			// 
			resources->ApplyResources(this->buttonSelectFile, L"buttonSelectFile");
			this->buttonSelectFile->Name = L"buttonSelectFile";
			this->buttonSelectFile->UseVisualStyleBackColor = true;
			this->buttonSelectFile->Click += gcnew System::EventHandler(this, &MyForm::buttonSelectFile_Click);
			// 
			// groupBoxStatisticalTest
			// 
			this->groupBoxStatisticalTest->Controls->Add(this->checkBoxSelectAll);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox1);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox2);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox3);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox4);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox5);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox6);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox7);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox8);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox9);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox10);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox11);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox12);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox13);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox14);
			this->groupBoxStatisticalTest->Controls->Add(this->checkBox15);
			resources->ApplyResources(this->groupBoxStatisticalTest, L"groupBoxStatisticalTest");
			this->groupBoxStatisticalTest->Name = L"groupBoxStatisticalTest";
			this->groupBoxStatisticalTest->TabStop = false;
			// 
			// checkBoxSelectAll
			// 
			resources->ApplyResources(this->checkBoxSelectAll, L"checkBoxSelectAll");
			this->checkBoxSelectAll->Name = L"checkBoxSelectAll";
			this->toolTip1->SetToolTip(this->checkBoxSelectAll, resources->GetString(L"checkBoxSelectAll.ToolTip"));
			this->checkBoxSelectAll->UseVisualStyleBackColor = true;
			this->checkBoxSelectAll->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectAll_CheckedChanged);
			// 
			// checkBox1
			// 
			resources->ApplyResources(this->checkBox1, L"checkBox1");
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox2
			// 
			resources->ApplyResources(this->checkBox2, L"checkBox2");
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox3
			// 
			resources->ApplyResources(this->checkBox3, L"checkBox3");
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox4
			// 
			resources->ApplyResources(this->checkBox4, L"checkBox4");
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox5
			// 
			resources->ApplyResources(this->checkBox5, L"checkBox5");
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->UseVisualStyleBackColor = true;
			this->checkBox5->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox6
			// 
			resources->ApplyResources(this->checkBox6, L"checkBox6");
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->UseVisualStyleBackColor = true;
			this->checkBox6->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox7
			// 
			resources->ApplyResources(this->checkBox7, L"checkBox7");
			this->checkBox7->Name = L"checkBox7";
			this->checkBox7->UseVisualStyleBackColor = true;
			this->checkBox7->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox8
			// 
			resources->ApplyResources(this->checkBox8, L"checkBox8");
			this->checkBox8->Name = L"checkBox8";
			this->checkBox8->UseVisualStyleBackColor = true;
			this->checkBox8->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox9
			// 
			resources->ApplyResources(this->checkBox9, L"checkBox9");
			this->checkBox9->Name = L"checkBox9";
			this->checkBox9->UseVisualStyleBackColor = true;
			this->checkBox9->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox10
			// 
			resources->ApplyResources(this->checkBox10, L"checkBox10");
			this->checkBox10->Name = L"checkBox10";
			this->checkBox10->UseVisualStyleBackColor = true;
			this->checkBox10->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox11
			// 
			resources->ApplyResources(this->checkBox11, L"checkBox11");
			this->checkBox11->Name = L"checkBox11";
			this->checkBox11->UseVisualStyleBackColor = true;
			this->checkBox11->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox12
			// 
			resources->ApplyResources(this->checkBox12, L"checkBox12");
			this->checkBox12->Name = L"checkBox12";
			this->checkBox12->UseVisualStyleBackColor = true;
			this->checkBox12->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox13
			// 
			resources->ApplyResources(this->checkBox13, L"checkBox13");
			this->checkBox13->Name = L"checkBox13";
			this->checkBox13->UseVisualStyleBackColor = true;
			this->checkBox13->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox14
			// 
			resources->ApplyResources(this->checkBox14, L"checkBox14");
			this->checkBox14->Name = L"checkBox14";
			this->checkBox14->UseVisualStyleBackColor = true;
			this->checkBox14->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// checkBox15
			// 
			resources->ApplyResources(this->checkBox15, L"checkBox15");
			this->checkBox15->Name = L"checkBox15";
			this->checkBox15->UseVisualStyleBackColor = true;
			this->checkBox15->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSelectOther_CheckedChanged);
			// 
			// buttonOptions
			// 
			resources->ApplyResources(this->buttonOptions, L"buttonOptions");
			this->buttonOptions->Name = L"buttonOptions";
			this->buttonOptions->UseVisualStyleBackColor = true;
			this->buttonOptions->Click += gcnew System::EventHandler(this, &MyForm::buttonOptions_Click);
			// 
			// groupBoxOptions
			// 
			this->groupBoxOptions->Controls->Add(this->labelLinearComplexity);
			this->groupBoxOptions->Controls->Add(this->labelSerial);
			this->groupBoxOptions->Controls->Add(this->labelApproximateEntropy);
			this->groupBoxOptions->Controls->Add(this->labelOverlappingTemplateMatchinds);
			this->groupBoxOptions->Controls->Add(this->labelNonOverlappingTemplateMatching);
			this->groupBoxOptions->Controls->Add(this->labelBlockFrequency);
			this->groupBoxOptions->Controls->Add(this->textBoxLinearComplexity);
			this->groupBoxOptions->Controls->Add(this->textBoxSerial);
			this->groupBoxOptions->Controls->Add(this->textBoxApproximateEntropy);
			this->groupBoxOptions->Controls->Add(this->textBoxOverlappingTemplateMatchinds);
			this->groupBoxOptions->Controls->Add(this->textBoxNonOverlappingTemplateMatching);
			this->groupBoxOptions->Controls->Add(this->textBoxBlockFrequency);
			resources->ApplyResources(this->groupBoxOptions, L"groupBoxOptions");
			this->groupBoxOptions->Name = L"groupBoxOptions";
			this->groupBoxOptions->TabStop = false;
			// 
			// labelLinearComplexity
			// 
			resources->ApplyResources(this->labelLinearComplexity, L"labelLinearComplexity");
			this->labelLinearComplexity->Name = L"labelLinearComplexity";
			// 
			// labelSerial
			// 
			resources->ApplyResources(this->labelSerial, L"labelSerial");
			this->labelSerial->Name = L"labelSerial";
			// 
			// labelApproximateEntropy
			// 
			resources->ApplyResources(this->labelApproximateEntropy, L"labelApproximateEntropy");
			this->labelApproximateEntropy->Name = L"labelApproximateEntropy";
			// 
			// labelOverlappingTemplateMatchinds
			// 
			resources->ApplyResources(this->labelOverlappingTemplateMatchinds, L"labelOverlappingTemplateMatchinds");
			this->labelOverlappingTemplateMatchinds->Name = L"labelOverlappingTemplateMatchinds";
			// 
			// labelNonOverlappingTemplateMatching
			// 
			resources->ApplyResources(this->labelNonOverlappingTemplateMatching, L"labelNonOverlappingTemplateMatching");
			this->labelNonOverlappingTemplateMatching->Name = L"labelNonOverlappingTemplateMatching";
			// 
			// labelBlockFrequency
			// 
			resources->ApplyResources(this->labelBlockFrequency, L"labelBlockFrequency");
			this->labelBlockFrequency->Name = L"labelBlockFrequency";
			// 
			// textBoxLinearComplexity
			// 
			resources->ApplyResources(this->textBoxLinearComplexity, L"textBoxLinearComplexity");
			this->textBoxLinearComplexity->Name = L"textBoxLinearComplexity";
			// 
			// textBoxSerial
			// 
			resources->ApplyResources(this->textBoxSerial, L"textBoxSerial");
			this->textBoxSerial->Name = L"textBoxSerial";
			// 
			// textBoxApproximateEntropy
			// 
			resources->ApplyResources(this->textBoxApproximateEntropy, L"textBoxApproximateEntropy");
			this->textBoxApproximateEntropy->Name = L"textBoxApproximateEntropy";
			// 
			// textBoxOverlappingTemplateMatchinds
			// 
			resources->ApplyResources(this->textBoxOverlappingTemplateMatchinds, L"textBoxOverlappingTemplateMatchinds");
			this->textBoxOverlappingTemplateMatchinds->Name = L"textBoxOverlappingTemplateMatchinds";
			// 
			// textBoxNonOverlappingTemplateMatching
			// 
			resources->ApplyResources(this->textBoxNonOverlappingTemplateMatching, L"textBoxNonOverlappingTemplateMatching");
			this->textBoxNonOverlappingTemplateMatching->Name = L"textBoxNonOverlappingTemplateMatching";
			// 
			// textBoxBlockFrequency
			// 
			resources->ApplyResources(this->textBoxBlockFrequency, L"textBoxBlockFrequency");
			this->textBoxBlockFrequency->Name = L"textBoxBlockFrequency";
			// 
			// progressBar1
			// 
			resources->ApplyResources(this->progressBar1, L"progressBar1");
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Step = 1;
			this->toolTip1->SetToolTip(this->progressBar1, resources->GetString(L"progressBar1.ToolTip"));
			// 
			// groupBoxStream
			// 
			this->groupBoxStream->Controls->Add(this->labelMinFileSize);
			this->groupBoxStream->Controls->Add(this->label11);
			this->groupBoxStream->Controls->Add(this->label10);
			this->groupBoxStream->Controls->Add(this->textBoxBitStream);
			this->groupBoxStream->Controls->Add(this->textBoxN);
			resources->ApplyResources(this->groupBoxStream, L"groupBoxStream");
			this->groupBoxStream->Name = L"groupBoxStream";
			this->groupBoxStream->TabStop = false;
			// 
			// labelMinFileSize
			// 
			resources->ApplyResources(this->labelMinFileSize, L"labelMinFileSize");
			this->labelMinFileSize->Name = L"labelMinFileSize";
			// 
			// label11
			// 
			resources->ApplyResources(this->label11, L"label11");
			this->label11->Name = L"label11";
			// 
			// label10
			// 
			resources->ApplyResources(this->label10, L"label10");
			this->label10->Name = L"label10";
			// 
			// textBoxBitStream
			// 
			resources->ApplyResources(this->textBoxBitStream, L"textBoxBitStream");
			this->textBoxBitStream->Name = L"textBoxBitStream";
			this->textBoxBitStream->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxBitStream_TextChanged);
			// 
			// textBoxN
			// 
			resources->ApplyResources(this->textBoxN, L"textBoxN");
			this->textBoxN->Name = L"textBoxN";
			this->textBoxN->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxBitStream_TextChanged);
			// 
			// buttonOpenInExcel
			// 
			resources->ApplyResources(this->buttonOpenInExcel, L"buttonOpenInExcel");
			this->buttonOpenInExcel->Name = L"buttonOpenInExcel";
			this->toolTip1->SetToolTip(this->buttonOpenInExcel, resources->GetString(L"buttonOpenInExcel.ToolTip"));
			this->buttonOpenInExcel->UseVisualStyleBackColor = true;
			this->buttonOpenInExcel->Click += gcnew System::EventHandler(this, &MyForm::buttonOpenInExcel_Click);
			// 
			// buttonFileOfAnalysis
			// 
			resources->ApplyResources(this->buttonFileOfAnalysis, L"buttonFileOfAnalysis");
			this->buttonFileOfAnalysis->Name = L"buttonFileOfAnalysis";
			this->toolTip1->SetToolTip(this->buttonFileOfAnalysis, resources->GetString(L"buttonFileOfAnalysis.ToolTip"));
			this->buttonFileOfAnalysis->UseVisualStyleBackColor = true;
			this->buttonFileOfAnalysis->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// buttonOpenDirectoryOfExperiments
			// 
			resources->ApplyResources(this->buttonOpenDirectoryOfExperiments, L"buttonOpenDirectoryOfExperiments");
			this->buttonOpenDirectoryOfExperiments->Name = L"buttonOpenDirectoryOfExperiments";
			this->toolTip1->SetToolTip(this->buttonOpenDirectoryOfExperiments, resources->GetString(L"buttonOpenDirectoryOfExperiments.ToolTip"));
			this->buttonOpenDirectoryOfExperiments->UseVisualStyleBackColor = true;
			this->buttonOpenDirectoryOfExperiments->Click += gcnew System::EventHandler(this, &MyForm::buttonOpenDirectoryOfExperiments_Click);
			// 
			// buttonTestStop
			// 
			resources->ApplyResources(this->buttonTestStop, L"buttonTestStop");
			this->buttonTestStop->Name = L"buttonTestStop";
			this->toolTip1->SetToolTip(this->buttonTestStop, resources->GetString(L"buttonTestStop.ToolTip"));
			this->buttonTestStop->UseVisualStyleBackColor = true;
			this->buttonTestStop->Click += gcnew System::EventHandler(this, &MyForm::buttonTestStop_Click);
			// 
			// groupBoxReport
			// 
			this->groupBoxReport->Controls->Add(this->buttonOpenInExcel);
			this->groupBoxReport->Controls->Add(this->buttonFileOfAnalysis);
			this->groupBoxReport->Controls->Add(this->buttonOpenDirectoryOfExperiments);
			resources->ApplyResources(this->groupBoxReport, L"groupBoxReport");
			this->groupBoxReport->Name = L"groupBoxReport";
			this->groupBoxReport->TabStop = false;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripStatusLabel1, 
				this->toolStripDropDownButton1});
			resources->ApplyResources(this->statusStrip1, L"statusStrip1");
			this->statusStrip1->Name = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			resources->ApplyResources(this->toolStripStatusLabel1, L"toolStripStatusLabel1");
			// 
			// toolStripDropDownButton1
			// 
			this->toolStripDropDownButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripDropDownButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->UA, 
				this->Rus, this->Eng});
			resources->ApplyResources(this->toolStripDropDownButton1, L"toolStripDropDownButton1");
			this->toolStripDropDownButton1->Name = L"toolStripDropDownButton1";
			// 
			// UA
			// 
			this->UA->Name = L"UA";
			resources->ApplyResources(this->UA, L"UA");
			this->UA->Click += gcnew System::EventHandler(this, &MyForm::UA_Click);
			// 
			// Rus
			// 
			this->Rus->Name = L"Rus";
			resources->ApplyResources(this->Rus, L"Rus");
			this->Rus->Click += gcnew System::EventHandler(this, &MyForm::Rus_Click);
			// 
			// Eng
			// 
			this->Eng->Name = L"Eng";
			resources->ApplyResources(this->Eng, L"Eng");
			this->Eng->Click += gcnew System::EventHandler(this, &MyForm::Eng_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripMenuItem1});
			resources->ApplyResources(this->menuStrip1, L"menuStrip1");
			this->menuStrip1->Name = L"menuStrip1";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripMenuItemViewHelp, 
				this->toolStripSeparator1, this->toolStripMenuItemAboutNIST});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			resources->ApplyResources(this->toolStripMenuItem1, L"toolStripMenuItem1");
			// 
			// toolStripMenuItemViewHelp
			// 
			this->toolStripMenuItemViewHelp->Name = L"toolStripMenuItemViewHelp";
			resources->ApplyResources(this->toolStripMenuItemViewHelp, L"toolStripMenuItemViewHelp");
			this->toolStripMenuItemViewHelp->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItemViewHelp_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			resources->ApplyResources(this->toolStripSeparator1, L"toolStripSeparator1");
			// 
			// toolStripMenuItemAboutNIST
			// 
			this->toolStripMenuItemAboutNIST->Name = L"toolStripMenuItemAboutNIST";
			resources->ApplyResources(this->toolStripMenuItemAboutNIST, L"toolStripMenuItemAboutNIST");
			this->toolStripMenuItemAboutNIST->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItemAboutNIST_Click);
			// 
			// MyForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->buttonTestStop);
			this->Controls->Add(this->groupBoxReport);
			this->Controls->Add(this->groupBoxStream);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->groupBoxOptions);
			this->Controls->Add(this->buttonOptions);
			this->Controls->Add(this->groupBoxStatisticalTest);
			this->Controls->Add(this->buttonTest);
			this->Controls->Add(this->groupBoxGeneratorSelection);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->groupBoxGeneratorSelection->ResumeLayout(false);
			this->groupBoxGeneratorSelection->PerformLayout();
			this->groupBoxStatisticalTest->ResumeLayout(false);
			this->groupBoxStatisticalTest->PerformLayout();
			this->groupBoxOptions->ResumeLayout(false);
			this->groupBoxOptions->PerformLayout();
			this->groupBoxStream->ResumeLayout(false);
			this->groupBoxStream->PerformLayout();
			this->groupBoxReport->ResumeLayout(false);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: int _standartWidth;
			 int _optionsWidth;
			 bool _optionsButtonClick;
			 InitNISTParam* _initNISTParam;
			 char* _experimentDirectory;
			 Thread^ Progresstrd;
			 Thread^ NISTtrd;
			 double _streamSize;
			 double _fileSizeWithReadFormat;
			 double _fileSize;
			 DateTime _startTime;

	private: 
		void buttonTest_Click(Object^  sender, EventArgs^  e) 
		{
			bool leastOneTestIsSelected = false;

			for each (Control^ control in groupBoxStatisticalTest ->Controls)
				if(control->GetType() == CheckBox::typeid)
					if(((CheckBox^)control)->Text != "Select All")
						if(((CheckBox^)control)->Checked)
						{
							leastOneTestIsSelected = true;
							break;
						}

						if(!leastOneTestIsSelected)
						{
							MessageBox::Show(GetResourceManagerFildName("SelectTest"), Text, MessageBoxButtons::OK, MessageBoxIcon::Warning);
							return;
						} 

						if(radioButtonInputFile->Checked && textBoxFileFullPath ->Text == String::Empty)
						{
							MessageBox::Show(GetResourceManagerFildName("SelectInputFile"), Text, MessageBoxButtons::OK, MessageBoxIcon::Warning);
							return;
						}   

						if(GetGenertorSelectionIndex() == -1)
						{
							MessageBox::Show("Error: Genertor Selection", Text,  MessageBoxButtons::OK, MessageBoxIcon::Warning);
							return;
						} 

						if (CheckFileSizeAndStreamSize() && radioButtonInputFile->Checked)
						{
							MessageBox::Show(GetResourceManagerFildName("ErrorMinimumLength"), Text,  MessageBoxButtons::OK, MessageBoxIcon::Warning);
							return;
						}

						try
						{  
							GenerateExperimentsDirs();

							_initNISTParam->SetApproximateEntropyBlockLength(int::Parse(textBoxApproximateEntropy->Text));
							_initNISTParam->SetBlockFrequencyBlockLength(int::Parse(textBoxBlockFrequency ->Text));
							_initNISTParam->SetLinearComplexitySequenceLength(int::Parse(textBoxLinearComplexity ->Text));
							_initNISTParam->SetNonOverlappingTemplateBlockLength(int::Parse(textBoxNonOverlappingTemplateMatching ->Text));
							_initNISTParam->SetOverlappingTemplateBlockLength(int::Parse(textBoxOverlappingTemplateMatchinds ->Text));
							_initNISTParam->SetSerialBlockLength(int::Parse(textBoxSerial ->Text));

							_initNISTParam->SetN(int::Parse(textBoxN ->Text));
							_initNISTParam->SetNumOfBitStreams(int::Parse(textBoxBitStream ->Text));

							_initNISTParam->SetInputFileName((char*)(void*)Marshal::StringToHGlobalAnsi(textBoxFileFullPath->Text));
							_initNISTParam->SetReadFileMode(comboBoxReadFormat->SelectedIndex);

							/*char **t = new char*[2];
							t[0] = (char*)(void*)Marshal::StringToHGlobalAnsi(Environment::CurrentDirectory);
							t[1] = (char*)(void*)Marshal::StringToHGlobalAnsi("1000");*/

							_initNISTParam->SetGenertorSelectionIndex(GetGenertorSelectionIndex());
							_initNISTParam->SetStatisticalTestVector(GetStatisticalTestVector());
							_initNISTParam->SetCulture((char*)(void*)Marshal::StringToHGlobalAnsi(_currentCulture));

							groupBoxGeneratorSelection->Enabled = false;
							groupBoxStatisticalTest->Enabled = false;
							groupBoxOptions->Enabled = false;
							groupBoxReport->Enabled = false;                          
							groupBoxStream->Enabled = false;
							buttonTest->Enabled = false;
							statusStrip1->Enabled = false;
							buttonTestStop->Enabled = true;

							_initNISTParam->ResetProgress();
							progressBar1->Value = 0;
							progressBar1->Maximum = _initNISTParam->GetMaxProgress();//int::Parse(textBoxBitStream ->Text);

							Progresstrd = gcnew Thread(gcnew ThreadStart(this, &NIST_UI::MyForm::UpdateProgress));
							Progresstrd->IsBackground = true;
							Progresstrd->Start();

							NISTtrd = gcnew Thread(gcnew ThreadStart(this, &NIST_UI::MyForm::NIST_Proc));
							NISTtrd->IsBackground = true;
							_startTime = DateTime::Now;
							NISTtrd->Start();
							progressBar1->Visible = true;

							Application::UseWaitCursor = true;
						}
						catch(Exception^ e)
						{
							MessageBox::Show("Tests error!\n" + e->Message, "NIST", MessageBoxButtons::OK, MessageBoxIcon::Error);
							return;                                
						}
		}

		delegate void DelegateThreadTask();
	private: 
		void ThreadTask()
		{
			if (!progressBar1->InvokeRequired)
			{
				progressBar1->Value = _initNISTParam->GetProgress();
				Application::DoEvents();
			}
			else 
			{
				DelegateThreadTask^ myThreadDelegate = gcnew DelegateThreadTask(this, &NIST_UI::MyForm::ThreadTask);      
				this->Invoke(myThreadDelegate);			
			}
		}

		delegate void DelegateTestDone();
	private: void TestDone()
			 {
				 if (!progressBar1->InvokeRequired)
				 {
					 progressBar1->Visible = false;

					 groupBoxGeneratorSelection->Enabled = true;
					 groupBoxStatisticalTest->Enabled = true;
					 groupBoxOptions->Enabled = true;                                           
					 groupBoxStream->Enabled = true;
					 buttonTest->Enabled = true;
					 statusStrip1->Enabled = true;
					 buttonTestStop->Enabled = false;

					 if(!showMessageNISTErrLock)
					 {
						 groupBoxReport->Enabled = true; 
						 MessageBox::Show(GetResourceManagerFildName("TestsIsdone") + " " +(DateTime::Now - _startTime).ToString()->Substring(0, 11), 
							 "NIST", MessageBoxButtons::OK, MessageBoxIcon::Information);
					 }
					 Application::DoEvents();
					 Application::UseWaitCursor = false;
				 }
				 else 
				 {
					 DelegateTestDone^ myThreadDelegate = gcnew DelegateTestDone(this, &NIST_UI::MyForm::TestDone);      
					 this->Invoke(myThreadDelegate);			
				 }

				 showMessageNISTErrLock = false;
			 }

	private: 
		void UpdateProgress()
		{	
			while(true)
			{
				ThreadTask();
				Thread::Sleep(100);

				if (!NISTtrd->IsAlive)
				{
					ThreadTask();
					Thread::Sleep(900);//показати прогрес завершеним;
					TestDone();
					Progresstrd->Abort();                         
				}
			}
		}

		bool showMessageNISTErrLock;
	private: void NIST_Proc()
			 {	              
				 try
				 {
					 _experimentDirectory = NIST_Main(_initNISTParam);    
				 }

				 catch(Exception^ e)
				 {
					 if(!showMessageNISTErrLock)
						 MessageBox::Show("Tests error!\n" + e->Message, "NIST", MessageBoxButtons::OK, MessageBoxIcon::Error);  
					 showMessageNISTErrLock = true;
				 }
			 }

			 wstring s2ws(const string& s)
			 {
				 int slength = (int)s.length() + 1;
				 int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 

				 wchar_t* buf = new wchar_t[len];
				 MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);

				 wstring r(buf);
				 delete[] buf;
				 return r;
			 }

			 int GetGenertorSelectionIndex()
			 {      
				 for (int i = 0; i < groupBoxGeneratorSelection ->Controls ->Count; i++)
					 if(groupBoxGeneratorSelection ->Controls[i]->GetType() == RadioButton::typeid)
						 if( ((RadioButton^)groupBoxGeneratorSelection ->Controls[i])->Checked)
							 return i;
				 return -1;
			 }

			 int* GetStatisticalTestVector()
			 {  
				 int* vector = new int[16];

				 for (int i = 0; i < groupBoxStatisticalTest ->Controls ->Count/*16*/; i++)
					 if(groupBoxStatisticalTest ->Controls[i]->GetType() == CheckBox::typeid)
						 if(((CheckBox^)groupBoxStatisticalTest ->Controls[i])->Checked)
							 vector[i] = 1;
						 else
							 vector[i] = 0;

				 return vector;
			 }

	private: 
		System::Void buttonOptions_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			_optionsButtonClick = !_optionsButtonClick;

			if(_optionsButtonClick)
			{
				buttonOptions ->Text = GetResourceManagerFildName("buttonOptionsClose"); 
				this -> Width = _optionsWidth;
			}
			else
			{
				buttonOptions ->Text = GetResourceManagerFildName("buttonOptionsOpen"); 
				this -> Width = _standartWidth;
			}
		}

	private: bool lockSelectedEvent;
	private: 
		System::Void checkBoxSelectAll_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			if(!lockSelectedEvent)
			{
				lockSelectedEvent = true;

				for each (Control^ control in groupBoxStatisticalTest ->Controls)
					if(control->GetType() == CheckBox::typeid)
						if(((CheckBox^)control)->Name != "checkBoxSelectAll")
							((CheckBox^)control)->Checked = checkBoxSelectAll->Checked;

				lockSelectedEvent = false;
			}
		}

	private: 
		System::Void checkBoxSelectOther_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			if(!lockSelectedEvent)
			{
				lockSelectedEvent = true;

				int selectedNumbers = 0;

				for each (Control^ control in groupBoxStatisticalTest ->Controls)
					if(control->GetType() == CheckBox::typeid)
						if(((CheckBox^)control)->Name != "checkBoxSelectAll")
							if(((CheckBox^)control)->Checked)
								selectedNumbers++;

				checkBoxSelectAll->Checked = selectedNumbers == 15;

				lockSelectedEvent = false;
			}

			if(((CheckBox^)sender)->Text == "Block Frequency")
				ChangeEnable(textBoxBlockFrequency, labelBlockFrequency);

			if(((CheckBox^)sender)->Text == "Non-overlapping Template Matching")
				ChangeEnable(textBoxNonOverlappingTemplateMatching, labelNonOverlappingTemplateMatching);

			if(((CheckBox^)sender)->Text == "Overlapping Template Matchings")
				ChangeEnable(textBoxOverlappingTemplateMatchinds, labelOverlappingTemplateMatchinds);

			if(((CheckBox^)sender)->Text == "Approximate Entropy")
				ChangeEnable(textBoxApproximateEntropy, labelApproximateEntropy);

			if(((CheckBox^)sender)->Text == "Serial")
				ChangeEnable(textBoxSerial, labelSerial);

			if(((CheckBox^)sender)->Text == "Linear Complexity")
				ChangeEnable(textBoxLinearComplexity, labelLinearComplexity);
		}

	private: 
		void ChangeEnable(TextBox^ textBox, Label^ label)
		{
			textBox->Enabled = !textBox->Enabled;
			label->Enabled = !label->Enabled;
		}

	private: 
		System::Void buttonSelectFile_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			OpenFileDialog^ openFile = gcnew OpenFileDialog();
			openFile->InitialDirectory = Environment::CurrentDirectory;

			if(openFile->ShowDialog(this) == System::Windows::Forms::DialogResult::OK )
			{
				radioButtonInputFile->Checked = true;
				textBoxFileFullPath->Text = openFile->FileName;
				_fileSize = (double)FileInfo(openFile->FileName).Length;
				comboBoxReadFormat_SelectedIndexChanged( gcnew Object(), gcnew EventArgs());
			}
			CheckFileSizeAndStreamSize();
		}

	private: 
		System::Void comboBoxReadFormat_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			if(comboBoxReadFormat->SelectedIndex == 1 /*"Binary"*/)
				_fileSizeWithReadFormat = _fileSize;
			else
				_fileSizeWithReadFormat = _fileSize / 8;

			labelFileSize->Text = GetResourceManagerFildName("FileSize") + " " + ((_fileSizeWithReadFormat == 0) ? "-" : (FileSizeBit(_fileSizeWithReadFormat * 8) + " = " + FileSizeByte(_fileSizeWithReadFormat)));	
			CheckFileSizeAndStreamSize();
		}

	private: System::Void radioButtonInputFile_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
			 {
				 if(radioButtonInputFile->Checked)
				 {
					 buttonSelectFile->Enabled = true;
					 textBoxFileFullPath ->Enabled = true;
					 comboBoxReadFormat ->Enabled = true;
					 labelReadFormat ->Enabled = true;
					 //labelMinFileSize->Enabled = true;
					 labelFileSize->Enabled = true;
				 }
				 else
				 {
					 buttonSelectFile->Enabled = false;
					 textBoxFileFullPath ->Enabled = false;
					 comboBoxReadFormat ->Enabled = false;
					 labelReadFormat ->Enabled = false;
					 //labelMinFileSize->Enabled = false;
					 labelFileSize->Enabled = false;
					 labelMinFileSize->BackColor = BackColor.Transparent;
					 labelFileSize->BackColor = BackColor.Transparent;
				 }

				 textBoxBitStream_TextChanged(gcnew Object(), gcnew EventArgs());
				 CheckFileSizeAndStreamSize();
			 }

	private: 
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			ShellExecute ( NULL, TEXT("open"), s2ws(string(_experimentDirectory) + "finalAnalysisReport.txt").c_str(), NULL, NULL, SW_SHOWNORMAL );
		}

	private: 
		System::Void buttonOpenDirectoryOfExperiments_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			ShellExecute ( NULL, TEXT("open"), s2ws(string(_experimentDirectory)).c_str(), NULL, NULL, SW_SHOWNORMAL );
		}

	private: 
		void GenerateExperimentsDirs()
		{
			wstring experimentsDirectory = (s2ws((char*)(void*)Marshal::StringToHGlobalAnsi(Environment::CurrentDirectory)) + s2ws(string("\\experiments")));

			String^ experimentsDir = gcnew String(experimentsDirectory.c_str());

			if(!Directory::Exists(experimentsDir))
				Directory::CreateDirectory(experimentsDir);

			const string algorithmNames[] = { "AlgorithmTesting", "LCG", "QCG1", "QCG2","CCG", "XOR", "MODEXP", "BBS", "MS", "G-SHA1"};
			int algorithmNamesLenght = 10;

			const string testNames[] = { "Frequency", "BlockFrequency", "CumulativeSums", "Runs", "LongestRun", "Rank","FFT", "NonOverlappingTemplate", 
										 "OverlappingTemplate", "Universal", "ApproximateEntropy", "RandomExcursions", "RandomExcursionsVariant", "Serial", "LinearComplexity" };
			int testNamesLenght = 15;

			for (int i = 0; i < algorithmNamesLenght; i++)
			{
				String^ algorithmDir = gcnew String(algorithmNames[i].c_str());
				algorithmDir = experimentsDir + "\\" + algorithmDir;

				if(!Directory::Exists(algorithmDir))
					Directory::CreateDirectory(algorithmDir);

				for (int j = 0; j < testNamesLenght; j++)
				{
					String^ testDir = gcnew String(testNames[j].c_str());
					testDir = algorithmDir + "\\" + testDir;

					if(!Directory::Exists(testDir))
						Directory::CreateDirectory(testDir);
				}
			}
		}

	private: 
		System::Void buttonTestStop_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			showMessageNISTErrLock = true;

			if(NISTtrd != nullptr)
				if (NISTtrd->IsAlive)
					NISTtrd->Abort();

			if(Progresstrd != nullptr)
				if (Progresstrd->IsAlive)
					Progresstrd->Abort();

			TestDone();

			showMessageNISTErrLock = false;
		}

	private: 
		System::Void buttonOpenInExcel_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			buttonOpenInExcel->Text = GetResourceManagerFildName("buttonOpenInExcelWait");
			buttonOpenInExcel->Enabled = false;
			Application::UseWaitCursor = true;
			Application::DoEvents();

			TxtInExcel^  txtInExcel = gcnew TxtInExcel();
			try
			{
				txtInExcel->Open(gcnew String((string(_experimentDirectory) + "finalAnalysisReport.txt").c_str()), 
					gcnew String(string(_experimentDirectory).c_str()),
					gcnew String("finalAnalysisReport.xls") );
			}
			catch(Exception^ ex)
			{
				txtInExcel->Dispose_();
				MessageBox::Show(ex->Message);
			}

			Application::UseWaitCursor = false;
			buttonOpenInExcel->Enabled = true;
			buttonOpenInExcel->Text = GetResourceManagerFildName("buttonOpenInExcelOpeninMSExcel");
		}

	private: String^ _currentCulture;
	private: void ChangeFormLanguage(String^ newLanguageString)
			 {
				 _currentCulture = newLanguageString;

				 ChangeCulture(newLanguageString, MyForm::Controls);
				 ChangeCulture(newLanguageString, groupBoxGeneratorSelection->Controls);
				 ChangeCulture(newLanguageString, groupBoxOptions->Controls);
				 ChangeCulture(newLanguageString, groupBoxReport->Controls);
				 ChangeCulture(newLanguageString, groupBoxStatisticalTest->Controls);
				 ChangeCulture(newLanguageString, groupBoxStream->Controls);
				 ChangeCulture(newLanguageString, statusStrip1->Controls);

				 ComponentResourceManager^ resources = gcnew ComponentResourceManager(MyForm::GetType());
				 CultureInfo^ newCultureInfo = gcnew CultureInfo(newLanguageString);

				 resources->ApplyResources(toolStripStatusLabel1, toolStripStatusLabel1->Name, newCultureInfo);
				 resources->ApplyResources(toolStripMenuItem1, toolStripMenuItem1->Name, newCultureInfo);
				 resources->ApplyResources(toolStripMenuItemViewHelp, toolStripMenuItemViewHelp->Name, newCultureInfo);
				 resources->ApplyResources(toolStripMenuItemAboutNIST, toolStripMenuItemAboutNIST->Name, newCultureInfo);

				 toolStripDropDownButton1->Text = newCultureInfo->NativeName;

				 for each (ToolStripMenuItem^ languageButton in toolStripDropDownButton1->DropDownItems)
					 languageButton->Checked = (languageButton->Text == toolStripDropDownButton1->Text);
			 }

	private: 
		void ChangeCulture(String^ newLanguageString, Control::ControlCollection^ controls)
		{
			ComponentResourceManager^ resources = gcnew ComponentResourceManager(MyForm::GetType());

			CultureInfo^ newCultureInfo = gcnew CultureInfo(newLanguageString);

			for each (Control^ control in controls)
				resources->ApplyResources(control, control->Name, newCultureInfo);
		}

	private: 
		System::Void UA_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			_newCulture = "uk-UA";
			_form->Close();
			//ChangeFormLanguage("uk-UA");
		}

	private: 
		System::Void Rus_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			_newCulture = "ru-RU";
			_form->Close();
			//ChangeFormLanguage("ru-RU");
		}
	private: 
		System::Void Eng_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			_newCulture = "en-US";
			_form->Close();
			//ChangeFormLanguage("en-US");
		}

	private: 
		System::Void toolStripMenuItemViewHelp_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			String^ helpFile = Environment::CurrentDirectory + "\\help\\nist_hlp_" + _currentCulture + ".chm";

			string stringHelpFile = string("hh.exe ") +  (char*)(void*)Marshal::StringToHGlobalAnsi(helpFile);

			WinExec( stringHelpFile.c_str(), SW_RESTORE);
		}

	private: 
		String^ GetResourceManagerFildName(String^ stringName)
		{
			return (gcnew ResourceManager("NIST_UI." + _currentCulture, MyForm::typeid->Assembly))->GetString(stringName);
		}

	private: 
		System::Void toolStripMenuItemAboutNIST_Click(System::Object^  sender, System::EventArgs^  e) 
		{      
			FormAboutNIST^ form = gcnew FormAboutNIST(_currentCulture, toolStripMenuItemAboutNIST->Text);
			form->Show();
			form->Left = this->Left + 40;
			form->Top = this->Top +80;
		}

	private: 
		System::Void textBoxBitStream_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			textBoxBitStream->Width = TextRenderer::MeasureText(textBoxBitStream->Text, textBoxBitStream->Font).Width + 15;
			textBoxN->Width = TextRenderer::MeasureText(textBoxN->Text, textBoxBitStream->Font).Width + 15;

			try
			{
				double bitStream = double::Parse(textBoxBitStream->Text);
				double n = double::Parse(textBoxN->Text);

				if (bitStream < 0 || n < 0)
					throw gcnew Exception();

				_streamSize = (n*bitStream)/8;
				labelMinFileSize->Text = (radioButtonInputFile->Checked ? GetResourceManagerFildName("MinFileSize") : GetResourceManagerFildName("ExploreStream"))+ 
					                     " " + FileSizeBit(_streamSize * 8) + " = " + FileSizeByte(_streamSize);
			}
			catch(Exception^ )
			{
				_streamSize = 0;
				labelMinFileSize->Text = (radioButtonInputFile->Checked ? GetResourceManagerFildName("MinFileSize") : GetResourceManagerFildName("ExploreStream")) + " -";
			}

			CheckFileSizeAndStreamSize();
		}

	private: 
		String^ FileSizeByte(double size)
		{
			return getDegree(size, 1024) + "byte";
		}
	private: 
		String^ FileSizeBit(double size)
		{
			return getDegree(size, 1000) + "bit";
		}
	private: 
		String^ getDegree(double size, double divider)
		{
			array<String^>^ degree = gcnew array<String^>{"", "K", "M", "G"};
			int index = 0;
			for ( ; size >= divider && index < 4; index++)
				size /= divider;

			return size.ToString("f2") + " " + degree[index];
		}
		
	private: 
		bool CheckFileSizeAndStreamSize()
		{	
			if(labelFileSize->Enabled)
				if (_streamSize < _fileSizeWithReadFormat)
				{
					labelFileSize->BackColor = BackColor.LightGreen;
					labelMinFileSize->BackColor = BackColor.LightGreen;
				}
				else
				{
					labelFileSize->BackColor = BackColor.FromArgb(255, 192, 192);
					labelMinFileSize->BackColor = BackColor.FromArgb(255, 192, 192);
				}

				return _streamSize >= _fileSizeWithReadFormat;
		}
	};
}