#include "plataforma.h"
#include <iostream>
#include <cstring>
#include "usuario.h"
#include "usuarioEstandar.h"
#include "usuarioPremium.h"
#include <fstream>
#include "publicidad.h"

using namespace std;

Plataforma::Plataforma() {
    numUsuarios = 0;
    numArtistas = 0;
    numPublicidades = 0;
    contadorCanciones = 0;
    usuarioActual = nullptr;
    ultimaPublicidadMostrada = -1;
}

Plataforma::~Plataforma() {
    for (int i = 0; i < numUsuarios; i++) {
        delete usuarios[i];
    }
    for (int i = 0; i < numArtistas; i++) {
        delete artistas[i];
    }
    for (int i = 0; i < numPublicidades; i++) {
        delete publicidades[i];
    }
}

char* Plataforma::copiarString(const char* str) {
    if (!str) return nullptr;
    char* nuevo = new char[strlen(str)+1];
    strcpy(nuevo, str);
    return nuevo;
}

int Plataforma::compararStrings(const char* str1, const char* str2) const {
    return strcmp(str1, str2);
}

bool Plataforma::agregarUsuario(Usuario* usuario) {
    if (numUsuarios >= 100) return false;
    usuarios[numUsuarios++] = usuario;
    return true;
}

bool Plataforma::agregarPublicidad(Publicidad* pub) {
    if (numPublicidades < 50) {
        publicidades[numPublicidades++] = pub;
        return true;
    }
    return false;
}

bool Plataforma::buscarUsuario(const char* nickname) {
    for (int i = 0; i < numUsuarios; i++)
        if (compararStrings(usuarios[i]->getNickname(), nickname) == 0)
            return true;
    return false;
}

Usuario* Plataforma::obtenerUsuario(const char* nickname) {
    for (int i = 0; i < numUsuarios; i++)
        if (compararStrings(usuarios[i]->getNickname(), nickname) == 0)
            return usuarios[i];
    return nullptr;
}


Usuario* Plataforma::obtenerContrasena(const char* contrasena) {
    for (int i = 0; i < numUsuarios; i++)
        if (compararStrings(usuarios[i]->getContrasena(), contrasena) == 0)
            return usuarios[i];
    return nullptr;
}

bool Plataforma::iniciarSesion(const char* nickname, const char* contrasena) {
    Usuario* u = obtenerUsuario(nickname);
    Usuario* p = obtenerContrasena(contrasena);
    if (u && p != nullptr) {
        usuarioActual = u;
        return true;
    }
    return false;
}

void Plataforma::cerrarSesion() {
    usuarioActual = nullptr;
}

Usuario* Plataforma::getUsuarioActual() const {
    return usuarioActual;
}

void Plataforma::reproduccionAleatoria() {
    cout << "Reproduciendo canción aleatoria..." << endl;
    if (usuarioActual)
        cout << "Usuario: " << usuarioActual->getNickname() << endl;
}

void Plataforma::mostrarPublicidadPonderada() {
    if (numPublicidades == 0) {
        cout << "No hay publicidades disponibles." << endl;
        return;
    }

    int totalPonderacion = 0;
    for (int i = 0; i < numPublicidades; i++)
        totalPonderacion += publicidades[i]->getPrioridad();

    int valor = rand() % totalPonderacion;
    int acumulado = 0;
    int indiceSeleccionado = 0;

    for (int i = 0; i < numPublicidades; i++) {
        acumulado += publicidades[i]->getPrioridad();
        if (valor < acumulado) {
            indiceSeleccionado = i;
            break;
        }
    }

    cout << "Publicidad: " << publicidades[indiceSeleccionado]->getMensaje() << endl;
}

void Plataforma::mostrarUsuarios() {
    cout << "Usuarios registrados:" << endl;
    for (int i = 0; i < numUsuarios; i++)
        usuarios[i]->mostrarInfo();
}

void Plataforma::mostrarPublicidades() {
    cout << "Publicidades registradas:" << endl;
    for (int i = 0; i < numPublicidades; i++)
        publicidades[i]->mostrar();
}

void Plataforma::gestionarListaFavoritos() {
    if (!usuarioActual) {
        cout << "Debe iniciar sesion para gestionar favoritos." << endl;
        return;
    }
    cout << "Gestionando lista de favoritos de: " << usuarioActual->getNickname() << endl;
}

