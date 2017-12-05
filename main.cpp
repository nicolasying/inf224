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

  for (int i = 0; i < 10; i++) {
    objectList[i] = new Multim();
  }

  delete objectList[1];
  delete objectList[2];
  delete objectList[3];
  delete objectList[4];
  delete objectList[9];
  objectList[1] = new Multim("Test", "/asd/asd");
  objectList[3] = new Photo();
  objectList[4] = new Photo("Neige", "~/Desktop/inf224/1.jpg", 2014, 2014);
  objectList[2] = new Video();
  objectList[9] = new Video("Norman 10 Million Bug", "~/Desktop/inf224/NORMAN\\ -\\ THE\\ 10\\ MILLION\\ BUG.mp4", 120);

  for (int i = 0; i < 10; i++) {
    if (objectList[i] != nullptr) {
      // objectList[i]->display(cout);
      objectList[i]->play();
    }
  }

  for (int i = 0; i < 10; i++) {
    if (objectList[i] != nullptr) {
      delete objectList[i];
    }
  }

  objectList[4]->play();
  return 0;
}
