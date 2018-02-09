//
//  exceptions: INF224 exception definitions
//  (c) Songsheng YING - 2018.
//  https://nicolasying.github.io
//

#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <stdexcept>
using namespace std;

/** @brief Database Exceptions.
 * 
   *  Contains different exception that can be encountered in the database operation.
   */
class DBError : public runtime_error {
    public:
    DBError(const string& __what): runtime_error(__what) {};
};

/** @brief Name already exists in the database for the group or the media.
   */
class NameConflict: public DBError {
public:
    /// @brief the conflicted name
    string name;
    NameConflict(const string& _name): DBError(_name), name(_name) {};
};

/** @brief Serialized file is written in a version non compatible with the current system
   */
class Incompatibility: public DBError {
public:
    /// @brief Protocol version of the serialization file
    int targetV;
    /// @brief Protocol version of the system
    int currentV;
    Incompatibility(const int _targetV, const int _currentV): DBError("Incompatibility"), targetV(_targetV), currentV(_currentV) {};
};

/** @brief Class type not defined in the system.
   */
class UnknownClass: public DBError {
public:
    /// @brief requested data class type
    string className;
    UnknownClass(const string& _type): DBError(_type), className(_type) {}; 
};

/** @brief Unrecognized serial section
   */
class SerialParseError: public DBError {
    public:
    /// @brief unrecognized serial file section
    string unknownClause;
    SerialParseError(const string& _clause):DBError(_clause), unknownClause(_clause) {};
};

#endif //ERROR_H