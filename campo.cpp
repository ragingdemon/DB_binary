#include "campo.h"
#include <string.h>

using std::fstream;

const int Campo::SIZE_CAMPO = sizeof(Campo::campo) + sizeof(Campo::nombre) + sizeof(Campo::tipo) + sizeof(Campo::longitud) + sizeof(Campo::llave);
//const int Campo::SIZE_CAMPO = sizeof(Campo) - 4;

int Campo::getSIZE_CAMPO()
{
    return SIZE_CAMPO;
}


int Campo::getCampo() const
{
    return campo;
}

void Campo::setCampo(int value)
{
    campo = value;
}

const char *Campo::getNombre() const
{
    return nombre;
}

void Campo::setNombre(char *nombre)
{
    strcpy(this->nombre,nombre);
}

char Campo::getTipo() const
{
    return tipo;
}

void Campo::setTipo(char value)
{
    tipo = value;
}
Campo::Campo(fstream &fs)
{
    fs.write((char*)&campo,sizeof(campo));
    fs.write(nombre,sizeof(nombre));
    fs.write(&tipo,sizeof(tipo));
    fs.write((char*)&longitud,sizeof(longitud));
    fs.write((char*)&llave,sizeof(llave));
}
