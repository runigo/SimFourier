/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
(d'après SiCF 2.0  simulateur de corde vibrante et spectre, mars 2019)
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

#include "fonction.h"

double fonctionMaximum(fonctionT * fonction);
double fonctionCarreMax(fonctionT * f);
int fonctionModule(fonctionT * fonction);
int fonctionModuleCarre(fonctionT * fonction);

int fonctionInitialise(fonctionT * f, int nombre)
	{
			//	Initialisation de la fonction
	int i;
		//	Nombre de point
	(*f).nombre = nombre;
		//	x, y et |f| = 0
	for(i=0;i<NOMBRE_MAX;i++)
		{
		(*f).reel[i] = 0;
		(*f).imag[i] = 0;
		(*f).module[i] = 0;
		}
	return 0;
	}

int fonctionRacinesNemesDe1(fonctionT * racineDe1, int n)
	{
			// Calcul des racines nieme de 1
	int i;
	for(i=0;i<n;i++)
		{
		(*racineDe1).reel[i]=cos(2*PI*i/(double)n);
		(*racineDe1).imag[i]=sin(2*PI*i/(double)n);
		}
	return 0;
	}

int fonctionRacinesMoins1(fonctionT * racineDe1, int n)
	{
			// Calcul des racines nieme de -1
	int i;
	for(i=0;i<n;i++)
		{
		(*racineDe1).reel[i]=cos(-2*PI*i/(double)n);
		(*racineDe1).imag[i]=sin(-2*PI*i/(double)n);
		}
	return 0;
	}

int fonctionEgale(fonctionT * f1, fonctionT * f2)
	{
			// projette la fonction f1 sur f2
	int i;
	for(i=0;i<(*f1).nombre;i++)
		{
		(*f2).reel[i] = (*f1).reel[i];
		(*f2).imag[i] = (*f1).imag[i];
		}
	return 0;
	}

int fonctionModule(fonctionT * fonction)
	{
			// Calcul la fonction module
	int i;
	for(i=0;i<(*fonction).nombre;i++)
		{
		(*fonction).module[i]=sqrt((*fonction).reel[i]*(*fonction).reel[i] + (*fonction).imag[i]*(*fonction).imag[i]);
		}
	return 0;
	}

double fonctionModuleMax1(fonctionT * fonction)
	{
			//	Transforme la fonction module afin que
			//		son maximum soit égale à 1
	int i;
	double max=0.0;

		//	Calcul de la fonction module |f(i)|
	fonctionModule(fonction);

		//	Recherche du maximum de |f(i)|
	for(i=0;i<(*fonction).nombre;i++)
		{
		if((*fonction).module[i] > max)
			{
			max=(*fonction).module[i];
			}
		}
		//	Division de |f(i)| par max
	if(max!=0.0)
		{
		for(i=0;i<(*fonction).nombre;i++)
			{
			(*fonction).module[i] = (*fonction).module[i] / max;
			}
		}
	return max;
	}

double fonctionsModuleMax1(fonctionT * f1, fonctionT * f2)
	{
			//	Transforme les fonctions modules afin que
			//		leur maximum soit égale ou inférieur à 1
	int i;
	double max=0.0;

		//	Calcul des fonctions modules |f(i)|
	fonctionModule(f1);
	fonctionModule(f2);

		//	Recherche du maximum de |f1(i)| U |f2(i)|
	for(i=0;i<(*f1).nombre;i++)
		{
		if((*f1).module[i] > max)
			{
			max=(*f1).module[i];
			}
		if((*f2).module[i] > max)
			{
			max=(*f2).module[i];
			}
		}
		//	Division de |f1(i)| et |f2(i)| par max
	if(max!=0.0)
		{
		for(i=0;i<(*f1).nombre;i++)
			{
			(*f1).module[i] = (*f1).module[i] / max;
			(*f2).module[i] = (*f2).module[i] / max;
			}
		}
	return max;
	}

int fonctionModuleDivise(fonctionT * fonction, double max)
	{
			//	Calcul la fonction module et la
			//	divise par max
	int i;

		//	Calcul de la fonction module |f(i)|
	fonctionModule(fonction);

		//	Division de |f(i)| par max
	if(max!=0.0)
		{
		for(i=0;i<(*fonction).nombre;i++)
			{
			(*fonction).module[i] = (*fonction).module[i] / max;
			}
		}
	return 0;
	}

int fonctionModuleCarre(fonctionT * fonction)
	{
			//	Calcul de la fonction |f(i)|^2 et l'enregistre
			//		dans la fonction module !
	int i;

	for(i=0;i<(*fonction).nombre;i++)
		{
		(*fonction).module[i] = (*fonction).reel[i] * (*fonction).reel[i] + (*fonction).imag[i] * (*fonction).imag[i];
		}

	return 0;
	}

int fonctionFiltreCoupe0(fonctionT * fonction)
	{
		//	Filtre l'harmonique correspondant à
		//		la moyenne de la fonction

	(*fonction).reel[0] = 0;
	(*fonction).imag[0] = 0;
	(*fonction).reel[(*fonction).nombre-1] = 0;
	(*fonction).imag[(*fonction).nombre-1] = 0;
	return 0;
	}


/*
int fonctionReplier(fonctionT * spectre, int diviseur)
	{// Effectue un repliement de spectre
	int i;
	fonctionT tmp;

	if (diviseur<1) diviseur = 1;

	for(i=0;i<N/2;i++)
		{
		tmp.reel[2*i] = (*spectre).reel[i];
		tmp.imag[2*i] = (*spectre).imag[i];
		tmp.reel[2*i+1] = (*spectre).reel[N-1-i];
		tmp.imag[2*i+1] = (*spectre).imag[N-1-i];
		}

	for(i=0;i<N;i++)
		{
		(*spectre).reel[i] = tmp.reel[N-1-i]/diviseur;
		(*spectre).imag[i] = tmp.imag[N-1-i]/diviseur;
		}

	return 0;
	}
*/
int fonctionNormalise(fonctionT * f,  double nouveauMax)
	{
	int i;

		//	Calcul du plus grand module de f
	double moduleMax = sqrt(fonctionCarreMax(f));

		//	Divise f par le plus grand module et multiplie par nouveauMax
	for(i=0;i<(*f).nombre;i++)
		{
		(*f).reel[i]=(*f).reel[i] * nouveauMax / moduleMax;
		(*f).imag[i]=(*f).imag[i] * nouveauMax / moduleMax;
		}

	return 0;
	}

double fonctionCarreMax(fonctionT * f)
	{
			//	Retourne le module carré maximum
	int i;
	double x,y;
	double maximum=0.0;
	double moduleCarre;

	for(i=0;i<(*f).nombre;i++)
		{
		x=(*f).reel[i];
		y=(*f).imag[i];
		moduleCarre=x*x+y*y;
		if(moduleCarre > maximum)
			{
			maximum=moduleCarre;
			}
		}
	return maximum;
	}
/*
double fonctionSommeModuleCarre(fonctionT * f)
	{
	int i;
	double somme = 0.0;

	for(i=0;i<N;i++)
		{
		somme += (*f).reel[i] * (*f).reel[i] + (*f).imag[i] * (*f).imag[i];
		}

	return somme;
	}

int fonctionAffiche(fonctionT * f)
  {
	int i;
	printf("fonction complexe\n");
	for(i=0;i<N;i++)
		{
		printf("  re[%d]:%f", i, (*f).reel[i]);
		printf("  im[%d]:%f\n", i, (*f).imag[i]);
		}
	return 0;
	}

int fonctionTest(fonctionT * f)
	{
	fonctionAffiche(f);
	return 0;
	}

*/
////////////////////////////////////////////////////////////////
