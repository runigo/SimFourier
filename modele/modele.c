/*
Copyright novembre 2023, Stephan Runigo
runigo@free.fr
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

#include "modele.h"

	//		INITIALISATION

	//		ÉVOLUTION TEMPORELLE

	//		JAUGE ET NORMALISATION
int modeleJaugeZero(modeleT * modele);


/*------------------------  INITIALISATION  -------------------------*/

int modeleInitialisation(modeleT * modele, int nombre, int dt) {

		(*modele).nombre =nombre;			//	Nombre de points

		//fprintf(stderr, " Initialisation du système\n");
	systemeInitialisation(&(*modele).systeme, nombre, dt);

		//fprintf(stderr, " Initialisation de fourier\n");
	fourierInitialise(&(*modele).fourier, nombre);

		//	Initialisation de initiale
	initialeInitialisation(&(*modele).initiale, (*modele).nombre);

		// Initialisation du moteurs
	//moteursInitialisation(moteursT * moteurs);
	return 0;
}

int modeleProjectionInitiale(modeleT * modele) {

	// Projette les positions initiales sur le système

		// Mise à jour des positions initiales
	initialeCreationPosition(&(*modele).initiale,1);

		// Projection sur le système
	int i;
	for(i=0;i<(*modele).nombre;i++)
		{
		(*modele).systeme.actuel.reel[i] = (*modele).initiale.enveloppe.reel[i] * (*modele).initiale.porteuse.reel[i];
		(*modele).systeme.actuel.imag[i] = (*modele).initiale.enveloppe.imag[i] * (*modele).initiale.porteuse.imag[i];
		}

	return 0;
}


/*----------------JAUGE ET NORMALISATION-------------------*/

int modeleJaugeZero(modeleT * modele) {
	(void)modele;
	return 0;
	}

//////////////////////////////////////////////////////////////////////////
