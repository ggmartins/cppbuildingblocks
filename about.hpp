#ifndef ABOUT_HPP
#define ABOUT_HPP

#define REVISION_FILE "REVISION"
//no namespace for now
//namespace code_commons {

class About {
public:
  About () : s("C++ Code Commons")  {}

  std::string str() { return " .";}

private:
  std::string s;
  std::string get_revision();
  friend std::ostream& operator<<(std::ostream &os, const About &about);

};

std::string getRevision()
{
  std::ostringstream out;
  std::ifstream in(REVISION_FILE, std::ios::in | std::ios::binary);
  if (in)
  {
    out << in.rdbuf();
    in.close();
  }
  else return "UNKREV";

  return "rev" + out.str();
}

std::ostream& operator<<(std::ostream &os, const About &about) 
{
  return os << "[" << about.s << "] v0.1 " + getRevision();
}

/*
namespace std {
std::string to_string(About &about)
{
    std::ostringstream o;
    o << about;
    return o.str();
}
}
*/

//}
#endif
