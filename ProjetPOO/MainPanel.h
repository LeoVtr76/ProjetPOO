#pragma once

#include "PersonnelPanel.h"
#include "StockPanel.h"
#include "CommandePanel.h"
#include "ClientPanel.h"
// Incluez ici les autres panels que vous avez.

namespace Corbeille5 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MainPanel : public Panel {
    public:
        event EventHandler^ PersonnelClicked;
        event EventHandler^ StockClicked;
        event EventHandler^ CommandClicked;
        event EventHandler^ ClientClicked;
        // Déclarez d'autres événements pour les différents boutons.

        MainPanel() {
            InitializeComponent();
        }

    protected:
        ~MainPanel() {
            // Nettoyage des ressources
        }

    private:
        TableLayoutPanel^ tableLayoutPanel;
        Button^ personnelButton;
        Button^ clientsButton;
        Button^ stockButton;
        Button^ commandesButton;
        Button^ statistiquesButton;

        void InitializeComponent() {
            // Initialisation des boutons
            this->tableLayoutPanel = (gcnew TableLayoutPanel());
            this->tableLayoutPanel->ColumnCount = 2;
            this->tableLayoutPanel->RowCount = 3;
            this->tableLayoutPanel->Dock = DockStyle::Fill;
            for (int i = 0; i < this->tableLayoutPanel->ColumnCount; i++) {
                this->tableLayoutPanel->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 50));
            }
            for (int i = 0; i < this->tableLayoutPanel->RowCount; i++) {
                this->tableLayoutPanel->RowStyles->Add(gcnew RowStyle(SizeType::Percent, (i < 2) ? 33 : 34));
            }

            // Initialisation des boutons
            personnelButton = CreateButton(L"Gestion Personnel");
            personnelButton->Click += gcnew EventHandler(this, &MainPanel::OnPersonnelClicked);
            clientsButton = CreateButton(L"Gestion Clients");
            clientsButton->Click += gcnew EventHandler(this, &MainPanel::OnClientClicked);
            stockButton = CreateButton(L"Gestion Stock");
            stockButton->Click += gcnew EventHandler(this, &MainPanel::OnStockClicked);
            commandesButton = CreateButton(L"Gestion Commandes");
            commandesButton->Click += gcnew EventHandler(this, &MainPanel::OnCommandClicked);
            statistiquesButton = CreateButton(L"Gestion Statistiques");

            // Ajout des boutons au TableLayoutPanel
            this->tableLayoutPanel->Controls->Add(personnelButton, 0, 0); // Colonne 0, Ligne 0
            this->tableLayoutPanel->Controls->Add(clientsButton, 1, 0); // Colonne 1, Ligne 0
            this->tableLayoutPanel->Controls->Add(stockButton, 0, 1); // Colonne 0, Ligne 1
            this->tableLayoutPanel->Controls->Add(commandesButton, 1, 1); // Colonne 1, Ligne 1
            this->tableLayoutPanel->Controls->Add(statistiquesButton, 0, 2); // Colonne 0, Ligne 2
            this->tableLayoutPanel->SetColumnSpan(statistiquesButton, 2); // Le bouton s'étend sur 2 colonnes

            this->Controls->Add(this->tableLayoutPanel);
        }
        Button^ CreateButton(String^ text) {
            Button^ button = (gcnew Button());
            button->Text = text;
            button->Dock = DockStyle::Fill;
            button->Margin = System::Windows::Forms::Padding(5);
            // Vous pouvez ajouter des gestionnaires d'événements ici
            return button;
        }
        void OnPersonnelClicked(Object^ sender, EventArgs^ e) {
            PersonnelClicked(sender, e);
        }
        void OnStockClicked(Object^ sender, EventArgs^ e) {
            StockClicked(sender, e);
        }
        void OnCommandClicked(Object^ sender, EventArgs^ e) {
            CommandClicked(sender, e);
        }
        void OnClientClicked(Object^ sender, EventArgs^ e) {
            ClientClicked(sender, e);
        }

        // Implémentez les gestionnaires d'événements On...Clicked pour les autres boutons.
    };
}
