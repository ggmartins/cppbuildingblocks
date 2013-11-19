#ifndef ELAPSED_HPP
#define ELAPSED_HPP
#include <boost/date_time.hpp>
#include <boost/format.hpp>

class timeelapsed {

private:
    boost::posix_time::ptime time;
public:

    timeelapsed() : time ( gettimenow() ) {   } 

    static inline boost::posix_time::ptime gettimenow() 
    {
	return boost::posix_time::microsec_clock::universal_time();
    }

    void reset()
    {
	time=gettimenow();
    }

    boost::posix_time::time_duration operator() () const {
	return gettimenow() - time;
    }

    std::string getsecs() {
	boost::posix_time::ptime time_now=gettimenow(); 
	boost::format f("%f");
        return str(f % (time_now - time));
    }
    

};


#define TIME(insert_code_here) do { \
    using namespace boost::posix_time; \
    timeelapsed elapsed; \
    insert_code_here \
    std::cout << "elapsed.getsecs() " << elapsed.getsecs() << std::endl; \
} while(0); 

#endif
