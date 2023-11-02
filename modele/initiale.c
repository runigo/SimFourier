/*
Copyright octobre 2023, Stephan Runigo
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

#include "initiale.h"

	//		INITIALISATION

	//		ÉVOLUTION TEMPORELLE
int initialeIncremente(initialeT * initiale);

	//		JAUGE ET NORMALISATION
int initialeJaugeZero(initialeT * initiale);


/*------------------------  INITIALISATION  -------------------------*/

int initialeInitialisation(initialeT * initiale, int nombre) {

		fonctionInitialise(&(*initiale).enveloppe, nombre);
		fonctionInitialise(&(*initiale).porteuse, nombre);

		(*initiale).nombre = nombre;			//	Nombre de points

		(*initiale).frequence = 1;		//	fréquence de la porteuse
		(*initiale).amplitude = 1;		//	amplitude de la porteuse
		(*initiale).largeur = 1;			//	largeur de l'enveloppe

		(*initiale).forme = 0;

	return 0;
}

int initialeInitialisePosition(initialeT * initiale, int forme) {

	// Initialisation des positions
(void)initiale;
(void)forme;
/*	switch (forme)
		{
		case 0:
			position = 0;break;
		default:
			;
		}
*/
	return 0;
}

int initialeInitialiseNombre(initialeT * initiale, int nombre)
	{
	if(nombre>NOMBRE_MIN-1 && nombre<NOMBRE_MAX+1 && ((nombre & (nombre - 1)) == 0))
		{
		(*initiale).nombre = nombre;
		printf("(*initiale).nombre = %d\n", (*initiale).nombre);
		return 0;
		}
	else
		{
		(*initiale).nombre = NOMBRE_IMP;
		printf("ERREUR initialeInitialiseNombre(%d) (*initiale).nombre = %d\n", nombre, (*initiale).nombre);
		}
	return 1;
	}

/*------------------------  ÉVOLUTION TEMPORELLE  -------------------------*/

int initialeEvolution(initialeT * initiale, int duree) {
(void)initiale;
(void)duree;

	return 0;
	}

/*----------------JAUGE ET NORMALISATION-------------------*/

//////////////////////////////////////////////////////////////////////////
