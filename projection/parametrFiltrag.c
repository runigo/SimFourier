/*
Copyright mai 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
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

#include "parametrFiltrag.h"

				//		Projections des caractéristiques du filtrage
				//		sur les commandes.

int parametrFiltragRotatifs(filtrageT * filtrage, parametrFiltragT * parametre, commandesT * commandes);
int parametrFiltragSelectifs(filtrageT * filtrage, commandesT * commandes);


	//-----------------    INITIALISATION      -----------------------//

int parametrFiltragInitialise(parametrFiltragT * parametre, int nombre)
	{
		//	facteur entre les grandeurs et la position des rotatifs
	(*parametre).radianFrequence = PIS2 / (nombre);
	(*parametre).radianOrdre = PIS2 / (nombre);
	(*parametre).radianDeltaF = PIS2 / (nombre);
	(*parametre).radianAmplification = PIS2 / (100);

	return 0;
	}

	//-----------------    PROJECTION      -----------------------//

int parametrFiltragCommandes(filtrageT * filtrage, parametrFiltragT * parametre, commandesT * commandes)
	{
			//	Projette les caractéristiques du filtrage
			//		sur les commandes

		//	Projection sur les boutons rotatifs
	parametrFiltragRotatifs(filtrage, parametre, commandes);

		//	Projection sur les boutons selectifs
	parametrFiltragSelectifs(filtrage, commandes);

	return 0;
	}

int parametrFiltragRotatifs(filtrageT * filtrage, parametrFiltragT * parametre, commandesT * commandes)
	{
		//	Projette les caractéristiques du filtrage sur les
		//		boutons rotatifs

	float theta;
	int longueur = (*commandes).rotatifFiltrDroite - (*commandes).rotatifFiltrGauche;

			//	Projection sur les boutons rotatifs du filtrage
		//	Fréquence 1
	theta = (*parametre).radianFrequence * ((*filtrage).passeBas.frequence);
	(*commandes).rotatifFiltrag[0].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifFiltrag[0].positionY = (int)(-longueur*sin(theta));
		//	Ordre 1
	theta = (*parametre).radianOrdre * ((*filtrage).passeBas.ordre);
	(*commandes).rotatifFiltrag[1].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifFiltrag[1].positionY = (int)(-longueur*sin(theta));
		//	Fréquence 2
	theta = (*parametre).radianFrequence * ( (*filtrage).passeHaut.frequence);
	(*commandes).rotatifFiltrag[2].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifFiltrag[2].positionY = (int)(-longueur*sin(theta));
		//	Ordre 2
	theta = (*parametre).radianOrdre * ( (*filtrage).passeHaut.ordre );
	(*commandes).rotatifFiltrag[3].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifFiltrag[3].positionY = (int)(-longueur*sin(theta));
		//	Fréquence 3
	theta = (*parametre).radianFrequence * ((*filtrage).passeBande.frequence);
	(*commandes).rotatifFiltrag[4].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifFiltrag[4].positionY = (int)(-longueur*sin(theta));
		//	Ordre 3
	theta = (*parametre).radianOrdre * ((*filtrage).passeBande.ordre);
	(*commandes).rotatifFiltrag[5].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifFiltrag[5].positionY = (int)(-longueur*sin(theta));
		//	Delta fréquence
	theta = (*parametre).radianFrequence * ((*filtrage).passeBande.deltaF);
	(*commandes).rotatifFiltrag[6].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifFiltrag[6].positionY = (int)(-longueur*sin(theta));
		//	Amplification
	theta = (*parametre).radianAmplification * ((*filtrage).amplification);
	(*commandes).rotatifFiltrag[7].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifFiltrag[7].positionY = (int)(-longueur*sin(theta));

	return 0;
	}

int parametrFiltragSelectifs(filtrageT * filtrage, commandesT * commandes)
	{
		//	Projette les caractéristiques du filtrage sur les
		//		boutons sélectifs

	int i;

	for(i=0;i<SELECTIF_FILTRES;i++)
		{
		(*commandes).selectifFiltrag[i].etat = 0;
		}

	if((*filtrage).passeBas.mode != 0)
		{
		switch((*filtrage).passeBas.symetrie) {
			case 0:
				(*commandes).selectifFiltrag[1].etat = 1; break;	//	Symétrique
			case 1:
				(*commandes).selectifFiltrag[2].etat = 1; break;	//	Droite
			case -1:
				(*commandes).selectifFiltrag[3].etat = 1; break;	//	Gauche
			default:
				fprintf(stderr, "ERREUR parametrFiltragSelectifs, passeBas.symetrie");
			}
		}

	if((*filtrage).passeHaut.mode != 0)
		{
		switch((*filtrage).passeHaut.symetrie) {
			case 0:
				(*commandes).selectifFiltrag[5].etat = 1; break;	//	Symétrique
			case 1:
				(*commandes).selectifFiltrag[7].etat = 1; break;	//	Droite
			case -1:
				(*commandes).selectifFiltrag[6].etat = 1; break;	//	Gauche
			default:
				fprintf(stderr, "ERREUR parametrFiltragSelectifs, passeHaut.symetrie");
			}
		}

	if((*filtrage).passeBande.mode != 0)
		{
		switch((*filtrage).passeBande.symetrie) {
			case 0:
				(*commandes).selectifFiltrag[9].etat = 1; break;	//	Symétrique
			case 1:
				(*commandes).selectifFiltrag[11].etat = 1; break;	//	Droite
			case -1:
				(*commandes).selectifFiltrag[10].etat = 1; break;	//	Gauche
			default:
				fprintf(stderr, "ERREUR parametrFiltragSelectifs, passeBande.symetrie");
			}
		if((*filtrage).passeBande.mode < 0)
			{
			(*commandes).selectifFiltrag[12].etat = 1;	//	Inverse
			}
		}
	return 0;
	}

	//-----------------    AFFICHAGE      -----------------------//

int parametrFiltragAffiche(parametrFiltragT * parametre) {

		//	Affiche les paramètres de la parametre

	printf("(*parametre).radianFrequence = %f\n", (*parametre).radianFrequence);
	printf("(*parametre).radianOrdre = %f\n", (*parametre).radianOrdre);
	printf("(*parametre).radianDeltaF = %f\n", (*parametre).radianDeltaF);
	printf("(*parametre).radianAmplification = %f\n", (*parametre).radianAmplification);
	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////
