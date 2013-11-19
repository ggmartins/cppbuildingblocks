#define BOOST_TEST_MODULE main
#include <boost/test/included/unit_test.hpp>
#include <string>
//#include <boost/test/output_test_stream.hpp>
//using boost::test_tools::output_test_stream;
#include "code_commons.h"
#include "about.hpp"
//elapsed
#include "elapsed/elapsed.hpp"
using namespace boost::posix_time;
//logging
#include "log4cpp/log.hpp"
//config/serialization
#include "xmlconf/xmlconf.hpp"

BOOST_AUTO_TEST_SUITE (main1)

BOOST_AUTO_TEST_CASE (auto_check)
{
  About about;
  std::cout << "** auto_check **" << std::endl;
  std::cout << about << std::endl;

  BOOST_CHECK( (to_string(about).find("rev") != std::string::npos) );
}


BOOST_AUTO_TEST_CASE (elapsed_test1)
{
  timeelapsed elapsed;
  std::cout << "** elapsed_test1 **" << std::endl;
  sleep(1);
  double time=elapsed().total_milliseconds();
  BOOST_CHECK( (time >= 1000.0) && (time < 1100.0) );
  std::cout << elapsed() << " elapsed()" << std::endl;
  BOOST_CHECK( to_string(elapsed()).find("00:00:01") != std::string::npos );
  sleep(1);
  std::cout << elapsed.getsecs() << " elapsed.getsecs()" << std::endl;
  BOOST_CHECK( to_string(elapsed()).find("00:00:02") != std::string::npos );
  elapsed.reset();
  sleep(1);
  std::cout << elapsed.getsecs() << " elapsed.getsecs()\n" << std::endl;
  BOOST_CHECK( to_string(elapsed()).find("00:00:01") != std::string::npos );

}

#define LOG_MAIN	"main.log.1"
#define LOG_MODULE	"module.log"
#define LOG_SECTOR	"sector.log"

BOOST_AUTO_TEST_CASE (log_test1)
{
    std::cout << "** log_test1 **" << std::endl;
    Log log("log4cpp/log4cpp.properties");
    log.main.info("testlog4cpp");
    log.module.info("testlog4cpp");
    log.module.error("testlog4cpp ERROR");
    log.moduleSector.info("passed here");
    log.moduleSector << log4cpp::Priority::INFO << "passed here" << log4cpp::eol;

    std::ostringstream out;
    std::ifstream in(LOG_MAIN, std::ios::in | std::ios::binary);
    if (in)
    {
      out << in.rdbuf();
      in.close();
    }
    BOOST_CHECK( out.str().find("ERROR") != std::string::npos );

    out.str("");
    in.open(LOG_MODULE, std::ios::in | std::ios::binary);
    if (in)
    {
      out << in.rdbuf();
      in.close();
    }
    BOOST_CHECK( out.str().find("ERROR") != std::string::npos );

    out.str("");
    in.open(LOG_SECTOR, std::ios::in | std::ios::binary);
    if (in)
    {
      out << in.rdbuf();
      in.close();
    }
    BOOST_CHECK( out.str().find("passed here") != std::string::npos );
    std::cout << std::endl;

}


BOOST_AUTO_TEST_CASE (config_test1)
{
    Config config1, config2;
    ConfigNode cn1, cn2;
    config1.addConfigNode(cn1);
    config1.addConfigNode(cn2);

    std::cout << "** config_test1 **" << std::endl;

    cn1.loaddir="site_heavy";
    cn2.loaddir="site_light";
    config1.save("xmlconf/site_config.xml");

    config2.load("xmlconf/site_config.xml");
    std::cout << config2 << std::endl; 
    std::cout << config1 << std::endl; 
    BOOST_CHECK( CHK_FILE_FOR_STR("xmlconf/site_config.xml", "<loaddir>site_heavy") );

    ConfigNode &cn3=config2.getConfigNode("site_light");
    std::cout << cn3 << std::endl;
    cn3.ignorelist="TEST";
    config2.save();
    BOOST_CHECK( CHK_FILE_FOR_STR("xmlconf/site_config.xml", "<ignorelist>TEST") );

    cn3=config2.getConfigNode("afasdsdfdsa");
    std::cout << cn3 << std::endl;   
    BOOST_CHECK( cn3.loaddir.empty() );
      
    cn1.init();
    config1.load(); //reload
    std::cout << config1 << std::endl;
    BOOST_CHECK (config1.to_string().find("/TEST")  != std::string::npos) ;

}

BOOST_AUTO_TEST_SUITE_END()

