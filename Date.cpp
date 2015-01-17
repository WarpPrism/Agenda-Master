#include <iostream>
#include <string>
#include <sstream>
#include "Date.h"
using namespace std;

Date::Date() {}
Date::Date(int y, int m, int d, int h, int mi) {
    year_ = y;
    month_ = m;
    day_ = d;
    hour_ = h;
    minute_ = mi;
}
int Date::getYear(void) const {
    return year_;
}
void Date::setYear(int year) {
    year_ = year;
}
int Date::getMonth(void) const {
    return month_;
}
void Date::setMonth(int month) {
    month_ = month;
}
int Date::getDay(void) const {
    return day_;
}
void Date::setDay(int day) {
    day_ = day;
}
int Date::getHour(void) const {
    return hour_;
}
void Date::setHour(int hour) {
    hour_ = hour;
}
int Date::getMinute(void) const {
    return minute_;
}
void Date::setMinute(int minute) {
    minute_ = minute;
}
bool Date::isValid(Date date) {
    int p[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int r[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date.getYear() < 1000 || date.getYear() > 9999) return false;
    if (date.getMonth() <= 0 || date.getMonth() > 12) return false;
    if (date.getDay() <= 0 || date.getDay() > 31) return false;
    if (date.getHour() < 0 || date.getHour() >= 24) return false;
    if (date.getMinute() < 0 || date.getMinute() >= 60) return false;
    if ((date.getYear() % 4 == 0 && date.getYear() % 100 != 0) ||
        date.getYear() % 400 == 0) {
        if (date.getDay() > r[date.getMonth() - 1]) {
            return false;
        }
    } else {
        if (date.getDay() > p[date.getMonth() - 1]) {
            return false;
        }
    }
    return true;
}
Date Date::stringToDate(std::string dateString) {
    stringstream ss(dateString);
    int year, month, day, hour, minute;
    char c;
    ss >> year >> c >> month >> c >> day >> c >> hour >> c >> minute;
    Date temp(year, month, day, hour, minute);
    return temp;
}
std::string Date::dateToString(Date date) {
    stringstream ss;
    ss << date.getYear() << '-';
    if (date.getMonth() < 10) {
        ss << 0 << date.getMonth() << '-';
    } else {
        ss << date.getMonth() << '-';
    }
    if (date.getDay() < 10) {
        ss << 0 << date.getDay() << '/';
    } else {
        ss << date.getDay() << '/';
    }
    if (date.getHour() < 10) {
        ss << 0 << date.getHour() << ':';
    } else {
        ss << date.getHour() << ':';
    }
    if (date.getMinute() < 10) {
        ss << 0 << date.getMinute();
    } else {
        ss << date.getMinute();
    }
    string temp = ss.str();
    return temp;
}
Date& Date::operator=(const Date& date) {
    year_ = date.year_;
    month_ = date.month_;
    day_ = date.day_;
    hour_ = date.hour_;
    minute_ = date.minute_;
    return *this;
}
bool Date::operator==(const Date& date) const {
    if (date.year_ == year_ && date.month_ == month_ && date.day_ == day_ &&
    date.hour_ == hour_ && date.minute_ == minute_) {
        return true;
    } else {
        return false;
    }
}
bool Date::operator>(const Date& date) const {
    if (year_ > date.year_)
        return true;
    if (year_ == date.year_ && month_ > date.month_)
        return true;
    if (year_ == date.year_ && month_ == date.month_ && day_ > date.day_)
        return true;
    if (year_ == date.year_ && month_ == date.month_ && day_ ==
        date.day_ && hour_ > date.hour_)
        return true;
    if (year_ == date.year_ && month_ == date.month_ &&
        day_ == date.day_ && hour_ == date.hour_ && minute_ > date.minute_)
        return true;
    return false;
}
bool Date::operator<(const Date& date) const {
    if (year_ < date.year_)
        return true;
    if (year_ == date.year_ && month_ < date.month_)
        return true;
    if (year_ == date.year_ && month_ == date.month_ && day_ < date.day_)
        return true;
    if (year_ == date.year_ && month_ == date.month_ &&
        day_ == date.day_ && hour_ < date.hour_)
        return true;
    if (year_ == date.year_ && month_ == date.month_ &&
        day_ == date.day_ && hour_ == date.hour_ && minute_ < date.minute_)
        return true;
    return false;
}
bool Date::operator>=(const Date& date) const {
    if ((*this) < date) return false;
    else return true;
}
bool Date::operator<=(const Date& date) const {
    if ((*this) > date) return false;
    else return true;
}
