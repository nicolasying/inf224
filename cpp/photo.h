//
//  photo: INF224 Media Type
//  (c) Songsheng YING - 2018.
//  https://nicolasying.github.io
//

#ifndef H_PHOTO
#define H_PHOTO

#include <string>
#include <iostream>
#include "multim.h"

/** @brief Links to an image
   *  Contains media name and media path in the system filesystem, and latitude and longitude of the image.
   *  
   *  Implements virtual methods of displaying the metadata display(), play file on the server play(), and serialization write().
   */
class Photo : public Multim {
protected:
    /// @brief latitude of the image.
    double latitude;
    /// @brief longitude of the image.
    double longitude;
private:
public:
    /// @brief constructor used in DB
    Photo(const std::string _name, const std::string _path, const double _latitude, const double _longitude): Multim(_name, _path), latitude(_latitude), longitude(_longitude) {}
    /// @brief constructor with auto parameters and links to an nonexisting file
    Photo(): Multim("PhotoObject" + Multim::getId(), ""), latitude(-1), longitude(-1) {}
    /// @brief default constructor that decreases the media object counter
    ~Photo() {};
    /// @brief default getter
    double getLatitude() const {return latitude;};
    /// @brief default getter
    double getLongitude() const {return longitude;}
    /// @brief default setter
    int setLatitude(const double _latitude);
    /// @brief default setter
    int setLongitude(const double _longitude);
    /// @brief output name, path, lati, longi to _optScr
    int display(std::ostream& _optScr) const override;
    /// @brief open image with imagej
    int play() const override;
    /// @brief output name, type, name, path, lati, longi to os.
    std::ostream& write(std::ostream& os) const override;
    static void *operator new     (size_t) = delete;
    static void *operator new[]   (size_t) = delete;
};

#endif // !H_PHOTO
