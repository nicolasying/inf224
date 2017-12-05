#include <string>
#include <iostream>
#include <cstdlib>
#include "video.h"

using namespace std;

int Video::setDuration(const int _duration) {
    duration = _duration;
    return 0;
}

int Video::display(std::ostream& _optScr) const {
    this->Multim::display(_optScr);
    _optScr << "\tType: Video\n\tDuration: " << duration << endl;
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
