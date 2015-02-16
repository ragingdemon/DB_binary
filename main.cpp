#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include "header.h"

using namespace std;


int main()
{    
    char option;
    bool loop;
    do {
        cout << "Menu\n"
             <<"1) crear nueva estructura\n"
            <<"2) listar\n"
           <<"3) salir\n"
          <<"respuesta : ";
        cin>>option;
        if(option == '1'){
            Header h;
            fstream file(h.getArchivo(),ios::out | ios::binary);
            h.write(file);
            file.flush();
            file.close();
            loop = true;
        }else if (option == '2') {
            cout<<"nombre del archivo: ";
            char archivo[21];
            cin>>archivo;
            Header h(archivo);
            loop = true;
        }else{
            loop = false;
        }
    } while (loop);
    return 0;
}

