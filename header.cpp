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
            long offset = datos_offset + avail_list * registro->getLongitud();
            int newHead;
            fs.seekg(offset+1);
            fs.read((char*)&newHead,sizeof(newHead));
            fs.seekg(offset);
            Contenido contenido(registro);
            contenido.setContent();
            contenido.writeContent(fs);
            setAvailList(fs,newHead);
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
    fstream fs(file, ios::in|ios::out|ios::binary);
    if (fs.is_open()) {
        int avail_list = getAvailList(fs);
        long offset = datos_offset + rrn * registro->getLongitud();
        fs.seekg(offset);
        fs.seekp(offset);
        char validar = fs.peek();
        if (validar == '\0' || !(fs.rdstate() == ios::goodbit)) {
            fs.close();
            return false;
        }
        fs.write("\0",1);
        fs.write((char*)&avail_list,sizeof(avail_list));
        fs.seekp(avail_list_offset);
        fs.write((char*)&rrn,sizeof(avail_list));
        fs.close();
        return true;
    }else{
        fs.close();
    }
    return false;
}

bool Header::modRegistro(int rrn)
{
    fstream fs(archivo, ios::in|ios::out|ios::binary);
    if (fs.is_open()) {
        long offset = datos_offset + rrn * registro->getLongitud();
        fs.seekg(offset);
        char validar = fs.peek();
        if (validar == '\0' || !(fs.rdstate() == ios::goodbit)) {
            fs.close();
            return false;
        }
        Contenido contenido(registro);
        contenido.setContent();
        contenido.writeContent(fs);
    }
    fs.close();
    return true;
}

bool Header::leerRegistro(int rrn)
{
    fstream fs(archivo, ios::in|ios::out|ios::binary);
    if (fs.is_open()) {
        long offset = datos_offset + rrn * registro->getLongitud();
        fs.seekg(offset);
        char validar = fs.peek();
        if (validar == '\0' || !(fs.rdstate() == ios::goodbit)) {
            fs.close();
            return false;
        }
        Contenido contenido(registro);
        contenido.readContent(fs);
        contenido.printContent();
    }
    fs.close();
    return true;
}

void Header::allRegistros()
{
    char opcion = 'n';
    int rrn = 0;
    bool eof = false;
    fstream fs(archivo, ios::in|ios::out|ios::binary);
    if (fs.is_open()) {
        do {

            for (int i = 0;i < 10; ++i) {
                long offset = datos_offset + rrn * registro->getLongitud();
                fs.seekg(offset);
                char validar = fs.peek();
                if (!(fs.rdstate() == ios::goodbit)) {
                    eof = true;
                    break;
                } else if (validar == '\0') {
                    continue;
                }
                Contenido contenido(registro);
                contenido.readContent(fs);
                contenido.printContent();
                rrn++;
            }
            if (eof) {
                cout<<"Llego al final del archivo"<<endl;
            } else {
                cout<<"Quiere continuar? (y/n): ";
                cin>>opcion;
            }
        } while (opcion != 'n' && !eof);
    }
}

void Header::compactar()
{
    fstream original(archivo, ios::in|ios::out|ios::binary);
    fstream nuevo("temp", ios::out|ios::binary);
    int longHeader = datos_offset;
    int longReg = registro->getLongitud();
    char hBuff[longHeader];
    char rbuff[longReg];
    if (original.is_open()) {
        //copiar el encabezado
        //original.read(hBuff,longHeader);
        //nuevo.write(hBuff,longHeader);
        //original.seekg(datos_offset);
        //cout<<hBuff<<endl;
        write(nuevo);
        //copiar registros
        int rrn = 0;
        while (original.rdstate() == ios::goodbit) {
            long offset = datos_offset + rrn * registro->getLongitud();
            original.seekg(offset);
            char validar = original.peek();
            if (validar != '\0' && original.rdstate() == ios::goodbit){
                original.read(rbuff,longReg);
                nuevo.write(rbuff,longReg);
            }
            rrn++;
        }
    }
    original.close();
    nuevo.close();
    return;
}
