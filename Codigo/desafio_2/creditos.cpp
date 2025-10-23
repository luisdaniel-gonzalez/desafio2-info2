#include "creditos.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

Creditos::Creditos() {}

Creditos::Creditos(string nom, string ape, string cod, string r):
    nombre(nom),apellido(ape),codigoSociedad(cod),rol(r) {}

Creditos::Creditos(const Creditos &c){
    nombre = c.nombre;
    apellido = c.apellido;
    codigoSociedad = c.codigoSociedad;
    rol = c.rol;
}

Creditos::~Creditos() {}

void Creditos::mostrar() const{
    cout<<rol<<": "<<nombre<<" "<<apellido<<" ("<<codigoSociedad<<")"<<endl;
}

string Creditos::getNombre() const {return nombre;}
string Creditos::getApellido() const {return apellido;}
string Creditos::getcodigoSociedad() const {return codigoSociedad;}
string Creditos::getRol() const {return rol;}

void Creditos::setNombre(const string &n){
    nombre = n;
}
void Creditos::setApellido(const string &a){
    apellido = a;
}
void Creditos::setcodigoSociedad(const string &s){
    codigoSociedad = s;
}
void Creditos::setRol(const string &r){
    rol = r;
}

void cargarCreditos(const string &nombreArchivo, Creditos *&creditos,int &numCreditos){
    ifstream archivo(nombreArchivo.c_str());
    if(!archivo){
        cout<<"no se encontro el archivo de creditos"<<endl;
        return;
    }
    string linea;
    numCreditos = 0;
    Creditos *temp = nullptr;

    while(getline(archivo,linea)){
        if (linea.empty()) continue;
        //obtenemos posiciones de los creditos del archivo de creditos
        int p1 = linea.find('|');
        int p2 = linea.find('|', p1 + 1);
        int p3 = linea.find('|', p2 + 1);
        int p4 = linea.find('|', p3 + 1);
        int p5 = linea.find('|', p4 + 1);
        int p6 = linea.find('|', p5 + 1);
        int p7 = linea.find('|', p6 + 1);
        int p8 = linea.find('|', p7 + 1);
        int p9 = linea.find('|', p8 + 1);
        int p10 = linea.find('|', p9 + 1);
        int p11 = linea.find('|', p10 + 1);

        string rol1 = linea.substr(0, p1);
        string nom1 = linea.substr(p1 + 1, p2 - p1 - 1);
        string ape1 = linea.substr(p2 + 1, p3 - p2 - 1);
        string cod1 = linea.substr(p3 + 1, p4 - p3 - 1);

        string rol2 = linea.substr(p4 + 1, p5 - p4 - 1);
        string nom2 = linea.substr(p5 + 1, p6 - p5 - 1);
        string ape2 = linea.substr(p6 + 1, p7 - p6 - 1);
        string cod2 = linea.substr(p7 + 1, p8 - p7 - 1);

        string rol3 = linea.substr(p8 + 1, p9 - p8 - 1);
        string nom3 = linea.substr(p9 + 1, p10 - p9 - 1);
        string ape3 = linea.substr(p10 + 1, p11 - p10 - 1);
        string cod3 = linea.substr(p11 + 1);

        Creditos c1(nom1, ape1, cod1, rol1);
        Creditos c2(nom2, ape2, cod2, rol2);
        Creditos c3(nom3, ape3, cod3, rol3);

        Creditos *nuevoArr = new Creditos[numCreditos + 3];
        for (int i = 0; i < numCreditos; i++)
            nuevoArr[i] = temp[i];

        nuevoArr[numCreditos] = c1;
        nuevoArr[numCreditos + 1] = c2;
        nuevoArr[numCreditos + 2] = c3;

        delete[] temp;
        temp = nuevoArr;
        numCreditos += 3;
    }

    archivo.close();
    creditos = temp;

    cout<<"creditos cargados con exito "<<numCreditos<<endl;
}
