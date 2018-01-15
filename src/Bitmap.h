/*!
 * \file Bitmap.h
 * \brief Header de la classe Bitmap
 */


#include <iostream>
#include <vector>
#include "Pixel.h"
#include "Point.h"

#ifndef BITMAP_H_
#define BITMAP_H_


/*!
 * \class Bitmap
 * \brief Objet Bitmap
 */
class Bitmap
{
	private:
		int nl_; /*!< Nombre de lignes du Bitmap. */
		int nc_; /*!< Nombre de colonnes du Bitmap. */
		Pixel** data_; /*!< Tableau de Pixels. */

	public:
		/*!
		 * \brief Constructeur avec paramètres de Bitmap
		 *
		 * Construit le Bitmap de dimensions (nl, nc)
		 */
		Bitmap(int nl, int nc);

		/*!
		 * \brief Constructeur de copie de Bitmap
		 * \param b : référence du Bitmap à copier
		 *
		 * Construit le Bitmap qui est la copie de b
		 */
		Bitmap(const Bitmap & b);

		/*!
		 * \brief Destructeur de Bitmap
		 */
		virtual ~Bitmap();


		/*!
		 * \brief Getter
		 * \return nl_
		 */
		int get_nl() const;

		/*!
		 * \brief Getter
		 * \return nc_
		 */
		int get_nc() const;


		/*!
		 * \brief Getter
		 * \param i : le numéro de la ligne
		 * \param j : le numéro de la colonne
		 * \return le pixel à la ligne i et à la colonne j
		 */
		Pixel getPixel(int i, int j) const;

		/*!
		 * \brief Setter
		 * \param i : le numéro de la ligne
		 * \param j : le numéro de la colonne
		 * \param p: le pixel à mettre
		 *
		 * Met le Pixel p à la ligne i et à la colonne j.
		 */
		void setPixel(int i, int j, Pixel p);


		/*!
		 * \brief Algorithme de de Casteljau
		 * \param vp : une vector de points
		 * \param ratio : le ratio de l'algortihme de de Casteljau
		 * \return le Point renvoyé par l'algorithme de de Casteljau.
		 */
		Point deCasteljau(std::vector<Point> vp, float ratio);

		/*!
		 * \brief Dessine les contours d'un caractère
		 * \param vp : une vector de points
		 */
		void draw(std::vector<Point> vp);


		/*!
		 * \brief Renvoie les numéros de la première et de la dernière ligne
		 * \return un std::pair<int,int> contenant les numéros de la première ligne et de la dernière ligne
		 */
		std::pair<int,int> first_last_line();

		/*!
		 * \brief Renvoie un vector contenant les numéros de colonnes des pixels noirs imméidatement suivis d'un pixel blanc
		 * \param i : le numéro de la ligne dont on souhaite compter le nombre de pixels
		 * \return un std::vector<int> contenant les numéros de colonnes des pixels noirs imméidatement suivis d'un pixel blanc
		 */
		std::vector<int> nb_pixels_ligne(int i);

		/*!
		 * \brief Remplit un caractère de pixels noirs
		 * \param lettre : la lettre en train d'être remplie pour les cas particuliers
		 */
		void fill(char lettre);


		/*!
		 * \brief Colorie en rouge les pixels blancs autour d'un pixel noir
		 * \param i : le numéro de la ligne du pixel à tester
		 * \param j : le numéro de la colonne du pixel à tester
		 */
		void blanc_rouge(int i, int j);

		/*!
		 * \brief Dessine le contour rouge de 2 pixels des caractères
		 */
		void contour_rouge();


		/*!
		 * \fn savePPM(const Bitmap & bitmap, const char *path)
		 * \brief Enregistrement d'image au format .ppm
		 * \param bitmap : un bitmap à enregistrer
		 * \param *path : le path où enregistrer le bitmap
		 * \return 0 si le bitmap a été enregistré, -1 sinon
		 */
		int savePPM(const char *path);


		/*!
		 * \brief Surcharge de l'opérateur << pour les tests
		 */
		friend std::ostream& operator<<(std::ostream& st, const Bitmap &b);
};

#endif /* BITMAP_H_ */
