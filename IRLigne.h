#ifndef IRLIGNE_H
#define IRLIGNE_H

#include <string>

//!  Classe de gestion d'une ligne de l'afficheur
/*!
  Elle gère le message à afficher sur une ligne de l'afficheur ainsi que les effets à appliquer. Une ligne est caractérisée par : \n
  1) son numéro de ligne : notre afficheur ne pouvant afficher qu'une seule ligne à la fois, ce numéro vaudra '1'. Les méthodes d'accès sont : getNumeroLigne() et setNumeroLigne() \n
  2) son numéro de page : notre afficheur est capable de gérer plusieurs page. Cependant, pour des raisons de simplification, nous n'utiliserons qu'une seule page. La première page se nommera donc 'A'. Les méthodes d'accès sont getNumeroPage() et setNumeroPage(). \n
  3) son effet de chargement : le texte peut appaître immediatement, arrivé de la droite ou de la gauche, avec un effet de neige... tous ces effets sont décrits dans l'énumération EffetChargement.
  */

//! Énumération EffetChargement
/*! Cette énumération donne la liste de tous les effets de chargement possibles.*/
typedef enum {
  LEADING_IMMEDIATE = 0 /*!< Apparition immédiate */,
  LEADING_XOPEN /*!< Ouverture comme un X */,
  LEADING_CURTAIN_UP/*!< Apparition ligne par ligne du bas vers le haut */,
  LEADING_CURTAIN_DOWN/*!< Apparition ligne par ligne du haut vers le bas */,
  LEADING_SCROLL_LEFT/*!< Le texte arrive de la droite vers la gauche */,
  LEADING_SCROLL_RIGHT/*!< Le texte arrive de la gauche vers la droite */,
  LEADING_VOPEN/*!< */,
  LEADING_VCLOSE,
  LEADING_SCROLL_UP,
  LEADING_SCROLL_DOWN,
  LEADING_HOLD,
  LEADING_SNOW,
  LEADING_TWINKLE,
  LEADING_BLOCK_MOVE,
  LEADING_RANDOM,
  LEADING_HELLO_WORLD,
  LEADING_WELCOME,
  LEADING_AMPLUS
} IREffetChargement;

typedef enum {
  NORMAL = 0,
  BLINKING,
  SONG_1,
  SONG_2,
  SONG_3
} IREffetAffichage;

typedef enum {
  W_0_5_SEC = 0,
  W_1_SEC,
  W_2_SEC,
  W_3_SEC,
  W_4_SEC,
  W_5_SEC,
  W_6_SEC,
  W_7_SEC,
  W_8_SEC,
  W_9_SEC,
  W_10_SEC,
  W_11_SEC,
  W_12_SEC,
  W_13_SEC,
  W_14_SEC,
  W_15_SEC,
  W_16_SEC,
  W_17_SEC,
  W_18_SEC,
  W_19_SEC,
  W_20_SEC,
  W_21_SEC,
  W_22_SEC,
  W_23_SEC,
  W_24_SEC,
  W_25_SEC
} IRTemporisationAffichage;

typedef enum {
  LAGGING_IMMEDIATE = 0,
  LAGGING_XOPEN,
  LAGGING_CURTAIN_UP,
  LAGGING_CURTAIN_DOWN,
  LAGGING_SCROLL_LEFT,
  LAGGING_SCROLL_RIGHT,
  LAGGING_VOPEN,
  LAGGING_VCLOSE,
  LAGGING_SCROLL_UP,
  LAGGING_SCROLL_DOWN,
  LAGGING_HOLD
} IREffetSortie;


class IRLigne
{
public:
     //! Un constructeur.
    /*!
      Le constructeur sans argument. Il initialise les attributs de l'objet avec des valeurs par défaut. Le message est "Hello", le numéro de la ligne est 1, le numéro de la page est 'A', l'effet de chargement est LEADING_SCROLL_LEFT, l'effet d'affichage est NORMAL, la temporisation d'affichage est de 2 secondes et l'effet de sortie est LAGGING_SCROLL_LEFT.
      \sa setMessage(), setNumeroLigne(), setNumeroPage(), setEffetChargement(), setEffetAffichage(), setTemporisationAffichage(), setEffetSortie(), ~Ligne()
    */
    IRLigne () ;

