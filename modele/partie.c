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
int partieCalculPartie(partieT * partie, double amplitude);
int partieCalculHarmonique(partieT * partie, double amplitude);
int partieCalculUniforme(partieT * partie, double amplitude);
int partieCalculGaussienne(partieT * partie, double amplitude);
int partieCalculLorentzienne(partieT * partie, double amplitude);
int partieCalculSinusCardinal(partieT * partie, double amplitude);
int partieCalculPeigne(partieT * partie, double amplitude);

	//		CHANGEMENT DES PARAMÈTRES
//int partieVariationNature(partieT * partie, int plusMoins); // complexe / périodique
int partieVariationEta(partieT * partie, int plusMoins);
int partieVariationRho(partieT * partie, int plusMoins);
int partieVariationKhi(partieT * partie, int plusMoins);
int partieRegleNature(partieT * partie, int etat); // complexe / périodique
int partieRegleEta(partieT * partie, int pourMille);
int partieRegleRho(partieT * partie, int pourMille);
int partieRegleKhi(partieT * partie, int pourMille);
//int partieVariationPhase(partieT * partie, int forme);

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
/*--------------------  CALCUL DES PARAMETRES INITIALES  ---------------------*/
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


int partieCalculPeriode(partieT * partie) {

	// Calcul de la période
		//printf("partieCalculPeriode = %i\n", (*partie).periode);

	(*partie).periode = exp2((*partie).eta) + (*partie).rho;			//	Période

	if((*partie).complexe == -1)
		{
	printf("partieCalculPeriode : (*enveloppe).periode = %i\n", (*partie).periode);
		}
	else
		{
	printf("partieCalculPeriode : (*porteuse).periode = %i\n", (*partie).periode);
		}

	return (*partie).periode;
}

int partieCalculPartie(partieT * partie, double amplitude) {

				// Calcul de l'enveloppe

				
		//	periodique : 0 enveloppe non-périodique, 1 enveloppe périodique,
					//	2 gaussienne, 3 lorentzienne, 4 sinus cardinal

	if((*partie).complexe < 0)	//	Cas de l'enveloppe
		{
		switch ((*partie).periodique)
			{
			case 0:	//	constante
				partieCalculUniforme(partie, amplitude);break;
			case 1:	//	harmonique
				partieCalculHarmonique(partie, amplitude);break;
			case 2:	//	gaussienne
				partieCalculGaussienne(partie, amplitude);break;
			case 3:	//	lorentzienne
				partieCalculLorentzienne(partie, amplitude);break;
			case 4:	//	sinus cardinal
				partieCalculSinusCardinal(partie, amplitude);break;
			default:
				partieCalculUniforme(partie, amplitude);
			}
		}

						// 0 porteuse réelle, 1 porteuse complexe, 2 peigne de Dirac, 3 constante/
	if((*partie).periodique < 0)	//	Cas de la porteuse
		{
		switch ((*partie).complexe)
			{
			case 3:	//	constante
				partieCalculUniforme(partie, amplitude);break;
			case 0:	//	harmonique
				partieCalculHarmonique(partie, amplitude);break;
			case 1:	//	harmonique
				partieCalculHarmonique(partie, amplitude);break;
			case 2:	//	peigne de Dirac
				partieCalculPeigne(partie, amplitude);break;
			default:
				partieCalculUniforme(partie, amplitude);
			}
		}

	return 0;
}

/*--------------------  CALCUL DES PARTIES INITIALES  ---------------------*/

int partieCalculUniforme(partieT * partie, double amplitude) {

					// Création d'une fonction uniforme
	int i;
	int nombre=(*partie).fonction.nombre;

	if((*partie).periodique < 0)	// Cas de la porteuse
	{
		for(i=0;i<nombre;i++)
			{
			(*partie).fonction.reel[i] = 1.0;
			(*partie).fonction.imag[i] = 1.0;
			}
	}

	if((*partie).complexe < 0)	// Cas de l'enveloppe
	{
		for(i=0;i<nombre;i++)
			{
			(*partie).fonction.reel[i] = amplitude;
			(*partie).fonction.imag[i] = 0.0;
			}
	}
	return 0;
}

