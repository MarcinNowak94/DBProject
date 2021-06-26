//Resources:
//Windows Forms Projects with C++ in Visual Studio 2019 https://www.rkaiser.de/wp-content/uploads/2019/04/cpp-2019-WinForms-Anleitung-EN.pdf
//string to system::string				https://docs.microsoft.com/en-us/cpp/dotnet/how-to-convert-standard-string-to-system-string?view=msvc-160
//embed files in winforms				https://www.youtube.com/watch?v=lxbUcU4Q5Fk
//Create a text file and write in it	https://www.youtube.com/watch?v=2NIUS-0ZlcQ
//datagridrow							https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.datagridview?view=net-5.0
//hat - handle operator					https://docs.microsoft.com/en-us/cpp/extensions/handle-to-object-operator-hat-cpp-component-extensions?view=msvc-160



#pragma once
#include "iostream"
#include "fstream"

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
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
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
		String^ content;		//how to initialize?

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
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->Content_label = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataView))->BeginInit();
			this->SuspendLayout();
			// 
			// SaveButton
			// 
			this->SaveButton->Location = System::Drawing::Point(281, 46);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(121, 28);
			this->SaveButton->TabIndex = 0;
			this->SaveButton->Text = L"Save";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &MainForm::SaveButton_Click);
			// 
			// LoadButton
			// 
			this->LoadButton->Location = System::Drawing::Point(282, 86);
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
			this->DataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->DataView->Location = System::Drawing::Point(26, 41);
			this->DataView->Name = L"DataView";
			this->DataView->Size = System::Drawing::Size(238, 325);
			this->DataView->TabIndex = 2;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"database";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::openFileDialog1_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::saveFileDialog1_FileOk);
			// 
			// Content_label
			// 
			this->Content_label->AutoSize = true;
			this->Content_label->Location = System::Drawing::Point(284, 142);
			this->Content_label->Name = L"Content_label";
			this->Content_label->Size = System::Drawing::Size(94, 13);
			this->Content_label->TabIndex = 3;
			this->Content_label->Text = L"Content goes here";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(431, 385);
			this->Controls->Add(this->Content_label);
			this->Controls->Add(this->DataView);
			this->Controls->Add(this->LoadButton);
			this->Controls->Add(this->SaveButton);
			this->Name = L"MainForm";
			this->Text = L"Database Editor";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	//returns handle to string object
	private: String^ getCureentContent() {
		std::string default = "/*return file content*/";
		String^ content = gcnew String(default.c_str());
		return content;
	};
	
	private: int parsecsv() {
		return EXIT_SUCCESS;
	};
	
	private: int displaycsv() {
		return EXIT_SUCCESS;
	};

	private: int displaytext() {
		return EXIT_SUCCESS;
	};

	private: int displayother() {
		return EXIT_SUCCESS;
	};

	private: int displaysql() {
		/*<3*/
		return EXIT_SUCCESS;
	};

	private: int parsecontent(){
		//System::String[] linefields[] = {};
		
		switch (this->datatype) {
			case filetype::csv:		{parsecsv(); displaycsv(); }; break;
			case filetype::text:	{displaytext(); }; break;
			case filetype::sql:		{displaysql(); }; break;
			case filetype::other:	{displayother(); }; break;
			default: {/*hereby gently enter panick mode because filetype is not set*/}; break;
		};
		for (auto character = 0; character < this->content->Length; character++){
			
		}
		
		/*parse content */
		//read from file	- 1st row as headers
		//
		this->datatype=filetype::other;

		return EXIT_SUCCESS;
	};


	private: System::Void LoadButton_Click(System::Object^ sender, System::EventArgs^ e){
		this->openFileDialog1->ShowDialog();
	};
	private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		StreamReader^ inputfile = gcnew StreamReader(this->openFileDialog1->FileName);
		//readcontent(inputfile);
		this->content= gcnew String(inputfile->ReadToEnd());
		//inputfile->Close;
		return;
	};
	private: System::Void SaveButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->saveFileDialog1->ShowDialog();
	};
	private: System::Void saveFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		StreamWriter^ outputfile = gcnew StreamWriter(this->saveFileDialog1->FileName);
		
		//set type of file
		if (this->saveFileDialog1->FileName->Contains(".csv"))		{ this->datatype = filetype::csv; }
		else if (this->saveFileDialog1->FileName->Contains(".txt")) { this->datatype = filetype::text; }
		else if (this->saveFileDialog1->FileName->Contains(".sql")) { this->datatype = filetype::sql; }
		else														{ this->datatype = filetype::other; };

		outputfile->Write(getCureentContent());
		outputfile->Close();
		
	};

	};
};