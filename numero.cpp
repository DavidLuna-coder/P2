#include "numero.hpp"
#include "cadena.hpp"
bool luhn(const Cadena& numero);
Numero::Numero(Cadena& C)
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
    C = aux;

    if (C.length() < 13 || C.length() > 19)
    {
        throw Incorrecto(LONGITUD);
    }
    
    if (!luhn(C))
    {
        throw Incorrecto(NO_VALIDO);
    }

    num_ = C;
}


Numero::operator const char *()
{
    return num_.c_str();
}

bool operator < (const Numero& N,const Numero& M)
{
    return N.num_ < M.num_;
}