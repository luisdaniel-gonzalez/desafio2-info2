#include "publicidad.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "plataforma.h"

using namespace std;

char* Publicidad::copiarString(const char* str) {
    if (!str) return nullptr;
    char* nuevo = new char[strlen(str) + 1];
    strcpy(nuevo, str);
    return nuevo;
}

Publicidad::Publicidad() : mensaje(nullptr), categoria(' '), prioridad(0) {}

Publicidad::Publicidad(const char* msg, char cat) : categoria(cat), prioridad(0) {
    mensaje = copiarString(msg);
}

Publicidad::Publicidad(const Publicidad& otra) : categoria(otra.categoria), prioridad(otra.prioridad) {
    mensaje = copiarString(otra.mensaje);
}

Publicidad::~Publicidad() {
    delete[] mensaje;
}

const char* Publicidad::getMensaje() const {
    return mensaje;
}

char Publicidad::getCategoria() const {
    return categoria;
}

int Publicidad::getPrioridad() const {
    return prioridad;
}

void Publicidad::setMensaje(const char* msg) {
    delete[] mensaje;
    mensaje = copiarString(msg);
}

void Publicidad::setCategoria(char cat) {
    categoria = cat;
}

void Publicidad::setPrioridad(int p) {
    prioridad = p;
}

void Publicidad::cargarPublicidades(const string &nombreArchivo, Plataforma &plataforma, int &numPublicidades) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout << "Error en nuestro sistema de publicidad" << endl;
        return;
    }

    string linea;
    int count = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        int p1 = linea.find('|');
        int p2 = linea.find('|', p1 + 1);

        string indicePub = linea.substr(0, p1);
        string categoriaPub = linea.substr(p1 + 1, p2 - p1 - 1);
        string mensajePub = linea.substr(p2 + 1);

        char categoria = categoriaPub[0];

        Publicidad *nueva = new Publicidad(mensajePub.c_str(), categoria);
        nueva->setPrioridad(3 - (count % 3));
        plataforma.agregarPublicidad(nueva);

        count++;
    }

    archivo.close();
}

void Publicidad::mostrar() const {
    cout << "Mensaje: " << (mensaje ? mensaje : "") << ", Categoria: " << categoria << ", Prioridad: " << prioridad << endl;
}

bool Publicidad::operator==(const Publicidad& otra) const {
    return strcmp(mensaje, otra.mensaje) == 0 && categoria == otra.categoria && prioridad == otra.prioridad;
}

Publicidad& Publicidad::operator=(const Publicidad& otra) {
    if (this != &otra) {
        delete[] mensaje;
        mensaje = copiarString(otra.mensaje);
        categoria = otra.categoria;
        prioridad = otra.prioridad;
    }
    return *this;
}
