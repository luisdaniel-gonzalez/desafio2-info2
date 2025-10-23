#include "publicidad.h"
#include <iostream>
#include <cstring>
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
