#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include "header.h"
#include "indexl.h"

using namespace std;


int main()
{
    char option;
    Header *h = nullptr;
    char tipo = Header::NO_INDEX;
    do {
        cout <<"Menu\n"
            <<"a) Crear nueva estructura\n"
           <<"b) Cargar estructura\n"
          <<"c) Agregar Registro\n"
         <<"d) Modificar Registro\n"
        <<"e) Eliminar Registro\n"
        <<"f) Leer registro\n"
        <<"g) Buscar registro\n"
        <<"h) Listar registros\n"
        <<"i) Compactar\n"
        <<"j) Usar indice lineal\n"
        <<"k) Usar arbol B\n"
        <<"l) Sin indices\n"
        <<"m) salir\n"
        <<"respuesta : ";
        cin>>option;
        if(option == 'a'){
            if(h){
                delete h;
                h = nullptr;
            }
            h = new Header(tipo);
            fstream file(h->getArchivo(),ios::out | ios::binary);
            h->write(file);
            file.close();
        }else if (option == 'b') {
            if(h){
                delete h;
                h = nullptr;
            }
            cout<<"nombre del archivo: ";
            char archivo[41];
            cin>>archivo;
            try {
                h = new Header(archivo,tipo);
                cout<<"exito"<<endl;
            } catch (...) {
                cout<<"no corresponde el tipo"<<endl;
            }
        }else if (option == 'c' && h != nullptr) {
            h->addRegistro(h->getArchivo());
        }else if (option == 'd' && h != nullptr) {
            int rrn;
            cout<<"RRN del registro que desea modificar: ";
            cin>>rrn;
            if (tipo == Header::NO_INDEX) {
                h->modRegistro(rrn);
            }else if (tipo == Header::INDEXL) {

            }else if (tipo == Header::INDEXB) {

            }
        }else if (option == 'e' && h != nullptr) {
            int rrn;
            cout<<"RRN del registro que desea borrar: ";
            cin>>rrn;
            h->removeRegistro(h->getArchivo(),rrn);
        }else if(option == 'f' && h != nullptr){
            int rrn;
            cout<<"RRN del registro que desea leer: ";
            cin>>rrn;
            h->leerRegistro(rrn);
        }else if(option == 'g' && h != nullptr){
            //buscar
        }else if(option == 'h' && h != nullptr){
            h->allRegistros();
        }else if(option == 'i' && h != nullptr){
            h->compactar();
        }else if(option == 'j'){
            if(h){
                delete h;
                h = nullptr;
            }
            tipo = Header::INDEXL;
        }else if(option == 'k'){
            if(h){
                delete h;
                h = nullptr;
            }
            tipo = Header::INDEXB;
        }else if(option == 'l'){
            break;
        }else if(option == 'm'){
            break;
        }
    } while (true);
    if(h)
        delete h;
    return 0;
}

