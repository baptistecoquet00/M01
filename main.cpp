#include <iostream>
#include <string>
#include "IRJournalLumineux.h"
#include "IRServeurUDP.h"

int main()
{ 
    IRServeurUDP Serveur;
    Serveur.OuvrirLaSocketDEcoute(4003);
    std::string msg;
    Serveur.RecevoirUnMessage(msg);
    Serveur.FermerLaSocket();
    
    IRJournalLumineux journal;
    journal.OuvrirPortSerie("/dev/ttyUSB0");
    journal.EnvoyerTrame(msg);
    journal.FermerPortSerie();
}
