/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
(SiCP 2.5 simulateur de chaîne de pendules, fevrier 2021)
SimFourier 0.0 Transformation de Fourier
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

#include "projection.h"

				//		Projection de la chaîne de pendules et des
				//		observables sur l'interface graphique

	//	INITIALISATION
int projectionInitialisePointDeVue(projectionT * projection,  float r,float psi, float phi);
int projectionReinitialiseBase(projectionT * projection);

	//	PROJECTION
float projectionValeurAbsolue(float valeur);
int projectionPerspectiveChaine(projectionT * projection, grapheT * graphe);
int projectionSystemeChaine3D(systemeT * systeme, projectionT * projection, grapheT * graphe);

int projectionInitialiseSupport(projectionT * projection, int nombre);
int projectionPerspectiveSupport(projectionT * projection, grapheT * graphe);

	//	CHANGE

	//	AFFICHAGE


	//-----------------    INITIALISATION      -----------------------//
int projectionInitialise(projectionT * projection)
	{

	(*projection).fenetreX = FENETRE_X;	// hauteur de la fenêtre
	(*projection).fenetreY = FENETRE_Y;	// largeur de la fenêtre

	(*projection).ratioXY=(float)FENETRE_X/(float)FENETRE_Y; // Rapport entre les dimensions de la fenêtre

	(*projection).rotation = 0;
	(*projection).logCouplage = 1.0 / log( (COUPLAGE_MAX/COUPLAGE_MIN) );
	(*projection).logDissipation = 1.0 / log( DISSIPATION_MAX/DISSIPATION_MIN );
	(*projection).logJosephson = 1.0 / log( JOSEPHSON_MAX/JOSEPHSON_MIN );
	(*projection).logAmplitude = 1.0 / log( AMPLITUDE_MAX/AMPLITUDE_MIN );
	(*projection).logFrequence = 1.0 / log( FREQUENCE_MAX/FREQUENCE_MIN );


	(*projection).largeur = LARGEUR_IMP;// largeur de la chaîne
	(*projection).ratioLH = 3.99;
	(*projection).hauteur = (int)((*projection).largeur/(*projection).ratioLH);// hauteur de la chaîne

	projectionInitialisePointDeVue(projection, 3*FENETRE_Y, PI/2 - 0.27, PI/2 + 0.21);//r, psi, phi

	return 0;
	}

int projectionInitialisePointDeVue(projectionT * projection, float r, float psi, float phi)
	{
		// Initialise la position de l'observateur et calcul les vecteurs perpendiculaires

	int i;
	for(i=0;i<2;i++)
		{
		vecteurInitialisePolaire(&(*projection).fonction[i].pointDeVue, r, psi, phi);
		}
	projectionReinitialiseBase(projection);
	return 0;
	}

int projectionReinitialiseBase(projectionT * projection)
	{
		// Réinitialise les vecteurs perpendiculaires

	int i;
	for(i=0;i<2;i++)
		{
		vecteurInitialiseVecteurPhi(&(*projection).fonction[i].pointDeVue, &(*projection).fonction[i].vecteurPhi, (*projection).fenetreX*RATIO_CHAINE_FENETRE_X);
		vecteurInitialiseVecteurPsi(&(*projection).fonction[i].pointDeVue, &(*projection).fonction[i].vecteurPsi, (*projection).fenetreY*RATIO_CHAINE_FENETRE_X*(*projection).ratioXY);
		}

	return 0;
	}

	//-----------------    PROJECTION      -----------------------//

float projectionValeurAbsolue(float valeur) {

	if(valeur<0) return -valeur;
	return valeur;
	}

