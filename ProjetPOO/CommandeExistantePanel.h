#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

	public ref class CommandeExistantePanel : public UserControl {

	public:
		event EventHandler^ BackButtonClicked;
		event EventHandler^ CheckBoxChecked;

		CommandeExistantePanel() {
			InitializeComponent();
			this->Resize += gcnew EventHandler(this, &CommandeExistantePanel::OnResize);
		}
	protected:
		~CommandeExistantePanel() {
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
		TextBox^ RefBox;
		ComboBox^ ArtBox;
		TextBox^ MontBox;
		TextBox^ AdrLivBox;
		TextBox^ DateLivBox;
		TextBox^ DatePaiBox;
		Label^ RefLab;
		Label^ ArtLab;
		Label^ MontLab;
		Label^ AdrLivLab;
		Label^ DateLivLab;
		Label^ DatePaiLab;



		void InitializeComponent() {
			this->AutoSize = true;
			this->Dock = DockStyle::Fill;

			Title = (gcnew Label());
			Title->Text = L"Commandes Existantes";
			Title->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 16, FontStyle::Bold);
			Title->AutoSize = true;
			Title->Location = Point(-50,20);
			Title->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			BackButton = (gcnew Button());
			BackButton->TabIndex = 13;
			BackButton->Text = L"Retour";
			BackButton->Size = Drawing::Size(75, 23);
			BackButton->Location = Point(this->Width - BackButton->Width - 10, 25);
			BackButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
			BackButton->Click += gcnew EventHandler(this, &CommandeExistantePanel::OnBackButtonClicked);

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
			checkBox->CheckedChanged += gcnew EventHandler(this, &CommandeExistantePanel::OnCheckBoxChecked);

			DeleteButton = (gcnew Button());
			DeleteButton->TabIndex = 11;
			DeleteButton->Text = L"Supprimer";
			DeleteButton->Size = Drawing::Size(150, 50);
			DeleteButton->Location = Point(this->Width - DeleteButton->Width - 10, -20);
			DeleteButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);

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

			RefBox = (gcnew TextBox());
			RefBox->Text = L"BonjourLeMonde!";
			RefBox->TabIndex = 5;
			RefBox->Size = Drawing::Size(140, 60);
			RefBox->Location = Point(this->Width - RefBox->Width + 220, 180);
			RefBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			RefBox->ReadOnly = true;
			RefBox->Enabled = false;

			ArtBox = (gcnew ComboBox());
			ArtBox->TabIndex = 6;
			ArtBox->Size = Drawing::Size(140, 60);
			ArtBox->Location = Point(this->Width - ArtBox->Width + 220, 270);
			ArtBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			MontBox = (gcnew TextBox());
			MontBox->TabIndex = 7;
			MontBox->Size = Drawing::Size(140, 60);
			MontBox->Location = Point(this->Width - MontBox->Width + 220, 360);
			MontBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			MontBox->ReadOnly = true;

			AdrLivBox = (gcnew TextBox());
			AdrLivBox->TabIndex = 8;
			AdrLivBox->Size = Drawing::Size(140, 60);
			AdrLivBox->Location = Point(this->Width - AdrLivBox->Width + 100, 180);
			AdrLivBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			AdrLivBox->ReadOnly = true;

			DateLivBox = (gcnew TextBox());
			DateLivBox->TabIndex = 9;
			DateLivBox->Size = Drawing::Size(140, 60);
			DateLivBox->Location = Point(this->Width - DateLivBox->Width + 100, 270);
			DateLivBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			DateLivBox->ReadOnly = true;

			DatePaiBox = (gcnew TextBox());
			DatePaiBox->TabIndex = 10;
			DatePaiBox->Size = Drawing::Size(140, 60);
			DatePaiBox->Location = Point(this->Width - DatePaiBox->Width + 100, 360);
			DatePaiBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			DatePaiBox->ReadOnly = true;

			RefLab = (gcnew Label());
			RefLab->Text = L"Référence :";
			RefLab->Size = Drawing::Size(80, 60);
			RefLab->Location = Point(this->Width - RefLab->Width + 160, 160);
			RefLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			ArtLab = (gcnew Label());
			ArtLab->Text = L"Article(s) :";
			ArtLab->Size = Drawing::Size(80, 60);
			ArtLab->Location = Point(this->Width - ArtLab->Width + 160, 250);
			ArtLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			MontLab = (gcnew Label());
			MontLab->Text = L"Montant de la commande :";
			MontLab->Size = Drawing::Size(140, 60);
			MontLab->Location = Point(this->Width - MontLab->Width + 220, 340);
			MontLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			AdrLivLab = (gcnew Label());
			AdrLivLab->Text = L"Adresse de livraison :";
			AdrLivLab->Size = Drawing::Size(140, 60);
			AdrLivLab->Location = Point(this->Width - AdrLivLab->Width + 100, 160);
			AdrLivLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			DateLivLab = (gcnew Label());
			DateLivLab->Text = L"Date de livraison :";
			DateLivLab->Size = Drawing::Size(140, 60);
			DateLivLab->Location = Point(this->Width - DateLivLab->Width + 100, 250);
			DateLivLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			DatePaiLab = (gcnew Label());
			DatePaiLab->Text = L"Date de paiement :";
			DatePaiLab->Size = Drawing::Size(140, 60);
			DatePaiLab->Location = Point(this->Width - DatePaiLab->Width + 100, 340);
			DatePaiLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);



			this->Controls->Add(Title);
			this->Controls->Add(listBox1);
			this->Controls->Add(BackButton);
			this->Controls->Add(checkBox);
			this->Controls->Add(DeleteButton);
			this->Controls->Add(ValidButton);
			this->Controls->Add(PreButton);
			this->Controls->Add(NextButton);
			this->Controls->Add(RefBox);
			this->Controls->Add(ArtBox);
			this->Controls->Add(MontBox);
			this->Controls->Add(AdrLivBox);
			this->Controls->Add(DateLivBox);
			this->Controls->Add(DatePaiBox);
			this->Controls->Add(RefLab);
			this->Controls->Add(ArtLab);
			this->Controls->Add(MontLab);
			this->Controls->Add(AdrLivLab);
			this->Controls->Add(DateLivLab);
			this->Controls->Add(DatePaiLab);


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
			
			int newWidth = textBoxWidth + ((this->Width - 800)* scale);

			newWidth = Math::Max(newWidth, textBoxHeight);

			RefBox->Size = Drawing::Size(newWidth, textBoxHeight);
			ArtBox->Size = Drawing::Size(newWidth, textBoxHeight);
			MontBox->Size = Drawing::Size(newWidth, textBoxHeight);
			AdrLivBox->Size = Drawing::Size(newWidth, textBoxHeight);
			DateLivBox->Size = Drawing::Size(newWidth, textBoxHeight);
			DatePaiBox->Size = Drawing::Size(newWidth, textBoxHeight);
		}

			
			
		

		void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
			BackButtonClicked(this, e);
		}

		void OnCheckBoxChecked(Object^ sender, EventArgs^ e) {
			bool isEnabled = dynamic_cast<CheckBox^>(sender)->Checked;

			RefBox->ReadOnly = !isEnabled;
			MontBox->ReadOnly = !isEnabled;
			AdrLivBox->ReadOnly = !isEnabled;
			DateLivBox->ReadOnly = !isEnabled;
			DatePaiBox->ReadOnly = !isEnabled;
		}
	};
}