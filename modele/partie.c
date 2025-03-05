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

#include "partie.h"

	//		INITIALISATION
int partieInitialisationPartie(partieT * partie, int nombre);

	//		CALCUL DE LA PARTIE


int partieCalculPartie(partieT * partie);
int partieCalculHarmonique(partieT * partie);
int partieCalculUniforme(partieT * partie);
int partieCalculCarre(partieT * partie);

	//		CHANGEMENT DES PARAMÈTRES
//int partieChangeNature(partieT * partie, int plusMoins); // complexe / périodique
int partieChangeEta(partieT * partie, int plusMoins);
int partieChangeRho(partieT * partie, int plusMoins);
int partieChangeKhi(partieT * partie, int plusMoins);
int partieRegleNature(partieT * partie, int etat); // complexe / périodique
int partieRegleEta(partieT * partie, int pourMille);
int partieRegleRho(partieT * partie, int pourMille);
int partieRegleKhi(partieT * partie, int pourMille);
//int partieChangePhase(partieT * partie, int forme);

	//		JAUGE ET NORMALISATION
int partieJaugeZero(partieT * partie);


/*------------------------  INITIALISATION  -------------------------*/

int partieInitialisation(partieT * partie, int nombre) {

	fonctionInitialise(&(*partie).fonction, nombre);

	(*partie).eta = log2((*partie).fonction.nombre) / 2;	//	Période1, réglage implicite
	(*partie).etaMax = log2((*partie).fonction.nombre);		//	Maximum de eta

	if(log2(nombre)>3)
		{ (*partie).etaMin = 3; }		//	Minimum de eta
	else
		{ (*partie).etaMin = 1; }

	(*partie).rho = exp2((*partie).eta)/2;			//	Période2, réglage implicite
	(*partie).rhoMax = exp2((*partie).eta);		//	Maximum de rho
	(*partie).khi = 1.0;		//	Décalage horizontale, phase à l'origine
	(*partie).periode = exp2((*partie).eta) + (*partie).rho;			//	Période

	(*partie).complexe = -1;			//	caractéristique de l'enveloppe
	(*partie).periodique = -1;			//	caractéristique de la porteuse

	return 0;
}

/*--------------------  CALCUL DE LA PARTIE  ---------------------*/
int partieCalculParametres(partieT * partie)
	{
			//	Calcul des paramètres de la partie

	(*partie).rhoMax = exp2((*partie).eta);		//	Maximum de rho

	if((*partie).rhoMax < 1)
		{
		(*partie).rho = 0 ;
		}
	else
		{
		while((*partie).rho > (*partie).rhoMax)
			{
			(*partie).rho = (*partie).rho / 2 ;
			}
		}

	partieCalculPeriode(partie);

	return 0;
	}
/*--------------------  CALCUL DES PARAMETRES INITIALES  ---------------------*/

int partieCalculPeriode(partieT * partie) {

	// Calcul de la période
		//printf("partieCalculPeriode = %i\n", (*partie).periode);

	(*partie).periode = exp2((*partie).eta) + (*partie).rho;			//	Période

	printf("partieCalculPeriode : (*partie).periode = %i\n", (*partie).periode);

	return (*partie).periode;
}

int partieCalculUniforme(partieT * partie) {

	// Création d'une fonction uniforme
	
	int i;
	int nombre=(*partie).fonction.nombre;

	for(i=0;i<nombre;i++)
		{
		(*partie).fonction.reel[i] = 1.0;
		(*partie).fonction.imag[i] = 1.0;
		}

	return 0;
}

