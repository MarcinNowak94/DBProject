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
// -*SCOPE CREEP WARNING* add full JSON compatibility
// -move implementation to .cpp file if necessary (prefer to leave as drop-in header file)
// -allow user to add columns

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

	enum class filetype { text, csv, sql, other };
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
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
		filetype datatype = filetype::other;
		System::String^ content;								//how to initialize?

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
			this->SaveButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
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
			this->LoadButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->LoadButton->Location = System::Drawing::Point(602, 57);
			this->LoadButton->Name = L"LoadButton";
			this->LoadButton->Size = System::Drawing::Size(121, 27);
			this->LoadButton->TabIndex = 1;
			this->LoadButton->Text = L"Load";
			this->LoadButton->UseVisualStyleBackColor = true;
			this->LoadButton->Click += gcnew System::EventHandler(this, &MainForm::LoadButton_Click);
			// 
			// DataView
			// 
			this->DataView->AllowUserToOrderColumns = true;
			this->DataView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DataView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::ColumnHeader;
			this->DataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->DataView->Location = System::Drawing::Point(0, 0);
			this->DataView->Margin = System::Windows::Forms::Padding(10);
			this->DataView->Name = L"DataView";
			this->DataView->Size = System::Drawing::Size(589, 507);
			this->DataView->TabIndex = 2;
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"database";
			this->openFileDialog->Filter = L"Comma separated Values|*.csv|Pliki tekstowe|*.txt";
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::openFileDialog_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"Comma separated Values|*.csv|Pliki tekstowe|*.txt";
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
	private: int craftContentfromDataView() {
		System::String^ content2 = "";
		for (auto row = 0; row < this->DataView->Rows->Count - 1; row++) {	//without empty row
			for (auto cell = 0; cell < this->DataView->Rows[row]->Cells->Count; cell++) {
				content2 += this->DataView->Rows[row]->Cells[cell]->Value->ToString() + (wchar_t)',';
			};
			content2 += "\n";
		};
		this->content = content2;
		return (String::Compare(content, content2));						//return info if content changed
	};
	private: int UpdateContent() {
		//reverse content parsing
		switch (this->datatype)
		{
		case (filetype::csv): {craftContentfromDataView(); } break;
		case (filetype::sql): {/*parse content of DataView into content*/; } break;
		case (filetype::text): {craftContentfromDataView(); } break;
		case (filetype::other): {/*just dump content*/; } break;
		default: {/*panic - unsupported type option*/}
			   break;
		};
		std::string default = "/*return file content*/";
		String^ content = gcnew String(default.c_str());
		return EXIT_SUCCESS;
	};

	private: array<String^>^ parsecsvline(String^ line) {
		//TODO: further improvement - Parse according to CSV specification 
		//https://datatracker.ietf.org/doc/html/rfc4180
		//	- check if has headers [how are they implemented?]
		//	- get line and check if amount of " (quote signs) is even
		//	  take into accunt "escape character, eg: "the "" is quote sign"
		//		- not even - get another line into buffer and check again
		//		- even - parse
		//	- treat everythin inside "" as one value (blank characters are parts of the field too)
		//	- divide fields by commas (be carefull not to include commas inside "")
		//	- [should I take into account different delimiters ?]
		array<String^>^ parsed;
		parsed = line->Split((wchar_t)',');
		return parsed;
	};

	private: int displaycsv(StreamReader^ inputfile) {
		while (!inputfile->EndOfStream) {
			String^ line = gcnew String(inputfile->ReadLine());
			this->content += line + "\n";
			array<String^>^ values = parsecsvline(line);

			if (!this->DataView->Rows->Count == 0) {
				this->DataView->Rows->Add(values);							//TODO: Figure out why added whiteline
			}
			else {
				for each (String ^ value in values) {
					this->DataView->Columns->Add(value, value);
				};
			};
		};
		return EXIT_SUCCESS;
	};
	private: int displaytext(StreamReader^ inputfile) {
		this->content = gcnew String(inputfile->ReadToEnd());
		this->DataView->Columns->Add("FileName", this->openFileDialog->FileName);
		this->DataView->Rows->Add(this->content);
		return EXIT_SUCCESS;
	};
	private: int displayother(StreamReader^ inputfile) {
		//Cozy place for Popup message about unsupported type
		return EXIT_SUCCESS;
	};

	private: System::Void LoadButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->openFileDialog->ShowDialog();
	};
	private: System::Void openFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		//Clear current content and displayed data
		this->content = "";
		this->DataView->CancelEdit();
		this->DataView->Columns->Clear();
		
		StreamReader^ file = gcnew StreamReader(this->openFileDialog->FileName);

		if (this->openFileDialog->FileName->Contains(".csv")) {
			this->datatype = filetype::csv;
			displaycsv(file);
		}
		else if (this->openFileDialog->FileName->Contains(".txt")) {
			this->datatype = filetype::text;
			displaytext(file);
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
		UpdateContent();

		StreamWriter^ outputfile = gcnew StreamWriter(this->saveFileDialog1->FileName);
		outputfile->Write(this->content);
		outputfile->Close();
	};
	};
};