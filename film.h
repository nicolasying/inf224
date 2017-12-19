#ifndef H_FILM
#define H_FILM

#include <string>
#include <iostream>
#include "video.h"

class Film : public Video {
protected:
  int nChap;
  int * chapterTable;
public:
  Film(): Video("FilmObject" + Multim::getId(), "", -1), nChap(0), chapterTable(nullptr) {}
  Film(const std::string _name, const std::string _path, const int _duration, const int _nChap, const int * const _chapterTable):
    Video(_name, _path, _duration), nChap(_nChap), chapterTable(nullptr) {setChapters(_nChap, _chapterTable);}

  Film(const Film& copied): Video(copied) {
    chapterTable = nullptr;
    nChap = copied.nChap + 1;
    setChapters(copied.nChap, copied.chapterTable);
  }
  Film& operator=(const Film& copied) {
    std::cout << "Film:\tCopy Constructor Called." << std::endl;
    Video::operator=(copied);
    chapterTable = nullptr;
    nChap = copied.nChap + 1;
    setChapters(copied.nChap, copied.chapterTable);
    return *this;
  }
  ~Film();
  int getChapterNumber() const {return nChap;}
  const int * const getChapterTable() const {return (const int * const) chapterTable;} // Protection on pointer and table contents by casting const
  int setChapters(const int _nChap, const int * const _chapterTable);
  int display(std::ostream& _optScr) const override;

  // int play() const override; // Use Video::play instead
};

#endif // !H_FILM
