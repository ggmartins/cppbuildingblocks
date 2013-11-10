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
	time=timeelapsed::gettimenow();
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
/*
int main(int argc, char **argv)
{
    using namespace boost::posix_time;
    timeelapsed elapsed;

    sleep(1);
    double time=elapsed().total_milliseconds();
    std::cout << "time=" << time << std::endl;
    std::cout << "elapsed() " << elapsed() << std::endl;
    sleep(1);
    std::cout << "elapsed.getsecs() " << elapsed.getsecs() << std::endl;
    elapsed.reset();
    sleep(1);
    std::cout << "elapsed.getsecs() " << elapsed.getsecs() << std::endl;
    return 0;
}
*/