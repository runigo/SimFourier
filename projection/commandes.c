/*
Copyright avril 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.3 Transformation de Fourier
(d'après SiCP 2.5 simulateur de chaîne de pendules, fevrier 2021)
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

#include "commandes.h"

int commandesAjusteZones(commandesT * commandes, int fenetreX, int fenetreY);
int commandesAjusteRotatifsInitiale(commandesT * commandes, float facteur);
int commandesAjusteSelectifsInitiale(commandesT * commandes, float facteur);
int commandesAjusteRotatifsGraphes(commandesT * commandes, float facteur);
int commandesAjusteSelectifsGraphes(commandesT * commandes, float facteur);
//int commandesInitialise(commandesT * commandes, float facteur);

int commandesAjusteCommandes(commandesT * commandes, int fenetreX, int fenetreY)
	{
			//	Réglage des positions des zones et des commandes en fonction de la taille de la fenêtre

	commandesAjusteZones(commandes, fenetreX, fenetreY);

	float facteur = 1.0;
	if(fenetreY<MENUS_Y)
		{
		facteur = (float)fenetreY/MENUS_Y;
		}

	commandesAjusteRotatifsInitiale(commandes, facteur);
	commandesAjusteSelectifsInitiale(commandes, facteur);
	commandesAjusteRotatifsGraphes(commandes, facteur);
	commandesAjusteSelectifsGraphes(commandes, facteur);

	return 0;
	}

int commandesAjusteZones(commandesT * commandes, int fenetreX, int fenetreY)
	{
				//	Positions des zones

	float facteur = 1.0;
	if(fenetreY < MENUS_Y)
		{
		facteur = (float)fenetreY / MENUS_Y;
		}

		// Zones suivant Y du menu 1
	(*commandes).mode = facteur * 24;

		// Zones suivant X des fonctions (zones 4, 5, 6, 7)
	(*commandes).fonctionsGauche = facteur * 200;
	(*commandes).fonctionsDroite = fenetreX - facteur * 100;

		// Zones suivant Y des fonctions
	(*commandes).fonctionHaut = facteur * 55;		//	frontière 4-5
	(*commandes).fonctionBas = fenetreY / 2;		//	frontière 5-6
	(*commandes).fourierHaut = (*commandes).fonctionBas + (*commandes).fonctionHaut;	//	6-7
	(*commandes).fourierBas = fenetreY;				//	frontière basse

			//	Zones des commandes du menu 2 suivant X
	(*commandes).rotatifsGauche = facteur * 20;
	(*commandes).rotatifsDroite = facteur * 100;

			//	Zones des commandes du menu 3 suivant X
	(*commandes).selectifsGauche = facteur * 134;
	(*commandes).selectifsDroite = facteur * 176;

	return 0;
	}

int commandesAjusteRotatifsInitiale(commandesT * commandes, float facteur)
	{
				//	Positions des boutons rotatifs du menu initiale
	int i;
	for(i=0;i<ROTATIF_INITIAL;i++)
		{
		rotatifInitialise(&(*commandes).rotatifInitial[i], (*commandes).rotatifsDroite-(*commandes).rotatifsGauche);
		}
	(*commandes).rotatifInitial[0].Y = facteur * 75; 	//	Largeur
	(*commandes).rotatifInitial[1].Y = facteur * 168;	//	Largeur
	(*commandes).rotatifInitial[2].Y = facteur * 285;	//	Symetrie
	(*commandes).rotatifInitial[3].Y = facteur * 404;	//	Phase
	(*commandes).rotatifInitial[4].Y = facteur * 548;	//	Période
	(*commandes).rotatifInitial[5].Y = facteur * 640;	//	Période

	return 0;
	}

int commandesAjusteSelectifsInitiale(commandesT * commandes, float facteur)
	{
					//	Positions des boutons selectifs du menu initiale
	int i;
	for(i=0;i<SELECTIF_INITIAL;i++)
		{
		selectifInitialise(&(*commandes).selectifInitial[i], (*commandes).selectifsDroite - (*commandes).selectifsGauche);
		}
			// BOUTONS SELECTIFS SUIVANT Y
	(*commandes).selectifInitial[0].Y = facteur * 69;  	//	Constant
	(*commandes).selectifInitial[1].Y = facteur * 114;		//	Rectangle
	(*commandes).selectifInitial[2].Y = facteur * 159;		//	Scie
	(*commandes).selectifInitial[3].Y = facteur * 203;		//	Sinus
	(*commandes).selectifInitial[4].Y = facteur * 264;		//	Apériodique
	(*commandes).selectifInitial[5].Y = facteur * 310;		//	Périodique
	(*commandes).selectifInitial[6].Y = facteur * 355;		//	Gaussienne
	(*commandes).selectifInitial[7].Y = facteur * 400;		//	Lorentzienne
	(*commandes).selectifInitial[8].Y = facteur * 444;		//	Sinus Cardinal
	(*commandes).selectifInitial[9].Y = facteur * 543;		//	Constant
	(*commandes).selectifInitial[10].Y = facteur * 588;	//	Dirac
	(*commandes).selectifInitial[11].Y = facteur * 631;	//	Sinus
	(*commandes).selectifInitial[12].Y = facteur * 677;	//	Complexe

	return 0;
	}

int commandesAjusteRotatifsGraphes(commandesT * commandes, float facteur)
	{
				//	Positions des boutons rotatifs des menus graphes
	int i;
	for(i=0;i<ROTATIF_GRAPHES;i++)
		{
		rotatifInitialise(&(*commandes).rotatifGraph[0][i], facteur*(621-483) );
		rotatifInitialise(&(*commandes).rotatifGraph[1][i], facteur*(621-483) );
		}
	(*commandes).rotatifGraph[0][0].X = facteur * 483; 	//	Largeur
	(*commandes).rotatifGraph[1][0].X = facteur * 483; 	//	Largeur

	return 0;
	}

int commandesAjusteSelectifsGraphes(commandesT * commandes, float facteur)
	{
				//	Positions des boutons selectifs des menus graphes
	int i, j;

	for(j=0;j<2;j++)
		{
		for(i=0;i<SELECTIF_GRAPHES;i++)
			{
			selectifInitialise(&(*commandes).selectifGraph[j][i], (*commandes).selectifsDroite - (*commandes).selectifsGauche);
			}
				// BOUTONS SELECTIFS SUIVANT X
		(*commandes).selectifGraph[j][0].X = facteur * 290;  	//	Implicite
		(*commandes).selectifGraph[j][1].X = facteur * 330;		//	Imaginaire
		(*commandes).selectifGraph[j][2].X = facteur * 377;		//	Reel
		(*commandes).selectifGraph[j][3].X = facteur * 424;		//	Sans
		(*commandes).selectifGraph[j][4].X = facteur * 683;		//	Point
		(*commandes).selectifGraph[j][5].X = facteur * 723;		//	Relié
		(*commandes).selectifGraph[j][6].X = facteur * 786;		//	Vecteur
		(*commandes).selectifGraph[j][7].X = facteur * 825;		//	Cartésien
		(*commandes).selectifGraph[j][8].X = facteur * 872;		//	Sans
		}
	return 0;
	}

int commandesInitialiseSouris(commandesT * commandes, int sourisX, int sourisY)
	{
		 // Rayon des petits boutons
	int rayonX=(*commandes).selectifsDroite-(*commandes).selectifsGauche;
	int rayonY=rayonX;

	if(sourisX<(*commandes).rotatifsDroite)
		{
		rayonX=(*commandes).rotatifsDroite-(*commandes).rotatifsGauche;
		rayonY=rayonX;
		}
/*	else 
		{
		if(sourisY>(*commandes).bas) // Zone du bas
			{
			rayonX=(*commandes).triangleX;
			rayonY=(*commandes).triangleY;
			}
		}
*/
		// POSITION DE LA SOURIS
	(*commandes).sourisX = sourisX; // position X de la souris
	(*commandes).sourisY = sourisY; // position Y de la souris

	(*commandes).sourisGauche = sourisX-rayonX; // position X de la souris - RayonBoutonX
	(*commandes).sourisDroite = sourisX+rayonX; // position X de la souris + RayonBoutonX
	(*commandes).sourisHaut = sourisY-rayonY; // position Y de la souris - RayonBoutonY
	(*commandes).sourisBas = sourisY+rayonY; // position Y de la souris + RayonBoutonY

	return 0;
	}

