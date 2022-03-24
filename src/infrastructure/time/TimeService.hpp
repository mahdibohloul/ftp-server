#ifndef FTP_SERVER_TIMESERVICE_HPP
#define FTP_SERVER_TIMESERVICE_HPP

#include "string"

class TimeService {
public:
    static std::string get_current_date_time();

private:
    TimeService();
};

#endif //FTP_SERVER_TIMESERVICE_HPP
