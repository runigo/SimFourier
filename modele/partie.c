/*
Copyright janvier 2024, Stephan Runigo
runigo@free.fr
SimFourier 1.1 Transformation de Fourier
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

#include "partie.h"

	//		INITIALISATION
int partieInitialisationPartie(partieT * partie, int nombre);

	//		CRÉATION DES POSITIONS partieS

int partieCalculPeriode(partieT * partie);
int partieCreationPartie(partieT * partie);
int partieCreationHarmonique(partieT * partie);
int partieCreationUniforme(partieT * partie);
int partieCreationCarre(partieT * partie);

	//		ÉVOLUTION TEMPORELLE
//int partieIncremente(partieT * partie);

	//		JAUGE ET NORMALISATION
int partieJaugeZero(partieT * partie);


/*------------------------  INITIALISATION  -------------------------*/

int partieInitialisation(partieT * partie, int nombre) {

		fonctionInitialise(&(*partie).fonction, nombre);

		(*partie).eta=nombre/2;		//	Période, réglage puissance de deux
		(*partie).rho = 0;			//	Période, réglage fin
		(*partie).khi = 1.0;		//	Décalage horizontale, phase à l'origine
		(*partie).P = 1.0;			//	Période

		(*partie).complexe = -1;			//	caractéristique de l'enveloppe
		(*partie).periodique = -1;			//	caractéristique de la porteuse

	return 0;
}

/*--------------------  CALCUL DES POSITIONS INITIALES  ---------------------*/

int partieCalculPeriode(partieT * partie) {
	int i;
	(*partie).P=1;
	for (i=0;i<(*partie).eta;i++)
		{
		(*partie).P=2*(*partie).P;
		}
	(*partie).P = (*partie).P + (*partie).rho;
	return (*partie).P;
}
/*int partieCalculPeriode(partieT * partie) {
		// Calcul de la période à partir de eta et rho
	int k=1;
	int P=2;
		//	P = 2^eta
	if( (*partie).eta > 0)
		{ while(k<(*partie).eta) { P=2*P; k++;} }
	else { P = 1; }
		//	P = P + dp
	if( (*partie).rho < P )
		{P=P+(*partie).rho;}
	else {P=(*partie).rho}
		//	P reste inférieur à "nombre"
	if( P < (*partie).fonction.nombre )
		{(*partie).P = P}
	else {(*partie).P = (*partie).fonction.nombre}
	return 0;
}
*/
int partieCreationPosition(partieT * partie) {

/*	switch (forme)
		{
		case 0:
			position = 0;break;
		default:
			;
		}
*/
(void)partie;

		//fprintf(stderr, "partieCreationPosition\n");
	//partieCreationPartie(&(*partie).enveloppe);
	//partieCreationPartie(&(*partie).porteuse);

	return 0;

}

int partieCreationPartie(partieT * partie) {
	switch ((*partie).complexe)
		{
	//	case -1:
		//	partieCreationUniforme(partie);break;
		case 0:
			partieCreationHarmonique(partie);break;
		case 1:
			partieCreationHarmonique(partie);break;
		default:
			;
		}

	switch ((*partie).periodique)
		{
	//	case -1:
		//	partieCreationUniforme(partie);break;
		case 0:
			partieCreationUniforme(partie);break;
		case 1:
			partieCreationCarre(partie);break;
		default:
			;
		}
	// Initialisation de l'enveloppe

//	partieCreationCarre(partie);
	//partieCreationEnveloppeUniforme(partie);

	return 0;
}

int partieCreationUniforme(partieT * partie) {

	// Création d'une enveloppe uniforme
	
	int i;
	int nombre=(*partie).fonction.nombre;

	for(i=0;i<nombre;i++)
		{
		(*partie).fonction.reel[i] = 1.0;
		(*partie).fonction.imag[i] = 1.0;
		}

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/

int partieChangeEta(partieT * partie, int delta) {
// delta = -1 : divise par 2 ; 0 : réglage nombrePeriode ; 1 multiplie par 2

int eta = (*partie).eta;
	switch (delta)
		{
		case -1:
			eta = eta / 2;break;
		case 0:
			eta = (*partie).fonction.nombre/2;break;
		case 1:
			eta = eta * 2;break;
		default:
			;
		}
	if(eta < (*partie).P)
		{
		(*partie).eta = eta;
		}
	else
		{
		printf("Fréquence limite atteinte. ");
		}
	printf("Eta  = %i\n", (*partie).eta);//%s, (*partie).nom

	return 0;
	}

int partieChangeRho(partieT * partie, int delta) {
(void)delta; // -1 : delta = 0 ; 0 : annule rho ; 1 réglage deltaPeriode
			//	Change la fréquence de la partie
int rho = (*partie).rho;
	switch (delta)
		{
		case -1:
			rho = rho - 1;break;
		case 0:
			rho = 0;break;
		case 1:
			rho = rho + 1;break;
		default:
			;
		}
	if(rho < 100 && rho > -1)
		{
		(*partie).rho = rho;
		}
	else
		{
		printf("Fréquence limite atteinte. ");
		}
	printf("rho  = %i\n", (*partie).rho);//%s, (*partie).nom

	return 0;
	}
/*
int partieChangeFrequence(partieT * partie, int delta, float facteur) {
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

int partieChangeAmplitude(partieT * partie, float facteur) {

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
	printf("Amplitude = %6.3f\n", (*partie).amplitude);

	return 0;
	}
*/
int partieChangeNature(partieT * partie){

		// Selon porteuse ou enveloppe, change complexe ou périodique

	if((*partie).complexe < 0) // Cas de l'enveloppe
		{
		if((*partie).periodique==0)
			{
			(*partie).periodique = 1;
			}
		else
			{
			(*partie).periodique = 0;
			}
		printf("enveloppe periodique = %i\n", (*partie).periodique);
		}

	if((*partie).periodique < 0) // Cas de la porteuse
		{
		if((*partie).periodique==0)
			{
			(*partie).complexe = 1;
			}
		else
			{
			(*partie).complexe = 0;
			}
		printf("porteuse complexe = %i\n", (*partie).complexe);
		}

	return 0;
	}

//////////////////////////////////////////////////////////////////////////
