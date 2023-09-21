#include "IRJournalLumineux.h"

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <iomanip>


IRJournalLumineux::IRJournalLumineux()
{
}

IRJournalLumineux::~IRJournalLumineux()
{
  // On s'assure que le port série se ferme correctement
  m_portSerie.fermer();
}




bool IRJournalLumineux::OuvrirPortSerie(string nomPortSerie)
{
    // Ouverture du port série
    if(m_portSerie.ouvrir(nomPortSerie) != 0)
    {
        cerr << "Erreur lors de l'ouverture du port serie" << endl;
        return false;
    }
    return true;
}


bool IRJournalLumineux::FermerPortSerie()
{
    return m_portSerie.fermer();
}


bool IRJournalLumineux::EnvoyerLigne(IRLigne ligne)
{
    return EnvoyerTrame(ligne.Trame());
}


bool IRJournalLumineux::EnvoyerTrame(string trame)
{
    // Envoi de la trame sur le port série
    if( m_portSerie.envoyerTrame(trame.c_str()) == false)
    {
        return false;
    }
#ifdef DEBUG
    cout << "Trame envoyée : " << trame << endl;
#endif
    // Lecture de la réponse si ID != 0
    /*if(m_identifiant != 0)
    {
        m_portSerie.lireMessage(_reponse, 10);
        // Si la réponse de l'afficheur n'est pas ACK
        if(strcmp(_reponse,"ACK") != 0)
        {
            return true;
        }
    }*/
    return true;
}


bool IRJournalLumineux::EnvoyerTrame(const char * trame, int longueurTrame)
{
    string str(trame,longueurTrame);
    return EnvoyerTrame(str);
}
