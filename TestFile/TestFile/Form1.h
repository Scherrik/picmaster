#pragma once
#include "Header.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_plus1;
	protected:

	private: System::Windows::Forms::TextBox^ out_textBox;

	private: System::Windows::Forms::TextBox^ in_textBox;



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
			this->button_plus1 = (gcnew System::Windows::Forms::Button());
			this->out_textBox = (gcnew System::Windows::Forms::TextBox());
			this->in_textBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button_plus1
			// 
			this->button_plus1->Location = System::Drawing::Point(257, 99);
			this->button_plus1->Name = L"button_plus1";
			this->button_plus1->Size = System::Drawing::Size(119, 56);
			this->button_plus1->TabIndex = 0;
			this->button_plus1->Text = L"button1";
			this->button_plus1->UseVisualStyleBackColor = true;
			this->button_plus1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// out_textBox
			// 
			this->out_textBox->Location = System::Drawing::Point(11, 34);
			this->out_textBox->Multiline = true;
			this->out_textBox->Name = L"out_textBox";
			this->out_textBox->Size = System::Drawing::Size(212, 255);
			this->out_textBox->TabIndex = 1;
			this->out_textBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// in_textBox
			// 
			this->in_textBox->Location = System::Drawing::Point(263, 42);
			this->in_textBox->Name = L"in_textBox";
			this->in_textBox->Size = System::Drawing::Size(125, 26);
			this->in_textBox->TabIndex = 2;
			this->in_textBox->TextChanged += gcnew System::EventHandler(this, &Form1::in_textBox_TextChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(923, 324);
			this->Controls->Add(this->in_textBox);
			this->Controls->Add(this->out_textBox);
			this->Controls->Add(this->button_plus1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		int n = Convert::ToInt32(in_textBox->Text);
		int result = plus_1(n);
		out_textBox->AppendText(String::Format("plus_1({0})={1}\r\n", n, result));
	}

	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void in_textBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
