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

class Incompatibility: public DBError {
public:
    int targetV, currentV;
    Incompatibility(const int _targetV, const int _currentV): targetV(_targetV), currentV(_currentV) {};
};

class UnknownClass: public DBError {
public:
    string className;
    UnknownClass(const string& _type): className(_type) {}; 
};

class SerialParseError: public DBError {
    public:
    string unknownClause;
    SerialParseError(const string& _clause): unknownClause(_clause) {};
};

#endif //ERROR_H