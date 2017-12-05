#ifndef H_VIDEO
#define H_VIDEO

#include <string>
#include <iostream>
#include "multim.h"

class Video : public Multim {
protected:
    int duration;
public:
    Video(const std::string _name, const std::string _path, const int _duration): Multim(_name, _path), duration(_duration) {}
    Video(): Multim("VideoObject" + Multim::getId(), ""), duration(-1) {}
    ~Video() {}
    int getDuration() const {return duration;}
    int setDuration(const int _duration);
    int display(std::ostream& _optScr) const override;

    int play() const override;
};

#endif // !H_VIDEO