#pragma once

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

namespace Corbeille5 {

	

	public ref class DeleteConfirmForm : public System::Windows::Forms::Form {
	public:
		event EventHandler^ YesButtonClicked;
		event EventHandler^ NoButtonClicked;

		DeleteConfirmForm() {
			InitializeComponent();
		}

	protected:
		~DeleteConfirmForm() {
			if (components) {
				delete components;
			}
		}

	private:

		System::ComponentModel::Container^ components;

		Label^ ConfirmLab;
		Button^ YesButton;
		Button^ NoButton;

		void InitializeComponent() {
			this->AutoSize = true;
			this->Dock = DockStyle::Fill;
			this->ClientSize = System::Drawing::Size(300, 100); 


			ConfirmLab = (gcnew Label());
			ConfirmLab->Text = L"Voulez-vous vraiment supprimer le personnel ?";
			ConfirmLab->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 8);
			ConfirmLab->AutoSize = true;
			ConfirmLab->Location = Point(40, 30);
			ConfirmLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			YesButton = (gcnew Button());
			YesButton->TabIndex = 1;
			YesButton->Text = L"Oui";
			YesButton->Size = Drawing::Size(40, 20);
			YesButton->Location = Point(80,60);
			YesButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			YesButton->Click += gcnew EventHandler(this, &DeleteConfirmForm::OnYesButtonClicked);

			NoButton = (gcnew Button());
			NoButton->TabIndex = 2;
			NoButton->Text = L"Non";
			NoButton->Size = Drawing::Size(40, 20);
			NoButton->Location = Point(180, 60);
			NoButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			NoButton->Click += gcnew EventHandler(this, &DeleteConfirmForm::OnNoButtonClicked);

			this->Controls->Add(ConfirmLab);
			this->Controls->Add(YesButton);
			this->Controls->Add(NoButton);

		}

		void OnYesButtonClicked(System::Object^ sender, System::EventArgs^ e) {
			this->Close();
		}

		void OnNoButtonClicked(System::Object^ sender, System::EventArgs^ e) {
			this->Close();
		}
	
	};
}