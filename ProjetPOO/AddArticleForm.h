#pragma once
#include "DatabaseManager.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Drawing;

namespace Corbeille5 {

    public ref class AddArticleForm : public Form {
    public:
        AddArticleForm() {
            InitializeComponent();
            LoadArticles();
        }

        property Dictionary<int, int>^ SelectedArticlesQuantities {
            Dictionary<int, int>^ get() {
                return selectedArticlesQuantities;
            }
        }

    private:
        DataGridView^ dataGridViewArticles;
        Button^ buttonValidate;
        Button^ buttonCancel;
        Dictionary<int, int>^ selectedArticlesQuantities;

        void InitializeComponent() {
            this->dataGridViewArticles = (gcnew System::Windows::Forms::DataGridView());
            this->buttonValidate = (gcnew System::Windows::Forms::Button());
            this->buttonCancel = (gcnew System::Windows::Forms::Button());
            this->selectedArticlesQuantities = gcnew Dictionary<int, int>();

            // Configuration du dataGridViewArticles
            this->dataGridViewArticles->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridViewArticles->Columns->Add("Article", "Article");
            this->dataGridViewArticles->Columns->Add("Quantité", "Quantité");
            this->dataGridViewArticles->Dock = DockStyle::Fill;

            // Ajout des boutons + et -
            AddPlusMinusButtons();

            // Configuration des boutons 'Valider' et 'Annuler'
            ConfigureButtons();

            // AddArticleForm
            ConfigureForm();
        }

        void AddPlusMinusButtons() {
            DataGridViewButtonColumn^ buttonColumnPlus = gcnew DataGridViewButtonColumn();
            DataGridViewButtonColumn^ buttonColumnMinus = gcnew DataGridViewButtonColumn();

            buttonColumnPlus->Name = "Plus";
            buttonColumnPlus->HeaderText = "";
            buttonColumnPlus->Text = "+";
            buttonColumnPlus->UseColumnTextForButtonValue = true;

            buttonColumnMinus->Name = "Minus";
            buttonColumnMinus->HeaderText = "";
            buttonColumnMinus->Text = "-";
            buttonColumnMinus->UseColumnTextForButtonValue = true;

            dataGridViewArticles->CellContentClick += gcnew DataGridViewCellEventHandler(this, &AddArticleForm::dataGridViewArticles_CellClick);

            this->dataGridViewArticles->Columns->Add(buttonColumnPlus);
            this->dataGridViewArticles->Columns->Add(buttonColumnMinus);
        }

        void ConfigureButtons() {
            // buttonValidate
            this->buttonValidate->Text = L"Valider";
            this->buttonValidate->UseVisualStyleBackColor = true;
            this->buttonValidate->Click += gcnew System::EventHandler(this, &AddArticleForm::OnValidateButtonClick);

            // buttonCancel
            this->buttonCancel->Text = L"Annuler";
            this->buttonCancel->UseVisualStyleBackColor = true;
            this->buttonCancel->Click += gcnew System::EventHandler(this, &AddArticleForm::OnCancelButtonClick);

            // Positionnement des boutons
            this->buttonValidate->Size = System::Drawing::Size(94, 23);
            this->buttonCancel->Size = System::Drawing::Size(94, 23);

            // Ajout des boutons à la fenêtre
            this->Controls->Add(this->buttonValidate);
            this->Controls->Add(this->buttonCancel);
        }

        void ConfigureForm() {
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->ClientSize = System::Drawing::Size(568, 522);
            this->Controls->Add(this->dataGridViewArticles);
            this->Name = L"AddArticleForm";
            this->Text = L"Ajouter des articles";

            // Assurez-vous que les boutons 'Valider' et 'Annuler' sont visibles et correctement placés
            this->Load += gcnew System::EventHandler(this, &AddArticleForm::OnLoad);
        }

        void OnLoad(Object^ sender, EventArgs^ e) {
            // Positionne les boutons 'Valider' et 'Annuler' en bas à droite et à gauche respectivement
            int spacing = 10;
            this->buttonValidate->Location = Point(this->ClientSize.Width - this->buttonValidate->Width - spacing, this->ClientSize.Height - this->buttonValidate->Height - spacing);
            this->buttonCancel->Location = Point(spacing, this->ClientSize.Height - this->buttonCancel->Height - spacing);
        }

        void LoadArticles() {
            DatabaseManager^ dbManager = gcnew DatabaseManager();
            Dictionary<int, String^>^ articles = dbManager->GetAllArticles();

            for each (KeyValuePair<int, String^> article in articles) {
                DataGridViewRow^ row = (gcnew DataGridViewRow());
                row->CreateCells(this->dataGridViewArticles);
                row->Cells[0]->Value = article.Value;
                row->Cells[1]->Value = "0"; // Quantité initiale
                row->Tag = article.Key;
                this->dataGridViewArticles->Rows->Add(row);
            }
        }

        void dataGridViewArticles_CellClick(Object^ sender, DataGridViewCellEventArgs^ e) {
            int articleId = safe_cast<int>(dataGridViewArticles->Rows[e->RowIndex]->Tag);
            if (e->ColumnIndex == 2) { // Bouton '+'
                IncrementArticleQuantity(articleId);
            }
            else if (e->ColumnIndex == 3) { // Bouton '-'
                DecrementArticleQuantity(articleId);
            }
        }

        void IncrementArticleQuantity(int articleId) {
            for each (DataGridViewRow ^ row in this->dataGridViewArticles->Rows) {
                if (safe_cast<int>(row->Tag) == articleId) {
                    int quantity = Convert::ToInt32(row->Cells[1]->Value) + 1;
                    row->Cells[1]->Value = quantity;
                    selectedArticlesQuantities[articleId] = quantity;
                    break;
                }
            }
        }

        void DecrementArticleQuantity(int articleId) {
            for each (DataGridViewRow ^ row in this->dataGridViewArticles->Rows) {
                if (safe_cast<int>(row->Tag) == articleId) {
                    int quantity = Convert::ToInt32(row->Cells[1]->Value) - 1;
                    if (quantity < 0) quantity = 0;
                    row->Cells[1]->Value = quantity;
                    selectedArticlesQuantities[articleId] = quantity;
                    break;
                }
            }
        }

        void OnValidateButtonClick(Object^ sender, EventArgs^ e) {
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }

        void OnCancelButtonClick(Object^ sender, EventArgs^ e) {
            this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->Close();
        }
    };
}
