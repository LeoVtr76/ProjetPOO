#pragma once
#include "DatabaseManager.h"
#include "InfopersonnelForm.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

    public ref class NewClientPanel : public UserControl {
    public:
        event EventHandler^ BackButtonClicked;
        event EventHandler^ ValidateButtonClicked;

        NewClientPanel() {
            InitializeComponent();
            FillCountryComboBox();
            this->Resize += gcnew EventHandler(this, &NewClientPanel::OnResize);
        }

    protected:
        ~NewClientPanel() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        Label^ labelFirstName;
        TextBox^ textBoxFirstName;
        Label^ labelLastName;
        TextBox^ textBoxLastName;
        Label^ labelBirthDate;
        TextBox^ textBoxBirthDate;
        Label^ labelCountry;
        ComboBox^ comboBoxCountry;
        Label^ labelPostalCode;
        ComboBox^ comboBoxPostalCode;
        Label^ labelCity;
        ComboBox^ comboBoxCity;
        Label^ labelAddress;
        TextBox^ textBoxAddress;
        Button^ buttonBack;
        Button^ buttonValidate;

        void InitializeComponent() {
            this->components = gcnew System::ComponentModel::Container();
            this->AutoSize = true;
            this->Dock = DockStyle::Fill;
            this->labelFirstName = CreateLabel(L"Prénom");
            this->textBoxFirstName = CreateTextBox();
            this->labelLastName = CreateLabel(L"Nom");
            this->textBoxLastName = CreateTextBox();
            this->labelBirthDate = CreateLabel(L"Date de naissance");
            this->textBoxBirthDate = CreateTextBox();
            this->labelCountry = CreateLabel(L"Pays");
            this->comboBoxCountry = CreateComboBox();
            this->comboBoxCountry->SelectedIndexChanged += gcnew EventHandler(this, &NewClientPanel::CountrySelectionChanged);
            this->labelPostalCode = CreateLabel(L"Code Postal");
            this->comboBoxPostalCode = CreateComboBox();
            this->comboBoxPostalCode->SelectedIndexChanged += gcnew EventHandler(this, &NewClientPanel::PostalCodeSelectionChanged);
            this->labelCity = CreateLabel(L"Ville");
            this->comboBoxCity = CreateComboBox();
            this->labelAddress = CreateLabel(L"Adresse");
            this->textBoxAddress = CreateTextBox();
            this->buttonBack = CreateButton(L"Retour");
            this->buttonBack->Click += gcnew EventHandler(this, &NewClientPanel::OnBackButtonClicked);
            this->buttonValidate = CreateButton(L"Valider");
            this->buttonValidate->Click += gcnew EventHandler(this, &NewClientPanel::OnValidateButtonClicked);

            AddControlsToPanel();

            PerformLayoutControls();
        }
        void FillCountryComboBox() {
            DatabaseManager^ dbManager = gcnew DatabaseManager();
            List<String^>^ countryList = dbManager->ShowCountry();

            this->comboBoxCountry->Items->Clear();
            for each (String ^ countryName in countryList) {
                this->comboBoxCountry->Items->Add(countryName);
            }
        }
        void FillCpComboBox() {
            String^ selectedCountry = this->comboBoxCountry->Text;
            DatabaseManager^ dbManager = gcnew DatabaseManager();
            List<String^>^ postalCodeList = dbManager->GetPostalCodes(selectedCountry);

            this->comboBoxPostalCode->Items->Clear();
            for each (String ^ postalCode in postalCodeList) {
                this->comboBoxPostalCode->Items->Add(postalCode);
            }
        }
        void FillCityComboBox() {
            String^ selectedCp = this->comboBoxPostalCode->Text;
            DatabaseManager^ dbManager = gcnew DatabaseManager();
            List<String^>^ cityList = dbManager->GetCities(selectedCp);

            this->comboBoxCity->Items->Clear();
            for each (String ^ city in cityList) {
                this->comboBoxCity->Items->Add(city);
            }
        }

        Label^ CreateLabel(String^ text) {
            Label^ label = gcnew Label();
            label->Text = text;
            label->AutoSize = true;
            label->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
            return label;
        }

        TextBox^ CreateTextBox() {
            TextBox^ textBox = gcnew TextBox();
            textBox->Width = 200;
            return textBox;
        }

        ComboBox^ CreateComboBox() {
            ComboBox^ comboBox = gcnew ComboBox();
            comboBox->Width = 200;
            comboBox->DropDownStyle = ComboBoxStyle::DropDown;
            comboBox->AutoCompleteMode = AutoCompleteMode::SuggestAppend;
            comboBox->AutoCompleteSource = AutoCompleteSource::ListItems;
            return comboBox;
        }

        Button^ CreateButton(String^ text) {
            Button^ button = gcnew Button();
            button->Text = text;
            button->AutoSize = true;
            return button;
        }
        void ClearFields() {

            this->textBoxFirstName->Clear();
            this->textBoxLastName->Clear();
            this->comboBoxCountry->SelectedIndex = -1;
            this->comboBoxPostalCode->SelectedIndex = -1;
            this->comboBoxCity->SelectedIndex = -1;
            this->textBoxAddress->Clear();
            this->textBoxBirthDate->Clear();
        }
        void AddControlsToPanel() {

            this->Controls->Add(labelFirstName);
            this->Controls->Add(textBoxFirstName);
            this->Controls->Add(labelLastName);
            this->Controls->Add(textBoxLastName);
            this->Controls->Add(labelBirthDate);
            this->Controls->Add(textBoxBirthDate);
            this->Controls->Add(labelCountry);
            this->Controls->Add(comboBoxCountry);
            this->Controls->Add(labelPostalCode);
            this->Controls->Add(comboBoxPostalCode);
            this->Controls->Add(labelCity);
            this->Controls->Add(comboBoxCity);
            this->Controls->Add(labelAddress);
            this->Controls->Add(textBoxAddress);
            this->Controls->Add(buttonBack);
            this->Controls->Add(buttonValidate);
        }

        void OnResize(Object^ sender, EventArgs^ e) {
            PerformLayoutControls();
        }

        void PerformLayoutControls() {
            int margin = 10;
            int labelHeight = 20;
            int textBoxHeight = 20;
            int verticalSpace = 30;

            int leftColumnWidth = this->Width / 2 - 2 * margin;
            int rightColumnWidth = this->Width / 2 - 2 * margin;

            labelFirstName->Location = Point(margin, margin);
            textBoxFirstName->Location = Point(margin, labelFirstName->Bottom + margin);
            textBoxFirstName->Width = leftColumnWidth;

            labelLastName->Location = Point(margin, textBoxFirstName->Bottom + margin);
            textBoxLastName->Location = Point(margin, labelLastName->Bottom + margin);
            textBoxLastName->Width = leftColumnWidth;

            labelBirthDate->Location = Point(margin, textBoxLastName->Bottom + margin);
            textBoxBirthDate->Location = Point(margin, labelBirthDate->Bottom + margin);
            textBoxBirthDate->Width = leftColumnWidth;

            labelCountry->Location = Point(this->Width / 2 + margin, margin);
            comboBoxCountry->Location = Point(this->Width / 2 + margin, labelCountry->Bottom + margin);
            comboBoxCountry->Width = rightColumnWidth;

            labelPostalCode->Location = Point(this->Width / 2 + margin, comboBoxCountry->Bottom + margin);
            comboBoxPostalCode->Location = Point(this->Width / 2 + margin, labelPostalCode->Bottom + margin);
            comboBoxPostalCode->Width = rightColumnWidth;

            labelCity->Location = Point(this->Width / 2 + margin, comboBoxPostalCode->Bottom + margin);
            comboBoxCity->Location = Point(this->Width / 2 + margin, labelCity->Bottom + margin);
            comboBoxCity->Width = rightColumnWidth;

            labelAddress->Location = Point(this->Width / 2 + margin, comboBoxCity->Bottom + margin);
            textBoxAddress->Location = Point(this->Width / 2 + margin, labelAddress->Bottom + margin);
            textBoxAddress->Width = rightColumnWidth;

            buttonBack->Location = Point(margin, this->Height - buttonBack->Height - margin);
            buttonValidate->Location = Point(this->Width - buttonValidate->Width - margin, this->Height - buttonValidate->Height - margin);
        }
        void comboBoxCountry_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
            String^ inputCountry = this->comboBoxCountry->Text;

            if (this->comboBoxCountry->FindStringExact(inputCountry) == -1) {
                DatabaseManager^ dbManager = gcnew DatabaseManager();
                dbManager->AddCountry(inputCountry);
                FillCountryComboBox();
            }
        }
        void CountrySelectionChanged(Object^ sender, EventArgs^ e) {
            FillCpComboBox();
        }
        void PostalCodeSelectionChanged(Object^ sender, EventArgs^ e) {
            String^ selectedPostalCode = this->comboBoxPostalCode->Text;
            FillCityComboBox();
        }
        void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
            BackButtonClicked(sender, e);
        }
        void OnValidateButtonClicked(Object^ sender, EventArgs^ e) {
            DatabaseManager^ dbManager = gcnew DatabaseManager();

            String^ country = comboBoxCountry->Text;
            String^ postalCode = comboBoxPostalCode->Text;
            String^ city = comboBoxCity->Text;

            if (!dbManager->CheckCountry(country)) {
                dbManager->AddCountry(country);
            }

            if (!dbManager->CheckCity(country, city)) {
                dbManager->AddCity(city, postalCode, country);
            }

            String^ address = textBoxAddress->Text;
            array<String^>^ addressParts = address->Split(' ');
            String^ streetNumber = addressParts[0];
            String^ streetName = String::Join(" ", addressParts, 1, addressParts->Length - 1);
            int addressId = dbManager->AddAddress(streetNumber, streetName, city);

            String^ firstName = textBoxFirstName->Text;
            String^ lastName = textBoxLastName->Text;
            String^ birthDate = textBoxBirthDate->Text;

            InfopersonnelForm^ messageForm = gcnew InfopersonnelForm();
            if (dbManager->ClientExists(firstName, lastName, birthDate)) {
                messageForm->SetMessage("Le client existe déjà.");
            }
            else {
                dbManager->AddClient(firstName, lastName, birthDate, addressId);
                messageForm->SetMessage("Le client à été ajouté avec succès !");
                ClearFields();
                FillCountryComboBox();
            }
            messageForm->ShowDialog();
        }
    };
}