int projectionSystemeCommandes(systemeT * systeme, projectionT * projection, commandesT * commandes, int duree, int mode) {

		// Projette le système sur les commandes

	float theta;
	float ratioRotatif = 0.9;
	float courantJosephson = projectionValeurAbsolue((*systeme).moteurs.courantJosephson);

				//	Projection sur les boutons rotatifs
	 //	Couplage
	theta = DEUXPI * (*projection).logCouplage * log( (*systeme).couplage / (COUPLAGE_MIN * (*systeme).nombre) );
	(*commandes).rotatifPositionX[0]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[0]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	 //	Dissipation
	theta = DEUXPI * (*projection).logDissipation * log( (*systeme).dissipation/DISSIPATION_MIN );
	(*commandes).rotatifPositionX[1]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[1]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Amplitude du moteur josephson
	theta = DEUXPI * (*projection).logJosephson * log( projectionValeurAbsolue(courantJosephson/JOSEPHSON_MIN) );
	(*commandes).rotatifPositionX[2]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[2]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Amplitude du moteur périodique
	theta = DEUXPI * (*projection).logAmplitude * log( (*systeme).moteurs.amplitude/AMPLITUDE_MIN );
	(*commandes).rotatifPositionX[3]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[3]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Fréquence du moteurs
	theta = DEUXPI * (*projection).logFrequence * log( (*systeme).moteurs.frequence/FREQUENCE_MIN );
	(*commandes).rotatifPositionX[4]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[4]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));


				//	Projection sur les petits boutons de droite
	int i;
	for(i=0;i<BOUTON_COMMANDES;i++) (*commandes).boutonEtat[i]=0;

			//	Conditions aux limites
	switch((*systeme).libreFixe) {
		case 0:
			(*commandes).boutonEtat[0]=1;break; //	Périodique
		case 1:
			(*commandes).boutonEtat[1]=1;break; //	Libre
		case 2:
			(*commandes).boutonEtat[2]=1;break; //	Fixe
		case 3:
			(*commandes).boutonEtat[3]=1;break; //	Mixte
		case 4:
			(*commandes).boutonEtat[3]=1;break; //	Mixte
		default:
			;
		}

		//	Dissipation
	switch((*systeme).modeDissipation) {
		case 0:
			(*commandes).boutonEtat[5]=1;break; //	Nulle
		case 1:
			(*commandes).boutonEtat[4]=1;break; //	Uniforme
		case 2:
			(*commandes).boutonEtat[6]=1;break; //	Extrémité
		default:
			;
		}

	if((*systeme).moteurs.etatJosephson ==1)
		{
		(*commandes).boutonEtat[7]=1; //	Marche
		}
	else
		{
		(*commandes).boutonEtat[8]=1; //	Arrêt
		}

	if((*systeme).moteurs.courantJosephson < 0)
		{
		(*commandes).boutonEtat[10]=1; //	Gauche
		}
	else
		{
	   	(*commandes).boutonEtat[9]=1; //	Droite
	    }

	switch((*systeme).moteurs.generateur)
		{
		case 0:
			(*commandes).boutonEtat[11]=1;break; //	Arrêt
		case 1:
			(*commandes).boutonEtat[12]=1;break; //	Sinus
		case 2:
			(*commandes).boutonEtat[13]=1;break; //	Carré
		case 3:
			(*commandes).boutonEtat[14]=1;break; //	Impulsion
		default:
			;
		}

	if((*systeme).moteurs.fluxon == 1)
		{
		if((*systeme).moteurs.deltaDephasage > 0)
			{
			(*commandes).boutonEtat[15]=1;
			}
		else
			{
			(*commandes).boutonEtat[16]=1;
		    }
		}

				//	Projection sur les petits boutons du bas

	for(i=0;i<TRIANGLE_COMMANDES;i++) (*commandes).triangleEtat[i]=0;

		//	Rotation automatique du point de vue
	switch((*projection).rotation)
		{
		case 3:
			(*commandes).triangleEtat[0]=1;break;
		case 1:
			(*commandes).triangleEtat[1]=1;break;
		case 0:
			(*commandes).triangleEtat[2]=0;break;
		case -1:
			(*commandes).triangleEtat[3]=1;break;
		case -3:
			(*commandes).triangleEtat[4]=1;break;
		default:
			;
		}

		//	Vitesse de la simulation
	if(duree<DUREE)
		{
			if(duree==1) (*commandes).triangleEtat[5]=-1; else (*commandes).triangleEtat[6]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).a * duree + (*commandes).b);
		}
	else
		{
		if(duree>DUREE)
			{
			if(duree==DUREE_MAX) (*commandes).triangleEtat[10]=-1; else (*commandes).triangleEtat[9]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).A * duree + (*commandes).B);
			}
		else
			{
			(*commandes).triangleEtat[8]=1;
			}
		}

	if(mode<0)
		{
		(*commandes).triangleEtat[7]=2;
		}

	return 0;
	}

