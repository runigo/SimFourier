/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
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

#include "projectionInitial.h"

				//		Projections des caractéristiques de la fonction initiale
				//		  sur les commandes

	//	INITIALISATION

	//	PROJECTION

	//	CHANGE

	//	AFFICHAGE


	//-----------------    INITIALISATION      -----------------------//
int projectionInitialInitialise(projectionInitialT * projection)
	{

	//(*projection).fenetreX = FENETRE_X;	// hauteur de la fenêtre
	//(*projection).fenetreY = FENETRE_Y;	// largeur de la fenêtre

	//(*projection).ratioXY=(float)FENETRE_X/(float)FENETRE_Y; // Rapport entre les dimensions de la fenêtre

	(*projection).logCouplage = 1.0;// / log( (COUPLAGE_MAX/COUPLAGE_MIN) );
	(*projection).logDissipation = 1.0;// / log( DISSIPATION_MAX/DISSIPATION_MIN );
	(*projection).logJosephson = 1.0;// / log( JOSEPHSON_MAX/JOSEPHSON_MIN );
	(*projection).logAmplitude = 1.0;// / log( AMPLITUDE_MAX/AMPLITUDE_MIN );
	(*projection).logFrequence = 1.0;// / log( FREQUENCE_MAX/FREQUENCE_MIN );


	return 0;
	}

	//-----------------    PROJECTION      -----------------------//

int projectionInitialeCommandes(initialeT * initiale, projectionInitialT * projection, commandesT * commandes) {

		// Projette les caractéristiques de la fonction initiale sur les commandes dans le mode initiale

(void)initiale;
(void)projection;
(void)commandes;
/*
	//float theta;
	//float ratioRotatif = 0.9;
	//float courantJosephson = projectionValeurAbsolue((*initiale).moteurs.courantJosephson);

				//	Projection sur les boutons rotatifs
	 //	Couplage
	theta = DEUXPI * (*projection).logCouplage * log( (*initiale).couplage / (COUPLAGE_MIN * (*initiale).nombre) );
	(*commandes).rotatifPositionX[0]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[0]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	 //	Dissipation
	theta = DEUXPI * (*projection).logDissipation * log( (*initiale).dissipation/DISSIPATION_MIN );
	(*commandes).rotatifPositionX[1]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[1]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Amplitude du moteur josephson
	theta = DEUXPI * (*projection).logJosephson * log( projectionValeurAbsolue(courantJosephson/JOSEPHSON_MIN) );
	(*commandes).rotatifPositionX[2]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[2]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));
	//	Amplitude du moteur périodique
	theta = DEUXPI * (*projection).logAmplitude * log( (*initiale).moteurs.amplitude/AMPLITUDE_MIN );
	(*commandes).rotatifPositionX[3]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[3]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Fréquence du moteurs
	theta = DEUXPI * (*projection).logFrequence * log( (*initiale).moteurs.frequence/FREQUENCE_MIN );
	(*commandes).rotatifPositionX[4]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[4]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));


*/

				//	Projection sur les petits boutons de droite
	int i;
	for(i=0;i<SELECTIF_COMMANDES;i++) (*commandes).selectif[i].etat=0;

			//	Forme du motif
	switch((*initiale).motif.forme) {
		case 0: //	Constant
			(*commandes).selectif[0].etat=1;break;
		case 1: //	sinusoïdale
			(*commandes).selectif[3].etat=1;break;
		case 2: //	Rectangle
			(*commandes).selectif[1].etat=1;break;
		case 3: //	Dent de scie
			(*commandes).selectif[2].etat=1;break;
		case 4: //	Gaussienne
			(*commandes).selectif[6].etat=1;break;
		case 5: //	Lorentzienne
			(*commandes).selectif[7].etat=1;break;
		case 6: //	Sinus cardinale
			(*commandes).selectif[8].etat=1;break;
		default:
			;
		}

	if((*initiale).enveloppe.periodique == 1)
		{
		(*commandes).selectif[5].etat=1; //	Apériodique
		}
	else
		{
		(*commandes).selectif[4].etat=1; //	Périodique
		}

	switch((*initiale).porteuse.complexe)
		{
		case 0:
			(*commandes).selectif[11].etat=1;break; //	Réel
		case 1:
			(*commandes).selectif[12].etat=1;break; //	Complexe
		case 2:
			(*commandes).selectif[10].etat=1;break; //	Peigne de dirac
		case 3:
			(*commandes).selectif[9].etat=1;break; //	Constant
		default:
			;
		}
	return 0;
	}

	//-----------------    CHANGE LA PROJECTION     -----------------------//

int projectionInitialeChangeFenetre(projectionInitialT * projection, int x, int y) {

		//	Enregistre le changement de la taille de la fenêtre
	(void)projection;
	(void)x;
	(void)y;
	//(*projection).fenetreX=x;
	//(*projection).fenetreY=y;

	return 0;
	}


	//-----------------    AFFICHAGE      -----------------------//

void projectionInitialeAffiche(projectionInitialT * projection) {

	//	Affiche les paramètres de la projection
	(void)projection;

	//printf("(*projection).ratioXY = %f\n", (*projection).ratioXY);
	//printf("(*projection).hauteur = %d\n", (*projection).hauteur);
	//printf("(*projection).largeur = %d\n", (*projection).largeur);
	//printf("(*projection).fenetreX = %d\n", (*projection).fenetreX);
	//printf("(*projection).fenetreY = %d\n", (*projection).fenetreY);
	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////
