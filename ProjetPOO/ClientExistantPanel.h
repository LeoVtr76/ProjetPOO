#pragma once

#include "DeleteConfirmForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

	public ref class ClientExistantPanel : public UserControl {

	public:
		event EventHandler^ BackButtonClicked;
		event EventHandler^ CheckBoxChecked;
		event EventHandler^ DeleteButtonClicked;

		ClientExistantPanel() {
			InitializeComponent();
			this->Resize += gcnew EventHandler(this, &ClientExistantPanel::OnResize);
		}
	protected:
		~ClientExistantPanel() {
			if (components) {
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

		Label^ Title;
		ListBox^ listBox1;
		Button^ BackButton;
		CheckBox^ checkBox;
		Button^ DeleteButton;
		Button^ ValidButton;
		Button^ PreButton;
		Button^ NextButton;
		TextBox^ NameBox;
		TextBox^ FirstNameBox;
		TextBox^ BirthDateBox;
		TextBox^ AddrBox;
		Label^ NameLab;
		Label^ FirstNameLab;
		Label^ BirthDateLab;
		Label^ AddrLab;
		

		void InitializeComponent() {
			this->AutoSize = true;
			this->Dock = DockStyle::Fill;

			Title = (gcnew Label());
			Title->Text = L"Clients Existants";
			Title->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 16, FontStyle::Bold);
			Title->AutoSize = true;
			Title->Location = Point(-20, 40);
			Title->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			BackButton = (gcnew Button());
			BackButton->TabIndex = 11;
			BackButton->Text = L"Retour";
			BackButton->Size = Drawing::Size(75, 23);
			BackButton->Location = Point(this->Width - BackButton->Width - 10, 25);
			BackButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
			BackButton->Click += gcnew EventHandler(this, &ClientExistantPanel::OnBackButtonClicked);

			listBox1 = (gcnew ListBox());
			listBox1->TabIndex = 1;
			listBox1->Size = Drawing::Size(200, 130);
			listBox1->Location = Point(1, 11);
			listBox1->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Bottom);

			checkBox = (gcnew CheckBox());
			checkBox->TabIndex = 4;
			checkBox->Text = L"Cocher pour modifier";
			checkBox->Size = Drawing::Size(192, 36);
			checkBox->Location = Point(1, this->Height - checkBox->Height - 10);
			checkBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);
			checkBox->CheckedChanged += gcnew EventHandler(this, &ClientExistantPanel::OnCheckBoxChecked);

			DeleteButton = (gcnew Button());
			DeleteButton->TabIndex = 9;
			DeleteButton->Text = L"Supprimer";
			DeleteButton->Size = Drawing::Size(150, 50);
			DeleteButton->Location = Point(this->Width - DeleteButton->Width - 10, -20);
			DeleteButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);
			DeleteButton->Click += gcnew EventHandler(this, &ClientExistantPanel::OnDeleteButtonClicked);

			ValidButton = (gcnew Button());
			ValidButton->TabIndex = 10;
			ValidButton->Text = L"Valider";
			ValidButton->Size = Drawing::Size(150, 50);
			ValidButton->Location = Point(this->Width - ValidButton->Width - 10, 40);
			ValidButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);

			PreButton = (gcnew Button());
			PreButton->TabIndex = 2;
			PreButton->Text = L"<";
			PreButton->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 12, FontStyle::Bold);
			PreButton->Size = Drawing::Size(30, 30);
			PreButton->Location = Point(-20, this->Height - PreButton->Height - 10);
			PreButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom);

			NextButton = (gcnew Button());
			NextButton->TabIndex = 3;
			NextButton->Text = L">";
			NextButton->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 12, FontStyle::Bold);
			NextButton->Size = Drawing::Size(30, 30);
			NextButton->Location = Point(150, this->Height - PreButton->Height - 10);
			NextButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom);

			NameBox = (gcnew TextBox());
			NameBox->TabIndex = 5;
			NameBox->Size = Drawing::Size(140, 60);
			NameBox->Location = Point(this->Width - NameBox->Width + 220, 180);
			NameBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			NameBox->ReadOnly = true;

			FirstNameBox = (gcnew TextBox());
			FirstNameBox->TabIndex = 6;
			FirstNameBox->Size = Drawing::Size(140, 60);
			FirstNameBox->Location = Point(this->Width - FirstNameBox->Width + 220, 290);
			FirstNameBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			FirstNameBox->ReadOnly = true;

			BirthDateBox = (gcnew TextBox());
			BirthDateBox->TabIndex = 7;
			BirthDateBox->Size = Drawing::Size(140, 60);
			BirthDateBox->Location = Point(this->Width - BirthDateBox->Width + 100, 180);
			BirthDateBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			BirthDateBox->ReadOnly = true;

			AddrBox = (gcnew TextBox());
			AddrBox->TabIndex = 8;
			AddrBox->Size = Drawing::Size(140, 60);
			AddrBox->Location = Point(this->Width - AddrBox->Width + 100, 290);
			AddrBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			AddrBox->ReadOnly = true;

			NameLab = (gcnew Label());
			NameLab->Text = L"Nom  :";
			NameLab->Size = Drawing::Size(80, 60);
			NameLab->Location = Point(this->Width - NameLab->Width + 160, 160);
			NameLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			FirstNameLab = (gcnew Label());
			FirstNameLab->Text = L"Prénom :";
			FirstNameLab->Size = Drawing::Size(80, 60);
			FirstNameLab->Location = Point(this->Width - FirstNameLab->Width + 160, 270);
			FirstNameLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			BirthDateLab = (gcnew Label());
			BirthDateLab->Text = L"Date de naissance :";
			BirthDateLab->Size = Drawing::Size(140, 60);
			BirthDateLab->Location = Point(this->Width - BirthDateLab->Width + 100, 160);
			BirthDateLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			AddrLab = (gcnew Label());
			AddrLab->Text = L"Adresse :";
			AddrLab->Size = Drawing::Size(140, 60);
			AddrLab->Location = Point(this->Width - AddrLab->Width + 100, 270);
			AddrLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			this->Controls->Add(Title);
			this->Controls->Add(listBox1);
			this->Controls->Add(BackButton);
			this->Controls->Add(checkBox);
			this->Controls->Add(DeleteButton);
			this->Controls->Add(ValidButton);
			this->Controls->Add(PreButton);
			this->Controls->Add(NextButton);
			this->Controls->Add(NameBox);
			this->Controls->Add(FirstNameBox);
			this->Controls->Add(BirthDateBox);
			this->Controls->Add(AddrBox);
			this->Controls->Add(NameLab);
			this->Controls->Add(FirstNameLab);
			this->Controls->Add(BirthDateLab);
			this->Controls->Add(AddrLab);

			AdjustButtonSizeAndPosition();
		}


		void OnResize(Object^ sender, EventArgs^ e) {
			AdjustButtonSizeAndPosition();
		}


		void AdjustButtonSizeAndPosition() {
			int spacing = 20;
			int textBoxHeight = 60;
			int textBoxWidth = 140;
			double scale = 0.5;

			int newWidth = textBoxWidth + ((this->Width - 800) * scale);

			newWidth = Math::Max(newWidth, textBoxHeight);

			NameBox->Size = Drawing::Size(newWidth, textBoxHeight);
			FirstNameBox->Size = Drawing::Size(newWidth, textBoxHeight);
			BirthDateBox->Size = Drawing::Size(newWidth, textBoxHeight);
			AddrBox->Size = Drawing::Size(newWidth, textBoxHeight);
		}

		void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
			BackButtonClicked(this, e);
		}

		void OnCheckBoxChecked(Object^ sender, EventArgs^ e) {
			bool isEnabled = dynamic_cast<CheckBox^>(sender)->Checked;

			NameBox->ReadOnly = !isEnabled;
			FirstNameBox->ReadOnly = !isEnabled;
			BirthDateBox->ReadOnly = !isEnabled;
			AddrBox->ReadOnly = !isEnabled;
		}

		void OnDeleteButtonClicked(Object^ sender, EventArgs^ e) {
			DeleteConfirmForm^ confirmForm = gcnew DeleteConfirmForm();
			confirmForm->ShowDialog();
		}

	};
}