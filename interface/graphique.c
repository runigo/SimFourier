/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.3 Transformation de Fourier
(d'après SimFoule 2.2 simulateur de foule, décembre 2019)
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

#include "graphique.h"

		//		INITIALISATION ,  SUPRESSION

		//		CONSTRUCTION DU GRAPHISME
int graphiqueMenus(graphiqueT * graphique, int mode);

int graphiqueCommandesInitiale(graphiqueT * graphique, commandesT * commandes);
int graphiqueCommandesSimulation(graphiqueT * graphique, commandesT * commandes);

		//			GRAPHISME
int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur);
int graphiqueTige(graphiqueT * graphique, int X, int Y, int x, int y, float sinT, float cosT);
int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur);

		//		INITIALISATION ,  SUPRESSION


int graphiqueInitialisation(graphiqueT * graphique, interfaceT * interface)
	{
    if (graphique == NULL || interface == NULL)
    	{
		fprintf(stderr, "ERREUR : graphiqueInitialisation, pointeur non valide");
		exit(0);
	    }

	int fenetreX;
	int fenetreY;

	SDL_GetWindowSize((*interface).fenetre, &fenetreX, &fenetreY);

	(*graphique).fenetreX=fenetreX;
	(*graphique).fenetreY=fenetreY;

	affichageInitialisation(&(*graphique).affichage, interface);

	texturesInitialisation(&(*graphique).textures, &(*graphique).affichage);

	return 0;
}

int graphiqueSuppression(graphiqueT * graphique)
	{
		// Destruction du rendu
	SDL_DestroyRenderer((*graphique).affichage.rendu);
	return 0;
	}

		//		CONSTRUCTION DU GRAPHISME

int graphiqueNettoyage(graphiqueT * graphique)
	{		//		Nettoyage du rendu
	return affichageNettoyage(&(*graphique).affichage);
	}

int graphiqueMiseAJour(graphiqueT * graphique)
	{		//		Affichage du rendu
	SDL_RenderPresent((*graphique).affichage.rendu);
	return 0;
	}

int graphiqueCommandes(graphiqueT * graphique, commandesT * commandes, int mode)
	{
		//	Dessine les menus et les commandes selon le mode

	graphiqueMenus(graphique, mode);

	if(mode == 0)
		{
		graphiqueCommandesInitiale(graphique, commandes);
		}
/*	else
		{
		graphiqueCommandesSimulation(graphique, commandes);
		}*/
	
	return 0;
	}

int graphiqueMenus(graphiqueT * graphique, int mode)
	{
		//	Dessine les menus

		//	Position du premier menu (zone 1, 2 et 3)
	SDL_Rect coordonnee = {0, 0, (*graphique).facteur * MENUS_X, (*graphique).facteur * MENUS_Y};

	if(mode==0)	//	Mode initiale
		{
		if ((*graphique).textures.initiale != 0)
			{
			SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.initiale, NULL, &coordonnee);
			}
		}
	else		//	Mode simulation
		{
		if ((*graphique).textures.simulation != 0)
			{
			SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.simulation, NULL, &coordonnee);
			}
		}

			//	Menu des graphes
		//	Taille et position du menu du graphe fonction (zone 4)
	coordonnee.w = (*graphique).facteur * 800;
	coordonnee.h = (*graphique).facteur * 55;
	coordonnee.y = 0;
	coordonnee.x = (*graphique).facteur * MENUS_X;
	if ((*graphique).textures.graphes != 0)
		{	//	Affichage du menu de la zone 4
		SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.graphes, NULL, &coordonnee);
			//	Taille et position du menu du graphe fourier (zone 6)
		coordonnee.y = 300;
			//	Affichage du menu de la zone 6
		SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.graphes, NULL, &coordonnee);
		}
	return 0;
	}

int graphiqueCommandesInitiale(graphiqueT * graphique, commandesT * commandes)
	{
		// Dessine les commandes du menu initiale

	SDL_Rect coordonnee = {0, 0, 35, 35};	//	Position et taille des boutons selectifs
	coordonnee.w = (*commandes).selectifsDroite-(*commandes).selectifsGauche;
	coordonnee.h = coordonnee.w;
	coordonnee.y = 0;
	coordonnee.x = (*commandes).selectifsGauche;

		//	Dessine les petits boutons sélectionés
	int i;
	for(i=0;i<SELECTIF_INITIAL;i++)
		{
		if((*commandes).selectifInitial[i].etat==1)
			{
			coordonnee.y = (*commandes).selectifInitial[i].Y; // Position y du bouton
			if ((*graphique).textures.selectifInitial[i] != 0)
				{
				SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.selectifInitial[i], NULL, &coordonnee);
				}
			}
		}
	for(i=0;i<SELECTIF_GRAPHES;i++)
		{
		if((*commandes).selectifGraphe[i].etat==1)
			{
			coordonnee.y = (*commandes).selectifGraphe[i].Y; // Position y du bouton
			if ((*graphique).textures.selectifGraphe[i] != 0)
				{
				SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.selectifGraphe[i], NULL, &coordonnee);
				}
			}
		}

		//	Dessine les aiguilles des boutons rotatifs
	int X, Y, x, y;
	graphiqueChangeCouleur(graphique, (*graphique).affichage.orange);
	X = (*commandes).rotatifsDroite;
	for(i=0;i<ROTATIF_INITIAL;i++)
		{
		Y = (*commandes).rotatifInitial[i].Y + (*commandes).rotatifInitial[i].dY;
		x = X + (*commandes).rotatifInitial[i].positionX;
		y = Y + (*commandes).rotatifInitial[i].positionY;
		SDL_RenderDrawLine((*graphique).affichage.rendu, X-1, Y, x-1, y);
		SDL_RenderDrawLine((*graphique).affichage.rendu, X, Y-1, x, y-1);
		SDL_RenderDrawLine((*graphique).affichage.rendu, X+1, Y, x+1, y);
		SDL_RenderDrawLine((*graphique).affichage.rendu, X, Y+1, x, y+1);
		}

	return 0;
	}

