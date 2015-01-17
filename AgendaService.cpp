#include <iostream>
#include <list>
#include <string>
#include <functional>
#include <algorithm>
#include "User.h"
#include "Meeting.h"
#include "Storage.h"
#include "Date.h"
#include "AgendaService.h"

using namespace std;

AgendaService::AgendaService() {
    storage_ = storage_ -> getInstance();
}
AgendaService::~AgendaService() {
    delete storage_;
    storage_ = NULL;
}
// User login
bool AgendaService::userLogIn(string userName, string password) {
    list<User> T;
    auto f =
        [&userName, &password] (const User& temp) -> bool {
            if (temp.getName() == userName &&
                temp.getPassword() == password) {
                return true;
            } else {
                return false;
            }
        };
    T = storage_ -> queryUser(f);
    if (T.empty()) {
        return false;
    } else {
        return true;
    }
}
// User register
bool AgendaService::userRegister(string userName, string password,
                  string email, string phone) {
    auto f =
        [&userName] (const User& temp) -> bool {
            if (temp.getName() == userName) {
                return true;
            } else {
                return false;
            }
        };
    list<User> T = storage_ -> queryUser(f);
    if (!T.empty()) {
        return false;
    } else {
        User newuser(userName, password, email, phone);
        storage_ -> createUser(newuser);
        return true;
    }
}
// delete User
bool AgendaService::deleteUser(string userName, string password) {
    auto f =
        [&userName, &password] (const User& temp) -> bool {
            if (temp.getName() == userName &&
                temp.getPassword() == password) {
                return true;
            } else {
                return false;
            }
        };
    if ((storage_ -> deleteUser(f)) > 0) {
        deleteAllMeetings(userName);
        return true;
    } else {
        return false;
    }
}
// list all users
list<User> AgendaService::listAllUsers(void) {
    auto f =
        [] (const User& temp) -> bool {
            return true;
        };
    list<User> T;
    T = storage_ -> queryUser(f);
    return T;
}
// create meeting
bool AgendaService::createMeeting(string userName, string title,
                   string participator,
                   string startDate, string endDate) {
    auto f1 =
        [] (const Meeting& temp) -> bool {
            return true;
        };
    auto f2 =
        [&participator] (const User& temp) -> bool {
            if (temp.getName() == participator) {
                return true;
            } else {
                return false;
            }
        };
    Date start, end;
    start = Date::stringToDate(startDate);
    end = Date::stringToDate(endDate);
    list<Meeting> T1 = storage_ -> queryMeeting(f1);
    list<User> T2 = storage_ -> queryUser(f2);
    list<Meeting>::iterator iter;
    if (T2.empty()) {
        return false;
    }
    if (!Date::isValid(start) || !Date::isValid(end) || start >= end) {
        return false;
    } else {
        for (iter = T1.begin(); iter != T1.end(); iter++) {
            if (title == iter -> getTitle()) {
                return false;
            } else {
                continue;
            }
        }
        for (iter = T1.begin(); iter != T1.end(); iter++) {
            if (userName == iter -> getSponsor() &&
                start < (iter -> getEndDate()) &&
                (iter -> getStartDate()) < end) {
                return false;
            }
            if (participator == iter -> getParticipator() &&
                start < (iter -> getEndDate()) &&
                (iter -> getStartDate()) < end) {
                return false;
            }
        }
    }
    Meeting newmeeting(userName, participator, start, end, title);
    storage_ -> createMeeting(newmeeting);
    return true;
}
// query meeting by title
list<Meeting> AgendaService::meetingQuery(string userName, string title) {
    auto f =
        [&userName, &title] (const Meeting& temp) -> bool {
            if ((temp.getSponsor() == userName ||
                temp.getParticipator() == userName) &&
                temp.getTitle() == title) {
                return true;
            } else {
                return false;
            }
        };
    return storage_ -> queryMeeting(f);
}
// query meeting by time internal
list<Meeting> AgendaService::meetingQuery(string userName, string startDate,
                           string endDate) {
    Date start, end;
    start = Date::stringToDate(startDate);
    end = Date::stringToDate(endDate);
    auto f =
        [&] (const Meeting& temp) -> bool {
            if ((temp.getSponsor() == userName ||
                 temp.getParticipator() == userName)) {
                if (start >= temp.getEndDate() || end <= temp.getStartDate()) {
                    return false;
                } else {
                    return true;
                }
            } else {
                return false;
            }
        };
    return storage_ -> queryMeeting(f);
}
// list all meetings
list<Meeting> AgendaService::listAllMeetings(string userName) {
    auto f =
        [&userName] (const Meeting& temp) -> bool {
            if (temp.getParticipator() == userName ||
                temp.getSponsor() == userName) {
                return true;
            } else {
                return false;
            }
        };
    return storage_ -> queryMeeting(f);
}
// list all sponsor meetings
list<Meeting> AgendaService::listAllSponsorMeetings(string userName) {
    auto f =
        [&userName] (const Meeting& temp) -> bool {
            if (temp.getSponsor() == userName) {
                return true;
            } else {
                return false;
            }
        };
    return storage_ -> queryMeeting(f);
}
// list all participate meetings
list<Meeting> AgendaService::listAllParticipateMeetings(string userName) {
    auto f =
        [&userName] (const Meeting& temp) -> bool {
            if (temp.getParticipator() == userName) {
                return true;
            } else {
                return false;
            }
        };
    return storage_ -> queryMeeting(f);
}
bool AgendaService::deleteMeeting(string userName, string title) {
    auto f =
        [&userName, &title] (const Meeting& temp) -> bool {
            if (temp.getSponsor() == userName &&
                temp.getTitle() == title) {
                return true;
            } else {
                return false;
            }
        };
    if (storage_ -> deleteMeeting(f)) {
        return true;
    } else {
        return false;
    }
}
bool AgendaService::deleteAllMeetings(string userName) {
    auto f =
        [&userName] (const Meeting& temp) -> bool {
            if (temp.getSponsor() == userName) {
                return true;
            } else {
                return false;
            }
        };
    if (storage_ -> deleteMeeting(f)) {
        return true;
    } else {
        return false;
    }
}
void AgendaService::startAgenda(void) {
    storage_ = Storage::getInstance();
}
void AgendaService::quitAgenda(void) {
    storage_ -> sync();
    // storage_ = NULL; // 内存泄漏
}
