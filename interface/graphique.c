/*
Copyright juin 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
(d'après SimFoule 2.2 simulateur de foule, décembre 2019)
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

#include "graphique.h"

		//		INITIALISATION ,  SUPRESSION ,  FONCTION ÉLÉMENTAIRE
int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur);

		//		CONSTRUCTION DU GRAPHISME
int graphiqueMenus(graphiqueT * graphique, int mode);
int graphiqueCommandesInitiale(graphiqueT * graphique, commandesT * commandes);
int graphiqueCommandesSimulation(graphiqueT * graphique, commandesT * commandes);
int graphiqueCommandesGraphes(graphiqueT * graphique, commandesT * commandes);
int graphiqueCommandesFiltres(graphiqueT * graphique, commandesT * commandes);


	//------     INITIALISATION ,  SUPRESSION ,  FONCTION ÉLÉMENTAIRE     ------//

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

		//	Création du rendu, initialisation des couleurs SDL
	affichageInitialisation(&(*graphique).affichage, interface);

		//	Création des textures
	texturesInitialisation(&(*graphique).textures, &(*graphique).affichage);

	return 0;
}

int graphiqueSuppression(graphiqueT * graphique)
	{
			// Destruction du rendu

	SDL_DestroyRenderer((*graphique).affichage.rendu);
	return 0;
	}

int graphiqueNettoyage(graphiqueT * graphique)
	{
			//		Nettoyage du rendu

	return affichageNettoyage(&(*graphique).affichage);
	}

int graphiqueMiseAJour(graphiqueT * graphique)
	{
			//		Affichage du rendu

	SDL_RenderPresent((*graphique).affichage.rendu);

	return 0;
	}

int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur)
	{
			//		Réglage de la couleur

	return SDL_SetRenderDrawColor((*graphique).affichage.rendu, couleur.r, couleur.g, couleur.b, couleur.a);
	}


		//----------------     CONSTRUCTION DU GRAPHISME     ---------------------//

int graphiqueCommandes(graphiqueT * graphique, commandesT * commandes, int mode)
	{
		//	Dessine les menus et les commandes selon le mode

	graphiqueMenus(graphique, mode);

	if(mode == 2)	//	Mode filtrage
		{
		graphiqueCommandesInitiale(graphique, commandes);
		graphiqueCommandesGraphes(graphique, commandes);
		graphiqueCommandesFiltres(graphique, commandes);
		}
	else
		{
		graphiqueCommandesInitiale(graphique, commandes);
		graphiqueCommandesGraphes(graphique, commandes);
		}
	return 0;
	}

int graphiqueMenus(graphiqueT * graphique, int mode)
	{
			//	Dessine les menus

		//	Position du premier menu (zone 1, 2 et 3)
	SDL_Rect coordonnee = {0, 0, (*graphique).facteur * INITIALE_X, (*graphique).facteur * INITIALE_Y};

	if(mode == 0 || mode == 2)	//	Mode initiale avec ou sans filtrage
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
	coordonnee.w = (*graphique).facteur * GRAPHE_X;
	coordonnee.h = (*graphique).facteur * GRAPHE_Y;
	coordonnee.y = 0;
	coordonnee.x = (*graphique).facteur * INITIALE_X;
	if ((*graphique).textures.graphes != 0)
		{	//	Affichage du menu de la zone 4
		SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.graphes, NULL, &coordonnee);
			//	Taille et position du menu du graphe fourier (zone 6)
		coordonnee.y = (*graphique).fenetreY / 2;
			//	Affichage du menu de la zone 6
		SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.graphes, NULL, &coordonnee);
		}

		//	Position du  menu rotatif filtrage (zone 8)
	coordonnee.w = (*graphique).facteur * FILTRE_ROTATIF_X;
	coordonnee.h = (*graphique).facteur * FILTRE_ROTATIF_Y;
	coordonnee.y = 0;
	coordonnee.x = (*graphique).fenetreX - coordonnee.w;

	if(mode==2)	//	Mode filtrage
		{
		if ((*graphique).textures.filtreRotatoire != 0)
			{
			SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.filtreRotatoire, NULL, &coordonnee);
			}
				//	Menu selectif du filtrage
			//	Taille et position des sélectif du filtrage (zone 9)
		coordonnee.w = (*graphique).facteur * FILTRE_SELECTIF_X;
		coordonnee.h = (*graphique).facteur * FILTRE_SELECTIF_Y;
		coordonnee.y = (*graphique).fenetreY / 2;
		coordonnee.x = (*graphique).fenetreX - coordonnee.w - (*graphique).facteur * 85;
		if ((*graphique).textures.filtreSelectif != 0)
			{	//	Affichage du menu de la zone 9
			SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.filtreSelectif, NULL, &coordonnee);
			}
		}
	else
		{
		coordonnee.w = (*graphique).facteur * FILTRAGE_X;
		coordonnee.h = (*graphique).facteur * FILTRAGE_Y;
		if ((*graphique).textures.filtrage != 0)
			{
			SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.filtrage, NULL, &coordonnee);
			}
		}
	return 0;
	}

int graphiqueCommandesGraphes(graphiqueT * graphique, commandesT * commandes)
	{
		//	Dessine les commandes des menus graphes

	SDL_Rect coordonnee = {0, 0, 35, 35};	//	Position et taille des boutons selectifs
	coordonnee.w = (*commandes).selectifsFonctionBas-(*commandes).selectifsFonctionHaut;
	coordonnee.h = coordonnee.w;
	coordonnee.y = (*commandes).selectifsFonctionHaut;	//	position y du menu graphe-fonction
	coordonnee.x = 0;

		//	Dessine les petits boutons sélectionés
	int i;
			//	Boutons du menu graphe-fonction
	for(i=0;i<SELECTIF_GRAPHES;i++)
		{
		if((*commandes).selectifGraph[0][i].etat==1)
			{
			coordonnee.x = (*commandes).selectifGraph[0][i].X; // Position x du bouton
			if ((*graphique).textures.selectifGraph[i] != 0)
				{
				SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.selectifGraph[i], NULL, &coordonnee);
				}
			}
		}

		//	position y du menu graphe-fourier
		coordonnee.y = (*commandes).selectifsFonctionHaut + (*graphique).fenetreY / 2;

			//	Boutons du menu graphe-fourier
	for(i=0;i<SELECTIF_GRAPHES;i++)
		{
		if((*commandes).selectifGraph[1][i].etat==1)
			{
			coordonnee.x = (*commandes).selectifGraph[1][i].X; // Position x du bouton
			if ((*graphique).textures.selectifGraph[i] != 0)
				{
				SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.selectifGraph[i], NULL, &coordonnee);
				}
			}
		}
	return 0;
	}

int graphiqueCommandesFiltres(graphiqueT * graphique, commandesT * commandes)
	{
		//	Dessine les commandes du menu filtrage

	SDL_Rect coordonnee = {0, 0, 35, 35};
		//	Position et taille des boutons selectifs
	coordonnee.w = (*commandes).selectifsFonctionBas-(*commandes).selectifsFonctionHaut;
	coordonnee.h = coordonnee.w;
	coordonnee.y = (*commandes).selectifsFonctionHaut + (*graphique).fenetreY / 2;
	coordonnee.x = 0;

		//	Dessine les petits boutons sélectionés
	int i;
	for(i=0;i<SELECTIF_FILTRES;i++)
		{
		if((*commandes).selectifFiltrag[i].etat==1)
			{
			coordonnee.x = (*commandes).selectifFiltrag[i].X; // Position x du bouton
			if ((*graphique).textures.selectifFiltrag[i] != 0)
				{
				SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.selectifFiltrag[i], NULL, &coordonnee);
				}
			}
		}

		//	Dessine les aiguilles des boutons rotatifs
	int X, Y, x, y;
	graphiqueChangeCouleur(graphique, (*graphique).affichage.orange);
	X = (*commandes).rotatifFiltrDroite;
	for(i=0;i<ROTATIF_FILTRES;i++) // (*graphique).fenetreY - (*graphique).facteur * 676 + 
		{
		Y = (*commandes).rotatifFiltrag[i].Y + (*commandes).rotatifFiltrag[i].dY;
		x = X + (*commandes).rotatifFiltrag[i].positionX;
		y = Y + (*commandes).rotatifFiltrag[i].positionY;
		SDL_RenderDrawLine((*graphique).affichage.rendu, X-1, Y, x-1, y);
		SDL_RenderDrawLine((*graphique).affichage.rendu, X, Y-1, x, y-1);
		SDL_RenderDrawLine((*graphique).affichage.rendu, X+1, Y, x+1, y);
		SDL_RenderDrawLine((*graphique).affichage.rendu, X, Y+1, x, y+1);
		}

	return 0;
	}

int graphiqueCommandesInitiale(graphiqueT * graphique, commandesT * commandes)
	{
		// Dessine les commandes du menu initiale

	SDL_Rect coordonnee = {0, 0, 35, 35};	//	Position et taille des boutons selectifs
	coordonnee.w = (*commandes).selectifInitialDroite-(*commandes).selectifInitialGauche;
	coordonnee.h = coordonnee.w;
	coordonnee.y = 0;
	coordonnee.x = (*commandes).selectifInitialGauche;

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

		//	Dessine les aiguilles des boutons rotatifs
	int X, Y, x, y;
	graphiqueChangeCouleur(graphique, (*graphique).affichage.orange);
	X = (*commandes).rotatifInitialDroite;
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

int graphiqueAxe(graphiqueT * graphique, grapheT * graphe)
	{
			//			Dessin des axes xyz
	int min = (*graphe).tronque;
	int max = (*graphe).nombre - (*graphe).tronque;
	graphiqueChangeCouleur(graphique, (*graphique).affichage.contraste);

	SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xa[min], (*graphe).ya[min], (*graphe).xa[max], (*graphe).ya[max]);
	SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).axeX[2], (*graphe).axeY[2], (*graphe).axeX[3], (*graphe).axeY[3]);
	SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).axeX[4], (*graphe).axeY[4], (*graphe).axeX[5], (*graphe).axeY[5]);

		//	Extrémité des axes
	int delta = 2;
	SDL_Rect rectangle;
	rectangle.x = (*graphe).axeX[3]-delta;
	rectangle.y = (*graphe).axeY[3]-delta;
	rectangle.w = 2*delta;
	rectangle.h = 2*delta;
	SDL_RenderFillRect((*graphique).affichage.rendu, &rectangle);

	rectangle.x = (*graphe).axeX[5]-delta;
	rectangle.y = (*graphe).axeY[5]-delta;
	rectangle.w = 2*delta;
	rectangle.h = 2*delta;
	SDL_RenderFillRect((*graphique).affichage.rendu, &rectangle);

	if((*graphe).tronque<2)
		{
		rectangle.x = (*graphe).xa[max]-delta;
		rectangle.y = (*graphe).ya[max]-delta;
		rectangle.w = 2*delta;
		rectangle.h = 2*delta;
		SDL_RenderFillRect((*graphique).affichage.rendu, &rectangle);
		}

	return 0;
	}

int graphiqueFonction(graphiqueT * graphique, grapheT * graphe)
	{
				//	Dessin de la fonction
	int i;
	int tronque = (*graphe).tronque;

	if((*graphe).arriere == 0)
		{
		for(i=tronque;i<((*graphe).nombre-1-tronque);i++)
			{
			if((*graphe).coord == 1)	//	Dessin des tiges
				{
	graphiqueChangeCouleur(graphique, (*graphique).affichage.grisClair);
	SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xa[i], (*graphe).ya[i]);
				}
				//	Dessin de la courbe
			graphiqueChangeCouleur(graphique, (*graphique).affichage.orange);
			if((*graphe).trait == 1)
				{
	SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xp[i+1], (*graphe).yp[i+1]);
				}
			else
				{
				SDL_RenderDrawPoint((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i]);
				}
			}
		}
	else
		{
		for(i=((*graphe).nombre-2-tronque);i>tronque;i--)
			{
			if((*graphe).coord == 1)	//	Dessin des tiges
				{
	graphiqueChangeCouleur(graphique, (*graphique).affichage.grisClair);
	SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xa[i], (*graphe).ya[i]);
				}
				//	Dessin de la courbe
			graphiqueChangeCouleur(graphique, (*graphique).affichage.orange);
			if((*graphe).trait == 1)
				{
	SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xp[i+1], (*graphe).yp[i+1]);
				}
			else
				{
				SDL_RenderDrawPoint((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i]);
				}
			}
		}
	return 0;
	}

//////////////////////////////////////////////////////////////////////////////

