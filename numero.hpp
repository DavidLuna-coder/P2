#ifndef _NUMERO_
#define _NUMERO_
#include "cadena.hpp"

class Numero
{
    public:
    Numero(const Cadena& num);
    enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
    class Incorrecto
    {
        public:
            Razon razon(){return r;}
        private:
            Razon r;
    };

    operator const char*();
    private:
    Cadena num_;
};

bool operator < (const Numero& N,const Numero& M);


#endif