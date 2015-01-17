CC = g++
FLAG = -std=c++0x
SRC = Date.o User.o Meeting.o Storage.o AgendaService.o AgendaUI.o
Final: Agenda.cpp Date User Meeting Storage AgendaService AgendaUI
	$(CC) $(FLAG) -o Final Agenda.cpp $(SRC)
Date: Date.cpp
	$(CC) $(FLAG) -c Date.cpp
User: User.cpp Date
	$(CC) $(FLAG) -c User.cpp
Meeting: Meeting.cpp Date User
	$(CC) $(FLAG) -c Meeting.cpp
Storage: Storage.cpp Date User Meeting
	$(CC) $(FLAG) -c Storage.cpp
AgendaService: AgendaService.cpp User Date Meeting Storage
	$(CC) $(FLAG) -c AgendaService.cpp
AgendaUI: AgendaUI.cpp Date User Meeting Storage AgendaService
	$(CC) $(FLAG) -c AgendaUI.cpp

clean:
	rm *.o Final agenda.data
