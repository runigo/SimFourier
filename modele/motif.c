/*
Copyright février 2024, Stephan Runigo
runigo@free.fr
SimFourier 1.2 Transformation de Fourier
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

#include "motif.h"

	//		INITIALISATION

	//		CHANGEMENT DES PARAMÈTRES
int motifChangeA(motifT * motif, int delta);
int motifChangeB(motifT * motif, int delta);
int motifChangeForme(motifT * motif, int forme);
int motifChangeSymetrie(motifT * motif, float facteur);
int motifChangeAmplitude(motifT * motif, float facteur);

	//		CALCUL DU MOTIF
int motifCalculParametres(motifT * motif, int P);

int motifCalcul(motifT * motif);
int motifCalculUniforme(motifT * motif);
int motifCalculHarmonique(motifT * motif);
int motifCalculCarre(motifT * motif);
int motifCalculTriangle(motifT * motif);
int motifCalculGaussienne(motifT * motif);
int motifCalculLorentzienne(motifT * motif);

	//		JAUGE ET NORMALISATION
int motifJaugeZero(motifT * motif);


/*------------------------  INITIALISATION  -------------------------*/

int motifInitialisation(motifT * motif, int nombre) {

		fonctionInitialise(&(*motif).fonction, nombre);	// Fonction motif

		(*motif).a=10;			//	Longueur horizontale (montée ou positif)
		(*motif).b=20;			//	Longueur horizontale (descente ou négatif)
		(*motif).C=(*motif).a+(*motif).b;		//	Période ( = a + b = 2^eta + rho )

		(*motif).A = 3;			//	Amplitude
		(*motif).B = 1;			//	Décalage verticale
		(*motif).sym = (float)(*motif).a / (float)(*motif).b;	//	facteur de symétrie (a/b)

		(*motif).forme = 2;			//	0 : harmonique, 1 : carrée, 2 : triangle,
								//	3 : gaussienne, 4 : Lorentzienne

		motifCalculParametres(motif, (*motif).a + (*motif).b);
	//	motifCalculPosition(motif);

	return 0;
}

/*--------------------  CALCUL DU MOTIF  ---------------------*/

int motifCalculMotif(motifT * motif, int P) {

		// Calcul des paramètres
	motifCalculParametres(motif, P);
	// Calcul de la fonction

	switch ((*motif).forme)
		{
		case -1:
			motifCalcul(motif);break;
		case 0:
			motifCalculUniforme(motif);break;
		case 1:
			motifCalculUniforme(motif);break;
		case 2:
			motifCalculCarre(motif);break;
		case 3:
			motifCalculTriangle(motif);break;
		case 4:
			motifCalculGaussienne(motif);break;
		case 5:
			motifCalculLorentzienne(motif);break;
		default:
			;
		}

	return 0;
}

int motifCalculParametres(motifT * motif, int P) {

		// Calcul des paramètres

	(*motif).a=(int)(P*((*motif).sym));
	(*motif).b=P-(*motif).a;
	(*motif).C=P;

	return 0;
}

int motifCalcul(motifT * motif) {

	// Création d'une enveloppe uniforme
	
	int i;
	int nombre=(*motif).a + (*motif).b;

	for(i=0;i<nombre;i++)
		{
		(*motif).fonction.reel[i] = (*motif).A;
		(*motif).fonction.imag[i] = (*motif).A;
		}

	return 0;
}

int motifCalculUniforme(motifT * motif) {

	// Création d'une enveloppe uniforme
	
	int i;
	int nombre=(*motif).a + (*motif).b;

	for(i=0;i<nombre;i++)
		{
		(*motif).fonction.reel[i] = (*motif).A;
		(*motif).fonction.imag[i] = (*motif).A;
		}

	return 0;
}

int motifCalculCarre(motifT * motif) {

	// Création d'une enveloppe carrée
	
	int i;

	for(i=0;i<(*motif).a;i++)
		{
		(*motif).fonction.reel[i] = (*motif).A;
		(*motif).fonction.imag[i] = (*motif).A;
		}

	for(i=(*motif).a;i<(*motif).C;i++)
		{
		(*motif).fonction.reel[i] = -(*motif).A;
		(*motif).fonction.imag[i] = -(*motif).A;
		}

	return 0;
}

int motifCalculTriangle(motifT * motif) {

	// Création d'une enveloppe triangle
	
	int i;
	float alpha = 2*(*motif).A/(*motif).a;

	for(i=0;i<(*motif).a;i++)
		{
		(*motif).fonction.reel[i] = i*alpha - (*motif).A;
		(*motif).fonction.imag[i] = (*motif).fonction.reel[i];
		}

	alpha = 2 * (*motif).A * (float)(*motif).a / (*motif).b;
	float beta = (*motif).A * (1 - 2 * (float)(*motif).a / (*motif).b) ;

	for(i=(*motif).a;i<(*motif).C;i++)
		{
		(*motif).fonction.reel[i] = i*alpha - beta;
		(*motif).fonction.imag[i] = (*motif).fonction.reel[i];
		}

	return 0;
}

