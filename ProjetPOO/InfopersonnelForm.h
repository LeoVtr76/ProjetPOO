#pragma once

namespace Corbeille5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class InfopersonnelForm : public System::Windows::Forms::Form {
	public:
		InfopersonnelForm(void) {
			InitializeComponent();
		}

	protected:
		~InfopersonnelForm() {
			if (components) {
				delete components;
			}
		}

	private:
		System::Windows::Forms::Label^ messageLabel;
		System::Windows::Forms::Button^ okButton;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->messageLabel = (gcnew System::Windows::Forms::Label());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();

			// messageLabel
			this->messageLabel->AutoSize = true;
			this->messageLabel->Location = System::Drawing::Point(50, 50); // Adjust as needed
			this->messageLabel->Name = L"messageLabel";
			this->messageLabel->Size = System::Drawing::Size(200, 40); // Adjust as needed
			this->messageLabel->TabIndex = 0;
			this->messageLabel->Text = L"";

			// okButton
			this->okButton->Location = System::Drawing::Point(100, 200); // Adjust as needed
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(75, 23);
			this->okButton->TabIndex = 1;
			this->okButton->Text = L"OK";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &InfopersonnelForm::okButton_Click);

			// InfopersonnelForm
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->messageLabel);
			this->Name = L"InfopersonnelForm";
			this->Text = L"Information";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

		void okButton_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Close();
		}

	public:
		void SetMessage(String^ message) {
			this->messageLabel->Text = message;
		}
	};
}
