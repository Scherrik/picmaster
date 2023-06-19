#include "pch.h"
#include "Form1.h"
#include <iostream> 
#include <Windows.h>
#include <msclr\marshal_cppstd.h>
#include <ctime>
// Use the Windows Forms namespace
using namespace System::Windows::Forms;
// Define the entry point for the application
[System::STAThread]
int main()
{
    // Enable visual styles for Windows Forms application
    Application::EnableVisualStyles();
    // Set compatible text rendering default
    Application::SetCompatibleTextRenderingDefault(false);
    // Run the application with Form1 as the main form
    Application::Run(gcnew CppCLRWinFormsProject::Form1());
    // Return 0 on success
    return 0;
}

int datareg1[128][2];

void CppCLRWinFormsProject::Form1::PopulateReg1()
{
    Register1->ColumnCount = 8;  // Set the number of columns
    Register1->RowCount = 32;    // Set the number of rows

    Register1->Rows->Clear();

    // Add column headers
    for (int j = 0; j < 8; j++)
    {
        Register1->Columns[j]->HeaderText = "0x" + j.ToString("X2"); // Set the column header text
    }

    // Add row headers
    for (int i = 0; i < 32; i++)
    {
        String^ rowHeader = "0x" + (i * 8).ToString("X2"); // Calculate the row header value

        // Add label to the row header cell
        DataGridViewRow^ row = gcnew DataGridViewRow();
        row->CreateCells(Register1);
        row->HeaderCell->Value = rowHeader;

        for (int j = 0; j < 8; j++)
        {
            int index = (i / 4) + (j * 8);
            int value = datareg1[index][i % 4];
            row->Cells[j]->Value = value.ToString("X2"); // Convert to hex and set the cell value
        }

        Register1->Rows->Add(row);
    }
}

void CppCLRWinFormsProject::Form1::Register1_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
    int row = e->RowIndex;
    int col = e->ColumnIndex;
    String^ hexValue = safe_cast<String^>(Register1->Rows[row]->Cells[col]->Value);
    int value = int::Parse(hexValue, System::Globalization::NumberStyles::HexNumber);

    // Calculate the index of the datareg1 array based on row and column
    int index = (row < 16) ? (row * 8 + col): (row * 8 + col - 128);
    int index2 = (row < 16) ? 0 : 1;

    // Update the corresponding value in the datareg1 array
    datareg1[index][index2] = value;

    UpdateReg1();
}

void CppCLRWinFormsProject::Form1::UpdateReg1()
{
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int index = i*8+j;
            int index2 = (i < 16) ? 0 : 1;
            int value = datareg1[index][index2]; 

            Register1->Rows[i]->Cells[j]->Value = value.ToString("X2"); // Update the cell with the new value
        }
    }

    UpdatePinButtons();
}




void CppCLRWinFormsProject::Form1::PopulateRARegister()
{
    // Clear existing controls
    tableLayoutPanel1->Controls->Clear();
    tableLayoutPanel1->RowCount = 15;
    tableLayoutPanel1->ColumnCount = 9;

    // Add column and row styles to the tableLayoutPanel
    for (int i = 0; i < 9; i++)
    {
        tableLayoutPanel1->ColumnStyles->Add(gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 30));
        tableLayoutPanel1->RowStyles->Add(gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30));
    }

    // Create an array of label names
    array<String^>^ labelNames = { "RA", "RB", "RC", "RD", "RE" };

    // Add labels for register, tris, and pin for each register
    for (int i = 0; i < 5; i++)
    {
        Label^ registerLabel = gcnew Label();
        registerLabel->Text = labelNames[i];
        registerLabel->TextAlign = ContentAlignment::MiddleCenter;
        tableLayoutPanel1->Controls->Add(registerLabel, 0, i * 3);

        Label^ trisLabel = gcnew Label();
        trisLabel->Text = "Tris";
        trisLabel->TextAlign = ContentAlignment::MiddleCenter;
        tableLayoutPanel1->Controls->Add(trisLabel, 0, i * 3 + 1);

        Label^ pinLabel = gcnew Label();
        pinLabel->Text = "Pin";
        pinLabel->TextAlign = ContentAlignment::MiddleCenter;
        tableLayoutPanel1->Controls->Add(pinLabel, 0, i * 3 + 2);
    }

    // Add labels for each bit in the register
    for (int i = 1; i < 9; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            Label^ label = gcnew Label();
            label->Text = "" + (8 - i); // Display the bit number
            label->TextAlign = ContentAlignment::MiddleCenter;
            tableLayoutPanel1->Controls->Add(label, i, j * 3);

            Label^ label1 = gcnew Label();
            if (j == 0 || j == 1)
            {
                label1->Text = "in";
            }
            else
            {
                label1->Text = "out";
            }
            label1->TextAlign = ContentAlignment::MiddleCenter;
            tableLayoutPanel1->Controls->Add(label1, i, j * 3 + 1);
        }
    }

    PinButton_add(5, 2);
    PinButton_add(6, 5);
    PinButton_add(7, 8);
    PinButton_add(8, 11);
    PinButton_add(9, 14);
}




