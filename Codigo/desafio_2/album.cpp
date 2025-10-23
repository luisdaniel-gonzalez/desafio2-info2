#include "album.h"
#include "cancion.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
Album::Album() {
    numcanciones = 0;
    canciones = nullptr;
    numGeneros = 0;
    duracionTotal = 0;
    puntuacion = 0;
}

Album::Album(string nom, int cod, string fecha, string sel, string port):
    nombre(nom), codigo(cod), fechaDeLanzamiento(fecha),sello(sel), rutaPortada(port), numcanciones(0),numGeneros(0), duracionTotal(0), puntuacion(0) {
    canciones = nullptr;
}

Album::Album(const Album &copia){
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
        canciones = new Cancion[numcanciones];
        for (int i = 0; i < numcanciones; i++)
            canciones[i] = copia.canciones[i];
    }
    else{
        canciones = nullptr;
    }
}

Album::~Album(){
    delete[] canciones;
}

void Album::agregarGenero(const string &g) {
    if (numGeneros < 4) {
        genero[numGeneros] = g;
        numGeneros++;
    }
}

void Album::agregarCancion(const Cancion &c) {
    Cancion *nuevoArr = new Cancion[numcanciones + 1];
    for (int i = 0; i < numcanciones; i++)
        nuevoArr[i] = canciones[i];
    nuevoArr[numcanciones] = c;

    delete[] canciones;
    canciones = nuevoArr;
    numcanciones++;

    duracionTotal += c.getDuracion();
}

void Album::mostrar() const{
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

string Album::getNombre() const {
    return nombre;
}
string Album::getPortada() const {
    return rutaPortada;
}
float Album::getPuntuacion() const {
    return puntuacion;
}
int Album::getCodigo() const {
    return codigo;
}

void Album::setPuntuacion(float p) {
    puntuacion = p;
}

void cargarAlbumes(const string &nombreArchivo, Album *&albumes, int &numAlbumes) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout<<"no se pudo abrir el archivo de albumes"<<endl;
        return;
    }

    string linea;
    numAlbumes = 0;
    Album *temp = nullptr;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        int p1 = linea.find('|');
        int p2 = linea.find('|', p1 + 1);
        int p3 = linea.find('|', p2 + 1);
        int p4 = linea.find('|', p3 + 1);
        int p5 = linea.find('|', p4 + 1);
        int p6 = linea.find('|', p5 + 1);
        int p7 = linea.find('|', p6 + 1);
        int p8 = linea.find('|', p7 + 1);
        int p9 = linea.find('|', p8 + 1);

        string nombre = linea.substr(0, p1);
        string codStr = linea.substr(p1 + 1, p2 - p1 - 1);
        string fecha = linea.substr(p2 + 1, p3 - p2 - 1);
        string sello = linea.substr(p3 + 1, p4 - p3 - 1);
        string portada = linea.substr(p4 + 1, p5 - p4 - 1);
        string puntStr = linea.substr(p5 + 1, p6 - p5 - 1);
        string g1 = linea.substr(p6 + 1, p7 - p6 - 1);
        string g2 = linea.substr(p7 + 1, p8 - p7 - 1);
        string g3 = linea.substr(p8 + 1, p9 - p8 - 1);
        string g4 = linea.substr(p9 + 1);

        int codigo = atoi(codStr.c_str());
        float puntuacion = atof(puntStr.c_str());

        Album nuevo(nombre, codigo, fecha, sello, portada);
        nuevo.setPuntuacion(puntuacion);

        if (!g1.empty()) nuevo.agregarGenero(g1);
        if (!g2.empty()) nuevo.agregarGenero(g2);
        if (!g3.empty()) nuevo.agregarGenero(g3);
        if (!g4.empty()) nuevo.agregarGenero(g4);

        Album *nuevoArr = new Album[numAlbumes + 1];
        for (int i = 0; i < numAlbumes; i++)
            nuevoArr[i] = temp[i];
        nuevoArr[numAlbumes] = nuevo;

        delete[] temp;
        temp = nuevoArr;
        numAlbumes++;
    }
    archivo.close();
    albumes = temp;

    cout<<"albumes cargados: "<<numAlbumes<<endl;
}

