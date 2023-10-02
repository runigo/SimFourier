/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
SimFourier 0.0 Transformation de Fourier
Ce logiciel est un programme informatique servant à donner une représentation
graphique de la transformation de Fourier à 1 dimension.
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

#include "graphe.h"
#include "commandes.h"
#include "interface.h"
#include "capteurs.h"


struct GraphiqueT {

	SDL_Renderer *rendu;

	SDL_Color fond;
	SDL_Color contraste;
	
	SDL_Color orange;
	SDL_Color orangeF;

	SDL_Color rouge;
	SDL_Color bleue;

	SDL_Color vert;
	SDL_Color vertF;

	SDL_Color gris;
	SDL_Color grisF;

	SDL_Color cyan;
	SDL_Color aubergine;

	SDL_Texture *masse;
	SDL_Texture *SimFourier;
	int taille;

		int fenetreX;	// hauteur de la fenêtre
		int fenetreY;	// largeur de la fenêtre
};
typedef struct GraphiqueT graphiqueT;

int graphiqueDestruction(graphiqueT * graphique);
int graphiqueInitialisation(graphiqueT * graphique, interfaceT * interface, int fond);

int graphiqueNettoyage(graphiqueT * graphique);
int graphiqueMiseAJour(graphiqueT * graphique);

int graphiqueCommandes(graphiqueT * graphique, commandesT * commandes);
int graphiqueCapteurs(graphiqueT * graphique, capteursT * capteurs);
void graphiquePenduleSupportPlein(graphiqueT * graphique, grapheT * graphe);
void graphiquePenduleSupport(graphiqueT * graphique, grapheT * graphe);
void graphiquePendule(graphiqueT * graphique, grapheT * graphe);

#endif
/////////////////////////////////////////////////////////////////
