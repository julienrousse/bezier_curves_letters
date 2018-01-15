/*!
 * \file Police.cpp
 * \brief Fichier de la classe Police
 */


#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Police.h"
#include "Bitmap.h"


Police::Police()
{
	Bitmap b(1000,1200);
	for (int i = 0; i < 26; i++)
		lettres_.push_back(b);
}

Police::~Police()
{
	lettres_.clear(); //! lettres_.clear() détruit les bitmaps du vector.
	std::vector<Bitmap>().swap(lettres_); //! std::vector<Bitmap>().swap(lettres_) libère l'emplacement mémoire
}



Bitmap Police::get_lettre(int i)
{
	return lettres_[i];
}



/*!
 * \brief Renvoie le nom du fichier
 * \param num : le numéro de la police
 * \param lettre : la lettre
 * \return un char* contenant le nom du fichier
 */
char* nom_fichier(char num, char lettre)
{
	char* nom_fichier = new char[21];
	sprintf(nom_fichier, "Police_I_Lettre_X.ppm");
	nom_fichier[7] = num;
	nom_fichier[16] = lettre;
	return nom_fichier;
}



void Police::draw_all()
{
	std::cout << "*** Création de la Police 1 ***" << std::endl; //! On affiche l'état d'avancement du programme.

	std::ifstream fichier("points_lettres.txt", std::ios::in); //! On lit le fichier "points_lettres.txt" contenant les coordonées des points à tracer (points extrémités et points de contrôle) (voir le rapport pour plus de détails)
	if (!fichier) {
		std::cout << "Erreur lors de la lecture du fichier" << std::endl;
		std::cout << "Vérifiez que le fichier 'points_lettres.txt' est dans le dossier du projet" << std::endl;
		exit(-1);}

	std::string ligne;
	for (int i = 0; i < 26; i++) {
		int nl = lettres_[i].get_nl();
		char lettre;
		int nb_traits, nb_points, x1, x2, x3, y1, y2, y3;

		std::getline(fichier,ligne);
		std::istringstream str_lettre(ligne);
		str_lettre >> lettre;
		std::getline(fichier,ligne);
		std::istringstream str_traits(ligne);
		str_traits >> nb_traits;

		std::cout << "Création de la lettre " << lettre << "..." << std::endl;

		for (int j = 0; j < nb_traits; j++) {
			std::getline(fichier,ligne);
			std::istringstream str_ligne(ligne);
			str_ligne >> nb_points;

			switch (nb_points) {
				case 2: {
					str_ligne >> x1 >> y1 >> x2 >> y2;
					Point t2[2] = {Point(nl - y1 - 50, x1), Point(nl - y2 - 50, x2)}; //! On effectue un changement de repère (voir rapport pour plus de détails).
					lettres_[i].draw(std::vector<Point>(t2, t2+2)); //! On utilise la méthode draw de la classe Bitmap.
					break;}
				case 3: {
					str_ligne >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
					Point t3[3] = {Point(nl - y1 - 50, x1), Point(nl - y2 - 50, x2), Point(nl - y3 - 50, x3)};
					lettres_[i].draw(std::vector<Point>(t3, t3+3));
					break;}
			}
		}

		lettres_[i].savePPM(nom_fichier('1', lettre));
	}

	fichier.close();
	std::cout << "*** Police 1 créée ***" << std::endl << std::endl;
}



/*!
 * \brief Renvoie la lettre correspondant au numéro donné en argument
 * \param num : le numéro de la lettre (ordre de l'alphabet, compris entre 0 et 25)
 * \return le char de la lettre correspondant à num
 */
char lettre_numero(int num)
{
	//! Ajout d'une exception si num n'est pas compris entre 0 et 25.
	if (num < 0 || num > 25)
		throw std::invalid_argument("num n'est pas dans l'intervalle [0,25]");
	return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[num];
}


void Police::fill_all()
{
	std::cout << "*** Création de la Police 2 ***" << std::endl; //! On affiche l'état d'avancement du programme.
	for (int i = 0; i < 26; i++)
	{
		char lettre = lettre_numero(i);
		std::cout << "Création de la lettre " << lettre << "..." << std::endl;
		lettres_[i].fill(lettre); //! On utilise la méthode fill de la classe Bitmap.
		lettres_[i].savePPM(nom_fichier('2', lettre));
	}

	std::cout << "*** Police 2 créée ***" << std::endl << std::endl;
}


void Police::contour_rouge_all()
{
	std::cout << "*** Création de la Police 3 ***" << std::endl; //! On affiche l'état d'avancement du programme.
	for (int i = 0; i < 26; i++)
	{
		char lettre = lettre_numero(i);
		std::cout << "Création de la lettre " << lettre << "..." << std::endl;
		lettres_[i].contour_rouge(); //! On utilise la méthode contour_rouge de la classe Bitmap.
		lettres_[i].savePPM(nom_fichier('3', lettre));
	}

	std::cout << "*** Police 3 créée ***" << std::endl << std::endl;
}

