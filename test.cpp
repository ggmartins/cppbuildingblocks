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
  BOOST_CHECK( (time > 1000.0) && (time < 1100.0) );
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

BOOST_AUTO_TEST_CASE (log_test1)
{
    std::cout << "** log_test1 **" << std::endl;
    Log log("log4cpp/log4cpp.properties");
    log.main.info("testlog4cpp");
    log.module.info("testlog4cpp");
    log.module.error("testlog4cpp ERROR");
    log.moduleSector.info("passed here");
    BOOST_CHECK( 0==0 );
}


BOOST_AUTO_TEST_SUITE_END()

