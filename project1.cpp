﻿#include <iostream>
#include <tchar.h>
#include <math.h>
#include <string>
#include <fstream>
#include "IRClientUDP.h"
int main() {
using namespace std;
float val1, val2;
char operateur;
float resultat;
int choix;
//char msg;
std::cout << "choisir : "<<std::endl << " 1-arithm" <<std::endl<< "2-trigo"<<std::endl;
std::cin>>choix;
std::cin.get();
/*
	   if (operateur == '+') {
				resultat = val1 + val2;
	   }
	   else if (operateur == '-') {
				  resultat = val1 - val2;
	   }
	   else if (operateur == '*') {
				  resultat = val1 * val2;
	   }
	  else if (operateur == '/') {
				  resultat = val1/val2;
	  } */
 if (choix == 1) {
 	std::cin >> val1 >> operateur >> val2;
    switch(operateur){
		case('+') :
			resultat = val1 + val2;
			break;
		case('-') :
			resultat = val1 - val2;
			break;
		case('*') :
			resultat = val1 * val2;
			break;
		case('/'):
			resultat = val1/val2;
			break;
		case('%') :
			resultat = (int)val1 % (int)val2;
			break;

	  }


 }
 if(choix==2) {
   string ftrigo;
   cin>>ftrigo>>val1;
   if(ftrigo=="sin"){
		resultat=sin(val1*(M_PI/180));
	}
	if(ftrigo=="cos"){
		resultat=cos(val1*(M_PI/180));
	}
	if(ftrigo=="tan"){
		resultat=tan(val1*(M_PI/180));
	}


 }
cout<< "RESULTAT : " << resultat <<endl;
cout << "FIN DU PROGRAMME CALCULATRICE SANS ERREUR" << endl;
cin.get();
cin.get();
fstream Fichierlog;
Fichierlog.open("journal.log", ios_base::app);
time_t t = time(0);
cout << "Horodatage : " << t <<endl;
tm now = *localtime(&t);
Fichierlog <<endl << now.tm_mday << "/" << (now.tm_mon + 1) << "/" << (now.tm_year + 1900)<<" - ";
Fichierlog << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec<<" " ;
Fichierlog<<" - "<<val1<<operateur<<val2<<"="<<resultat<<" ";
Fichierlog.close();

//msg=resultat;

IRClientUDP client;
client.OuvrirLaSocketDeCommunication("172.20.21.157",4003);
client.EnvoyerUnMessage(msg);
client.FermerLaSocket();

return 0;
/*std::cout<<"saisir la premiere valeur : ";
std::cin>>val1;
std::cin.get();

std::cout<<"saisir la deuxieme valeur: ";
std::cin>>val2;
std::cin.get();//capturer le caract�re entr�e

std::cout<<"saisir l'operateur: ";
std::cin>>operateur;
std::cin.get();


std::cin >> val1 >> operateur >> val2;
std::cin.get();

std::cout<< "RESULTAT : " << operateur <<std::endl;
std::cin.get();// capturer le caract�re entr�e
return 0; */

}
