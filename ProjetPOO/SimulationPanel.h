#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {
	
	public ref class SimulationPanel : public UserControl {

	public:
		event EventHandler^ BackButtonClicked;

		SimulationPanel() {
			InitializeComponent();
		}

	protected:
		~SimulationPanel() {
			if (components) {
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

		Button^ BackButton;
		Button^ ValidButton;
		CheckedListBox^ VATBox;
		CheckedListBox^ SalesMarginBox;
		CheckedListBox^ TradeDiscBox;
		CheckedListBox^ UnknownMarkBox;
		TextBox^ PurchValueStockBox;
		TextBox^ ResultComValueStockBox;
		Label^ Title;
		Label^ PurchValueStockLab;
		Label^ VATLab;
		Label^ SalesMarginLab;
		Label^ TradeDiscLab;
		Label^ UnknownMarkLab;
		Label^ ResultComValueStockLab;


		void InitializeComponent() {

			this->AutoSize = true;
			this->Dock = DockStyle::Fill;

			BackButton = (gcnew Button());
			BackButton->TabIndex = 8;
			BackButton->Text = L"Retour";
			BackButton->Size = Drawing::Size(75, 25);
			BackButton->Location = Point(35, 115);
			BackButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom | AnchorStyles::Left);
			BackButton->Click += gcnew EventHandler(this, &SimulationPanel::OnBackButtonClicked);

			ValidButton = (gcnew Button());
			ValidButton->TabIndex = 6;
			ValidButton->Text = L"Valider";
			ValidButton->Size = Drawing::Size(100, 40);
			ValidButton->Font = gcnew Drawing::Font(L"Microsoft SansSerif", 10);
			ValidButton->Location = Point(20, 90);
			ValidButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom);

			Title = (gcnew Label());
			Title->Text = L"Simulation des variations de valeurs commerciales";
			Title->Font = gcnew Drawing::Font(L"Microsoft SansSerif", 16, FontStyle::Bold);
			Title->AutoSize = true;
			Title->Location = Point(-200, 20);
			Title->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			PurchValueStockBox = (gcnew TextBox());
			PurchValueStockBox->TabIndex = 1;
			PurchValueStockBox->Size = Drawing::Size(100, 60);
			PurchValueStockBox->Location = Point(this->Width - PurchValueStockBox->Width - 30, 120);
			PurchValueStockBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			ResultComValueStockBox = (gcnew TextBox());
			ResultComValueStockBox->TabIndex = 7;
			ResultComValueStockBox->Size = Drawing::Size(100, 60);
			ResultComValueStockBox->Location = Point(this->Width - ResultComValueStockBox->Width - 30, 450);
			ResultComValueStockBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			ResultComValueStockBox->ReadOnly = true;

			VATBox = gcnew CheckedListBox();
			VATBox->TabIndex = 2;
			VATBox->FormattingEnabled = true;
			VATBox->Items->AddRange(gcnew cli::array<Object^>(3) { L"TVA 1", L"TVA 2", L"TVA 3" });
			VATBox->Location = Point(-140, 200);
			VATBox->Size = Drawing::Size(120, 60);
			VATBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			SalesMarginBox = gcnew CheckedListBox();
			SalesMarginBox->TabIndex = 3;
			SalesMarginBox->FormattingEnabled = true;
			SalesMarginBox->Items->AddRange(gcnew cli::array<Object^>(3) { L"5%", L"10%", L"15%" });
			SalesMarginBox->Location = Point(-140, 300);
			SalesMarginBox->Size = Drawing::Size(120, 60);
			SalesMarginBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			TradeDiscBox = gcnew CheckedListBox();
			TradeDiscBox->TabIndex = 4;
			TradeDiscBox->FormattingEnabled = true;
			TradeDiscBox->Items->AddRange(gcnew cli::array<Object^>(2) { L"5%", L"6%"});
			TradeDiscBox->Location = Point(160, 200);
			TradeDiscBox->Size = Drawing::Size(120, 60);
			TradeDiscBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			UnknownMarkBox = gcnew CheckedListBox();
			UnknownMarkBox->TabIndex = 5;
			UnknownMarkBox->FormattingEnabled = true;
			UnknownMarkBox->Items->AddRange(gcnew cli::array<Object^>(3) { L"2%", L"3%", "5%" });
			UnknownMarkBox->Location = Point(160, 300);
			UnknownMarkBox->Size = Drawing::Size(120, 60);
			UnknownMarkBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			PurchValueStockLab = (gcnew Label());
			PurchValueStockLab->Text = L"Valeur d’achat du stock :";
			PurchValueStockLab->Size = Drawing::Size(100, 60);
			PurchValueStockLab->Location = Point(this->Width - PurchValueStockLab->Width - 30, 90);
			PurchValueStockLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			VATLab = (gcnew Label());
			VATLab->Text = L"TVA :";
			VATLab->Size = Drawing::Size(100, 60);
			VATLab->Location = Point(-140, 180);
			VATLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			SalesMarginLab = (gcnew Label());
			SalesMarginLab->Text = L"Marge commerciale :";
			SalesMarginLab->Size = Drawing::Size(120, 60);
			SalesMarginLab->Location = Point(-140, 280);
			SalesMarginLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			TradeDiscLab = (gcnew Label());
			TradeDiscLab->Text = L"Remise commerciale :";
			TradeDiscLab->Size = Drawing::Size(120, 60);
			TradeDiscLab->Location = Point(160, 180);
			TradeDiscLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			UnknownMarkLab = (gcnew Label());
			UnknownMarkLab->Text = L"Démarque inconnue :";
			UnknownMarkLab->Size = Drawing::Size(120, 60);
			UnknownMarkLab->Location = Point(160, 280);
			UnknownMarkLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			ResultComValueStockLab = (gcnew Label());
			ResultComValueStockLab->Text = L"Résultat de la valeur commerciale du stock :";
			ResultComValueStockLab->Size = Drawing::Size(100, 60);
			ResultComValueStockLab->Location = Point(this->Width - ResultComValueStockBox->Width - 30, 405);
			ResultComValueStockLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);


			this->Controls->Add(Title);
			this->Controls->Add(BackButton);
			this->Controls->Add(ValidButton);
			this->Controls->Add(VATBox);
			this->Controls->Add(SalesMarginBox);
			this->Controls->Add(TradeDiscBox);
			this->Controls->Add(UnknownMarkBox);
			this->Controls->Add(PurchValueStockBox);
			this->Controls->Add(ResultComValueStockBox);
			this->Controls->Add(PurchValueStockLab);
			this->Controls->Add(VATLab);
			this->Controls->Add(SalesMarginLab);
			this->Controls->Add(TradeDiscLab);
			this->Controls->Add(UnknownMarkLab);
			this->Controls->Add(ResultComValueStockLab);


		}



		void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
			BackButtonClicked(this, e);
		}

		
	};
}