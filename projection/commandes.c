/*
Copyright juin 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
(d'après SiCP 2.5 simulateur de chaîne de pendules, fevrier 2021)
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

#include "commandes.h"

float commandesAjusteZones(commandesT * commandes, int fenetreX, int fenetreY);
int commandesAjusteRotatifsInitiale(commandesT * commandes, float facteur);
int commandesAjusteSelectifsInitiale(commandesT * commandes, float facteur);
int commandesAjusteRotatifsGraphes(commandesT * commandes, float facteur);
int commandesAjusteSelectifsGraphes(commandesT * commandes, float facteur);
int commandesAjusteRotatifsFiltres(commandesT * commandes, float facteur);
int commandesAjusteSelectifsFiltres(commandesT * commandes, int fenetreX, float facteur);
//int commandesInitialise(commandesT * commandes, float facteur);

float commandesAjusteCommandes(commandesT * commandes, int fenetreX, int fenetreY)
	{
			//	Réglage des positions des zones et des commandes en fonction de la taille de la fenêtre

	float facteur = commandesAjusteZones(commandes, fenetreX, fenetreY);

	commandesAjusteRotatifsInitiale(commandes, facteur);
	commandesAjusteSelectifsInitiale(commandes, facteur);
	commandesAjusteRotatifsGraphes(commandes, facteur);
	commandesAjusteSelectifsGraphes(commandes, facteur);
	commandesAjusteRotatifsFiltres(commandes, facteur);
	commandesAjusteSelectifsFiltres(commandes, fenetreX, facteur);

	return facteur;
	}

float commandesAjusteZones(commandesT * commandes, int fenetreX, int fenetreY)
	{
				//	Calcul de facteur et positions des zones

	(void)fenetreX;

	float facteur = 1.0;	//	Facteur lié à la taille de la fenêtre
	float facteurX = 1.0;	//	Facteur lié à la taille de la fenêtre
	if(fenetreY < FENETRE_Y)
		{
		facteur = (float)fenetreY / FENETRE_Y;
		printf("commandesAjusteZones FACTEUR Y = %f\n", facteur);
		}
	if(fenetreX < FENETRE_X)
		{
		facteurX = (float)fenetreX / FENETRE_X;
		printf("commandesAjusteZones FACTEUR X = %f\n", facteur);
		}
	if(facteurX < facteur)
		{
		facteur = facteurX;
		printf("commandesAjusteZones FACTEUR = %f\n", facteur);
		}

			//	Zones suivant X des rotatifs du menu initiale
	(*commandes).rotatifInitialGauche = facteur * 11;
	(*commandes).rotatifInitialDroite = facteur * 70;

			//	Zones suivant X des selectifs du menu initiale
	(*commandes).selectifInitialGauche = facteur * 83;
	(*commandes).selectifInitialDroite = facteur * 114;

			// Zones suivant X des fonctions (zones 4, 5, 6, 7)
	(*commandes).fonctionsGauche = facteur * 126;
	(*commandes).fonctionsDroite = fenetreX - facteur * FILTRE_ROTATIF_X;	//	Début de la zone 8
	(*commandes).filtrageGauche = fenetreX - facteur * (FILTRE_ROTATIF_X+FILTRE_SELECTIF_X);	//	Début de la zone 9

			//	Zones suivant X des rotatifs du menu filtrage
	(*commandes).rotatifFiltrGauche = fenetreX - facteur * 67;
	(*commandes).rotatifFiltrDroite = fenetreX - facteur * 8;

		// Zones suivant Y du menu 1
	(*commandes).mode = facteur * 24;

		// Zones suivant Y des menus graphe et filtrage
	(*commandes).selectifsFonctionHaut = facteur * 7;	//	Petits bouton du menu graphe-fonction (zone 4)
	(*commandes).selectifsFonctionBas = facteur * 35;
	//(*commandes).selectifsFonction = facteur * 7;	//	position y des selectifs
		// Zones suivant Y des fonctions
	(*commandes).fonctionHaut = facteur * 43;		//	frontière 4-5
	(*commandes).fonctionBas = fenetreY / 2;		//	frontière 5-6
	(*commandes).fourierHaut = (*commandes).fonctionBas + (*commandes).fonctionHaut;	//	6-7
	(*commandes).fourierBas = fenetreY;				//	frontière basse

	return facteur;
	}

int commandesAjusteRotatifsInitiale(commandesT * commandes, float facteur)
	{
				//	Positions des boutons rotatifs du menu initiale
	int i;
	for(i=0;i<ROTATIF_INITIAL;i++)
		{
		rotatifInitialise(&(*commandes).rotatifInitial[i], (*commandes).rotatifInitialDroite-(*commandes).rotatifInitialGauche);
		}
	(*commandes).rotatifInitial[0].Y = facteur * 51; 	//	Largeur
	(*commandes).rotatifInitial[1].Y = facteur * 122;	//	Largeur
	(*commandes).rotatifInitial[2].Y = facteur * 221;	//	Symetrie
	(*commandes).rotatifInitial[3].Y = facteur * 291;	//	Phase
	(*commandes).rotatifInitial[4].Y = facteur * 398;	//	Amplitude
	(*commandes).rotatifInitial[5].Y = facteur * 468;	//	Décalage
	(*commandes).rotatifInitial[6].Y = facteur * 602;	//	Période
	(*commandes).rotatifInitial[7].Y = facteur * 673;	//	Période

	return 0;
	}

int commandesAjusteSelectifsInitiale(commandesT * commandes, float facteur)
	{
					//	Positions des boutons selectifs du menu initiale
	int i;
	for(i=0;i<SELECTIF_INITIAL;i++)
		{
		selectifInitialise(&(*commandes).selectifInitial[i], (*commandes).selectifInitialDroite - (*commandes).selectifInitialGauche);
		}
			// BOUTONS SELECTIFS SUIVANT Y
	(*commandes).selectifInitial[0].Y = facteur * 51;		//	Constant
	(*commandes).selectifInitial[1].Y = facteur * 83;		//	Rectangle
	(*commandes).selectifInitial[2].Y = facteur * 114;		//	Scie
	(*commandes).selectifInitial[3].Y = facteur * 146;		//	Sinus
	(*commandes).selectifInitial[4].Y = facteur * 207;		//	Apériodique
	(*commandes).selectifInitial[5].Y = facteur * 241;		//	Périodique
	(*commandes).selectifInitial[6].Y = facteur * 272;		//	Gaussienne
	(*commandes).selectifInitial[7].Y = facteur * 304;		//	Lorentzienne
	(*commandes).selectifInitial[8].Y = facteur * 336;		//	Sinus Cardinal
	(*commandes).selectifInitial[9].Y = facteur * 414;		//	Centrage horizontal
	(*commandes).selectifInitial[10].Y = facteur * 465;		//	Minimum = 0
	(*commandes).selectifInitial[11].Y = facteur * 505;		//	Centrage vertical
	(*commandes).selectifInitial[12].Y = facteur * 601;		//	Constant
	(*commandes).selectifInitial[13].Y = facteur * 633;		//	Dirac
	(*commandes).selectifInitial[14].Y = facteur * 664;		//	Sinus
	(*commandes).selectifInitial[15].Y = facteur * 696;		//	Complexe

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
			selectifInitialise(&(*commandes).selectifGraph[j][i], (*commandes).selectifInitialDroite - (*commandes).selectifInitialGauche);
			}
				// BOUTONS SELECTIFS SUIVANT X
		(*commandes).selectifGraph[j][0].X = facteur * 187;  	//	Implicite
		(*commandes).selectifGraph[j][1].X = facteur * 215;		//	Imaginaire
		(*commandes).selectifGraph[j][2].X = facteur * 248;		//	Reel
		(*commandes).selectifGraph[j][3].X = facteur * 306;		//	Point
		(*commandes).selectifGraph[j][4].X = facteur * 333;		//	Relié
		(*commandes).selectifGraph[j][5].X = facteur * 383;		//	Vecteur
		(*commandes).selectifGraph[j][6].X = facteur * 410;		//	Sans
		}
	return 0;
	}

int commandesAjusteRotatifsFiltres(commandesT * commandes, float facteur)
	{
				//	Positions des boutons rotatifs du menu filtrage
	int i;
	for(i=0;i<ROTATIF_FILTRES;i++)
		{
		rotatifInitialise(&(*commandes).rotatifFiltrag[i], (*commandes).rotatifFiltrDroite-(*commandes).rotatifFiltrGauche);
		}
	(*commandes).rotatifFiltrag[0].Y = facteur * 47; 	//	Fréquence 1
	(*commandes).rotatifFiltrag[1].Y = facteur * 118;	//	Ordre 1
	(*commandes).rotatifFiltrag[2].Y = facteur * 216;	//	Fréquence 2
	(*commandes).rotatifFiltrag[3].Y = facteur * 287;	//	Ordre 2
	(*commandes).rotatifFiltrag[4].Y = facteur * 393;	//	Fréquence 3
	(*commandes).rotatifFiltrag[5].Y = facteur * 464;	//	Ordre 3
	(*commandes).rotatifFiltrag[6].Y = facteur * 535;	//	Delta f
	(*commandes).rotatifFiltrag[7].Y = facteur * 638;	//	Amplification

	return 0;
	}

int commandesAjusteSelectifsFiltres(commandesT * commandes, int fenetreX, float facteur)
	{
				//	Positions des boutons selectifs du menu filtres
	int i;

	for(i=0;i<SELECTIF_FILTRES;i++)
		{
		selectifInitialise(&(*commandes).selectifFiltrag[i], (*commandes).selectifInitialDroite - (*commandes).selectifInitialGauche);
		}
				// BOUTONS SELECTIFS SUIVANT X
	(*commandes).selectifFiltrag[0].X = fenetreX - facteur * 621;  	//	Passe bas éteint
	(*commandes).selectifFiltrag[1].X = fenetreX - facteur * 591;		//	Passe bas
	(*commandes).selectifFiltrag[2].X = fenetreX - facteur * 558;		//	Passe bas droite
	(*commandes).selectifFiltrag[3].X = fenetreX - facteur * 527;		//	Passe bas gauche
	(*commandes).selectifFiltrag[4].X = fenetreX - facteur * 444;		//	Passe haut éteint
	(*commandes).selectifFiltrag[5].X = fenetreX - facteur * 413;		//	Passe haut
	(*commandes).selectifFiltrag[6].X = fenetreX - facteur * 381;		//	Passe haut gauche
	(*commandes).selectifFiltrag[7].X = fenetreX - facteur * 350;  	//	Passe haut droite
	(*commandes).selectifFiltrag[8].X = fenetreX - facteur * 266;		//	Passe bande éteint
	(*commandes).selectifFiltrag[9].X = fenetreX - facteur * 237;		//	Passe bande
	(*commandes).selectifFiltrag[10].X = fenetreX - facteur * 205;		//	Passe bande gauche
	(*commandes).selectifFiltrag[11].X = fenetreX - facteur * 172;		//	Passe bande droite
	(*commandes).selectifFiltrag[12].X = fenetreX - facteur * 140;		//	Passe bande inverse

	return 0;
	}

int commandesInitialiseSouris(commandesT * commandes, int sourisX, int sourisY)
	{
		 // Rayon des petits boutons
	int rayonX=(*commandes).selectifInitialDroite-(*commandes).selectifInitialGauche;
	int rayonY=rayonX;

	if(sourisX<(*commandes).rotatifInitialDroite || sourisX>(*commandes).fonctionsDroite)
		{	//	Zones des boutons rotatifs
		rayonX=(*commandes).rotatifInitialDroite-(*commandes).rotatifInitialGauche;
		rayonY=rayonX;
		}

		//	Position de la souris
	(*commandes).sourisX = sourisX; // position X de la souris
	(*commandes).sourisY = sourisY; // position Y de la souris
		//	"Région d'action" de la souris
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
			//printf("commandesSourisZone 1\n");
			return 1;
			}
		if((*commandes).sourisX < (*commandes).rotatifInitialDroite && (*commandes).sourisX > (*commandes).rotatifInitialGauche)
			{	//	Rotatif
			//printf("commandesSourisZone 2\n");
			return 2;
			}
		if((*commandes).sourisX < (*commandes).selectifInitialDroite && (*commandes).sourisX > (*commandes).selectifInitialGauche)
			{	//	Selectif
			//printf("commandesSourisZone 3\n");
			return 3;
			}
		}
	else
		{
		if((*commandes).sourisX < (*commandes).fonctionsDroite)	//		MENU 2 = zones 4, 5, 6 et 7, et 9
			{
			if((*commandes).sourisY < (*commandes).fonctionHaut)
				{	//	Menu fonction		printf("commandesSourisZone 4\n");
				return 4;
				}
			if((*commandes).sourisY < (*commandes).fonctionBas)
				{	//	Fonction		printf("commandesSourisZone 5\n");
				return 5;
				}
			if((*commandes).sourisY < (*commandes).fourierHaut)
				{	//	Menu fourier et sélectifs des filtres
				if((*commandes).sourisX < (*commandes).filtrageGauche)
					{		//printf("commandesSourisZone 6\n");
					return 6;
					}
				else
					{		//printf("commandesSourisZone 9\n");
					return 9;
					}
				}		//printf("commandesSourisZone 7\n");
			return 7;	//	Fourier
			}
		else						//		MENU 3 = zone 8
			{
			if((*commandes).sourisY < (*commandes).fonctionHaut)
				{	//	Bouton filtrage		printf("commandesSourisZone 10\n");
				return 10;
				}
			else
				{
				if((*commandes).sourisX < (*commandes).rotatifFiltrDroite && (*commandes).sourisX > (*commandes).rotatifFiltrGauche)
					{	//	Rotatif		printf("commandesSourisZone 8\n");
					return 8;
					}
				}
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

int commandeSelectifsFiltres(commandesT * commandes)
	{
			// Retourne le numéro du boutons sélectif du menu filtrage
	int i;
		{
		for(i=0;i<SELECTIF_FILTRES;i++)
			{
			//	Si dans la zone suivant X
			if((*commandes).selectifFiltrag[i].X>(*commandes).sourisGauche
				&& ((*commandes).selectifFiltrag[i].X+(*commandes).selectifFiltrag[i].dX)<(*commandes).sourisDroite)
				return i;
			}
		}
	return -1;
	}

int commandeRotatifsFiltres(commandesT * commandes)
	{
			// Retourne le numéro du boutons rotatif du menu filtrage
	int i;
		{
		for(i=0;i<ROTATIF_FILTRES;i++)
			{
			//	Si dans la zone suivant Y
			if((*commandes).rotatifFiltrag[i].Y>(*commandes).sourisHaut
				&& ((*commandes).rotatifFiltrag[i].Y+(*commandes).rotatifFiltrag[i].dY)<(*commandes).sourisBas)
				{
				printf("i = %d, ", i);
				rotatifAffiche(&(*commandes).rotatifFiltrag[i]);
				return i;
				}
			}
		}
	return -1;
	}

//////////////////////////////////////////////////////////////////
