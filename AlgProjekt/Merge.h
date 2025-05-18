/**
 * @file Merge.h
 * @author Filip Štegner
 * @brief Definice funkce pro slévání k seřazených polí čísel do jednoho seřazeného pole.
 */
#pragma once
#include <cstdarg>

//
//	Algoritmus jsem vymyslel sám.
//
/**
 * Slévá k seřazených polí čísel do jednoho seřazeného pole.
 * @param arrays Pole seřazených polí.
 * @param sizes Pole velikostí jednotlivých polí.
 * @param k Počet polí. k >= 2 && k <= 100
 * @return Seřazené pole čísel.
*/
int* merge(int** arrays, int* sizes, int k);

// V této funkci se používá variadic arguments (va_list) pro předání proměnného počtu argumentů.
// Zdroj: https://en.cppreference.com/w/cpp/utility/variadic
// Tuto funkci jsem použil pro testování.
/**
 * Slévá k seřazených polí čísel do jednoho seřazeného pole. (Testovací funkce)
 * @param k Počet polí. k >= 2 && k <= 100
 * @param ... zapsané pole ve formátu "<pole>, <počet prvků v poli>, <pole>, <počet prvků v poli>, ..."
 * @return Seřazené pole čísel.
*/
int* merge_va(const int k, ...);