int commandesSourisZone(commandesT * commandes)
	{
		//	Retourne la zone où se trouve la souris

	if((*commandes).sourisX < (*commandes).fonctionsGauche)	//	MENU 1 = zones 1, 2 et 3
		{
		if((*commandes).sourisY < (*commandes).mode)
			{	//	Selection initiale/simulation
				printf("commandesSourisZone 1\n");
			return 1;
			}
		if((*commandes).sourisX < (*commandes).rotatifsDroite && (*commandes).sourisX > (*commandes).rotatifsGauche)
			{	//	Rotatif
				printf("commandesSourisZone 2\n");
			return 2;
			}
		if((*commandes).sourisX < (*commandes).selectifsDroite && (*commandes).sourisX > (*commandes).selectifsGauche)
			{	//	Selectif
				printf("commandesSourisZone 3\n");
			return 3;
			}
		}
	else
		{
		if((*commandes).sourisX < (*commandes).fonctionsDroite)	//		MENU 2 = zones 4, 5, 6 et 7
			{
			if((*commandes).sourisY < (*commandes).fonctionHaut)
				{	//	Menu fonction
				printf("commandesSourisZone 4\n");
				return 4;
				}
			if((*commandes).sourisY < (*commandes).fonctionBas)
				{	//	Fonction
				printf("commandesSourisZone 5\n");
				return 5;
				}
			if((*commandes).sourisY < (*commandes).fourierHaut)
				{	//	Menu fourier
				printf("commandesSourisZone 6\n");
				return 6;
				}
			printf("commandesSourisZone 7\n");
			return 7;	//	Fourier
			}
		else						//		MENU 3 = zone 8
			{
			printf("commandesSourisZone 8\n");
			return 8;
			}
		}
	
	return -1;
	}