int partieCalculHarmonique(partieT * partie, double amplitude) {

	// Création d'une fonction harmonique
	int i;
	int periode=(*partie).periode/DEUXPI;
	int khi=(*partie).khi;
	int nombre=(*partie).fonction.nombre;
		//fprintf(stderr, " Projection sur le système\n");

	if(periode==0)
		{
		fprintf(stderr, "ERREUR partieCalculHarmonique periode=0 !!! \n");
		periode=nombre/10;
		}
	else
		{
		if((*partie).periodique < 0)	// Cas de la porteuse
			{
			for(i=0;i<nombre;i++)
				{
				(*partie).fonction.reel[i] = cos( ((double)i) / periode + khi );
				}
			if((*partie).complexe == 1)
				{
				(*partie).fonction.imag[i] = sin( ((double)i) / periode + khi );
				}
			else
				{
				(*partie).fonction.imag[i] = 0.0;
				}
			}
		else	// Cas de l'enveloppe
			{
			for(i=0;i<nombre;i++)
				{
				(*partie).fonction.reel[i] = amplitude * cos( ((double)i) / periode + khi );
				(*partie).fonction.imag[i] = 0.0;
				}
			}
		}
	return 0;
}

int partieCalculGaussienne(partieT * partie, double amplitude) {

	printf("Enveloppe gaussienne \n");

	int khi = (*partie).khi;		//	Décalage horizontal
	int sigma = (*partie).periode;	//	Largeur à mi hauteur
	int i;
	double argument;

	if( sigma == 0 )
		{
		fprintf(stderr, "ERREUR partieCalculGaussienne, sigma = 0 \n");
		sigma = 1;
		}

	double amgis = (double)1/sigma;

	for(i=0;i<(*partie).fonction.nombre;i++)
		{
		argument = amgis * (i-khi);
		(*partie).fonction.reel[i] = amplitude * amgis * exp(-argument*argument);
		}

	return 0;
}

int partieCalculLorentzienne(partieT * partie, double amplitude) {

	printf("Enveloppe lorentzienne \n");
	
	int khi = (*partie).khi;		//	Décalage horizontal
	int gamma = (*partie).periode;	//	Largeur à mi hauteur
	int i;
	double argument;

	if( gamma == 0 )
		{
		fprintf(stderr, "ERREUR partieCalculLorentzienne, gamma = 0 \n");
		gamma = 1;
		}

	double ammag = (double)1/gamma;

	for(i=0;i<(*partie).fonction.nombre;i++)
		{
		argument = ammag * (i-khi);
		(*partie).fonction.reel[i] = amplitude * ammag /(1 + argument*argument);
		}

	return 0;
}

int partieCalculSinusCardinal(partieT * partie, double amplitude) {

	printf("Enveloppe sinus cardinal \n");
	
	int khi = (*partie).khi;		//	Décalage horizontal
	int largeur = (*partie).periode;	//	Largeur à mi hauteur
	int i;
	double argument;

	if( largeur == 0 )
		{
		fprintf(stderr, "ERREUR partieCalculSinusCardinal, largeur = 0 \n");
		largeur = 1;
		}

	double ammag = (double)1/largeur;

	for(i=0;i<(*partie).fonction.nombre;i++)
		{
		argument = ammag * (i-khi);
		(*partie).fonction.reel[i] = amplitude * sin(argument)/argument;
		}

	return 0;
}

