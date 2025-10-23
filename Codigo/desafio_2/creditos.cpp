#include "creditos.h"
#include <iostream>
#include <string>

using namespace std;

creditos::creditos() {}

creditos::creditos(string nom, string ape, string cod, string rol):
    nombre(nom),apellido(ape),codigoSociedad(cod),rol(r) {}

creditos::creditos(const credito &c){
    nombre = c.nombre;
    apellido = c.apellido;
    codigoSociedad = c.codigoSociedad;
    rol = c.rol;
}

creditos::~Creditos() {}

void creditos::mostrar() const{
    cout<<rol<<": "<<nombre<<" "<<apellido<<" ("<<codigoSociedad<<")"<<endl;
}

string creditos::getNombre() const {return nombre;}
string creditos::getApellido() const {return apellido;}
string creditos::getcodigoSociedad() const {return codigoSociedad;}
string creditos::getRol() const {return rol;}

void creditos::setNombre(const string &n)
