#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

    public ref class PersonnelPanel : public UserControl {
    public:
        event EventHandler^ BackButtonClicked;
        event EventHandler^ NewStaffButtonClicked;
        event EventHandler^ ExistingStaffButtonClicked;

        PersonnelPanel() {
            InitializeComponent();
            this->Resize += gcnew EventHandler(this, &PersonnelPanel::OnResize);
        }

    protected:
        ~PersonnelPanel() {
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
            this->AutoSize = true;
            this->Dock = DockStyle::Fill;

            Title = (gcnew Label());
            Title->Text = L"Gestion du personnel";
            Title->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 16, FontStyle::Bold);
            Title->AutoSize = true;
            Title->Location = Point(-20, 20);
            Title->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

            BackButton = (gcnew Button());
            BackButton->Text = L"Retour";
            BackButton->Size = Drawing::Size(75, 23);
            BackButton->Location = Point(20, this->Height - 50); 
            BackButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom | AnchorStyles::Left);
            BackButton->Click += gcnew EventHandler(this, &PersonnelPanel::OnBackButtonClicked);

            NewButton = (gcnew Button());
            NewButton->Text = L"Nouveau Personnel";
            NewButton->Size = Drawing::Size(150, 50);
            NewButton->Click += gcnew EventHandler(this, &PersonnelPanel::OnNewButtonClicked);

            ExistButton = (gcnew Button());
            ExistButton->Text = L"Personnel existant";
            ExistButton->Size = Drawing::Size(150, 50);
            ExistButton->Click += gcnew EventHandler(this, &PersonnelPanel::OnExistingStaffButtonClicked);

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
            NewStaffButtonClicked(sender, e);
        }

        void OnExistingStaffButtonClicked(Object^ sender, EventArgs^ e) {
            ExistingStaffButtonClicked(sender, e);
        }
    };
}
