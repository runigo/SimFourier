/*
Copyright avril 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.3 Transformation de Fourier
(d'après SiCP 2.3 simulateur de chaîne de pendules, mai 2018)
Ce logiciel est un programme informatique servant à donner une représentation
graphique de la transformation de Fourier à 1 dimension et de la simulation
d'équations de propagation.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée. Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard l'attention de l'utilisateur est attirée sur les risques
associés au chargement, à l'utilisation, à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant des connaissances informatiques approfondies. Les
utilisateurs sont donc invités à charger et tester l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#ifndef _COMMANDES_
#define _COMMANDES_

#include "rotatif.h"
#include "selectif.h"

/***********************************************************************

	Ajuste la position des zones en fonction de la taille de la fenêtre

	Détecte la position de la souris dans les zones et les menus.

************************************************************************/

typedef struct CommandesT commandesT;
	struct CommandesT
		{
			//	Tableaux de commandes des menus
		rotatifT rotatifInitial[ROTATIF_INITIAL];		//	Rotatifs du menu initial
		selectifT selectifInitial[SELECTIF_INITIAL];	//	Sélectifs du menu initial
		rotatifT rotatifGraph[2][ROTATIF_GRAPHES];		//	Linéaires des menus graphes
		selectifT selectifGraph[2][SELECTIF_GRAPHES];	//	Sélectifs des menus graphes

			// Zones suivant X des commandes des menus verticaux (initial et simulation)
		int rotatifsGauche;
		int rotatifsDroite;
		int selectifsGauche;
		int selectifsDroite;

			// Zones suivant Y du menu 1
		int mode;

			// Zones suivant X des fonctions (zones 4, 5, 6, 7)
		int fonctionsGauche;
		int fonctionsDroite;

			// Zones suivant Y des fonctions
		int fonctionHaut;	//	limite zone 4 zone 5
		int fonctionBas;	//	limite zone 5 zone 6
		int fourierHaut;	//	limite zone 6 zone 7
		int fourierBas;		//	fenetreY

		int sourisX; // position X de la souris
		int sourisY; // position Y de la souris

		int sourisGauche; // position X de la souris - demiBouton
		int sourisDroite; // position X de la souris + demiBouton
		int sourisHaut; // position Y de la souris - demiBouton
		int sourisBas; // position Y de la souris + demiBouton

		};

//int commandesInitialise(commandesT * commandes, double facteur);

int commandesInitialiseSouris(commandesT * commandes, int sourisX, int sourisY);
int commandesAjusteCommandes(commandesT * commandes, int x, int y);

int commandesSourisZone(commandesT * commandes);

int commandeSelectifsInitiale(commandesT * commandes);
int commandeRotatifsInitiale(commandesT * commandes);
int commandeSelectifsGraphes(commandesT * commandes);
int commandeRotatifsGraphes(commandesT * commandes);
int commandeTriangles(commandesT * commandes);
int commandeLineaires(commandesT * commandes);

#endif
