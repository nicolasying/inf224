#include <string>
#include <iostream>
#include "group.h"

using namespace std;

int Group::groupCounter = 0;
int Group::idGen = 0;

int Group::display(ostream& _optScr) const {
    _optScr << "Group\t Display:" << endl << "\t" << name << " : " << endl;
    for (auto & it : (*this)) it->display(_optScr);
    return 0;
}

int Group::iniEnv() {
    Group::groupCounter = 0;
    Group::idGen = 0;
    return 0;
}
