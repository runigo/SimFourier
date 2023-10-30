/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
(SiCP 2.5 simulateur de chaîne de pendules, fevrier 2021)
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

#include "projectionGraph.h"

				//		Projections des graphes 3D
				//		 sur les graphes 2D

	//	INITIALISATION

	//	PROJECTION
int projectionPerspectiveGraphes(projectionGraphT * projection, graphesT * graphes);
int projectionPerspectiveGraphe(grapheT * graphe, int centrageX, int centrageY);
int projectionPerspectiveSupport(projectionGraphT * projection, grapheT * graphe);

	//	CHANGE

	//	AFFICHAGE


	//-----------------    INITIALISATION      -----------------------//
int projectionGraphInitialise(projectionGraphT * projection)
	{

	(*projection).fenetreX = FENETRE_X;	// hauteur de la fenêtre
	(*projection).fenetreY = FENETRE_Y;	// largeur de la fenêtre

	//(*projection).ratioXY=(float)FENETRE_X/(float)FENETRE_Y; // Rapport entre les dimensions de la fenêtre

	return 0;
	}

	//-----------------    PROJECTION      -----------------------//

int projectionGraphGraphes(projectionGraphT * projection, graphesT * graphes) {

		// Projection des graphes 3D sur les graphes 2D

		// Initialisation des points du support
	//projectionInitialiseSupport(projection, (*systeme).nombre);

		//		Projection des graphes 3D sur les graphes 2D
		// Projection en 2D de la représentation 3D
	projectionPerspectiveSupport(projection, &(*graphes).fonction);
	projectionPerspectiveSupport(projection, &(*graphes).fourier);
	//projectionPerspectiveGraphes(projection, graphes);
	projectionPerspectiveGraphe(&(*graphes).fonction, (int)( (*projection).fenetreX * RATIO_C_X ), (int)( (*projection).fenetreY * RATIO_C_Y_Q ) );
	projectionPerspectiveGraphe(&(*graphes).fourier, (int)( (*projection).fenetreX * RATIO_C_X ), (int)( (*projection).fenetreY * RATIO_C_Y_F ) );
	return 0;
	}

int projectionPerspectiveSupport(projectionGraphT * projection, grapheT * graphe)
	{
			//	Projette le support 3D sur le rendu en perspective

	vecteurT v;
	int i;
	int centrageX = (int)( (*projection).fenetreX * (*graphe).ratiox );
	int centrageY = (int)( (*projection).fenetreY * (*graphe).ratioy );

	for(i=0;i<7;i++)
		{
			// Coordonnees 2D des points du support
		vecteurDifferenceCartesien(&(*graphe).support[i], &(*graphe).pointDeVue.position, &v);
		(*graphe).supporX[i] = centrageX + vecteurScalaireCartesien(&v, &(*graphe).pointDeVue.vecteurPsi);
		(*graphe).supporY[i] = centrageY + vecteurScalaireCartesien(&v, &(*graphe).pointDeVue.vecteurPhi);
		}

	if((*graphe).pointDeVue.position.psi<0)
		{
		(*graphe).gauche=1;
		if((*graphe).pointDeVue.position.psi < -PI/2)
			{
			(*graphe).arriere=1;
			}
		else
			{
			(*graphe).arriere=0;
			}
		}
	else
		{
		(*graphe).gauche=0;
		if((*graphe).pointDeVue.position.psi > PI/2)
			{
			(*graphe).arriere=1;
			}
		else
			{
			(*graphe).arriere=0;
			}
		}

	if((*graphe).pointDeVue.position.phi<PI/2)
		{
		(*graphe).dessous=1;
		}
	else
		{
		(*graphe).dessous=0;
		}

	return 0;
	}

int projectionPerspectiveGraphes(projectionGraphT * projection, graphesT * graphes)
	{
			//	Projette les graphes 3D sur les graphes 2D

	projectionPerspectiveGraphe(&(*graphes).fonction, (int)( (*projection).fenetreX * RATIO_C_X ), (int)( (*projection).fenetreY * RATIO_C_Y_Q ) );
	projectionPerspectiveGraphe(&(*graphes).fourier, (int)( (*projection).fenetreX * RATIO_C_X ), (int)( (*projection).fenetreY * RATIO_C_Y_F ) );

	return 0;
	}

int projectionPerspectiveGraphe(grapheT * graphe, int centrageX, int centrageY)
	{
						//	Projette un graphe 3D sur son graphe 2D
	vecteurT v;
	int i;
	int nombre = (*graphe).nombre;

	for(i=0;i<nombre;i++)
		{
				// Coordonnees 2D du point et centrage du graphe

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

	return 0;
	}

	//-----------------    CHANGE LA PROJECTION     -----------------------//

int projectionGraphChangeFenetre(projectionGraphT * projection, int x, int y) {

		//	Enregistre le changement de la taille de la fenêtre

	(*projection).fenetreX=x;
	(*projection).fenetreY=y;

	//(*projection).ratioXY=(float)x/(float)y;

	//projectionReinitialiseBase(projection);
	return 0;
	}
/*
int projectionGraphChangeTaille(projectionGraphT * projection, float x) {

		// Change la taille de la chaîne

	int largeur = (*projection).largeur * x;

	if(largeur > LARGEUR_MAX)
		{
		printf("Maximum de la taille ateinte\n");
		}
	else
		{
		if(largeur < LARGEUR_MIN)
			{
			printf("Minimum de la taille ateinte\n");
			}
		else
			{
			(*projection).largeur = largeur;
			(*projection).hauteur = (int)(largeur/(*projection).ratioLH);
			printf("(*projection).hauteur = %d\n", (*projection).hauteur);
			printf("(*projection).largeur = %d\n", (*projection).largeur);
			}
		}

	return 0;
	}
*/

	//-----------------    AFFICHAGE      -----------------------//

void projectionGraphAffiche(projectionGraphT * projection) {

	//	Affiche les paramètres de la projection

/*
	printf(" Hauteur de la fenêtre\n");
	vecteurAffiche(&(*projection).fenetreX);
	printf(" Largeur de la fenêtre\n");
	vecteurAffiche(&(*projection).fenetreY);
	printf(" Rapport largeur / hauteur\n");
	vecteurAffiche(&(*projection).ratioXY);
*/
	//printf("(*projection).ratioXY = %f\n", (*projection).ratioXY);
	printf("(*projection).fenetreX = %d\n", (*projection).fenetreX);
	printf("(*projection).fenetreY = %d\n", (*projection).fenetreY);

	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////
