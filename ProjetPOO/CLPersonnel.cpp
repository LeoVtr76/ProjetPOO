#include "pch.h"

CLPersonnel::CLPersonnel(int id, String^ nom, String^ prenom, String^ niveauHierarchique, DateTime dateEmbauche, String^ superieurHierarchique, String^ adresse){
    this->_id = id;
    this->_nom = nom;
    this->_prenom = prenom;
    this->_adresse = adresse;
    this->_superieurHierarchique = superieurHierarchique;
    this->_niveauHierarchique = niveauHierarchique;
    this->_dateEmbauche = dateEmbauche;
}

int CLPersonnel::GetId() {
    return this->_id;
}

String^ CLPersonnel::GetNom() {
    return this->_nom;
}

String^ CLPersonnel::GetPrenom() {
    return this->_prenom;
}

String^ CLPersonnel::GetAdresse() {
    return this->_adresse;
}

String^ CLPersonnel::GetSuperieurHierarchique() {
    return this->_superieurHierarchique;
}

String^ CLPersonnel::GetNiveauHierarchique() {
    return this->_niveauHierarchique;
}

DateTime CLPersonnel::GetDateEmbauche() {
    return this->_dateEmbauche;
}