int motifCalculGaussienne(motifT * motif) {

	// Création d'une enveloppe gaussienne
	
	int i;

	for(i=0;i<NOMBRE_MAX;i++)
		{
		(*motif).fonction.reel[i] = (*motif).A;
		(*motif).fonction.imag[i] = (*motif).A;
		}

	return 0;
}

int motifCalculLorentzienne(motifT * motif) {

	// Création d'une enveloppe lorentzienne
	
	int i;

	for(i=0;i<NOMBRE_MAX;i++)
		{
		(*motif).fonction.reel[i] = (*motif).A;
		(*motif).fonction.imag[i] = (*motif).A;
		}

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/
int motifChangeParametre(motifT * motif, int parametre, int variation){

	switch (parametre)
		{
		case 0:
			motifChangeForme(motif, variation);break;
		case 1:
			motifChangeSymetrie(motif, variation);break;
		case 2:
			motifChangeA(motif, variation);break;
		case 3:
			motifChangeB(motif, variation);break;
		//case 4:
			//motifChangeC(motif, variation);break;
		default:
			;
		}
	return 0;
}

int motifChangeForme(motifT * motif, int forme){

	if(forme>-1 && forme<6)
		(*motif).forme = forme;			//	0 : constante, 1 : harmonique, 2 : carrée, 3 : triangle,
							//	4 : gaussienne, 5 : lorentzienne
	else printf("Erreur, ");

	printf("Forme  = %i\n", (*motif).forme);//%s, (*motif).nom

	return 0;
}

int motifChangeSymetrie(motifT * motif, float variation) {
(void)motif;
(void)variation;
	/* float symetrie = (*motif).sym * (1 + (float)variation/100.0);

	//if(symetrie 

	switch (delta)
		{
		case -1:
			nombrePeriode = nombrePeriode / 2;break;
		case 0:
			nombrePeriode = (*motif).nombre/2;break;
		case 1:
			nombrePeriode = nombrePeriode * 2;break;
		default:
			;
		}
	if(nombrePeriode < FREQUENCE_MAX && nombrePeriode > FREQUENCE_MIN)
		{
		(*motif).nombrePeriode = nombrePeriode;
		}
	else
		{
		printf("Fréquence limite atteinte. ");
		}
	printf("Fréquence  = %i\n", (*motif).nombrePeriode);//%s, (*motif).nom
*/
	return 0;
	}

int motifChangeA(motifT * motif, int delta) {
(void)delta; // -1 : delta = 0 ; 0 : réglage nombrePeriode ; 1 réglage deltaPeriode
(void)motif;			//	Change la fréquence de la motif
/*
int deltaPeriode = (*motif).deltaPeriode;
	switch (delta)
		{
		case -1:
			deltaPeriode = deltaPeriode - 1;break;
		case 0:
			deltaPeriode = 33;break;
		case 1:
			deltaPeriode = deltaPeriode + 1;break;
		default:
			;
		}
	if(deltaPeriode < 100 && deltaPeriode > -1)
		{
		(*motif).deltaPeriode = deltaPeriode;
		}
	else
		{
		printf("Fréquence limite atteinte. ");
		}
	printf("Fréquence  = %i\n", (*motif).deltaPeriode);//%s, (*motif).nom
*/
	return 0;
	}

int motifChangeB(motifT * motif, int delta) {
(void)delta; // -1 : delta = 0 ; 0 : réglage nombrePeriode ; 1 réglage deltaPeriode
(void)motif;		//	Change la fréquence de la motif
/*	switch (delta)
		{
		case 0:
			;break;
		case -1:
			;break;
		case 1:
			;break;
		default:
			;
		}
	if((*motif).nombrePeriode * facteur < FREQUENCE_MAX && (*motif).nombrePeriode * facteur > FREQUENCE_MIN)
		{
		(*motif).nombrePeriode = (*motif).nombrePeriode * facteur;
		}
	else
		{
		printf("Fréquence limite atteinte. ");
		}
	printf("Fréquence  = %i\n", (*motif).nombrePeriode);//%s, (*motif).nom
*/
	return 0;
	}

int motifChangeAmplitude(motifT * motif, float facteur) {

			//	Change l'amplitude du signal

	float amplitude = (*motif).A * facteur;
	if(amplitude < AMPLITUDE_MAX && amplitude > AMPLITUDE_MIN)
		{
		(*motif).A = amplitude;
		}
	else
		{
		printf("Amplitude limite atteinte. ");
		}
	printf("Amplitude générateur = %6.3f\n", (*motif).A);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////
