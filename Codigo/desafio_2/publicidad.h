#ifndef PUBLICIDAD_H
#define PUBLICIDAD_H

class Publicidad {
private:
    char* mensaje;
    char categoria;
    int prioridad;

    char* copiarString(const char* str);

public:

    Publicidad();
    Publicidad(const char* msg, char cat);
    Publicidad(const Publicidad& otra);

    ~Publicidad();

    const char* getMensaje() const;
    char getCategoria() const;
    int getPrioridad() const;

    void setMensaje(const char* msg);
    void setCategoria(char cat);
    void setPrioridad(int p);

    void mostrar() const;

    bool operator==(const Publicidad& otra) const;
    Publicidad& operator=(const Publicidad& otra);
};

#endif // PUBLICIDAD_H
