/*
Copyright juin 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
(d'après SimFoule 2.2  simulateur de foule, décembre 2019)
Ce logiciel est un programme informatique servant à donner une représentation
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

#ifndef _GRAPHIQUE_
#define _GRAPHIQUE_

#include "../projection/projection.h"
#include "textures.h"
#include "affichage.h"


typedef struct GraphiqueT graphiqueT;
struct GraphiqueT {

	affichageT affichage;		// 	Rendu et couleurs

	texturesT textures;			//  Textures

	double facteur;		//	adaptation de la taille du menu en fonction de la
						//	hauteur de la fenêtre.

	int fenetreX;	//	largeur de la fenêtre
	int fenetreY;	//	hauteur de la fenêtre
};

		//		INITIALISATION ,  SUPRESSION ,  FONCTION ÉLÉMENTAIRE
int graphiqueInitialisation(graphiqueT * graphique, interfaceT * interface);
int graphiqueSuppression(graphiqueT * graphique);
int graphiqueNettoyage(graphiqueT * graphique);
int graphiqueMiseAJour(graphiqueT * graphique);
int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur);

		//		CONSTRUCTION DU GRAPHISME
int graphiqueCommandes(graphiqueT * graphique, commandesT * commandes, int mode);
int graphiqueAxe(graphiqueT * graphique, grapheT * graphe);
int graphiqueFonction(graphiqueT * graphique, grapheT * graphe);

#endif
/////////////////////////////////////////////////////////////////
