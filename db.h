#ifndef H_DB
#define H_DB

#include <iostream>
#include <map>
#include <string>
#include "multim.h"
#include "video.h"
#include "photo.h"
#include "film.h"
#include "group.h"

class DB {
private:
  std::map<string, MulPtr> media;
  std::map<string, GrPtr> groups;
public:
  void create()
}


#endif // !H_DB
