#include "artista.h"
#include "album.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
Artista::Artista() {
    albumes = nullptr;
    numAlbumes = 0;
    codigo = 0;
    edad = 0;
    seguidores = 0;
    posicion = 0;
}

Artista::Artista(int cod, string nom, int ed, string paisArt)
{
    codigo = cod;
    nombre = nom;
    edad = ed;
    pais = paisArt;
    seguidores = 0;
    posicion = 0;
    albumes = nullptr;
    numAlbumes = 0;
}

Artista::Artista(const Artista &copia){
    codigo = copia.codigo;
    nombre = copia.nombre;
    edad = copia.edad;
    pais = copia.pais;
    seguidores = copia.seguidores;
    posicion = copia.posicion;
    numAlbumes = copia.numAlbumes;

    if(numAlbumes > 0){
        albumes = new Album[numAlbumes];
        for(int i =0;i<numAlbumes;i++){
            albumes[i]=copia.albumes[i];
        }
    }
    else{
        albumes = nullptr;
    }
}

Artista::~Artista() {
    delete[] albumes;
}

void Artista::agregarAlbum(const Album &a){
    Album *nuevoArr = new Album[numAlbumes + 1];
    for (int i = 0; i < numAlbumes; i++)
        nuevoArr[i] = albumes[i];
    nuevoArr[numAlbumes] = a;

    delete[] albumes;
    albumes = nuevoArr;
    numAlbumes++;
}

void Artista::mostrar() const{
    cout<<"artista: "<<nombre<<" ("<<pais<<") "<<endl;
    cout<<"edad: "<<edad<<" seguidores: "<<seguidores<<"posicion global: "<<posicion<<endl;

    for(int i=0;i<numAlbumes;i++){
        cout<<"album:"<<i+1<<"---\n";
        albumes[i].mostrar();
    }
}

int Artista::getCodigo() const {
    return codigo;
}
string Artista::getNombre() const {
    return nombre;
}
string Artista::getPais() const {
    return pais;
}
int Artista::getEdad() const {
    return edad;
}

void Artista::setSeguidores(int s) {
    seguidores = s;
}
void Artista::setRanking(float r) {
    posicion = r;
}

void Artista::cargarArtistas(const string &nombreArchivo, Artista *&artistas, int &numArtistas) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout << "Error en nuestros sistema de artistas" << endl;
        return;
    }

    string linea;
    numArtistas = 0;
    Artista *temp = nullptr;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        // Formato: idArtista|nombreArtista|edad|pais|seguidores|

        int p1 = linea.find('|');
        int p2 = linea.find('|', p1 + 1);
        int p3 = linea.find('|', p2 + 1);
        int p4 = linea.find('|', p3 + 1);

        string codArt = linea.substr(0, p1);
        string nombreArt = linea.substr(p1 + 1, p2 - p1 - 1);
        string edadArt = linea.substr(p2 + 1, p3 - p2 - 1);
        string paisArt = linea.substr(p3 + 1, p4 - p3 - 1);
        string segArt = linea.substr(p4 + 1);

        int codigo = atoi(codArt.c_str());
        int edad = atoi(edadArt.c_str());
        int seguidores = atoi(segArt.c_str());

        Artista nuevo(codigo, nombreArt, edad, paisArt);
        nuevo.setSeguidores(seguidores);

        Artista* nuevoArr = new Artista[numArtistas + 1];

        for (int i = 0; i < numArtistas; i++) {
            nuevoArr[i] = temp[i];
        }

        nuevoArr[numArtistas] = nuevo;
        nuevoArr[numArtistas].setSeguidores(seguidores);

        delete[] temp;
        temp = nuevoArr;
        numArtistas++;
    }
    archivo.close();
    artistas = temp;
}

