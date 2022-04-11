#include "usuario.hpp"
#include <cstdlib>
#include <unistd.h>
Clave::Clave(const char* clave)
{
    Cadena CL(clave);
    if (CL.length() < 5)
    {
        throw Incorrecta(Razon::CORTA);
    }

    clave_ = crypt(clave,"qwertyuiopasdfghjklñzxcmvnb");
    if (clave_ == nullptr)
    {
        throw Incorrecta(Razon::ERROR_CRYPT);
    }
    
}

bool Clave::verifica(const char* cl) const
{
    const char* cifr;
    cifr = crypt(cl,"qwertyuiopasdfghjklñzxcmvnb");
    if (cl == clave_)
    {
        return true;
    }
    else
        return false;
}

Usuario::Usuario(const Cadena &id,const Cadena &nom, const Cadena &apell, const Cadena &dir, const Clave &cl): nom_(nom),apell_(apell),dir_(dir),cl_(cl)
{   
    if (!IDs_.insert(id).second)
    {
        
    }
    
}
