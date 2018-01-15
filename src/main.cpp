/*!
 * \file main.cpp
 * \brief Fichier main
 */


#include <iostream>
#include "Police.h"


int main()
{
	//! On crée une instance de Police.
	Police police;

	//! On appelle les méthodes draw_all, fill_all et contour_rouge_all

	police.draw_all();

	police.fill_all();

	police.contour_rouge_all();


	/*!
	 * Remarque : on aurait pu écrire\n
	 * Police police;\n
	 * police.draw_all();\n
	 * Police police2;\n
	 * police2.draw_all();\n
	 * police2.fill_all();\n
	 * Police police3;\n
	 * police3.draw_all();\n
	 * police3.fill_all();\n
	 * police3.contour_rouge_all();\n
	 * si on avait voulu avoir 3 instances de Polices
	*/

	return 0;
}


