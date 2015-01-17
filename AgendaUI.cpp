#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include "AgendaUI.h"

using namespace std;

AgendaUI::AgendaUI() {
    cout << "-------------------------- Agenda -------------------------------"
    << endl;
    cout << "Welocme to Agenda Master!" << endl;
    cout << "Action :" << endl;
    cout << "l  - log in Agenda by user name and password" << endl;
    cout << "r  - register an Agenda account" << endl;
    cout << "q  - quit Agenda" << endl;
    cout << "-----------------------------------------------------------------"
    << endl;
    cout << "Agenda : ~$ ";
    startAgenda();
}
// public to client code
void AgendaUI::OperationLoop(void) {
    getOperation();
}

void AgendaUI::startAgenda(void) {
    agendaService_.startAgenda();
}
std::string AgendaUI::getOperation() {
    string op;
    cin >> op;
    while (op != "q") {
        if (!executeOperation(op)) {
            cout << "Error: command not found!" << endl;
        }
        if (userName_.empty()) {
            cout << "-------------------------- Agenda -------------------------------"
            << endl;
            cout << "Action :" << endl;
            cout << "l  - log in Agenda by user name and password" << endl;
            cout << "r  - register an Agenda account" << endl;
            cout << "q  - quit Agenda" << endl;
            cout << "-----------------------------------------------------------------"
            << endl;
            cout << "Agenda : ~$ ";
        } else {
            cout << endl;
            cout << "----------------------- Agenda -------------------------------" << endl;
            cout << "Action :" << endl;
            cout << "o - log out Agenda" << endl
            <<  "dc - delete Agenda account" << endl
            <<  "lu - list all Agenda user" << endl
            <<  "cm - creat a meeting" << endl
            <<  "la - list all meetings" << endl
            <<  "las - list all sponsor meetings" << endl
            <<  "lap - list all participate meetings" << endl
            <<  "qm - query meeting by title" << endl
            <<  "qt - query meetings by time interval" << endl
            <<  "dm - delete meeting by title" << endl
            <<  "da - delete all meetings" << endl
            <<  "---------------------------------------------------------------" << endl << endl;
            cout << "Agenda@" << userName_ << " : # ";
        }
        cin >> op;
    }
    quitAgenda();
    cout << "sync finished!" << endl;
    cout << "Quit Agenda Success!" << endl;
    exit(0);
}
void AgendaUI::quitAgenda(void) {
    agendaService_.quitAgenda();
}
bool AgendaUI::executeOperation(string op) {
    if (userName_.empty()) {
        if (op == "l") {
            userLogIn();
            return true;
        }
        if (op == "r") {
            userRegister();
            return true;
        }
    }
    if (!userName_.empty()) {
        if (op == "o") {
            userLogOut();
            return true;
        }
        if (op == "dc") {
            deleteUser();
            return true;
        }
        if (op == "lu") {
            listAllUsers();
            return true;
        }
        if (op == "cm") {
            createMeeting();
            return true;
        }
        if (op == "la") {
            listAllMeetings();
            return true;
        }
        if (op == "las") {
            listAllSponsorMeetings();
            return true;
        }
        if (op == "lap") {
            listAllParticipateMeetings();
            return true;
        }
        if (op == "qm") {
            queryMeetingByTitle();
            return true;
        }
        if (op == "qt") {
            queryMeetingByTimeInterval();
            return true;
        }
        if (op == "dm") {
            deleteMeetingByTitle();
            return true;
        }
        if (op == "da") {
            deleteAllMeetings();
            return true;
        }
    }
    return false;
}
void AgendaUI::userLogIn(void) {
    string name, password;
    cout << endl << endl;
    cout << "[log in]" << " " << "[user name]" << " " << "[password]"<< endl;
    cout << "[log in]" << " ";
    cin >> name >> password;
    if (agendaService_.userLogIn(name, password)) {
        cout << "[log in]" << " " << "succeed!" << endl;
        userName_ = name;
        userPassword_ = password;
    } else {
        cout << "[Error]" << " " << "No such account! Login fail!" << endl;
    }
}
void AgendaUI::userRegister(void) {
    string name, password, email, phone;
    cout << endl << endl;
    cout << "[register] [user name] [password] [email] [phone]" << endl;
    cout << "[register] ";
    cin >> name >> password >> email >> phone;
    if (agendaService_.userRegister(name, password, email, phone))  {
        cout << "[register]" << " " << "succeed!" << endl;
    } else {
        cout << "[Error]" << " " << "register fail!" << endl;
    }
}
void AgendaUI::userLogOut(void) {
    userName_.clear();
    userPassword_.clear();
    cout << endl << endl;
}
void AgendaUI::deleteUser(void) {
    cout << endl << endl;
    if (agendaService_.deleteUser(userName_, userPassword_)) {
        cout << "[delete agenda] account succeed!" << endl;
    } else {
        cout << "[Error] delete agenda account fail!" << endl;
    }
}
void AgendaUI::listAllUsers(void) {
    cout << endl << endl;
    cout << "[list all users]" << endl << endl;
    cout << left << setw(20) << "name"
         << setw(20) << "email"
         << setw(20) << "phone" << endl;
    list<User>::iterator iter;
    list<User> T;
    T = agendaService_.listAllUsers();
    for (iter = T.begin(); iter != T.end(); iter++) {
        cout << left << setw(20) << (*iter).getName()
             << setw(20) << (*iter).getEmail()
             << setw(20) << (*iter).getPhone() << endl;
    }
}
void AgendaUI::createMeeting(void) {
    string title, par, stime, etime;
    cout << endl << endl;
    cout << "[create meeting] [title] [participator] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[create meeting] ";
    cin >> title >> par >> stime >> etime;
    if (agendaService_.createMeeting(userName_, title, par, stime, etime)) {
        cout << "[create meeting]" << " " << "succeed!" << endl;
    } else {
        cout << "[Error] create meeting fail!" << endl;
    }
}
void AgendaUI::listAllMeetings(void) {
    cout << endl << endl;
    cout << "[list all meetings]" << endl << endl;
    printMeetings(agendaService_.listAllMeetings(userName_));
    cout << endl;
}
void AgendaUI::listAllSponsorMeetings(void) {
    cout << endl << endl;
    cout << "[list all sponsor meetings]" << endl << endl;
    printMeetings(agendaService_.listAllSponsorMeetings(userName_));
    cout << endl;
}
void AgendaUI::listAllParticipateMeetings(void) {
    cout << endl << endl;
    cout << "[list all participate meetings]" << endl << endl;
    printMeetings(agendaService_.listAllParticipateMeetings(userName_));
}
void AgendaUI::queryMeetingByTitle(void) {
    string title;
    cout << endl << endl;
    cout << "[query meetings] [title]" << endl;
    cout << "[query meetings] ";
    cin >> title;
    cout << endl << endl;
    printMeetings(agendaService_.meetingQuery(userName_, title));
    cout << endl;
}
void AgendaUI::queryMeetingByTimeInterval(void) {
    string stime, etime;
    cout << endl << endl;
    cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[query meetings] ";
    cin >> stime >> etime;
    cout << endl << endl;
    cout << "[query meetings]" << endl;
    printMeetings(agendaService_.meetingQuery(userName_, stime, etime));
    cout << endl;
}
void AgendaUI::deleteMeetingByTitle(void) {
    string title;
    cout << endl << endl;
    cout << "[delete meeting] [title]" << endl;
    cout << "[delete meeting] ";
    cin >> title;
    cout << endl << endl;
    if (agendaService_.deleteMeeting(userName_, title)) {
        cout << "[delete meeting by title]" << " " << "succeed!" << endl;
    } else {
        cout << "[Error] Delete meeting fail!" << endl;
    }
}
void AgendaUI::deleteAllMeetings(void) {
    cout << endl << endl;
    agendaService_.deleteAllMeetings(userName_);
    cout << "Delete all meetings succeed!" << endl;
}
void AgendaUI::printMeetings(list<Meeting> meetings) {
    if (meetings.empty()) {
       cout << "There are no corresponding meetings now." << endl;
       return;
    }
    list<Meeting>::iterator iter;
    cout << std::left
         << std::setw(20) << "title"
         << std::setw(20) << "sponsor"
         << std::setw(20) << "participator"
         << std::setw(20) << "start time"
         << std::setw(20) << "end time" << endl;
    for (iter = meetings.begin(); iter != meetings.end(); iter++) {
        cout << left
             << setw(20) << iter->getTitle()
             << setw(20) << iter->getSponsor()
             << setw(20) << iter->getParticipator()
             << setw(20) << Date::dateToString(iter->getStartDate())
             << setw(20) << Date::dateToString(iter->getEndDate()) << endl;
    }
}
