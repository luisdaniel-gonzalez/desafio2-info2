#include "usuarioEstandar.h"
#include <iostream>
#include <cstring>
using namespace std;

UsuarioEstandar::UsuarioEstandar() : Usuario(), anuncios(0) {}

UsuarioEstandar::UsuarioEstandar(const char* nick,const char* contrasena, const char* tipo, const char* ciudad, const char* pais, const char* fecha)
    : Usuario(nick, contrasena, tipo, ciudad, pais, fecha), anuncios(0) {}

UsuarioEstandar::UsuarioEstandar(const UsuarioEstandar& otro)
    : Usuario(otro), anuncios(otro.anuncios) {}

UsuarioEstandar::~UsuarioEstandar() {}

int UsuarioEstandar::getAnuncios() const {
    return anuncios;
}

int UsuarioEstandar::getCalidadAudio() const {
    return 128;
}

void UsuarioEstandar::setAnuncios(int cantidad) {
    anuncios = cantidad;
}

void UsuarioEstandar::reproducirMusica() {
    cout << "Reproduciendo musica para usuario estandar: " << getNickname() << endl;
}

void UsuarioEstandar::mostrarInfo() const {
    cout << "Usuario estandar: " << getNickname() << ", Ciudad: " << getCiudad()
         << ", Pais: " << getPais() << ", Fecha de registro: " << getFechaDeRegistro() << endl;
}

void UsuarioEstandar::mostrarPublicidad() {
    cout << "Mostrando publicidad: " << anuncios << endl;
}

UsuarioEstandar& UsuarioEstandar::operator=(const UsuarioEstandar& otro) {
    if (this != &otro) {
        Usuario::operator=(otro);
        anuncios = otro.anuncios;
    }
    return *this;
}
