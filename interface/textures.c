/*
Copyright février 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.1 Transformation de Fourier
(d'après SimFoule 2.2  simulateur de foule, décembre 2019)
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

#include "textures.h"


int texturesMenus(texturesT * textures, affichageT * affichage);
int texturesBoutons(texturesT * textures, affichageT * affichage);


int texturesInitialisation(texturesT * textures, affichageT * affichage)
	{
	texturesBoutons(textures, affichage);
	texturesMenus(textures, affichage);
	return 0;
}

int texturesMenus(texturesT * textures, affichageT * affichage)
	{
/*
	SDL_Surface *panneau = 0;

	panneau = SDL_LoadBMP("./image/SimFouleUniforme.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, ./image/SimFouleUniforme.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textures).simfoule = SDL_CreateTextureFromSurface((*affichage).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*textures).simfoule == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}
*/

	SDL_Surface *lumiereVerte = 0;

	lumiereVerte = SDL_LoadBMP("./image/lumiereVerte.bmp");
	if (!lumiereVerte)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereVerte.bmp : %s\n",SDL_GetError());
		}
	(*textures).lumiereVerte = SDL_CreateTextureFromSurface((*affichage).rendu, lumiereVerte);
	SDL_FreeSurface(lumiereVerte);
	if ((*textures).lumiereVerte == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	SDL_Surface *lumiereRouge = 0;

	lumiereRouge = SDL_LoadBMP("./image/lumiereRouge.bmp");
	if (!lumiereRouge)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereRouge.bmp : %s\n",SDL_GetError());
		}
	(*textures).lumiereRouge = SDL_CreateTextureFromSurface((*affichage).rendu, lumiereRouge);
	SDL_FreeSurface(lumiereRouge);
	if ((*textures).lumiereRouge == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	SDL_Surface *lumiereJaune = 0;

	lumiereJaune = SDL_LoadBMP("./image/lumiereJaune.bmp");
	if (!lumiereJaune)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereJaune.bmp : %s\n",SDL_GetError());
		}
	(*textures).lumiereJaune = SDL_CreateTextureFromSurface((*affichage).rendu, lumiereJaune);
	SDL_FreeSurface(lumiereJaune);
	if ((*textures).lumiereJaune == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	SDL_Surface *lumiereOrange = 0;

	lumiereOrange = SDL_LoadBMP("./image/lumiereOrange.bmp");
	if (!lumiereOrange)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereOrange.bmp : %s\n",SDL_GetError());
		}
	(*textures).lumiereOrange = SDL_CreateTextureFromSurface((*affichage).rendu, lumiereOrange);
	SDL_FreeSurface(lumiereOrange);
	if ((*textures).lumiereOrange == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

		fprintf(stderr,"texturesInitialisation \n");



	return 0;
}

int texturesBoutons(texturesT * textures, affichageT * affichage)
	{
		//	 Boutons

	SDL_Surface *image = 0;

	image = SDL_LoadBMP("./image/aperio.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonVide.bmp : %s\n",SDL_GetError());
		}
	(*textures).boutonVide = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).boutonVide == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}


	image = SDL_LoadBMP("./image/constant.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonMur.bmp : %s\n",SDL_GetError());
		}
	(*textures).boutonMur = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).boutonMur == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}


	image = SDL_LoadBMP("./image/dirac.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonSortie.bmp : %s\n",SDL_GetError());
		}
	(*textures).boutonSortie = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).boutonSortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/gauss.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonMobile.bmp : %s\n",SDL_GetError());
		}
	(*textures).boutonMobile = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).boutonMobile == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}


	image = SDL_LoadBMP("./image/lorentz.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonPoint.bmp : %s\n",SDL_GetError());
		}
	(*textures).boutonPoint = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).boutonPoint == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}


	image = SDL_LoadBMP("./image/periodique.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonTrait.bmp : %s\n",SDL_GetError());
		}
	(*textures).boutonTrait = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).boutonTrait == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}


	SDL_Surface *menu = 0;
	menu = SDL_LoadBMP("./image/rectangle.bmp");
	if (!menu)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleConstruction01.bmp : %s\n",SDL_GetError());
		}
	(*textures).boutonRectangle = SDL_CreateTextureFromSurface((*affichage).rendu, menu);
	SDL_FreeSurface(menu);
	if ((*textures).boutonRectangle == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////



