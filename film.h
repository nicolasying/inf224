#ifndef H_FILM
#define H_FILM

#include <string>
#include <iostream>
#include "video.h"

class Film : public Video {
protected:
  int nChap;
  int* chapterTable;
public:
  Film(): Video("FilmObject" + Multim::getId(), "", -1), nChap(0),
    chapterTable(nullptr) {}
  Film(const std::string _name, const std::string _path, const int _duration,
    const int _nChap, const int * _chapterTable):
    Video(_name, _path, _duration), nChap(_nChap), chapterTable(nullptr) {setChapters(_nChap, _chapterTable)}
  ~Film() {}
  int getChapterNumber() const {return nChap;}
  const int * getChapterTable() const (return (const int *) chapterTable;)
  int setChapters(const int _nChap, int * const _chapterTable);
  int display(std::ostream& _optScr) const override;

  int play() const override;
};

#endif // !H_FILM