int partieCalculPeigne(partieT * partie, double amplitude) {

	printf("Enveloppe peigne de dirac \n");
	
	int khi = (*partie).khi;		//	Décalage horizontal
	int periode = (*partie).periode;	//	Largeur à mi hauteur
	int i, j;

	if( periode == 0 )
		{
		fprintf(stderr, "ERREUR partieCalculPeigne, periode = 0 \n");
		periode = 1;
		}

	if (khi<(*partie).fonction.nombre)
		{
		for(i=0;i<(*partie).fonction.nombre;i++)
			{
			j = (i-khi) % periode;
			if( j == 0)
				{
				(*partie).fonction.reel[i] = amplitude;
				}
			else
				{
				(*partie).fonction.reel[i] = 0;
				}
			}
		}
	else
		{
		fprintf(stderr, "ERREUR partieCalculPeigne, khi>nombre \n");
		}

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/

int partieRegleParametre(partieT * partie, int parametre, int pourMille) {

	// Fait varier un paramètre de la partie
	fprintf(stderr, " partieRegleParametre, %d\n", parametre);

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

int partieVariationParametre(partieT * partie, int parametre, int variation) {

	// Fait varier un paramètre de la partie
	fprintf(stderr, " partieVariationParametre, %d\n", parametre);

	switch (parametre)
		{
	//	case 0:
	//		partieVariationNature(partie, variation);break;
		case 1:
			partieVariationEta(partie, variation);break;
		case 2:
			partieVariationRho(partie, variation);break;
		case 3:
			partieVariationKhi(partie, variation);break;
		default:
			;
		}

	partieCalculParametres(partie);

	return 0;
}

int partieRegleNature(partieT * partie, int etat){

		// Selon porteuse ou enveloppe, regle la nature complexe ou périodique

	//fprintf(stderr, " partieRegleNature, %d\n", etat);
	//		periodique			-1 SI porteuse,
							//	0 enveloppe non-périodique, 1 enveloppe périodique,
							//	2 gaussienne, 3 lorentzienne, 4 sinus cardinal

	if((*partie).complexe < 0) // Cas de l'enveloppe
		{
		if(etat > -1 && etat < 5)
			{
			(*partie).periodique = etat;
			}
		}

	if((*partie).periodique < 0) // Cas de la porteuse
		{
		if(etat > -1 && etat < 4)
			{
			(*partie).complexe = etat;
			}
		}

	return 0;
	}
/*
int partieVariationNature(partieT * partie, int plusMoins){
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
int partieVariationEta(partieT * partie, int delta) {

			//	Fait varier eta de la partie

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
		printf("eta minimum atteint, etaMin = %d ,", (*partie).etaMin);
		}
	else
		{
		if(eta < log2((*partie).fonction.nombre))
			{
			(*partie).eta = eta;
			}
		else
			{
			(*partie).eta = (*partie).etaMax;
			printf("eta maximum atteint. ");
			}
		}
	printf("eta  = %i\n", (*partie).eta);//%s, (*partie).nom

	return 0;
	}

int partieVariationRho(partieT * partie, int delta) {
	// -1 : delta = 0 ; 0 : annule rho ; 1 réglage deltaPeriode
			//	Fait varier la fréquence de la partie
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
	if(rho < (*partie).rhoMax && rho > -1)
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

int partieVariationKhi(partieT * partie, int delta) {

			//	Fait varier le déphasage de la partie

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
	if(khi < (*partie).periode && khi > -1)
		{
		(*partie).khi = khi;
		}
	else
		{
		printf("khi limite atteint. ");
		}
	printf("khi  = %i\n", (*partie).khi);

	return 0;
	}

int partieRegleEta(partieT * partie, int pourMille) {

		//	Regle eta de la parie

	//fprintf(stderr, " partieRegleEta, pourMille = %d\n", pourMille);

	int eta = ( (*partie).etaMax * pourMille) / 1000;

	//fprintf(stderr, " partieRegleEta, eta = %d\n", eta);

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

	printf("Eta  = %i\n", (*partie).eta);

	return 0;
	}

int partieRegleRho(partieT * partie, int pourMille) {

	int rho = (pourMille * (*partie).rhoMax) / 1000;

	if(rho < (*partie).rhoMax && rho > -1)
		{
		(*partie).rho = rho;
		}
	else
		{
		printf("rho limite atteint, ");
		}
	printf("rho  = %i\n", (*partie).rho);//%s, (*partie).nom

	return 0;
	}

int partieRegleKhi(partieT * partie, int pourMille) {
	//
	//	khi = KHI_MAX * pourMille / 1000
	int khi = ( (*partie).fonction.nombre * pourMille ) / 1000;

	if(khi < (*partie).periode && khi > -1)
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
int partieVariationAmplitude(partieT * partie, float facteur) {

			//	Fait varier l'amplitude du signal

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
int partieAffiche(partieT * partie)
	{
	printf("\nParamètres de la partie : \n");
	printf("     eta = %d", (*partie).eta); printf("     etaMax = %d", (*partie).etaMax); printf("     etaMin = %d\n", (*partie).etaMin);
	printf("     rho = %d", (*partie).rho); printf("     rhoMax = %d\n", (*partie).rhoMax);
	printf("     khi = %d", (*partie).khi); printf("     periode = %d", (*partie).periode); printf("     complexe = %d\n", (*partie).complexe);
	return 0;
	}
//////////////////////////////////////////////////////////////////////////
