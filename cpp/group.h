//
//  group: INF224 Basic Type
//  (c) Songsheng YING - 2018.
//  https://nicolasying.github.io
//

#ifndef H_GROUP
#define H_GROUP

#include <string>
#include <list>
#include <iostream>
#include "multim.h"

/** @brief Database base type.
   *  Contains a list of media objects, has a name for the group.
   *  
   *  Implements virtual methods of displaying the metadata display(), play file on the server play(), and serialization write().
   */
class Group : public std::list<MulPtr> {
private:
protected:
    /// @brief the name of the group
    std::string name;
public:
    /// @brief resets groupCounter and idGen
    static int iniEnv(); 
    
    /// @brief counts current group number in the active system.
    static int groupCounter; 
    /// @brief counts historical total group number.
    static int idGen;
    /// @brief constructor that increases groupCounter and idGen, auto name the group
    Group(): name("Untitled Group" + Group::getId()) {Group::groupCounter++; Group::idGen++;}
    /// @brief constructor that increases groupCounter and idGen, name the group with the supplied parameter
    Group(const std::string _gName): name(_gName) {Group::groupCounter++; Group::idGen++;}
    /// @brief deconstructor that lowers the groupCounter
    ~Group() {Group::groupCounter--;}
    /// @brief get unique identifiers for groups
    inline static std::string getId() {return std::to_string(Group::idGen);}

    /// @brief default getter
    std::string getName() const {return name;};
    /// @brief default setter
    int setName(const std::string _gName) {name = _gName;  return 0;}
    /// @brief display in order the media metadata.
    int display(std::ostream& _optScr) const;
    
    static void *operator new     (size_t) = delete;
    static void *operator new[]   (size_t) = delete;
};

using GrPtr = std::shared_ptr<Group>;
#endif // !H_GROUP
