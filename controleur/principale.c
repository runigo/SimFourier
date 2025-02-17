/*
Copyright février 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.1 Transformation de Fourier
(d'après SiCP 2.0.1 simulateur de chaîne de pendules, mars 2018)
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
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies. Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "principale.h"

int main(int nb, char *opt[])
	{
	controleurT control;

	fprintf(stderr, "\nDémarrage de SimFourier\n");

	fprintf(stderr, "\nInitialisations des options de la ligne de commande\n");
	assert(donneesOptions(&control.options)==0);

	fprintf(stderr, "Traitement des options de la ligne de commande\n");
	assert(optionsTraitement(&control.options, nb, opt)==0);

	fprintf(stderr, "Initialisations du controleur\n");
	assert(donneesControleur(&control)==0);

	fprintf(stderr, "Démarrage du controleur\n");
	assert(controleurDemarrage(&control)==0);

	//fprintf(stderr, "Calcul énergétique\n");
	//observableAfficheEnergie(&control.systeme);

	fprintf(stderr, "\nSuppression du controleur\n");
	assert(controleurSuppression(&control)==0);

	fprintf(stderr, "\nSortie de SimFourier\n");

	return 0;
	}

//////////////////////////////////////////////////////////////////
