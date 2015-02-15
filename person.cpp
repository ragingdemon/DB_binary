#include "person.h"
#include <string.h>
#include <sstream>
using std::ofstream;
using std::ifstream;

Person::Person()
{

}

Person::Person(const char *fist_name, const char *last_name, int age, char gender, double salary, int weight):
    /*first_name(fist_name), last_name(last_name), */age(age), gender(gender), salary(salary),weight(weight)
{
     strcpy(this->first_name,fist_name);
     strcpy(this->last_name,last_name);
}

void Person::save(ofstream &out)
{
    out.write(first_name,sizeof(first_name));
    out.write(last_name,sizeof(last_name));
    out.write((char*)&age,sizeof(age));
    out.write((char*)&gender,sizeof(gender));
    out.write((char*)&salary,sizeof(salary));
    out.write((char*)&weight,sizeof(weight));
}

void Person::load(ifstream &in)
{
    in.read(first_name,sizeof(first_name));
    in.read(last_name,sizeof(last_name));
    in.read((char*)age,sizeof(age));
    in.read((char*)&gender,sizeof(gender));
    in.read((char*)&salary,sizeof(salary));
    in.read((char*)&weight,sizeof(weight));
}

std::string Person::toString()
{
    std::stringstream ss;
    ss<<first_name<<','<<last_name<<','<<age<<','<<gender<<','<<salary<<','<<weight;
    return ss.str();
}
