#ifndef H_PHOTO
#define H_PHOTO

#include <string>
#include <iostream>
#include "multim.h"

class Photo : public Multim {
protected:
    double latitude;
    double longitude;
public:
    Photo(const std::string _name, const std::string _path, const double _latitude, const double _longitude): Multim(_name, _path), latitude(_latitude), longitude(_longitude) {}
    Photo(): Multim("PhotoObject" + Multim::getId(), ""), latitude(-1), longitude(-1) {}
    ~Photo() {};
    double getLatitude() const {return latitude;};
    double getLongitude() const {return longitude;}
    int setLatitude(const double _latitude);
    int setLongitude(const double _longitude);
    int display(std::ostream& _optScr) const override;
    int play() const override;
    std::ostream& write(std::ostream& os) const override;
};

#endif // !H_PHOTO
