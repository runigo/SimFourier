/*
Copyright février 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
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
//int graphiqueLigne(graphiqueT * graphique, int X, int Y, int x, int y);
int graphiqueTige(graphiqueT * graphique, int X, int Y, int x, int y, float sinT, float cosT);
int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur);
//int graphiqueMasse(graphiqueT * graphique, int abs, int ord);
//int graphiqueMobile(graphiqueT * graphique, grapheT * graphe);

		//		INITIALISATION ,  SUPRESSION


int graphiqueInitialisation(graphiqueT * graphique, interfaceT * interface, int taille)
	{
    if (graphique == NULL || interface == NULL)
    	{
        return -1; // Erreur : pointeur non valide
	    }

	int fenetreX;
	int fenetreY;

	(*graphique).taille = taille;

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
	else
		{
		graphiqueCommandesSimulation(graphique, commandes);
		}
	
	return 0;
	}

int graphiqueMenus(graphiqueT * graphique, int mode)
	{
		//	Dessine le menu correspondant au mode

	SDL_Rect coordonnee = {0, 0, MENUS_X, MENUS_Y};
	if(mode==0)		//	Menu initiale
		{
		if ((*graphique).textures.initiale != 0)
			{
			SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.initiale, NULL, &coordonnee);
			}
		}
	else		//	Menu simulation
		{
		if ((*graphique).textures.simulation != 0)
			{
			SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.simulation, NULL, &coordonnee);
			}
		}
	return 0;
	}

int graphiqueCommandesSimulation(graphiqueT * graphique, commandesT * commandes)
	{
		// Dessine les commandes du menu simulation

	SDL_Rect coordonnee = {0, 0, (*graphique).fenetreX, (*graphique).fenetreY};
	//int centrage = 5;
	coordonnee.w=20;
	coordonnee.h=20;
	coordonnee.x = (*commandes).selectifsGauche;	// Positon X de la zone des petits boutons
	int i;
	int X, Y, x, y;

	for(i=0;i<SELECTIF_COMMANDES;i++)
		{
		if( (*commandes).selectif[i].etat == 1 )
			{
			coordonnee.y = (*commandes).selectif[i].Y; // Positon Y des petits boutons
			//	Dessin des petits boutons
			if ((*graphique).textures.mobile != 0)
				{
				SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.mobile, NULL, &coordonnee);
				}
			}
		}

	graphiqueChangeCouleur(graphique, (*graphique).affichage.orange);
	X=(*commandes).rotatifsDroite;
	for(i=0;i<ROTATIF_COMMANDES;i++)
		{
		Y=(*commandes).rotatif[i].centre;
		x=X+(*commandes).rotatif[i].X;
		y=Y+(*commandes).rotatif[i].Y;
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

	SDL_Rect coordonnee = {0, (*graphique).fenetreY - 35, 238, 35};

	//int centrage = 12;
	coordonnee.w=(*commandes).selectifsDroite-(*commandes).selectifsGauche;
	coordonnee.h=coordonnee.w;
	coordonnee.y = (*commandes).fourierBas;	// Positon Y de la zone du bas
	coordonnee.x = (*commandes).selectifsGauche;	// Positon X de la zone des petits boutons

				// Boutons selectif
	int i;
	for(i=0;i<SELECTIF_COMMANDES;i++)
		{
		if((*commandes).selectif[i].etat==1)
			{
			coordonnee.y = (*commandes).selectif[i].Y; // Positon Y des boutons
			//	Dessin des boutons
			if ((*graphique).textures.selectif[i] != 0)
				{
				SDL_RenderCopy((*graphique).affichage.rendu, (*graphique).textures.selectif[i], NULL, &coordonnee);
				}
			}
		}

							// Boutons rotatifs
	int X, Y, x, y;
	graphiqueChangeCouleur(graphique, (*graphique).affichage.orange);
	X=(*commandes).rotatifsDroite;
	for(i=0;i<ROTATIF_COMMANDES;i++)
		{
		Y=(*commandes).rotatif[i].Y+(*commandes).rotatif[i].dY;
		x=X+(*commandes).rotatif[i].positionX;
		y=Y+(*commandes).rotatif[i].positionY;
		SDL_RenderDrawLine((*graphique).affichage.rendu, X-1, Y, x-1, y);
		SDL_RenderDrawLine((*graphique).affichage.rendu, X, Y-1, x, y-1);
		SDL_RenderDrawLine((*graphique).affichage.rendu, X+1, Y, x+1, y);
		SDL_RenderDrawLine((*graphique).affichage.rendu, X, Y+1, x, y+1);
		}

	return 0;
	}

int graphiquePenduleSupport(graphiqueT * graphique, grapheT * graphe)
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

//	if((*graphe).arriere != 0) // Vue de derrière, la chaîne est dessinée vers les précédents.
//	else {(*graphe).arriere = 0;}

	graphiqueChangeCouleur(graphique, (*graphique).affichage.orange);
	for(i=0;i<(*graphe).nombre;i++)
		{
		//	Dessin des tiges
	SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xa[i], (*graphe).ya[i]);
	//	graphiqueTige(graphique, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xa[i], (*graphe).ya[i], 0, 0);//(*graphe).sinTheta, (*graphe).cosTheta);
		}

	graphiqueChangeCouleur(graphique, (*graphique).affichage.contraste);
	for(i=0;i<((*graphe).nombre-1);i++)
		{
		//	Dessin de la courbe
	SDL_RenderDrawLine((*graphique).affichage.rendu, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xp[i+1], (*graphe).yp[i+1]);
	//	graphiqueTige(graphique, (*graphe).xp[i], (*graphe).yp[i], (*graphe).xa[i], (*graphe).ya[i], 0, 0);//(*graphe).sinTheta, (*graphe).cosTheta);
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

