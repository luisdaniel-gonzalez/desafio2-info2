#include "album.h"
#include "cancion.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
album::album() {
    numcanciones = 0;
    canciones = nullptr;
    numGeneros = 0;
    duracionTotal = 0;
    puntuacion = 0;
}

album::album(string nom, int cod, string fecha, string sel, string port):
    nombre(nom), codigo(cod), fechaDeLanzamiento(fecha),sello(sel), rutaPortada(port), numcanciones(0),numGeneros(0), duracionTotal(0), puntuacion(0) {
    canciones = nullptr;
}

album::album(const album &copia){
    nombre = copia.nombre;
    codigo = copia.codigo;
    fechaDeLanzamiento = copia.fechaDeLanzamiento;
    sello = copia.sello;
    rutaPortada = copia.rutaPortada;
    puntuacion = copia.puntuacion;
    duracionTotal = copia.duracionTotal;
    numcanciones = copia.numcanciones;
    numGeneros = copia.numGeneros;

    for (int i = 0; i < numGeneros; i++)
        genero[i] = copia.genero[i];
    if (numcanciones > 0) {
        canciones = new cancion[numcanciones];
        for (int i = 0; i < numcanciones; i++)
            canciones[i] = copia.canciones[i];
    }
    else{
        canciones = nullptr;
    }
}

album::~album(){
    delete[] canciones;
}

void album::agregarGenero(const string &g) {
    if (numGeneros < 4) {
        genero[numGeneros] = g;
        numGeneros++;
    }
}

void album::agregarCancion(const Cancion &c) {
    Cancion *nuevoArr = new cancion[numcanciones + 1];
    for (int i = 0; i < numcanciones; i++)
        nuevoArr[i] = canciones[i];
    nuevoArr[numcanciones] = c;

    delete[] canciones;
    canciones = nuevoArr;
    numcanciones++;

    duracionTotal += c.getDuracion();
}

void album::mostrar() const{
    cout<<"album: "<<nombre<<" ("<<fechaDeLanzamiento<<")"<<endl;
    cout<<"sello: "<<sello<<" puntuacion: "<<puntuacion<<endl;
    cout<<"generos: ";
    for (int i = 0; i < numGeneros; i++)
        cout << genero[i] << " ";
    cout<<"duracion total: "<<duracionTotal<<"min"<<endl;
    cout<<"canciones: "<<endl;
    for (int i = 0; i < numcanciones; i++)
        canciones[i].mostrar();
}

string album::getNombre() const {
    return nombre;
}
string album::getPortada() const {
    return portadaRuta;
}
float album::getPuntuacion() const {
    return puntuacion;
}
int album::getCodigo() const {
    return codigo;
}

void album::setPuntuacion(float p) {
    puntuacion = p;
}

