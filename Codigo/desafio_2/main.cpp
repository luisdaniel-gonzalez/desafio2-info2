#include <iostream>
#include "plataforma.h"

using namespace std;

int main() {

    Plataforma main;

    const char* mensajePublicidad = "Compra el curso del profe Augusto";
    char categoriaPublicidad = 'A';
    const char* cantante = "Luis Fonsi";
    const char* album = "Vida";
    const char* rutaPortada = "C:/Musica/Vida.jpg";
    const char* tituloCancion = "Despacito";
    const char* rutaAudio = "C:/Musica/Despacito.mp3";
    int duracionSegundos = 230;

    main.mostrarReproduccion(mensajePublicidad,
                                     categoriaPublicidad,
                                     cantante,
                                     album,
                                     rutaPortada,
                                     tituloCancion,
                                     rutaAudio,
                                     duracionSegundos);

    return 0;
}

