#include "artista.h"
#include "album.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
artista::artista() {
    albumes = nullptr;
    numAlbumes = 0;
    codigo = 0;
    edad = 0;
    seguidores = 0;
    posicion = 0;
}

artista::artista(const artista &copia){
    codigo = copia.codigo;
    nombre = copia.nombre;
    edad = copia.edad;
    pais = copia.pais;
    seguidores = copia.seguidores;
    posicion = copia.posicion;
    numAlbumes = copia.numAlbumes;

    if(numAlbumes > 0){
        albumnes = new album[numAlbumes];
        for(int i =0;i<numAlbumes;i++){
            albumes[i]=copia.albumes[i];
        }
    }
    else{
        albumes = nullptr;
    }
}

artista::~Artista() {
    delete[] albumes;
}

void artista::agregarAlbum(const album &a){
    album *nuevoArr = new album[numAlbumes + 1];
    for (int i = 0; i < numAlbumes; i++)
        nuevoArr[i] = albumes[i];
    nuevoArr[numAlbumes] = a;

    delete[] albumes;
    albumes = nuevoArr;
    numAlbumes++;
}

void artista::mostrar() const{
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
    ranking = r;
}
