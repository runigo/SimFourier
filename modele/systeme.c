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

#include "systeme.h"

	//		INITIALISATION
int systemeInitialiseHbardtSmdx2(systemeT * systeme);
int systemeInitialisePotentielReduit(systemeT * systeme);
int systemeInitialiseDt(systemeT * systeme, float dt);
int systemeProjectionInitiale(systemeT * systeme);
	//		ÉVOLUTION TEMPORELLE
int systemeIncremente(systemeT * systeme);
int systemeCouplage(systemeT * systeme);
int systemeInertie(systemeT * systeme);
int systemeCourantLimite(systemeT * systeme);

	//		JAUGE ET NORMALISATION
int systemeJaugeZero(systemeT * systeme);


/*------------------------  INITIALISATION  -------------------------*/

int systemeInitialisation(systemeT * systeme, int nombre, float dt) {

		// Initialisation des paramètres avec les valeurs implicites
	(*systeme).masse = MASSE_IMP;	//	Masse du quanton
	(*systeme).dx = DX_IMP;			//	Pas spatial
	(*systeme).hbar = HBAR_IMP;		//	Constante de Planck réduite

	//	Initialisation du système
	systemeInitialiseNombre(systeme, nombre);	//	Nombre de points
	systemeInitialiseDt(systeme, dt);			//	Pas temporel

		// Initialisation des fonctions
	fonctionInitialise(&(*systeme).ancien, nombre);
	fonctionInitialise(&(*systeme).actuel, nombre);
	fonctionInitialise(&(*systeme).nouveau, nombre);
	fonctionInitialise(&(*systeme).potentiel, nombre);

		// Initialisation du potentiel et du potentiel réduit
	systemeInitialisePotentiel(systeme, 1);

		// Initialisation du paramètre réduit
	systemeInitialiseHbardtSmdx2(systeme);

	return 0;
}

int systemeInitialisePotentiel(systemeT * systeme, int forme) {

	// Réinitialisation du potentiel
	int i;

	if((*systeme).nombre==0)
		{
		printf("ERREUR systemeInitialisePotentiel : (*systeme).nombre = %d\n", (*systeme).nombre);
		return 1;
		}
	else
		{
		for(i=0;i<(*systeme).nombre;i++)
			{		// Puits parabolique
			(*systeme).potentiel.reel[i] = ( (float)forme * i * ( (*systeme).nombre - i ) ) / (*systeme).nombre / (*systeme).nombre;
			}
		}
	return systemeInitialisePotentielReduit(systeme);
}
/*
int systemeInitialisePosition(systemeT * systeme, int forme) {

	// Initialisation des positions
	int i;
	float posi;
	float position = (float)forme / (*systeme).nombre;
	switch (forme)
		{
		case 0:
			position = 0;break;
		case 1:
			systemeProjectionInitiale(systeme);break;
		case 2:
			position = (float)forme / (*systeme).nombre;break;
		case 3:
			position = (float)forme / (*systeme).nombre;break;
		default:
			;
		}

	for(i=0;i<(*systeme).nombre;i++)
		{
		posi = position * (i-(*systeme).nombre/2);
		(*systeme).ancien.reel[i] = posi;
		(*systeme).actuel.reel[i] = posi;
		(*systeme).nouveau.reel[i] = posi;
		}

	return 0;
}
*/
int systemeInitialisePoint(systemeT * systeme, float ancien, float actuel, float nouveau, int i) {

	// Réinitialisation des positions

	(*systeme).ancien.reel[i] = ancien;
	(*systeme).actuel.reel[i] = actuel;
	(*systeme).nouveau.reel[i] = nouveau;

	return 0;
}

int systemeInitialiseNombre(systemeT * systeme, int nombre)
	{
	if(nombre>NOMBRE_MIN-1 && nombre<NOMBRE_MAX+1 && ((nombre & (nombre - 1)) == 0))
		{
		(*systeme).nombre = nombre;
		printf("(*systeme).nombre = %d\n", (*systeme).nombre);
		return 0;
		}
	else
		{
		(*systeme).nombre = NOMBRE_IMP;
		printf("ERREUR systemeInitialiseNombre(%d) (*systeme).nombre = %d\n", nombre, (*systeme).nombre);
		}
	return 1;
	}

int systemeInitialiseDt(systemeT * systeme, float dt)
	{
	int erreur=0;

	if(dt>=DT_MIN && dt<=DT_MAX)
		{
		(*systeme).dt = dt;
		printf("(*systeme).dt = %f\n", (*systeme).dt);
		erreur=0;
		}
	else
		{
		(*systeme).dt = DT_IMP;
		printf("ERREUR systemeInitialiseDt(%f) (*systeme).dt = %f\n", dt, (*systeme).dt);
		erreur=1;
		}

	erreur += systemeInitialisePotentielReduit(systeme);
	erreur += systemeInitialiseHbardtSmdx2(systeme);

	return erreur;
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
		(*systeme).masse = MASSE_IMP;
		printf("ERREUR systemeInitialiseMasse(%f) (*systeme).masse = %f\n", masse, (*systeme).masse);
		erreur=1;
		}

	erreur += systemeInitialisePotentielReduit(systeme);
	erreur += systemeInitialiseHbardtSmdx2(systeme);

	return erreur;
	}

int systemeInitialisePotentielReduit(systemeT * systeme) {

	// Initialisation du potentiel réduit v(x) = 2 + V(x).2m/hbar

	int i;

	if( (*systeme).hbar != 0.0 )
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
	if(denominateur != 0.0 )
		{
		(*systeme).hbardtSmdx2 = (*systeme).hbar * (*systeme).dt / denominateur;
		printf("(*systeme).hbardtSmdx2 = %f\n", (*systeme).hbardtSmdx2);
		return 0;
		}
	else
		{
		(*systeme).hbardtSmdx2 = (*systeme).hbar * (*systeme).dt / MASSE_IMP / DX_IMP / DX_IMP;
		printf("ERREUR (*systeme).hbardtSmdx2 = %f\n", (*systeme).hbardtSmdx2);
		return 1;
		}
}

/*------------------------  ÉVOLUTION TEMPORELLE  -------------------------*/

int systemeEvolution(systemeT * systeme, int duree, int mode) {
	int i;
	(void)mode;
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

	for(i=1;i<N;i++)	// La partie imaginaire du potentiel (V(x)) est le potentiel réduit v(x) = 2 + V(x).2m/hbar
		{
			// Partie réelle
		(*systeme).nouveau.reel[i] = (*systeme).ancien.reel[i] - (*systeme).hbardtSmdx2 * ((*systeme).actuel.imag[i] + (*systeme).actuel.imag[i] - (*systeme).potentiel.imag[i] * (*systeme).actuel.imag[i]);
			// Partie imaginaire
		(*systeme).nouveau.imag[i] = (*systeme).ancien.imag[i] - (*systeme).hbardtSmdx2 * ((*systeme).actuel.reel[i] + (*systeme).actuel.reel[i] - (*systeme).potentiel.imag[i] * (*systeme).actuel.reel[i]);
		}

	return 0;
	}

int systemeIncremente(systemeT * systeme)
	{
		//	Incrémente l'ancien et l'actuel état du systeme

	int i;

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
