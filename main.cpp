//
//  main.cpp
//

#include <iostream>
#include "multim.h"
#include "video.h"
#include "photo.h"
#include "group.h"
#include "film.h"

using namespace std;

int main(int argc, char* argv[]) {

  cout << "Begin Test" << endl;

  Multim * objectList[10];
  objectList[0] = new Multim();
  objectList[1] = new Multim("Test", "/asd/asd");
  objectList[3] = new Photo();
  objectList[4] = new Photo("Neige", "~/Desktop/inf224/1.jpg", 2014, 2014);
  objectList[2] = new Video();
  objectList[9] = new Video("Norman 10 Million Bug", "~/Desktop/inf224/NORMAN\\ -\\ THE\\ 10\\ MILLION\\ BUG.mp4", 120);
  int tempTable[] = {1, 2, 3};
  objectList[5] = new Film("Norman 10 Million Bug", "~/Desktop/inf224/NORMAN\\ -\\ THE\\ 10\\ MILLION\\ BUG.mp4", 120, 3, tempTable);
  objectList[7] = new Film();
  objectList[8] = new Film();
  objectList[8]->display(cout);
  *(objectList[8]) = *(objectList[7]);
  objectList[8]->display(cout);
  objectList[6] = new Film(*static_cast<Film *>(objectList[5]));
  objectList[6]->setName("New Name");
  tempTable[2] = 4;
  static_cast<Film *>(objectList[5])->setChapters(3, tempTable);
  Group * g1 = new Group();
  Group * g2 = new Group("Named Group");
  for (int i = 0; i < 10; i++) {
    g1->push_back(objectList[i]);
  }
  cout << "flg" << endl;
  for (int i = 0; i < 10; i += 2) {
    g2->push_back(objectList[i]);
  }

  g1->display(cout);
  g2->display(cout);

  for (int i = 0; i < 10; i++) {
    if (objectList[i] != nullptr) {
      delete objectList[i];
    }
  }

  return 0;
}
