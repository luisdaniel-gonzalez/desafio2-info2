#ifndef CREDITOS_H
#define CREDITOS_H
#include <string>
using namespace std;

class Creditos
{
private:
    string nombre;
    string apellido;
    string codigoSociedad;
    string rol;

public:
    Creditos();
    Creditos(string nom, string ape, string cod, string rol);
    Creditos(const Creditos &c);

    ~Creditos();

    void mostrar() const;

    string getNombre() const;
    string getApellido() const;
    string getcodigoSociedad() const;
    string getRol() const;
    void setNombre(const string &n);
    void setApellido(const string &a);
    void setcodigoSociedad(const string &s);
    void setRol(const string &r);
};

#endif // CREDITOS_H
