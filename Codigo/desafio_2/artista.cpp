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
    ranking = 0;
}

Artista::Artista(int cod, string nom, int ed, string p){
    codigo = cod;
    nombre = nom;
    edad = ed;
    pais = p;
    seguidores =0;
    posicion = 0;
    numAlbumes=0;
    albumes = nullptr;
    ranking =0;
}

Artista::Artista(const Artista &copia){
    codigo = copia.codigo;
    nombre = copia.nombre;
    edad = copia.edad;
    pais = copia.pais;
    seguidores = copia.seguidores;
    posicion = copia.posicion;
    ranking = copia.ranking;
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
    cout<<"edad: "<<edad<<" seguidores: "<<seguidores<<"posicion global: "<<ranking<<endl;

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

void cargarArtistas(const string &nombreArchivo, Artista *&artistas, int &numArtistas) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout << "no se pudo abrir el archivo de artistas" << endl;
        return;
    }

    string linea;
    numArtistas = 0;
    Artista *temp = nullptr;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        int p1 = linea.find('|');
        int p2 = linea.find('|', p1 + 1);
        int p3 = linea.find('|', p2 + 1);
        int p4 = linea.find('|', p3 + 1);
        int p5 = linea.find('|', p4 + 1);

        string nombre = linea.substr(0, p1);
        string codStr = linea.substr(p1 + 1, p2 - p1 - 1);
        string edadStr = linea.substr(p2 + 1, p3 - p2 - 1);
        string pais = linea.substr(p3 + 1, p4 - p3 - 1);
        string segStr = linea.substr(p4 + 1, p5 - p4 - 1);
        string rankStr = linea.substr(p5 + 1);

        int codigo = atoi(codStr.c_str());
        int edad = atoi(edadStr.c_str());
        int seguidores = atoi(segStr.c_str());
        float ranking = atof(rankStr.c_str());

        Artista nuevo(codigo, nombre, edad, pais);
        nuevo.setSeguidores(seguidores);
        nuevo.setRanking(ranking);

        Artista *nuevoArr = new Artista[numArtistas + 1];
        for (int i = 0; i < numArtistas; i++)
            nuevoArr[i] = temp[i];
        nuevoArr[numArtistas] = nuevo;

        delete[] temp;
        temp = nuevoArr;
        numArtistas++;
    }

    archivo.close();
    artistas = temp;

    cout<<"artistas cargados: "<<numArtistas<<endl;
}