int projectionObservablesCapteurs(observablesT * observables, projectionT * projection, capteursT * capteurs) {

		//	Projette les observables sur les capteurs

	(void)projection;
	float a;
	int i, k, y0;
						//	Observables	:	0 Energie, 1 Cinetique, 2 Couplage, 3 Rappel
						//	Capteurs	:	0, 1, 2 : Somme, 3, 4, 5 : droite/gauche
		//	SOMME
	if((*observables).observable[0].maximumSomme!=0.0)
		{
		a = -(float)((*capteurs).capteur[0].hauteur) / (*observables).observable[0].maximumSomme;
		}
	else
		{
		a = 0.0;
		}
	y0 = (*capteurs).capteur[0].yZero;
	for(i=0;i<DUREE_CAPTEURS;i++)
		{
		k=(i+(*observables).index+1)%DUREE_CAPTEURS;
		(*capteurs).capteur[0].somme[i].y = (int)(a*(*observables).observable[3].somme[k]) + y0;
		(*capteurs).capteur[1].somme[i].y = (int)(a*(*observables).observable[1].somme[k]) + y0;
		(*capteurs).capteur[2].somme[i].y = (int)(a*(*observables).observable[2].somme[k]) + y0;
		}


		//	GAUCHE DROITE
	if((*observables).observable[0].maximumSomme!=0.0)
		{
		a = -(float)((*capteurs).capteur[3].hauteur) / (*observables).observable[0].maximumSomme;
		}
	else
		{
		a = 0.0;
		}
	y0 = (*capteurs).capteur[3].yZero;
	for(i=0;i<DUREE_CAPTEURS;i++)
		{
		k=(i+(*observables).index+1)%DUREE_CAPTEURS;
		(*capteurs).capteur[3].gauche[i].y = (int)(a*(*observables).observable[0].gauche[k]) + y0;
		(*capteurs).capteur[3].droite[i].y = (int)(a*(*observables).observable[0].droite[k]) + y0;
		(*capteurs).capteur[3].somme[i].y = (int)(a*(*observables).observable[0].somme[k]) + y0;
		}

	return 0;
	}

int projectionSystemeChaineDePendule(systemeT * systeme, projectionT * projection, grapheT * graphe) {

		// Projection du système sur le rendu en perspective

		// Projection du système sur la chaîne de pendule 3D
	projectionSystemeChaine3D(systeme, projection, graphe);

		// Initialisation des points du support
	projectionInitialiseSupport(projection, (*systeme).nombre);

		// Projection en 2D de la représentation 3D
	projectionPerspectiveChaine(projection, graphe);
	projectionPerspectiveSupport(projection, graphe);

	return 0;
	}

