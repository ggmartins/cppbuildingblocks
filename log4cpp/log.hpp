#ifndef _LOG_HPP
#define _LOG_HPP

#include <log4cpp/Category.hh>
#include <log4cpp/CategoryStream.hh>
#include <log4cpp/PropertyConfigurator.hh>



class Log
{
public:
    //c++11
    log4cpp::Category& root=log4cpp::Category::getRoot();
    log4cpp::Category& module1=log4cpp::Category::getInstance(std::string("module1"));
    log4cpp::Category& module1_sector1=log4cpp::Category::getInstance(std::string("module1.module1_sector1"));

    Log(std::string initFileName)
    {
	log4cpp::PropertyConfigurator::configure(initFileName);
	root.info("Log initialized (root)");
	//root.warn("");
	//root.error("");
	//root.debig("");

//	module1.info("Log initialized (module1) [%s]", initFileName);
	//module1.warn("");
	//module1.error("");
	//module1.debug("");

//	module1_sector1.info("Log initialized (module1_sector) [%s]", initFileName);
	//module1_sector.warn("");
	//module1_sector.error("");
	//module1_sector.debug("");
	root << log4cpp::Priority::INFO << "Done." << log4cpp::eol;
    }

    ~Log() { log4cpp::Category::shutdown(); }

};



#endif //_LOGSETUP_HPP
