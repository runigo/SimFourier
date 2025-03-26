/*
Copyright mars 2025, Stephan Runigo
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

int commandesAjusteZones(commandesT * commandes, double facteur);
int commandesAjusteRotatifsInitiale(commandesT * commandes, double facteur);
int commandesAjusteSelectifsInitiale(commandesT * commandes, double facteur);
int commandesAjusteRotatifsGraphes(commandesT * commandes, double facteur);
int commandesAjusteSelectifsGraphes(commandesT * commandes, double facteur);
//int commandesInitialise(commandesT * commandes, double facteur);

int commandesAjusteCommandes(commandesT * commandes, double facteur)
	{
			//	Réglage des positions des zones et des commandes

	commandesAjusteZones(commandes, facteur);
	commandesAjusteRotatifsInitiale(commandes, facteur);
	commandesAjusteSelectifsInitiale(commandes, facteur);
	//commandesAjusteRotatifsGraphes(commandes, facteur);
	//commandesAjusteSelectifsGraphes(commandes, facteur);

	return 0;
	}

int commandesAjusteZones(commandesT * commandes, double facteur)
	{

			// Zones suivant Y du menu 1
		(*commandes).mode = facteur * 24;

			// Zones suivant X des fonctions
		(*commandes).fonctionsGauche = facteur * 200;
		(*commandes).fonctionsDroite = facteur * 600;

			// Zones suivant Y des fonctions
		(*commandes).fonctionHaut = 30;
		(*commandes).fonctionBas = 300;
		(*commandes).fourierHaut = 330;
		(*commandes).fourierBas = 600;

			//	Zones des commandes suivant X
	(*commandes).selectifsGauche = facteur * 134;
	(*commandes).selectifsDroite = facteur * 176;
	//(*commandes).selectifsCentre = ( (*commandes).selectifsDroite + (*commandes).selectifsGauche ) / 2;

	(*commandes).rotatifsGauche = facteur * 20;
	(*commandes).rotatifsDroite = facteur * 100;
	//(*commandes).rotatifsCentre = ((*commandes).rotatifsDroite+(*commandes).rotatifsGauche)/2;

	return 0;
	}

int commandesAjusteRotatifsInitiale(commandesT * commandes, double facteur)
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

int commandesAjusteSelectifsInitiale(commandesT * commandes, double facteur)
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

int commandesAjusteRotatifsGraphes(commandesT * commandes, double facteur)
	{
				//	Positions des boutons rotatifs des menus graphes
	int i;
	for(i=0;i<ROTATIF_GRAPHES;i++)
		{
		rotatifInitialise(&(*commandes).rotatifGraph[i], (*commandes).rotatifsDroite-(*commandes).rotatifsGauche);
		}
	(*commandes).rotatifGraph[0].Y = facteur * 75; 	//	Largeur
	(*commandes).rotatifGraph[1].Y = facteur * 168;	//	Largeur
	(*commandes).rotatifGraph[2].Y = facteur * 285;	//	Symetrie
	(*commandes).rotatifGraph[3].Y = facteur * 404;	//	Phase
	(*commandes).rotatifGraph[4].Y = facteur * 548;	//	Période
	(*commandes).rotatifGraph[5].Y = facteur * 640;	//	Période

	return 0;
	}

int commandesAjusteSelectifsGraphes(commandesT * commandes, double facteur)
	{
					//	Positions des boutons selectifs des menus graphes
	int i;
	for(i=0;i<SELECTIF_GRAPHES;i++)
		{
		selectifInitialise(&(*commandes).selectifGraph[i], (*commandes).selectifsDroite - (*commandes).selectifsGauche);
		}
			// BOUTONS SELECTIFS SUIVANT X
	(*commandes).selectifGraph[0].X = facteur * 69;  	//	Implicite
	(*commandes).selectifGraph[1].X = facteur * 114;		//	Imaginaire
	(*commandes).selectifGraph[2].X = facteur * 159;		//	Reel
	(*commandes).selectifGraph[3].X = facteur * 203;		//	Sans
	(*commandes).selectifGraph[4].X = facteur * 264;		//	Point
	(*commandes).selectifGraph[5].X = facteur * 310;		//	Relié
	(*commandes).selectifGraph[6].X = facteur * 355;		//	Vecteur
	(*commandes).selectifGraph[7].X = facteur * 400;		//	Cartésien
	(*commandes).selectifGraph[8].X = facteur * 444;		//	Sans

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

int commandeSelectifsInitiale(commandesT * commandes)
	{
			// Retourne le numéro du boutons sélectif
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
			// Retourne le numéro du boutons rotatif
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
//////////////////////////////////////////////////////////////////
