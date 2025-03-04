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

#include "modele.h"

	//		INITIALISATION

	//		ÉVOLUTION
int modeleProjectionSystemeFourier(modeleT * modele);
int modeleProjectionSystemeEnergie(modeleT * modele);

	//		CHANGE

	//		JAUGE ET NORMALISATION
//int modeleJaugeZero(modeleT * modele);


/*------------------------  INITIALISATION  -------------------------*/

int modeleInitialisation(modeleT * modele, int nombre, float dt) {

		(*modele).change = 1;	//	Indicateur de variation d'un paramètre

		//fprintf(stderr, " Initialisation du système\n");
	systemeInitialisation(&(*modele).systeme, nombre, dt);

		//fprintf(stderr, " Initialisation de fourier\n");
	fourierInitialise(&(*modele).fourier, nombre);

		//	Initialisation de initiale
	initialeInitialisation(&(*modele).initiale, nombre);

		// Initialisation du moteurs
	//moteursInitialisation(moteursT * moteurs);
	return 0;
}

int modeleIncrementationInitiale(modeleT * modele) {

		//fprintf(stderr, " Incrémentation ancien et nouveau \n");

	int i;
	for(i=0;i<(*modele).systeme.nombre;i++)
		{
		(*modele).systeme.nouveau.reel[i] = (*modele).systeme.actuel.reel[i];
		(*modele).systeme.nouveau.imag[i] = (*modele).systeme.actuel.imag[i];
		(*modele).systeme.ancien.reel[i] = (*modele).systeme.actuel.reel[i];
		(*modele).systeme.ancien.imag[i] = (*modele).systeme.actuel.imag[i];
		}

	return 0;
}

int modeleProjectionInitiale(modeleT * modele) {

	// Projette les positions initiales sur le système
		//fprintf(stderr, " Projection sur le système\n");
	int i;
	for(i=0;i<(*modele).systeme.nombre;i++)  //  Partie réelle
		{
		(*modele).systeme.actuel.reel[i]
			= (*modele).initiale.enveloppe.fonction.reel[i] * (*modele).initiale.porteuse.fonction.reel[i];
		}

	if((*modele).initiale.porteuse.complexe == 1)
		{
		for(i=0;i<(*modele).systeme.nombre;i++)  //  Partie imaginaire
			{
		(*modele).systeme.actuel.imag[i]
			= (*modele).initiale.enveloppe.fonction.reel[i] * (*modele).initiale.porteuse.fonction.imag[i];
			}
		}
	else
		{
		for(i=0;i<(*modele).systeme.nombre;i++)  //  Partie imaginaire
			{
		(*modele).systeme.actuel.imag[i] = 0;
			}
		}

	return 0;
}
/*
int modeleProjectionInitiale(modeleT * modele) {

	// Projette les positions initiales sur le système
		//fprintf(stderr, " Projection sur le système\n");
	int i;
	for(i=0;i<(*modele).systeme.nombre;i++)
		{
		(*modele).systeme.actuel.reel[i]
			= (*modele).initiale.enveloppe.fonction.reel[i] * (*modele).initiale.porteuse.fonction.reel[i];
		(*modele).systeme.actuel.imag[i]
			= (*modele).initiale.enveloppe.fonction.reel[i] * (*modele).initiale.porteuse.fonction.imag[i];
		(*modele).systeme.nouveau.reel[i] = (*modele).systeme.actuel.reel[i];
		(*modele).systeme.nouveau.imag[i] = (*modele).systeme.actuel.imag[i];
		(*modele).systeme.ancien.reel[i] = (*modele).systeme.actuel.reel[i];
		(*modele).systeme.ancien.imag[i] = (*modele).systeme.actuel.imag[i];
		}

	return 0;
}
*/
/*------------------------  ÉVOLUTION DU MODÈLE  -------------------------*/

int modeleEvolutionInitiale(modeleT * modele, int duree, int echelle)
	{
	(void)duree;
	(void)echelle;
		//fprintf(stderr, "Calcul de la fonction initiale\n");
	modeleProjectionInitiale(modele);

		//fprintf(stderr, "Projection du système sur les spectres\n");
	modeleProjectionSystemeFourier(modele);

		//fprintf(stderr, "Calcul des spectres\n");
	//fourierCalcule(&(*modele).fourier);

		//fprintf(stderr, "Normalisation des spectres\n");
	//fonctionNormalise(&(*modele).fourier.spectre, echelle);
	//fonctionNormalise(&(*modele).fourier.gauche, echelle);
	//fonctionNormalise(&(*modele).fourier.droite, echelle);

		//fprintf(stderr, "Mise à jour des observables\n");
	//observablesMiseAJour(&(*modele).observables, &(*modele).modele.systeme);

	return 0;
	}

