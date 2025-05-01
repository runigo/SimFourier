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

#include "parametrInitial.h"

				//		Projections des caractéristiques de la fonction initiale
				//		sur les commandes.
				//			MODE INITIALE de simFourier

int parametrInitialRotatifs(initialeT * initiale, parametrInitialT * parametre, commandesT * commandes);
int parametrInitialSelectifs(initialeT * initiale, commandesT * commandes);


	//-----------------    INITIALISATION      -----------------------//

int parametrInitialInitialise(parametrInitialT * parametre, int nombre)
	{
		//	facteur entre les grandeurs et la position des rotatifs
	(*parametre).radianEta = log2(nombre);
	(*parametre).radianRho = log2(nombre)/2;
	(*parametre).radianKhi = nombre/2;
	(*parametre).radianSym = PIS2;

	(*parametre).radianAmplitude = PIS2/(AMPLITUDE_MAX - AMPLITUDE_MIN);
	(*parametre).radianDecalage = PIS2/AMPLITUDE_MAX/2;

	return 0;
	}

	//-----------------    PROJECTION      -----------------------//

int parametrInitialCommandes(initialeT * initiale, parametrInitialT * parametre, commandesT * commandes)
	{
			//	Projette les caractéristiques de la fonction initiale
			//		sur les commandes dans le mode initiale

		//	Projection sur les boutons rotatifs
	parametrInitialRotatifs(initiale, parametre, commandes);

		//	Projection sur les boutons selectifs
	parametrInitialSelectifs(initiale, commandes);

	return 0;
	}

int parametrInitialRotatifs(initialeT * initiale, parametrInitialT * parametre, commandesT * commandes)
	{
		//	Projette les caractéristiques de la fonction initiale sur les
		//		boutons rotatifs dans le mode initiale

	float theta;
	int longueur = (*commandes).rotatifsDroite - (*commandes).rotatifsGauche;

		// facteur de proportionalité entre les grandeurs de l'enveloppe et la position des rotatifs
	(*parametre).radianEta = PIS2 / ((*initiale).enveloppe.etaMax - (*initiale).enveloppe.etaMin);
	(*parametre).radianRho = PIS2 / exp2((*initiale).enveloppe.eta);
	(*parametre).radianKhi = PIS2 / (*initiale).enveloppe.fonction.nombre;

			//	Projection sur les boutons rotatifs de la partie enveloppe
		//	Période enveloppe, eta
	theta = (*parametre).radianEta * ((*initiale).enveloppe.eta - (*initiale).enveloppe.etaMin);
	(*commandes).rotatifInitial[0].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifInitial[0].positionY = (int)(-longueur*sin(theta));
		//	Période enveloppe, rho
	theta = (*parametre).radianRho * ((*initiale).enveloppe.rho);
	(*commandes).rotatifInitial[1].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifInitial[1].positionY = (int)(-longueur*sin(theta));
		//	Symétrie motif
	theta = (*parametre).radianSym * ( (*initiale).motif.symetrie );
	(*commandes).rotatifInitial[2].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifInitial[2].positionY = (int)(-longueur*sin(theta));
		//	Phase motif
	theta = (*parametre).radianKhi * ( (*initiale).enveloppe.khi );
	(*commandes).rotatifInitial[3].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifInitial[3].positionY = (int)(-longueur*sin(theta));
		//	Amplitude motif
	theta = (*parametre).radianAmplitude * ((*initiale).motif.amplitude + AMPLITUDE_MAX);
	(*commandes).rotatifInitial[4].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifInitial[4].positionY = (int)(-longueur*sin(theta));
		//	Décalage verticale
	theta = (*parametre).radianDecalage * ((*initiale).motif.decalage);
	(*commandes).rotatifInitial[5].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifInitial[5].positionY = (int)(-longueur*sin(theta));

		// facteur de proportionalité entre les grandeurs de la porteuse et la position des rotatifs
	(*parametre).radianEta = PIS2 / ((*initiale).porteuse.etaMax - (*initiale).porteuse.etaMin);
	(*parametre).radianRho = PIS2 / ( exp2((*initiale).porteuse.eta) );

		//	Projection sur les boutons rotatifs de la partie porteuse
	//	Période porteuse, eta
	theta = (*parametre).radianEta * ((*initiale).porteuse.eta - (*initiale).porteuse.etaMin);
	(*commandes).rotatifInitial[6].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifInitial[6].positionY = (int)(-longueur*sin(theta));
	//	Période porteuse, rho
	theta = (*parametre).radianRho * ((*initiale).porteuse.rho);
	(*commandes).rotatifInitial[7].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifInitial[7].positionY = (int)(-longueur*sin(theta));

	return 0;
	}

int parametrInitialSelectifs(initialeT * initiale, commandesT * commandes)
	{
		//	Projette les caractéristiques de la fonction initiale sur les
		//		boutons séelectifs dans le mode initiale

	int i;
	int motif=0;	//	Indicateur motif / fonction en cloche

	for(i=0;i<SELECTIF_INITIAL;i++) (*commandes).selectifInitial[i].etat = 0;

			//	Forme de l'enveloppe
	switch((*initiale).enveloppe.periodique) {
		case 2:
			(*commandes).selectifInitial[6].etat = 1; break;	//	Gaussienne
		case 3:
			(*commandes).selectifInitial[7].etat = 1; break;	//	Lorentzienne
		case 4:
			(*commandes).selectifInitial[8].etat = 1; break;	//	Sinus cardinale
		default:
			motif=1;	//	La sélection n'est pas une fonction en cloche
		}

	if(motif == 1)		//	Forme du motif
	 {
		switch((*initiale).enveloppe.periodique) {
			case 0:
				(*commandes).selectifInitial[4].etat = 1; break;	//	périodique
			case 1:
				(*commandes).selectifInitial[5].etat = 1; break;	//	non périodique
			default:
				;
			}
		switch((*initiale).motif.forme) {
			case 0:
				(*commandes).selectifInitial[0].etat = 1; break;	//	Constant
			case 1:
				(*commandes).selectifInitial[3].etat = 1; break;	//	sinusoïdale
			case 2:
				(*commandes).selectifInitial[1].etat = 1; break;	//	Rectangle
			case 3:
				(*commandes).selectifInitial[2].etat = 1; break;	//	Dent de scie
			default:
				;
			}
	 	}
	
	switch((*initiale).porteuse.complexe)
		{
		case 0:
			(*commandes).selectifInitial[13].etat = 1;break;	//	Réel
		case 1:
			(*commandes).selectifInitial[14].etat = 1;break;	//	Complexe
		case 2:
			(*commandes).selectifInitial[12].etat = 1;break;	//	Peigne de dirac
		case 3:
			(*commandes).selectifInitial[11].etat = 1;break;	//	Constant
		default:
			;
		}
	return 0;
	}

	//-----------------    AFFICHAGE      -----------------------//

int parametrInitialAffiche(parametrInitialT * parametre) {

		//	Affiche les paramètres de la parametre

	printf("(*parametre).radianEta = %f\n", (*parametre).radianEta);
	printf("(*parametre).radianRho = %f\n", (*parametre).radianRho);
	printf("(*parametre).radianKhi = %f\n", (*parametre).radianKhi);
	printf("(*parametre).radianSym = %f\n", (*parametre).radianSym);
	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////
