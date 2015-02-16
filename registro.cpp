#include "registro.h"

Registro::Registro(int cantidad_campos):
    cantidad_campos(cantidad_campos)
{
    for (int var = 0; var < cantidad_campos; ++var) {
        Campo *campo = new Campo(var);
        longitud += campo->getLongitud();
        campos.push_back(campo);
    }
}

Registro::Registro(fstream &fs)
{
    long position = fs.tellg();
    longitud = 0;
    fs.read((char*)&cantidad_campos,sizeof(cantidad_campos));
    for (int var = 0; var < cantidad_campos; ++var) {
        Campo *campo = new Campo(fs);
        longitud += campo->getLongitud();
        campos.push_back(campo);
    }
}

Registro::~Registro()
{
    for (int var = 0; var < cantidad_campos; ++var) {
        delete campos.at(var);
    }
}

int Registro::getCantidad_campos() const
{
    return cantidad_campos;
}

void Registro::setCantidad_campos(int value)
{
    cantidad_campos = value;
}

vector<Campo *> Registro::getCampos() const
{
    return campos;
}

void Registro::setCampos(const vector<Campo *> &value)
{
    campos = value;
}

int Registro::getLongitud() const
{
    return longitud;
}

void Registro::write(std::fstream &fs)
{
    fs.write((char*)&cantidad_campos,sizeof(cantidad_campos));
    for (int var = 0; var < cantidad_campos; ++var) {
        campos.at(var)->write(fs);
    }
}
