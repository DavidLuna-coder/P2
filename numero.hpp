#ifndef _NUMERO_
#define _NUMERO_
#include "cadena.hpp"

class Numero
{
    public:
    Numero(Cadena& num);
    enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
    class Incorrecto
    {
        public:
            Razon razon(){return r;}
            Incorrecto(Razon raz):r(raz){};
        private:
            Razon r;
    };

    operator const char*() const;
    friend bool operator < (const Numero& N,const Numero& M);
    friend Tarjeta;
    private:
    Cadena num_;
};

bool operator < (const Numero& N,const Numero& M);


#endif