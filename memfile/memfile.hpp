#ifndef MEMFILE_H
#define MEMFILE_H

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
#include <map>
#include <iostream>
#include <sstream>

namespace fs = boost::filesystem;

class MemFile {
  
  fs::path mfpath;
  uint32_t mfsize;
  uint8_t *buf;
  MemFile(MemFile const&);
  void operator=(MemFile const&);
  //friend std::ostream & operator<<(std::ostream &out, MemFile mf);

public:
 
  bool isvalid;

  MemFile(fs::path mf) : mfpath(mf), isvalid(true) //, size(0), buffer(0)
  {
    try
    {
      std::ifstream mfile(mf.string(), std::ifstream::binary);
      mfsize=fs::file_size(mf);
      buf=new uint8_t(mfsize+1);
      memset(buf, 0, sizeof(uint8_t)*(mfsize+1));
      mfile.read((char *)buf, (int)mfsize);
      mfile.close();
    }
    catch (...) { isvalid=false; }
  }

  uint8_t *buffer() { return buf; }

  std::string to_string() { return std::string((char *)buf); }
  std::string to_print() 
  { 
    std::ostringstream sout;
    sout << "[" << mfpath.string() <<"," << mfsize <<"]"; 
    return sout.str(); 
  }

  uint32_t size() { return this->mfsize; }

  virtual ~MemFile()
  {
    delete buf;
  }
};

/*std::ostream & operator<<(std::ostream &out, MemFile mf)
{
  std::ostringstream sout;
  sout << mf.to_print();
  return out << sout;
}*/

class Memdir  {

  typedef std::multimap < fs::path, MemFile *  > memfile_t;
  memfile_t memfile;
  std::string dirname;
  fs::path mdpath;

  Memdir() : dirname() {}

  Memdir(Memdir const&);
  void operator=(Memdir const&);

public:
  ~Memdir() 
  {
    for(auto it=memfile.begin(); it!=memfile.end(); it++)
      delete (it->second);
  }

  //TODO recursive
  int load(std::string dname)
  {
    dirname=dname;
    mdpath=fs::path(dname);
    fs::directory_iterator end_iter;    
    if (fs::exists (mdpath) && fs::is_directory (mdpath))
    {
      for (fs::directory_iterator dir_iter (mdpath); dir_iter != end_iter; ++dir_iter) 
      {
        if (fs::is_regular_file (dir_iter->status ()))
          memfile.insert (memfile_t::value_type (*dir_iter,  new MemFile(*dir_iter) ));
      }
      return 0;
    }
    //TODO catch ex
    //catch (const filesystem_error& ex)
    return 1;
  }

  std::string to_string()
  {
    std::ostringstream sout;
    for(auto it=memfile.begin(); it!=memfile.end(); it++)
    {
      sout << it->first <<" - " << (*it->second).to_print() << std::endl;
    }
    return sout.str();
  }

  static Memdir &getInstance() 
  {
    static Memdir memdir;
    return memdir;
  }

}; // MEMDIR


int main (int argc, char **argv)
{

  Memdir &memdir=Memdir::getInstance();
  memdir.load("data");
  std::cout << memdir.to_string();

  return 0;
}

#endif //MEMFILE_H
