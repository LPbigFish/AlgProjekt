/**
 * @file merge.cpp
 * @author Filip Štegner
 * @brief Implementace funkce pro slévání k seřazených polí čísel do jednoho seřazeného pole.
 */


#include "Merge.h"
//
//	Algoritmus jsem vymyslel sám skrz logické bádání.
//	Časovou složitost jsem vypočítal N * k ve všech případech. Ale protože k není nikdy vyšší jak 100, dá se říct, že se jedná o lineární algoritmus O ( N ).
//
/**
 * Slévá k seřazených polí čísel do jednoho seřazeného pole.
 * @param arrays Pole seřazených polí.
 * @param sizes Pole velikostí jednotlivých polí.
 * @param k Počet polí. k >= 2 && k <= 100
 * @return Seřazené pole čísel.
*/
int* merge(int** arrays, int* sizes, const int k)
{
	int sum_of_sizes = 0;
	for (int i = 0; i < k; i++) {
		sum_of_sizes += sizes[i];
	}

	int* ptrs = new int[k] {0};
	int* result = new int[sum_of_sizes];

	// 0..sum_of_sizes - 1
	for (int result_pointer = 0; result_pointer < sum_of_sizes; result_pointer++) {
		// index nejnižšího prvku
		int min_id = -1;

		for (int i = 0; i < k; i++) {
			if (sizes[i] > ptrs[i]) {
				if (min_id < 0 || arrays[min_id][ptrs[min_id]] > arrays[i][ptrs[i]]) {
					min_id = i;
				}
			}
		}

		if (min_id < 0) {
			break;
		}

		result[result_pointer] = arrays[min_id][ptrs[min_id]];
		ptrs[min_id]++;
	}

	delete[] ptrs;

	return result;
}

// V této funkci se používá variadic arguments (va_list) pro předání proměnného počtu argumentů.
// Zdroj: https://en.cppreference.com/w/cpp/utility/variadic
// Tuto funkci jsem použil pro testování.
/**
 * Slévá k seřazených polí čísel do jednoho seřazeného pole. (Testovací funkce)
 * @param k Počet polí. k >= 2 && k <= 100
 * @param ... zapsané pole ve formátu "<pole>, <počet prvků v poli>, <pole>, <počet prvků v poli>, ..."
 * @return Seřazené pole čísel.
*/
int* merge_va(const int k, ...)
{
	va_list args;
	va_start(args, k);

	int** arrays = new int*[k];
	int* sizes = new int[k];

	for (int i = 0; i < k; i++) {
		arrays[i] = va_arg(args, int*);
		sizes[i] = va_arg(args, int);
	}
	va_end(args);

	int* result = merge(arrays, sizes, k);

	delete[] arrays;
	delete[] sizes;
	return result;
}


