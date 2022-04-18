#include "usuario.hpp"
#include <random>
#include <unistd.h>
#include <cstring>
#include "articulo.hpp"
#include "tarjeta.hpp"
Clave::Clave(const char* clave)
{
    Cadena CL(clave);
    if (CL.length() < 5)
    {
        throw Incorrecta(Razon::CORTA);
    }
    std::random_device r;
    std::uniform_int_distribution<char> dist('0','z');
    const char salt[3] = {dist(r),dist(r),'\0'};
    clave_ = crypt(clave,salt);
    if (clave_ == nullptr)
    {
        throw Incorrecta(Razon::ERROR_CRYPT);
    }
    
}

bool Clave::verifica(const char* cl) const
{
    if (strcmp(crypt(cl,clave_.c_str()),clave_.c_str()))
    {
        return true;
    }
    else
        return false;
}

//* Constructor USUARIO
Usuario::Usuario(const Cadena &id,const Cadena &nom, const Cadena &apell, const Cadena &dir, const Clave &cl): nom_(nom),apell_(apell),dir_(dir),cl_(cl)
{   
    if (!IDs_.insert(id).second)
    {
        throw Id_duplicado(id);
    }
}

//* ASOCIACIONES
void Usuario::es_titular_de(Tarjeta& Tar)
{
    T[Tar.numero()] = &Tar;
}

void Usuario::no_es_titular_de(Tarjeta& Tar)
{
    T.erase(Tar.numero());
}

void Usuario::compra(Articulo &Art, int cantidad = 1)
{
    if (cantidad <= 0)
    {
        A.erase(&Art);
    }
    else
    {
        A[&Art] = cantidad;
    }
}

std::ostream& operator << (std::ostream& os, const Usuario& U)
{
    os << U.id_ << " [" << U.cl_.clave() <<"]" << U.nom_ << U.apell_ << std::endl;
    os << U.dir_ << std::endl;
    os << "Tarjetas: " << std::endl;

    for(auto it = U.T.begin(); it != U.T.end(); it++)
    {
        os << *(it->second) << std::endl;
    }
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& U)
{
    os << "Carrito de compra de " << U.id() << " [" << U.compra().size()<<"] " << std::endl;
    os << "------------------------------------------------------------------------"<<std::endl;
    os << "------------------------------------------------------------------------"<<std::endl;
    for (auto it = U.compra().begin();it != U.compra().end(); it++)
    {
        os<<"\t" << it->second <<"\t"<< it->first << std::endl;
    }
}

Usuario::~Usuario()
{
    for (auto it = T.begin(); it != T.end(); it++)
    {
        it->second->anula_titular();
    }
}