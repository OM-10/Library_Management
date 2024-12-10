#ifndef LIBRARY_UTILS_H
#define LIBRARY_UTILS_H

#include <string>
#include <ctime>

// Utility to get the current date
inline std::string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday);
}

// Utility to calculate days between two dates (simplistic, assumes correct date format)
inline int daysBetween(const std::string &startDate, const std::string &endDate) {
    struct tm tm1 = {}, tm2 = {};
    strptime(startDate.c_str(), "%Y-%m-%d", &tm1);
    strptime(endDate.c_str(), "%Y-%m-%d", &tm2);

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    return difftime(t2, t1) / (60 * 60 * 24);
}

#endif // LIBRARY_UTILS_H
