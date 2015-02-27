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
        <<"6) salir\n"
        <<"respuesta : ";
        cin>>option;
        if(option == '1'){
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
        }else if (option == '3' && h != nullptr) {
            h->addRegistro(h->getArchivo());
        }else if (option == '5' && h != nullptr) {
            int rrn;
            cout<<"RRN del registro que desea borrar: ";
            cin>>rrn;
            h->removeRegistro(h->getArchivo(),rrn);
        }else if(option == '6'){
            break;
        }
    } while (true);
    return 0;
}

