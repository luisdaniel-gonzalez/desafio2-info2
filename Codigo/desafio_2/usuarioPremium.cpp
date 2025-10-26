#include "usuarioPremium.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

UsuarioPremium::UsuarioPremium() : Usuario(), cantidadFavoritos(0), siguiente(nullptr) {
    memset(capacidadFavoritos, 0, sizeof(capacidadFavoritos));
    listaDeFavoritos = nullptr;
}

UsuarioPremium::UsuarioPremium(const char* nick, const char* contrasena, const char* tipo,
                               const char* ciudad, const char* pais, const char* fecha)
    : Usuario(nick, contrasena, tipo, ciudad, pais, fecha), cantidadFavoritos(0), siguiente(nullptr) {
    memset(capacidadFavoritos, 0, sizeof(capacidadFavoritos));
    listaDeFavoritos = nullptr;
}

UsuarioPremium::UsuarioPremium(const UsuarioPremium& otro)
    : Usuario(otro), cantidadFavoritos(otro.cantidadFavoritos), siguiente(nullptr) {
    memcpy(capacidadFavoritos, otro.capacidadFavoritos, sizeof(capacidadFavoritos));

    if (cantidadFavoritos > 0) {
        listaDeFavoritos = new Cancion*[cantidadFavoritos];
        for (int i = 0; i < cantidadFavoritos; i++) {
            listaDeFavoritos[i] = otro.listaDeFavoritos[i];
        }
    } else {
        listaDeFavoritos = nullptr;
    }
}

UsuarioPremium::~UsuarioPremium() {
    delete[] listaDeFavoritos;  // ← AGREGAR
}

int UsuarioPremium::getCalidadAudio() const {
    return 320;
}

int UsuarioPremium::getCantidadFavoritos() const {
    return cantidadFavoritos;
}

Cancion** UsuarioPremium::getListaDeFavoritos() const {
    return listaDeFavoritos;
}

UsuarioPremium* UsuarioPremium::getSiguiente() const {
    return siguiente;
}

void UsuarioPremium::setSiguiente(UsuarioPremium* usuario) {
    siguiente = usuario;
}

void UsuarioPremium::editarFavoritos() {
    if (cantidadFavoritos == 0) {
        cout << "\nNo tienes canciones en favoritos" << endl;
        return;
    }

    cout << "\n**** TUS FAVORITOS ****" << endl;
    for (int i = 0; i < cantidadFavoritos; i++) {
        cout << i + 1 << ". " << listaDeFavoritos[i]->getNombre()
        << " (" << listaDeFavoritos[i]->getDuracion() << " min)" << endl;
    }

    cout << "\nOpciones:" << endl;
    cout << "1. Eliminar una cancion" << endl;
    cout << "2. Volver" << endl;
    cout << "Seleccione: ";

    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        cout << "Numero de cancion a eliminar: ";
        int num;
        cin >> num;
        eliminarFavorito(num - 1);
    }
}

void UsuarioPremium::seguirLista(UsuarioPremium* otroUsuario) {
    if (!otroUsuario) {
        cout << "Usuario no encontrado" << endl;
        return;
    }

    cout << "\n**** Lista de " << otroUsuario->getNickname() << " ****" << endl;

    if (otroUsuario->getCantidadFavoritos() == 0) {
        cout << "Este usuario no tiene canciones en favoritos" << endl;
        return;
    }

    Cancion** susFavoritos = otroUsuario->getListaDeFavoritos();
    for (int i = 0; i < otroUsuario->getCantidadFavoritos(); i++) {
        cout << i + 1 << ". " << susFavoritos[i]->getNombre()
        << " (" << susFavoritos[i]->getDuracion() << " min)" << endl;
    }

    cout << "\nDeseas copiar esta lista a tus favoritos? (1=Si, 0=No): ";
    int copiar;
    cin >> copiar;

    if (copiar == 1) {
        for (int i = 0; i < otroUsuario->getCantidadFavoritos(); i++) {
            agregarFavorito(susFavoritos[i]);
        }
        cout << "Lista copiada exitosamente!" << endl;
    }
}

void UsuarioPremium::ajustarLista() {
    cout << "Ajustando lista de favoritos..." << endl;
    editarFavoritos();
}

