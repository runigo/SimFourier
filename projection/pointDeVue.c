/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
(SiCP 2.5 simulateur de chaîne de pendules, fevrier 2021)
SimFourier 1.0 Transformation de Fourier
Ce logiciel est un programme informatique servant à donner une représentation
graphique de la transformation de Fourier à 1 dimension.
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

#include "pointDeVue.h"

				//		Projection de la chaîne de pendules et des
				//		observables sur l'interface graphique

	//	INITIALISATION

	//	CHANGE

	//	AFFICHAGE


	//-----------------    INITIALISATION      -----------------------//

int pointDeVueInitialise(pointDeVueT * pointDeVue, float r, float psi, float phi)
	{
		// Initialise la position de l'observateur et calcul les vecteurs perpendiculaires

	vecteurInitialisePolaire(pointDeVue, r, psi, phi);
	pointDeVueReinitialiseBase(pointDeVue);
	return 0;
	}

int pointDeVueReinitialiseBase(pointDeVueT * pointDeVue)
	{
		// Réinitialise les vecteurs perpendiculaires

	vecteurInitialiseVecteurPhi(&(*pointDeVue).pointDeVue, &(*projection).vecteurPhi, (*pointDeVue).largeur);
		vecteurInitialiseVecteurPsi(&(*pointDeVue).pointDeVue, &(*projection).vecteurPsi, (*pointDeVue).hauteur);
		}

	// Calcul des vecteurs perpendiculaires au vecteur point de vue
	vecteurInitialisePhi(&(*pointDeVue).pointDeVue, &(*pointDeVue).vecteurPhi, &(*pointDeVue).hauteur);
	vecteurInitialisePsi(&(*pointDeVue).pointDeVue, &(*pointDeVue).vecteurPsi, &(*pointDeVue).largeur);
	return 0;
	}


	//-----------------    CHANGE LE POINT DE VUE     -----------------------//

int pointDeVueChangePhi(pointDeVueT * pointDeVue, float x) {

		// Change la position de l'observateur suivant phi

	float r, psi, phi;

	r = (*pointDeVue).pointDeVue.r;
	psi = (*pointDeVue).pointDeVue.psi;
	phi = (*pointDeVue).pointDeVue.phi + x;

		// phi reste inférieur à PI
	if(phi > PI)
		{
		phi = PI;
		}

		// phi reste supérieur à zéro
	if(phi < 0.0)
		{
		phi = 0.0;
		}

	vecteurInitialisePolaire(&(*pointDeVue).pointDeVue, r, psi, phi);
	pointDeVueReinitialiseBase(pointDeVue);

	return 0;
	}

int pointDeVueChangePsi(pointDeVueT * pointDeVue, float x) {

		// Change la position de l'observateur suivant psi

	float r, psi, phi;

	r = (*pointDeVue).r;
	psi = (*pointDeVue).psi + x;
	phi = (*pointDeVue).phi;

	if(psi > PI)
		{
		psi = psi - DEUXPI;
		}

	if(psi < -PI)
		{
		psi = psi + DEUXPI;
		}

	vecteurInitialisePolaire(&(*pointDeVue).pointDeVue, r, psi, phi);
	pointDeVueReinitialiseBase(pointDeVue);

	return 0;
	}

int pointDeVueChangeTaille(pointDeVueT * pointDeVue, float x) {

		// Change la taille de la chaîne

	int largeur = (*pointDeVue).largeur * x;

	if(largeur > LARGEUR_MAX)
		{
		printf("Maximum de la taille ateinte\n");
		}
	else
		{
		if(largeur < LARGEUR_MIN)
			{
			printf("Minimum de la taille ateinte\n");
			}
		else
			{
			(*pointDeVue).largeur = largeur;
			(*pointDeVue).hauteur = (int)(largeur/(*pointDeVue).ratioLH);
			printf("(*projection).hauteur = %d\n", (*pointDeVue).hauteur);
			printf("(*projection).largeur = %d\n", (*pointDeVue).largeur);
			}
		}

	return 0;
	}

	//-----------------    AFFICHAGE      -----------------------//

int pointDeVueAffiche(pointDeVueT * pointDeVue) {

		// Affiche les valeurs de psi et phi

	float r, psi, phi;

	r = (*pointDeVue).r;
	psi = (*pointDeVue).psi;
	phi = (*pointDeVue).phi;

	printf("(*projection).pointDeVue.r = %f\n", r);
	printf("(*projection).pointDeVue.psi = %f\n", psi);
	printf("(*projection).pointDeVue.phi = %f\n", phi);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////
