#include "plataforma.h"
//#include "artista.h"
#include <iostream>
#include <cstring>
using namespace std;

Plataforma::Plataforma() {
    numUsuarios = 0;
    numArtistas = 0;
    numPublicidades = 0;
    usuarioActual = nullptr;
    ultimaPublicidadMostrada = -1;
}

Plataforma::~Plataforma() {
    for (int i = 0; i < numUsuarios; i++) {
        delete usuarios[i];
    }
    for (int i = 0; i < numArtistas; i++) {
     //   delete artistas[i];
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
    if (numPublicidades >= 50) return false;
    publicidades[numPublicidades++] = pub;
    return true;
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

bool Plataforma::iniciarSesion(const char* nickname) {
    Usuario* u = obtenerUsuario(nickname);
    if (u) {
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

/*void Plataforma::mostrarArtistas() {
    cout << "Artistas registrados:" << endl;
    for (int i = 0; i < numArtistas; i++) // Implementar de Jean
        artistas[i]->mostrarInfo();
}*/

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
                                     int duracionSegundos) {

    cout << "*****************************" << endl;

    if (mensajePublicidad != nullptr && mensajePublicidad[0] != '\0') {
        cout << "Mensaje publicitario: " << mensajePublicidad << endl;
        cout << "Categoria del mensaje: " << categoriaPublicidad << endl;
        cout << "*****************************" << endl;
    }

    cout << "Cantante: " << cantante << endl;
    cout << "Album: " << album << endl;
    cout << "Portada: " << rutaPortada << endl;
    cout << "Titulo de la cancion: " << tituloCancion << endl;
    cout << "Ruta del audio: " << rutaAudio << endl;
    cout << "Duracion: " << duracionSegundos << " segundos" << endl;

    cout << "Opciones de reproduccion:" << endl;
    cout << "1.- Reproducir" << endl;
    cout << "2.- Detener" << endl;

    if (usuarioActual && strcmp(usuarioActual->getTipoDeMembresia(), "premium") == 0) {
        cout << "3.- Siguiente" << endl;
        cout << "4.- Anterior" << endl;
        cout << "5.- Repetir canción" << endl;
    }

    cout << "*****************************" << endl;
}


int Plataforma::getCantidadUsuarios() const { return numUsuarios; }
int Plataforma::getCantidadArtistas() const { return numArtistas; }
int Plataforma::getCantidadPublicidades() const { return numPublicidades; }
