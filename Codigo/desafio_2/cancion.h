#ifndef CANCION_H
#define CANCION_H
#include <iostream>
#include <string>
using namespace std;
#include "creditos.h"

class cancion
{
private:
    string nombre;
    int id;
    float duracion;
    string ruta;
    int reproducciones;
    creditos *creditos;
    int numCreditos;

public:
    cancion();
    cancion(string nom,int id, float dur,string rut);
    cancion(const Cancion &copia);

    ~Cancion();

    void agregarCredito(const creditos &c);
    void reproducir(int calidad) const;
    void mostrar() const;

    int getId() const;
    string getNombre() const;
    float getDuracion() const;
    int getReproducciones() const;
    string Ruta() const;
};

#endif // CANCION_H