bool UsuarioPremium::eliminarFavorito(int indice) {
    if (indice < 0 || indice >= cantidadFavoritos) {
        cout << "Indice invalido" << endl;
        return false;
    }

    if (cantidadFavoritos == 1) {
        delete[] listaDeFavoritos;
        listaDeFavoritos = nullptr;
        cantidadFavoritos = 0;
        cout << "Cancion eliminada de favoritos" << endl;
        return true;
    }

    Cancion** nuevoArr = new Cancion*[cantidadFavoritos - 1];

    int j = 0;
    for (int i = 0; i < cantidadFavoritos; i++) {
        if (i != indice) {
            nuevoArr[j++] = listaDeFavoritos[i];
        }
    }

    delete[] listaDeFavoritos;
    listaDeFavoritos = nuevoArr;
    cantidadFavoritos--;

    cout << "Cancion eliminada de favoritos" << endl;
    return true;
}

bool UsuarioPremium::agregarFavorito(Cancion* cancion) {
    if (!cancion) return false;

    for (int i = 0; i < cantidadFavoritos; i++) {
        if (listaDeFavoritos[i]->getId() == cancion->getId()) {
            cout << "La cancion ya esta en favoritos" << endl;
            return false;
        }
    }

    Cancion** nuevoArr = new Cancion*[cantidadFavoritos + 1];

    for (int i = 0; i < cantidadFavoritos; i++) {
        nuevoArr[i] = listaDeFavoritos[i];
    }

    nuevoArr[cantidadFavoritos] = cancion;

    delete[] listaDeFavoritos;
    listaDeFavoritos = nuevoArr;
    cantidadFavoritos++;

    cout << "Cancion agregada a favoritos: " << cancion->getNombre() << endl;
    return true;
}

Cancion* UsuarioPremium::operator[](int indice) const {
    if (indice < 0 || indice >= cantidadFavoritos) {
        return nullptr;
    }
    return listaDeFavoritos[indice];
}

void UsuarioPremium::mostrarInfo() const {
    cout << "Usuario Premium: " << getNickname() << ", Ciudad: " << getCiudad()
    << ", Pais: " << getPais() << ", Fecha de registro: " << getFechaDeRegistro()
    << ", Favoritos: " << cantidadFavoritos << endl;
}

UsuarioPremium& UsuarioPremium::operator=(const UsuarioPremium& otro) {
    if (this != &otro) {
        Usuario::operator=(otro);

        delete[] listaDeFavoritos;

        cantidadFavoritos = otro.cantidadFavoritos;
        memcpy(capacidadFavoritos, otro.capacidadFavoritos, sizeof(capacidadFavoritos));

        if (cantidadFavoritos > 0) {
            listaDeFavoritos = new Cancion*[cantidadFavoritos];
            for (int i = 0; i < cantidadFavoritos; i++) {
                listaDeFavoritos[i] = otro.listaDeFavoritos[i];
            }
        } else {
            listaDeFavoritos = nullptr;
        }

        siguiente = nullptr;
    }
    return *this;
}

void UsuarioPremium::cargarListas(const string& nombreArchivo,
                                  UsuarioPremium** usuarios, int numUsuarios,
                                  Cancion* canciones, int numCanciones) {

    ifstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout << "Error: No se pudo abrir " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        // Formato: dueñoNickname|nombreLista|idCancion1,idCancion2,idCancion3|
        int p1 = linea.find('|');
        int p2 = linea.find('|', p1 + 1);
        int p3 = linea.find('|', p2 + 1);
        int p4 = linea.find('|', p3 + 1);
        int p5 = linea.find('|', p4 + 1);

        string nickname = linea.substr(0, p1);
        string idCanciones = linea.substr(p4 + 1, p5 - p4 - 1);

        UsuarioPremium* usuario = nullptr;
        for (int i = 0; i < numUsuarios; i++) {
            if (strcmp(usuarios[i]->getNickname(), nickname.c_str()) == 0) {
                usuario = usuarios[i];
                break;
            }
        }

        if (!usuario) {
            cout << "Usuario no encontrado" << endl;
            continue;
        }

        size_t pos = 0;
        int cancionesAgregadas = 0;

        while (pos < idCanciones.length()) {
            size_t coma = idCanciones.find(',', pos);
            if (coma == string::npos) coma = idCanciones.length();

            string idStr = idCanciones.substr(pos, coma - pos);

            if (!idStr.empty()) {
                int idCancion = atoi(idStr.c_str());


                for (int i = 0; i < numCanciones; i++) {
                    if (canciones[i].getId() == idCancion) {
                        if (usuario->agregarFavorito(&canciones[i])) {
                            cancionesAgregadas =  cancionesAgregadas + 1;
                }
                break;
            }
        }
    }

    pos = coma + 1;

        }

        cout << "Lista cargada para " << nickname << endl;
    }

    archivo.close();
}

