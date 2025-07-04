/*
Copyright mai 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
(D'après SiCP 1.3.7  simulateur de chaîne de pendules, septembre 2017)
Ce logiciel est un programme informatique permettant de donner une représentation
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

#include "graphe.h"

int grapheReglageAxes(grapheT * graphe, int axes);
int grapheReglageTrait(grapheT * graphe, int trait);
int grapheReglageCoord(grapheT * graphe, int coord);
int grapheChangeCoord(grapheT * graphe, int coord);
int grapheReglagePdv(grapheT * graphe, int position);

int grapheInitialisation(grapheT * graphe, int nombre)
	{
			//	Initalisation d'un graphe

	int i;
	(*graphe).nombre=nombre;

	(*graphe).axes = 1;		//	Avec ou sans axes
	(*graphe).trait = 1;	//	Points reliés ou non
	(*graphe).coord = 1;	//	Style des coordonnées

	(*graphe).dessous = 0;
	(*graphe).arriere = 0;
	(*graphe).gauche = 0;

	(*graphe).longueur = LONGUEUR_IMP;
	(*graphe).rayon = RAYON_IMP;

	(*graphe).positionX = 0.0;	//	Position dans la fenêtre, reste constant
	(*graphe).positionY = 0.0;	//	Initialisé dans projection

	for(i=0;i<NOMBRE_MAX;i++){
		vecteurInitialisePolaire(&(*graphe).point[i], 0.0, 0.0, 0.0);
		vecteurInitialisePolaire(&(*graphe).axe[i], 0.0, 0.0, 0.0);
		(*graphe).xp[i] = 0;
		(*graphe).yp[i] = 0;
		(*graphe).xa[i] = 0;
		(*graphe).ya[i] = 0;
		}

	for(i=0;i<SUPPORT;i++){
		vecteurInitialisePolaire(&(*graphe).support[i],0.0,0.0,0.0);
		(*graphe).axeX[i] = 0;
		(*graphe).axeY[i] = 0;
		}

	pointDeVueInitialise(&(*graphe).pointDeVue);
	grapheInitialiseSupport(graphe);

	return 0;
	}

int grapheInitialiseSupport(grapheT * graphe){

			//	Réinitialisation des axes 3D
//
//                                                Z
//                                          Y              X'
//                                                O
//                                                      Y'
//                                                Z'
//             X

	int i;
	for(i=0;i<SUPPORT;i++)
		{
		(*graphe).support[i].x = 0;
		(*graphe).support[i].y = 0;
		(*graphe).support[i].z = 0;
		}

					// AXE X'X (y et z = 0)
	(*graphe).support[0].x = -(*graphe).longueur;
	(*graphe).support[1].x = (*graphe).longueur;

					// AXE Y'Y
	(*graphe).support[2].y = -(*graphe).rayon;
	(*graphe).support[3].y = (*graphe).rayon;

					// AXE Z'Z
	(*graphe).support[4].z = -(*graphe).rayon;
	(*graphe).support[5].z = (*graphe).rayon;

		//	Initialisation des abscisses du graphe
	int nombre=(*graphe).nombre;
	if(nombre==0)
		{
		printf("ERREUR, grapheInitialiseSupport, nombre == 0\n");
		exit(0);
		}
	else
		{
		int longueur = (*graphe).longueur * 2;
		for(i=0;i<nombre;i++)
			{
			(*graphe).axe[i].x = (longueur * (float)i/nombre - (*graphe).longueur);
			(*graphe).point[i].x = (*graphe).axe[i].x ;
			}
		}
	return 0;
	}

int graphe3D2D(grapheT * graphe, int fenetreX, int fenetreY)
	{
						//	Projette un graphe 3D sur son graphe 2D
	vecteurT v;
	int i;
	int nombre = (*graphe).nombre;

		// centrage du graphe
	int centrageX = (int)( fenetreX * (*graphe).positionX );
	int centrageY = (int)( fenetreY * (*graphe).positionY );

	for(i=0;i<nombre;i++)
		{
				// Coordonnees 2D du point
			// v = masse - point de vue
		vecteurDifferenceCartesien(&(*graphe).point[i], &(*graphe).pointDeVue.position, &v);
			// x = X + v.Psi		 y = Y + v.Phi
		(*graphe).xp[i] = centrageX + vecteurScalaireCartesien(&v, &(*graphe).pointDeVue.vecteurPsi);
		(*graphe).yp[i] = centrageY + vecteurScalaireCartesien(&v, &(*graphe).pointDeVue.vecteurPhi);

				// Coordonnees 2D de l'axe
			// v = axe - point de vue
		vecteurDifferenceCartesien(&(*graphe).axe[i], &(*graphe).pointDeVue.position, &v);
			// x = X + v.Psi		 y = Y + v.Phi
		(*graphe).xa[i] = centrageX + vecteurScalaireCartesien(&v, &(*graphe).pointDeVue.vecteurPsi);
		(*graphe).ya[i] = centrageY + vecteurScalaireCartesien(&v, &(*graphe).pointDeVue.vecteurPhi);
		}

	for(i=0;i<SUPPORT;i++)
		{
				// Coordonnees 2D des axes
			// v = masse - point de vue
		vecteurDifferenceCartesien(&(*graphe).support[i], &(*graphe).pointDeVue.position, &v);
			// x = X + v.Psi		 y = Y + v.Phi
		(*graphe).axeX[i] = centrageX + vecteurScalaireCartesien(&v, &(*graphe).pointDeVue.vecteurPsi);
		(*graphe).axeY[i] = centrageY + vecteurScalaireCartesien(&v, &(*graphe).pointDeVue.vecteurPhi);
		}

	return 0;
	}

int grapheChangeParametre(grapheT * graphe, int parametre, int variation, int pourMille)
	{
			// Change un paramètre du graphe

	if(variation == 0)	//	Réglage du paramètre
		{
		switch (parametre)
			{
			case 0:	//	Point de vue implicite
				grapheReglagePdv(graphe, pourMille); break;
			case 1:	//	Point de vue imaginaire
				grapheReglagePdv(graphe, pourMille); break;
			case 2:	//	Point de vue réel
				grapheReglagePdv(graphe, pourMille); break;
			case 3:	//	trait point
				grapheReglageTrait(graphe, pourMille); break;
			case 4:	//	trait courbe
				grapheReglageTrait(graphe, pourMille); break;
			case 5:	//	coord vecteur
				grapheReglageCoord(graphe, pourMille); break;
			case 6:	//	coord sans
				grapheReglageCoord(graphe, pourMille); break;
			default:
				printf("ERREUR : grapheChangeParametre, paramètre inexistant\n");
			}
		}
	else	//	Variation du paramètre
		{
		printf("ERREUR : grapheChangeParametre, variation != 0\n");
		}

	return 0;
	}

int grapheReglageAxes(grapheT * graphe, int axes)
	{
		// Change la représentation graphique des axes (Derrière ou devant la courbe, sans)

	switch (axes)
		{
		case 0:	//	point
			(*graphe).axes = 0;
			printf("Axes : non représentés\n"); break;
		case 1:	//	trait
			(*graphe).axes = 1;
			printf("Axes : Derrière la courbe\n"); break;
		case 2:	//	trait
			(*graphe).axes = 2;
			printf("Axes : Devant la courbe\n"); break;
		default:
			printf("ERREUR grapheRegleAxes\n");
		}
	return 0;
	}

int grapheReglagePdv(grapheT * graphe, int position)
	{
		// Regle la position du point de vue

	switch (position)
		{
		case 0:	//	implicite
			pointDeVueReglePhi(&(*graphe).pointDeVue, PHI);
			pointDeVueReglePsi(&(*graphe).pointDeVue, PSI);
			printf("Point de vue implicite\n"); break;
		case 1:	//	imaginaire
			pointDeVueReglePhi(&(*graphe).pointDeVue, PIS2);
			pointDeVueReglePsi(&(*graphe).pointDeVue, -PIS2);
			printf("Point de vue imaginaire\n"); break;
		case 2:	//	réel
			pointDeVueReglePhi(&(*graphe).pointDeVue, PI);
			pointDeVueReglePsi(&(*graphe).pointDeVue, -PIS2);
			printf("Point de vue réel\n"); break;
		default:
			printf("ERREUR grapheReglage point de vue\n");
		}
	return 0;
	}

int grapheReglageTrait(grapheT * graphe, int trait)
	{
			// Regle la représentation graphique de la courbe
				// Change la représentation graphique de la fonction (points reliés ou non)
	switch (trait)
		{
		case 0:	//	point
			(*graphe).trait = 0;
			printf("Courbe : points non reliés\n"); break;
		case 1:	//	trait
			(*graphe).trait = 1;
			printf("Courbe : points reliés\n"); break;
		default:
			printf("ERREUR grapheRegleTrait\n");
		}
	return 0;
	}

int grapheReglageCoord(grapheT * graphe, int coord)
	{
			// Regle la représentation graphique de la courbe
				// Change la représentation graphique des coordonnées (vecteur ou cartésien)
	switch (coord)
		{
		case 0:
			(*graphe).coord = 0;
			printf("Coordonées : sans représentation\n"); break;
		case 1:
			(*graphe).coord = 1;
			printf("Coordonées : style vecteur\n"); break;
		case 2:
			(*graphe).coord = 2;
			printf("Coordonées : style cartésien\n"); break;
		default:
			printf("ERREUR grapheChangeCoord\n");
		}
	return 0;
	}

	//-----------------    AFFICHAGE      -----------------------//

int grapheAffiche(grapheT * graphe) {

		// Affiche les valeurs de psi et phi

	printf("(*graphe).pointDeVue.position :\n");
	vecteurAffiche(&(*graphe).pointDeVue.position);

	int i;
	for(i=0;i<3;i++){
		printf("\n(*graphe).support[%i] :\n", i);
		vecteurAffiche(&(*graphe).support[i]);}
	for(i=0;i<3;i++){
		printf("\n(*graphe).point[%i] :\n", i);
		vecteurAffiche(&(*graphe).point[i]);}
	for(i=0;i<3;i++){
		printf("\n(*graphe).axe[%i] :\n", i);
		vecteurAffiche(&(*graphe).axe[i]);}

//	printf("\n(*graphe).xa[0], ya[0] : %i, %i\n",(*graphe).xa[0],(*graphe).ya[0]);
//	printf("\n(*graphe).xp[0], yp[0] : %i, %i\n\n",(*graphe).xp[0],(*graphe).yp[0]);

	return 0;
	}

//////////////////////////////////////////////////////////////////
