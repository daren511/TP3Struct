//////////////////////////////////////////////////////////////////////
// B O A R D . H
// 12 D�cembre 2012
// Francis C�t� & Daren Ken St- Laurent
//////////////////////////////////////////////////////////////////////
#pragma once
#include "Matrice.h"
#include "Poids.h"
#include <iostream>
using namespace std;

class CBoard
{
public:
	//--- Constructeur et destructeur
	CBoard(ostream &, bool veutTrace);
	virtual ~CBoard();

	//--- M�thode de lancement de la recherche de solution
	void PlacerCavalier(unsigned int i, unsigned int j);

	//--- Autre m�thode publique
	void SetTrace(bool);

private:
	// Nombre de cases de l'�chiquier
	static const int MAXCASES;

	// Ostream habituel
	ostream & out_;

	 // bool Continuer ou non
	bool continuerRecherche_;

	// Afficher la trace
	bool faireTrace_;

	 // Afficher le # de pas dans la matrice
	int  noPasDuTrajet_;

	 // Afficher le nombre de solutions si laiss� fonctionner
	int  nbDeSolutions_;

	// Ligne d�part � l'�x�cution
	int  ligneDepart_;

	 // Colonne d�part � l'�x�cution
	int  colonneDepart_;

	CMatrice<bool> grilleVisitee_;  

	CMatrice<int>  grilleTrajet_; 

	 // Matrice Poids pour la matrice principale
    CMatrice<CPoids> PoidsGrille_;

private:
	//--- M�thode lanc�e par le PlacerCavalier public
	void PlacerCavalier(int i, int j);
	
	void TrouverCase(vector<CPoids> &ListeDeplacement , int i , int j);
	
	// Fonction pour trouver le poids
	int TrouverPoids(int i,int j);

	//--- Autres m�thodes utiles
	void AfficherNoSolution(int);
	
	void AfficherTrajet(int noSolution);
	
	void AfficherTrajetTrace();
	
	bool ToutEstVisite();
	
	void Wait(int nbSec);
};
