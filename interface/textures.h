/*
Copyright juin 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
(d'après SimFoule 2.2  simulateur de foule, décembre 2019)
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

#ifndef _TEXTURES_
#define _TEXTURES_

#include "affichage.h"

struct TexturesT {

	SDL_Texture *simulation;			//	Menu simulation
	SDL_Texture *mobile;

	SDL_Texture *initiale;			//	Menu initiale
	SDL_Texture *selectifInitial[SELECTIF_INITIAL];

	SDL_Texture *graphes;			//	Menu graphes
	SDL_Texture *selectifGraph[SELECTIF_GRAPHES];

	SDL_Texture *filtreRotatoire;			//	Menu filtrage
	SDL_Texture *filtreSelectif;
	SDL_Texture *selectifFiltrag[SELECTIF_FILTRES];
	SDL_Texture *filtrage;


		//	 voyants
	SDL_Texture *lumiereVerte;
	SDL_Texture *lumiereRouge;
	SDL_Texture *lumiereOrange;
	SDL_Texture *lumiereJaune;

};
typedef struct TexturesT texturesT;

int texturesInitialisation(texturesT * textures, affichageT * affichage);

#endif
/////////////////////////////////////////////////////////////////
