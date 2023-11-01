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
int pointDeVueReinitialiseBase(pointDeVueT * pointDeVue);

	//	CHANGE

	//	AFFICHAGE


	//-----------------    INITIALISATION      -----------------------//

int pointDeVueInitialise(pointDeVueT * pointDeVue)
	{
	vecteurInitialisePolaire(&(*pointDeVue).position, DISTANCE_IMP, -1.062487, 1.695699);
	vecteurInitialisePolaire(&(*pointDeVue).vecteurPhi, 0.0, 0.0, 0.0);
	vecteurInitialisePolaire(&(*pointDeVue).vecteurPsi, 0.0, 0.0, 0.0);
	pointDeVueReinitialiseBase(pointDeVue);
	return 0;
	}

int pointDeVueReinitialiseBase(pointDeVueT * pointDeVue)
	{
		// Réinitialise les vecteurs perpendiculaires
	vecteurInitialiseVecteurPhi(&(*pointDeVue).position, &(*pointDeVue).vecteurPhi, (*pointDeVue).position.r);
	vecteurInitialiseVecteurPsi(&(*pointDeVue).position, &(*pointDeVue).vecteurPsi, (*pointDeVue).position.r);
	return 0;
	}
	//-----------------    CHANGE LE POINT DE VUE     -----------------------//

int pointDeVueChangePhi(pointDeVueT * pointDeVue, float x) {

		// Change la position de l'observateur suivant phi

	float r, psi, phi;

	r = (*pointDeVue).position.r;
	psi = (*pointDeVue).position.psi;
	phi = (*pointDeVue).position.phi + x;

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

	vecteurInitialisePolaire(&(*pointDeVue).position, r, psi, phi);
	pointDeVueReinitialiseBase(pointDeVue);

	return 0;
	}

int pointDeVueChangePsi(pointDeVueT * pointDeVue, float x) {

		// Change la position de l'observateur suivant psi

	float r, psi, phi;

	r = (*pointDeVue).position.r;
	psi = (*pointDeVue).position.psi + x;
	phi = (*pointDeVue).position.phi;

	if(psi > PI)
		{
		psi = psi - DEUXPI;
		}

	if(psi < -PI)
		{
		psi = psi + DEUXPI;
		}

	vecteurInitialisePolaire(&(*pointDeVue).position, r, psi, phi);
	pointDeVueReinitialiseBase(pointDeVue);

	return 0;
	}

int pointDeVueChangeDistance(pointDeVueT * pointDeVue, float x) {

		// Change la distance de l'observateur

	float distance = (*pointDeVue).position.r * x;

	if(distance > DISTANCE_MAX)
		{
		printf("Maximum de la distance ateinte\n");
		}
	else
		{
		if(distance < DISTANCE_MIN)
			{
			printf("Minimum de la distance ateinte\n");
			}
		else
			{
			(*pointDeVue).position.r = distance;
			printf("(*pointDeVue).position.r = %f\n", (*pointDeVue).position.r);
			}
		}
	pointDeVueReinitialiseBase(pointDeVue);

	return 0;
	}

	//-----------------    AFFICHAGE      -----------------------//

int pointDeVueAffiche(pointDeVueT * pointDeVue) {

		// Affiche les valeurs de psi et phi

	float r, psi, phi;

	r = (*pointDeVue).position.r;
	psi = (*pointDeVue).position.psi;
	phi = (*pointDeVue).position.phi;

	printf("(*projection).pointDeVue.r = %f\n", r);
	printf("(*projection).pointDeVue.psi = %f\n", psi);
	printf("(*projection).pointDeVue.phi = %f\n", phi);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////
