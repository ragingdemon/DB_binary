#include "header.h"
#include <string.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ios;

Registro *Header::getRegistro() const
{
    return registro;
}

int Header::getAvail_list_offset() const
{
    return avail_list_offset;
}

int Header::getDatos_offset() const
{
    return datos_offset;
}

void Header::write(std::fstream &fs)
{
    fs.write(archivo,sizeof(archivo));
    registro->write(fs);
    int availList = -1;
    fs.write((char*)&availList,sizeof(avail_list_offset));
}

Header::Header()
{
    cout<<"Nombre del archivo: ";
    cin>>archivo;
    cout<<"Cantidad de campos: ";
    int cantidad_campos;
    cin>>cantidad_campos;
    registro = new Registro(cantidad_campos);
    avail_list_offset = sizeof(archivo) + sizeof(registro->getCantidad_campos())
            + registro->getCantidad_campos() * Campo::getSIZE_CAMPO();
    datos_offset = avail_list_offset + sizeof(avail_list_offset);
}

Header::Header(const char *nombre)
{
    fstream fs(nombre, ios::in | ios::binary);
    if (fs.is_open()) {
        fs.read(archivo,sizeof(archivo));
        long position = fs.tellg();
        registro = new Registro(fs);
        avail_list_offset = sizeof(archivo) + sizeof(registro->getCantidad_campos())
                + registro->getCantidad_campos() * Campo::getSIZE_CAMPO();
        datos_offset = avail_list_offset + sizeof(avail_list_offset);
    }else{
        cout<<"no se abrio el archivo"<<endl;
    }
}

Header::~Header()
{
    if(registro)
        delete registro;
}

const char *Header::getArchivo() const
{
    return archivo;
}
