/*
Copyright juin 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
Ce logiciel est un programme informatique servant à donner une représentation
graphique de la transformation de Fourier à 1 dimension et d'observer l'effet
d'un filtrage.
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

#include "filtrage.h"

int filtrageProjectionFouFct(filtrageT * filtrage);

int filtrageChangeAmplification(filtrageT * filtrage, int variation, int pourMille);

/*----------------  INITIALISATION  -------------------*/

int filtrageInitialisation(filtrageT * filtrage, int nombre)
	{
	filtreInitialise(&(*filtrage).passeBas, nombre);
	(*filtrage).passeBas.type = 1;
	filtreInitialise(&(*filtrage).passeHaut, nombre);
	(*filtrage).passeHaut.type = 2;
	filtreInitialise(&(*filtrage).passeBande, nombre);
	(*filtrage).passeBande.type = 3;

	filtrePasseBas(&(*filtrage).passeBas);
	filtrePasseHaut(&(*filtrage).passeHaut);
	filtrePasseBande(&(*filtrage).passeBande);

	int i;
	for(i=0;i<NOMBRE_MAX;i++)
		{
		(*filtrage).filtre[i]=1.0;
		}

	(*filtrage).amplification = 1.0;

	fonctionInitialise(&(*filtrage).fou, nombre);
	fourierInitialise(&(*filtrage).fct, nombre);

	return 0;
	}

int filtrageCalcule(filtrageT * filtrage)
	{
			// Projection fou -> fct et calcul de la TF

		//fprintf(stderr, "Projection de fou sur fct\n");
	filtrageProjectionFouFct(filtrage);

		//fprintf(stderr, "Calcul de la TF et normalisation\n");
	fourierCalcule(&(*filtrage).fct);
	fonctionNormaliseNombre(&(*filtrage).fct.spectre);

	return 0;
	}

int filtrageCalculeFiltre(filtrageT * filtrage)
	{
			// Calcul du filtre
	int i;
	int nombre = (*filtrage).fou.nombre;

	for(i=0;i<nombre;i++)
		{
		(*filtrage).filtre[i] = (*filtrage).amplification * (*filtrage).passeBas.gain[i]
		 * (*filtrage).passeHaut.gain[i] * (*filtrage).passeBande.gain[i];
		}

	return 0;
	}

int filtrageProjectionFouFct(filtrageT * filtrage)
	{
				//	Projection de fou sur fct
	int i;
	int nombre = (*filtrage).fou.nombre;

	for(i=0;i<nombre;i++)
		{
		(*filtrage).fct.spectre.reel[i] = (*filtrage).fou.reel[i];
		(*filtrage).fct.spectre.imag[i] = (*filtrage).fou.imag[i];
		}

	return 0;
	}


		/*************       CHANGEMENT D'UN PARAMÈTRE        **************/

int filtrageChangeParametre(filtrageT * filtrage, int fonction, int parametre, int variation, int pourMille)
	{
			// 	Change un paramètre du filtrage

	switch (fonction)
		{
		case 0:	//	Amplification du filtrage
			filtrageChangeAmplification(filtrage, variation, pourMille);break;
		case 1:	//	Passe bas
			filtreChangeParametre(&(*filtrage).passeBas, parametre, variation, pourMille);
			filtrePasseBas(&(*filtrage).passeBas);break;
		case 2:	//	Passe haut
			filtreChangeParametre(&(*filtrage).passeHaut, parametre, variation, pourMille);
			filtrePasseHaut(&(*filtrage).passeHaut);break;
		case 3:	//	Passe bande
			filtreChangeParametre(&(*filtrage).passeBande, parametre, variation, pourMille);
			filtrePasseBande(&(*filtrage).passeBande);break;
		default:
			printf("ERREUR filtrageChangeParametre fonction = %d\n", fonction);
		}

	filtrageCalculeFiltre(filtrage);

	return 0;
	}

int filtrageChangeAmplification(filtrageT * filtrage, int variation, int pourMille)
	{
	float amplification;

	if(variation==0)
		{
		//filtragePourMilleAmplification(filtrage, pourMille);
		amplification = AMPLIFICATION_MIN + (float)(AMPLIFICATION_MAX-AMPLIFICATION_MIN)*pourMille/1000.0;
		}
	else
		{
		//filtrageVariationAmplification(filtrage, variation);
		amplification = (*filtrage).amplification + variation;
		}

	if(amplification>AMPLIFICATION_MAX)
		{
		(*filtrage).amplification = AMPLIFICATION_MAX;
		printf("Amplification maximale atteinte, amplification = %6.3f\n", (*filtrage).amplification);
		}
	else
		{
		if(amplification<AMPLIFICATION_MIN)
			{
			(*filtrage).amplification = AMPLIFICATION_MIN;
			printf("Amplification minimale atteinte, amplification = %6.3f\n", (*filtrage).amplification);
			}
		else
			{
			(*filtrage).amplification = amplification;
			printf("Amplification = %6.3f\n", (*filtrage).amplification);
			}
		}
	return 0;
	}

int filtrageAffiche(filtrageT * filtrage)
	{
			// 	Affiche les paramètres du filtrage

	(void)filtrage;

	//printf("(*filtrage). = %6.3f\n", (*filtrage).);

	//printf("(*filtrage). = %d", (*filtrage).);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////
