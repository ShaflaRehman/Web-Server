public ref class MyForm3 : public System::Windows::Forms::Form
{
public:
    MyForm3()
    {
        InitializeComponent();
    }

protected:
    ~MyForm3()
    {
        if (components)
        {
            delete components;
        }
    }

public: System::Windows::Forms::TextBox^ textBox1;

protected:
private:
    System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
    void InitializeComponent(void)
    {
        this->textBox1 = (gcnew System::Windows::Forms::TextBox());
        this->SuspendLayout();
        // 
        // textBox1
        // 
        this->textBox1->Location = System::Drawing::Point(50, 50); // Set a margin from the top-left corner
        this->textBox1->Multiline = true;
        this->textBox1->Name = L"textBox1";
        this->textBox1->Size = System::Drawing::Size(1800, 1300); // Adjust size
        this->textBox1->TabIndex = 0;
        this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 16)); // Set a readable font and size
        this->textBox1->WordWrap = true; // Enable word wrap
        this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical; // Add vertical scrollbar
        this->textBox1->ReadOnly = true; // Make it read-only if you only want to display text
        this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm3::textBox1_TextChanged);
        // 
        // MyForm3
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(1920, 1080); // Set client size to full HD resolution
        this->Controls->Add(this->textBox1);
        this->Margin = System::Windows::Forms::Padding(8, 7, 8, 7);
        this->Name = L"MyForm3";
        this->Text = L"MyForm3";
        this->Load += gcnew System::EventHandler(this, &MyForm3::MyForm3_Load);
        this->ResumeLayout(false);
        this->PerformLayout();
    }
#pragma endregion

private: System::Void MyForm3_Load(System::Object^ sender, System::EventArgs^ e) {
    // Optionally, load any initial text or perform other setup here
    // Example: textBox1->Text = "Initial Text";
}

private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    // Handle text changed event if needed
}
};
