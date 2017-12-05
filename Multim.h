#ifndef H_MULTIM
#define H_MULTIM

#include <string>
#include <iostream>

class Multim {
private:
  static int fileCounter;
  static int idGen;
protected:
  std::string name;
  std::string path;
public:
  Multim();
  Multim(const std::string _name, const std::string _path);
  virtual ~Multim();
  std::string getName() const;
  std::string getPath() const;
  int setName(const std::string _name);
  int setPath(const std::string _path);
  virtual int display(std::ostream& _optScr) const;
  inline static std::string getId() {return std::to_string(Multim::idGen);}
  static int iniEnv();
};

#endif // !H_MULTIM