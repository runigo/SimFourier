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

#include "initiale.h"

	//		INITIALISATION
int initialeInitialisationPartie(partieT * partie, int nombre);

	//		CRÉATION DES POSITIONS INITIALES

int initialeCreationPartie(partieT * partie);

int initialeCreationCarre(partieT * partie);
int initialeCreationUniforme(partieT * partie);
int initialeCreationHarmonique(partieT * partie);
/*
int initialeCreationEnveloppe(initialeT * initiale);
int initialeCreationPorteuse(initialeT * initiale);
int initialeCreationPorteuseHarmonique(initialeT * initiale);
int initialeCreationEnveloppeCarre(initialeT * initiale);
int initialeCreationEnveloppeUniforme(initialeT * initiale);
*/
	//		ÉVOLUTION TEMPORELLE
//int initialeIncremente(initialeT * initiale);

	//		JAUGE ET NORMALISATION
int initialeJaugeZero(initialeT * initiale);


/*------------------------  INITIALISATION  -------------------------*/

int initialeInitialisation(initialeT * initiale, int nombre) {

		initialeInitialisationPartie(&(*initiale).enveloppe, nombre);
		initialeInitialisationPartie(&(*initiale).porteuse, nombre);

		(*initiale).enveloppe.complexe = 2;			//	oscillation harmonique
		(*initiale).porteuse.periodique = 2;			//	périodise le motif
	//strcpy( &(*initiale).porteuse.nom, "porteuse" );
	//strcpy( &(*initiale).enveloppe.nom, "enveloppe" );

	return 0;
}

int initialeInitialisationPartie(partieT * partie, int nombre) {

		fonctionInitialise(&(*partie).fonction, nombre);

		(*partie).nombre = nombre;			//	Nombre de points

		(*partie).nombrePeriode=nombre/2;			//	Nombre de période
		(*partie).deltaPeriode = 0;			//	Réglage fin
		(*partie).phase = 1.0;			//	phase
		(*partie).amplitude = 2.0;		//	amplitude
		(*partie).facteur = 0.0;			//	facteur de disymétrie

		(*partie).complexe = 1;			//	oscillation harmonique
		(*partie).periodique = -1;			//	périodise le motif

		(*partie).forme = 0;			//	0 : harmonique, 1 : carrée, 2 : triangle

	return 0;
}

/*--------------------  CRÉATION DES POSITIONS INITIALES  ---------------------*/

int initialeCreationPosition(initialeT * initiale, int forme) {

/*	switch (forme)
		{
		case 0:
			position = 0;break;
		default:
			;
		}
*/
(void)forme;

		//fprintf(stderr, "initialeCreationPosition\n");
	initialeCreationPartie(&(*initiale).enveloppe);
	initialeCreationPartie(&(*initiale).porteuse);

	//initialeCreationCarre(&(*initiale).enveloppe);
	//initialeCreationHarmonique(&(*initiale).porteuse);

	return 0;

}

int initialeCreationPartie(partieT * partie) {
	switch ((*partie).complexe)
		{
		case -1:
			initialeCreationUniforme(partie);break;
		case 0:
			initialeCreationHarmonique(partie);break;
		case 1:
			initialeCreationHarmonique(partie);break;
		default:
			;
		}

	switch ((*partie).periodique)
		{
		case -1:
			initialeCreationUniforme(partie);break;
		case 0:
			initialeCreationUniforme(partie);break;
		case 1:
			initialeCreationCarre(partie);break;
		default:
			;
		}
	// Initialisation de l'enveloppe

//	initialeCreationCarre(partie);
	//partieCreationEnveloppeUniforme(partie);

	return 0;
}

int initialeCreationUniforme(partieT * partie) {

	// Création d'une enveloppe uniforme
	
	int i;
	int nombre=(*partie).nombre;

	for(i=0;i<nombre;i++)
		{
		(*partie).fonction.reel[i] = (*partie).amplitude;
		(*partie).fonction.imag[i] = (*partie).amplitude;
		}

	return 0;
}

int initialeCreationCarre(partieT * partie) {

	// Création d'une enveloppe carrée
	
	int i;
	int nombre=(*partie).nombre;
	float frequence = (float)((*partie).nombrePeriode) * (1.0 + 0.01*(float)((*partie).deltaPeriode))/4;


	for(i=0;i<nombre;i++)
		{
		if(i%(*partie).nombrePeriode > frequence){
			(*partie).fonction.reel[i] = -(*partie).amplitude;
			(*partie).fonction.imag[i] = -(*partie).amplitude;}
		else{
			(*partie).fonction.reel[i] = (*partie).amplitude;
			(*partie).fonction.imag[i] = (*partie).amplitude;}
		}

	return 0;
}

