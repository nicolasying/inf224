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

  cout << "Main:\tBegin Test" << endl;

  Group * g1 = new Group();
  Group * g2 = new Group("Named Group");

  {
    MulPtr objectList[10];
    // Multim * objectList[10];
    objectList[0] = make_shared<Multim>();
    objectList[1] = make_shared<Multim>("Test", "/asd/asd");
    objectList[3] = make_shared<Photo>();
    objectList[4] = make_shared<Photo>("Neige", "~/Desktop/inf224/1.jpg", 2014, 2014);
    objectList[2] = make_shared<Video>();
    objectList[9] = make_shared<Video>("Norman 10 Million Bug", "~/Desktop/inf224/NORMAN\\ -\\ THE\\ 10\\ MILLION\\ BUG.mp4", 120);
    int tempTable[] = {1, 2, 3};
    objectList[5] = make_shared<Film>("Norman 10 Million Bug 2", "~/Desktop/inf224/NORMAN\\ -\\ THE\\ 10\\ MILLION\\ BUG.mp4", 120, 3, tempTable);
    objectList[7] = make_shared<Film>();
    objectList[8] = make_shared<Film>();
    objectList[8]->display(cout);
    *(static_cast<Film *>(objectList[8].get())) = *(static_cast<Film *>(objectList[5].get()));
    objectList[8]->display(cout);
    cout << "Main:\tdeleting trial." << endl << endl;
    const int * filp = (static_cast< Film* >(objectList[5].get()))->getChapterTable();
    cout << filp[0] << filp[1] << filp[2] << endl;
    const_cast<int *>(filp)[2] = 1010;
    cout << filp[0] << filp[1] << filp[2] << endl;
    objectList[6] = make_shared<Film>(*(static_cast<Film*>(objectList[5].get())));
    objectList[6]->setName("New Name");
    tempTable[2] = 4;
    static_cast<Film *>(objectList[5].get())->setChapters(3, tempTable);
    for (int i = 0; i < 9; i++) {
      g1->push_back(objectList[i]);
    }

    for (int i = 0; i < 10; i += 2) {
      g2->push_back(objectList[i]);
    }
  }

  cout << "Main:\tExiting the cycle." << endl;

  g1->display(cout);
  g2->display(cout);


  return 0;
}