int projectionInitialiseSupport(projectionT * projection, int nombre)
//
//                                                Y
//                                                
//                                             
//                                                 
//                                         X            Z'
//                                                O
//                                                       X'
//                                                
//                                                
//                                                Y'
//             Z

	{
	int i;
	float xyz;
	for(i=0;i<6;i++)
		{
		(*projection).support[i].x = 0;
		}

					// AXE Ox
	xyz = 1.2*(*projection).largeur;
	(*projection).support[0].x = xyz;
	(*projection).support[1].x = -xyz;

					// AXE Oy
	xyz = 1.2*(*projection).hauteur;
	(*projection).support[2].y = xyz;
	(*projection).support[3].y = -xyz;

					// AXE Oz
	xyz = 6.5 * (*projection).longueur;
	(*projection).support[4].z = xyz;
	xyz = 0.5 * (*projection).longueur;
	(*projection).support[5].z = -xyz;
	(void)nombre;
	return 0;
	}

int projectionPerspectiveSupport(projectionT * projection, grapheT * graphe)
	{
			//	Projette le support 3D sur le rendu en perspective

	vecteurT v;
	int i;
	int centrageX = (int)( (*projection).fenetreX * RATIO_C_X );
	int centrageY = (int)( (*projection).fenetreY * RATIO_C_Y );

	for(i=0;i<14;i++)
		{
			// Coordonnees 2D des points du support
		vecteurDifferenceCartesien(&(*projection).support[i], &(*projection).pointDeVue, &v);
		(*graphe).supporX[i] = centrageX + vecteurScalaireCartesien(&v, &(*projection).vecteurPsi);
		(*graphe).supporY[i] = centrageY + vecteurScalaireCartesien(&v, &(*projection).vecteurPhi);
		}
	if((*projection).pointDeVue.psi<0)
		{
		(*graphe).gauche=1;
		if((*projection).pointDeVue.psi < -PI/2)
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
		if((*projection).pointDeVue.psi > PI/2)
			{
			(*graphe).arriere=1;
			}
		else
			{
			(*graphe).arriere=0;
			}
		}

	if((*projection).pointDeVue.phi<PI/2)
		{
		(*graphe).dessous=1;
		}
	else
		{
		(*graphe).dessous=0;
		}

	return 0;
	}

int projectionPerspectiveChaine(projectionT * projection, grapheT * graphe)
	{
			//	Projette la chaine 3D sur le rendu en perspective

	pointsT *iterGraph=(*graphe).premier;

	vecteurT v;
	int centrageX = (int)( (*projection).fenetreX * RATIO_C_X );
	int centrageY = (int)( (*projection).fenetreY * RATIO_C_Y );

	do
		{
				// Coordonnees 2D de la masse et centrage du graphe

			// v = masse - point de vue
		vecteurDifferenceCartesien(&(iterGraph->masse), &(*projection).pointDeVue, &v);
			// x = X + v.Psi		 y = Y + v.Phi
		iterGraph->xm = centrageX + vecteurScalaireCartesien(&v, &(*projection).vecteurPsi);
		iterGraph->ym = centrageY + vecteurScalaireCartesien(&v, &(*projection).vecteurPhi);


				// Coordonnees 2D de l'axe

			// v = axe - point de vue
		vecteurDifferenceCartesien(&(iterGraph->axe), &(*projection).pointDeVue, &v);
			// x = X + v.Psi		 y = Y + v.Phi
		iterGraph->xa = centrageX + vecteurScalaireCartesien(&v, &(*projection).vecteurPsi);
		iterGraph->ya = centrageY + vecteurScalaireCartesien(&v, &(*projection).vecteurPhi);

		iterGraph = iterGraph->suivant;
		}
	while(iterGraph!=(*graphe).premier);

	return 0;
	}