int modeleEvolutionSimulation(modeleT * modele, int duree, int echelle)
	{
	(void)duree;
	(void)echelle;
		//fprintf(stderr, "Evolution temporelle du système\n");
	systemeEvolution(&(*modele).systeme, duree, 1);

		//fprintf(stderr, "Projection du système sur les spectres\n");
	modeleProjectionSystemeFourier(modele);

		//fprintf(stderr, "Calcul des spectres\n");
	//fourierCalcule(&(*modele).fourier);

		//fprintf(stderr, "Normalisation des spectres\n");
	//fonctionNormalise(&(*modele).fourier.spectre, echelle);
	//fonctionNormalise(&(*modele).fourier.gauche, echelle);
	//fonctionNormalise(&(*modele).fourier.droite, echelle);

		//fprintf(stderr, "Mise à jour des observables\n");
	//observablesMiseAJour(&(*modele).observables, &(*modele).modele.systeme);

	return 0;
	}

int modeleEnergiePotentielle(modeleT * modele, int duree, int echelle)
	{
	(void)duree;
	(void)echelle;
	(void)modele;

		fprintf(stderr, "Enregistrement de l'énergie potentielle\n");
	//modeleProjectionInitiale(modele);

		//fprintf(stderr, "Projection sur la fonction énergie potentielle\n");
	//modeleProjectionSystemeEnergie(modele);

		//fprintf(stderr, "Normalisation des spectres\n");
	//fonctionNormalise(&(*modele).fourier.spectre, echelle);

	return 0;
	}

int modeleProjectionSystemeFourier(modeleT * modele)
	{
		//	Projection du système sur les fonctions de fourier
	int i;
	int j = (*modele).systeme.nombre;

	for(i=0;i<j;i++)
		{
		(*modele).fourier.spectre.reel[i]=(*modele).systeme.actuel.reel[i];
		(*modele).fourier.spectre.imag[i]=(*modele).systeme.actuel.imag[i];
		}

	j = (*modele).systeme.nombre/2;

	for(i=0;i<j;i++)
		{
		(*modele).fourier.gauche.reel[i]=(*modele).systeme.actuel.reel[i];
		(*modele).fourier.gauche.imag[i]=(*modele).systeme.actuel.imag[i];
		(*modele).fourier.droite.reel[i]=(*modele).systeme.actuel.reel[i+j];
		(*modele).fourier.droite.imag[i]=(*modele).systeme.actuel.imag[i+j];
		}

	return 0;
	}

int modeleProjectionSystemeEnergie(modeleT * modele)
	{
		//	Projection de la fonction initiale sur la fonction potentiel
	int i;
	int j = (*modele).systeme.nombre;

	for(i=0;i<j;i++)
		{
		(*modele).systeme.potentiel.reel[i]=(*modele).systeme.actuel.reel[i];
		(*modele).systeme.potentiel.imag[i]=(*modele).systeme.actuel.imag[i];
		}

	return 0;
	}


/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/

int modeleChangeInitiale(modeleT * modele, int fonction, int parametre, int variation, int pourMille) {

	// Change un paramètre de initiale et projette sur le système

		//fprintf(stderr, " modeleChangeInitiale, %d, %d, %d, %d \n", fonction, parametre, variation, pourMille);
	if(variation == 0)
		{		// Réglage du parametre
		initialeRegleParametre(&(*modele).initiale, fonction, parametre, pourMille);
		}
	else
		{		// Changement du parametre
		initialeChangeParametre(&(*modele).initiale, fonction, parametre, variation);
		}

		// Calcul de la fonction initiale
	initialeCalculInitiale(&(*modele).initiale);

		// Projection sur le système
	modeleProjectionInitiale(modele);

		// Indique le changement
	(*modele).change = 1;

	return 0;
}


/*----------------JAUGE ET NORMALISATION-------------------*/

int modeleJaugeZero(modeleT * modele) {
	(void)modele;
	return 0;
	}

//////////////////////////////////////////////////////////////////////////
