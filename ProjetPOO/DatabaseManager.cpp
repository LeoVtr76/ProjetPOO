#include "pch.h"
using namespace System::Collections::Generic;

DatabaseManager::DatabaseManager() {
    connectionString = "Data Source=LOVAUTHIER69D8\\MSSQL_LEO;"
        "Initial Catalog=ProjetPOOtest;"
        "Integrated Security=True;";
}
List<String^>^ DatabaseManager::ShowCountry() {
    List<String^>^ countryList = gcnew List<String^>();
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT pays_nom FROM pays";
    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    SqlDataAdapter^ da = gcnew SqlDataAdapter(command);
    DataTable^ dt = gcnew DataTable();

    try {
        connection->Open();
        da->Fill(dt);

        for each (DataRow ^ row in dt->Rows) {
            String^ countryName = row["pays_nom"]->ToString();
            countryList->Add(countryName);
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
    return countryList;
}
List<String^>^ DatabaseManager::GetPostalCodes(String^ countryName) {
    List<String^>^ postalCodeList = gcnew List<String^>();
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    SqlCommand^ command;
    command = gcnew SqlCommand("SELECT DISTINCT VIL_CP FROM ville INNER JOIN pays ON ville.ID_PAYS = pays.ID_PAYS WHERE pays.PAYS_NOM = @countryName", connection);
    command->Parameters->AddWithValue("@countryName", countryName);
    SqlDataAdapter^ da = gcnew SqlDataAdapter(command);
    DataTable^ dt = gcnew DataTable();

    try {
        connection->Open();
        da->Fill(dt);

        for each (DataRow ^ row in dt->Rows) {
            String^ postalCode = row["VIL_CP"]->ToString();
            postalCodeList->Add(postalCode);
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
    return postalCodeList;
}
List<String^>^ DatabaseManager::GetCities(String^ postalCode) {
    List<String^>^ cityList = gcnew List<String^>();
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT DISTINCT VIL_NOM FROM ville WHERE VIL_CP = @postalCode";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@postalCode", postalCode);

    SqlDataAdapter^ da = gcnew SqlDataAdapter(command);
    DataTable^ dt = gcnew DataTable();

    try {
        connection->Open();
        da->Fill(dt);

        for each (DataRow ^ row in dt->Rows) {
            String^ cityName = row["VIL_NOM"]->ToString();
            cityList->Add(cityName);
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
    return cityList;
}
void DatabaseManager::AddCountry(String^ countryName){
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "INSERT INTO pays (pays_nom) VALUES (@pays_nom)";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@pays_nom", countryName);
    try {
        connection->Open();
        command->ExecuteNonQuery();
        Console::WriteLine("Pays ajouté avec succès !");
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
bool DatabaseManager::CheckCountry(String^ countryName) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT COUNT(1) FROM pays WHERE PAYS_NOM = @countryName";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@countryName", countryName);

    try {
        connection->Open();
        int count = (int)command->ExecuteScalar();
        return count > 0;
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
        return false;
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
bool DatabaseManager::CheckCity(String^ countryName, String^ cityName) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT COUNT(1) FROM ville INNER JOIN pays ON ville.ID_PAYS = pays.ID_PAYS WHERE pays.PAYS_NOM = @countryName AND ville.VIL_NOM = @cityName";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@countryName", countryName);
    command->Parameters->AddWithValue("@cityName", cityName);

    try {
        connection->Open();
        int count = (int)command->ExecuteScalar();
        return count > 0;
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
        return false;
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
void DatabaseManager::AddCity(String^ cityName, String^ postalCode, String^ countryName) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);

    String^ countryIdQuery = "SELECT ID_PAYS FROM pays WHERE PAYS_NOM = @countryName";
    SqlCommand^ countryIdCommand = gcnew SqlCommand(countryIdQuery, connection);
    countryIdCommand->Parameters->AddWithValue("@countryName", countryName);

    try {
        connection->Open();
        int countryId = (int)countryIdCommand->ExecuteScalar();

        String^ insertCityQuery = "INSERT INTO ville (VIL_NOM, VIL_CP, ID_PAYS) VALUES (@cityName, @postalCode, @countryId)";
        SqlCommand^ insertCityCommand = gcnew SqlCommand(insertCityQuery, connection);
        insertCityCommand->Parameters->AddWithValue("@cityName", cityName);
        insertCityCommand->Parameters->AddWithValue("@postalCode", postalCode);
        insertCityCommand->Parameters->AddWithValue("@countryId", countryId);

        insertCityCommand->ExecuteNonQuery();
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
int DatabaseManager::AddAddress(String^ streetNumber, String^ streetName, String^ cityName){
    SqlConnection^ connection = gcnew SqlConnection(connectionString);

    String^ cityIdQuery = "SELECT ID_VILLE FROM ville WHERE VIL_NOM = @cityName";
    SqlCommand^ cityIdCommand = gcnew SqlCommand(cityIdQuery, connection);
    cityIdCommand->Parameters->AddWithValue("@cityName", cityName);

    int cityId = -1;

    try {
        connection->Open();
        cityId = (int)cityIdCommand->ExecuteScalar();

        String^ insertAddressQuery = "INSERT INTO adresse (ADR_NUM_RUE, ADR_RUE, ID_VILLE) OUTPUT INSERTED.ID_ADRESSE VALUES (@streetNumber, @streetName, @cityId)";
        SqlCommand^ insertAddressCommand = gcnew SqlCommand(insertAddressQuery, connection);
        insertAddressCommand->Parameters->AddWithValue("@streetNumber", streetNumber);
        insertAddressCommand->Parameters->AddWithValue("@streetName", streetName);
        insertAddressCommand->Parameters->AddWithValue("@cityId", cityId);

        int newAddressId = (int)insertAddressCommand->ExecuteScalar();
        return newAddressId;
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
        return -1;
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
void DatabaseManager::AddArticle(String^ name, String^ price, String^ amount, String^ sr) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "INSERT INTO article (ART_NOM, ART_MONT_UHC, ART_QTT, ART_SR) VALUES (@name, @price, @amount, @sr)";
    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->Add("@name", SqlDbType::VarChar)->Value = name;
    command->Parameters->Add("@price", SqlDbType::Decimal)->Value = Decimal::Parse(price);
    command->Parameters->Add("@amount", SqlDbType::Int)->Value = Int32::Parse(amount);
    command->Parameters->Add("@sr", SqlDbType::Int)->Value = Int32::Parse(sr);
    try {
        connection->Open();
        command->ExecuteNonQuery();
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
int DatabaseManager::GetCommandByRef(String^ ref) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT ID_COMMANDE FROM commande WHERE COM_REF = @ref";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@ref", ref);

    try {
        connection->Open();
        Object^ result = command->ExecuteScalar();
        if (result != nullptr) {
            return Convert::ToInt32(result);
        }
        else {
            return -1;
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
        return -1;
    }
    finally {
        if (connection->State == ConnectionState::Open) {
            connection->Close();
        }
    }
}
List<CLPersonnel^>^ DatabaseManager::GetAllPersonnel() {
    List<CLPersonnel^>^ list = gcnew List<CLPersonnel^>();
    SqlConnection^ connection = gcnew SqlConnection(connectionString);

    SqlCommand^ command = gcnew SqlCommand(
        "SELECT p.ID_PERSONNEL, p.PERS_NOM, p.PERS_PRENOM, p.PERS_NH, p.PERS_DATE_EMB, "
        "a.ADR_RUE, v.VIL_NOM, pa.PAYS_NOM, "
        "sup.PERS_NOM + ' ' + sup.PERS_PRENOM AS Supérieur "
        "FROM personnel p "
        "JOIN adresse a ON p.ID_ADRESSE = a.ID_ADRESSE "
        "JOIN ville v ON a.ID_VILLE = v.ID_VILLE "
        "JOIN pays pa ON v.ID_PAYS = pa.ID_PAYS "
        "LEFT JOIN personnel sup ON p.ID_PERSONNEL_1 = sup.ID_PERSONNEL", connection);

    try {
        connection->Open();
        SqlDataReader^ reader = command->ExecuteReader();
        while (reader->Read()) {
            int id = reader->GetInt32(0);
            String^ nom = reader->GetString(1);
            String^ prenom = reader->GetString(2);
            String^ nh = reader->GetString(3);
            DateTime dateEmbauche = reader->GetDateTime(4);
            String^ rue = reader->GetString(5);
            String^ ville = reader->GetString(6);
            String^ pays = reader->GetString(7);
            String^ adresseComplete = String::Format("{0}, {1}, {2}", rue, ville, pays);
            String^ supérieur = reader->IsDBNull(8) ? "N/A" : reader->GetString(8);

            CLPersonnel^ p = gcnew CLPersonnel(id, nom, prenom, nh, dateEmbauche, supérieur, adresseComplete);
            list->Add(p);
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open) {
            connection->Close();
        }
    }
    return list;
}

CLPersonnel^ DatabaseManager::GetPersonnelById(int personnelId) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);

    SqlCommand^ command = gcnew SqlCommand(
        "SELECT p.ID_PERSONNEL, p.PERS_NOM, p.PERS_PRENOM, p.PERS_NH, p.PERS_DATE_EMB, "
        "a.ADR_RUE, v.VIL_NOM, pa.PAYS_NOM, "
        "sup.PERS_NOM + ' ' + sup.PERS_PRENOM AS Supérieur "
        "FROM personnel p "
        "JOIN adresse a ON p.ID_ADRESSE = a.ID_ADRESSE "
        "JOIN ville v ON a.ID_VILLE = v.ID_VILLE "
        "JOIN pays pa ON v.ID_PAYS = pa.ID_PAYS "
        "LEFT JOIN personnel sup ON p.ID_PERSONNEL_1 = sup.ID_PERSONNEL "
        "WHERE p.ID_PERSONNEL = @PersonnelID", connection);

    command->Parameters->AddWithValue("@PersonnelID", personnelId);

    CLPersonnel^ personnel = nullptr;

    try {
        connection->Open();
        SqlDataReader^ reader = command->ExecuteReader();
        if (reader->Read()) {
            int id = reader->GetInt32(0);
            String^ nom = reader->GetString(1);
            String^ prenom = reader->GetString(2);
            String^ nh = reader->GetString(3);
            DateTime dateEmbauche = reader->GetDateTime(4);
            String^ rue = reader->GetString(5);
            String^ ville = reader->GetString(6);
            String^ pays = reader->GetString(7);
            String^ adresseComplete = String::Format("{0}, {1}, {2}", rue, ville, pays);
            String^ supérieur = reader->IsDBNull(8) ? "N/A" : reader->GetString(8);

            personnel = gcnew CLPersonnel(id, nom, prenom, nh, dateEmbauche, supérieur, adresseComplete);
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open) {
            connection->Close();
        }
    }

    return personnel;
}

void DatabaseManager::AddCommandArticle(int commandId, int articleId, int quantity) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "INSERT INTO article_commande (ID_COMMANDE, ID_ARTICLE, ART_COM_QTT) VALUES (@commandId, @articleId, @quantity)";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@commandId", commandId);
    command->Parameters->AddWithValue("@articleId", articleId);
    command->Parameters->AddWithValue("@quantity", quantity);

    try {
        connection->Open();
        command->ExecuteNonQuery();
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur lors de l'ajout de l'article à la commande : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open) {
            connection->Close();
        }
    }
}
Dictionary<int, String^>^ DatabaseManager::GetAllArticles() {
    Dictionary<int, String^>^ articles = gcnew Dictionary<int, String^>();
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT ID_ARTICLE, ART_NOM FROM article";
    SqlCommand^ command = gcnew SqlCommand(commandText, connection);

    try {
        connection->Open();
        SqlDataReader^ reader = command->ExecuteReader();

        while (reader->Read()) {
            int id = reader->GetInt32(0); 
            String^ name = reader->GetString(1);
            articles->Add(id, name);
        }
        reader->Close();
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }

    return articles;
}
bool DatabaseManager::ArticleExist(String^ name) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT COUNT(*) FROM article WHERE ART_NOM = @name";
    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@name", name);

    try {
        connection->Open();
        int count = Convert::ToInt32(command->ExecuteScalar());
        return count > 0;
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
        return false;
    }
    finally {
        if (connection->State == ConnectionState::Open) {
            connection->Close();
        }
    }
}
void DatabaseManager::AddPersonnel(String^ firstName, String^ lastName, String^ hierarchyLevel, String^ hireDate, int managerId, int addressId) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);

    String^ commandText = "INSERT INTO personnel (PERS_PRENOM, PERS_NOM, PERS_NH, PERS_DATE_EMB, ID_ADRESSE";
    if (managerId != -1) {
        commandText += ", ID_PERSONNEL_1";
    }
    commandText += ") VALUES (@firstName, @lastName, @hierarchyLevel, @hireDate, @addressId";
    if (managerId != -1) {
        commandText += ", @managerId";
    }
    commandText += ")";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);

    command->Parameters->AddWithValue("@firstName", firstName);
    command->Parameters->AddWithValue("@lastName", lastName);
    command->Parameters->AddWithValue("@hierarchyLevel", hierarchyLevel);
    command->Parameters->AddWithValue("@hireDate", DateTime::Parse(hireDate));
    command->Parameters->AddWithValue("@addressId", addressId);
    if (managerId != -1) {
        command->Parameters->AddWithValue("@managerId", managerId);
    }

    try {
        connection->Open();
        command->ExecuteNonQuery();
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
void DatabaseManager::AddClient(String^ firstName, String^ lastName, String^ birthDate, int addressId) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);

    String^ commandText = "INSERT INTO client (CLI_PRENOM, CLI_NOM, CLI_DATE_ANNIV, ID_ADRESSE) VALUES (@firstName, @lastName, @birthDate, @addressId)";
    SqlCommand^ command = gcnew SqlCommand(commandText, connection);

    command->Parameters->AddWithValue("@firstName", firstName);
    command->Parameters->AddWithValue("@lastName", lastName);
    command->Parameters->AddWithValue("@birthDate", DateTime::Parse(birthDate));
    command->Parameters->AddWithValue("@addressId", addressId);

    try {
        connection->Open();
        command->ExecuteNonQuery();
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
Dictionary<String^, int>^ DatabaseManager::GetManagers() {
    Dictionary<String^, int>^ persDict = gcnew Dictionary<String^, int>();
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT ID_PERSONNEL, PERS_PRENOM, PERS_NOM FROM personnel";
    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    SqlDataAdapter^ da = gcnew SqlDataAdapter(command);
    DataTable^ dt = gcnew DataTable();

    try {
        connection->Open();
        da->Fill(dt);

        for each (DataRow ^ row in dt->Rows) {
            String^ fullName = row["PERS_PRENOM"]->ToString() + " " + row["PERS_NOM"]->ToString();
            int persId = Convert::ToInt32(row["ID_PERSONNEL"]);
            persDict->Add(fullName, persId);
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
    return persDict;
}
Dictionary<String^, int>^ DatabaseManager::GetClients() {
    Dictionary<String^, int>^ clientDict = gcnew Dictionary<String^, int>();
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT ID_CLIENT, CLI_PRENOM, CLI_NOM FROM client";
    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    SqlDataAdapter^ da = gcnew SqlDataAdapter(command);
    DataTable^ dt = gcnew DataTable();

    try {
        connection->Open();
        da->Fill(dt);

        for each (DataRow ^ row in dt->Rows) {
            String^ fullName = row["CLI_PRENOM"]->ToString() + " " + row["CLI_NOM"]->ToString();
            int clientId = Convert::ToInt32(row["ID_CLIENT"]);
            clientDict->Add(fullName, clientId);
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
    return clientDict;
}
int DatabaseManager::GetClientAddressById(int clientId) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT ID_ADRESSE FROM client WHERE ID_CLIENT = @clientId";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@clientId", clientId);

    try {
        connection->Open();
        Object^ result = command->ExecuteScalar();
        if (result != nullptr) {
            return Convert::ToInt32(result);
        }
        else {
            return -1; 
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
        return -1; 
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
bool DatabaseManager::CommandExist(String^ ref) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT COUNT(*) FROM commande WHERE COM_REF = @ref";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@ref", ref);

    try {
        connection->Open();
        int count = Convert::ToInt32(command->ExecuteScalar());
        return count > 0;
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
        return false;
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
void DatabaseManager::AddCommand(String^ ref, String^ datePaie, String^ dateReg, String^ dateLiv, String^ amountHT, String^ amountTVA, int clientId, int addressId) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);

    String^ commandText = "INSERT INTO commande (COM_REF, COM_DATE_PAIEM, COM_DATE_REGL, COM_DATE_LIV, COM_MONT_TOT_HT, COM_MONT_TOT_TVA, ID_CLIENT, ID_ADRESSE) "
        "VALUES (@ref, @datePaie, @dateReg, @dateLiv, @amountHT, @amountTVA, @clientId, @addressId)";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);

    command->Parameters->AddWithValue("@ref", ref);
    command->Parameters->AddWithValue("@datePaie", DateTime::Parse(datePaie));
    command->Parameters->AddWithValue("@dateReg", DateTime::Parse(dateReg));
    command->Parameters->AddWithValue("@dateLiv", DateTime::Parse(dateLiv));
    command->Parameters->AddWithValue("@amountHT", Decimal::Parse(amountHT));
    command->Parameters->AddWithValue("@amountTVA", Decimal::Parse(amountTVA));
    command->Parameters->AddWithValue("@clientId", clientId);
    command->Parameters->AddWithValue("@addressId", addressId);

    try {
        connection->Open();
        command->ExecuteNonQuery();
        Console::WriteLine("Commande ajoutée avec succès !");
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur lors de l'ajout de la commande : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}

bool DatabaseManager::PersonnelExists(String^ firstName, String^ lastName, String^ hireDate) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT COUNT(*) FROM personnel WHERE PERS_PRENOM = @firstName AND PERS_NOM = @lastName AND PERS_DATE_EMB = @hireDate";

    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@firstName", firstName);
    command->Parameters->AddWithValue("@lastName", lastName);
    command->Parameters->AddWithValue("@hireDate", DateTime::Parse(hireDate));

    try {
        connection->Open();
        int count = (int)command->ExecuteScalar();
        return count > 0;
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
        return false;
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
bool DatabaseManager::ClientExists(String^ firstName, String^ lastName, String^ birthDate) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT COUNT(*) FROM client WHERE CLI_PRENOM = @firstName AND CLI_NOM = @lastName AND CLI_DATE_ANNIV = @birthDate";
    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@firstName", firstName);
    command->Parameters->AddWithValue("@lastName", lastName);
    command->Parameters->AddWithValue("@birthDate", DateTime::Parse(birthDate));

    try {
        connection->Open();
        int count = (int)command->ExecuteScalar();
        return count > 0;
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
        return false;
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
}
String^ DatabaseManager::GetArticleById(int articleId) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);
    String^ commandText = "SELECT ART_NOM FROM article WHERE ID_ARTICLE = @articleId";
    SqlCommand^ command = gcnew SqlCommand(commandText, connection);
    command->Parameters->AddWithValue("@articleId", articleId);

    String^ articleName = "";

    try {
        connection->Open();
        Object^ result = command->ExecuteScalar();
        if (result != nullptr) {
            articleName = result->ToString();
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
    }
    finally {
        if (connection->State == ConnectionState::Open)
            connection->Close();
    }
    return articleName;
}






