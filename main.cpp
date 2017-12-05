//
//  main.cpp
//

#include <iostream>
#include "multim.h"
#include "video.h"
#include "photo.h"

using namespace std;

int main(int argc, char* argv[]) {

  cout << "Begin Test" << endl;
  
  Multim * objectList[10];

  for (int i = 0; i <= 10; i++) {
    objectList[i] = new Multim();
  }

  delete objectList[3];
  objectList[3] = new Photo();
  delete objectList[1];
  objectList[1] = new Multim("Test", "/asd/asd");
  delete objectList[2];
  objectList[2] = new Video();

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
