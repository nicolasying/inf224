#ifndef H_GROUP
#define H_GROUP

#include <string>
#include <list>
#include <iostream>
#include "multim.h"

class Group : public std::list<MulPtr> {
private:
  static int groupCounter;
  static int idGen;
protected:
    std::string name;
public:
    static int iniEnv(); // Reset counters
    Group(): name("Untitled Group" + Group::getId()) {Group::groupCounter++; Group::idGen++;}
    Group(const std::string _gName): name(_gName) {Group::groupCounter++; Group::idGen++;}
    ~Group() {Group::groupCounter--;}
    inline static std::string getId() {return std::to_string(Group::idGen);} // Get unique identifiers
    std::string getName() const {return name;};
    int setName(const std::string _gName) {name = _gName;  return 0;}
    int display(std::ostream& _optScr) const;
};

#endif // !H_GROUP
