/*
Copyright février 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
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

typedef struct CommandesT commandesT;
	struct CommandesT
		{
		rotatifT rotatif[ROTATIF_COMMANDES];
		selectifT selectif[SELECTIF_COMMANDES];

			// Zones suivant X des commandes
		int rotatifsCentre;
		int selectifsCentre;
		int rotatifsDroite;
		int selectifsDroite;
		int rotatifsGauche;
		int selectifsGauche;

			// Zones suivant Y du menu 1
		int mode;

			// Zones suivant X des fonctions
		int fonctionsGauche;
		int fonctionsDroite;

			// Zones suivant Y des fonctions
		int fonctionHaut;
		int fonctionBas;
		int fourierHaut;
		int fourierBas;

		int sourisX; // position X de la souris
		int sourisY; // position Y de la souris

		int sourisGauche; // position X de la souris - demiBouton
		int sourisDroite; // position X de la souris + demiBouton
		int sourisHaut; // position Y de la souris - demiBouton
		int sourisBas; // position Y de la souris + demiBouton

		};

int commandesInitialiseBoutons(commandesT * commandes, int largeur, int hauteur);
int commandesInitialiseSouris(commandesT * commandes, int sourisX, int sourisY);

int commandesSourisPosition(commandesT * commandes);

int commandeSelectifs(commandesT * commandes);
int commandeRotatifs(commandesT * commandes);
int commandeTriangles(commandesT * commandes);
int commandeLineaires(commandesT * commandes);

#endif
