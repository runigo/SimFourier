/*
Copyright février 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
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

int commandesInitialiseZones(commandesT * commandes, int largeur, int hauteur);
int commandesInitialiseRotatifs(commandesT * commandes, int largeur, int hauteur);
int commandesInitialiseSelectifs(commandesT * commandes, int largeur, int hauteur);
int commandesInitialise(commandesT * commandes, int largeur, int hauteur);

int commandesInitialiseZones(commandesT * commandes, int largeur, int hauteur)
	{
	(void)largeur;
	(void)hauteur;

			// Zones suivant Y du menu 1
		(*commandes).mode = 24;

			// Zones suivant X des fonctions
		(*commandes).fonctionsGauche = 200;
		(*commandes).fonctionsDroite = 600;

			// Zones suivant Y des fonctions
		(*commandes).fonctionHaut = 30;
		(*commandes).fonctionBas = hauteur/2;
		(*commandes).fourierHaut = hauteur/2 +20;
		(*commandes).fourierBas = hauteur;

	return 0;
	}

int commandesInitialiseRotatifs(commandesT * commandes, int largeur, int hauteur)
	{
	(void)largeur;
	(void)hauteur;
				//	Positions des boutons rotatifs

		//	Suivant X
	(*commandes).rotatifsGauche = 20;
	(*commandes).rotatifsDroite = 100;
	(*commandes).rotatifsCentre = ((*commandes).rotatifsDroite+(*commandes).rotatifsGauche)/2;

	int i;
	for(i=0;i<ROTATIF_COMMANDES;i++)
		{
		rotatifInitialise(&(*commandes).rotatif[i], (*commandes).rotatifsDroite-(*commandes).rotatifsGauche);
		}

		//	Suivant Y
	(*commandes).rotatif[0].Y = 75; 	//	Largeur
	(*commandes).rotatif[1].Y = 168;	//	Largeur
	(*commandes).rotatif[2].Y = 285;	//	Symetrie
	(*commandes).rotatif[3].Y = 404;	//	Phase
	(*commandes).rotatif[4].Y = 548;	//	Période
	(*commandes).rotatif[5].Y = 640;	//	Période

	return 0;
	}

int commandesInitialiseSelectifs(commandesT * commandes, int largeur, int hauteur)
	{
				//	Positions des boutons selectifs
	int i;
	for(i=0;i<SELECTIF_COMMANDES;i++)
		{
		selectifInitialise(&(*commandes).selectif[i], largeur, hauteur);
		}

		//	Suivant X
	(*commandes).selectifsGauche = 134;
	(*commandes).selectifsDroite = 176;
	(*commandes).selectifsCentre = ((*commandes).selectifsDroite+(*commandes).selectifsGauche)/2;

		// BOUTONS SELECTIFS SUIVANT Y
	(*commandes).selectif[0].Y=69;  	//	Constant
	(*commandes).selectif[1].Y=114;		//	Rectangle
	(*commandes).selectif[2].Y=159;		//	Scie
	(*commandes).selectif[3].Y=203;		//	Sinus
	(*commandes).selectif[4].Y=264;		//	Apériodique
	(*commandes).selectif[5].Y=310;		//	Périodique
	(*commandes).selectif[6].Y=355;		//	Gaussienne
	(*commandes).selectif[7].Y=400;		//	Lorentzienne
	(*commandes).selectif[8].Y=444;		//	Sin Cardinal
	(*commandes).selectif[9].Y=543;		//	Constant
	(*commandes).selectif[10].Y=588;	//	Dirac
	(*commandes).selectif[11].Y=631;	//	Sinus
	(*commandes).selectif[12].Y=677;	//	Complexe

	return 0;
	}

int commandesInitialise(commandesT * commandes, int largeur, int hauteur)
	{
			//	Positions graphiques des zones et des commandes

	commandesInitialiseRotatifs(commandes, largeur, hauteur);

	commandesInitialiseSelectifs(commandes, largeur, hauteur);

	commandesInitialiseZones(commandes, largeur, hauteur);

		(*commandes).sourisX = 10; // position X de la souris
		(*commandes).sourisY = 10; // position Y de la souris

		(*commandes).sourisGauche = 5; // position X de la souris - demiBouton
		(*commandes).sourisDroite = 15; // position X de la souris + demiBouton
		(*commandes).sourisHaut = 5; // position Y de la souris - demiBouton
		(*commandes).sourisBas = 15; // position Y de la souris + demiBouton

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

	//fprintf(stderr, " commandesInitialiseSouris, %d, %d\n", (*commandes).sourisX,(*commandes).sourisY);
	return 0;
	}

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

int commandeSelectifs(commandesT * commandes)
	{
			// Retourne le numéro du boutons sélectif
	int i;
		{
		for(i=0;i<SELECTIF_COMMANDES;i++)
			{
			//	Si dans la zone suivant Y
			if((*commandes).selectif[i].Y>(*commandes).sourisHaut
				&& ((*commandes).selectif[i].Y+(*commandes).selectif[i].dY)<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}

int commandeRotatifs(commandesT * commandes)
	{
			// Retourne le numéro du boutons rotatif
	int i;
		{
		for(i=0;i<ROTATIF_COMMANDES;i++)
			{
			//	Si dans la zone suivant Y
			if((*commandes).rotatif[i].Y>(*commandes).sourisHaut
				&& ((*commandes).rotatif[i].Y+(*commandes).rotatif[i].dY)<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}
//////////////////////////////////////////////////////////////////
