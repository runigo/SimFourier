/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
(SiCP 1.6 simulateur de chaîne de pendules, mars 2018)
SimFourier 0.1 Transformation de Fourier
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

#include "point.h"

int pointInitialise(pointT * point) {

		vecteurInitialise(&(*point).point);	// Coordonnees 3D du point

		vecteurinitialise(&(*point).axe);	// Coordonnees 3D de l'axe

			//	Mémorise la position angulaire pour la colorisation
		(*point).sinTheta = 0;
		(*point).cosTheta = 0;	


		(*point).xp = 0;		// Absisse 2D du point
		(*point).yp = 0;		// Ordonnée 2D du point


		(*point).xa = 0;		// Absisse 2D de l'axe
		(*point).ya = 0;		// Ordonnée 2D de l'axe
return 0;
}
//////////////////////////////////////////////////////////////////////
