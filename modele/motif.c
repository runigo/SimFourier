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

#include "motif.h"

	//		INITIALISATION
int motifInitialisationPartie(motifT * motif, int nombre);

	//		CRÉATION DES POSITIONS INITIALES

int motifCreationPartie(motifT * motif);

int motifCreationCarre(motifT * motif);
int motifCreationUniforme(motifT * motif);
int motifCreationHarmonique(motifT * motif);
/*
int motifCreationEnveloppe(motifT * motif);
int motifCreationPorteuse(motifT * motif);
int motifCreationPorteuseHarmonique(motifT * motif);
int motifCreationEnveloppeCarre(motifT * motif);
int motifCreationEnveloppeUniforme(motifT * motif);
*/
	//		ÉVOLUTION TEMPORELLE
//int motifIncremente(motifT * motif);

	//		JAUGE ET NORMALISATION
int motifJaugeZero(motifT * motif);


/*------------------------  INITIALISATION  -------------------------*/

int motifInitialisation(motifT * motif, int nombre) {

		fonctionInitialise(&(*motif).fonction, nombre);	// Fonction motif

		(*motif).nombre = nombre;			//	Nombre de points

		(*motif).d=0;			//	décalage horizontal à l'origine
		(*motif).eta = 3;			//	puissance de deux
		(*motif).rho = 1;			//	dP

		(*motif).A = 3;			//	Amplitude
		(*motif).facteur = 0.7;	//	facteur de symétrie (a/b)

		(*motif).forme = 2;			//	0 : harmonique, 1 : carrée, 2 : triangle,
								//	3 : gaussienne, 4 : Lorentzienne

		motifCalculPosition(motif);

		int a;		//	Longueur horizontale (montée ou positif)
		int b;		//	Longueur horizontale (descente ou négatif)
		int P;		//	Période ( = a + b = 2^eta + rho )

	return 0;
}

/*--------------------  CRÉATION DES POSITIONS INITIALES  ---------------------*/

int motifCalculPosition(motifT * motif) {
	int i

	(*motif).P=1;
	for (i=0;i<(*motif).eta;i++)
		{(*motif).P=2*(*motif).P;}
	(*motif).P=(*motif).P+(*motif).rho;

	(*motif).a=(*motif).P*(*motif).facteur;
	if((*motif).facteur=!0)
		{(*motif).b=(*motif).P/(*motif).facteur;}
	else{(*motif).b=(*motif).P;}

//	0 : harmonique, 1 : carrée, 2 : triangle, 3 : gaussienne, 4 : Lorentzienne
	switch ((*motif).forme)
		{
		case 0:
			motifCreationHarmonique(motif);break;
		case 1:
			motifCreationCarree(motif);break;
		case 2:
			motifCreationTriangle(motif);break;
		case 3:
			motifCreationGaussienne(motif);break;
		case 4:
			motifCreationLorentzienne(motif);break;
		default:
			;
		}

	return 0;
}

int motifCreationUniforme(motifT * motif) {

	// Création d'une enveloppe uniforme
	
	int i;
	int nombre=(*motif).nombre;

	for(i=0;i<nombre;i++)
		{
		(*motif).fonction.reel[i] = (*motif).amplitude;
		(*motif).fonction.imag[i] = (*motif).amplitude;
		}

	return 0;
}

int motifCreationCarre(motifT * motif) {

	// Création d'une enveloppe carrée
	
	int i;
	int nombre=(*motif).nombre;
	float frequence = (float)((*motif).nombrePeriode) * (1.0 + 0.01*(float)((*motif).deltaPeriode))/4;


	for(i=0;i<nombre;i++)
		{
		if(i%(*motif).nombrePeriode > frequence){
			(*motif).fonction.reel[i] = -(*motif).amplitude;
			(*motif).fonction.imag[i] = -(*motif).amplitude;}
		else{
			(*motif).fonction.reel[i] = (*motif).amplitude;
			(*motif).fonction.imag[i] = (*motif).amplitude;}
		}

	return 0;
}

int motifCreationHarmonique(motifT * motif) {

	// Initialisation de la motif
	
	int i;
	int nombre = (*motif).nombre;
	float amplitude = (*motif).amplitude;
	float frequence = (float)((*motif).nombrePeriode) * (1.0 + 0.01*(float)((*motif).deltaPeriode));
	float phase = (*motif).phase;
/*
		for(i=0;i<nombre;i++)
			{
			if((*motif).complexe == -1)
				{(*motif).fonction.imag[i] = amplitude;(*motif).fonction.reel[i] = amplitude;}
			else {
				(*motif).fonction.reel[i] = amplitude * cos((float)i/nombre*frequence+phase);
				if((*motif).complexe == 1)
					{(*motif).fonction.imag[i] = amplitude * sin((float)i/nombre*frequence+phase);}
				else {(*motif).fonction.imag[i] = 0.0;}
				}
			}
*/
		for(i=0;i<nombre;i++)
			{
			(*motif).fonction.reel[i] = amplitude * cos((float)i/nombre*frequence+phase);
			(*motif).fonction.imag[i] = amplitude * sin((float)i/nombre*frequence+phase);
			}

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/

int motifChangeNombrePeriode(motifT * motif, int delta) {
(void)delta; // -1 : divise par 2 ; 0 : réglage nombrePeriode ; 1 multiplie par 2
			//	Change la fréquence de la motif
int nombrePeriode = (*motif).nombrePeriode;
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

	return 0;
	}

int motifChangeDeltaPeriode(motifT * motif, int delta) {
(void)delta; // -1 : delta = 0 ; 0 : réglage nombrePeriode ; 1 réglage deltaPeriode
			//	Change la fréquence de la motif
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

	return 0;
	}

int motifChangeFrequence(motifT * motif, int delta, float facteur) {
(void)delta; // -1 : delta = 0 ; 0 : réglage nombrePeriode ; 1 réglage deltaPeriode
			//	Change la fréquence de la motif
	switch (delta)
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

	return 0;
	}

int motifChangeAmplitude(motifT * motif, float facteur) {

			//	Change l'amplitude du signal

	float amplitude = (*motif).amplitude * facteur;
	if(amplitude < AMPLITUDE_MAX && amplitude > AMPLITUDE_MIN)
		{
		(*motif).amplitude = (*motif).amplitude * facteur;
		}
	else
		{
		printf("Amplitude limite atteinte. ");
		}
	printf("Amplitude générateur = %6.3f\n", (*motif).amplitude);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////
