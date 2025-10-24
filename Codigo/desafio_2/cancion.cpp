#include "cancion.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

void Cancion::setReproducciones(int newReproducciones)
{
    reproducciones = newReproducciones;
}

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
    rutaBase = copia.rutaBase;
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
    cout<<"Reproduciendo "<<nombre<<" en "<<calidad<<" kbps/n"<<endl;
    cout<<"ruta: "<<ruta<<"-"<<calidad<<".ogg"<<endl;
    cout<< "********************" <<endl;
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

int Cancion::getIdAlbum() const
{
    return idAlbum;
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
string Cancion::getRutaBase() const {
    return rutaBase;
}

void Cancion::cargarCanciones(const string &nombreArchivo, Cancion *&canciones, int &numCanciones) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout << "Error en nuestro sistema de canciones" << endl;
        return;
    }

    string linea;
    numCanciones = 0;
    Cancion *temp = nullptr;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        int pos[10];
        pos[0] = linea.find('|');
        for (int i = 1; i < 10; i++)
            pos[i] = linea.find('|', pos[i - 1] + 1);

        string idStr = linea.substr(0, pos[0]);
        string idArtistaStr = linea.substr(pos[0] + 1, pos[1] - pos[0] - 1);
        string idAlbumStr = linea.substr(pos[1] + 1, pos[2] - pos[1] - 1);
        string nombre = linea.substr(pos[3] + 1, pos[4] - pos[3] - 1);
        string duracionStr = linea.substr(pos[4] + 1, pos[5] - pos[4] - 1);
        string ruta128 = linea.substr(pos[5] + 1, pos[6] - pos[5] - 1);
        string ruta320 = linea.substr(pos[6] + 1, pos[7] - pos[6] - 1);
        string rutaPortada = linea.substr(pos[7] + 1, pos[8] - pos[7] - 1);
        string creditos = linea.substr(pos[8] + 1, pos[9] - pos[8] - 1);
        string vecesStr = linea.substr(pos[9] + 1);

        int id = atoi(idStr.c_str());
        float duracion = atof(duracionStr.c_str());
        int veces = atoi(vecesStr.c_str());

        Cancion nueva(nombre, id, duracion, ruta128);
        nueva.setReproducciones(veces);

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
}
