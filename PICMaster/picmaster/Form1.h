#pragma once


namespace CppCLRWinFormsProject {
	using namespace System::IO;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
		  

	private:
			void PopulateReg1();
			void UpdateReg1();	
			void PopulateRARegister();
			void PinButton_add(int num, int row);
			void PinButton_Click(System::Object^ sender, System::EventArgs^ e);
			void UpdatePinButtons();
			int FindLineNumber(String^ text, int cursorIndex);
			List<int>^ breakpoints = gcnew List<int>();
			List<int>^ breakpointLines = gcnew List<int>();
			
	public:
		Form1(void)
		{
			InitializeComponent();
			// Set the interval to 250 milliseconds
			PopulateReg1();
		}
		
	
	
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ ProgramMemory;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ Register1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ProgramMemory = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->Register1 = (gcnew System::Windows::Forms::DataGridView());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Register1))->BeginInit();
			this->SuspendLayout();
			// 
			// ProgramMemory
			// 
			this->ProgramMemory->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->ProgramMemory->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->ProgramMemory->Location = System::Drawing::Point(4, 157);
			this->ProgramMemory->Name = L"ProgramMemory";
			this->ProgramMemory->Size = System::Drawing::Size(527, 379);
			this->ProgramMemory->TabIndex = 0;
			this->ProgramMemory->Text = L"";
			this->ProgramMemory->Click += gcnew System::EventHandler(this, &Form1::ProgramMemory_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Enabled = false;
			this->label1->Location = System::Drawing::Point(12, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(129, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Program Memory";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(4, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(112, 30);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Read";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// Register1
			// 
			this->Register1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Register1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->Register1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->Register1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->Register1->Location = System::Drawing::Point(1135, 12);
			this->Register1->Name = L"Register1";
			this->Register1->RowHeadersWidth = 62;
			this->Register1->RowTemplate->Height = 28;
			this->Register1->Size = System::Drawing::Size(349, 458);
			this->Register1->TabIndex = 3;
			this->Register1->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::Register1_CellEndEdit);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(1196, 494);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(91, 42);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Step";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(1196, 542);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(91, 42);
			this->button3->TabIndex = 5;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(1196, 590);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(91, 42);
			this->button4->TabIndex = 6;
			this->button4->Text = L"button4";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				30)));
			this->tableLayoutPanel1->Location = System::Drawing::Point(589, 47);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(2);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->Size = System::Drawing::Size(30, 0);
			this->tableLayoutPanel1->TabIndex = 7;
			// 
			// Form1
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1496, 738);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->Register1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ProgramMemory);
			this->Name = L"Form1";
			this->Text = L"picmaster";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Register1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}



#pragma endregion
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {

		// Call the function with the desired values
		PopulateRARegister();
	}

	private: System::Void Register1_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ strfilename = openFileDialog1->InitialDirectory + openFileDialog1->FileName;
			String^ data = File::ReadAllText(strfilename);
			ProgramMemory->Text = data;
		}
	}

	private: System::Void tableLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		// Code for handling the Paint event of tableLayoutPanel1
	}

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ProgramMemory_Click(System::Object^ sender, System::EventArgs^ e);

};
}