int commandeSelectifsInitiale(commandesT * commandes)
	{
			// Retourne le numéro du boutons sélectif du menu initiale
	int i;
		{
		for(i=0;i<SELECTIF_INITIAL;i++)
			{
			//	Si dans la zone suivant Y
			if((*commandes).selectifInitial[i].Y>(*commandes).sourisHaut
				&& ((*commandes).selectifInitial[i].Y+(*commandes).selectifInitial[i].dY)<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}

int commandeRotatifsInitiale(commandesT * commandes)
	{
			// Retourne le numéro du boutons rotatif du menu graphe
	int i;
		{
		for(i=0;i<ROTATIF_INITIAL;i++)
			{
			//	Si dans la zone suivant Y
			if((*commandes).rotatifInitial[i].Y>(*commandes).sourisHaut
				&& ((*commandes).rotatifInitial[i].Y+(*commandes).rotatifInitial[i].dY)<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}
int commandeSelectifsGraphes(commandesT * commandes)
	{
			// Retourne le numéro du boutons sélectif des menus graphes
	int i;
		{
		for(i=0;i<SELECTIF_GRAPHES;i++)
			{
			//	Si dans la zone suivant X
			if((*commandes).selectifGraph[0][i].X>(*commandes).sourisGauche
				&& ((*commandes).selectifGraph[0][i].X+(*commandes).selectifGraph[0][i].dX)<(*commandes).sourisDroite)
				return i;
			}
		}
	return -1;
	}

int commandeRotatifsGraphes(commandesT * commandes)
	{
			// Retourne le numéro du boutons rotatif du menu initiale
	int i;
		{
		for(i=0;i<ROTATIF_GRAPHES;i++)
			{
			//	Si dans la zone suivant X
			if((*commandes).rotatifGraph[0][i].X>(*commandes).sourisGauche
				&& ((*commandes).rotatifGraph[0][i].X+(*commandes).rotatifGraph[0][i].dX)<(*commandes).sourisDroite)
				return i;
			}
		}
	return -1;
	}
/*
int commandesSourisZone(commandesT * commandes)
	{
		//	Retourne la zone où se trouve la souris

	if((*commandes).sourisX < (*commandes).fonctionsGauche)		//		MENU 1
		{
		if((*commandes).sourisY < (*commandes).mode)
			{	//	Selection initiale/simulation
			return 1;
			}
		else
			{
			if((*commandes).sourisX < (*commandes).rotatifsDroite && (*commandes).sourisX > (*commandes).rotatifsGauche)
				{	//	Rotatif
				return 2;
				}
			else
				{	//	Selectif
				if((*commandes).sourisX < (*commandes).selectifsDroite && (*commandes).sourisX > (*commandes).selectifsGauche)
					{
					return 3;
					}
				}
			}
		}
	else
		{
		if((*commandes).sourisX < (*commandes).fonctionsDroite)	//		MENU 2
			{
			if((*commandes).sourisY < (*commandes).fonctionHaut)
				{	//	Menu fonction
				return 4;
				}
			else
				{
				if((*commandes).sourisY < (*commandes).fonctionBas)
					{	//	Fonction
					return 5;
					}
				else
					{
					if((*commandes).sourisY < (*commandes).fourierHaut)
						{	//	Menu fourier
						return 6;
						}
					else
						{	//	Fourier
							return 7;
						}
					}
				}
			}
		else								//		MENU 3
			{
			return 8;
			}
		}
	
	return -1;
	}
*/
//////////////////////////////////////////////////////////////////
