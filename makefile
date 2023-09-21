all: journal

main.o: main.cpp
	g++ -Wall -c main.cpp

IRLigne.o: IRLigne.cpp
	g++ -Wall -c IRLigne.cpp

IRJournalLumineux.o: IRJournalLumineux.cpp
	g++ -Wall -c IRJournalLumineux.cpp

IRServeurUDP.o: IRServeurUDP.cpp
	g++ -Wall -c IRServeurUDP.cpp

PortSerieAfficheur.o: PortSerieAfficheur.cpp
	g++ -Wall -c PortSerieAfficheur.cpp

journal: main.o IRLigne.o IRJournalLumineux.o IRServeurUDP.o PortSerieAfficheur.o
	g++ -Wall main.o IRLigne.o IRJournalLumineux.o IRServeurUDP.o PortSerieAfficheur.o -o journal 

clean:
	rm -f *.o journal
