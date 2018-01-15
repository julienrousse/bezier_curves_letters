/*!
 * \file Point.h
 * \brief Header de la classe Point
 */


#include<iostream>

#ifndef POINT_H_
#define POINT_H_


/*!
 * \class Point
 * \brief Objet Point
 */
class Point {
	private:
		int x_; /*!< Abscisse du point. */
		int y_; /*!< Ordonnée du point. */
	public:
		/*!
		 * \brief Constructeur par défaut
		 * Construit le point (0,0)
		 */
		Point();

		/* \brief Constructeur avec paramètres
		 * Construit le point (x,y)
		 */
		Point(int x, int y);


		/*!
		 * \brief Getter
		 * \return x_
		 */
		int get_x();

		/*!
		 * \brief Getter
		 * \return y_
		 */
		int get_y();


		/*!
		 * \brief Surcharge de l'opérateur << pour les tests
		 *
		 */
		friend std::ostream& operator<<(std::ostream& st, const Point & p);
};

#endif /* POINT_H_ */
