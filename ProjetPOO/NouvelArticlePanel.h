#pragma once
#include "DatabaseManager.h"
#include "InfopersonnelForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

    public ref class NewArticlePanel : public UserControl {
    public:
        event EventHandler^ BackButtonClicked;
        NewArticlePanel() {
            InitializeComponent();
            this->Resize += gcnew EventHandler(this, &NewArticlePanel::OnResize);
        }

    protected:
        ~NewArticlePanel() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        Label^ Title;
        TextBox^ TextBoxArticleName;
        Label^ LabelArticleName;
        TextBox^ TextBoxArticlePrice;
        Label^ LabelArticlePrice;
        TextBox^ TextBoxArticleAmount;
        Label^ LabelArticleAmount;
        Label^ LabelSeuilReap;
        TextBox^ TextBoxSeuilReap;
        Button^ BackButton;
        Button^ ValidateButton;

        void InitializeComponent() {
            // Configuration du UserControl
            this->AutoSize = true;
            this->Dock = DockStyle::Fill;

            // Création et configuration du label
            Title = (gcnew Label());
            Title->Text = L"Nouvel article";
            Title->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 16, FontStyle::Bold);
            Title->AutoSize = true;
            Title->Location = Point(20, 20); // Positionnement du titre
            Title->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);

            // Création et configuration du bouton de retour
            BackButton = (gcnew Button());
            BackButton->Text = L"Retour";
            BackButton->Size = Drawing::Size(75, 23);
            BackButton->Location = Point(20, this->Height - 50); // Positionnement du bouton de retour
            BackButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom | AnchorStyles::Left);
            BackButton->Click += gcnew EventHandler(this, &NewArticlePanel::OnBackButtonClicked);

            // Création des TextBox et des Label    
            TextBoxArticleName = CreateTextBox();
            LabelArticleName = CreateLabel(L"Nom de l'article");
            TextBoxArticleAmount = CreateTextBox();
            LabelArticleAmount = CreateLabel(L"Quantité de l'article");
            TextBoxArticlePrice = CreateTextBox();
            LabelArticlePrice = CreateLabel(L"Prix de l'article");
            LabelSeuilReap = CreateLabel(L"Seuil de réapprovisionnement");
            TextBoxSeuilReap = CreateTextBox();

            ValidateButton = CreateButton(L"Valider");
            ValidateButton->Click += gcnew System::EventHandler(this, &NewArticlePanel::OnValidateButtonClicked);
            // Ajout des contrôles au UserControl
            this->Controls->Add(Title);
            this->Controls->Add(TextBoxArticleName);
            this->Controls->Add(LabelArticleName);
            this->Controls->Add(TextBoxArticlePrice);
            this->Controls->Add(LabelArticlePrice);
            this->Controls->Add(TextBoxArticleAmount);
            this->Controls->Add(LabelArticleAmount);
            this->Controls->Add(LabelSeuilReap);
            this->Controls->Add(TextBoxSeuilReap);
            this->Controls->Add(BackButton);
            this->Controls->Add(ValidateButton);

            AdjustControlPositions();
        }
        void ClearFields() {
            this->TextBoxArticleName->Clear();
            this->TextBoxArticlePrice->Clear();
            this->TextBoxArticleAmount->Clear();
            this->TextBoxSeuilReap->Clear();
        }

        TextBox^ CreateTextBox() {
            TextBox^ textBox = gcnew TextBox();
            textBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
            return textBox;
        }
        Button^ CreateButton(String^ text) {
            Button^ button = gcnew Button();
            button->Text = text;
            button->AutoSize = true;
            button->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom | AnchorStyles::Right);
            return button;
        }
        Label^ CreateLabel(String^ text) {
            Label^ label = gcnew Label();
            label->Text = text;
            label->AutoSize = true;
            label->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);
            return label;
        }

        void OnResize(Object^ sender, EventArgs^ e) {
            AdjustControlPositions();
        }

        void AdjustControlPositions() {
            int spacing = 20;
            int labelHeight = 20;
            int textBoxHeight = 20;
            int verticalSpacing = 10;

            // Positionnement des labels et des TextBox
            LabelArticleName->Location = Point(spacing, Title->Bottom + spacing);
            TextBoxArticleName->Location = Point(spacing, LabelArticleName->Bottom + verticalSpacing);
            TextBoxArticleName->Size = Drawing::Size(this->Width - 2 * spacing, textBoxHeight);

            LabelArticlePrice->Location = Point(spacing, TextBoxArticleName->Bottom + spacing);
            TextBoxArticlePrice->Location = Point(spacing, LabelArticlePrice->Bottom + verticalSpacing);
            TextBoxArticlePrice->Size = Drawing::Size(this->Width - 2 * spacing, textBoxHeight);

            LabelArticleAmount->Location = Point(spacing, TextBoxArticlePrice->Bottom + spacing);
            TextBoxArticleAmount->Location = Point(spacing, LabelArticleAmount->Bottom + verticalSpacing);
            TextBoxArticleAmount->Size = Drawing::Size(this->Width - 2 * spacing, textBoxHeight);

            LabelSeuilReap->Location = Point(spacing, TextBoxArticleAmount->Bottom + spacing);
            TextBoxSeuilReap->Location = Point(spacing, LabelSeuilReap->Bottom + verticalSpacing);
            TextBoxSeuilReap->Size = Drawing::Size(this->Width - 2 * spacing, textBoxHeight);

            // Réajuster la position du bouton de retour en bas à gauche
            BackButton->Location = Point(spacing, this->Height - BackButton->Height - spacing);
            ValidateButton->Location = Point(this->Width - ValidateButton->Width - spacing, this->Height - ValidateButton->Height - spacing);
        }

        void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
            BackButtonClicked(this, e);
        }
        void OnValidateButtonClicked(Object^ sender, EventArgs^ e) {
            DatabaseManager^ dbManager = gcnew DatabaseManager();
            String^ name = TextBoxArticleName->Text;
            String^ price = TextBoxArticlePrice->Text;
            String^ amount = TextBoxArticleAmount->Text;
            String^ sr = TextBoxSeuilReap->Text;
            InfopersonnelForm^ messageForm = gcnew InfopersonnelForm();
            if (dbManager->ArticleExist(name)) {
                messageForm->SetMessage("L'article existe déjà.");
            }
            else {
                dbManager->AddArticle(name, price, amount, sr);;
                messageForm->SetMessage("L'article à été ajouté avec succès !");
                ClearFields();
            }
            messageForm->ShowDialog();
            
        }
    };
}