void CppCLRWinFormsProject::Form1::PinButton_add(int num, int row)
{
    int value1 = datareg1[num][0]; // Assuming 0-based indexing
    int value2 = datareg1[num][1];

    for (int i = 0; i < 8; i++)
    {
        int bit1 = (value1 >> (7 - i)) & 1; // Reverse the bit index
        int bit2 = (value2 >> (7 - i)) & 1; // Reverse the bit index

        Button^ button = gcnew Button();
        button->Text = ((bit2 << 1) | bit1).ToString();
        button->Click += gcnew System::EventHandler(this, &Form1::PinButton_Click);
        button->Tag = gcnew array<int> { num, i}; // Reverse the bit index
        tableLayoutPanel1->Controls->Add(button, 8-i, row);
    }
}




void CppCLRWinFormsProject::Form1::UpdatePinButtons()
{
    for (int i = 0; i < tableLayoutPanel1->Controls->Count; i++)
    {
        Button^ button = dynamic_cast<Button^>(tableLayoutPanel1->Controls[i]);
        if (button != nullptr)
        {
            array<int>^ tagArray = dynamic_cast<array<int>^>(button->Tag);
            if (tagArray != nullptr && tagArray->Length == 2)
            {
                int dataregIndex = tagArray[0];
                int bitIndex = tagArray[1];

                int value = datareg1[dataregIndex][bitIndex / 16];
                int bit = (value >> (bitIndex % 16)) & 1;
                button->Text = (bit == 1) ? "1" : "0";
            }
        }
    }
}

void CppCLRWinFormsProject::Form1::PinButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    Button^ pinButton = dynamic_cast<Button^>(sender);
    if (pinButton != nullptr)
    {
        array<int>^ tagArray = dynamic_cast<array<int>^>(pinButton->Tag);
        if (tagArray != nullptr && tagArray->Length == 2)
        {
            int dataregIndex = tagArray[0];
            int bitIndex = tagArray[1]; // Reverse the bit index

            // Update the corresponding bit in the datareg1 array
            int bitValue = (datareg1[dataregIndex][bitIndex / 32] >> (bitIndex % 32)) & 1;
            if (bitValue == 1)
            {
                pinButton->Text = "0";
                datareg1[dataregIndex][bitIndex / 32] &= ~(1 << (bitIndex % 32)); // Clear the bit
            }
            else if (bitValue == 0)
            {
                pinButton->Text = "1";
                datareg1[dataregIndex][bitIndex / 32] |= (1 << (bitIndex % 32)); // Set the bit
            }
        }
    }

    // Do something with the updated integer value
    // For example, you can display it in a TextBox
    UpdateReg1();
}



