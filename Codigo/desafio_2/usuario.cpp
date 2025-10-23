#include <iostream>
#include "usuario.h"
#include <cstring>

using namespace std;

char *Usuario::getContrasena() const
{
    return contrasena;
}

char* Usuario::copiarString(const char* str) {

    if (str == nullptr) {
        return nullptr;
    }

    int longitud = 0;
    while (str[longitud] != '\0') {
        longitud++;
    }

    char* nuevo = new char[longitud + 1];
    for (int i = 0; i < longitud; i++) {
        nuevo[i] = str[i];
    }
    nuevo[longitud] = '\0';

    return nuevo;
}

Usuario::Usuario() {
    nickname = nullptr;
    tipoDeMembresia = nullptr;
    ciudad = nullptr;
    pais = nullptr;
    fechaDeRegistro = nullptr;
}

Usuario::Usuario(const char* nick, const char* tipo, const char* ciudad,
                 const char* pais, const char* fecha) {
    nickname = copiarString(nick);
    tipoDeMembresia = copiarString(tipo);
    this->ciudad = copiarString(ciudad);
    this->pais = copiarString(pais);
    fechaDeRegistro = copiarString(fecha);
}

Usuario::Usuario(const Usuario& otro) {
    nickname = copiarString(otro.nickname);
    tipoDeMembresia = copiarString(otro.tipoDeMembresia);
    ciudad = copiarString(otro.ciudad);
    pais = copiarString(otro.pais);
    fechaDeRegistro = copiarString(otro.fechaDeRegistro);
}

Usuario::~Usuario() {
    if (nickname != nullptr) delete[] nickname;
    if (tipoDeMembresia != nullptr) delete[] tipoDeMembresia;
    if (ciudad != nullptr) delete[] ciudad;
    if (pais != nullptr) delete[] pais;
    if (fechaDeRegistro != nullptr) delete[] fechaDeRegistro;
}

const char* Usuario::getNickname() const {
    return nickname;
}

const char* Usuario::getTipoDeMembresia() const {
    return tipoDeMembresia;
}

const char* Usuario::getCiudad() const {
    return ciudad;
}

const char* Usuario::getPais() const {
    return pais;
}

const char* Usuario::getFechaDeRegistro() const {
    return fechaDeRegistro;
}

void Usuario::setNickname(const char* nick) {
    if (nickname != nullptr) {
        delete[] nickname;
    }
    nickname = copiarString(nick);
}

void Usuario::setTipoDeMembresia(const char* tipo) {
    if (tipoDeMembresia != nullptr) {
        delete[] tipoDeMembresia;
    }
    tipoDeMembresia = copiarString(tipo);
}

void Usuario::setCiudad(const char* ciudad) {
    if (this->ciudad != nullptr) {
        delete[] this->ciudad;
    }
    this->ciudad = copiarString(ciudad);
}

void Usuario::setPais(const char* pais) {
    if (this->pais != nullptr) {
        delete[] this->pais;
    }
    this->pais = copiarString(pais);
}

void Usuario::setFechaDeRegistro(const char* fecha) {
    if (fechaDeRegistro != nullptr) {
        delete[] fechaDeRegistro;
    }
    fechaDeRegistro = copiarString(fecha);
}

void Usuario::mostrarInfo() const {
    cout << "Nickname: " << (nickname ? nickname : "N/A") << endl;
    cout << "Tipo de membresia: " << (tipoDeMembresia ? tipoDeMembresia : "N/A") << endl;
    cout << "Ciudad: " << (ciudad ? ciudad : "N/A") << endl;
    cout << "Pais: " << (pais ? pais : "N/A") << endl;
    cout << "Fecha de registro: " << (fechaDeRegistro ? fechaDeRegistro : "N/A") << endl;
}

void Usuario::reproduccionAleatoria() {
    cout << "Reproduccion aleatoria iniciada..." << endl;
}

void Usuario::mostrarPublicidad() {
}

void Usuario::iniciaSesion() {
    cout << "Usuario " << (nickname ? nickname : "desconocido") << " ha iniciado sesion" << endl;
}

bool Usuario::operator==(const Usuario& otro) const {
    if (nickname == nullptr || otro.nickname == nullptr) {
        return false;
    }

    int i = 0;
    while (nickname[i] != '\0' && otro.nickname[i] != '\0') {
        if (nickname[i] != otro.nickname[i]) {
            return false;
        }
        i++;
    }
    return nickname[i] == otro.nickname[i];
}

Usuario& Usuario::operator=(const Usuario& otro) {
    if (this != &otro) {
        if (nickname != nullptr) delete[] nickname;
        if (tipoDeMembresia != nullptr) delete[] tipoDeMembresia;
        if (ciudad != nullptr) delete[] ciudad;
        if (pais != nullptr) delete[] pais;
        if (fechaDeRegistro != nullptr) delete[] fechaDeRegistro;

        nickname = copiarString(otro.nickname);
        tipoDeMembresia = copiarString(otro.tipoDeMembresia);
        ciudad = copiarString(otro.ciudad);
        pais = copiarString(otro.pais);
        fechaDeRegistro = copiarString(otro.fechaDeRegistro);
    }
    return *this;
}
