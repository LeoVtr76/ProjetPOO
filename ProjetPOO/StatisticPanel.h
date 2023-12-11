#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace Corbeille5 {

	public ref class StatisticPanel : public UserControl {

	public:
		event EventHandler^ BackButtonClicked;
		event EventHandler^ SimuButtonClicked;

		StatisticPanel() {
			InitializeComponent();
			this->Resize += gcnew EventHandler(this, &StatisticPanel::OnResize);
		}

	protected:
		~StatisticPanel() {
			if (components) {
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

		Button^ SimuButton;
		Button^ BackButton;
		ListBox^ TopTenSalesBox;
		ListBox^ WorstTenSalesBox;
		ListBox^ SubTreshProductBox;
		ComboBox^ MonthChoiceBox;
		ComboBox^ YearChoiceBox;
		TextBox^ TurnoverBox;
		TextBox^ AverageBasketBox;
		TextBox^ TotalAmountCustBox;
		TextBox^ ComValueStockBox;
		TextBox^ StockPurchValueBox;
		Label^ Title;
		Label^ AverageBasketLab;
		Label^ TurnoverLab;
		Label^ SubTreshProductLab;
		Label^ TotalAmountCustLab;
		Label^ TopTenSalesLab;
		Label^ WorstTenSalesLab;
		Label^ ComValueStockLab;
		Label^ StockPurchValueLab;
		Label^ MonthChoiceLab;
		Label^ YearChoiceLab;

		void InitializeComponent() {

			this->AutoSize = true;
			this->Dock = DockStyle::Fill;

			Title = (gcnew Label());
			Title->Text = L"Statistiques";
			Title->Font = gcnew Drawing::Font(L"Microsoft SansSerif", 16, FontStyle::Bold);
			Title->AutoSize = true;
			Title->Location = Point(0, 20);
			Title->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			BackButton = (gcnew Button());
			BackButton->TabIndex = 12;
			BackButton->Text = L"Retour";
			BackButton->Size = Drawing::Size(75, 25);
			BackButton->Location = Point(35, 115);
			BackButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom | AnchorStyles::Left);
			BackButton->Click += gcnew EventHandler(this, &StatisticPanel::OnBackButtonClicked);

			SimuButton = (gcnew Button());
			SimuButton->TabIndex = 11;
			SimuButton->Text = L"Simulation";
			SimuButton->Size = Drawing::Size(100, 40);
			SimuButton->Font = gcnew Drawing::Font(L"Microsoft SansSerif", 10);
			SimuButton->Location = Point(20, 90);
			SimuButton->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom);
			SimuButton->Click += gcnew EventHandler(this, &StatisticPanel::OnSimuButtonClicked);

			SubTreshProductBox = (gcnew ListBox());
			SubTreshProductBox->TabIndex = 1;
			SubTreshProductBox->Size = Drawing::Size(150, 70);
			SubTreshProductBox->Location = Point(5, 40);
			SubTreshProductBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top | AnchorStyles::Bottom);

			TopTenSalesBox = (gcnew ListBox());
			TopTenSalesBox->TabIndex = 9;
			TopTenSalesBox->Size = Drawing::Size(150, 250);
			TopTenSalesBox->Location = Point(-5, 40);
			TopTenSalesBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

			WorstTenSalesBox = (gcnew ListBox());
			WorstTenSalesBox->TabIndex = 10;
			WorstTenSalesBox->Size = Drawing::Size(150, 250);
			WorstTenSalesBox->Location = Point(-5, 315);
			WorstTenSalesBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

			AverageBasketBox = (gcnew TextBox());
			AverageBasketBox->TabIndex = 2;
			AverageBasketBox->Size = Drawing::Size(150, 60);
			AverageBasketBox->Location = Point(this->Width - AverageBasketBox->Width + 200, 130);
			AverageBasketBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			AverageBasketBox->ReadOnly = true;

			TotalAmountCustBox = (gcnew TextBox());
			TotalAmountCustBox->TabIndex = 3;
			TotalAmountCustBox->Size = Drawing::Size(150, 60);
			TotalAmountCustBox->Location = Point(this->Width - TotalAmountCustBox->Width + 200, 230);
			TotalAmountCustBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			TotalAmountCustBox->ReadOnly = true;

			ComValueStockBox = (gcnew TextBox());
			ComValueStockBox->TabIndex = 4;
			ComValueStockBox->Size = Drawing::Size(150, 60);
			ComValueStockBox->Location = Point(this->Width - ComValueStockBox->Width + 200, 330);
			ComValueStockBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			ComValueStockBox->ReadOnly = true;

			StockPurchValueBox = (gcnew TextBox());
			StockPurchValueBox->TabIndex = 5;
			StockPurchValueBox->Size = Drawing::Size(150, 60);
			StockPurchValueBox->Location = Point(this->Width - StockPurchValueBox->Width + 200, 430);
			StockPurchValueBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);
			StockPurchValueBox->ReadOnly = true;

			TurnoverBox = (gcnew TextBox());
			TurnoverBox->TabIndex = 8;
			TurnoverBox->Size = Drawing::Size(150, 60);
			TurnoverBox->Location = Point(this->Width - TurnoverBox->Width + 100, 380);
			TurnoverBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);
			TurnoverBox->ReadOnly = true;

			MonthChoiceBox = (gcnew ComboBox());
			MonthChoiceBox->TabIndex = 6;
			MonthChoiceBox->Size = Drawing::Size(150, 60);
			MonthChoiceBox->Location = Point(this->Width - MonthChoiceBox->Width + 100, 180);
			MonthChoiceBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			YearChoiceBox = (gcnew ComboBox());
			YearChoiceBox->TabIndex = 7;
			YearChoiceBox->Size = Drawing::Size(150, 60);
			YearChoiceBox->Location = Point(this->Width - YearChoiceBox->Width + 100, 280);
			YearChoiceBox->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			SubTreshProductLab = (gcnew Label());
			SubTreshProductLab->Text = L"Produit(s) sous le seuil de réapprovisionnement :";
			SubTreshProductLab->Size = Drawing::Size(140,60);
			SubTreshProductLab->Location = Point(8, 10);
			SubTreshProductLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			TopTenSalesLab = (gcnew Label());
			TopTenSalesLab->Text = L"Top 10 des articles les plus vendus :";
			TopTenSalesLab->Size = Drawing::Size(140,60);
			TopTenSalesLab->Location = Point(-5, 10);
			TopTenSalesLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

			WorstTenSalesLab = (gcnew Label());
			WorstTenSalesLab->Text = L"Top 10 des articles les moins vendus :";
			WorstTenSalesLab->Size = Drawing::Size(140, 60);
			WorstTenSalesLab->Location = Point(-5, 285);
			WorstTenSalesLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

			AverageBasketLab = (gcnew Label());
			AverageBasketLab->Text = L"Panier moyen (après remise) :";
			AverageBasketLab->Size = Drawing::Size(145, 60);
			AverageBasketLab->Location = Point(this->Width - AverageBasketLab->Width + 195, 112);
			AverageBasketLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			TotalAmountCustLab = (gcnew Label());
			TotalAmountCustLab->Text = L"Montant total des achats pour un client :";
			TotalAmountCustLab->Size = Drawing::Size(140, 60);
			TotalAmountCustLab->Location = Point(this->Width - TotalAmountCustLab->Width + 190, 200);
			TotalAmountCustLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			ComValueStockLab = (gcnew Label());
			ComValueStockLab->Text = L"Valeur commerciale du stock :";
			ComValueStockLab->Size = Drawing::Size(150, 60);
			ComValueStockLab->Location = Point(this->Width - ComValueStockLab->Width + 200, 312);
			ComValueStockLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			StockPurchValueLab = (gcnew Label());
			StockPurchValueLab->Text = L"Valeur d’achat du stock :";
			StockPurchValueLab->Size = Drawing::Size(140, 60);
			StockPurchValueLab->Location = Point(this->Width - StockPurchValueLab->Width + 190, 412);
			StockPurchValueLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Left | AnchorStyles::Top);

			MonthChoiceLab = (gcnew Label());
			MonthChoiceLab->Text = L"Mois du chiffre d'affaire :";
			MonthChoiceLab->Size = Drawing::Size(140, 60);
			MonthChoiceLab->Location = Point(this->Width - MonthChoiceLab->Width + 90, 160);
			MonthChoiceLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			YearChoiceLab = (gcnew Label());
			YearChoiceLab->Text = L"Année du chiffre d'affaire :";
			YearChoiceLab->Size = Drawing::Size(140, 60);
			YearChoiceLab->Location = Point(this->Width - YearChoiceLab->Width + 90, 260);
			YearChoiceLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			TurnoverLab = (gcnew Label());
			TurnoverLab->Text = L"Chiffre d'affaire :";
			TurnoverLab->Size = Drawing::Size(140, 60);
			TurnoverLab->Location = Point(this->Width - TurnoverLab->Width + 90, 360);
			TurnoverLab->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top);

			this->Controls->Add(Title);
			this->Controls->Add(SimuButton);
			this->Controls->Add(BackButton);
			this->Controls->Add(TopTenSalesBox);
			this->Controls->Add(WorstTenSalesBox);
			this->Controls->Add(TurnoverBox);
			this->Controls->Add(MonthChoiceBox);
			this->Controls->Add(YearChoiceBox);
			this->Controls->Add(AverageBasketBox);
			this->Controls->Add(SubTreshProductBox);
			this->Controls->Add(TotalAmountCustBox);
			this->Controls->Add(ComValueStockBox);
			this->Controls->Add(StockPurchValueBox);
			this->Controls->Add(AverageBasketLab);
			this->Controls->Add(TurnoverLab);
			this->Controls->Add(SubTreshProductLab);
			this->Controls->Add(TotalAmountCustLab);
			this->Controls->Add(TopTenSalesLab);
			this->Controls->Add(WorstTenSalesLab);
			this->Controls->Add(ComValueStockLab);
			this->Controls->Add(StockPurchValueLab);
			this->Controls->Add(MonthChoiceLab);
			this->Controls->Add(YearChoiceLab);

			AdjustButtonSizeAndPosition();
		}

		void OnResize(Object^ sender, EventArgs^ e) {
			AdjustButtonSizeAndPosition();
		}

		void AdjustButtonSizeAndPosition() {
			int spacing = 20;
			int textBoxHeight = 60;
			int textBoxWidth = 150;
			double scale = 0.5;

			int newWidth = textBoxWidth + ((this->Width - 800) * scale);

			newWidth = Math::Max(newWidth, textBoxHeight);

			AverageBasketBox->Size = Drawing::Size(newWidth, textBoxHeight);
			TotalAmountCustBox->Size = Drawing::Size(newWidth, textBoxHeight);
			ComValueStockBox->Size = Drawing::Size(newWidth, textBoxHeight);
			StockPurchValueBox->Size = Drawing::Size(newWidth, textBoxHeight);
			MonthChoiceBox->Size = Drawing::Size(newWidth, textBoxHeight);
			YearChoiceBox->Size = Drawing::Size(newWidth, textBoxHeight);
			TurnoverBox->Size = Drawing::Size(newWidth, textBoxHeight);
		}

		void OnBackButtonClicked(Object^ sender, EventArgs^ e) {
			BackButtonClicked(this, e);
		}

		void OnSimuButtonClicked(Object^ sender, EventArgs^ e) {
			SimuButtonClicked(sender, e);
		}

	};
}