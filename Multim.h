#ifndef H_MULTIM
#define H_MULTIM

#include <string>
#include <iostream>

class Multim {
private:
  static int fileCounter;
  static int idGen;
  std::string name;
  std::string path;
public:
  Multim();
  Multim(std::string _name, std::string _path);
  ~Multim();
  std::string getName() const;
  std::string getPath() const;
  int setName(std::string _name);
  int setPath(std::string _path);
  int display(std::ostream& _optScr) const;
  static int iniEnv();
};

#endif // !H_MULTIM