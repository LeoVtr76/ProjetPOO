#pragma once
#include "MainPanel.h"
#include "PersonnelPanel.h"
#include "CommandePanel.h"
#include "ClientPanel.h"
#include "StockPanel.h"
#include "NouvelArticlePanel.h"
#include "CommandeExistantePanel.h"

// Incluez ici les autres panels que vous avez.

namespace Corbeille5 {

    using namespace System::Windows::Forms;

    public ref class MyForm : public Form {
    public:
        MyForm() {
            InitializeComponent();
            //MainPanel event
            mainPanel->PersonnelClicked += gcnew System::EventHandler(this, &MyForm::ShowPersonnelPanel);
            mainPanel->StockClicked += gcnew System::EventHandler(this, &MyForm::ShowStockPanel);
            mainPanel->CommandClicked += gcnew System::EventHandler(this, &MyForm::ShowCommandPanel);
            mainPanel->ClientClicked += gcnew System::EventHandler(this, &MyForm::ShowClientPanel);

            this->MinimumSize = System::Drawing::Size(800, 600);
        }

    protected:
        ~MyForm() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        MainPanel^ mainPanel;
        StockPanel^ stockPanel;

        void InitializeComponent() {
            this->mainPanel = (gcnew MainPanel());  
            this->Controls->Add(this->mainPanel);
            this->mainPanel->Dock = DockStyle::Fill;
            this->Text = L"MyForm";
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(800, 600); // Taille de la fen�tre
        }

        void ShowPersonnelPanel(Object^ sender, EventArgs^ e) {
            PersonnelPanel^ personnelPanel = gcnew PersonnelPanel();
            personnelPanel->BackButtonClicked += gcnew System::EventHandler(this, &MyForm::ShowMainPanel);
            this->Controls->Clear();
            this->Controls->Add(personnelPanel);
            personnelPanel->Dock = DockStyle::Fill;
        }
        void ShowStockPanel(Object^ sender, EventArgs^ e) {
            StockPanel^ stockPanel = gcnew StockPanel();
            stockPanel->BackButtonClicked += gcnew System::EventHandler(this, &MyForm::ShowMainPanel);
            stockPanel->NewArticleButtonClicked+= gcnew EventHandler(this, &MyForm::ShowNewArticlePanel);
            this->Controls->Clear();
            this->Controls->Add(stockPanel);
            stockPanel->Dock = DockStyle::Fill;
        }
        void ShowNewArticlePanel(Object^ sender, EventArgs^ e) {
            NewArticlePanel^ newArticlePanel = gcnew NewArticlePanel();
            newArticlePanel->BackButtonClicked += gcnew System::EventHandler(this, &MyForm::ShowStockPanel);
            this->Controls->Clear();
            this->Controls->Add(newArticlePanel);
            newArticlePanel->Dock = DockStyle::Fill;
        }
        void ShowCommandPanel(Object^ sender, EventArgs^ e) {
            CommandePanel^ commandePanel = gcnew CommandePanel();
            commandePanel->BackButtonClicked += gcnew System::EventHandler(this, &MyForm::ShowMainPanel);
            commandePanel->ExistingCommandClicked += gcnew EventHandler(this, &MyForm::ShowExistingCommandPanel);
            this->Controls->Clear();
            this->Controls->Add(commandePanel);
            commandePanel->Dock = DockStyle::Fill;

        }
        void ShowExistingCommandPanel(Object^ sender, EventArgs^ e) {
            CommandeExistantePanel^ commandeExistantePanel = gcnew CommandeExistantePanel();
            commandeExistantePanel->BackButtonClicked += gcnew System::EventHandler(this, &MyForm::ShowCommandPanel);
            this->Controls->Clear();
            this->Controls->Add(commandeExistantePanel);
            commandeExistantePanel->Dock = DockStyle::Fill;
        }


        void ShowClientPanel(Object^ sender, EventArgs^ e) {
            ClientPanel^ clientPanel = gcnew ClientPanel();
            clientPanel->BackButtonClicked += gcnew System::EventHandler(this, &MyForm::ShowMainPanel);
            this->Controls->Clear();
            this->Controls->Add(clientPanel);
            clientPanel->Dock = DockStyle::Fill;

        }
        void ShowMainPanel(Object^ sender, EventArgs^ e) {
            this->Controls->Clear();
            this->Controls->Add(mainPanel);
            mainPanel->Dock = DockStyle::Fill;
        }
    };
}