#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "plataforma.h"
#include "publicidad.h"
#include "usuarioEstandar.h"
#include "usuarioPremium.h"
#include "album.h"
#include "cancion.h"
#include "creditos.h"
#include "artista.h"

Plataforma plataforma;
Cancion cancion;
Album album;

using namespace std;

class HistorialCanciones {
private:
    const Cancion* canciones[5];
    int inicio, fin, cantidad;

public:
    HistorialCanciones() : inicio(0), fin(0), cantidad(0) {}

    void agregar(const Cancion* c) {
        canciones[fin] = c;
        fin = (fin + 1) % 5;
        if (cantidad < 5) cantidad++;
        else inicio = (inicio + 1) % 5;
    }

    const Cancion* retroceder(int pasos) {
        if (pasos >= cantidad) return nullptr;
        int idx = (fin - 1 - pasos + 5) % 5;
        return canciones[idx];
    }

    int getCantidad() const { return cantidad; }
};



void simularReproduccion(Plataforma& plataforma, Usuario* usuario,
                         Cancion* canciones, int numCanciones,
                         Album* albumes, int numAlbumes,
                         Artista* artistas, int numArtistas) {

    const int MAX_CANCIONES = 5;
    int cancionesReproducidas = 0;
    int indiceCancionActual = 0;
    bool reproduciendo = true;
    bool modoRepetir = false;
    HistorialCanciones historial;

    cout << "\n **** REPRODUCIENDO ****" << endl;

    while (cancionesReproducidas < MAX_CANCIONES && reproduciendo) {

        Cancion* cancionActual = &canciones[indiceCancionActual];
        Album* albumActual = nullptr;
        Artista* artistaActual = nullptr;

        if (numAlbumes > 0) albumActual = &albumes[0];
        if (numArtistas > 0) artistaActual = &artistas[0];

        if (!modoRepetir) {
            historial.agregar(cancionActual);
        }

        for (int i = 0; i < numAlbumes; i++) {
            if (cancionActual->getIdAlbum() == albumes[i].getIdAlbum()) {
                albumActual = &albumes[i];
                break;
            }
        }

        plataforma.mostrarReproduccion(
            "Publicidad de ejemplo",
            'A',
            artistaActual ? artistaActual->getNombre().c_str() : "Desconocido",
            albumActual ? albumActual->getNombre().c_str() : "Sin álbum",
            albumActual ? albumActual->getPortada().c_str() : "sin_portada.png",
            cancionActual->getNombre().c_str(),
            cancionActual->getRutaBase().c_str(),
            cancionActual->getDuracion(),
            modoRepetir,
            usuario
            );

        this_thread::sleep_for(chrono::seconds(3));

        if (!modoRepetir) {
            cancionesReproducidas++;
            indiceCancionActual = (indiceCancionActual + 1) % numCanciones;
        }

        if (cancionesReproducidas > 0 && cancionesReproducidas % 3 == 0) {
            if (modoRepetir) {
                cout << "Repetir: Desactivado automaticamente" << endl;
                modoRepetir = false;
            }
        }
    }

    cout << "\n*** REPRODUCCION TERMINADA ****" << endl;
}

int main() {

    srand(time(0));

    Plataforma plataforma;

    plataforma.cargarDatos("debug/dataSet/usuarios.txt", plataforma);


    Cancion* canciones = nullptr;
    int numCanciones = 0;
    cancion.cargarCanciones("debug/dataSet/cancion.txt", canciones, numCanciones);

    Album* albumes = nullptr;
    int numAlbumes = 0;
    album.cargarAlbumes("debug/dataSet/albumes.txt", albumes, numAlbumes);

    Publicidad* publicidad = new Publicidad();
    int numPublicidad = 0;
    publicidad->cargarPublicidades("debug/dataSet/publicidad.txt", plataforma, numPublicidad);


    Artista artista;
    Artista* artistas = nullptr;
    int numArtistas = 0;
    artista.cargarArtistas("debug/dataSet/artistas.txt", artistas, numArtistas);


    Creditos* creditos = nullptr;
    int numCreditos = 0;
    creditos->cargarCreditos("debug/dataSet/creditos.txt", creditos, numCreditos);


    char opcion = 0;
    Usuario* usuarioActual = nullptr;


    do {
        cout << "\n************************************" << endl;
        cout << "          UdeaTunes " << endl;
        cout << "************************************" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
        case '1': {
            char nickname[50];
            char contrasena[20];
            cout << "\nIngrese su nickname: ";
            cin >> nickname;
            cout << "Ingrese su contrasena: ";
            cin >> contrasena;

            if (plataforma.iniciarSesion(nickname, contrasena)) {
                usuarioActual = plataforma.getUsuarioActual();
                cout << "\nBienvenido " << usuarioActual->getNickname() << endl;
                cout << "Tipo de membresia: " << usuarioActual->getTipoDeMembresia() << endl;

                this_thread::sleep_for(chrono::seconds(3));
                simularReproduccion(plataforma, usuarioActual,
                                    canciones, numCanciones,
                                    albumes, numAlbumes,
                                    artistas, numArtistas);

                plataforma.cerrarSesion();
                usuarioActual = nullptr;
            } else {
                cout << "Usuario no encontrado" << endl;
            }
            break;
        }

        case '2':
            cout << "\nTe esperamos de vuelta pronto, UdeATunero" << endl;
            break;

        default:
            cout << "Opcion invalida" << endl;
        }

    } while(opcion != '2');

    plataforma.medirConsumoRecursos(1);

    delete[] canciones;
    delete[] albumes;
    delete[] artistas;
    if (creditos != nullptr) delete[] creditos;

    return 0;
}

