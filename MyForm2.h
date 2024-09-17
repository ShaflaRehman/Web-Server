#pragma once
#include "Global_variables.h"
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <string>



namespace WebEngine {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm2 : public System::Windows::Forms::Form {
    public:
        MyForm2(void) {
            InitializeComponent();
        }

    protected:
        ~MyForm2() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::TextBox^ textBox1;
        System::Collections::Generic::List<Button^>^ buttons; // Collection to store buttons
    private: System::Windows::Forms::Button^ button1;


           String^ buttonText; // Store the text of the clicked button

#pragma region Windows Form Designer generated code
           void InitializeComponent(void) {
               System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm2::typeid));
               this->textBox1 = (gcnew System::Windows::Forms::TextBox());
               this->button1 = (gcnew System::Windows::Forms::Button());
               this->SuspendLayout();
               // 
               // textBox1
               // 
               this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 16));
               this->textBox1->Location = System::Drawing::Point(1517, 0);
               this->textBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
               this->textBox1->Multiline = true;
               this->textBox1->Name = L"textBox1";
               this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
               this->textBox1->Size = System::Drawing::Size(2129, 1778);
               this->textBox1->TabIndex = 0;
               this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm2::textBox1_TextChanged);
               // 
               // button1
               // 
               this->button1->Location = System::Drawing::Point(22, 31);
               this->button1->Name = L"button1";
               this->button1->Size = System::Drawing::Size(168, 73);
               this->button1->TabIndex = 6;
               this->button1->Text = L"backward";
               this->button1->UseVisualStyleBackColor = true;
               this->button1->Click += gcnew System::EventHandler(this, &MyForm2::button1_Click);
               this->button1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm2::button1_MouseClick);
               // 
               // MyForm2
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font; //for scrolling
               this->ClientSize = System::Drawing::Size(3204, 1748);
               this->Controls->Add(this->button1);
               this->Controls->Add(this->textBox1);
               this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
               this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
               this->Name = L"MyForm2";
               this->Text = L"MyForm2";
               this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
               this->Load += gcnew System::EventHandler(this, &MyForm2::MyForm2_Load);
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

    public:
        
        void SetTextAndTitle(String^ text, String^ title) {
            // Display the text content
            textBox1->Text = text;
            // Set the form title to the clicked button text
            this->Text = title;
           
            buttonText = title;
        }

        // Method to dynamically create buttons
        void CreateButtons() {
            buttons = gcnew System::Collections::Generic::List<Button^>();
            int buttonCount = 0;

            // Debugging output
            //MessageBox::Show("files_displayed size: " + files_displayed.size().ToString() + "\ncount_global: " + count_global.ToString());

            for (int i = 0; i < files_displayed.size(); ++i) {
                if (i == count_global) {
                    continue;
                }

                Button^ newButton = gcnew Button();
                newButton->Text = gcnew System::String(files_displayed[i].c_str());
                newButton->Size = System::Drawing::Size(500, 50); // Increase button size to ensure full text is displayed
                newButton->Location = System::Drawing::Point(50, 50 + (buttonCount * 60)); // Adjust position below the previous button
                newButton->Font = gcnew System::Drawing::Font("Arial", 16); // Increase font size

                // Style the button to look like a hyperlink
                newButton->FlatStyle = FlatStyle::Flat;
                newButton->FlatAppearance->BorderSize = 0;
                newButton->ForeColor = Color::Blue;
                newButton->Font = gcnew System::Drawing::Font(newButton->Font, FontStyle::Underline);
                newButton->Cursor = Cursors::Hand;

                newButton->Click += gcnew System::EventHandler(this, &MyForm2::dynamicButton_Click);

                this->Controls->Add(newButton);
                buttons->Add(newButton);

                buttonCount++;
            }
        }

    private:
        // Event handler for dynamically created button click
        System::Void dynamicButton_Click(System::Object^ sender, System::EventArgs^ e) {





            Button^ clickedButton = dynamic_cast<Button^>(sender);
            if (clickedButton != nullptr) {
                String^ text = clickedButton->Text;
                std::string text1 = msclr::interop::marshal_as<std::string>(text);
                backStack.push(text1);
                // Convert System::String^ to std::string
                std::string filename = msclr::interop::marshal_as<std::string>(clickedButton->Text);

                // Read the content of the text file
                std::ifstream file(filename);
                std::string content;
                if (file.is_open()) {
                    std::string line;
                    while (std::getline(file, line)) {
                        content += line + "\n";
                    }
                    file.close();
                }
                else {
                    MessageBox::Show("Failed to open file: " + clickedButton->Text);
                    return;
                }

                // Set the text in textBox1 and update the form title
                SetTextAndTitle(gcnew System::String(content.c_str()), clickedButton->Text);
            }
        }

    private: System::Void MyForm2_Load(System::Object^ sender, System::EventArgs^ e) {
        CreateButtons();
    }

    private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
    {

    }
    private: System::Void button1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
        if (!(backStack.empty()))
        {
            string text = backStack.top();
            System::String^ text1 = gcnew System::String(text.c_str());
            backStack.pop();
            std::string filename = msclr::interop::marshal_as<std::string>(text1);

            // Read the content of the text file
            std::ifstream file(filename);
            std::string content;
            if (file.is_open()) {
                std::string line;
                while (std::getline(file, line)) {
                    content += line + "\n";
                }
                file.close();
            }
            else {
                MessageBox::Show("Failed to open file: " + text1);
                return;
            }

            // Set the text in textBox1 and update the form title
            SetTextAndTitle(gcnew System::String(content.c_str()), text1);




        }
    }
    };
}