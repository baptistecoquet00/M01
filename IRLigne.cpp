#include "IRLigne.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <sstream>


IRLigne::IRLigne( )
{
    //strcpy(m_message, "Hello");
    m_numeroAfficheur = 1;
    m_message = "Hello";
    m_numeroLigne = 1;
    m_numeroPage = 'A';
    m_effetChargement = LEADING_SCROLL_LEFT;
    m_effetAffichage = NORMAL;
    m_temporisationAffichage = W_2_SEC;
    m_effetSortie = LAGGING_SCROLL_LEFT;

    PreparerPaquetDonnees();
//    sprintf(m_paquetDonnees, "<L%d><P%c><F%c><M%c><W%c><F%c>%s", m_numeroLigne, m_numeroPage, 'A' + m_effetChargement, 'A' + m_effetAffichage, 'A' + m_temporisationAffichage, 'A' + m_effetSortie, m_message);
}


IRLigne::IRLigne( const char * message, unsigned int longueurMessage )
{
    // A faire : tester que la longueur de message soit inféreure ou égale à celle de m_message
    m_message = std::string(message, longueurMessage);
    m_numeroLigne = 1;
    m_numeroPage = 'A';
    m_effetChargement = LEADING_SCROLL_LEFT;
    m_effetAffichage = NORMAL;
    m_temporisationAffichage = W_2_SEC;
    m_effetSortie = LAGGING_SCROLL_LEFT;

    PreparerPaquetDonnees();
    //sprintf(m_paquetDonnees, "<L%d><P%c><F%c><M%c><W%c><F%c>%s", m_numeroLigne, m_numeroPage, 'A' + m_effetChargement, 'A' + m_effetAffichage, 'A' + m_temporisationAffichage, 'A' + m_effetSortie, m_message);
}

IRLigne::IRLigne( std::string message)
{
    m_message = message;
    m_numeroLigne = 1;
    m_numeroPage = 'A';
    m_effetChargement = LEADING_SCROLL_LEFT;
    m_effetAffichage = NORMAL;
    m_temporisationAffichage = W_2_SEC;
    m_effetSortie = LAGGING_SCROLL_LEFT;

    PreparerPaquetDonnees();
//    sprintf(m_paquetDonnees, "<L%d><P%c><F%c><M%c><W%c><F%c>%s", m_numeroLigne, m_numeroPage, 'A' + m_effetChargement, 'A' + m_effetAffichage, 'A' + m_temporisationAffichage, 'A' + m_effetSortie, m_message);
}

IRLigne::~IRLigne()
{
}

void IRLigne::ModifierMessage( std::string message) 
{
    m_message = message;
    PreparerPaquetDonnees();    
}

void IRLigne::ModifierEffetChargement(IREffetChargement effetChargement) 
{ 
    m_effetChargement = effetChargement;
    PreparerPaquetDonnees();
}

void IRLigne::ModifierEffetAffichage(IREffetAffichage effetAffichage)
{ 
    m_effetAffichage = effetAffichage;
    PreparerPaquetDonnees();
}

void IRLigne::ModifierTemporisationAffichage(IRTemporisationAffichage temporisationAffichage)
{ 
    m_temporisationAffichage = temporisationAffichage;
    PreparerPaquetDonnees();
}

void IRLigne::ModifierEffetSortie(IREffetSortie effetSortie)
{ 
    m_effetSortie = effetSortie;
    PreparerPaquetDonnees();
}

void IRLigne::PreparerPaquetDonnees()
{
    std::stringstream ss;
    ss  << "<L" << m_numeroLigne 
        << "><P" << m_numeroPage 
        << "><F" << (char)('A' + m_effetChargement) 
        << "><M" << (char)('A' + m_effetAffichage) 
        << "><W" << (char)('A' + m_temporisationAffichage) 
        << "><F" << (char)('A' + m_effetSortie) 
        <<">" << m_message ;
        // Ajouter le checksum et <E> de fin
    m_paquetDonnees = ss.str();
    unsigned char checksum = CalculerChecksum(m_paquetDonnees);
    std::stringstream ss2;
    ss2  << "<ID" << std::setfill('0') << std::setw(2) << m_numeroAfficheur << ">"
        << m_paquetDonnees
        << std::setfill('0') << std::setw(2) << std::setiosflags(std::ios_base::uppercase) << std::hex <<  (unsigned short)checksum << std::dec
        << "<E>";
    m_paquetDonnees = ss2.str();
}

