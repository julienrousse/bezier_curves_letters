/*!
 * \file Bitmap.cpp
 * \brief Header de la classe Bitmap
 */


#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "Bitmap.h"
#include "Point.h"


Bitmap::Bitmap(int nl, int nc)
{
	/*!
	 * Ajout d'une exception si les arguments sont négatifs.
	 */
	if (nl < 0 or nc < 0)
		throw std::invalid_argument ("Erreur : au moins un argument est négatif");
	nl_ = nl;
	nc_ = nc;

	data_ = new Pixel*[nl_];
	for (int i = 0; i < nl_; i++)
		data_[i] = new Pixel[nc_];

	Pixel p;
	for (int i = 0; i < nl_; i++)
		for (int j = 0; j < nc_; j++)
			data_[i][j] = p;
}

Bitmap::Bitmap(const Bitmap & b)
{
	nl_ = b.nl_;
	nc_ = b.nc_;

	data_ = new Pixel*[nl_];
	for (int i = 0; i < nl_; i++)
		data_[i] = new Pixel[nc_];

	for (int i = 0; i < nl_; i++)
		for (int j = 0; j < nc_; j++)
			data_[i][j] = b.data_[i][j];
}

Bitmap::~Bitmap()
{
	for (int i = 0; i < nl_; i++)
		delete[] data_[i];

	delete[] data_;
}


int Bitmap::get_nl() const
{
	return nl_;
}

int Bitmap::get_nc() const
{
	return nc_;
}


Pixel Bitmap::getPixel(int i, int j) const
{
	/*!
	 * Ajout d'une exception si les coordonnées entrées ne sont pas dans le Bitmap.
	 */
	if (i < 0 or i > nl_ or j < 0 or j > nc_)
		throw std::invalid_argument ("Erreur : les coordonnées entrées ne sont pas dans le Bitmap");
	return data_[i][j];
}

void Bitmap::setPixel(int i, int j, Pixel p)
{
	/*!
	 * Ajout d'une exception si les coordonnées entrées ne sont pas dans le Bitmap.
	 */
	if (i < 0 or i > nl_ or j < 0 or j > nc_)
		throw std::invalid_argument ("Erreur : les coordonnées entrées ne sont pas dans le Bitmap");
	data_[i][j] = p;
}



Point Bitmap::deCasteljau(std::vector<Point> vp, float t)
{
	if (vp.size() == 1)
		return vp[0];

	else
	{
		std::vector<Point> newvp(vp.size() - 1);
		for (unsigned int i = 0; i < newvp.size(); i++)
		{
			float fx = (1 - t) * vp[i].get_x() + t * vp[i+1].get_x();
			float fy = (1 - t) * vp[i].get_y() + t * vp[i+1].get_y();
			//! Les surcharges des opérateurs + et * possibles mais il est plus sûr de faire
			//! de cette façon pour avoir le bon résultat après conversion implicite float et int.

			newvp[i] = Point(round(fx), round(fy));
		}

		return deCasteljau(newvp, t);
	}
}


void Bitmap::draw(std::vector<Point> vp)
{
	float ratio = 0.0001; //! On choisit 0.0001 comme ratio, qui offre un bon compromis entre précision et rapidité d'exécution du programme.
	for (float t = 0; t <= 1; t += ratio)
	{
		Point p = deCasteljau(vp, t);
		setPixel(p.get_x(), p.get_y(), Pixel(0,0,0));
	}
}



std::pair<int,int> Bitmap::first_last_line()
{
	std::pair<int,int> fl(0,0);
	for (int i = 0; i < nl_; i++)
		for (int j = 0; j < nc_; j++)
			if (getPixel(i,j) == Pixel(0,0,0))
			{
				if (fl.first == 0)
					fl.first = i;
				fl.second = i;
				break; //! Une fois la dernière ligne avec un ou plusieurs pixels noirs atteinte, il est inutile de continuer.
			}
	return fl;
}


std::vector<int> Bitmap::nb_pixels_ligne(int i)
{
	std::vector<int> coordonnees;
	for (int j = 0; j < nc_; j++)
	{
		if (getPixel(i,j) == Pixel(0,0,0) && getPixel(i,j+1) == Pixel(255,255,255)) //! On recherche les pixels noirs immédiatement suivis d'un pixel blanc.
			coordonnees.push_back(j);
	}
	return coordonnees;
}


