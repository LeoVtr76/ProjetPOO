#pragma once
#include "DatabaseManager.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

    public ref class NewStaffPanel : public UserControl {
    public:
        event EventHandler^ BackButtonClicked;
        event EventHandler^ ValidateButtonClicked;

        NewStaffPanel() {
            InitializeComponent();
            FillCountryComboBox();
            this->Resize += gcnew EventHandler(this, &NewStaffPanel::OnResize);
        }

    protected:
        ~NewStaffPanel() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        // Left side controls
        Label^ labelFirstName;
        TextBox^ textBoxFirstName;
        Label^ labelLastName;
        TextBox^ textBoxLastName;
        Label^ labelHireDate;
        TextBox^ textBoxHireDate;
        Label^ labelHierarchyLevel;
        TextBox^ textBoxHierarchyLevel;

        // Right side controls
        Label^ labelManager;
        ComboBox^ comboBoxManager;
        Label^ labelCountry;
        ComboBox^ comboBoxCountry;
        Label^ labelPostalCode;
        ComboBox^ comboBoxPostalCode;
        Label^ labelCity;
        ComboBox^ comboBoxCity;
        Label^ labelAddress;
        TextBox^ textBoxAddress;

        // Bottom controls
        Button^ buttonBack;
        Button^ buttonValidate;

        void InitializeComponent() {
            this->components = gcnew System::ComponentModel::Container();
            this->AutoSize = true;
            this->Dock = DockStyle::Fill;

            // Left side controls initialization
            this->labelFirstName = CreateLabel(L"Prénom");
            this->textBoxFirstName = CreateTextBox();
            this->labelLastName = CreateLabel(L"Nom");
            this->textBoxLastName = CreateTextBox();
            this->labelHireDate = CreateLabel(L"Date d'Embauche");
            this->textBoxHireDate = CreateTextBox();
            this->labelHierarchyLevel = CreateLabel(L"Niveau Hiérarchique");
            this->textBoxHierarchyLevel = CreateTextBox();

            // Right side controls initialization
            this->labelManager = CreateLabel(L"Responsable");
            this->comboBoxManager = CreateComboBox();
            this->comboBoxManager->DropDownStyle = ComboBoxStyle::DropDownList;
            this->labelCountry = CreateLabel(L"Pays");
            this->comboBoxCountry = CreateComboBox();
            this->comboBoxCountry->SelectedIndexChanged += gcnew EventHandler(this, &NewStaffPanel::CountrySelectionChanged);
            this->labelPostalCode = CreateLabel(L"Code Postal");
            this->comboBoxPostalCode = CreateComboBox();
            this->comboBoxPostalCode->SelectedIndexChanged += gcnew EventHandler(this, &NewStaffPanel::PostalCodeSelectionChanged);
            this->labelCity = CreateLabel(L"Ville");
            this->comboBoxCity = CreateComboBox();
            this->labelAddress = CreateLabel(L"Adresse");
            this->textBoxAddress = CreateTextBox();

            // Bottom controls initialization
            this->buttonBack = CreateButton(L"Retour");
            this->buttonValidate = CreateButton(L"Valider");
            this->buttonValidate->Click += gcnew EventHandler(this, &NewStaffPanel::OnValidateButtonClicked);

            // Add controls to UserControl
            AddControlsToPanel();

            // Initial layout
            PerformLayoutControls();
        }
        void FillCountryComboBox() {
            DatabaseManager^ dbManager = gcnew DatabaseManager();
            List<String^>^ countryList = dbManager->ShowCountry();

            // Nettoyer et remplir le ComboBox
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
        // Helpers for creating controls
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

        // Adding controls to UserControl
        void AddControlsToPanel() {
            // Left side controls
            this->Controls->Add(labelFirstName);
            this->Controls->Add(textBoxFirstName);
            this->Controls->Add(labelLastName);
            this->Controls->Add(textBoxLastName);
            this->Controls->Add(labelHireDate);
            this->Controls->Add(textBoxHireDate);
            this->Controls->Add(labelHierarchyLevel);
            this->Controls->Add(textBoxHierarchyLevel);

            // Right side controls
            this->Controls->Add(labelManager);
            this->Controls->Add(comboBoxManager);
            this->Controls->Add(labelCountry);
            this->Controls->Add(comboBoxCountry);
            this->Controls->Add(labelPostalCode);
            this->Controls->Add(comboBoxPostalCode);
            this->Controls->Add(labelCity);
            this->Controls->Add(comboBoxCity);
            this->Controls->Add(labelAddress);
            this->Controls->Add(textBoxAddress);

            // Bottom controls
            this->Controls->Add(buttonBack);
            this->Controls->Add(buttonValidate);
        }

        // Resize event handler
        void OnResize(Object^ sender, EventArgs^ e) {
            PerformLayoutControls();
        }

        // Layout controls on the panel
        void PerformLayoutControls() {
            int margin = 10;
            int labelHeight = 20;
            int textBoxHeight = 20;
            int verticalSpace = 30;

            // Calculate column widths
            int leftColumnWidth = this->Width / 2 - 2 * margin;
            int rightColumnWidth = this->Width / 2 - 2 * margin;

            // Position left column controls
            labelFirstName->Location = Point(margin, margin);
            textBoxFirstName->Location = Point(margin, labelFirstName->Bottom + margin);
            textBoxFirstName->Width = leftColumnWidth;

            labelLastName->Location = Point(margin, textBoxFirstName->Bottom + margin);
            textBoxLastName->Location = Point(margin, labelLastName->Bottom + margin);
            textBoxLastName->Width = leftColumnWidth;

            labelHireDate->Location = Point(margin, textBoxLastName->Bottom + margin);
            textBoxHireDate->Location = Point(margin, labelHireDate->Bottom + margin);
            textBoxHireDate->Width = leftColumnWidth;

            labelHierarchyLevel->Location = Point(margin, textBoxHireDate->Bottom + margin);
            textBoxHierarchyLevel->Location = Point(margin, labelHierarchyLevel->Bottom + margin);
            textBoxHierarchyLevel->Width = leftColumnWidth;

            // Position right column controls
            labelManager->Location = Point(this->Width / 2 + margin, margin);
            comboBoxManager->Location = Point(this->Width / 2 + margin, labelManager->Bottom + margin);
            comboBoxManager->Width = rightColumnWidth;

            labelCountry->Location = Point(this->Width / 2 + margin, comboBoxManager->Bottom + margin);
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

            // Position bottom controls
            buttonBack->Location = Point(margin, this->Height - buttonBack->Height - margin);
            buttonValidate->Location = Point(this->Width - buttonValidate->Width - margin, this->Height - buttonValidate->Height - margin);
        }
        void comboBoxCountry_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
            String^ inputCountry = this->comboBoxCountry->Text;

            // Vérifier si le pays saisi est déjà dans la liste
            if (this->comboBoxCountry->FindStringExact(inputCountry) == -1) {
                // La valeur saisie n'est pas dans la liste
                // Ajouter le nouveau pays à la base de données
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
        // Event handlers
        void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
            BackButtonClicked(sender, e);
        }

        void OnValidateButtonClicked(Object^ sender, EventArgs^ e) {
            DatabaseManager^ dbManager = gcnew DatabaseManager();

            // Vérification des valeurs des ComboBox
            String^ country = comboBoxCountry->Text;
            String^ postalCode = comboBoxPostalCode->Text;
            String^ city = comboBoxCity->Text;

            // Ajouter le pays s'il n'existe pas
            if (!dbManager->CheckCountry(country)) {
                dbManager->AddCountry(country);
            }

            // Ajouter la ville et son code postal s'ils n'existent pas
            if (!dbManager->CheckCity(country, city)) {
                dbManager->AddCity(city, postalCode, country);
            }

            // Traitement et création de l'adresse
            String^ address = textBoxAddress->Text;
            array<String^>^ addressParts = address->Split(' ');
            String^ streetNumber = addressParts[0];
            String^ streetName = String::Join(" ", addressParts, 1, addressParts->Length - 1);
            int addressId = dbManager->AddAddress(streetNumber, streetName, city);

            // Création du personnel
            String^ firstName = textBoxFirstName->Text;
            String^ lastName = textBoxLastName->Text;
            String^ hierarchyLevel = textBoxHierarchyLevel->Text;
            String^ hireDate = textBoxHireDate->Text;
            Object^ managerId;
            if (comboBoxManager->SelectedIndex >= 0) {
                managerId = comboBoxManager->SelectedItem; 
            }
            else {
                managerId = DBNull::Value;
            }
            dbManager->AddPersonnel(firstName, lastName,hierarchyLevel,hireDate,managerId, addressId);
        }
    };
}
