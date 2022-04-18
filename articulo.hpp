#ifndef _ARTICULO_
#define _ARTICULO_
#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>

class Articulo
{
public:
    Articulo(const Cadena& ref, const Cadena& t_, const Fecha& f,float p, unsigned stock = 0): ref_(ref),titulo_(t_), f_publi_(f),precio_(p),stock_(stock){};
    const Cadena& referencia() const;
    const Cadena& titulo() const;
    const Fecha& f_publi() const;
    float precio() const;
    float& precio();
    unsigned stock() const;
    unsigned& stock();
    ~Articulo();
private:
    const Cadena ref_;
    const Cadena titulo_;
    const Fecha f_publi_;
    float precio_;
    unsigned stock_;

};

std::ostream& operator<<(std::ostream &os, const Articulo& A);


inline const Cadena& Articulo::referencia() const
{
    return ref_;
}

inline const Cadena& Articulo::titulo() const
{
    return titulo_;
}

inline const Fecha&  Articulo::f_publi() const
{
    return f_publi_;
}

inline float Articulo::precio() const
{
    return precio_;
}

inline float& Articulo::precio()
{
    return precio_;
}

inline unsigned Articulo::stock() const
{
    return stock_;
}

inline unsigned& Articulo::stock()
{
    return stock_;
}
#endif