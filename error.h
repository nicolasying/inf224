#ifndef ERROR_H
#define ERROR_H

#include <string>
using namespace std;

class DBError {};

class NameConflict: public DBError {
public:
    string name;
    NameConflict(const string& _name): name(_name) {};
};

#endif //ERROR_H