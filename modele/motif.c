/*
Copyright mars 2024, Stephan Runigo
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
int motifChangeSymetrie(motifT * motif, int delta);

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

		(*motif).A = 5.3;			//	Amplitude
		(*motif).B = 0.0;			//	Décalage verticale
		(*motif).sym = (float)(*motif).a / (float)(*motif).b;	//	facteur de symétrie (a/b)

		(*motif).forme = 3;			//	0 : harmonique, 1 : carrée, 2 : triangle,
								//	3 : gaussienne, 4 : Lorentzienne

		motifCalculParametres(motif, (*motif).a + (*motif).b);
		motifCalculTriangle(motif);
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

	return 0;
}

int motifCalculUniforme(motifT * motif) {

	printf("Enveloppe uniforme");
	
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

	printf("Enveloppe carrée");

	int i;
	int P = (*motif).a +(*motif).b;

	for(i=0;i<(*motif).a;i++)
		{
		(*motif).fonction.reel[i] = (*motif).A;
		(*motif).fonction.imag[i] = (*motif).A;
		}

	for(i=(*motif).a;i<P;i++)
		{
		(*motif).fonction.reel[i] = -(*motif).A;
		(*motif).fonction.imag[i] = -(*motif).A;
		}

	return 0;
}

int motifCalculTriangle(motifT * motif) {

	printf("Enveloppe triangle");
	
	int i;
	int P = (*motif).a +(*motif).b;
	float alpha = 2*(*motif).A/(*motif).a;

	for(i=0;i<(*motif).a;i++)
		{
		(*motif).fonction.reel[i] = i*alpha - (*motif).A;
		(*motif).fonction.imag[i] = (*motif).fonction.reel[i];
		}

	alpha = 2 * (*motif).A * (float)(*motif).a / (*motif).b;
	float beta = (*motif).A * (1 - 2 * (float)(*motif).a / (*motif).b) ;

	for(i=(*motif).a;i<P;i++)
		{
		(*motif).fonction.reel[i] = i*alpha - beta;
		(*motif).fonction.imag[i] = (*motif).fonction.reel[i];
		}

	return 0;
}

int motifCalculGaussienne(motifT * motif) {

	printf("Enveloppe gaussienne");
	
	int i;

	for(i=0;i<NOMBRE_MAX;i++)
		{
		(*motif).fonction.reel[i] = (*motif).A;
		(*motif).fonction.imag[i] = (*motif).A;
		}

	return 0;
}

int motifCalculLorentzienne(motifT * motif) {

	printf("Enveloppe lorentzienne");
	
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
		{
		(*motif).forme = forme;			//	0 : constante, 1 : harmonique, 2 : carrée, 3 : triangle,
							//	4 : gaussienne, 5 : lorentzienne
		}
	else
		{
		printf("Erreur dans motifChangeForme ");
		}

	printf("Forme  = %i\n", (*motif).forme);

	return 0;
}

int motifChangeSymetrie(motifT * motif, int delta) {

	// Change l'amplitude du motif

	float amplitude = ((*motif).A * delta)/100;

	if(amplitude < AMPLITUDE_MIN)
		{
		(*motif).A = AMPLITUDE_MIN;
		printf("Amplitude minimale atteinte. ");
		}
	else
		{
		if(amplitude > AMPLITUDE_MAX)
			{
			(*motif).A = AMPLITUDE_MAX;
			printf("Amplitude maximale atteinte. ");
			}
		else
			{
			(*motif).A = amplitude;
			}
		}
	printf("Amplitude motif = %f\n", (*motif).A);

	return 0;
	}

int motifChangeA(motifT * motif, int delta) {

	// Change l'amplitude du motif

	float amplitude = ((*motif).A * delta)/100;

	if(amplitude < AMPLITUDE_MIN)
		{
		(*motif).A = AMPLITUDE_MIN;
		printf("Amplitude minimale atteinte. ");
		}
	else
		{
		if(amplitude > AMPLITUDE_MAX)
			{
			(*motif).A = AMPLITUDE_MAX;
			printf("Amplitude maximale atteinte. ");
			}
		else
			{
			(*motif).A = amplitude;
			}
		}
	printf("Amplitude motif = %f\n", (*motif).A);

	return 0;
	}

int motifChangeB(motifT * motif, int delta) {

	// Change le décalage verticale du motif

	float decalage = ((*motif).A * delta)/100;

	if(decalage < AMPLITUDE_MIN)
		{
		(*motif).A = AMPLITUDE_MIN;
		printf("Décalage minimale atteinte. ");
		}
	else
		{
		if(decalage > AMPLITUDE_MAX)
			{
			(*motif).A = AMPLITUDE_MAX;
			printf("Décalage maximale atteinte. ");
			}
		else
			{
			(*motif).A = decalage;
			}
		}
	printf("Décalage verticale = %f\n", (*motif).A);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////