int initialeCreationHarmonique(partieT * partie) {

	// Initialisation de la partie
	
	int i;
	int nombre = (*partie).nombre;
	float amplitude = (*partie).amplitude;
	float frequence = (float)((*partie).nombrePeriode) * (1.0 + 0.01*(float)((*partie).deltaPeriode));
	float phase = (*partie).phase;
/*
		for(i=0;i<nombre;i++)
			{
			if((*partie).complexe == -1)
				{(*partie).fonction.imag[i] = amplitude;(*partie).fonction.reel[i] = amplitude;}
			else {
				(*partie).fonction.reel[i] = amplitude * cos((float)i/nombre*frequence+phase);
				if((*partie).complexe == 1)
					{(*partie).fonction.imag[i] = amplitude * sin((float)i/nombre*frequence+phase);}
				else {(*partie).fonction.imag[i] = 0.0;}
				}
			}
*/
		for(i=0;i<nombre;i++)
			{
			(*partie).fonction.reel[i] = amplitude * cos((float)i/nombre*frequence+phase);
			(*partie).fonction.imag[i] = amplitude * sin((float)i/nombre*frequence+phase);
			}

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/

int initialeChangeNombrePeriode(partieT * partie, int delta) {
(void)delta; // -1 : divise par 2 ; 0 : réglage nombrePeriode ; 1 multiplie par 2
			//	Change la fréquence de la partie
int nombrePeriode = (*partie).nombrePeriode;
	switch (delta)
		{
		case -1:
			nombrePeriode = nombrePeriode / 2;break;
		case 0:
			nombrePeriode = (*partie).nombre/2;break;
		case 1:
			nombrePeriode = nombrePeriode * 2;break;
		default:
			;
		}
	if(nombrePeriode < FREQUENCE_MAX && nombrePeriode > FREQUENCE_MIN)
		{
		(*partie).nombrePeriode = nombrePeriode;
		}
	else
		{
		printf("Fréquence limite atteinte. ");
		}
	printf("Fréquence  = %i\n", (*partie).nombrePeriode);//%s, (*partie).nom

	return 0;
	}

int initialeChangeDeltaPeriode(partieT * partie, int delta) {
(void)delta; // -1 : delta = 0 ; 0 : réglage nombrePeriode ; 1 réglage deltaPeriode
			//	Change la fréquence de la partie
int deltaPeriode = (*partie).deltaPeriode;
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
		(*partie).deltaPeriode = deltaPeriode;
		}
	else
		{
		printf("Fréquence limite atteinte. ");
		}
	printf("Fréquence  = %i\n", (*partie).deltaPeriode);//%s, (*partie).nom

	return 0;
	}

int initialeChangeFrequence(partieT * partie, int delta, float facteur) {
(void)delta; // -1 : delta = 0 ; 0 : réglage nombrePeriode ; 1 réglage deltaPeriode
			//	Change la fréquence de la partie
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
	if((*partie).nombrePeriode * facteur < FREQUENCE_MAX && (*partie).nombrePeriode * facteur > FREQUENCE_MIN)
		{
		(*partie).nombrePeriode = (*partie).nombrePeriode * facteur;
		}
	else
		{
		printf("Fréquence limite atteinte. ");
		}
	printf("Fréquence  = %i\n", (*partie).nombrePeriode);//%s, (*partie).nom

	return 0;
	}

int initialeChangeAmplitude(partieT * partie, float facteur) {

			//	Change l'amplitude du signal

	float amplitude = (*partie).amplitude * facteur;
	if(amplitude < AMPLITUDE_MAX && amplitude > AMPLITUDE_MIN)
		{
		(*partie).amplitude = (*partie).amplitude * facteur;
		}
	else
		{
		printf("Amplitude limite atteinte. ");
		}
	printf("Amplitude générateur = %6.3f\n", (*partie).amplitude);

	return 0;
	}

int initialeChangeComplexe(partieT * partie, int mode){

	switch (mode)
		{
		case -1:
			(*partie).complexe = -1;break;
		case 0:
			(*partie).complexe = 0;break;
		case 1:
			(*partie).complexe = 1;break;
		default:
			;
		}
	printf("(*partie).complexe = %i\n", (*partie).complexe);

	return 0;
	}

int initialeChangePeriodique(partieT * partie, int mode){

	switch (mode)
		{
		case -1:
			(*partie).periodique = -1;break;
		case 0:
			(*partie).periodique = 0;break;
		case 1:
			(*partie).periodique = 1;break;
		default:
			;
		}
	printf("(*partie).periodique = %i\n", (*partie).periodique);

	return 0;
	}


/*------------------------  ÉVOLUTION TEMPORELLE  -------------------------*/

int initialeEvolution(initialeT * initiale, int duree) {
(void)initiale;
(void)duree;

	return 0;
	}

/*----------------JAUGE ET NORMALISATION-------------------*/

//////////////////////////////////////////////////////////////////////////
