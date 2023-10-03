/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
SimFourier 0.1 Transformation de Fourier
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

#include "systeme.h"

	//		INITIALISATION
int systemeInitialiseHbardtSmdx2(systemeT * systeme);

	//		ÉVOLUTION TEMPORELLE
int systemeIncremente(systemeT * systeme);
int systemeCouplage(systemeT * systeme);
int systemeInertie(systemeT * systeme);
int systemeCourantLimite(systemeT * systeme);

	//		JAUGE ET NORMALISATION
int systemeJaugeZero(systemeT * systeme);


/*------------------------  INITIALISATION  -------------------------*/

int systemeInitialiseSysteme(systemeT * systeme, int nombre) {

	//	Initialisation du système

	int nombre;			//	Nombre de points

		// Initialisation des paramètres avec les valeurs implicites
	(*systeme).masse = MASSE;	//	Masse du quanton
	(*systeme).dt = DT;			//	Pas temporel
	(*systeme).dx = DX;			//	Pas spatial
	(*systeme).hbar = HBAR;		//	Constante de Planck réduite
	systemeInitialiseHbardtSmdx2(systeme);

		// Initialisation des fonctions
	fonctionInitialise(&(*systeme).ancien, nombre);
	fonctionInitialise(&(*systeme).actuel, nombre);
	fonctionInitialise(&(*systeme).nouveau, nombre);
	fonctionInitialise(&(*systeme).fourier, nombre);
	fonctionInitialise(&(*systeme).potentiel, nombre);

		// Initialisation des paramètres réduits
	systemeInitialisePotentielReduit(systeme);
	systemeInitialiseHbardtSmdx2(systeme);

}

int systemeInitialiseNombre(systemeT * systeme, int nombre)
	{
	if(nombre>=NOMBRE_MIN && nombre<=NOMBRE_MAX)
		{
		(*systeme).nombre = nombre;
		printf("(*systeme).nombre = %d\n", (*systeme).nombre);
		return 0;
		}
	else
		{
		(*systeme).nombre = NOMBRE;
		printf("ERREUR systemeInitialiseNombre(%d) (*systeme).nombre = %d\n", nombre, (*systeme).nombre);
		}
	return 1;
	}

int systemeInitialiseMasse(systemeT * systeme, float masse)
	{
	int erreur;
	if(masse>=MASSE_MIN && masse<=MASSE_MAX)
		{
		(*systeme).masse = masse;
		printf("(*systeme).masse = %f\n", (*systeme).masse);
		erreur=0;
		}
	else
		{
		(*systeme).masse = MASSE;
		printf("ERREUR systemeInitialiseMasse(%f) (*systeme).masse = %f\n", masse, (*systeme).masse);
		erreur=1;
		}

	systemeInitialisePotentielReduit(systemeT * systeme);
	systemeInitialiseHbardtSmdx2(systemeT * systeme);

	return erreur;
	}

int systemeInitialisePotentielReduit(systemeT * systeme) {

	// Initialisation du potentiel réduit v(x) = 2 + V(x).2m/hbar

	if((*systeme).hbar =! 0 )
		{
		for(i=0;i<NOMBRE_MAX;i++)
			{
			(*systeme).potentiel.imag[i] = 2 + 2 * (*systeme).potentiel.reel[i] * (*systeme).masse / (*systeme).hbar;
			}
		return 0;
		}
	else
		{
		for(i=0;i<NOMBRE_MAX;i++)
			{
			(*systeme).potentiel.imag[i] = 2 + 2 * (*systeme).potentiel.reel[i];
			}
		printf("ERREUR DANS LE CALCUL DU POTENTIEL RÉDUIT\n");
		return -1;
		}
}

int systemeInitialiseHbardtSmdx2(systemeT * systeme) {

	// Initialisation du paramètre réduit hbardtSmdx2 = hbar dt / m dx2

	float denominateur = (*systeme).masse * (*systeme).dx * (*systeme).dx;
	if(denominateur =! 0 )
		{
		(*systeme).hbardtSmdx2 = (*systeme).hbar * (*systeme).dt / denominateur;
		printf("(*systeme).hbardtSmdx2 = %d\n", (*systeme).hbardtSmdx2);
		return 0;
		}
	else
		{
		hbardtSmdx2 = (*systeme).hbar * (*systeme).dt / MASSE / DX / DX;
		printf("ERREUR (*systeme).hbardtSmdx2 = %d\n", (*systeme).hbardtSmdx2);
		return 1;
		}
}

/*------------------------  ÉVOLUTION TEMPORELLE  -------------------------*/

int systemeEvolution(systemeT * systeme, int duree) {
	int i;

		//	Évolution du système pendant duree*dt
	for(i=0;i<duree;i++) {
		systemeInertie(systeme);
		systemeIncremente(systeme);
		}

	return 0;
	}

int systemeInertie(systemeT * systeme) {

		//	Équation de Schrödinger appliqué au système

	int i;
	int N = (*systeme).nombre-1;

		//	Cas des extrémitées


		// Reste de la chaîne

	for(i=1;i<N;i++)
		{
			// Partie réelle
		(*systeme).nouveau.reel[i] = (*systeme).ancien.reel[i] - (*systeme).Dt * ((*systeme).actuel.imag[i] + (*systeme).actuel.imag[i] - (*systeme).potentiel.imag[i] * (*systeme).actuel.imag[i]);
			// Partie imaginaire
		(*systeme).nouveau.imag[i] = (*systeme).ancien.imag[i] - (*systeme).Dt * ((*systeme).actuel.reel[i] + (*systeme).actuel.reel[i] - (*systeme).potentiel.imag[i] * (*systeme).actuel.reel[i]);
		}

	return 0;
	}

int systemeIncremente(systemeT * systeme)
	{
		//	Incrémente l'ancien et l'actuel état du systeme

	for(i=0;i<(*systeme).nombre;i++)
		{
			// Partie réelle
		(*systeme).ancien.reel[i] = (*systeme).actuel.reel[i];
			// Partie imaginaire
		(*systeme).ancien.imag[i] = (*systeme).actuel.imag[i];
			// Partie réelle
		(*systeme).actuel.reel[i] = (*systeme).nouveau.reel[i];
			// Partie imaginaire
		(*systeme).actuel.imag[i] = (*systeme).nouveau.imag[i];
		}

	return 0;
	}

/*----------------JAUGE ET NORMALISATION-------------------*/

int systemeJaugeZero(systemeT * systeme) {
	(void)systeme;
	return 0;
	}

//////////////////////////////////////////////////////////////////////////
