/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.3 Transformation de Fourier
(d'après SiCP 2.5 simulateur de chaîne de pendules, février 2021)
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

#include "parametrSystem.h"

				//		Projections du systeme sur les commandes,
				//		les capteurs et les graphes

	//	INITIALISATION
int parametreInitialisePointDeVue(parametrSystemT * parametre,  float r,float psi, float phi);
int parametreReinitialiseBase(parametrSystemT * parametre);

	//	PROJECTION

	//	CHANGE

	//	AFFICHAGE


	//-----------------    INITIALISATION      -----------------------//
int parametrSystemInitialise(parametrSystemT * parametre)
	{

	(*parametre).logCouplage = 1.0;// / log( (COUPLAGE_MAX/COUPLAGE_MIN) );
	(*parametre).logDissipation = 1.0;// / log( DISSIPATION_MAX/DISSIPATION_MIN );
	(*parametre).logJosephson = 1.0;// / log( JOSEPHSON_MAX/JOSEPHSON_MIN );
	(*parametre).logAmplitude = 1.0;// / log( AMPLITUDE_MAX/AMPLITUDE_MIN );
	(*parametre).logFrequence = 1.0;// / log( FREQUENCE_MAX/FREQUENCE_MIN );


	return 0;
	}

	//-----------------    PROJECTION      -----------------------//

int parametrSystemCommandes(systemeT * systeme, parametrSystemT * parametre, commandesT * commandes) {

		// Projette le système sur les commandes dans le mode simulation

(void)systeme;
(void)parametre;
(void)commandes;
/*
	//float theta;
	//float ratioRotatif = 0.9;
	//float courantJosephson = parametreValeurAbsolue((*systeme).moteurs.courantJosephson);

				//	Projection sur les boutons rotatifs
	 //	Couplage
	theta = DEUXPI * (*parametre).logCouplage * log( (*systeme).couplage / (COUPLAGE_MIN * (*systeme).nombre) );
	(*commandes).rotatifPositionX[0]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[0]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	 //	Dissipation
	theta = DEUXPI * (*parametre).logDissipation * log( (*systeme).dissipation/DISSIPATION_MIN );
	(*commandes).rotatifPositionX[1]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[1]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Amplitude du moteur josephson
	theta = DEUXPI * (*parametre).logJosephson * log( parametreValeurAbsolue(courantJosephson/JOSEPHSON_MIN) );
	(*commandes).rotatifPositionX[2]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[2]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));
	//	Amplitude du moteur périodique
	theta = DEUXPI * (*parametre).logAmplitude * log( (*systeme).moteurs.amplitude/AMPLITUDE_MIN );
	(*commandes).rotatifPositionX[3]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[3]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Fréquence du moteurs
	theta = DEUXPI * (*parametre).logFrequence * log( (*systeme).moteurs.frequence/FREQUENCE_MIN );
	(*commandes).rotatifPositionX[4]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[4]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));



				//	Projection sur les petits boutons de droite
	//int i;
	//for(i=0;i<BOUTON_COMMANDES;i++) (*commandes).boutonEtat[i]=0;

			//	Conditions aux limites
	switch((*systeme).libreFixe) {
		case 0:
			(*commandes).boutonEtat[0]=1;break; //	Périodique
		case 1:
			(*commandes).boutonEtat[1]=1;break; //	Libre
		case 2:
			(*commandes).boutonEtat[2]=1;break; //	Fixe
		case 3:
			(*commandes).boutonEtat[3]=1;break; //	Mixte
		case 4:
			(*commandes).boutonEtat[3]=1;break; //	Mixte
		default:
			;
		}

	if((*systeme).moteurs.etatJosephson ==1)
		{
		(*commandes).boutonEtat[7]=1; //	Marche
		}
	else
		{
		(*commandes).boutonEtat[8]=1; //	Arrêt
		}

	if((*systeme).moteurs.courantJosephson < 0)
		{
		(*commandes).boutonEtat[10]=1; //	Gauche
		}
	else
		{
	   	(*commandes).boutonEtat[9]=1; //	Droite
	    }

	switch((*systeme).moteurs.generateur)
		{
		case 0:
			(*commandes).boutonEtat[11]=1;break; //	Arrêt
		case 1:
			(*commandes).boutonEtat[12]=1;break; //	Sinus
		case 2:
			(*commandes).boutonEtat[13]=1;break; //	Carré
		case 3:
			(*commandes).boutonEtat[14]=1;break; //	Impulsion
		default:
			;
		}

	if((*systeme).moteurs.fluxon == 1)
		{
		if((*systeme).moteurs.deltaDephasage > 0)
			{
			(*commandes).boutonEtat[15]=1;
			}
		else
			{
			(*commandes).boutonEtat[16]=1;
		    }
		}

				//	Projection sur les petits boutons du bas

	for(i=0;i<TRIANGLE_COMMANDES;i++) (*commandes).triangleEtat[i]=0;

		//	Rotation automatique du point de vue
	switch((*parametre).rotation)
		{
		case 3:
			(*commandes).triangleEtat[0]=1;break;
		case 1:
			(*commandes).triangleEtat[1]=1;break;
		case 0:
			(*commandes).triangleEtat[2]=0;break;
		case -1:
			(*commandes).triangleEtat[3]=1;break;
		case -3:
			(*commandes).triangleEtat[4]=1;break;
		default:
			;
		}
*/
	return 0;
	}

int parametreControleurCommandes(parametrSystemT * parametre, commandesT * commandes, int duree, int mode) {

		// Projette le controleur sur les commandes

(void)parametre;
(void)commandes;
(void)duree;
(void)mode;
/*
		//	Vitesse de la simulation
	if(duree<DUREE_IMP)
		{
			if(duree==1) (*commandes).triangleEtat[5]=-1; else (*commandes).triangleEtat[6]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).a * duree + (*commandes).b);
		}
	else
		{
		if(duree>DUREE_IMP)
			{
			if(duree==DUREE_MAX) (*commandes).triangleEtat[10]=-1; else (*commandes).triangleEtat[9]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).A * duree + (*commandes).B);
			}
		else
			{
			(*commandes).triangleEtat[8]=1;
			}
		}

	if(mode<0)
		{
		(*commandes).triangleEtat[7]=2;
		}
*/
	return 0;
	}

/*
int parametreObservablesCapteurs(observablesT * observables, parametrSystemT * parametre, capteursT * capteurs) {

		//	Projette les observables sur les capteurs

	(void)parametre;
	float a;
	int i, k, y0;
						//	Observables	:	0 Energie, 1 Cinetique, 2 Couplage, 3 Rappel
						//	Capteurs	:	0, 1, 2 : Somme, 3, 4, 5 : droite/gauche
		//	SOMME
	if((*observables).observable[0].maximumSomme!=0.0)
		{
		a = -(float)((*capteurs).capteur[0].hauteur) / (*observables).observable[0].maximumSomme;
		}
	else
		{
		a = 0.0;
		}
	y0 = (*capteurs).capteur[0].yZero;
	for(i=0;i<DUREE_CAPTEURS;i++)
		{
		k=(i+(*observables).index+1)%DUREE_CAPTEURS;
		(*capteurs).capteur[0].somme[i].y = (int)(a*(*observables).observable[3].somme[k]) + y0;
		(*capteurs).capteur[1].somme[i].y = (int)(a*(*observables).observable[1].somme[k]) + y0;
		(*capteurs).capteur[2].somme[i].y = (int)(a*(*observables).observable[2].somme[k]) + y0;
		}


		//	GAUCHE DROITE
	if((*observables).observable[0].maximumSomme!=0.0)
		{
		a = -(float)((*capteurs).capteur[3].hauteur) / (*observables).observable[0].maximumSomme;
		}
	else
		{
		a = 0.0;
		}
	y0 = (*capteurs).capteur[3].yZero;
	for(i=0;i<DUREE_CAPTEURS;i++)
		{
		k=(i+(*observables).index+1)%DUREE_CAPTEURS;
		(*capteurs).capteur[3].gauche[i].y = (int)(a*(*observables).observable[0].gauche[k]) + y0;
		(*capteurs).capteur[3].droite[i].y = (int)(a*(*observables).observable[0].droite[k]) + y0;
		(*capteurs).capteur[3].somme[i].y = (int)(a*(*observables).observable[0].somme[k]) + y0;
		}
	return 0;
	}
*/

	//-----------------    CHANGE LA PROJECTION     -----------------------//

int parametrSystemChangeFenetre(parametrSystemT * parametre, int x, int y) {

		//	Enregistre le changement de la taille de la fenêtre
	(void)parametre;
	(void)x;
	(void)y;
	//(*parametre).fenetreX=x;
	//(*parametre).fenetreY=y;

	return 0;
	}


	//-----------------    AFFICHAGE      -----------------------//

void parametrSystemAffiche(parametrSystemT * parametre) {

	//	Affiche les paramètres de la parametre
	(void)parametre;

	//printf("(*parametre).ratioXY = %f\n", (*parametre).ratioXY);
	//printf("(*parametre).hauteur = %d\n", (*parametre).hauteur);
	//printf("(*parametre).largeur = %d\n", (*parametre).largeur);
	//printf("(*parametre).fenetreX = %d\n", (*parametre).fenetreX);
	//printf("(*parametre).fenetreY = %d\n", (*parametre).fenetreY);
	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////
