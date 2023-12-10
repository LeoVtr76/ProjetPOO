#pragma once
#include <cliext/vector>
using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Collections::Generic;
public ref class DatabaseManager {
private:
    String^ connectionString;

public:
    DatabaseManager();
    List<String^>^ ShowCountry();
    List<String^>^ GetPostalCodes(String^ countryName);
    List<String^>^ GetCities(String^ postalCode);
    void AddCountry(String^ countryName);
    bool CheckCountry(String^ countryName);
    bool CheckCity(String^ countryName,String^ cityName);
    void AddCity(String^ cityName, String^ postalCode, String^ countryName);
    int AddAddress(String^ streetNumber, String^ streetName, String^ cityName);
    void AddPersonnel(String^ firstName, String^ lastName, String^ hierarchyLevel, String^ hireDate, int managerId, int addressId);
    void AddClient(String^ firstName, String^ lastName, String^ birthDate, int addressId);
    //List<String^>^ GetManagers();
    Dictionary<String^, int>^ DatabaseManager::GetManagers();
    Dictionary<String^, int>^ DatabaseManager::GetClients();
    bool PersonnelExists(String^ firstName, String^ lastName, String^ hireDate);
    bool ClientExists(String^ firstName, String^ lastName, String^ birthDate);
    int GetClientAddressById(int clientId);
    bool CommandExist(String^ ref);
    void AddCommand(String^ ref,String^ datePaie,String^ dateReg, String^ dateLiv, String^ amountHT, String^ amountTVA,int clientId,int addressId);
};
