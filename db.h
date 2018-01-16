#ifndef H_DB
#define H_DB

#include <iostream>
#include <memory>
#include <map>
#include <string>
#include "tcpserver.h"
#include "multim.h"
#include "video.h"
#include "photo.h"
#include "film.h"
#include "group.h"


class DB {
private:
  std::map<std::string, MulPtr> media;
  std::map<std::string, GrPtr> groups;
  static const std::string reqSearch;
  static const std::string reqPlay;
  static const std::string reqDelete;
public:
  MulPtr createPhoto(const std::string _name, const std::string _path, const double _latitude, const double _longitude);
  MulPtr createVideo(const std::string _name, const std::string _path, const int _duration);
  MulPtr createFilm(const std::string _name, const std::string _path, const int _duration, const int _nChap, const int * const _chapterTable);
  GrPtr createGroup(const std::string _gName);
  void searchMedia(const std::string _name, std::ostream& _optScr);
  void searchGroup(const std::string _name, std::ostream& _optScr);
  void playMedia(const std::string _name);
  void deleteMedia(const std::string _name);
  void deleteGroup(const std::string _name);
  bool processRequest(cppu::TCPConnection& cnx, const std::string& request, std::string& response);
};


#endif // !H_DB
