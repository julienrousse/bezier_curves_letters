/*!
 * \file Pixel.cpp
 * \brief Fichier de la classe Pixel
 */


#include <iostream>
#include <stdexcept>
#include "Pixel.h"


Pixel::Pixel(int r, int g, int b)
{
	/*!
	 * Ajout d'une exception si les arguments ne sont pas compris entre 0 et 255.
	 */
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		throw std::invalid_argument ("Erreur : au moins un argument n'est pas compris entre 0 et 255");

	else
	{
		r_ = r;
		g_ = g;
		b_ = b;
	}
}


int Pixel::get_r()
{
	return r_;
}

int Pixel::get_g()
{
	return g_;
}

int Pixel::get_b()
{
	return b_;
}


std::ostream& operator<<(std::ostream& st, const Pixel &p)
{
	return st << "Pixel : (" << p.r_ << ", " << p.g_ << ", " << p.b_ << ")";
}


bool operator==(const Pixel& p1, const Pixel& p2)
{
	return (p1.r_ == p2.r_) && (p1.g_ == p2.g_) && (p1.b_ == p2.b_);
}

bool operator!=(const Pixel& p1, const Pixel& p2)
{
	return !(p1 == p2);
}

