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

        // Ajouter chaque pays à la liste
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

        // Ensuite, insérez la ville
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

        // Ensuite, insérez l'adresse
        String^ insertAddressQuery = "INSERT INTO adresse (ADR_NUM_RUE, ADR_RUE, ID_VILLE) OUTPUT INSERTED.ID_ADRESSE VALUES (@streetNumber, @streetName, @cityId)";
        SqlCommand^ insertAddressCommand = gcnew SqlCommand(insertAddressQuery, connection);
        insertAddressCommand->Parameters->AddWithValue("@streetNumber", streetNumber);
        insertAddressCommand->Parameters->AddWithValue("@streetName", streetName);
        insertAddressCommand->Parameters->AddWithValue("@cityId", cityId);

        // Récupérer et retourner l'ID de la nouvelle adresse
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
void DatabaseManager::AddPersonnel(String^ firstName, String^ lastName, String^ hierarchyLevel, String^ hireDate, Object^ managerId, int addressId) {
    SqlConnection^ connection = gcnew SqlConnection(connectionString);

    String^ commandText = "INSERT INTO personnel (PERS_NOM, PERS_PRENOM, PERS_NH, PERS_DATE_EMB, ID_SUPERIEUR, ID_ADRESSE) VALUES (@firstName, @lastName, @hierarchyLevel, @hireDate, @managerId, @addressId)";
    SqlCommand^ command = gcnew SqlCommand(commandText, connection);

    command->Parameters->AddWithValue("@firstName", firstName);
    command->Parameters->AddWithValue("@lastName", lastName);
    command->Parameters->AddWithValue("@hierarchyLevel", hierarchyLevel);
    command->Parameters->AddWithValue("@hireDate", DateTime::Parse(hireDate));

    if (managerId == nullptr || managerId->GetType() == DBNull::typeid) {
        command->Parameters->AddWithValue("@managerId", DBNull::Value);
    }
    else {
        command->Parameters->AddWithValue("@managerId", managerId);
    }

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