int graphiqueAxeEtFonction(graphiqueT * graphique, grapheT * graphe)
	{
//
//                                                Z
//                                          Y              X'
//                                                O
//                                                      Y'
//                                                Z'
//             X


		//	Point du support
	graphiqueChangeCouleur(graphique, (*graphique).affichage.contraste);
		// Axes x'x, y'y, z'z
	if((*graphe).arriere <= 0) // Vue de devant
		{
		SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).supporX[0], (*graphe).supporY[0], (*graphe).supporX[1], (*graphe).supporY[1]);
		SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).supporX[2], (*graphe).supporY[2], (*graphe).supporX[3], (*graphe).supporY[3]);
		SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).supporX[4], (*graphe).supporY[4], (*graphe).supporX[5], (*graphe).supporY[5]);
		}


		// Chaine de pendule
	graphiquePendule(graphique, graphe);

	graphiqueChangeCouleur(graphique, (*graphique).affichage.contraste);

		// Axes x'x, y'y, z'z
	if((*graphe).arriere > 0) // Vue de derrière
		{
		SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).supporX[0], (*graphe).supporY[0], (*graphe).supporX[1], (*graphe).supporY[1]);
		SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).supporX[2], (*graphe).supporY[2], (*graphe).supporX[3], (*graphe).supporY[3]);
		SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).supporX[4], (*graphe).supporY[4], (*graphe).supporX[5], (*graphe).supporY[5]);
		}

	return 0;
	}

int graphiquePendule(graphiqueT * graphique, grapheT * graphe)
	{
	int i;

			//	Dessin de la première tige
	//	graphiqueChangeCouleur(graphique, (*graphique).affichage.grisClair);
	//	SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[(*graphe).nombre], (*graphe).yp[(*graphe).nombre], (*graphe).xa[(*graphe).nombre], (*graphe).ya[(*graphe).nombre]);

	if((*graphe).arriere == 0)
		{
		for(i=0;i<((*graphe).nombre-1);i++)
			{
				//	Dessin des tiges
			graphiqueChangeCouleur(graphique, (*graphique).affichage.grisClair);
			SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xa[i], (*graphe).ya[i]);
				//	Dessin de la courbe
			graphiqueChangeCouleur(graphique, (*graphique).affichage.orange);
			SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xp[i+1], (*graphe).yp[i+1]);
			}
		}
	else
		{
		for(i=((*graphe).nombre-2);i>0;i--)
			{
				//	Dessin des tiges
			graphiqueChangeCouleur(graphique, (*graphique).affichage.grisClair);
			SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xa[i], (*graphe).ya[i]);
				//	Dessin de la courbe
			graphiqueChangeCouleur(graphique, (*graphique).affichage.orange);
			SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xp[i+1], (*graphe).yp[i+1]);
			}
		}
	return 0;
	}

		//	FONCTIONS DE DESSINS GÉOMÉTRIQUES

int graphiqueTige(graphiqueT * graphique, int X, int Y, int x, int y, float sinT, float cosT)
	{
	int decalageDroit = 0;
	int decalageDiag = 1;
	(void)sinT;
	(void)cosT;

	SDL_SetRenderDrawColor((*graphique).affichage.rendu, 25, 25, 25, 255);

		// Horizontales 		    R	  V	  B
	//SDL_SetRenderDrawColor((*graphique).affichage.rendu, sinusC, 55+sinusC, 125+sinusC, 255-sinusC);
	//graphiqueChangeCouleur(graphique, (*graphique).cyan);
	SDL_RenderDrawLine((*graphique).affichage.rendu, X-decalageDroit, Y-decalageDiag, x-decalageDroit, y-decalageDiag);
	SDL_RenderDrawLine((*graphique).affichage.rendu, X+decalageDroit, Y+decalageDiag, x+decalageDroit, y+decalageDiag);

		// Verticale
	//SDL_SetRenderDrawColor((*graphique).affichage.rendu, 250-sinusC, 250-sinusC, 25, 255);
	//graphiqueChangeCouleur(graphique, (*graphique).jaune);
	SDL_RenderDrawLine((*graphique).affichage.rendu, X+decalageDiag, Y+decalageDroit, x+decalageDiag, y+decalageDroit);
	SDL_RenderDrawLine((*graphique).affichage.rendu, X-decalageDiag, Y-decalageDroit, x-decalageDiag, y-decalageDroit);

	return 0;
	}

int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur)
	{
	return SDL_SetRenderDrawColor((*graphique).affichage.rendu, couleur.r, couleur.g, couleur.b, couleur.a);
	}

//////////////////////////////////////////////////////////////////////////////

