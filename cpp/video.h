//
//  video: INF224 Media Type
//  (c) Songsheng YING - 2018.
//  https://nicolasying.github.io
//

#ifndef H_VIDEO
#define H_VIDEO

#include <string>
#include <iostream>
#include "multim.h"

/** @brief Links to a video
   *  Contains media name and media path in the system filesystem, and duration of the video.
   *  
   *  Implements virtual methods of displaying the metadata display(), play file on the server play(), and serialization write().
   */
class Video : public Multim {
protected:
    /// @brief duration of the video.   
    int duration;
private:
public:
    /// @brief constructor used in DB
    Video(const std::string _name, const std::string _path, const int _duration): Multim(_name, _path), duration(_duration) {}
    /// @brief constructor with auto parameters and links to an nonexisting file
    Video(): Multim("VideoObject" + Multim::getId(), ""), duration(-1) {}
    /// @brief default constructor that decreases the media object counter
    ~Video() {}
    /// @brief default getter
    int getDuration() const {return duration;}
    /// @brief default setter
    int setDuration(const int _duration);
    /// @brief output name, path, duration to _optScr
    int display(std::ostream& _optScr) const override;
    /// @brief open image with mpv
    int play() const override;
    /// @brief output name, type, name, duration to os.
    std::ostream& write(std::ostream& os) const override;
    static void *operator new     (size_t) = delete;
    static void *operator new[]   (size_t) = delete;
};

#endif // !H_VIDEO