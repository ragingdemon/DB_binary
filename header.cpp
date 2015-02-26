#include "header.h"
#include "contenido.h"
#include <string.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ios;

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
        registro = new Registro(fs);
        avail_list_offset = sizeof(archivo) + sizeof(registro->getCantidad_campos())
                + registro->getCantidad_campos() * Campo::getSIZE_CAMPO();
        datos_offset = avail_list_offset + sizeof(avail_list_offset);
    }else{
        cout<<"no se abrio el archivo"<<endl;
    }
    fs.close();
}

Header::~Header()
{
    if(registro)
        delete registro;
}

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

const char *Header::getArchivo() const
{
    return archivo;
}

int Header::getAvailList(fstream &fs)
{
    int head;
    if (fs.is_open()) {
        fs.seekg(avail_list_offset);
        fs.read((char*)&head,sizeof(head));
        fs.seekg(0);
    }else{
        return -2;
    }
    return head;
}

bool Header::setAvailList(fstream &fs, int value)
{
    if (fs.is_open()) {
        fs.seekp(avail_list_offset);
        fs.write((char*)&value,sizeof(value));
    } else {
        return false;
    }
    return true;
}

bool Header::addRegistro(const char *file)
{
    fstream fs(file, ios::in|ios::out|ios::binary);
    if (fs.is_open()) {
        int avail_list = getAvailList(fs);
        if (avail_list == -1) {
            fs.seekp(0,ios::end);
            Contenido contenido(registro);
            contenido.setContent();
            contenido.writeContent(fs);
        }else if (avail_list < -1) {
            fs.close();
            return false;
        }else{

        }

    } else {
        fs.close();
        return false;
    }
    fs.close();
    return true;
}

bool Header::addRegistro(const char *file, Contenido &contenido)
{
    fstream fs(file, ios::in|ios::out|ios::binary);
    if (fs.is_open()) {
    } else {
        return false;
    }
    return true;
}

bool Header::removeRegistro(const char *file, int rrn)
{
    int avail_list = -2;
    fstream in(file, ios::in|ios::binary);
    if (in.is_open()) {
        avail_list = getAvailList(in);
    }
    in.close();
    std::ofstream out(file, ios::out|ios::binary|ios::trunc);
    if (out.is_open() && avail_list != -2) {
        //out.seekp(ios::end);
        long file_size = out.tellp();
        long offset = datos_offset + rrn * registro->getLongitud();
        /*
        if (offset > file_size) {
            return false;
        }
        */
        out.seekp(offset);
        cout<<"puntero: "<<out.tellp()<<endl;
        out.write("\0",1);
        cout<<"puntero: "<<out.tellp()<<endl;
        out.write((char*)&avail_list,sizeof(avail_list));
        cout<<"puntero: "<<out.tellp()<<endl;
        out.seekp(avail_list_offset);
        cout<<"puntero: "<<out.tellp()<<endl;
        out.write((char*)&rrn,sizeof(avail_list));
        cout<<"puntero: "<<out.tellp()<<endl;
        out.close();
        return true;
    }else{
        out.close();
    }
    return false;
}
