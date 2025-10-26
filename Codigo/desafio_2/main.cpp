#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "plataforma.h"
#include "publicidad.h"
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
                         Artista* artistas, int numArtistas, bool modoAleatorio) {

    const int MAX_CANCIONES = 5;
    int cancionesReproducidas = 0;
    int indiceCancionActual = 0;
    bool reproduciendo = true;
    bool modoRepetir = false;
    HistorialCanciones historial;

    cout << "\n **** REPRODUCIENDO ****" << endl;

    while (cancionesReproducidas < MAX_CANCIONES && reproduciendo) {

        if (modoAleatorio) {
            indiceCancionActual = rand() % numCanciones;
        }

        Cancion* cancionActual = &canciones[indiceCancionActual];
        Album* albumActual = nullptr;
        Artista* artistaActual = nullptr;

        if (numAlbumes > 0) albumActual = &albumes[0];
        if (numArtistas > 0) artistaActual = &artistas[0];

        if (!modoRepetir) {
            historial.agregar(cancionActual);
        }

        for (int i = 0; i < numAlbumes; i++) {
            if (albumes[i].getIdAlbum() == cancionActual->getIdAlbum()) {
                albumActual = &albumes[i];
                break;
            }
        }


        int idArtista = cancionActual->getId() / 10000;
        for (int i = 0; i < numArtistas; i++) {
            if (artistas[i].getCodigo() == idArtista) {
                artistaActual = &artistas[i];
                break;
            }
        }

        string nombreCantante;

        if (cancionActual->getCantante().empty()) {
            nombreCantante = "Artista Desconocido";
        } else {
            nombreCantante = cancionActual->getCantante();
        }

        string rutaAudio;

        if (strcmp(usuario->getTipoDeMembresia(), "premium") == 0) {
            rutaAudio = cancionActual->getRuta320().c_str();
        } else {
            rutaAudio = cancionActual->getRuta128().c_str();
        }


        plataforma.mostrarReproduccion(
            "Publicidad de ejemplo",
            'A',
             nombreCantante.c_str(),
            albumActual ? albumActual->getNombre().c_str() : "Album Desconocido",
            cancionActual ? cancionActual->getRutaPortada().c_str() : "sin_portada.jpg",
            cancionActual->getNombre().c_str(),
            rutaAudio.c_str(),
            cancionActual->getDuracion(),
            modoRepetir,
            usuario,
            cancionesReproducidas
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


    Album* albumes = nullptr;
    int numAlbumes = 0;
    album.cargarAlbumes("debug/dataSet/albumes.txt", albumes, numAlbumes);

    Cancion* canciones = nullptr;
    int numCanciones = 0;
    cancion.cargarCanciones("debug/dataSet/cancion.txt", canciones, numCanciones, albumes, numAlbumes);

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
        cout << "1.- Iniciar sesion" << endl;
        cout << "2.- Salir" << endl;
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

                char opcionSesion = 0;
                do {

                    cout << "1.- Reproducir musica" << endl;

                    if (strcmp(usuarioActual->getTipoDeMembresia(), "premium") == 0) {
                        cout << "2.- Ver mis favoritos" << endl;
                        cout << "3.- Agregar cancion a favoritos" << endl;
                        cout << "4.- Seguir a otro usuario" << endl;
                        cout << "5.- Cerrar sesion" << endl;

                    } else {
                        cout << "2.- Cerrar sesion" << endl;
                    }

                    cout << "Seleccione: ";
                    cin >> opcionSesion;

                    if (strcmp(usuarioActual->getTipoDeMembresia(), "premium") == 0) {
                        UsuarioPremium* premium = dynamic_cast<UsuarioPremium*>(usuarioActual); // Hacemos un casteo dinamico para obtener por herencia

                        switch(opcionSesion) {
                        case '1':

                            char aleatorioModo;
                            cout << "\nDesea reproducir de forma aleatoria? (s/n): ";
                            cin >> aleatorioModo;

                            bool aleatorio;
                            if (aleatorioModo == 's'){
                                aleatorio = true;
                            } else {
                                aleatorio = false;
                            }

                            simularReproduccion(plataforma, usuarioActual,
                                                canciones, numCanciones,
                                                albumes, numAlbumes,
                                                artistas, numArtistas, aleatorio);
                            break;

                        case '2':
                            premium->editarFavoritos();
                            break;

                        case '3':
                            cout << "\nCanciones disponibles:" << endl;
                            int maxMostrar;
                            maxMostrar = (numCanciones < 10) ? numCanciones : 10;
                            for (int i = 0; i < maxMostrar; i++) {
                                cout << i + 1 << ". " << canciones[i].getNombre() << endl;
                            }
                            cout << "Seleccione numero (1-" << maxMostrar << "): ";
                            int num;
                            cin >> num;

                            if (num > 0 && num <= maxMostrar) {
                                premium->agregarFavorito(&canciones[num - 1]);
                            } else {
                                cout << "Opcion invalida" << endl;
                            }
                            break;

                        case '4':
                        {
                            cout << "\nIngrese nickname del usuario a seguir: ";
                            char nickBuscar[50];
                            cin >> nickBuscar;

                            Usuario* usuarioEncontrado = plataforma.obtenerUsuario(nickBuscar);

                            if (usuarioEncontrado &&
                                strcmp(usuarioEncontrado->getTipoDeMembresia(), "premium") == 0 &&
                                strcmp(usuarioEncontrado->getNickname(), usuarioActual->getNickname()) != 0) {

                                UsuarioPremium* otroPremium = (UsuarioPremium*)usuarioEncontrado;
                                premium->seguirLista(otroPremium);

                            } else {
                                cout << "Usuario no encontrado o no es Premium" << endl;
                            }
                        }
                        break;
                        case '5':
                            cout << "Cerrando sesion...\n" << endl;
                            plataforma.medirConsumoRecursos();
                            break;

                        default:
                            cout << "Opcion invalida" << endl;
                        }
                    } else {
                        switch(opcionSesion) {
                        case '1':

                            char aleatorioModo;
                            cout << "\nDesea reproducir de forma aleatoria? (s/n): ";
                            cin >> aleatorioModo;

                            bool aleatorio;
                            if (aleatorioModo == 's'){
                                aleatorio = true;
                            } else {
                                aleatorio = false;
                            }

                            simularReproduccion(plataforma, usuarioActual,
                                                canciones, numCanciones,
                                                albumes, numAlbumes,
                                                artistas, numArtistas, aleatorio);
                            break;

                        case '2':
                            cout << "Cerrando sesion...\n" << endl;
                            plataforma.medirConsumoRecursos();
                            break;

                        default:
                            cout << "Opcion invalida" << endl;
                        }
                    }

                } while (opcionSesion != '5' && opcionSesion != '2');

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

    delete[] canciones;
    delete[] albumes;
    delete[] artistas;
    if (creditos != nullptr) delete[] creditos;
    delete publicidad;

    return 0;
}

