#include <iostream>
#include <list>
#include <functional>
#include <string>
#include <fstream>
#include <cstring>
#include "Storage.h"
using namespace std;
Storage* Storage::instance_ = NULL;

Storage* Storage::getInstance(void) {
    if (instance_ == NULL) {
        instance_ = new Storage();
    }
    return instance_;
}
Storage::Storage() {
    readFromFile("agenda.data");
}
Storage::~Storage() {
    sync();
    instance_ = NULL;
}
bool Storage::readFromFile(const char* fpath) {
    ifstream source;
    source.open(fpath, std::fstream::in);
    if (!source) {
        return false;
    }
    userList_.clear();
    meetingList_.clear();
    size_t u_total = 0, m_total = 0, start = 0, end = 0;
    string str;
    string user[4], meet[5];
    string u[] = {"name:\"", "password:\"", "email:\"", "phone:\""};
    string m[] = {"sponsor:\"", "participator:\"", "sdate:\"", "edate:\"", "title:\""};
    // read User from source file
    getline(source, str);
    start = str.find("total:") + 7;
    end = str.length() - 2;
    for (size_t i = start; i < end; ++i) {
        u_total = u_total * 10 + (str[i] - '0');
    }
    for (size_t i = 0; i < u_total; ++i) {
        getline(source, str);
        for (size_t j = 0; j < 4; ++j) {
            user[j] = "";
            for (size_t k = str.find(u[j]) + u[j].size(); str[k] != '\"'; ++k) {
                user[j].push_back(str[k]);
            }
        }
        User temp(user[0], user[1], user[2], user[3]);
        userList_.push_back(temp);
    }
    getline(source, str);
    start = str.find("total:") + 7;   // caution! do not calculate wrong index
    end = str.length() - 2;
    for (size_t i = start; i < end; ++i) {
        m_total = m_total * 10 + (str[i] - '0');
    }
    for (size_t i = 0; i < m_total; ++i) {
        getline(source, str);
        for (size_t j = 0; j < 5; ++j) {
            meet[j] = "";
            for (size_t k = str.find(m[j]) + m[j].size(); str[k] != '\"'; ++k) {
                meet[j].push_back(str[k]);
            }
        }
        Date d1 = Date::stringToDate(meet[2]), d2 = Date::stringToDate(meet[3]);
        Meeting temp(meet[0], meet[1], d1, d2, meet[4]);
        meetingList_.push_back(temp);
    }
    source.close();    // remember close file
    return true;
}
// write infomation to file
bool Storage::writeToFile(const char* fpath) {
    ofstream dest;
    dest.open(fpath, std::fstream::out);
    if (!dest) {    // check that the open succeeded
        cerr << "File can't open!" << endl;
        return false;
    }
    size_t count = userList_.size();  // user number
    string summary, container;
    // write User's list to file
    summary = "{collection:\"User\",total:\"";
    container.push_back(count % 10 + '0');
    for (count /= 10; count > 0; count /= 10) {
        container.push_back(count % 10 + '0');
    }
    for (int i = container.size() - 1; i >= 0; --i) {
        summary.push_back(container[i]);
    }
    summary += "\"}\n";
    dest << summary;
    for (auto p = userList_.begin(); p != userList_.end(); p++) {
        container = "{name:\"" + p->getName() + "\",";
        container += "password:\"" + p->getPassword() + "\",";
        container += "email:\"" + p->getEmail() + "\",";
        container += "phone:\"" + p->getPhone() + "\"}\n";
        dest << container;
    }
    container = "";    // clear the container
    // write meeting's list to file
    count = meetingList_.size();  // meeting number
    summary = "{collection:\"Meeting\",total:\"";
    container.push_back(count % 10 + '0');
    for (count /= 10; count > 0; count /= 10) {
        container.push_back(count % 10 + '0');
    }
    for (int i = container.size() - 1; i >= 0; --i) {
        summary.push_back(container[i]);
    }
    summary += "\"}\n";
    dest << summary;
    for (auto p = meetingList_.begin(); p != meetingList_.end(); p++) {
        container = "{sponsor:\"" + p->getSponsor() + "\",";
        container += "participator:\"" + p->getParticipator() + "\",";
        container += "sdate:\"" + Date::dateToString(p->getStartDate()) + "\",";
        container += "edate:\"" + Date::dateToString(p->getEndDate()) + "\",";
        container += "title:\"" + p->getTitle() + "\"}\n";
        dest << container;
    }
    dest.close();    // remember close file
    return true;
}
void Storage::createUser(const User& user) {
    userList_.push_back(user);
}
std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
    list<User> temp;
    list<User>::iterator iter;
    for (iter = userList_.begin(); iter != userList_.end(); iter++) {
        if (filter(*iter)) {
            temp.push_back(*iter);
        }
    }
    return temp;
}
int Storage::updateUser(std::function<bool(const User&)> filter,
               std::function<void(User&)> switcher) {
    int count = 0;
    list<User>::iterator iter;
    for (iter = userList_.begin(); iter!= userList_.end(); iter++) {
        if (filter(*iter)) {
            switcher(*iter);
            count++;
        }
    }
    return count;
}
int Storage::deleteUser(std::function<bool(const User&)> filter) {
    int count = 0;
    list<User>::iterator iter = userList_.begin();
    while (iter != userList_.end()) {
        if (filter(*iter)) {
            iter = userList_.erase(iter);
            count++;
        } else {
            iter++;
        }
    }
    return count;
}
void Storage::createMeeting(const Meeting& meeting) {
    meetingList_.push_back(meeting);
}
std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting&)> filter) {
    list<Meeting> temp;
    list<Meeting>::iterator iter;
    for (iter = meetingList_.begin(); iter != meetingList_.end(); iter++) {
        if (filter(*iter)) {
            temp.push_back(*iter);
        }
    }
    return temp;
}
int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
                  std::function<void(Meeting&)> switcher) {
    int count = 0;
    list<Meeting>::iterator iter;
    for (iter = meetingList_.begin(); iter!= meetingList_.end(); iter++) {
        if (filter(*iter)) {
            switcher(*iter);
            count++;
        }
    }
    return count;
}
int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
    int count = 0;
    list<Meeting>::iterator iter = meetingList_.begin();
    while (iter != meetingList_.end()) {
        if (filter(*iter)) {
            iter = meetingList_.erase(iter);
            count++;
        } else {
            iter++;
        }
    }
    return count;
}
bool Storage::sync(void) {
    if (writeToFile("agenda.data")) {
        return true;
    } else {
        return false;
    }
}
