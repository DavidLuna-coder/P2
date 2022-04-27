#include "numero.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"
#include <cstring>
bool luhn(const Cadena& numero);
Numero::Numero(const Cadena& C)
{
    char aux[C.length() + 1];
    
    int i = 0;

    for(int j = 0; j != C.length(); j++)
    {
        if (isdigit(C[j]) )
        {
            aux[i] = C[j];
            i++; 
        }
        else if(isalpha(C[j]))
        {
            throw Incorrecto(DIGITOS);
        }
    }
    aux[i] = '\0';
    Cadena AUX = aux;

    if (AUX.length() < 13 || AUX.length() > 19)
    {
        throw Incorrecto(LONGITUD);
    }
    
    if (!luhn(C))
    {
        throw Incorrecto(NO_VALIDO);
    }

    num_ = AUX;
}

Numero::operator const char *() const
{
    return num_.c_str();
}

bool operator < (const Numero& N,const Numero& M)
{
    return N.num_ < M.num_;
}