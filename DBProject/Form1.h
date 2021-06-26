//Resources:
//Windows Forms Projects with C++ in Visual Studio 2019 https://www.rkaiser.de/wp-content/uploads/2019/04/cpp-2019-WinForms-Anleitung-EN.pdf
//string to system::string				https://docs.microsoft.com/en-us/cpp/dotnet/how-to-convert-standard-string-to-system-string?view=msvc-160
//embed files in winforms				https://www.youtube.com/watch?v=lxbUcU4Q5Fk
//Create a text file and write in it	https://www.youtube.com/watch?v=2NIUS-0ZlcQ
//datagridrow							https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.datagridview?view=net-5.0
//hat - handle operator					https://docs.microsoft.com/en-us/cpp/extensions/handle-to-object-operator-hat-cpp-component-extensions?view=msvc-160
//parsing system::string into array		https://stackoverflow.com/questions/10546250/how-to-define-an-array-of-strings-in-c-cli
//managed arrays						https://docs.microsoft.com/en-us/cpp/dotnet/how-to-use-arrays-in-cpp-cli?view=msvc-160



#pragma once
#include <string>

namespace DBProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;				//File access
	//using namespace System.Reflection		//assembly reflection ?

	enum class filetype { text, csv, sql, other};
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ SaveButton;
	private: System::Windows::Forms::Button^ LoadButton;
	private: System::Windows::Forms::DataGridView^ DataView;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;


	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Label^ Content_label;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		BindingSource^ bindingSource1 = gcnew BindingSource();
		filetype datatype=filetype::other;
		System::String^ content;		//how to initialize?
		int rows = 0;
		int cols = 0;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->LoadButton = (gcnew System::Windows::Forms::Button());
			this->DataView = (gcnew System::Windows::Forms::DataGridView());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->Content_label = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataView))->BeginInit();
			this->SuspendLayout();
			// 
			// SaveButton
			// 
			resources->ApplyResources(this->SaveButton, L"SaveButton");
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &MainForm::SaveButton_Click);
			// 
			// LoadButton
			// 
			resources->ApplyResources(this->LoadButton, L"LoadButton");
			this->LoadButton->Name = L"LoadButton";
			this->LoadButton->UseVisualStyleBackColor = true;
			this->LoadButton->Click += gcnew System::EventHandler(this, &MainForm::LoadButton_Click);
			// 
			// DataView
			// 
			this->DataView->AllowUserToOrderColumns = true;
			this->DataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			resources->ApplyResources(this->DataView, L"DataView");
			this->DataView->Name = L"DataView";
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"database";
			resources->ApplyResources(this->openFileDialog, L"openFileDialog");
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::openFileDialog_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::saveFileDialog_FileOk);
			// 
			// Content_label
			// 
			resources->ApplyResources(this->Content_label, L"Content_label");
			this->Content_label->Name = L"Content_label";
			// 
			// MainForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->Content_label);
			this->Controls->Add(this->DataView);
			this->Controls->Add(this->LoadButton);
			this->Controls->Add(this->SaveButton);
			this->Name = L"MainForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	//returns handle to string object
	private: String^ getCureentContent() {
		//reverse content parsing
		std::string default = "/*return file content*/";
		String^ content = gcnew String(default.c_str());
		return content;
	};
	
	private: int parsecsv(StreamReader^ inputfile) {
		while (!inputfile->EndOfStream) {
			String^ line = gcnew String(inputfile->ReadLine()) + "\n";
			//sanitize
			line = line->Replace((wchar_t)'"', NULL)
				->Replace((wchar_t)'\t', NULL)
				->Replace((wchar_t)' ', NULL);

			array<String^>^ values = line->Split((wchar_t)',');


			if (!this->rows == 0) {
				this->DataView->Rows->Add(values);
				/*for each (String ^ value in values) {
					this->DataView->Rows->Add(value, value);
				};*/
			}
			else {
				for each (String ^ value in values) {
					this->DataView->Columns->Add(value, value);
					this->cols++;
				};
			};
			this->content += line;
			this->rows++;
			//this->parsedcontent->Add(line->Split((__wchar_t)"\\n"));
		};
		return EXIT_SUCCESS;
	};
	private: int displaycsv(StreamReader^ inputfile) {
		return parsecsv(inputfile);
	};
	private: int displaytext(StreamReader^ inputfile) {
		this->content = gcnew String(inputfile->ReadToEnd());

		return EXIT_SUCCESS;
	};
	private: int displayother(StreamReader^ inputfile) {
		//Popup message about unsupported type
		return EXIT_SUCCESS;
	};
	private: int displaysql(String^ dbname) {
		/*<3*/
		connecttodb(dbname);
		return EXIT_SUCCESS;
	};
	private: int connecttodb(String^ dbname) {
		/*<3*/
		return EXIT_SUCCESS;
	};

	private: System::Void LoadButton_Click(System::Object^ sender, System::EventArgs^ e){
		this->openFileDialog->ShowDialog();
	};
	private: System::Void openFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		StreamReader^ file = gcnew StreamReader(this->openFileDialog->FileName);

		if (this->openFileDialog->FileName->Contains(".csv")) {
			this->datatype = filetype::csv;
			parsecsv(file);
		}
		else if (this->openFileDialog->FileName->Contains(".txt")) { 
			this->datatype = filetype::text;
			displaytext(file);
		}
		else if (this->openFileDialog->FileName->Contains(".sql")) { 
			this->datatype = filetype::sql; 
			connecttodb(this->openFileDialog->FileName);
		}
		else { 
			this->datatype = filetype::other;
			displayother(file);
		};
		file->Close();
	};
	private: System::Void SaveButton_Click(System::Object^ sender, System::EventArgs^ e) {
		switch (this->datatype)
		{
		case (filetype::csv): {/*parse content of DataView into content*/; } break;
		case (filetype::sql): {/*parse content of DataView into content*/; } break;
		case (filetype::text): {/*parse content of text editor into content*/; } break;
		case (filetype::other): {/*just dump content*/; } break;
		default: {/*panic - unsupported type option*/}
			   break;
		};
		this->saveFileDialog1->ShowDialog();
		/*dump content into specified file*/
	};
	private: System::Void saveFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		StreamWriter^ outputfile = gcnew StreamWriter(this->saveFileDialog1->FileName);
		
		//set type of file
		
		outputfile->Write(getCureentContent());
		outputfile->Close();
		
	};

	};
};