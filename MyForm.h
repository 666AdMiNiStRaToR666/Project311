#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex>
#include <msclr/marshal_cppstd.h>

namespace Project311 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    bool isConsonant(char c) {
        // ���������, �������� �� ������ ���������
        c = std::tolower(c);
        return (c == 'b' || c == 'c' || c == 'd' || c == 'f' || c == 'g' || c == 'h' || c == 'k' ||
            c == 'l' || c == 'm' || c == 'n' || c == 'p' || c == 'q' || c == 'r' || c == 's' ||
            c == 't' || c == 'v' || c == 'w' || c == 'x' || c == 'z');
    }

    std::string sortWordsByConsonantRatio(const std::string& sentence) {
        // ��������� ����������� �� �����
        std::regex wordRegex("\\b(\\w+)\\b");
        std::sregex_iterator iter(sentence.begin(), sentence.end(), wordRegex);
        std::sregex_iterator end;

        std::vector<std::pair<std::string, double>> words;

        // �������� �� ������� ����� � ��������� ���� ���������
        while (iter != end) {
            std::smatch match = *iter;
            std::string word = match.str();

            int consonantCount = 0;
            int totalCount = 0;

            // ������������ ���������� ��������� � �����
            for (char c : word) {
                if (std::isalpha(c)) {
                    totalCount++;
                    if (isConsonant(c)) {
                        consonantCount++;
                    }
                }
            }

            // ��������� ���� ���������
            double consonantRatio = static_cast<double>(consonantCount) / totalCount;

            // ��������� ����� � ��� ���� ��������� � ������
            words.push_back(std::make_pair(word, consonantRatio));

            ++iter;
        }

        // ��������� ����� �� ����������� ���� ���������
        std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
            });

        // �������� ��������������� ����� � ������
        std::string result;
        for (const auto& word : words) {
            result += word.first + " ";
        }

        return result;
    }

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
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::TextBox^ textBox1;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->SuspendLayout();
            // 
            // button1
            // 
            this->button1->AutoSize = true;
            this->button1->Location = System::Drawing::Point(40, 110);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(201, 30);
            this->button1->TabIndex = 0;
            this->button1->Text = L"����������� � �����������";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(52, 155);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(0, 16);
            this->label1->TabIndex = 1;
            // 
            // textBox1
            // 
            this->textBox1->Location = System::Drawing::Point(40, 77);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(200, 22);
            this->textBox1->TabIndex = 2;
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(279, 233);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->button1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->Name = L"MyForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"������������ ����";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        // �������� ��������� ����������� �� ���������� ����
        System::String^ inputSentence = textBox1->Text;

        // ����������� System::String � std::string
        std::string sentence = msclr::interop::marshal_as<std::string>(inputSentence);

        // �������� ������� ��� ������������ � ���������� ����
        std::string result = sortWordsByConsonantRatio(sentence);

        // ����������� std::string � System::String ��� ����������� �� �����
        System::String^ outputResult = gcnew System::String(result.c_str());

        // ������� ��������� �� �����
        label1->Text = outputResult;
    }

    private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}
//����������� � ����������� ����� ��������� ����������� � ������������ � ������ ���� ��������� 
//(B, C, D, F, G, H, K, L, M, N, P, Q, R, S, T, V, W, X, Z) � ���� ������.