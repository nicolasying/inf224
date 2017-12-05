#include <string>
#include <iostream>
#include "multim.h"

using namespace std;

int Multim::fileCounter = 0;
int Multim::idGen = 0;

Multim::Multim() {
  name = "MediaObject" + Multim::getId();
  path = "";
  Multim::fileCounter++;
  Multim::idGen++;
}

Multim::Multim(string _name, string _path) {
    name = _name;
    path = _path;
    Multim::fileCounter++;
    Multim::idGen++;
}

Multim::~Multim() {
    Multim::fileCounter--;
}

string Multim::getName() const {
    return name;
}

string Multim::getPath() const {
    return path;
}

int Multim::setName(string _name) {
    name = _name;
    return 0;
}

int Multim::setPath(string _path) {
    path = _path;
    return 0;
}

int Multim::display(ostream& _optScr) const {
    _optScr << name << " : " << path << endl;
    return 0;
}

int Multim::iniEnv() {
    Multim::fileCounter = 0;
    Multim::idGen = 0;
    return 0;
}

int Multim::play() const {
    cerr << "Multimedia: Play called on an non-existing system file." << endl << "---Media Info---\n";
    this->display(cerr);
    cerr << "---End of Media Info---\n";
    return 1;
}
