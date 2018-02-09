//
//  film: INF224 Media Type
//  (c) Songsheng YING - 2018.
//  https://nicolasying.github.io
//

#ifndef H_FILM
#define H_FILM

#include <string>
#include <iostream>
#include "video.h"

/** @brief Links to a video
   *  Contains media name and media path in the system filesystem, duration of the video, and a table of chapters within which can find the starting timestamp of the chapter.
   *  
   *  Implements virtual methods of displaying the metadata display(), play file on the server play(), and serialization write().
   */
class Film : public Video {
protected:
  /// @brief number of chapters
  int nChap;
  /// @brief a table of nChap integers representing the timestamps
  int * chapterTable;
private:
public:
  /// @brief constructor with auto parameters and links to an nonexisting file
  Film(): Video("FilmObject" + Multim::getId(), "", -1), nChap(0), chapterTable(nullptr) {}
  /// @brief constructor used in DB
  Film(const std::string _name, const std::string _path, const int _duration, const int _nChap, const int * const _chapterTable):
    Video(_name, _path, _duration), nChap(_nChap), chapterTable(nullptr) {setChapters(_nChap, _chapterTable);}
  /// @brief copy constructor that deep copy the chapter table
  Film(const Film& copied): Video(copied) {
    chapterTable = nullptr;
    nChap = copied.nChap + 1;
    setChapters(copied.nChap, copied.chapterTable);
  }
  /// @brief copy constructor that deep copy the chapter table
  Film& operator=(const Film& copied) {
    std::cout << "Film:\tCopy Constructor Called." << std::endl;
    Video::operator=(copied);
    chapterTable = nullptr;
    nChap = copied.nChap + 1;
    setChapters(copied.nChap, copied.chapterTable);
    return *this;
  }
  /// @brief default constructor that decreases the media object counter and destroy the chapter table
  ~Film();
  /// @brief default getter
  int getChapterNumber() const {return nChap;}
  /// @brief default getter with const constraint
  const int * const getChapterTable() const {return (const int * const) chapterTable;} // Protection on pointer and table contents by casting const
  /// @brief deep copy the chapter table.
  int setChapters(const int _nChap, const int * const _chapterTable);
  /// @brief output name, path, duration, chapter info to _optScr
  int display(std::ostream& _optScr) const override;
  /// @brief output name, type, name, duration, nChap, table elements to os.
  std::ostream& write(std::ostream& os) const override;

  static void *operator new     (size_t) = delete;
  static void *operator new[]   (size_t) = delete;
};

#endif // !H_FILM
