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

#include "textures.h"


int texturesNULL(texturesT * textures);
int texturesSelectifsGraphes(texturesT * textures, affichageT * affichage);
int texturesSelectifsInitial(texturesT * textures, affichageT * affichage);
int texturesSelectifsFiltres(texturesT * textures, affichageT * affichage);
int texturesMenus(texturesT * textures, affichageT * affichage);
int texturesVoyants(texturesT * textures, affichageT * affichage);


int texturesNULL(texturesT * textures)
	{
	int i;
	for(i=0;i<SELECTIF_INITIAL;i++)
		{
		(*textures).selectifInitial[i] = NULL;
		}

	for(i=0;i<SELECTIF_GRAPHES;i++)
		{
		(*textures).selectifGraph[i] = NULL;
		}

	for(i=0;i<SELECTIF_FILTRES;i++)
		{
		(*textures).selectifFiltrag[i] = NULL;
		}

	(*textures).simulation = NULL;
	(*textures).mobile = NULL;

	(*textures).initiale = NULL;
	(*textures).graphes = NULL;
	(*textures).filtreRotatoire = NULL;
	(*textures).filtreSelectif = NULL;

		//	 voyants
	(*textures).lumiereVerte = NULL;
	(*textures).lumiereRouge = NULL;
	(*textures).lumiereOrange = NULL;
	(*textures).lumiereJaune = NULL;
	return 0;
	}

int texturesInitialisation(texturesT * textures, affichageT * affichage)
	{
	texturesNULL(textures);
	texturesSelectifsInitial(textures, affichage);
	texturesSelectifsGraphes(textures, affichage);
	texturesSelectifsFiltres(textures, affichage);
	texturesMenus(textures, affichage);
	//texturesVoyants(textures, affichage);
	return 0;
}

int texturesSelectifsInitial(texturesT * textures, affichageT * affichage)
	{
		//	 Boutons selectifInitial
	SDL_Surface *image = 0;

	image = SDL_LoadBMP("./image/constant.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/constant.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[0] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[0] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/rectangle.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/rectangle.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[1] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[1] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/scie.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/scie.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[2] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[2] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/sinus.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/sinus.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[3] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[3] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/aperiodiq.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/aperiodiq.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[4] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[4] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/periodique.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/periodique.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[5] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[5] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/gauss.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/gauss.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[6] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[6] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/lorentz.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/lorentz.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[7] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[7] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/sincar.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/sincar.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[8] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[8] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/zero.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/lorentz.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[9] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[9] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/un.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/sincar.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[10] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[10] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/constant.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/constant.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[11] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[11] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/dirac.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/dirac.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[12] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[12] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/sinus.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/sinus.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[13] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[13] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/spirale.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/spirale.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifInitial[14] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifInitial[14] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	return 0;
}

int texturesSelectifsGraphes(texturesT * textures, affichageT * affichage)
	{
		//	 Boutons des menus graphes
	SDL_Surface *image = 0;

	image = SDL_LoadBMP("./image/implicite.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/implicite.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifGraph[0] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifGraph[0] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/imaginaire.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/imaginaire.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifGraph[1] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifGraph[1] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/reel.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/reel.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifGraph[2] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifGraph[2] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/point.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/point.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifGraph[3] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifGraph[3] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/relie.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/relie.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifGraph[4] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifGraph[4] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/vecteur.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/vecteur.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifGraph[5] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifGraph[5] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/vide.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/vide.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifGraph[6] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifGraph[6] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	return 0;
}

int texturesSelectifsFiltres(texturesT * textures, affichageT * affichage)
	{
		//	 Boutons du menu filtrage
	SDL_Surface *image = 0;

	image = SDL_LoadBMP("./image/passeBas.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/passeBas.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifFiltrag[1] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifFiltrag[1] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/passeBasDroite.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/passeBasDroite.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifFiltrag[2] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifFiltrag[2] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/passeBasGauche.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/passeBasGauche.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifFiltrag[3] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifFiltrag[3] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/passeHaut.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/passeHaut.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifFiltrag[5] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifFiltrag[5] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/passeHautGauche.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/passeHautGauche.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifFiltrag[6] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifFiltrag[6] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/passeHautDroite.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/passeHautDroite.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifFiltrag[7] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifFiltrag[7] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/passeBande.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/passeBande.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifFiltrag[9] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifFiltrag[9] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/passeBandeGauche.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/passeBandeGauche.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifFiltrag[10] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifFiltrag[10] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/passeBandeDroite.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/passeBandeDroite.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifFiltrag[11] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifFiltrag[11] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	image = SDL_LoadBMP("./image/inverse.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image ./image/inverse.bmp : %s\n",SDL_GetError());
		}
	(*textures).selectifFiltrag[12] = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textures).selectifFiltrag[12] == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	return 0;
}

int texturesMenus(texturesT * textures, affichageT * affichage)
	{

	SDL_Surface *panneau = 0;

	panneau = SDL_LoadBMP("./image/initiale.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, ./image/initiale.bmp : %s\n",SDL_GetError());
		}
	(*textures).initiale = SDL_CreateTextureFromSurface((*affichage).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*textures).initiale == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	panneau = SDL_LoadBMP("./image/simulation.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, ./image/simulation.bmp : %s\n",SDL_GetError());
		}
	(*textures).simulation = SDL_CreateTextureFromSurface((*affichage).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*textures).simulation == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	panneau = SDL_LoadBMP("./image/graphes.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, ./image/graphes.bmp : %s\n",SDL_GetError());
		}
	(*textures).graphes = SDL_CreateTextureFromSurface((*affichage).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*textures).graphes == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	panneau = SDL_LoadBMP("./image/filtrageRotatoire.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, ./image/filtrageRotatoire.bmp : %s\n",SDL_GetError());
		}
	(*textures).filtreRotatoire = SDL_CreateTextureFromSurface((*affichage).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*textures).filtreRotatoire == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	panneau = SDL_LoadBMP("./image/filtrageSelectif.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, ./image/filtrageSelectif.bmp : %s\n",SDL_GetError());
		}
	(*textures).filtreSelectif = SDL_CreateTextureFromSurface((*affichage).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*textures).filtreSelectif == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}

	panneau = SDL_LoadBMP("./image/filtrage.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, ./image/filtrage.bmp : %s\n",SDL_GetError());
		}
	(*textures).filtrage = SDL_CreateTextureFromSurface((*affichage).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*textures).filtrage == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		}


	return 0;
}

int texturesVoyants(texturesT * textures, affichageT * affichage)
	{
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

//////////////////////////////////////////////////////////////////////////////



