#include "pch.h"
using namespace System::Collections::Generic;

DatabaseManager::DatabaseManager() {
    connectionString = "Data Source=LOVAUTHIER69D8\\MSSQL_LEO;"
        "Initial Catalog=ProjetPOO;"
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

        // Ajouter chaque pays � la liste
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
        Console::WriteLine("Pays ajout� avec succ�s !");
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

        // Ensuite, ins�rez la ville
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

    // D'abord, trouvez l'ID de la ville
    String^ cityIdQuery = "SELECT ID_VILLE FROM ville WHERE VIL_NOM = @cityName";
    SqlCommand^ cityIdCommand = gcnew SqlCommand(cityIdQuery, connection);
    cityIdCommand->Parameters->AddWithValue("@cityName", cityName);

    int cityId = -1;

    try {
        connection->Open();
        cityId = (int)cityIdCommand->ExecuteScalar();

        // Ensuite, ins�rez l'adresse
        String^ insertAddressQuery = "INSERT INTO adresse (ADR_NUM_RUE, ADR_RUE, ID_VILLE) OUTPUT INSERTED.ID_ADRESSE VALUES (@streetNumber, @streetName, @cityId)";
        SqlCommand^ insertAddressCommand = gcnew SqlCommand(insertAddressQuery, connection);
        insertAddressCommand->Parameters->AddWithValue("@streetNumber", streetNumber);
        insertAddressCommand->Parameters->AddWithValue("@streetName", streetName);
        insertAddressCommand->Parameters->AddWithValue("@cityId", cityId);

        // R�cup�rer et retourner l'ID de la nouvelle adresse
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
void DatabaseManager::AddPersonnel(String^ firstName, String^ lastName, String^ hierarchyLevel, String^ hireDate, int managerId, int addressId) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);

    String^ commandText = "INSERT INTO personnel (PERS_PRENOM, PERS_NOM, PERS_NH, PERS_DATE_EMB, ID_ADRESSE";
    if (managerId != -1) {
        commandText += ", ID_SUPERIEUR";
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
            String^ fullName = row["PRES_PRENOM"]->ToString() + " " + row["PRES_NOM"]->ToString();
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
            return -1; // Ou une autre valeur indiquant qu'aucune adresse n'a �t� trouv�e
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Erreur : " + e->Message);
        return -1; // Ou une autre valeur indiquant une erreur
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
        Console::WriteLine("Commande ajout�e avec succ�s !");
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
        //AND PERS_DATE_EMB = @hireDate";
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






