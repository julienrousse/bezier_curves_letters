/*!
 * \file Point.cpp
 * \brief Fichier de la classe Point
 */


#include <iostream>
#include <stdexcept>
#include "Point.h"


Point::Point()
{
	x_ = 0;
	y_ = 0;
}

Point::Point(int x, int y)
{
	/*!
	 * Ajout d'une exception si les arguments sont négatifs.
	 */
	if (x < 0 || y < 0)
		throw std::invalid_argument ("Erreur : au moins un argument est négatif");
	x_ = x;
	y_ = y;
}


int Point::get_x()
{
	return x_;
}

int Point::get_y()
{
	return y_;
}



std::ostream& operator<<(std::ostream& st, const Point &p)
{
	return st << "Point : (" << p.x_ << ", " << p.y_ << ")";
}
