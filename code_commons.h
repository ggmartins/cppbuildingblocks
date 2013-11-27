#ifndef CODE_COMMONS
#define CODE_COMMONS
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
 std::ostringstream out;
 out << t;
 return out.str();
}


bool CHK_FILE_FOR_STR(std::string filename, std::string str)
{
  std::ostringstream out;
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    out << in.rdbuf();
    in.close();
  }
  else return false;

  return (out.str().find(str) != std::string::npos);
} 

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}


#endif //CODE_COMMONS
