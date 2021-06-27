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
//system convert class					https://stackoverflow.com/questions/2674670/how-to-sort-string-as-number-in-datagridview-in-winforms
//general visual C++ information		http://functionx.com/vccli/index.htm


//Possible improvements:
// -multiple files: add tabs for all open files that user might switch to. 
//	Needs: change content into collection of objects, have to actively switch with tab and know which content is active
// -csv parsing according to specification, now implemented only basic
// -*SCOPE CREEP WARNING* add JSON compatibility maybe with https://github.com/nlohmann/json
//

#pragma once
#include <string>
#include <vector>

namespace DBProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;													//File access

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
	private: System::Windows::Forms::CheckBox^ NumbersCheckbox;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Panel^ panel1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		BindingSource^ bindingSource1 = gcnew BindingSource();
		filetype datatype=filetype::other;
		System::String^ content;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->LoadButton = (gcnew System::Windows::Forms::Button());
			this->DataView = (gcnew System::Windows::Forms::DataGridView());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->NumbersCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// SaveButton
			// 
			this->SaveButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->SaveButton->Location = System::Drawing::Point(146, 3);
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
			this->LoadButton->Location = System::Drawing::Point(146, 37);
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
			this->DataView->Size = System::Drawing::Size(520, 361);
			this->DataView->TabIndex = 2;
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"database";
			this->openFileDialog->Filter = L"Comma separated Values|*.csv|Pliki tekstowe|*.txt|Baza danych|*.db";
			this->openFileDialog->Title = L"Chose file to load";
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::openFileDialog_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"Comma separated Values|*.csv|Pliki tekstowe|*.txt|Baza danych|*.db";
			this->saveFileDialog1->Title = L"Save as";
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::saveFileDialog_FileOk);
			// 
			// NumbersCheckbox
			// 
			this->NumbersCheckbox->AccessibleName = L"NumbersCheckbox";
			this->NumbersCheckbox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->NumbersCheckbox->AutoSize = true;
			this->NumbersCheckbox->Location = System::Drawing::Point(146, 70);
			this->NumbersCheckbox->Name = L"NumbersCheckbox";
			this->NumbersCheckbox->Size = System::Drawing::Size(68, 17);
			this->NumbersCheckbox->TabIndex = 3;
			this->NumbersCheckbox->Text = L"Numbers";
			this->NumbersCheckbox->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(146, 93);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(121, 20);
			this->textBox1->TabIndex = 4;
			// 
			// chart1
			// 
			this->chart1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(533, 151);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(314, 198);
			this->chart1->TabIndex = 5;
			this->chart1->Text = L"chart1";
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->panel1->Controls->Add(this->SaveButton);
			this->panel1->Controls->Add(this->LoadButton);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Controls->Add(this->NumbersCheckbox);
			this->panel1->Location = System::Drawing::Point(533, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(314, 133);
			this->panel1->TabIndex = 6;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(859, 361);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->DataView);
			this->Name = L"MainForm";
			this->Text = L"Database Editor";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	//returns handle to string object
	private: int calculateDataGridValues() {
		std::vector<std::vector<Double>> table;
		int rowoffset = 1;
		int celloffset = 0;
		//array<Double^>^ values = gcnew array<Double^>[this->DataView->Rows->Count - 1]; [this->DataView->Rows[row]->Cells->Count]
		for (auto row = rowoffset; row < this->DataView->Rows->Count - 1; row++) {	//without empty row
			std::vector<Double> row_values;
			for (auto cell = celloffset; cell < this->DataView->Rows[row]->Cells->Count; cell++) {
				Double cellcontent = 0;
				try
				{
					auto text = this->DataView->Rows[row]->Cells[cell]->Value->ToString();
					cellcontent = System::Convert::ToDouble(text);
				}
				catch (const std::exception&) {
					cellcontent = NULL;
					//„System.FormatException” w mscorlib.dll
				}
				finally{
					row_values.push_back(cellcontent);
				};
				row_values.push_back(System::Convert::ToDouble(this->DataView->Rows[row]->Cells[cell]->Value));
				//System::Convert::ToDouble(this->DataView->Rows[row]->Cells[cell]->Value);
			};
			table.push_back(row_values);
		};
		true;
		return EXIT_SUCCESS;
	};

	private: int craftContentfromDataView() {
		System::String^ content2 = "";
		for (auto row = 0; row < this->DataView->Rows->Count-1; row++) {	//without empty row
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
		case (filetype::csv):	{craftContentfromDataView();} break;
		case (filetype::sql): {/*parse content of DataView into content*/; } break;
		case (filetype::text):	{craftContentfromDataView();} break;
		case (filetype::other): {/*just dump content*/; } break;
		default: {/*panic - unsupported type option*/}
			   break;
		};
		std::string default = "/*return file content*/";
		String^ content = gcnew String(default.c_str());
		return EXIT_SUCCESS;
	};
	
	private: array<String^>^ parsecsvline(String^ line) {
		//TODO: further improvement - Parse according to https://datatracker.ietf.org/doc/html/rfc4180
		//	- check if has headers [how are they implemented?]
		//	- get line and check if amount of " (quote signs) is even
		//	  take into accunt "escape character, eg: "the "" is quote sign"
		//		- not even - get another line into buffer and check again
		//		- even - parse
		//	- treat everythin inside "" as one value (blank characters are parts of the field too)
		//	- divide fields by commas (be carefull not to include commas inside "")
		//	- [should I take into account different delimiters ?]		
		
		array<String^>^ parsed; 
		//if (!line->Contains((System::String^)"\"")) {
		//	parsed = line->Split((wchar_t)',');
		//}
		//else {
		//	//count occurences of " and check if even
		//}
		//
		//for (auto character = 0; character < line->Length; character++) {

		//};
		parsed = line->Split((wchar_t)',');
		return parsed;
	};
	//works only for rows which are fully filled with numbers
	private: array<double^>^ create_double_array(array<String^>^ strarray) {
		array<double^>^ dblarray = gcnew array<double^>(strarray->Length);
		for (int element = 0; element < strarray->Length; element++) {
			Double doubleval = 0;
			Double::TryParse(strarray[element], doubleval);
			dblarray[element] = doubleval;
		};
		return dblarray;
	};
	

	//does not work - need to figure out a way to add columns of certain type
	//private: int displaycsv_v2_temp(StreamReader^ inputfile) {
	//	while (!inputfile->EndOfStream) {
	//		String^ line = gcnew String(inputfile->ReadLine()) + "\n";
	//		this->content += line;
	//		array<String^>^ values = parsecsvline(line);
	//		values->Length;
	//		//cvan try to add empty row and iterate through cells separately
	//		if (!this->DataView->Rows->Count == 0) {
	//			if (!this->NumbersCheckbox->Checked) {
	//				this->DataView->Rows->Add(values);
	//			}
	//			else {
	//				//add each cell as double
	//				this->DataView->Rows->Add(create_double_array(values));
	//			};
	//		}
	//		else {
	//			DataGridViewColumnCollection columns();

	//			for each (String ^ value in values) {
	//				DataColumn ^ column = gcnew DataColumn(value, System::Double::typeid );
	//				columns::Add(column);
	//				
	//			};
	//			this->DataView->Columns->Add(columns);
	//		};
	//	};
	//	//calculateDataGridValues();
	//	return EXIT_SUCCESS;
	//};

	private: int displaycsv(StreamReader^ inputfile) {
		while (!inputfile->EndOfStream) {
			String^ line = gcnew String(inputfile->ReadLine()) + "\n";
			this->content += line;
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
			displaycsv_v2_temp(file);
			//displaycsv(file);
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
		UpdateContent();

		StreamWriter^ outputfile = gcnew StreamWriter(this->saveFileDialog1->FileName);
		outputfile->Write(this->content);
		outputfile->Close();
	};
};
};