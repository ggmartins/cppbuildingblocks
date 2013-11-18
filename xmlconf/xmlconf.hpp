#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <list>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/ref.hpp>

using boost::reference_wrapper;
using boost::ref;

class ConfigNode {
  // insert private data here
  std::string ignorelist;
  bool status=false;
  int size=0;
  unsigned int hash=0;

  //intrusive serialization data
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
     ar & BOOST_SERIALIZATION_NVP(loaddir);
     ar & BOOST_SERIALIZATION_NVP(ignorelist);
     ar & BOOST_SERIALIZATION_NVP(status);
     ar & BOOST_SERIALIZATION_NVP(size);
  }
   
public:
  // insert public data here
  std::string loaddir;

  void init () 
  {
    loaddir="";
    ignorelist="";
    status=false;
    size=0;
    hash=0;
  }

  friend std::ostream& operator<<(std::ostream &os, const ConfigNode &confignode);
  ConfigNode () {}
  virtual ~ConfigNode () {}
};

BOOST_CLASS_VERSION(ConfigNode, 1)

std::ostream& operator<<(std::ostream &os, const ConfigNode &confignode)
{
  return os << "config_node loaddir[" <<confignode.loaddir<< "/" << confignode.size << "/" << \
     confignode.status << "/"<< confignode.ignorelist << "]";
}


class Config
{
  friend class boost::serialization::access;
  std::list <ConfigNode> nodes;
  std::list <reference_wrapper<ConfigNode>> rnodes;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    if(!rnodes.size()) { ar & BOOST_SERIALIZATION_NVP(nodes); }
    else
    {
	std::list <ConfigNode> nodes; //mask class var
	std::list<reference_wrapper<ConfigNode>>::const_iterator it;
	for (it = rnodes.begin(); it != rnodes.end(); ++it) {
	   nodes.push_back((*it).get());
    	}
        ar & BOOST_SERIALIZATION_NVP(nodes); 
    }
  }
public:
  friend std::ostream& operator<<(std::ostream &os, const Config &config);
  Config(){}
  virtual ~Config () {}
  void addConfigNode(ConfigNode &node)
  {
    rnodes.push_back(ref(node));
  }

  void save(std::string filename)
  {
    //unsigned int flags = boost::archive::no_header;
    std::ofstream ofs(filename);
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);//, flags); 
    oa << BOOST_SERIALIZATION_NVP(this);
  }

  void load(std::string filename)
  {
    std::ifstream ifs(filename);
    assert(ifs.good());
    boost::archive::xml_iarchive xml(ifs);
    xml >> BOOST_SERIALIZATION_NVP(*this);
    std::list<ConfigNode>::const_iterator it;
    std::list<reference_wrapper<ConfigNode>>::const_iterator rit;
    rnodes.clear();
    for (it = nodes.begin(); it != nodes.end(); ++it) {
       rnodes.push_back(ref((ConfigNode &)(*it))); //need proper cast here
    }

  } 

};


std::ostream& operator<<(std::ostream &os, const Config &config)
{
  std::string init="config ";
  std::ostringstream sout; sout << init;

  std::list<reference_wrapper<ConfigNode>>::const_iterator it;
  for (it = config.rnodes.begin(); it != config.rnodes.end(); ++it) {
    sout << (*it).get();
  }

  /*std::list<ConfigNode>::const_iterator cit;
  for (cit = config.nodes.begin(); cit != config.nodes.end(); ++cit) {
    sout << (*cit);
  } */

  return os << sout.str();
}

//BOOST_CLASS_IMPLEMENTATION(ConfigNode, object_serializable)
BOOST_CLASS_IMPLEMENTATION(Config, object_serializable)
int main (int argc, char **argv)
{
  Config config1, config2;
  ConfigNode cn1, cn2;
  
  config1.addConfigNode(cn1);
  config1.addConfigNode(cn2);

  cn1.loaddir="site_heavy";
  cn2.loaddir="site_light";
  config1.save("site_config.xml");

  config2.load("site_config.xml");
 
  std::cout << config1 << std::endl; 
  std::cout << config2 << std::endl; 
 
  cn1.init();
  config1.load("site_config.xml");
  std::cout << config1 << std::endl;
  
  return 0;
}