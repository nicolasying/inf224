#include <string>
#include <iostream>
#include "photo.h"

using namespace std;

int Photo::setLatitude(const double _latitude) {
    latitude = _latitude;
    return 0;
}

int Photo::setLongitude(const double _longitude){
    longitude = _longitude;
    return 0;
}

int Photo::display(std::ostream& _optScr) const {
    this->Multim::display(_optScr);
    _optScr << "\tType: Photo\n\tLatitude: " << latitude << "\n\tLongitude: " << longitude << endl;
    return 0;
}

int Photo::play() const {
    if (path != "") {
        system(("imagej " + path + " &").c_str());
        return 0;
    } else {
        this->Multim::play();
        return 1;
    }
}
ostream& Photo::write(ostream& os) const {
    Multim::write(os);
    os << getLatitude() << endl << getLongitude() << endl;
    return os;
}