     //! Un constructeur.
    /*!
      Le constructeur à un argument. L'argument attendu est le message à afficher. Sinon, par défaut, le numéro de la ligne est 1, le numéro de la page est 'A', l'effet de chargement est LEADING_SCROLL_LEFT, l'effet d'affichage est NORMAL, la temporisation d'affichage est de 2 secondes et l'effet de sortie est LAGGING_SCROLL_LEFT.
      \sa setMessage(), setNumeroLigne(), setNumeroPage(), setEffetChargement(), setEffetAffichage(), setTemporisationAffichage(), setEffetSortie(), ~Ligne()
    */
    IRLigne ( const char * message, unsigned int longueurMessage );
    IRLigne ( std::string message );

     //! Le destructeur.
    /*!
      Le destructeur ne fait rien de particulier.
      \sa Ligne()
    */
    ~IRLigne();

    //! Méthode d'accès permettant de lire l'attribut m_numeroLigne.
    /*!
      \return Cette méthode renvoie le numero de la ligne.
      \sa setNumeroLigne()
    */
    inline int NumeroLigne() const { return m_numeroLigne;}

    //! Méthode d'accès permettant de modifier l'attribut m_numeroLigne.
    /*!
      \param numeroLigne le nouveau numero de ligne.
      \sa getNumeroLigne()
    */
    inline void ModifierNumeroLigne(int numeroLigne) {m_numeroLigne = numeroLigne; m_paquetDonnees[2] = '0' + numeroLigne; }

    //! Méthode d'accès permettant de lire l'attribut m_numeroPage.
    /*!
      \return Cette méthode renvoie le numero de la page.
      \sa setNumeroPage()
    */
    inline char NumeroPage() const { return m_numeroPage;}

    //! Méthode d'accès permettant de modifier l'attribut m_numeroPage.
    /*!
      \param numeroPage le nouveau numero de page.
      \sa getNumeroPage()
    */
    inline void ModifierNumeroPage(char numeroPage) {m_numeroPage = numeroPage; m_paquetDonnees[6] = numeroPage; }


    //inline const char * getMessage() const { return m_message;}
    //inline void setMessage(const char message[]) {strcpy(m_message,message); strcpy(m_paquetDonnees+24,message); }
    inline std::string Message() const {return m_message;}
    void ModifierMessage( std::string message);

    inline IREffetChargement EffetChargement() const {return m_effetChargement;}
    void ModifierEffetChargement(IREffetChargement effetChargement);

    inline IREffetAffichage EffetAffichage() const {return m_effetAffichage;}
    void ModifierEffetAffichage(IREffetAffichage effetAffichage);

    inline IRTemporisationAffichage TemporisationAffichage() const {return m_temporisationAffichage;}
    void ModifierTemporisationAffichage(IRTemporisationAffichage temporisationAffichage);

    inline IREffetSortie EffetSortie() const {return m_effetSortie;}
    void ModifierEffetSortie(IREffetSortie effetSortie);

    /*!
      \brief Méthode renvoyant la trame complete à envoyer à l'afficheur
      \param adresseIPServeur l'adresse IP du serveur UDP à joindre
      \param portServeur le port du serveur UDP à joindre
      \return Cette méthode renvoie la chaine de caractères (un objet de la classe string) complèete à envoyer au journal lumineux. Cette trame commence par l'identifiant de l'afficheur, suivi des effets d'affichage, du cheksum et se termine par <E>.
      \sa FermerLaSocket()
    */
    inline std::string Trame() const {return m_paquetDonnees;}

    /*!
      \brief Cette méthode extrait toutes les informations d'une trame si elle est correcte (vérification du checksum)
      \param uneTrame la trame à extraire
      \return Cette méthode renvoie true si la trame est correcte et que l'extraction des données s'est faite correctement, false sinon.
      \sa FermerLaSocket()
    */
    bool ModifierTrame(std::string uneTrame);

private:

    // Le message à afficher
    //char m_message[15];
    std::string m_message;
    int m_numeroAfficheur;
    // Le numéro de page et de ligne
    int m_numeroLigne;
    char m_numeroPage;
    // Les effets en entrée
    IREffetChargement m_effetChargement;
    IREffetAffichage m_effetAffichage;
    IRTemporisationAffichage m_temporisationAffichage;
    IREffetSortie m_effetSortie;
    // Le message à afficher avec numéro de page, de ligne, et les effets et le checksum.
    //char m_paquetDonnees[255];
    std::string m_paquetDonnees;
    void PreparerPaquetDonnees();
    unsigned char CalculerChecksum(std::string message) const;

};



#endif
