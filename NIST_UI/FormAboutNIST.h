#pragma once

namespace NIST_UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;

	/// <summary>
	/// Summary for FormAboutNIST
	/// </summary>
	public ref class FormAboutNIST : public System::Windows::Forms::Form
	{

	private:
		String^ _nistVersion;
		String^ _nist;
		String^ _kafelec;
		String^ _nau;
		String^ _abelnau;
		String^ _sg6336;
		String^ _sovist9;

	public:
		FormAboutNIST(String^ culture, String^ formName)
		{
			InitializeComponent();
          	
			_nistVersion = "www.csrc.nist.gov/groups/ST/toolkit/rng/documentation_software.html";
		    _nist = "www.nist.gov";
		    _kafelec = "www.kafelec.nau.edu.ua";
		    _nau = "www.nau.edu.ua";
		    _abelnau = "mailto:abelnau@ukr.net";
		    _sg6336 = "mailto:sg6336@yandex.ua";
		    _sovist9 = "mailto:sovist9@mail.ru";

			this->Text = formName;

			AddInfoAboutAuthors(linkLabelAutors, culture);
			AddInfoAboutVersion(linkLabelVer, culture);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormAboutNIST()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::LinkLabel^  linkLabelVer;
	private: System::Windows::Forms::LinkLabel^  linkLabelAutors;


	protected: 
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormAboutNIST::typeid));
			this->linkLabelVer = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabelAutors = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// linkLabelVer
			// 
			resources->ApplyResources(this->linkLabelVer, L"linkLabelVer");
			this->linkLabelVer->Name = L"linkLabelVer";
			this->linkLabelVer->TabStop = true;
			this->linkLabelVer->UseCompatibleTextRendering = true;
			this->linkLabelVer->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &FormAboutNIST::linkLabelVer_LinkClicked);
			// 
			// linkLabelAutors
			// 
			resources->ApplyResources(this->linkLabelAutors, L"linkLabelAutors");
			this->linkLabelAutors->Name = L"linkLabelAutors";
			this->linkLabelAutors->TabStop = true;
			this->linkLabelAutors->UseCompatibleTextRendering = true;
			this->linkLabelAutors->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &FormAboutNIST::linkLabelAutor_LinkClicked);
			// 
			// FormAboutNIST
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->linkLabelAutors);
			this->Controls->Add(this->linkLabelVer);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Name = L"FormAboutNIST";
			this->ResumeLayout(false);

		}

#pragma endregion

private: 
	System::Void linkLabelVer_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) 
	{
		linkLabeClicked(linkLabelVer, e);
	}

private: 
	System::Void linkLabelAutor_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) 
	{
		linkLabeClicked(linkLabelAutors, e);
	}

private:
	void linkLabeClicked(LinkLabel^ linkLabel, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e)
	{
		linkLabel->Links[ linkLabel->Links->IndexOf( e->Link ) ]->Visited = true;

		String^ target = dynamic_cast<String^>(e->Link->LinkData);

		if(nullptr != target)		
			System::Diagnostics::Process::Start( target );
	}

private: 
	void AddInfoAboutAuthors(LinkLabel^ linkLabel, String^ culture)
	{	
		if (culture == "uk-UA")
		{
			linkLabel->Text = 
				"Графічний інтерфейс розроблений на кафедрі електроніки \n"+
				"Національного авіаційного університету, Київ - 2014.   \n\n"+

				"Автори:\n" +  
				"Білецький Анатолій Якович, доктор технічних наук, професор.\n" + 				
				"E-mail: abelnau@ukr.net\n\n" +

				"Навроцький Денис Олександрович, аспірант.\n" +
				"E-mail: sg6336@yandex.ua\n\n" +

				"Семенюк Олександр Іванович, бакалавр.\n" + 
				"E-mail: sovist9@mail.ru";
			linkLabel->Links->Add(35, 19, _kafelec);
			linkLabel->Links->Add(56, 38, _nau);
			linkLabel->Links->Add(189, 15, _abelnau);
			linkLabel->Links->Add(256, 16, _sg6336);
			linkLabel->Links->Add(320, 15, _sovist9);
		}

		if (culture == "ru-RU")
		{
			linkLabel->Text = 
				"Графический интерфейс разработан на кафедре электроники \n" + 
				"Национального авиационного университета, Киев - 2014.   \n\n" + 

				"Авторы: \n" + 
				"Белецкий Анатолий Яковлевич, доктор технических наук, профессор. \n" + 
				"E-mail: abelnau@ukr.net \n\n" + 

				"Навроцкий Денис Александрович, аспирант. \n" + 
				"E-mail: sg6336@yandex.ua \n\n" + 

				"Семенюк Александр Иванович, бакалавр. \n" + 
				"E-mail: sovist9@mail.ru";
			linkLabel->Links->Add(36, 19, _kafelec);
			linkLabel->Links->Add(56, 40, _nau);
			linkLabel->Links->Add(198, 15, _abelnau);
			linkLabel->Links->Add(266, 16, _sg6336);
			linkLabel->Links->Add(332, 15, _sovist9);
		}

		if (culture == "en-US")
		{
			linkLabel->Text = 
				"GUI developed at the Department of Electronics \n" +
				"National Aviation University, Kyiv - 2014. \n\n" +

				"Authors: \n" +
				"Beletsky Anatoly, PhD, professor. \n" +
				"E-mail: abelnau@ukr.net \n\n" +

				"Navrotskyi Denys, a graduate student. \n" +
				"E-mail: sg6336@yandex.ua \n\n" +

				"Semeniuk Alexander, BA. \n" +
				"E-mail: sovist9@mail.ru";
			linkLabel->Links->Add(21, 25, _kafelec);
			linkLabel->Links->Add(47, 29, _nau);
			linkLabel->Links->Add(146, 15, _abelnau);
			linkLabel->Links->Add(211, 16, _sg6336);
			linkLabel->Links->Add(263, 15, _sovist9);
		}
	}

private:
	void AddInfoAboutVersion(LinkLabel^ linkLabel, String^ culture)
	{	

		if (culture == "uk-UA")
		{
			linkLabel->Text = "Версія NIST STS: 2.1.2 від 9 липня 2014";
			linkLabel->Links->Add(7, 4, _nist);
			linkLabel->Links->Add(17, 22, _nistVersion);
		}

		if (culture == "ru-RU")
		{
			linkLabel->Text = "Версия NIST STS: 2.1.2 от 9 июля 2014";
			linkLabel->Links->Add(7, 4, _nist);
			linkLabel->Links->Add(17, 20, _nistVersion);
		}

		if (culture == "en-US")
		{
			linkLabel->Text = "Version NIST STS: 2.1.2 on July 9, 2014";
			linkLabel->Links->Add(8, 4, _nist);
			linkLabel->Links->Add(18, 21, _nistVersion);
		}
	}
};
}
