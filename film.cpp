#include <string>
#include <iostream>
#include <cstdlib>
#include "film.h"

using namespace std;

int Film::display(std::ostream& _optScr) const {
    this->Multim::display(_optScr);
    _optScr << "\tType: Film\n\tDuration: " << duration << endl;
    int offSet = 0;
    for(int i = 0; i < nChap; i++) {
      _optScr << "\t\tChapter " << i << ": " << chapterTable[i] << "at " << offset << endl;
      offSet += chapterTable[i];
    }
    return 0;
}

int Video::play() const {
    if (path != "") {
        system(("mpv " + path + " &").c_str());
        return 0;
    } else {
        this->Multim::play();
        return 1;
    }
}

int Film::setChapters(const int _nChap, int * const _chapterTable) {
  if(_nChap != nChap) {
    delete[] chapterTable;
    nChap = _nChap;
    chapterTable = new int[_nChap];
  }
  for(int i = 0; i < nChap; i++) chapterTable[i] = _chapterTable[i];
}

int Film::play() const override;
