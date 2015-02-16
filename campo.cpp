#include "campo.h"
#include <iostream>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;

const int Campo::SIZE_CAMPO = sizeof(Campo::campo) + sizeof(Campo::nombre) + sizeof(Campo::tipo) + sizeof(Campo::longitud) + sizeof(Campo::llave);
//const int Campo::SIZE_CAMPO = sizeof(Campo) - 4;

Campo::Campo(int campo):
    campo(campo)
{
    cout<<"Nombre del campo: ";
    cin>>nombre;
    cout<<"Tipo (s/i/d): ";
    cin>>tipo;
    if (tipo == 's') {
        cout<<"longitud del campo: ";
        cin>>longitud;
    } else if (tipo == 'i') {
        longitud = sizeof(int);
    } else if (tipo == 'd') {
        longitud = sizeof(double);
    }
    cout<<"Es llave? :";
    cin>>llave;
}

Campo::Campo(int campo, const char *nombre, char tipo, int longitud, bool llave):
    campo(campo), tipo(tipo), longitud(longitud), llave(llave)
{
    strcpy(this->nombre,nombre);
}

Campo::Campo(fstream &fs)
{
    long position = fs.tellg();
    fs.read((char*)&campo,sizeof(campo));
    fs.read(nombre,sizeof(nombre));
    fs.read(&tipo,sizeof(tipo));
    fs.read((char*)&longitud,sizeof(longitud));
    fs.read((char*)&llave,sizeof(llave));
}

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

int Campo::getLongitud() const
{
    return longitud;
}

void Campo::setLongitud(int value)
{
    longitud = value;
}

void Campo::write(fstream &fs)
{
    fs.write((char*)&campo,sizeof(campo));
    fs.write(nombre,sizeof(nombre));
    fs.write(&tipo,sizeof(tipo));
    fs.write((char*)&longitud,sizeof(longitud));
    fs.write((char*)&llave,sizeof(llave));
}

