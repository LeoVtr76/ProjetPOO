#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

    public ref class CommandePanel : public UserControl {
    public:
        event EventHandler^ BackButtonClicked;
        event EventHandler^ NewButtonClicked;
        event EventHandler^ ExistingCommandClicked;

        CommandePanel() {
            InitializeComponent();
            this->Resize += gcnew EventHandler(this, &CommandePanel::OnResize);
        }

    protected:
        ~CommandePanel() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        Label^ Title;
        Button^ NewButton;
        Button^ ExistButton;
        Button^ BackButton;

        void InitializeComponent() {
            // Configuration du UserControl
            this->AutoSize = true;
            this->Dock = DockStyle::Fill;

            // Création et configuration du label
            Title = (gcnew Label());
            Title->Text = L"Gestion des commandes";
            Title->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 16, FontStyle::Bold);
            Title->AutoSize = true;
            Title->Location = Point(-20, 20); // Positionnement du titre
            Title->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

            // Création et configuration du bouton de retour
            BackButton = (gcnew Button());
            BackButton->Text = L"Retour";
            BackButton->Size = Drawing::Size(75, 23);
            BackButton->Location = Point(20, this->Height - 50); // Positionnement du bouton de retour
            BackButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom | AnchorStyles::Left);
            BackButton->Click += gcnew EventHandler(this, &CommandePanel::OnBackButtonClicked);

            // Création et configuration des boutons NewButton et ExistButton
            NewButton = (gcnew Button());
            NewButton->Text = L"Nouvelle Commande";
            NewButton->Size = Drawing::Size(150, 50);
            NewButton->Click += gcnew EventHandler(this, &CommandePanel::OnNewButtonClicked);

            ExistButton = (gcnew Button());
            ExistButton->Text = L"Commande existante";
            ExistButton->Size = Drawing::Size(150, 50);
            ExistButton->Click += gcnew EventHandler(this, &CommandePanel::OnExistingCommandClicked);

            // Ajout des contrôles au UserControl
            this->Controls->Add(Title);
            this->Controls->Add(BackButton);
            this->Controls->Add(NewButton);
            this->Controls->Add(ExistButton);

            AdjustButtonSizeAndPosition();
        }

        void OnResize(Object^ sender, EventArgs^ e) {
            AdjustButtonSizeAndPosition();
        }

        void AdjustButtonSizeAndPosition() {
            // Réglage de la taille et de la position des boutons en fonction de la nouvelle taille de la fenêtre
            int spacing = 20;
            int buttonWidth = (this->Width - 3 * spacing) / 2;
            int buttonHeight = 50;
            int buttonY = (this->Height - buttonHeight) / 2;

            NewButton->Location = Point(spacing, buttonY);
            NewButton->Size = Drawing::Size(buttonWidth, buttonHeight);

            ExistButton->Location = Point(2 * spacing + buttonWidth, buttonY);
            ExistButton->Size = Drawing::Size(buttonWidth, buttonHeight);
        }

        void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
            BackButtonClicked(this, e);
        }
        void OnNewButtonClicked(Object^ sender, EventArgs^ e) {
            NewButtonClicked(sender, e);
        }

        void OnExistingCommandClicked(Object^ sender, EventArgs^ e) {
            ExistingCommandClicked(sender, e);
        }
    };
}
