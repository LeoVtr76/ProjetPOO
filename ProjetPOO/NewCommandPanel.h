#pragma once
#include "DatabaseManager.h"
#include "InfopersonnelForm.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

    public ref class NewCommandPanel : public UserControl {
    public:
        event EventHandler^ BackButtonClicked;
        event EventHandler^ ValidateButtonClicked;

        NewCommandPanel() {
            InitializeComponent();
            FillCountryComboBox();
            FillClientComboBox();
            this->Resize += gcnew EventHandler(this, &NewCommandPanel::OnResize);
        }

    protected:
        ~NewCommandPanel() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        // Left side controls
        Label^ labelRef;
        TextBox^ textBoxRef;
        Label^ labelPaiementDate;
        TextBox^ textBoxPaiementDate;
        Label^ labelReglementDate;
        TextBox^ textBoxReglementDate;
        Label^ labelDeliveryDate;
        TextBox^ textBoxDeliveryDate;
        Label^ labelMontantHT;
        TextBox^ textBoxMontantHT;
        Label^ labelMontantTVA;
        TextBox^ textBoxMontantTVA;
        Label^ labelArticles;
        ComboBox^ comboBoxArticles;

        // Right side controls
        Label^ labelClient;
        ComboBox^ comboBoxClient;
        CheckBox^ checkBoxIsSameAddress;
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
            this->labelRef = CreateLabel(L"Réference");
            this->textBoxRef = CreateTextBox();
            this->labelPaiementDate = CreateLabel(L"Date de paiement");
            this->textBoxPaiementDate = CreateTextBox();
            this->labelReglementDate = CreateLabel(L"Date de règlement");
            this->textBoxReglementDate = CreateTextBox();
            this->labelDeliveryDate = CreateLabel(L"date de livraison");
            this->textBoxDeliveryDate = CreateTextBox();
            this->labelMontantHT = CreateLabel(L"Montant HT");
            this->textBoxMontantHT = CreateTextBox();
            this->labelMontantTVA = CreateLabel(L"Montant TVA");
            this->textBoxMontantTVA = CreateTextBox();
            this->labelArticles = CreateLabel(L"Articles");
            this->comboBoxArticles = CreateComboBox();

            // Right side controls initialization
            this->labelClient = CreateLabel(L"Client");
            this->comboBoxClient = CreateComboBox();
            this->comboBoxClient->DropDownStyle = ComboBoxStyle::DropDownList;
            this->checkBoxIsSameAddress = CreateCheckBox(L"Adresse différente de celle du client");
            this->checkBoxIsSameAddress->CheckedChanged += gcnew System::EventHandler(this, &NewCommandPanel::OnCheckBoxChanged);
            this->labelCountry = CreateLabel(L"Pays");
            this->comboBoxCountry = CreateComboBox();
            this->comboBoxCountry->SelectedIndexChanged += gcnew EventHandler(this, &NewCommandPanel::CountrySelectionChanged);
            this->labelPostalCode = CreateLabel(L"Code Postal");
            this->comboBoxPostalCode = CreateComboBox();
            this->comboBoxPostalCode->SelectedIndexChanged += gcnew EventHandler(this, &NewCommandPanel::PostalCodeSelectionChanged);
            this->labelCity = CreateLabel(L"Ville");
            this->comboBoxCity = CreateComboBox();
            this->labelAddress = CreateLabel(L"Adresse");
            this->textBoxAddress = CreateTextBox();
            this->labelCountry->Visible = false;
            this->comboBoxCountry->Visible = false;
            this->labelPostalCode->Visible = false;
            this->comboBoxPostalCode->Visible = false;
            this->labelCity->Visible = false;
            this->comboBoxCity->Visible = false;
            this->labelAddress->Visible = false;
            this->textBoxAddress->Visible = false;

            // Bottom controls initialization
            this->buttonBack = CreateButton(L"Retour");
            this->buttonBack->Click += gcnew EventHandler(this, &NewCommandPanel::OnBackButtonClicked);
            this->buttonValidate = CreateButton(L"Valider");
            this->buttonValidate->Click += gcnew EventHandler(this, &NewCommandPanel::OnValidateButtonClicked);

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
        void FillClientComboBox() {
            DatabaseManager^ dbManager = gcnew DatabaseManager();
            Dictionary<String^, int>^ clientDict = dbManager->GetClients();

            this->comboBoxClient->Items->Clear();
            for each (KeyValuePair<String^, int> client in clientDict) {
                this->comboBoxClient->Items->Add(client.Key);
            }
            this->comboBoxClient->Tag = clientDict;
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
        CheckBox^ CreateCheckBox(String^ text) {
            CheckBox^ checkBox = gcnew CheckBox();
            checkBox->AutoSize = true;
            checkBox->TabIndex = 0;
            checkBox->Text = text;
            checkBox->UseVisualStyleBackColor = true;
            return checkBox;

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
            // Clear all TextBoxes, reset ComboBoxes, etc.
            this->textBoxRef->Clear();
            this->textBoxPaiementDate->Clear();
            this->textBoxReglementDate->Clear();
            this->textBoxDeliveryDate->Clear();
            this->textBoxMontantHT->Clear();
            this->textBoxMontantTVA->Clear();
            this->comboBoxArticles->SelectedIndex = -1;

            this->comboBoxClient->SelectedIndex = -1;
            //this->checkBoxIsSameAddress->
            this->comboBoxCountry->SelectedIndex = -1;
            this->comboBoxPostalCode->SelectedIndex = -1;
            this->comboBoxCity->SelectedIndex = -1;
            this->textBoxAddress->Clear();
        }
        // Adding controls to UserControl
        void AddControlsToPanel() {
            // Left side controls
            this->Controls->Add(labelRef);
            this->Controls->Add(textBoxRef);
            this->Controls->Add(labelPaiementDate);
            this->Controls->Add(textBoxPaiementDate);
            this->Controls->Add(labelReglementDate);
            this->Controls->Add(textBoxReglementDate);
            this->Controls->Add(labelDeliveryDate);
            this->Controls->Add(textBoxDeliveryDate);
            this->Controls->Add(labelMontantHT);
            this->Controls->Add(textBoxMontantHT);
            this->Controls->Add(labelMontantTVA);
            this->Controls->Add(textBoxMontantTVA);
            this->Controls->Add(labelArticles);
            this->Controls->Add(comboBoxArticles);

            // Right side controls
            this->Controls->Add(labelClient);
            this->Controls->Add(comboBoxClient);
            this->Controls->Add(checkBoxIsSameAddress);
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
            labelRef->Location = Point(margin, margin);
            textBoxRef->Location = Point(margin, labelRef->Bottom + margin);
            textBoxRef->Width = leftColumnWidth;

            labelPaiementDate->Location = Point(margin, textBoxRef->Bottom + margin);
            textBoxPaiementDate->Location = Point(margin, labelPaiementDate->Bottom + margin);
            textBoxPaiementDate->Width = leftColumnWidth;

            labelReglementDate->Location = Point(margin, textBoxPaiementDate->Bottom + margin);
            textBoxReglementDate->Location = Point(margin, labelReglementDate->Bottom + margin);
            textBoxReglementDate->Width = leftColumnWidth;

            labelDeliveryDate->Location = Point(margin, textBoxReglementDate->Bottom + margin);
            textBoxDeliveryDate->Location = Point(margin, labelDeliveryDate->Bottom + margin);
            textBoxDeliveryDate->Width = leftColumnWidth;

            labelMontantHT->Location = Point(margin, textBoxDeliveryDate->Bottom + margin);
            textBoxMontantHT->Location = Point(margin, labelMontantHT->Bottom + margin);
            textBoxMontantHT->Width = leftColumnWidth;

            labelMontantTVA->Location = Point(margin, textBoxMontantHT->Bottom + margin);
            textBoxMontantTVA->Location = Point(margin, labelMontantTVA->Bottom + margin);
            textBoxMontantTVA->Width = leftColumnWidth;

            labelArticles->Location = Point(margin, textBoxMontantTVA->Bottom + margin);
            comboBoxArticles->Location = Point(margin, labelArticles->Bottom + margin);
            comboBoxArticles->Width = leftColumnWidth;

            // Position right column controls
            labelClient->Location = Point(this->Width / 2 + margin, margin);
            comboBoxClient->Location = Point(this->Width / 2 + margin, labelClient->Bottom + margin);
            comboBoxClient->Width = rightColumnWidth;

            checkBoxIsSameAddress->Location = Point(this->Width / 2 + margin, comboBoxClient->Bottom + margin);
            checkBoxIsSameAddress->Width = rightColumnWidth;

            labelCountry->Location = Point(this->Width / 2 + margin, checkBoxIsSameAddress->Bottom + margin);
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
        void OnCheckBoxChanged(Object^ sender, EventArgs^ e) {
            bool isAddressDifferent = this->checkBoxIsSameAddress->Checked;

            // Activer ou désactiver les contrôles d'adresse
            this->labelCountry->Visible = isAddressDifferent;
            this->comboBoxCountry->Visible = isAddressDifferent;
            this->labelPostalCode->Visible = isAddressDifferent;
            this->comboBoxPostalCode->Visible = isAddressDifferent;
            this->labelCity->Visible = isAddressDifferent;
            this->comboBoxCity->Visible = isAddressDifferent;
            this->labelAddress->Visible = isAddressDifferent;
            this->textBoxAddress->Visible = isAddressDifferent;

            if (!isAddressDifferent) {
                this->comboBoxCountry->SelectedIndex = -1;
                this->comboBoxPostalCode->SelectedIndex = -1;
                this->comboBoxCity->SelectedIndex = -1;
                this->textBoxAddress->Clear();
            }
        }
        void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
            BackButtonClicked(sender, e);
        }
        void OnValidateButtonClicked(Object^ sender, EventArgs^ e) {
            DatabaseManager^ dbManager = gcnew DatabaseManager();
            int clientId;
            String^ selectedClientName = (String^)comboBoxClient->SelectedItem;
            Dictionary<String^, int>^ clientDict = (Dictionary<String^, int>^)comboBoxClient->Tag;

            if (clientDict->ContainsKey(selectedClientName)) {
                clientId = clientDict[selectedClientName];
            }

            // Vérification des valeurs des ComboBox
            String^ country = comboBoxCountry->Text;
            String^ postalCode = comboBoxPostalCode->Text;
            String^ city = comboBoxCity->Text;
            int addressId;
            if (this->checkBoxIsSameAddress->Checked) {
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
                addressId = dbManager->AddAddress(streetNumber, streetName, city);
            }
            else {
                addressId = dbManager->GetClientAddressById(clientId);
            }
            String^ ref = textBoxRef->Text;
            String^ datePaie = textBoxPaiementDate->Text;
            String^ dateReg = textBoxReglementDate->Text;
            String^ dateLiv = textBoxDeliveryDate->Text;
            String^ amountHT = textBoxMontantHT->Text;
            String^ amountTVA = textBoxMontantTVA->Text;
            
            InfopersonnelForm^ messageForm = gcnew InfopersonnelForm();
            if (dbManager->CommandExist(ref)) {
                messageForm->SetMessage("La commande existe déjà.");
            }
            else {
                dbManager->AddCommand(ref, datePaie, dateReg, dateLiv, amountHT, amountTVA, clientId, addressId);
                messageForm->SetMessage("La commande à été ajouté avec succès !");
                ClearFields();
                FillCountryComboBox();
                FillClientComboBox();
            }
            messageForm->ShowDialog();
        }
    };
}
