#pragma once

#include "DeleteConfirmForm.h"
#include "DatabaseManager.h"
#include "CLPersonnel.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

	public ref class PersonnelExistantPanel : public UserControl {

	public:
		event EventHandler^ BackButtonClicked;
		event EventHandler^ CheckBoxChecked;
		event EventHandler^ DeleteButtonClicked;

		PersonnelExistantPanel() {
			InitializeComponent();
			FillPersonnelList();
			this->Resize += gcnew EventHandler(this, &PersonnelExistantPanel::OnResize);
		}
	protected:
		~PersonnelExistantPanel() {
			if (components) {
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		bool firstLoad = true;
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
		TextBox^ HiringDateBox;
		TextBox^ HierarSupBox;
		TextBox^ HierarLevelBox;
		TextBox^ Addrbox;
		Label^ NameLab;
		Label^ FirstNameLab;
		Label^ HiringDateLab;
		Label^ HierarSupLab;
		Label^ HierarLevelLab;
		Label^ AddrLab;



		void InitializeComponent() {
			this->AutoSize = true;
			this->Dock = DockStyle::Fill;

			Title = (gcnew Label());
			Title->Text = L"Personnels Existants";
			Title->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 16, FontStyle::Bold);
			Title->AutoSize = true;
			Title->Location = Point(-50, 20);
			Title->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			BackButton = (gcnew Button());
			BackButton->TabIndex = 12;
			BackButton->Text = L"Retour";
			BackButton->Size = Drawing::Size(75, 25);
			BackButton->Location = Point(35, 115);
			BackButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom | AnchorStyles::Left);
			BackButton->Click += gcnew EventHandler(this, &PersonnelExistantPanel::OnBackButtonClicked);

			listBox1 = (gcnew ListBox());
			listBox1->TabIndex = 1;
			listBox1->Size = Drawing::Size(150, 80);
			listBox1->Location = Point(5, 20);
			listBox1->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Bottom);
			listBox1->SelectedIndexChanged += gcnew EventHandler(this, &PersonnelExistantPanel::OnListBoxSelectedIndexChanged);

			checkBox = (gcnew CheckBox());
			checkBox->TabIndex = 4;
			checkBox->Text = L"Cocher pour modifier";
			checkBox->Size = Drawing::Size(192, 36);
			checkBox->Location = Point(1, this->Height - checkBox->Height - 10);
			checkBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);
			checkBox->CheckedChanged += gcnew EventHandler(this, &PersonnelExistantPanel::OnCheckBoxChecked);

			DeleteButton = (gcnew Button());
			DeleteButton->TabIndex = 11;
			DeleteButton->Text = L"Supprimer";
			DeleteButton->Size = Drawing::Size(150, 50);
			DeleteButton->Location = Point(this->Width - DeleteButton->Width - 10, -20);
			DeleteButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);
			DeleteButton->Click += gcnew EventHandler(this, &PersonnelExistantPanel::OnDeleteButtonClicked);

			ValidButton = (gcnew Button());
			ValidButton->TabIndex = 12;
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
			FirstNameBox->Location = Point(this->Width - FirstNameBox->Width + 220, 270);
			FirstNameBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			FirstNameBox->ReadOnly = true;

			Addrbox = (gcnew TextBox());
			Addrbox->TabIndex = 7;
			Addrbox->Size = Drawing::Size(140, 60);
			Addrbox->Location = Point(this->Width - Addrbox->Width + 220, 360);
			Addrbox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			Addrbox->ReadOnly = true;

			HierarSupBox = (gcnew TextBox());
			HierarSupBox->TabIndex = 8;
			HierarSupBox->Size = Drawing::Size(140, 60);
			HierarSupBox->Location = Point(this->Width - HierarSupBox->Width + 100, 180);
			HierarSupBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			HierarSupBox->ReadOnly = true;

			HierarLevelBox = (gcnew TextBox());
			HierarLevelBox->TabIndex = 9;
			HierarLevelBox->Size = Drawing::Size(140, 60);
			HierarLevelBox->Location = Point(this->Width - HierarLevelBox->Width + 100, 270);
			HierarLevelBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			HierarLevelBox->ReadOnly = true;

			HiringDateBox = (gcnew TextBox());
			HiringDateBox->TabIndex = 10;
			HiringDateBox->Size = Drawing::Size(140, 60);
			HiringDateBox->Location = Point(this->Width - HiringDateBox->Width + 100, 360);
			HiringDateBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			HiringDateBox->ReadOnly = true;

			NameLab = (gcnew Label());
			NameLab->Text = L"Nom :";
			NameLab->Size = Drawing::Size(80, 60);
			NameLab->Location = Point(this->Width - NameLab->Width + 160, 160);
			NameLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			FirstNameLab = (gcnew Label());
			FirstNameLab->Text = L"Prénom(s) :";
			FirstNameLab->Size = Drawing::Size(80, 60);
			FirstNameLab->Location = Point(this->Width - FirstNameLab->Width + 160, 250);
			FirstNameLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			AddrLab = (gcnew Label());
			AddrLab->Text = L"Adresse :";
			AddrLab->Size = Drawing::Size(140, 60);
			AddrLab->Location = Point(this->Width - AddrLab->Width + 220, 340);
			AddrLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			HiringDateLab = (gcnew Label());
			HiringDateLab->Text = L"Date d'embauche:";
			HiringDateLab->Size = Drawing::Size(140, 60);
			HiringDateLab->Location = Point(this->Width - HiringDateLab->Width + 100, 160);
			HiringDateLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			HierarSupLab = (gcnew Label());
			HierarSupLab->Text = L"Supérieur hiérarchique :";
			HierarSupLab->Size = Drawing::Size(140, 60);
			HierarSupLab->Location = Point(this->Width - HierarSupLab->Width + 100, 250);
			HierarSupLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			HierarLevelLab = (gcnew Label());
			HierarLevelLab->Text = L"Niveau hiérarchique :";
			HierarLevelLab->Size = Drawing::Size(140, 60);
			HierarLevelLab->Location = Point(this->Width - HierarLevelLab->Width + 100, 340);
			HierarLevelLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

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
			this->Controls->Add(HiringDateBox);
			this->Controls->Add(HierarSupBox);
			this->Controls->Add(HierarLevelBox);
			this->Controls->Add(Addrbox);
			this->Controls->Add(NameLab);
			this->Controls->Add(FirstNameLab);
			this->Controls->Add(HiringDateLab);
			this->Controls->Add(HierarSupLab);
			this->Controls->Add(HierarLevelLab);
			this->Controls->Add(AddrLab);


			AdjustButtonSizeAndPosition();
		}
		void FillPersonnelList() {
			DatabaseManager^ dbManager = gcnew DatabaseManager();
			List<CLPersonnel^>^ personnelList = dbManager->GetAllPersonnel();

			listBox1->Items->Clear();
			for each (CLPersonnel ^ personnel in personnelList) {
				listBox1->Items->Add(personnel->GetId() + " " + personnel->GetNom() + " " + personnel->GetPrenom());
			}
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
			HiringDateBox->Size = Drawing::Size(newWidth, textBoxHeight);
			HierarSupBox->Size = Drawing::Size(newWidth, textBoxHeight);
			HierarLevelBox->Size = Drawing::Size(newWidth, textBoxHeight);
			Addrbox->Size = Drawing::Size(newWidth, textBoxHeight);
		}

		void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
			BackButtonClicked(this, e);
		}
		void OnListBoxSelectedIndexChanged(Object^ sender, EventArgs^ e) {
			if (listBox1->SelectedIndex != -1) {
				DatabaseManager^ dbManager = gcnew DatabaseManager();
				String^ item = listBox1->Items[listBox1->SelectedIndex]->ToString();
				int firstSpaceIndex = item->IndexOf(' ');
				int id;
				if (firstSpaceIndex != -1) {
					id = System::Convert::ToInt32(item->Substring(0, firstSpaceIndex));
				}
				int selectedPersonnelId = listBox1->SelectedIndex; // Vous devez déterminer comment obtenir l'ID du personnel sélectionné.
				CLPersonnel^ selectedPersonnel = dbManager->GetPersonnelById(id);

				if (selectedPersonnel != nullptr) {
					// Maintenant, mettez à jour les TextBox avec les informations de personnel
					NameBox->Text = selectedPersonnel->GetNom();
					FirstNameBox->Text = selectedPersonnel->GetPrenom();
					HiringDateBox->Text = selectedPersonnel->GetNiveauHierarchique(); //"NH";
					HierarSupBox->Text = selectedPersonnel->GetDateEmbauche().ToString("dd/MM/yyyy"); //"Date";
						
					HierarLevelBox->Text = selectedPersonnel->GetSuperieurHierarchique(); //"Superieur";
					Addrbox->Text = selectedPersonnel->GetAdresse();
				}
			}
		}
		void OnVisibleChanged(Object^ sender, EventArgs^ e) {
			if (this->Visible) {
				if (firstLoad) {
					FillPersonnelList();
					firstLoad = false;
				}
			}
		}
		void OnCheckBoxChecked(Object^ sender, EventArgs^ e) {
			bool isEnabled = dynamic_cast<CheckBox^>(sender)->Checked;

			NameBox->ReadOnly = !isEnabled;
			FirstNameBox->ReadOnly = !isEnabled;
			HiringDateBox->ReadOnly = !isEnabled;
			HierarSupBox->ReadOnly = !isEnabled;
			HierarLevelBox->ReadOnly = !isEnabled;
			Addrbox->ReadOnly = !isEnabled;
		}

		void OnDeleteButtonClicked(Object^ sender, EventArgs^ e) {
			DeleteConfirmForm^ confirmForm = gcnew DeleteConfirmForm();
			confirmForm->ShowDialog();
		}

	};
}