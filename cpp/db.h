//
//  db: INF224 Media Database
//  (c) Songsheng YING - 2018.
//  https://nicolasying.github.io
//

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

/** @brief Media Database.
   *  The database is the centralized administration portal of the media files and groups.
   *  
   *  It is the unique interface to create, search, enumerate and play media files and groups.
   *  Therefore the support of serialization and deserialization of the database enables the possibility of transferring databases.
   *  It is also in charge of processing the requested relayed by the TCP server.
   *
   *  Current version does not implement yet the deletion.
   */
class DB {
private:
  /// @brief media container as a map between media objects and media name.
  std::map<std::string, MulPtr> media; 
  /// @brief group container as a map between group objects and group name.
  std::map<std::string, GrPtr> groups; 
  static const std::string reqSearch;
  static const std::string reqPlay;
  static const std::string reqDelete;
  static const std::string reqList;
  static const std::string reqSerial;
public:
  /** @brief constructor: initializes the database with all default parameters.
   * 
   * To enforce media contents, use deserialization methods to import.
   */
  DB() {};
  /// @brief Create a photo, throws an NameConflict in case of existing names.
  MulPtr createPhoto(const std::string _name, const std::string _path, const double _latitude, const double _longitude);
  /// @brief Create a video
  MulPtr createVideo(const std::string _name, const std::string _path, const int _duration);
  /// @brief Create a film
  MulPtr createFilm(const std::string _name, const std::string _path, const int _duration, const int _nChap, const int * const _chapterTable);
  /// @brief Create a group, return a pointer for group manipulation. @see Group
  GrPtr createGroup(const std::string _gName);
  /// @brief Display all media and group names
  void listAll(std::ostream& _optScr);
  /// @brief find a media file corresponding to the name, and display its metadata
  void searchMedia(const std::string _name, std::ostream& _optScr);
  /// @brief find a group corresponding to the name, and display the metadata of its member media files
  void searchGroup(const std::string _name, std::ostream& _optScr);
  /// @brief find a media file corresponding to the name, and play it on the server
  void playMedia(const std::string _name);
  /// @brief find a media file corresponding to the name, and delete it from database
  void deleteMedia(const std::string _name);
  /// @brief find a group corresponding to the name, and delete it from database
  void deleteGroup(const std::string _name);
  /// @brief process interface requests including research, play, deletion, list and database dump (serialization)
  bool processRequest(cppu::TCPConnection& cnx, const std::string& request, std::string& response);
  /// @brief serialize the database to an output stream
  friend std::ostream& operator<<(std::ostream& os, const DB& db);
  /// @brief populate database media files apart from a standard serialization output
  friend std::istream& operator>>(std::istream& is, DB& db);
};


#endif // !H_DB
