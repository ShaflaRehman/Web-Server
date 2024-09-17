#pragma once

#include <string>
#include <msclr/marshal_cppstd.h>
#include "Search.h"
#include "stopwords.h"
#include "MyForm1.h"
#include "Global_variables.h"
#include "file_freq.h"
#include "MyForm3.h"
#include <shellapi.h> // Include for ShellExecute

namespace WebEngine {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Button^ Search_button;
    protected: Search* obj;
    private: System::Windows::Forms::PictureBox^ pictureBox4;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::PictureBox^ pictureBoxIcon;
    private: System::Windows::Forms::Button^ button1;

    protected:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
            this->Search_button = (gcnew System::Windows::Forms::Button());
            this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->pictureBoxIcon = (gcnew System::Windows::Forms::PictureBox());
            this->button1 = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxIcon))->BeginInit();
            this->SuspendLayout();
            // 
            // Search_button
            // 
            this->Search_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
            this->Search_button->Location = System::Drawing::Point(2471, 872);
            this->Search_button->Margin = System::Windows::Forms::Padding(6);
            this->Search_button->Name = L"Search_button";
            this->Search_button->Size = System::Drawing::Size(240, 78);
            this->Search_button->TabIndex = 1;
            this->Search_button->Text = L"Search";
            this->Search_button->UseVisualStyleBackColor = true;
            this->Search_button->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
            // 
            // pictureBox4
            // 
            this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
            this->pictureBox4->Location = System::Drawing::Point(1046, 388);
            this->pictureBox4->Margin = System::Windows::Forms::Padding(6);
            this->pictureBox4->Name = L"pictureBox4";
            this->pictureBox4->Size = System::Drawing::Size(1280, 388);
            this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
            this->pictureBox4->TabIndex = 2;
            this->pictureBox4->TabStop = false;
            // 
            // textBox1
            // 
            this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
            this->textBox1->Location = System::Drawing::Point(974, 878);
            this->textBox1->Margin = System::Windows::Forms::Padding(6);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(1451, 68);
            this->textBox1->TabIndex = 0;
            this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
            this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox1_KeyDown);
            // 
            // pictureBoxIcon
            // 
            this->pictureBoxIcon->BackColor = System::Drawing::Color::White;
            this->pictureBoxIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBoxIcon.Image")));
            this->pictureBoxIcon->Location = System::Drawing::Point(984, 884);
            this->pictureBoxIcon->Margin = System::Windows::Forms::Padding(6);
            this->pictureBoxIcon->Name = L"pictureBoxIcon";
            this->pictureBoxIcon->Size = System::Drawing::Size(60, 60);
            this->pictureBoxIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->pictureBoxIcon->TabIndex = 3;
            this->pictureBoxIcon->TabStop = false;
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(30, 29);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(203, 83);
            this->button1->TabIndex = 4;
            this->button1->Text = L"History";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button1_MouseClick);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(3204, 1748);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->pictureBoxIcon);
            this->Controls->Add(this->pictureBox4);
            this->Controls->Add(this->Search_button);
            this->Controls->Add(this->textBox1);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Margin = System::Windows::Forms::Padding(6);
            this->Name = L"MyForm";
            this->Text = L"New Tab - Google Chrome";
            this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxIcon))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    }

    private: System::Void textBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
        if (e->KeyCode == System::Windows::Forms::Keys::Enter) {
            button1_Click(sender, e);
            e->SuppressKeyPress = true; // To prevent the 'ding' sound on Enter key press
        }
    }

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
    {
        obj = new Search();
        String^ s = textBox1->Text;
        to_search = msclr::interop::marshal_as<std::string>(s);

        // Check if the input is a URL
        if (to_search.find("http://") == 0 || to_search.find("https://") == 0) {
            // Open the URL in the default web browser
            System::Diagnostics::Process::Start(gcnew String(to_search.c_str()));
        }
        else {
            // Perform search
            obj->search(to_search);
            obj->SearchHistory(to_search);
            MyForm1^ display_form = gcnew MyForm1();
            String^ name = this->Name;
            string stdname = msclr::interop::marshal_as<std::string>(name);

            backStack.push(stdname);
            display_form->Show();
            this->Close();
        }
    }

    private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
  private: System::Void button1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
      // Read data from "History.txt"
      std::ifstream historyFile("History.txt");
      std::string historyData((std::istreambuf_iterator<char>(historyFile)), std::istreambuf_iterator<char>());
      historyFile.close();

      // Split historyData by newline characters ('\n')
      std::istringstream iss(historyData);
      std::vector<std::string> lines;
      std::string line;
      while (std::getline(iss, line)) {
          lines.push_back(line);
      }

      // Convert each group of three lines to a single System::String and concatenate
      String^ historyDataStr = "";
      for (size_t i = 0; i + 2 < lines.size(); i += 3) {
          std::string combinedLine = lines[i] + " " + lines[i + 1] + " " + lines[i + 2];
          historyDataStr += gcnew String(combinedLine.c_str()) + Environment::NewLine;
      }

      // Create a new instance of MyForm3
      MyForm3^ form3 = gcnew MyForm3();

      // Set the text of textBoxHistory
      form3->textBox1->Text = historyDataStr;

      // Show the form
      form3->Show();
  }

    };
}
