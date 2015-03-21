#include "MyForm.h"
#include <windows.h>

using namespace NIST_UI;


[STAThreadAttribute]//for openFileDialog in Debug Mode

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)//only WinForms
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                       _In_opt_ HINSTANCE hPrevInstance,
                       _In_ LPTSTR    lpCmdLine,
                       _In_ int       nCmdShow)
//int main()//console windows with WinForms
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	MyForm::_newCulture = CultureInfo::CurrentCulture->Name;

	if (!(MyForm::_newCulture == "en-US" || MyForm::_newCulture == "ru-RU" || MyForm::_newCulture == "uk-UA"))
		MyForm::_newCulture = "en-US";
	
	while (MyForm::_newCulture != "")//зміна мови
	{  
	  MyForm::_form = gcnew MyForm(MyForm::_newCulture);
	  MyForm::_newCulture = "";
	  Application::Run(MyForm::_form);
	}

	return 0;
}

