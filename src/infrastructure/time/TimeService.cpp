#include "TimeService.hpp"

using namespace std;

TimeService::TimeService() = default;


string TimeService::get_current_date_time() {
    time_t now;
    struct tm *tm;
    time(&now);
    tm = localtime(&now);
    auto time_str = string(asctime(tm));
    time_str.pop_back();
    return time_str;
}