int partieCalculHarmonique(partieT * partie) {

	// Création d'une fonction harmonique
	
	int i;
	int periode=(*partie).periode;
	int K=(*partie).khi;
	int nombre=(*partie).fonction.nombre;
		//fprintf(stderr, " Projection sur le système\n");

	if((*partie).periode==0)
		{
		fprintf(stderr, " periode=0 !!! \n");
		periode=nombre/10;
		}
	//else
		{
		for(i=0;i<nombre;i++)
			{
			(*partie).fonction.reel[i] = cos( ((float)i)/periode + K );
			(*partie).fonction.imag[i] = sin( ((float)i)/periode + K );
			}
		}

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/

int partieRegleParametre(partieT * partie, int parametre, int pourMille) {

	// Change un paramètre de la partie

	switch (parametre)
		{
		case 0:
			partieRegleNature(partie, pourMille);break;
		case 1:
			partieRegleEta(partie, pourMille);break;
		case 2:
			partieRegleRho(partie, pourMille);break;
		case 3:
			partieRegleKhi(partie, pourMille);break;
		default:
			;
		}

	partieCalculParametres(partie);

	return 0;
}

int partieChangeParametre(partieT * partie, int parametre, int variation) {

	// Change un paramètre de la partie

	switch (parametre)
		{
	//	case 0:
	//		partieChangeNature(partie, variation);break;
		case 1:
			partieChangeEta(partie, variation);break;
		case 2:
			partieChangeRho(partie, variation);break;
		case 3:
			partieChangeKhi(partie, variation);break;
		default:
			;
		}

	partieCalculParametres(partie);

	return 0;
}

int partieRegleNature(partieT * partie, int etat){

		// Selon porteuse ou enveloppe, regle la nature complexe ou périodique

	//fprintf(stderr, " partieRegleNature, %d\n", etat);

	if((*partie).complexe < 0) // Cas de l'enveloppe
		{
		if(etat==0 || etat==1)
			{
			(*partie).periodique = etat;
			printf("enveloppe periodique = %i\n", (*partie).periodique);
			}
		}

	if((*partie).periodique < 0) // Cas de la porteuse
		{
		if(etat==0 || etat==1 || etat==2 || etat==3)
			{
			(*partie).complexe = etat;
			printf("porteuse complexe = %i\n", (*partie).complexe);
			}
		}

	return 0;
	}
/*
int partieChangeNature(partieT * partie, int plusMoins){
(void) plusMoins;
		// Selon porteuse ou enveloppe, change complexe ou périodique
		printf("plusMoins = %i\n", plusMoins);

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
*/
int partieChangeEta(partieT * partie, int delta) {
// delta = -1 : divise par 2 ; 0 : réglage nombrePeriode ; 1 multiplie par 2
			//	Change la fréquence de la partie
int eta = (*partie).eta;
	switch (delta)
		{
		case -1:
			eta = eta -1;break;
		case 0:
			eta = 2;break;
		case 1:
			eta = eta +1;break;
		default:
			;
		}
	if(eta < (*partie).etaMin)
		{
		(*partie).eta = (*partie).etaMin;
		printf("eta minimum atteint.\n");
		}
	if(eta < log2((*partie).fonction.nombre))
		{
		(*partie).eta = eta;
		}
	else
		{
		(*partie).eta = (*partie).etaMax;
		printf("eta maximum atteint. ");
		}
	printf("Eta  = %i\n", (*partie).eta);//%s, (*partie).nom

	return 0;
	}

int partieChangeRho(partieT * partie, int delta) {
	// -1 : delta = 0 ; 0 : annule rho ; 1 réglage deltaPeriode
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
	if(rho < 10 && rho > -1)
		{
		(*partie).rho = rho;
		}
	else
		{
		printf("rho limite atteint. ");
		}
	printf("rho  = %i\n", (*partie).rho);//%s, (*partie).nom

	return 0;
	}

int partieChangeKhi(partieT * partie, int delta) {
 // -1 : delta = 0 ; 0 : annule rho ; 1 réglage deltaPeriode
			//	Change la fréquence de la partie

	int khi = (*partie).khi;
	switch (delta)
		{
		case -1:
			khi = khi - 1;break;
		case 0:
			khi = 0;break;
		case 1:
			khi = khi + 1;break;
		default:
			;
		}
	if(khi < (*partie).fonction.nombre && khi > -1)
		{
		(*partie).khi = khi;
		}
	else
		{
		printf("khi limite atteint. ");
		}
	printf("khi  = %i\n", (*partie).khi);//%s, (*partie).nom

	return 0;
	}

int partieRegleEta(partieT * partie, int pourMille) {

	fprintf(stderr, " partieRegleEta, pourMille = %d\n", pourMille);

	int eta = ( (*partie).etaMax * pourMille) / 1000;

	fprintf(stderr, " partieRegleEta, eta = %d\n", eta);

	if( eta > (*partie).etaMin )
		{
		if( eta < (*partie).etaMax )
			{
			(*partie).eta = eta;
			}
		else
			{
			(*partie).eta = (*partie).etaMax;
			printf("eta maximum atteint. ");
			}
		}
	else
		{
		(*partie).eta = (*partie).etaMin;
		printf("eta minimum atteint. ");
		}

	printf("Eta  = %i\n", (*partie).eta);//%s, (*partie).nom

	return 0;
	}

int partieRegleRho(partieT * partie, int pourMille) {

	int rho = pourMille / 10;

	if(rho < 100 && rho > -1)
		{
		(*partie).rho = rho;
		}
	else
		{
		printf("rho limite atteint. ");
		}
	printf("rho  = %i\n", (*partie).rho);//%s, (*partie).nom

	return 0;
	}

int partieRegleKhi(partieT * partie, int pourMille) {
	//
	//	khi = KHI_MAX * pourMille / 1000
	int khi = ( (*partie).fonction.nombre * pourMille ) / 1000;

	if(khi < (*partie).fonction.nombre && khi > -1)
		{
		(*partie).khi = khi;
		}
	else
		{
		printf("khi limite atteint. ");
		}
	printf("khi  = %i\n", (*partie).khi);//%s, (*partie).nom

	return 0;
	}
/*
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
//////////////////////////////////////////////////////////////////////////
