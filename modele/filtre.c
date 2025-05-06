/*
Copyright avril 2025, Stephan Runigo
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

#include "filtre.h"

int filtreInitialise(filtreT * filtre, int nombre)
	{
			//	Initialisation du filtre

		//	Nombre de point
	(*filtre).nombre = nombre;

		//	Fréquence implicite
	(*filtre).frequence = nombre / 4;

		//	Largeur implicite
	(*filtre).largeur = nombre / 16;

		//	mode symétrie implicite
	(*filtre).mode = 1;

	filtreUniforme(filtre);

	return 0;
	}

int filtreUniforme(filtreT * filtre)
	{
			//	Initialise un filtre uniforme
	int i;
	for(i=0;i<NOMBRE_MAX;i++)
		{
		(*filtre).gain[i] = 1.0;
		}
	return 0;
	}

int filtrePasseBas(filtreT * filtre)
	{
			//	Crée un filtre passe bas
	int i;
	int max = (*filtre).nombre - 1;
	int frequence = (*filtre).frequence;
	for(i=0;i<frequence;i++)
		{
		(*filtre).gain[i]=1.0;
		(*filtre).gain[max-i]=1.0;
		}
	return 0;
	}

int filtrePasseHaut(filtreT * filtre)
	{
			//	Crée un filtre passe haut
	int i;
	int frequence = (*filtre).frequence;
	int max = (*filtre).nombre - 1 - frequence;
	for(i=frequence;i<max;i++)
		{
		(*filtre).gain[i]=1.0;
		(*filtre).gain[max-i]=1.0;
		}
	return 0;
	}


int filtrePasseBande(filtreT * filtre)
	{
			//	Crée un filtre passe bande
	int i;
	int frequence = (*filtre).frequence;
	int max = (*filtre).nombre - 1 - frequence;
	for(i=frequence;i<max;i++)
		{
		(*filtre).gain[i]=1.0;
		(*filtre).gain[max-i]=1.0;
		}
	return 0;
	}

		///////////////      CHANGEMENT D'UN PARAMETRE       /////////////////////////////

int filtreChangeParametre(filtreT * filtre, int parametre, int variation, int pourMille)
	{
	(void) filtre;
	(void)parametre;
	(void)variation;
	(void)pourMille;
	return 0;
	}

int filtreAffiche(filtreT * filtre)
	{
	(void) filtre;
	return 0;
	}

int filtreTest(filtreT * filtre)
	{
	filtreAffiche(filtre);
	return 0;
	}

////////////////////////////////////////////////////////////////