int projectionSystemeChaine3D(systemeT * systeme, projectionT * projection, grapheT * graphe)
	{
	//	Projette le système sur une chaîne de pendule en 3 Dimensions

	float i = -(*systeme).nombre/2;

	chaineT *iterSystem=(*systeme).premier;
	pointsT *iterGraph=(*graphe).premier;

	do
		{
			// Axe fixe
		iterGraph->axe.x = (*projection).largeur*(i/(*systeme).nombre);
		iterGraph->axe.y = 0;
		iterGraph->axe.z = 0;

			// Masse
		iterGraph->masse.x = iterGraph->axe.x;
		iterGraph->sinTheta = sin(iterSystem->pendule.nouveau);
		iterGraph->cosTheta = cos(iterSystem->pendule.nouveau);
		iterGraph->masse.y = (*projection).hauteur * iterGraph->sinTheta;
		iterGraph->masse.z = (*projection).hauteur * iterGraph->cosTheta;

		//if(x>0) iterGraph->position=1;
		//else iterGraph->position=0;

		iterGraph = iterGraph->suivant;
		iterSystem = iterSystem->suivant;

		i = i + 1.0;

		}
	while(iterGraph!=(*graphe).premier);
	return 0;
	}


	//-----------------    CHANGE LA PROJECTION     -----------------------//

int projectionChangeFenetre(projectionT * projection, int x, int y) {

		//	Enregistre le changement de la taille de la fenêtre

	(*projection).fenetreX=x;
	(*projection).fenetreY=y;

	(*projection).ratioXY=(float)x/(float)y;

	projectionReinitialiseBase(projection);
	return 0;
	}

int projectionChangePhi(projectionT * projection, float x) {

		// Change la position de l'observateur suivant phi

	float r, psi, phi;

	r = (*projection).pointDeVue.r;
	psi = (*projection).pointDeVue.psi;
	phi = (*projection).pointDeVue.phi + x;

		// phi reste inférieur à PI
	if(phi > PI)
		{
		phi = PI;
		}

		// phi reste supérieur à zéro
	if(phi < 0.0)
		{
		phi = 0.0;
		}

	vecteurInitialisePolaire(&(*projection).pointDeVue, r, psi, phi);
	projectionReinitialiseBase(projection);

	return 0;
	}

int projectionChangePsi(projectionT * projection, float x) {

		// Change la position de l'observateur suivant psi

	float r, psi, phi;

	r = (*projection).pointDeVue.r;
	psi = (*projection).pointDeVue.psi + x;
	phi = (*projection).pointDeVue.phi;

	if(psi > PI)
		{
		psi = psi - DEUXPI;
		}

	if(psi < -PI)
		{
		psi = psi + DEUXPI;
		}

	vecteurInitialisePolaire(&(*projection).pointDeVue, r, psi, phi);
	projectionReinitialiseBase(projection);

	return 0;
	}

int projectionChangeTaille(projectionT * projection, float x) {

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

	//-----------------    AFFICHAGE      -----------------------//

int projectionAffichePointDeVue(projectionT * projection) {

		// Affiche les valeurs de psi et phi

	float r, psi, phi;

	r = (*projection).pointDeVue.r;
	psi = (*projection).pointDeVue.psi;
	phi = (*projection).pointDeVue.phi;

	printf("(*projection).pointDeVue.r = %f\n", r);
	printf("(*projection).pointDeVue.psi = %f\n", psi);
	printf("(*projection).pointDeVue.phi = %f\n", phi);

	return 0;
	}


void projectionAffiche(projectionT * projection) {

	//	Affiche les paramètres de la projection

	printf(" Point de vue\n");
	vecteurAffiche(&(*projection).pointDeVue);
	printf(" Vecteur psi\n");
	vecteurAffiche(&(*projection).vecteurPsi);
	printf(" Vecteur phi\n");
	vecteurAffiche(&(*projection).vecteurPhi);

	printf("(*projection).rotation = %d\n", (*projection).rotation);
	printf("(*projection).ratioXY = %f\n", (*projection).ratioXY);
	printf("(*projection).hauteur = %d\n", (*projection).hauteur);
	printf("(*projection).largeur = %d\n", (*projection).largeur);
	printf("(*projection).fenetreX = %d\n", (*projection).fenetreX);
	printf("(*projection).fenetreY = %d\n", (*projection).fenetreY);
	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////