void Plataforma::cargarDatos(const string &nombreArchivo, Plataforma &plataforma) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout << "Error en nuestro sistema de usuarios" << endl;
        return;
    }

    string linea;

    int count = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        int p1 = linea.find('|');
        int p2 = linea.find('|', p1 + 1);
        int p3 = linea.find('|', p2 + 1);
        int p4 = linea.find('|', p3 + 1);
        int p5 = linea.find('|', p4 + 1);

        string nickname = linea.substr(0, p1);
        string contrasena = linea.substr(p1 + 1, p2 - p1 - 1);
        string membresia = linea.substr(p2 + 1, p3 - p2 - 1);
        string ciudad = linea.substr(p3 + 1, p4 - p3 - 1);
        string pais = linea.substr(p4 + 1, p5 - p4 - 1);
        string nacimiento = linea.substr(p5 + 1);

        Usuario* nuevoUsuario = nullptr;

        if (membresia == "premium") {
            nuevoUsuario = new UsuarioPremium(nickname.c_str(), contrasena.c_str(), membresia.c_str(),
                                              ciudad.c_str(), pais.c_str(), nacimiento.c_str());
        } else {
            nuevoUsuario = new UsuarioEstandar(nickname.c_str(), contrasena.c_str(), membresia.c_str(),
                                               ciudad.c_str(), pais.c_str(), nacimiento.c_str());
        }

        if (plataforma.agregarUsuario(nuevoUsuario)) {
            count = count + 1;
        }
    } archivo.close();
}

int Plataforma::calcularMemoriaTotal() const {
    int total = sizeof(*this);
    total += numUsuarios * sizeof(Usuario);
    total += numPublicidades * sizeof(Publicidad);
    total += numArtistas * sizeof(int);
    return total;
}

void Plataforma::medirConsumoRecursos(int iteraciones) const {
    int memoriaTotal = calcularMemoriaTotal();
    cout << endl;
    cout << "RECURSOS" << endl;
    cout << "Iteraciones realizadas: " << iteraciones << endl;
    cout << "Memoria total estimada: " << memoriaTotal << " bytes" << endl;
    cout << endl;
}

void Plataforma::mostrarReproduccion(const char* mensajePublicidad,
                                     char categoriaPublicidad,
                                     const char* cantante,
                                     const char* album,
                                     const char* rutaPortada,
                                     const char* tituloCancion,
                                     const char* rutaAudio,
                                     int duracionSegundos,
                                     bool modoRepetir,
                                     Usuario* usuario) {

    contadorCanciones = 0;

    if (strcmp(usuario->getTipoDeMembresia(), "estandar") == 0 &&
        contadorCanciones % 2 == 0 && contadorCanciones > 0) {
        mostrarPublicidadPonderada();
    }

    cout << "*****************************" << endl;

    if (strcmp(usuario->getTipoDeMembresia(), "estandar") == 0 &&
        contadorCanciones % 2 == 0 && contadorCanciones > 0) {
        cout << "*****************************" << endl;
    }


    if (strcmp(usuario->getTipoDeMembresia(), "premium") != 0) {
        cout << "\nESPACIO PUBLICITARIO" << endl;
        mostrarPublicidadPonderada();
        cout << endl;
    } else {
        cout << endl;
    }

    cout << "Cantante: " << cantante << endl;
    cout << "Album: " << album << endl;
    cout << "Portada: " << rutaPortada << endl;
    cout << "Titulo: " << tituloCancion << endl;
    cout << "Ruta del audio: " << rutaAudio << "-" << usuario->getCalidadAudio() << ".ogg" << endl;
    cout << "Duracion: " << duracionSegundos << " segundos" << endl;


    if (modoRepetir) {
        cout << "Repetir: ACTIVADO" << endl;
    }

    cout << "Opciones de reproduccion:" << endl;
    cout << "1.- Reproducir" << endl;
    cout << "2.- Detener" << endl;

    if (strcmp(usuario->getTipoDeMembresia(), "premium") == 0) {
        cout << "3.- Siguiente" << endl;
        cout << "4.- Anterior" << endl;
        cout << "5.- Repetir cancion" << endl;
    }
}



int Plataforma::getCantidadUsuarios() const { return numUsuarios; }
int Plataforma::getCantidadArtistas() const { return numArtistas; }
int Plataforma::getCantidadPublicidades() const { return numPublicidades; }
