#pragma once

#include "DeleteConfirmForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

	public ref class ExistingArticlePanel : public UserControl {

	public:
		event EventHandler^ BackButtonClicked;
		event EventHandler^ CheckBoxChecked;
		event EventHandler^ DeleteButtonClicked;

		ExistingArticlePanel() {
			InitializeComponent();
			this->Resize += gcnew EventHandler(this, &ExistingArticlePanel::OnResize);
		}
	protected:
		~ExistingArticlePanel() {
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
		TextBox^ QuantityBox;
		TextBox^ PriceUETBox;
		TextBox^ RestockingTresholdBox;
		Label^ NameLab;
		Label^ QuantityLab;
		Label^ PriceUETLab;
		Label^ RestockingTresholdLab;


		void InitializeComponent() {
			this->AutoSize = true;
			this->Dock = DockStyle::Fill;

			Title = (gcnew Label());
			Title->Text = L"Articles Existants";
			Title->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 16, FontStyle::Bold);
			Title->AutoSize = true;
			Title->Location = Point(-20, 20);
			Title->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			BackButton = (gcnew Button());
			BackButton->TabIndex = 12;
			BackButton->Text = L"Retour";
			BackButton->Size = Drawing::Size(75, 25);
			BackButton->Location = Point(35, 115);
			BackButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom | AnchorStyles::Left);
			BackButton->Click += gcnew EventHandler(this, &ExistingArticlePanel::OnBackButtonClicked);

			listBox1 = (gcnew ListBox());
			listBox1->TabIndex = 1;
			listBox1-> Size = Drawing::Size(150, 80);
			listBox1->Location = Point(5, 20);
			listBox1->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Bottom);

			checkBox = (gcnew CheckBox());
			checkBox->TabIndex = 4;
			checkBox->Text = L"Cocher pour modifier";
			checkBox->Size = Drawing::Size(192, 36);
			checkBox->Location = Point(1, this->Height - checkBox->Height - 10);
			checkBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);
			checkBox->CheckedChanged += gcnew EventHandler(this, &ExistingArticlePanel::OnCheckBoxChecked);

			DeleteButton = (gcnew Button());
			DeleteButton->TabIndex = 9;
			DeleteButton->Text = L"Supprimer";
			DeleteButton->Size = Drawing::Size(150, 50);
			DeleteButton->Location = Point(this->Width - DeleteButton->Width - 10, -20);
			DeleteButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);
			DeleteButton->Click += gcnew EventHandler(this, &ExistingArticlePanel::OnDeleteButtonClicked);

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

			QuantityBox = (gcnew TextBox());
			QuantityBox->TabIndex = 6;
			QuantityBox->Size = Drawing::Size(140, 60);
			QuantityBox->Location = Point(this->Width - QuantityBox->Width + 220, 290);
			QuantityBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			QuantityBox->ReadOnly = true;

			PriceUETBox = (gcnew TextBox());
			PriceUETBox->TabIndex = 7;
			PriceUETBox->Size = Drawing::Size(140, 60);
			PriceUETBox->Location = Point(this->Width - PriceUETBox->Width + 100, 180);
			PriceUETBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			PriceUETBox->ReadOnly = true;

			RestockingTresholdBox = (gcnew TextBox());
			RestockingTresholdBox->TabIndex = 8;
			RestockingTresholdBox->Size = Drawing::Size(140, 60);
			RestockingTresholdBox->Location = Point(this->Width - RestockingTresholdBox->Width + 100, 290);
			RestockingTresholdBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			RestockingTresholdBox->ReadOnly = true;

			NameLab = (gcnew Label());
			NameLab->Text = L"Nom  :";
			NameLab->Size = Drawing::Size(80, 60);
			NameLab->Location = Point(this->Width - NameLab->Width + 160, 160);
			NameLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			QuantityLab = (gcnew Label());
			QuantityLab->Text = L"Quantité :";
			QuantityLab->Size = Drawing::Size(80, 60);
			QuantityLab->Location = Point(this->Width - QuantityLab->Width + 160, 270);
			QuantityLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			PriceUETLab = (gcnew Label());
			PriceUETLab->Text = L"Prix Unitaire Hors Taxes :";
			PriceUETLab->Size = Drawing::Size(140, 60);
			PriceUETLab->Location = Point(this->Width - PriceUETLab->Width + 100, 160);
			PriceUETLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			RestockingTresholdLab = (gcnew Label());
			RestockingTresholdLab->Text = L"Seuil de réapprovisionnement :";
			RestockingTresholdLab->Size = Drawing::Size(180, 60);
			RestockingTresholdLab->Location = Point(this->Width - RestockingTresholdLab->Width + 140, 270);
			RestockingTresholdLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			this->Controls->Add(Title);
			this->Controls->Add(listBox1);
			this->Controls->Add(BackButton);
			this->Controls->Add(checkBox);
			this->Controls->Add(DeleteButton);
			this->Controls->Add(ValidButton);
			this->Controls->Add(PreButton);
			this->Controls->Add(NextButton);
			this->Controls->Add(NameBox);
			this->Controls->Add(QuantityBox);
			this->Controls->Add(PriceUETBox);
			this->Controls->Add(RestockingTresholdBox);
			this->Controls->Add(NameLab);
			this->Controls->Add(QuantityLab);
			this->Controls->Add(PriceUETLab);
			this->Controls->Add(RestockingTresholdLab);

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
			QuantityBox->Size = Drawing::Size(newWidth, textBoxHeight);
			PriceUETBox->Size = Drawing::Size(newWidth, textBoxHeight);
			RestockingTresholdBox->Size = Drawing::Size(newWidth, textBoxHeight);
		}

		void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
			BackButtonClicked(this, e);
		}

		void OnCheckBoxChecked(Object^ sender, EventArgs^ e) {
			bool isEnabled = dynamic_cast<CheckBox^>(sender)->Checked;

			NameBox->ReadOnly = !isEnabled;
			QuantityBox->ReadOnly = !isEnabled;
			PriceUETBox->ReadOnly = !isEnabled;
			RestockingTresholdBox->ReadOnly = !isEnabled;
		}

		void OnDeleteButtonClicked(Object^ sender, EventArgs^ e) {
			DeleteConfirmForm^ confirmForm = gcnew DeleteConfirmForm();
			confirmForm->ShowDialog();
		}

	};
}
