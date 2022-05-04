#include "articulo.hpp"
#include <iomanip>

std::ostream& operator<<(std::ostream &os, const Articulo& A)
{   
    os << "[" << A.referencia() << "] " <<'"'<< A.titulo()<<'"'<<", "<<A.f_publi().anno()<<". " <<std::setprecision(3) << A.precio()<<" €";
    return os;
}