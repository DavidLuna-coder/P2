#include "articulo.hpp"
#include <iomanip>

std::ostream& operator<<(std::ostream &os, const Articulo& A)
{   
    os << "[" << A.referencia() << "] " <<'"'<< A.titulo()<<'"'<<", "<<A.f_publi()<<". " <<std::setprecision(2) << A.precio()<<" €";
    return os;
}