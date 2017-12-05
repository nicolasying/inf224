//
//  main.cpp
//

#include <iostream>
#include "Multim.h"
using namespace std;

int main(int argc, char* argv[]) {

  cout << "Begin Test" << endl;
  
  Multim * objectList[10];

  for (int i = 0; i <= 10; i++) {
    objectList[i] = new Multim();
  }

  delete objectList[3];
  objectList[3] = nullptr;
  delete objectList[1];
  
  objectList[1] = new Multim("Test", "/asd/asd");

  for (int i = 0; i <= 10; i++) {
    if (objectList[i] != nullptr) {
      objectList[i]->display(cout);
    }
  }

  for (int i = 0; i <= 10; i++) {
    if (objectList[i] != nullptr) {
      delete objectList[i];
    }
  }

  return 0;
}
