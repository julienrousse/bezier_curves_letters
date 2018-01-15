/*!
 * \file Pixel.h
 * \brief Header de la classe Pixel
 */


#include<iostream>

#ifndef PIXEL_H_
#define PIXEL_H_


/*!
 * \class Pixel
 * \brief Objet Pixel
 */
class Pixel
{
	private:
		int r_; /*!< Attribut rouge du pixel. */
		int g_; /*!< Attribut vert du pixel. */
		int b_; /*!< Attribut bleu du pixel. */

	public:
		/*!
		 * \brief Constructeur de Pixel
		 *
		 * \param r = 255 : la valeur rouge du pixel, vaut 255 par défaut.
		 * \param g = 255 : la valeur vert du pixel, vaut 255 par défaut.
		 * \param b = 255 : la valeur bleu du pixel, vaut 255 par défaut.
		 *
		 * Des valeurs par défaut sont fournies : (255, 255, 255).
		 * Le constructeur construit donc un pixel blanc si aucune valeur n'est fournie.
		 */
		Pixel (int r = 255, int g = 255, int b = 255);


		/*!
		 * \brief Getter
		 * \return r_
		 */
		int get_r();

		/*!
		 * \brief Getter
		 * \return g_
		 */
		int get_g();

		/*!
		 * \brief Getter
		 * \return b_
		 */
		int get_b();


		/*!
		 * \brief Surcharge de l'opérateur << pour les tests
		 */
		friend std::ostream& operator<<(std::ostream& st, const Pixel &p);

		/*!
		 * \brief Surcharge de l'opérateur == pour comparer 2 pixels
		 * \param p1 : le premier pixel à comparer
		 * \param p2 : le deuxième pixel à comparer
		 * \return true si les deux pixels sont identiques, false sinon.
		 */
		friend bool operator==(const Pixel &p1, const Pixel &p2);

		/*!
		 * \brief Surcharge de l'opérateur != pour comparer 2 pixels
		 * \param p1 : le premier pixel à comparer
		 * \param p2 : le deuxième pixel à comparer
		 * \return false si les deux pixels sont identiques, true sinon.
		 */
		friend bool operator!=(const Pixel &p1, const Pixel &p2);
};


#endif /* PIXEL_H_ */
