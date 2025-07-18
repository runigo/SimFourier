/*
Copyright mai 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
Ce logiciel est un programme informatique permettant de donner une représentation
graphique de la transformation de Fourier à 1 dimension et d'observer l'effet
d'un filtrage.
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

#ifndef _CONSTANTES_
#define _CONSTANTES_

//#include "unistd.h"

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <time.h>

//#define PI 3.14159265358979323846264338327950288419716939937510582
//#define PI 3.1415926535897932384626433832795
#define PI 3.14159265359
#define PIS2 1.570796327
#define DEUXPI 6.28318530718

		//-------------- PARAMÈTRES GRAPHIQUES ---------------

	//	TAILLE DES MENUS
#define INITIALE_X 125
#define INITIALE_Y 774

#define GRAPHE_X 365
#define GRAPHE_Y 43

#define FILTRE_ROTATIF_X 78
#define FILTRE_ROTATIF_Y 711

#define FILTRE_SELECTIF_X 562
#define FILTRE_SELECTIF_Y 43

	//  TAILLE IMPLICITE DU BOUTON filtrage
#define FILTRAGE_X 78
#define FILTRAGE_Y 38

	//  TAILLE IMPLICITE DES BOUTONS
#define SELECTIF_X 40
#define SELECTIF_Y 40

	//  TAILLE IMPLICITE DE LA FENÊTRE
#define FENETRE_X 1200
#define FENETRE_Y  INITIALE_Y
	//  TAILLE IMPLICITE DU MENU. X = Y / 4


	//	POINT DE VUE IMPLICITE
#define PHI 1.7
#define PSI -1.1


	//	PARAMÈTRES DES CAPTEURS
#define GRAPHES 2 // Nombres de graphes

	//  NOMBRE DE COMMANDES
#define SELECTIF_INITIAL 16		// Nombres de boutons selectifs du menu initial
#define SELECTIF_GRAPHES 7		// Nombres de boutons selectifs des menus graphes
#define SELECTIF_FILTRES 13		// Nombres de boutons selectifs du menu filtrage
#define ROTATIF_INITIAL 8		// Nombre de boutons rotatifs du menu initial
#define ROTATIF_GRAPHES 1		// Nombre de boutons linéaires des menus graphes
#define ROTATIF_FILTRES 8		// Nombre de boutons rotatifs du menu filtrage

	//	PARAMÈTRES DES CAPTEURS
#define OBSERVABLES 4 // Nombres d'observables
#define CAPTEURS 6 // Nombres de capteurs
#define DUREE_CAPTEURS 128 // Nombre de points en mémoire

	//	PARAMÈTRES GRAPHIQUES DE LA CHAÎNE
#define SUPPORT 7			// Nombre de point du support (axes)
#define LONGUEUR_IMP 25		// Longueur implicite de la chaîne
#define RAYON_IMP 10			// Rayon implicite de la chaîne
//#define ECHELLE_IMP 10		// Echelle des graphes

#define DISTANCE_MAX 100
#define DISTANCE_IMP 10
#define DISTANCE_MIN 1


#define RATIO_C_X 0.399		// Ratio Centrage X
#define RATIO_C_Y_Q 0.263		// Ratio Centrage Y Fonction
#define RATIO_C_Y_F 0.526		// Ratio Centrage Y Fourier



		//---------- PARAMÈTRES DE DISCRÉTISATION TEMPORELLE DU SYSTÈME -------

	//	DT * DUREE = TEMPS_AFFICHAGE => temps réel

//#define TEMPS_AFFICHAGE 110	// Durée entre les affichages en ms
#define TEMPS_AFFICHAGE 210	// Durée entre les affichages en ms

#define DUREE_MIN 1			// Nombre implicite d'incrémentation du système entre deux affichages.
#define DUREE_IMP 100			// Nombre implicite d'incrémentation du système entre deux affichages.
#define DUREE_MAX 599		// Nombre maximal d'incrémentation du système entre deux affichages.

#define DT_MIN 0.00003		// Discrétisation minimale du temps
#define DT_IMP 0.0011			// Discrétisation implicite du temps
#define DT_MAX 0.003		// Discrétisation maximale du temps
		//---------------- PARAMÈTRES DE LA CORDE ---------------------

#define NOMBRE_MIN 64 	//	Nombre minimal de points
#define NOMBRE_IMP 1024		//	Nombre implicite de points
#define NOMBRE_MAX 8192 //	Nombre maximal de points

#define AMPLITUDE_MAX 77.7	//	Valeur maximale de l'amplitude de la porteuse
#define AMPLITUDE_MIN 0.077	//	Valeur minimale de l'amplitude de la porteuse

#define ECHELLE_MAX 77.7	//	Valeur maximale de l'echelle de la TF
#define ECHELLE_MIN 0.077	//	Valeur minimale de l'echelle de la TF

	//	PARAMÈTRES QUANTIQUE

#define MASSE_MAX 77.7	//	Masse maximale
#define MASSE_IMP 1.0	//	Masse implicite
#define MASSE_MIN 0.7	//	Masse minimale

#define HBAR_MAX 10.0	//	hbar maximale
#define HBAR_IMP 1.0	//	hbar implicite
#define HBAR_MIN 0.01	//	hbar minimale

#define DX_MAX 10.0		//	Pas spatial maximale
#define DX_IMP 1.0		//	Pas spatial implicite
#define DX_MIN 0.01		//	Pas spatial minimale



		//---------------- PARAMÈTRES DU FILTRAGE ---------------------

#define AMPLIFICATION_MAX 10.0	//	Valeur maximale de l'amplification
#define AMPLIFICATION_MIN 1.0	//	Valeur minimale de l'amplification

//#define FREQUENCE_MAX NOMBRE_MAX / 2	//	Valeur maximale de la fréquence des filtre
//#define FREQUENCE_MIN NOMBRE_MIN / 2	//	Valeur minimale de la fréquence des filtre

#define ORDRE_RATIO 8	//	NOMBRE / ORDRE_MAX
#define DELTA_F_RATIO 2		//	NOMBRE / DELTA_F_MAX

	//	PARAMÈTRES MOTEUR

//#define FREQUENCE_MAX 77	//	Valeur maximale de la fréquence du moteur
//#define FREQUENCE_MIN 0.077	//	Valeur minimale de la fréquence du moteur

//#define AMPLITUDE_MAX 7.7	//	Valeur maximale de l'amplitude du moteur
//#define AMPLITUDE_MIN 0.0077	//	Valeur minimale de l'amplitude du moteur

#endif
