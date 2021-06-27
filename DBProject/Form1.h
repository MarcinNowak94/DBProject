//Resources:
//Windows Forms Projects with C++ in Visual Studio 2019 https://www.rkaiser.de/wp-content/uploads/2019/04/cpp-2019-WinForms-Anleitung-EN.pdf
//string to system::string				https://docs.microsoft.com/en-us/cpp/dotnet/how-to-convert-standard-string-to-system-string?view=msvc-160
//embed files in winforms				https://www.youtube.com/watch?v=lxbUcU4Q5Fk
//Create a text file and write in it	https://www.youtube.com/watch?v=2NIUS-0ZlcQ
//datagridrow							https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.datagridview?view=net-5.0
//hat - handle operator					https://docs.microsoft.com/en-us/cpp/extensions/handle-to-object-operator-hat-cpp-component-extensions?view=msvc-160
//parsing system::string into array		https://stackoverflow.com/questions/10546250/how-to-define-an-array-of-strings-in-c-cli
//managed arrays						https://docs.microsoft.com/en-us/cpp/dotnet/how-to-use-arrays-in-cpp-cli?view=msvc-160
//csv specification						https://datatracker.ietf.org/doc/html/rfc4180


//Possible improvements:
// -multiple files: add tabs for all open files that user might switch to. 
//	Needs: change content into collection of objects, have to actively switch with tab and know which content is active
// -csv parsing according to specification, now implemented only basic
// -*SCOPE CREEP WARNING* add JSON compatibility
//

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


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		BindingSource^ bindingSource1 = gcnew BindingSource();
		filetype datatype=filetype::other;
		System::String^ content;								//how to initialize?
		int rows = 0;
		int cols = 0;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->LoadButton = (gcnew System::Windows::Forms::Button());
			this->DataView = (gcnew System::Windows::Forms::DataGridView());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataView))->BeginInit();
			this->SuspendLayout();
			// 
			// SaveButton
			// 
			this->SaveButton->Location = System::Drawing::Point(602, 23);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(121, 28);
			this->SaveButton->TabIndex = 0;
			this->SaveButton->Text = L"Save";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &MainForm::SaveButton_Click);
			// 
			// LoadButton
			// 
			this->LoadButton->Location = System::Drawing::Point(602, 57);
			this->LoadButton->Name = L"LoadButton";
			this->LoadButton->Size = System::Drawing::Size(119, 27);
			this->LoadButton->TabIndex = 1;
			this->LoadButton->Text = L"Load";
			this->LoadButton->UseVisualStyleBackColor = true;
			this->LoadButton->Click += gcnew System::EventHandler(this, &MainForm::LoadButton_Click);
			// 
			// DataView
			// 
			this->DataView->AllowUserToOrderColumns = true;
			this->DataView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::ColumnHeader;
			this->DataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->DataView->Dock = System::Windows::Forms::DockStyle::Left;
			this->DataView->Location = System::Drawing::Point(0, 0);
			this->DataView->Margin = System::Windows::Forms::Padding(10);
			this->DataView->Name = L"DataView";
			this->DataView->Size = System::Drawing::Size(589, 507);
			this->DataView->TabIndex = 2;
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"database";
			this->openFileDialog->Filter = L"Comma separated Values|*.csv|Pliki tekstowe|*.txt|Baza danych|*.db";
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::openFileDialog_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::saveFileDialog_FileOk);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(735, 507);
			this->Controls->Add(this->DataView);
			this->Controls->Add(this->LoadButton);
			this->Controls->Add(this->SaveButton);
			this->Name = L"MainForm";
			this->Text = L"Database Editor";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataView))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	//returns handle to string object
	private: int getCureentContent() {
		//reverse content parsing
		switch (this->datatype)
		{
		case (filetype::csv): {
			auto content2 = content;
			this->content = "";
			/*parse content of DataView into content*/; 
			for each (DataGridViewRow^ row in this->DataView->Rows) {
				for each (DataGridViewElement^ cell in this->DataView->Rows) {
					content += cell + ",";
				}
				content += "\n";
			};
			content += "\n";
			if (String::Compare(content, content2)) {
				return EXIT_SUCCESS;
			};
		} break;
		case (filetype::sql): {/*parse content of DataView into content*/; } break;
		case (filetype::text): {/*parse content of text editor into content*/; } break;
		case (filetype::other): {/*just dump content*/; } break;
		default: {/*panic - unsupported type option*/}
			   break;
		};


		std::string default = "/*return file content*/";
		String^ content = gcnew String(default.c_str());
		return EXIT_SUCCESS;
	};
	
	private: String^ sanitizeline(String^ line) {
		return line->Replace((wchar_t)'"', ' ')
			->Replace((wchar_t)'\t', ' ')
			->Replace((wchar_t)' ', NULL);
	};
	private: int parsecsv(StreamReader^ inputfile) {
		//TODO: further improvement - Parse according to https://datatracker.ietf.org/doc/html/rfc4180
		//	- check if has headers [how are they implemented?]
		//	- get line and check if amount of " (quote signs) is even
		//	  take into accunt "escape character, eg: "the "" is quote sign"
		//		- not even - get another line into buffer and check again
		//		- even - parse
		//	- treat everythin inside "" as one value (blank characters are parts of the field too)
		//	- divide fields by commas (be carefull not to include commas inside "")
		//	- [should I take into account different delimiters ?]
				
		while (!inputfile->EndOfStream) {
			String^ line = gcnew String(inputfile->ReadLine()) + "\n";
			array<String^>^ values = line->Split((wchar_t)',');
			//line = sanitizeline(line);

			if (!this->rows == 0) {
				this->DataView->Rows->Add(values);				//TODO: Figure out why added whiteline
			}
			else {
				for each (String ^ value in values) {
					this->DataView->Columns->Add(value, value);
					this->cols++;									
				};
			};
			this->content += line;
			this->rows++;
		};
		return EXIT_SUCCESS;
	};
	private: int displaycsv(StreamReader^ inputfile) {
		return parsecsv(inputfile);
	};
	private: int displaytext(StreamReader^ inputfile) {
		this->content = gcnew String(inputfile->ReadToEnd());
		this->DataView->Columns->Add("FileName", this->openFileDialog->FileName);
		this->DataView->Rows->Add(this->content);
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
		this->saveFileDialog1->ShowDialog();
		/*dump content into specified file*/

	};
	private: System::Void saveFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		StreamWriter^ outputfile = gcnew StreamWriter(this->saveFileDialog1->FileName);
		
		//set type of file
		
		//outputfile->Write(getCureentContent());
		outputfile->Write(this->content);
		outputfile->Close();
		
	};
	};
};