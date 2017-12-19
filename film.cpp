#include <string>
#include <iostream>
#include <cstdlib>
#include "film.h"

using namespace std;

Film::~Film() {
    delete[] chapterTable;
}

int Film::display(std::ostream& _optScr) const {
    this->Multim::display(_optScr);
    _optScr << "\tType: Film\n\tDuration: " << duration << endl;
    int offset = 0;
    for(int i = 0; i < nChap; i++) {
      _optScr << "\t\tChapter " << i << ": " << chapterTable[i] << " at " << offset << endl;
      offset += chapterTable[i];
    }
    return 0;
}

int Film::setChapters(const int _nChap, const int * const _chapterTable) {
  if(_nChap != nChap || !chapterTable) {
    delete[] chapterTable;
    nChap = _nChap;
    chapterTable = new int[_nChap];
  }
  for(int i = 0; i < nChap; i++) chapterTable[i] = _chapterTable[i];
  return 0;
}
