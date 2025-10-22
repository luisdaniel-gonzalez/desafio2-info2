#include <iostream>
#include "usuario.h"
#include "usuario_estandar.h"
// #include "usuarioPremium.h"

using namespace std;

int main()
{
    int opcion;
    do {
        cout << "1. Mostrar info usuario estandar\n";
        cout << "2. Reproducir canción (estándar)\n";
        cout << "3. Mostrar info usuario premium\n";
        cout << "4. Gestionar favoritos (premium)\n";
        cout << "0. Salir\n";
        cin >> opcion;

        switch(opcion) {
        case 1: user1.mostrarInfo(); break;
        case 2:
            user1.incrementarReproduccion();
            if(user1.mostrarPublicidad())
                cout << "Anuncio!\n";
            break;
        case 3: user2.mostrarInfo(); break;
        case 4: user2.agregarFavorito(...); break;
        }

    } while(opcion != 0);

}
