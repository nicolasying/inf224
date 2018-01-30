//
//  main.cpp
//

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "multim.h"
#include "video.h"
#include "photo.h"
#include "group.h"
#include "film.h"
#include "db.h"
#include "tcpserver.h"
using namespace cppu;
using namespace std;


int main(int argc, char* argv[]) {
  const int PORT = atoi(argv[1]);
  // cree l'objet qui gère les données
  shared_ptr<DB> base(new DB());
  GrPtr g1 = base->createGroup("Named Group");
  GrPtr g2 = base->createGroup("New Group");
  
  {
    MulPtr objectList[10];
    
    objectList[0] = base->createPhoto("Neige", "./1.jpg", 2014, 2014);
    objectList[1] = base->createVideo("Norman 10 Million Bug", "./NORMAN\\ -\\ THE\\ 10\\ MILLION\\ BUG.mp4", 120);
    int tempTable[] = {1, 2, 3};
    objectList[2] = base->createFilm("Norman 10 Million Bug 2", "./NORMAN\\ -\\ THE\\ 10\\ MILLION\\ BUG.mp4", 120, 3, tempTable);
    objectList[3] = base->createFilm("Norman 10 Million Bug 3", "./NORMAN\\ -\\ THE\\ 10\\ MILLION\\ BUG.mp4", 120, 3, tempTable);
    objectList[3]->setName("New Name"); // donne incohérence comme ce n'est pas le base qui gère le nommage.
    
    for (int i = 0; i < 4; i++) {
      g1->push_back(objectList[i]);
    }

    for (int i = 0; i < 4; i += 2) {
      g2->push_back(objectList[i]);
    }
  }

  cout << "Main:\tContent Prepared." << endl;

  // cree le TCPServer
  shared_ptr<TCPServer> server(new TCPServer());
  
  

  // le serveur appelera cette méthode chaque fois qu'il y a une requête
  server->setCallback(*base, &DB::processRequest);
  
  // lance la boucle infinie du serveur
  cout << "Starting Server on port " << PORT << endl;
  
  int status = server->run(PORT);
  
  // en cas d'erreur
  if (status < 0) {
    cerr << "Could not start Server on port " << PORT << endl;
    return 1;
  }
  
  return 0;
}

// Ancient version 
/*
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
*/ // End of ancient version