void Bitmap::fill( char lettre)
{
	std::pair<int,int> fl = first_last_line();
	int first_five = 0; //! first_five est défini pour les cas particuliers des lettres 'M', 'N' et 'W'
	int first_seven = 0; //! first_seven est défini pour les cas particuliers des lettres 'M' et 'W'
	for (int i = 0; i < nl_; i++) {
		if (i > fl.first && i < fl.second) {
			std::vector<int> coordonnees = nb_pixels_ligne(i);
			if (coordonnees.size() == 0) //! S'il n'y a pas de pixels noirs sur une ligne, on passe à la ligne suivante
				continue;

			if (coordonnees.size() == 3) { //! Présence de cas particuliers pour les lettres 'C', 'G', 'J', 'Q' et 'S' pour les vectors de taille 3
				if ((lettre == 'J' && (i == 747 || i == 748)) || (lettre == 'Q' && i == 964) || (lettre == 'S' && i == 746)) // Suppression du 1er pixel
					coordonnees.erase(coordonnees.begin());
				else if ((lettre == 'C' && (i == 398 || i == 399 || i == 400 || i == 695 || i == 696 || i == 697)) || (lettre == 'G' && (i == 394 || i == 395 || i == 396 || i == 536)) || (lettre == 'S' && i == 337)) // Suppression du 3e pixel
					coordonnees.erase(coordonnees.begin() + 2);
				else coordonnees.erase(coordonnees.begin() + 1);}

			if (coordonnees.size() == 5 && lettre == 'W') //! Présence de cas particuliers pour les lettres 'M', 'N', 'P', 'Q' et 'W' pour les vectors de taille 5
				coordonnees.erase(coordonnees.begin() + 3);
			else if (coordonnees.size() == 5 && first_five <= 3 && lettre != 'P' && lettre != 'Q') {
				coordonnees.erase(coordonnees.begin() + 1);
				first_five += 1;
				if (lettre == 'N' && first_five == 3)
					first_five += 2;}
			else if (coordonnees.size() == 5 && ((first_five > 3 && lettre != 'M') || (lettre == 'Q' && i != 616 && i != 617) || lettre == 'P'))
				coordonnees.erase(coordonnees.begin() + 3);
			else if (coordonnees.size() == 5 && ((first_five > 3 && lettre == 'M') || (lettre == 'Q' && (i == 616 || i == 617))))
				coordonnees.erase(coordonnees.begin() + 2);

			if (coordonnees.size() == 7 && ((first_seven <= 3 && lettre == 'M') || (first_seven > 2 && lettre == 'W'))) { //! Présence de cas particuliers pour les lettres 'B', 'M' et 'W' pour les vectors de taille 7
				coordonnees.erase(coordonnees.begin() + 5);
				if (lettre == 'W') {
					coordonnees.erase(coordonnees.begin() + 4);
					coordonnees.erase(coordonnees.begin() + 1);}
				first_seven += 1;}
			if (coordonnees.size() == 7 && ((first_seven > 3 && lettre == 'M') || (first_seven <= 2 && lettre == 'W') || lettre == 'B')) {
				coordonnees.erase(coordonnees.begin() + 3);
				first_seven += 1;}

			if (coordonnees.size() == 9) //! Présence de cas particulier pour 'B' pour les vectors de taille 9
				coordonnees.erase(coordonnees.begin() + 4);

			if (coordonnees.size() % 2 == 0) {
				if (coordonnees.size() == 6 && (lettre == 'W' && (i == 666 || i == 667))) { //! 2 lignes avec un comportement particulier de la lettre 'W' pour les vectors de taille 6
					coordonnees.erase(coordonnees.begin() + 4);
					coordonnees.erase(coordonnees.begin() + 1);}
				for (unsigned int k = 0; k < coordonnees.size(); k += 2) //! La dernière boucle générique est utilisée pour toutes les lignes (toutes les tailles de vectors sont rendues paires)
					for (int l = coordonnees[k]; l <= coordonnees[k+1]; l++)
						setPixel(i, l, Pixel(0,0,0));}}}}



void Bitmap::blanc_rouge(int i, int j)
{
	if (getPixel(i,j) == Pixel(255,255,255))
		setPixel(i, j, Pixel(255,0,0));
}

void Bitmap::contour_rouge()
{
	for (int i = 0; i < nl_; i++)
	{
		for (int j = 0; j < nc_ - 2; j++)
		{
			if (getPixel(i,j) == Pixel(0,0,0))
			{
				blanc_rouge(i-2, j);
				blanc_rouge(i-1, j);
				blanc_rouge(i+1, j);
				blanc_rouge(i+2, j);
				blanc_rouge(i, j-1);
				blanc_rouge(i, j-2);
				blanc_rouge(i, j+1);
				blanc_rouge(i, j+2);

				//! On met des pixels rouges dans les angles et les diagonales (voir rapport pour plus de détails)
				blanc_rouge(i-2, j-2);
				blanc_rouge(i-2, j-1);
				blanc_rouge(i-2, j+1);
				blanc_rouge(i-2, j+2);
				blanc_rouge(i-1, j-2);
				blanc_rouge(i-1, j-1);
				blanc_rouge(i-1, j+1);
				blanc_rouge(i-1, j+2);
				blanc_rouge(i+1, j-2);
				blanc_rouge(i+1, j-1);
				blanc_rouge(i+1, j+1);
				blanc_rouge(i+1, j+2);
				blanc_rouge(i+2, j-1);
				blanc_rouge(i+2, j-2);
				blanc_rouge(i+2, j+1);
				blanc_rouge(i+2, j+2);
			}
		}
	}
}



int Bitmap::savePPM(const char *path)
{
	FILE *image;
	image = fopen(path, "wb"); //! On ouvre un fichier en écriture. Ouvrir avec fopen plutôt qu'avec un ofstream est généralement plus rapide.
	if (image == NULL)
		exit(-1);

	fprintf(image, "P3\n"); //! On écrit dans le fichier l'en-tête des fichiers .ppm.
	fprintf(image, "%d %d\n", nc_, nl_);
	fprintf(image, "255\n");

	for (int i = 0; i < nl_; i++)
	{
		for(int j = 0; j < nc_; j++)
		{
			char buffer[20];
			Pixel pixel = getPixel(i,j);
			sprintf(buffer, "%d %d %d ", pixel.get_r(), pixel.get_g(), pixel.get_b()); //! On écrit dans le fichier les Pixels du Bitmap
			fputs(buffer, image);
		}
	}

	fclose(image);
	return 0;
}



std::ostream& operator<<(std::ostream& st, const Bitmap &b)
{
	return st << "Pixel : (" << b.nl_ << ", " << b.nc_ << ")\n" << "First element : " << b.data_[0][0];
}
