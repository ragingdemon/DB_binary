#ifndef PERSON_H
#define PERSON_H

#include <fstream>
#include <string>

using std::ofstream;
using std::ifstream;
using std::string;

class Person
{
    char first_name[15];
    char last_name[15];
    int age;
    char gender;
    double salary;
    int weight;

public:
    Person();
    Person(const char *fist_name,const char *last_name,int age,char gender,double salary, int weight);
    void save(ofstream& out);
    void load(ifstream& in);
    string toString();
};

#endif // PERSON_H
