#ifndef _FECHA_
#define _FECHA_
#include <iostream>

class Fecha
{
public:
    class Invalida
    {
        public:
        Invalida(const char* str):Error(str){}
        const char* por_que() const;
        private:
        const char* Error;
    };
    //Variables Públicas
    const unsigned AnnoMinimo = 1902;
    const unsigned AnnoMaximo = 2037;

    //Constructores
    explicit Fecha( unsigned dia = 0, unsigned mes = 0, unsigned anno = 0);
    Fecha(const Fecha& F);
    Fecha(const char* f);
    Fecha& operator=(const Fecha& F);
    //Observadores
    int dia() const;
    int mes() const;
    int anno() const;

    
    const char* cadena() const;
    //Operadores amigos
    friend Fecha operator += (Fecha&, int n);
    friend bool operator == (const Fecha& F, const Fecha& G);
    friend bool operator < (const Fecha& F,const Fecha& G); 

private:

    void EstablecerAnno(unsigned);
    void EstablecerMes(unsigned);
    void EstablecerDia(unsigned dia,unsigned mes,unsigned anno); 
    unsigned d;
    unsigned m;
    unsigned a;
};

inline const char* Fecha::Invalida:: por_que() const
{
    return Error;
}

Fecha operator +=(Fecha&, int n);
Fecha operator -=(Fecha&, int n);
Fecha operator ++(Fecha&);
Fecha operator ++(Fecha&, int);
Fecha operator --(Fecha&);
Fecha operator --(Fecha&, int);
Fecha operator +(Fecha&, int n);
Fecha operator -(Fecha&, int n);
bool operator == (const Fecha& F,const Fecha& G);
bool operator < (const Fecha& F,const Fecha& G);
bool operator != (const Fecha& F, const Fecha& G);
std::ostream& operator<<(std::ostream& os,const Fecha& F);
std::istream& operator>>(std::istream& is, Fecha& F);

#endif