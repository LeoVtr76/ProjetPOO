#pragma once
using namespace System;

public ref class CLPersonnel {
private:
    int _id;
    String^ _nom;
    String^ _prenom;
    String^ _adresse;
    String^ _superieurHierarchique;
    String^ _niveauHierarchique;
    DateTime _dateEmbauche;

public:
    CLPersonnel(int id, String^ nom, String^ prenom, String^ niveauHierarchique, DateTime dateEmbauche, String^ superieurHierarchique, String^ adresse);

    int GetId();
    String^ GetNom();
    String^ GetPrenom();
    String^ GetAdresse();
    String^ GetSuperieurHierarchique();
    String^ GetNiveauHierarchique();
    DateTime GetDateEmbauche();
};