unsigned char IRLigne::CalculerChecksum(std::string message) const
{
    // Calcul du CS
    unsigned char checksum = 0;
    //std::cout << "TEST : message = " << message << std::endl;
    for (unsigned int i=0 ; i < message.length() ; i++)
    {
        checksum = checksum ^ message[i];
    }
    //std::cout << "TEST : checksum = " << std::hex << (unsigned short)checksum << std::dec << std::endl;
    return checksum;
}


bool IRLigne::ModifierTrame(std::string uneTrame)
{
    //000000000011111111112222222222
    //012345678901234567890123456789
    //<ID00><L1><PA><FE><MA><WC><FE>

    // Si la trame fini par la valeur 0, on la supprime :
    if(uneTrame[uneTrame.length()-1] == 0) { uneTrame.erase(uneTrame.length()-1,1); }
    
    // On vérifie que la trame commence par <IDXX>
    if (uneTrame.substr(0,3) != "<ID") {std::cout << "Erreur sur l'id" << std::endl; return false;}
    
    // On vérifie que la trame se finisse par <E>
    std::cout << (int)uneTrame[uneTrame.length()-1] << uneTrame[uneTrame.length()-1] << std::endl;
    std::cout << (int)uneTrame[uneTrame.length()-2] << uneTrame[uneTrame.length()-2] << std::endl;
    std::cout << (int)uneTrame[uneTrame.length()-3] << uneTrame[uneTrame.length()-3] << std::endl;
    std::cout << uneTrame.substr(uneTrame.length()-3,3) << std::endl;
    if (uneTrame.substr(uneTrame.length()-3,3) != "<E>") {std::cout << "Erreur sur <E>" << std::endl; return false;}
    
    // On vérifie le checsum
    std::string s_checksum = uneTrame.substr(uneTrame.length()-5,2);
    //std::cout << "Checksum lu : " << s_checksum << std::endl;
    unsigned int checksum;
    std::stringstream ss_checksum(s_checksum);
    ss_checksum >> std::hex >> checksum;
    //std::cout << "Checksum lu : " << std::hex << checksum << std::endl;
    std::cout << "Le paquet a recalculer : " << uneTrame.substr(6,uneTrame.length()-11) << std::endl;
    unsigned char checksum_recu = CalculerChecksum(uneTrame.substr(6,uneTrame.length()-11));
    if(checksum != checksum_recu) {std::cout << "Checksum différent : " << std::hex << (unsigned int)checksum << " - " << (unsigned int)checksum_recu << std::endl; return false;}
    //std::cout << "Checksum OK" << std::endl;
    // On copie les données :
    // L'id
    std::string s_id = uneTrame.substr(3,2);
    std::stringstream ss_id(s_id);
    ss_id >> m_numeroAfficheur;
    // Le numéro de ligne <LX>
    std::string s_numligne = uneTrame.substr(8,1);
    std::stringstream ss_numligne(s_id);
    ss_numligne >> m_numeroLigne;
    // Le numéro de page <PX>
    m_numeroPage = uneTrame[12];
    // L'effet d'entrée <FX>
    m_effetChargement = (IREffetChargement) (uneTrame[16]-'A');
    // L'effet de chargement <MX>
    m_effetAffichage = (IREffetAffichage) (uneTrame[20]-'A');
    // La durée d'affichage
    m_temporisationAffichage = (IRTemporisationAffichage) (uneTrame[24]-'A');
    // L'effet de sortie'
    m_effetSortie = (IREffetSortie) (uneTrame[28]-'A');
    // Le message
    m_message = uneTrame.substr(30,uneTrame.length()-3-2-30);
    PreparerPaquetDonnees();
    //std::cout << Trame() << std::endl;
    return true;
}



