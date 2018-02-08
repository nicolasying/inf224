#ifndef H_MULTIM
#define H_MULTIM

#include <string>
#include <iostream>
#include <memory>

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

  static int iniEnv(); // Reset counters
  inline static std::string getId() {return std::to_string(Multim::idGen);} // Get unique identifiers

  virtual int play() const; // Play the file with system programs

  friend std::ostream& operator<<(std::ostream& os, const Multim& obj) {return obj.write(os); };
  virtual std::ostream& write(std::ostream& os) const;
};

using MulPtr = std::shared_ptr<Multim>;

#endif // !H_MULTIM
