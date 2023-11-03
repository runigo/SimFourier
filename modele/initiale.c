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

	//		RÉINITIALISATION

int initialeInitialiseEnveloppe(initialeT * initiale);
int initialeInitialisePorteuse(initialeT * initiale);
int initialeInitialisePorteuseHarmonique(initialeT * initiale);
int initialeInitialiseEnveloppeCarre(initialeT * initiale);

	//		ÉVOLUTION TEMPORELLE
int initialeIncremente(initialeT * initiale);

	//		JAUGE ET NORMALISATION
int initialeJaugeZero(initialeT * initiale);


/*------------------------  INITIALISATION  -------------------------*/

int initialeInitialisation(initialeT * initiale, int nombre) {

		fonctionInitialise(&(*initiale).enveloppe, nombre);
		fonctionInitialise(&(*initiale).porteuse, nombre);
		fonctionInitialise(&(*initiale).potentiel, nombre);

		(*initiale).nombre = nombre;			//	Nombre de points

		(*initiale).periode=(int)nombre/8;			//	periode de l'enveloppe
		(*initiale).frequence = 2000.0;		//	fréquence de la porteuse
		(*initiale).phase = 1.0;			//	phase de la porteuse
		(*initiale).amplitude = 1.0;		//	amplitude de la porteuse
		(*initiale).largeur = 1.0;			//	largeur de l'enveloppe
		(*initiale).facteur = 0.0;			//	facteur de disymétrie

		(*initiale).complexe = 1;			//	oscillation harmonique
		(*initiale).periodique = 1;			//	périodise le carré et le triangle

		(*initiale).forme = 0;			//	0 : harmonique, 1 : carrée, 2 : triangle

	return 0;
}

int initialeInitialisePosition(initialeT * initiale, int forme) {

/*	switch (forme)
		{
		case 0:
			position = 0;break;
		default:
			;
		}
*/
(void)forme;

	initialeInitialisePorteuseHarmonique(initiale);
	initialeInitialiseEnveloppe(initiale);

	return 0;

}

int initialeInitialiseEnveloppe(initialeT * initiale) {

	// Initialisation de l'enveloppe

	initialeInitialiseEnveloppeCarre(initiale);

	return 0;
}

int initialeInitialiseEnveloppeCarre(initialeT * initiale) {

	// Initialisation de l'enveloppe
	
	int i;
	int nombre=(*initiale).nombre;
	float periode=(*initiale).periode/2;


	for(i=0;i<nombre;i++)
		{
		if(i%(*initiale).periode > periode){
			(*initiale).enveloppe.reel[i] = 0;
			(*initiale).enveloppe.imag[i] = 0;}
		else{
			(*initiale).enveloppe.reel[i] = 5;
			(*initiale).enveloppe.imag[i] = 0;}
		}

	return 0;
}
/*
int initialeInitialisePorteuse(initialeT * initiale) {

	else{
		initialeInitialisePorteuseHarmonique(initiale);}

	return 0;
}
*/
int initialeInitialisePorteuseHarmonique(initialeT * initiale) {

	// Initialisation de la porteuse
	
	int i;
	int nombre=(*initiale).nombre;
	float amplitude=(*initiale).amplitude;
	float frequence=(*initiale).frequence;
	float phase=(*initiale).phase;

		for(i=0;i<nombre;i++)
			{
			if((*initiale).complexe == -1)
				{(*initiale).porteuse.imag[i] = amplitude;(*initiale).porteuse.reel[i] = amplitude;}
			else {
				(*initiale).porteuse.reel[i] = amplitude * cos((float)i/nombre*frequence+phase);
				if((*initiale).complexe == 1)
					{(*initiale).porteuse.imag[i] = amplitude * sin((float)i/nombre*frequence+phase);}
				else {(*initiale).porteuse.imag[i] = 0.0;}
				}
			}

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/

int initialeChangeFrequence(initialeT * initiale, float facteur) {

			//	Change la fréquence de la porteuse

	if((*initiale).frequence * facteur < FREQUENCE_MAX && (*initiale).frequence * facteur > FREQUENCE_MIN)
		{
		(*initiale).frequence = (*initiale).frequence * facteur;
		}
	else
		{
		printf("Fréquence limite atteinte. ");
		}
	printf("Fréquence porteuse = %6.3f\n", (*initiale).frequence);

	return 0;
	}

int initialeChangeAmplitude(initialeT * initiale, float facteur) {

			//	Change l'amplitude du signal

	float amplitude = (*initiale).amplitude * facteur;
	if(amplitude < AMPLITUDE_MAX && amplitude > AMPLITUDE_MIN)
		{
		(*initiale).amplitude = (*initiale).amplitude * facteur;
		}
	else
		{
		printf("Amplitude limite atteinte. ");
		}
	printf("Amplitude générateur = %6.3f\n", (*initiale).amplitude);

	return 0;
	}

int initialeChangePorteuse(initialeT * initiale, int mode){

	switch (mode)
		{
		case -1:
			(*initiale).complexe = -1;break;
		case 0:
			(*initiale).complexe = 0;break;
		case 1:
			(*initiale).complexe = 1;break;
		default:
			;
		}
	printf("(*initiale).complexe = %i\n", (*initiale).complexe);

	return 0;
	}

int initialeChangeEnveloppe(initialeT * initiale, int mode){

	switch (mode)
		{
		case -1:
			(*initiale).periodique = -1;break;
		case 0:
			(*initiale).periodique = 0;break;
		case 1:
			(*initiale).periodique = 1;break;
		default:
			;
		}
	printf("(*initiale).periodique = %i\n", (*initiale).periodique);

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
