#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include "header.h"

using namespace std;


int main()
{    
    char option;
    Header *h = nullptr;
    do {
        cout <<"Menu\n"
            <<"1) crear nueva estructura\n"
           <<"2) Cargar estructura\n"
          <<"3) Agregar Registro\n"
         <<"4) Modificar Registro\n"
        <<"5) Eliminar Registro\n"
        <<"6) Leer registro\n"
        <<"7) Listar registros\n"
        <<"8) Compactar\n"
        <<"9) Usar indice lineal\n"
        <<"0) Usar arbol B\n"
        <<"s) salir\n"
        <<"respuesta : ";
        cin>>option;
        if(option == '1'){
            h = new Header();
            fstream file(h->getArchivo(),ios::out | ios::binary);
            h->write(file);
            file.close();
        }else if (option == '2') {
            cout<<"nombre del archivo: ";
            char archivo[41];
            cin>>archivo;
            h = new Header(archivo);
        }else if (option == '3' && h != nullptr) {
            h->addRegistro(h->getArchivo());
        }else if (option == '4' && h != nullptr) {
            int rrn;
            cout<<"RRN del registro que desea modificar: ";
            cin>>rrn;
            h->modRegistro(rrn);
        }else if (option == '5' && h != nullptr) {
            int rrn;
            cout<<"RRN del registro que desea borrar: ";
            cin>>rrn;
            h->removeRegistro(h->getArchivo(),rrn);
        }else if(option == '6' && h != nullptr){
            int rrn;
            cout<<"RRN del registro que desea leer: ";
            cin>>rrn;
            h->leerRegistro(rrn);
        }else if(option == '7' && h != nullptr){
            h->allRegistros();
        }else if(option == '8'){
            break;
        }else if(option == '9'){
            break;
        }else if(option == '0'){
            break;
        }else if(option == 's'){
            break;
        }
    } while (true);
    if(h)
        delete h;
    return 0;
}

