#include <iostream>
#include <string.h>
#include <fstream>
#include "person.h"

using namespace std;
void prueba(const char*);

int main()
{
    char option;
    bool loop;
    do {
        cout << "Menu\n"
             <<"1) agregar\n"
            <<"2) listar\n"
           <<"3) salir\n"
          <<"entonces : ";
        cin>>option;
        prueba("es una prueba");
        if(option == '1'){
            char first_name[15];
            char last_name[15];
            int age;
            char gender;
            double salary;
            int weight;
            cout << "nombre: "; cin >> first_name;
            cout << "apellido: "; cin >> last_name;
            cout << "edad: "; cin >> age;
            cout << "genero: "; cin >> gender;
            cout << "salario: "; cin >> salary;
            cout << "peso: "; cin >> weight;
            Person p(first_name,last_name,age,gender,salary,weight);
            ofstream file("binario.bin",ios::out | ios::binary | ios::app);
            p.save(file);
            file.close();
            loop = true;
        }else if (option == '2') {
            Person p;
            ifstream file("binario.bin",ios::in | ios::binary);
            while (file.good()) {
                p.load(file);
                cout<<p.toString()<<endl;
            }
            loop = true;
        }else{
            loop = false;
        }
    } while (loop);
    return 0;
}

void prueba(const char* o){
    char test[15];
    strcpy(test,o);
    cout << test <<endl;
}