void CppCLRWinFormsProject::Form1::button2_Click(System::Object^ sender, System::EventArgs^ e) {
    static int currentRow = 0; // Variable to store the current row, initialized to 0
    static int previousRow = -1; // Variable to store the previously highlighted row, initialized to -1

    // Split the text in the ProgramMemory textbox into an array of lines
    array<String^>^ lines = ProgramMemory->Text->Split(Environment::NewLine->ToCharArray(), StringSplitOptions::RemoveEmptyEntries);

    // Check if the previous row is within the bounds of the lines array
    if (previousRow >= 0 && previousRow < lines->Length)
    {
        // Remove the highlighting from the previous row
        String^ previousLine = lines[previousRow];
        int startIndex = ProgramMemory->Text->IndexOf(previousLine); // Find the starting index of the previous line
        int endIndex = startIndex + previousLine->Length; // Calculate the ending index of the previous line

        ProgramMemory->Select(startIndex, previousLine->Length);
        ProgramMemory->SelectionBackColor = ProgramMemory->BackColor; // Set the background color to the default
        ProgramMemory->SelectionColor = ProgramMemory->ForeColor; // Set the text color to the default

        // Display the previous line in a MessageBox
        
        //ProgramCounter++?!
    }

    // Check if the current row is within the bounds of the lines array
    if (currentRow < lines->Length)
    {
        // Get the current line
        String^ currentLine = lines[currentRow];

        // Highlight the current line by applying formatting
        String^ programText = ProgramMemory->Text; // Get the entire program text from the textbox
        int startIndex = programText->IndexOf(currentLine); // Find the starting index of the current line
        int endIndex = startIndex + currentLine->Length; // Calculate the ending index of the current line

        // Apply formatting to the current line
        ProgramMemory->Select(startIndex, currentLine->Length);
        ProgramMemory->SelectionBackColor = Color::Yellow;
        ProgramMemory->SelectionColor = Color::Black;

        // Scroll to the currently highlighted line
        ProgramMemory->ScrollToCaret();

        // Move to the next row for the next button press
        currentRow++;
        previousRow = currentRow - 1; // Set the previously highlighted row to the previous row
    }
}

void CppCLRWinFormsProject::Form1::ProgramMemory_Click(System::Object^ sender, System::EventArgs^ e)
{
    int currentLine = ProgramMemory->GetLineFromCharIndex(ProgramMemory->SelectionStart) + 1;
    int lineIndex = ProgramMemory->GetLineFromCharIndex(ProgramMemory->SelectionStart);
    int lineStartIndex = ProgramMemory->GetFirstCharIndexFromLine(lineIndex);
    int nextLineStartIndex = ProgramMemory->GetFirstCharIndexFromLine(lineIndex + 1);
    int lineLength = nextLineStartIndex - lineStartIndex;

    String^ lineText = ProgramMemory->Text->Substring(lineStartIndex, 4);
    lineText = lineText->Trim(); // Remove leading/trailing whitespace

    if (lineText->Length == 0)
    {
        // No action to be performed if the first 4 characters are empty
        return;
    }

    bool breakpointExists = breakpoints->Contains(currentLine);

    if (breakpointExists)
    {
        // Remove the breakpoint from the clicked line
        ProgramMemory->SelectionStart = lineStartIndex;
        ProgramMemory->SelectionLength = lineLength;
        ProgramMemory->SelectionBackColor = ProgramMemory->BackColor;

        // Remove the breakpoint from the breakpoints list
        breakpoints->Remove(currentLine);

        // Remove the corresponding integer from the breakpointLines list
        int intValue;
        if (Int32::TryParse(lineText, System::Globalization::NumberStyles::HexNumber, nullptr, intValue))
        {
            if (breakpointLines->Contains(intValue))
            {
                breakpointLines->Remove(intValue);
            }
        }
    }
    else
    {
        // Set a new breakpoint at the clicked line
        ProgramMemory->SelectionStart = lineStartIndex;
        ProgramMemory->SelectionLength = lineLength;
        ProgramMemory->SelectionBackColor = Color::Red;

        // Add the breakpoint to the breakpoints list
        breakpoints->Add(currentLine);

        // Convert the first 4 characters to an int
        int intValue;
        if (Int32::TryParse(lineText, System::Globalization::NumberStyles::HexNumber, nullptr, intValue))
        {
            // Store the int value in a list
            if (!breakpointLines->Contains(intValue))
            {
                breakpointLines->Add(intValue);
            }
        }
    }
}


int CppCLRWinFormsProject::Form1::FindLineNumber(String^ text, int cursorIndex)
{
    // Split the text into an array of lines
    array<String^>^ lines = text->Split(Environment::NewLine->ToCharArray(), StringSplitOptions::None);

    int lineNumber = 1;
    int currentIndex = 0;

    // Find the line number based on the cursor index
    while (currentIndex <= cursorIndex && lineNumber <= lines->Length)
    {
        currentIndex += lines[lineNumber - 1]->Length + 2; // Add the length of the line and the line break characters

        if (currentIndex > cursorIndex)
        {
            break;
        }

        lineNumber++;
    }

    return lineNumber;
}







