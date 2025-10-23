#include "usuarioPremium.h"
#include <iostream>
#include <cstring>
using namespace std;

UsuarioPremium::UsuarioPremium() : Usuario(), cantidadFavoritos(0), siguiente(nullptr) {
    memset(capacidadFavoritos, 0, sizeof(capacidadFavoritos));
}

UsuarioPremium::UsuarioPremium(const char* nick, const char* tipo, const char* ciudad, const char* pais, const char* fecha)
    : Usuario(nick, tipo, ciudad, pais, fecha), cantidadFavoritos(0), siguiente(nullptr) {
    memset(capacidadFavoritos, 0, sizeof(capacidadFavoritos));
}

UsuarioPremium::UsuarioPremium(const UsuarioPremium& otro)
    : Usuario(otro), cantidadFavoritos(otro.cantidadFavoritos), siguiente(nullptr) {
    memcpy(capacidadFavoritos, otro.capacidadFavoritos, sizeof(capacidadFavoritos));
}

UsuarioPremium::~UsuarioPremium() {}

int UsuarioPremium::getCalidadAudio() const {
    return 320;
}

int UsuarioPremium::getCantidadFavoritos() const {
    return cantidadFavoritos;
}

UsuarioPremium* UsuarioPremium::getSiguiente() const {
    return siguiente;
}

void UsuarioPremium::setSiguiente(UsuarioPremium* usuario) {
    siguiente = usuario;
}

void UsuarioPremium::editarFavoritos() {
    cout << "Editar lista de favoritos (función mínima implementada)" << endl;
}

void UsuarioPremium::seguirLista(UsuarioPremium* otroUsuario) {
    cout << "Seguir lista de otro usuario premium: " << otroUsuario->getNickname() << endl;
}

void UsuarioPremium::ajustarLista() {
    cout << "Ajustando lista de favoritos..." << endl;
}

bool UsuarioPremium::eliminarFavorito(int indice) {
    if (indice < 0 || indice >= cantidadFavoritos) return false;
    cout << "Eliminando favorito en índice " << indice << endl;
    return true;
}

void UsuarioPremium::mostrarInfo() const {
    cout << "Usuario Premium: " << getNickname() << ", Ciudad: " << getCiudad()
    << ", Pais: " << getPais() << ", Fecha de registro: " << getFechaDeRegistro()
    << ", Favoritos: " << cantidadFavoritos << endl;
}

UsuarioPremium& UsuarioPremium::operator=(const UsuarioPremium& otro) {
    if (this != &otro) {
        Usuario::operator=(otro);
        cantidadFavoritos = otro.cantidadFavoritos;
        memcpy(capacidadFavoritos, otro.capacidadFavoritos, sizeof(capacidadFavoritos));
        siguiente = nullptr;
    }
    return *this;
}
