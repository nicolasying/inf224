//
//  multim: INF224 Media Type
//  (c) Songsheng YING - 2018.
//  https://nicolasying.github.io
//

#ifndef H_MULTIM
#define H_MULTIM

#include <string>
#include <iostream>
#include <memory>

/** @brief Media base type.
   *  Contains media name and media path in the system filesystem.
   *  
   *  Implements virtual methods of displaying the metadata display(), play file on the server play(), and serialization write().
   */
class Multim {
private:
  /// @brief counts current media file number in the active system.
  static int fileCounter; 
  /// @brief counts historical total media file number.
  static int idGen; 
protected:
/// @brief the name of the media file
  std::string name; 
  /// @brief media file path in OS filesystem.
  std::string path; 
public:
  /// @brief constructor that increases fileCounter and idGen
  Multim(); 
  /// @brief constructor used in DB
  Multim(const std::string _name, const std::string _path);
  /// @brief deconstructor that lowers the fileCounter
  virtual ~Multim();
  /// @brief getter of name
  std::string getName() const;
  /// @brief getter of path
  std::string getPath() const;
  /// @brief setter of name
  int setName(const std::string _name);
  /// @brief setter of path
  int setPath(const std::string _path);

  /// @brief resets fileCounter and idGen
  static int iniEnv(); 
  /// @brief get unique identifiers
  inline static std::string getId() {return std::to_string(Multim::idGen);}
  
  /// @brief output media metadata to _optScr
  virtual int display(std::ostream& _optScr) const;
  /// @brief Play the file with system programs
  virtual int play() const;

  /// @brief overloads << to enable serialization of objects
  friend std::ostream& operator<<(std::ostream& os, const Multim& obj) {return obj.write(os); };
  /// @brief virtual implementation of serialization method
  virtual std::ostream& write(std::ostream& os) const;
  static void *operator new     (size_t) = delete;
  static void *operator new[]   (size_t) = delete;
};

using MulPtr = std::shared_ptr<Multim>;

#endif // !H_MULTIM
