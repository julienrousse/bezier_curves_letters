/*!
 * \file Police.h
 * \brief Header de la classe Police
 */


#ifndef POLICE_H_
#define POLICE_H_

#include <vector>
#include "Bitmap.h"


/*!
 * \class Police
 * \brief Objet Police
 */
class Police
{
	private:
		std::vector<Bitmap> lettres_; /*!< vector de Bitmaps. */
	public:
		/*!
		 * \brief Constructeur par défaut
		 * Construit 26 Bitmaps de taille (1000, 1200) composés de Pixels blancs
		 */
		Police();

		/*!
		 * \brief Destructeur de Police
		 */
		virtual ~Police();


		/*!
		 * \brief Renvoie le bitmap de la lettre n°i
		 * \param i : le numéro de la lettre dont on souhaite récupérer le Bitmap (le numéro correspond à son emplacement de l'alphabet, 1 pour A par exemple)
		 * \return le Bitmap de la lettre n°i
		 */
		Bitmap get_lettre(int i);


		/*!
		 * \brief Dessine les contours de tous les Bitmaps de la Police
		 */
		void draw_all();

		/*!
		 * \brief Remplit tous les Bitmaps de la Police de Pixels noirs
		 */
		void fill_all();

		/*!
		 * \brief Dessine le contour rouge de 2 pixels de tous les Bitmaps de la Police
		 */
		void contour_rouge_all();
};

#endif /* POLICE_H_ */
