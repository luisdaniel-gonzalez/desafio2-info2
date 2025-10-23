#include "cancion.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

Cancion::Cancion() {
    id = 0;
    duracion = 0;
    ruta = "";
    reproducciones = 0;
    creditos = nullptr;
    numCreditos = 0;
}

Cancion::Cancion(string nom, int id_,float dur,string ruta_):
    nombre(nom),id(id_),duracion(dur),ruta(ruta_),reproducciones(0),creditos(nullptr),numCreditos(0) {}

Cancion::Cancion(const Cancion &copia){
    nombre = copia.nombre;
    id = copia.id;
    duracion = copia.duracion;
    ruta = copia.ruta;
    reproducciones = copia.reproducciones;
    numCreditos = copia.numCreditos;
    if (numCreditos > 0) {
        creditos = new Creditos[numCreditos];
        for (int i = 0; i < numCreditos; i++)
            creditos[i] = copia.creditos[i];
    }
    else{
        creditos = nullptr;
    }
}

Cancion::~Cancion() {
    delete[] creditos;
}

void Cancion::agregarCredito(const Creditos &c) {
    Creditos *nuevo = new Creditos[numCreditos + 1];
    for (int i = 0; i < numCreditos; i++)
        nuevo[i] = creditos[i];
    nuevo[numCreditos] = c;
    delete[] creditos;
    creditos = nuevo;
    numCreditos++;
}

void Cancion::reproducir(int calidad) const{
    cout<<"reproduciendo "<<nombre<<" en "<<calidad<<" kbps/n"<<endl;
    cout<<"ruta: "<<ruta<<"-"<<calidad<<".ogg"<<endl;
    cout<<"**********************"<<endl;
}

void Cancion::mostrar()const{
    cout<<"cancion: "<<nombre<<" |ID: "<<id<<" |duracion: "<<duracion<<"min"<<endl;
    for(int i=0; i<numCreditos;i++){
        creditos[i].mostrar();
    }
}

int Cancion::getId() const {
    return id;
}
string Cancion::getNombre() const {
    return nombre;
}
float Cancion::getDuracion() const {
    return duracion;
}
int Cancion::getReproducciones() const {
    return reproducciones;
}
string Cancion::getRuta() const {
    return ruta;
}

//ahora comenzamos con las funciones para abrir el archivo

void cargarCanciones(const string &nombreArchivo, Cancion *&canciones, int &numCanciones) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout << "no se pudo abrir el archivo de canciones" << endl;
        return;
    }

    string linea;
    numCanciones = 0;
    Cancion *temp = nullptr;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        int p1 = linea.find('|');
        int p2 = linea.find('|', p1 + 1);
        int p3 = linea.find('|', p2 + 1);
        int p4 = linea.find('|', p3 + 1);

        string nombre = linea.substr(0, p1);
        string idStr = linea.substr(p1 + 1, p2 - p1 - 1);
        string durStr = linea.substr(p2 + 1, p3 - p2 - 1);
        string ruta = linea.substr(p3 + 1, p4 - p3 - 1);
        string repStr = linea.substr(p4 + 1);

        int id = atoi(idStr.c_str());
        float duracion = atof(durStr.c_str());
        int reproducciones = atoi(repStr.c_str());

        Cancion nueva(nombre, id, duracion, ruta);

        Cancion *nuevoArr = new Cancion[numCanciones + 1];
        for (int i = 0; i < numCanciones; i++)
            nuevoArr[i] = temp[i];
        nuevoArr[numCanciones] = nueva;

        delete[] temp;
        temp = nuevoArr;
        numCanciones++;
    }
    archivo.close();
    canciones = temp;
    cout<<"canciones cargadas: "<<numCanciones<<endl;
}
