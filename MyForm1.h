#pragma once
#include "Global_variables.h"
#include "file_freq.h"
#include <msclr/marshal_cppstd.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "MyForm2.h"



namespace WebEngine {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm1 : public System::Windows::Forms::Form {
    public:
        MyForm1(void) {
            InitializeComponent();
        }

    protected:
        ~MyForm1() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;


           System::Collections::Generic::List<Button^>^ buttons; // Collection to store buttons

#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm1::typeid));
            this->SuspendLayout();
            // 
            // MyForm1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1355, 687);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->MinimizeBox = false;
            this->Name = L"MyForm1";
            this->Text = L"New Tab - Google Chrome";
            this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
            this->Load += gcnew System::EventHandler(this, &MyForm1::MyForm1_Load);
            this->ResumeLayout(false);

        }
#pragma endregion

    private:
        System::Void MyForm1_Load(System::Object^ sender, System::EventArgs^ e) {
            try {
                // Ensure links and buttons are initialized
                if (links.size() == 0) {
                    MessageBox::Show("No links available.");
                    return;
                }

                buttons = gcnew System::Collections::Generic::List<Button^>(); // Initialize the collection

                // Update form title to reflect search box text
                this->Text = gcnew System::String(to_search.c_str());

                // Iterate through links and create buttons dynamically
                for (int count = 0; count < links.size(); count++) {
                    if (links[count].freq > 0) {
                        Button^ newButton = gcnew Button();
                        newButton->Text = msclr::interop::marshal_as<System::String^>(links[count].filename);
                        newButton->Size = System::Drawing::Size(500, 50); // Increase button size to ensure full text is displayed
                        newButton->Location = System::Drawing::Point((this->Width - newButton->Width) / 2, 100 + (count * 60)); // Center button and adjust spacing
                        newButton->Font = gcnew System::Drawing::Font(newButton->Font->FontFamily, 16); // Increase font size

                        // Style the button to look like a hyperlink
                        newButton->FlatStyle = FlatStyle::Flat;
                        newButton->FlatAppearance->BorderSize = 0;
                        newButton->ForeColor = Color::Blue;
                        newButton->Font = gcnew System::Drawing::Font(newButton->Font, FontStyle::Underline);
                        newButton->Cursor = Cursors::Hand;

                        newButton->Click += gcnew System::EventHandler(this, &MyForm1::dynamicButton_Click); // Attach event handler
                        this->Controls->Add(newButton);
                        buttons->Add(newButton); // Add button to collection
                        files_displayed.push_back(msclr::interop::marshal_as<std::string>(newButton->Text));
                    }
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("An error occurred: " + ex->Message);
            }
        }

    private:
    private:
        System::Void dynamicButton_Click(System::Object^ sender, System::EventArgs^ e) {
            // Handle button click event here
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
                   // MessageBox::Show("Failed to open file: " + clickedButton->Text);
                    return;
                }

                for (int i = 0; i < files_displayed.size(); i++) {
                    if (clickedButton->Text == gcnew System::String(files_displayed[i].c_str())) {
                        count_global = i;
                        break;
                    }
                }

               

                // Create and show MyForm2 with the content and title
                MyForm2^ form2 = gcnew MyForm2();
                form2->SetTextAndTitle(gcnew System::String(content.c_str()), clickedButton->Text); // Pass the content and title to MyForm2
                form2->Show();
            }
            this->Close();
        }
    };


}
