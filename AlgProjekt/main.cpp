#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include "Merge.h"

using namespace std;

// Pro získání seznamu souborů v adresáři pro načtení
// https://www.geeksforgeeks.org/cpp-program-to-get-the-list-of-files-in-a-directory/
// https://www.baeldung.com/linux/list-files-using-c#the-c-way-1
namespace fs = filesystem;

int main(int argc, char** argv) {
	if (argc != 4) {
		cerr << "Usage: " << argv[0] << " <počet vstupních souborů> <directory> <název výstupního souboru>" << endl;
		return 1;
	}

	int k = stoi(argv[1]);
	if (k < 2 || k > 100) {
		cerr << "Invalid number of input files: " << argv[1] << endl;
		return 1;
	}

	const char* directory = argv[2];
	const char* output_name = argv[3];

	int** arrays = new int* [k];
	int* sizes = new int[k];

	try {
		for (fs::directory_entry const& entry : fs::directory_iterator(directory)) {
			static int i = 0;
			if (i >= k) {
				break;
			}

			if (!entry.is_regular_file()) {
				continue;
			}

			ifstream file(entry.path());
			if (!file) {
				cerr << "Error opening file: " << entry.path() << endl;
				delete[] arrays;
				delete[] sizes;
				return 2;
			}

			vector<int> numbers;
			string line;
			int number = 0;
			while (getline(file, line)) {
				number = stoi(line);
				numbers.push_back(number);
			}

			sizes[i] = numbers.size();
			arrays[i] = new int[sizes[i]];
			for (int j = 0; j < sizes[i]; j++) {
				arrays[i][j] = numbers[j];
			}
			i++;
		}

	}
	catch (const std::exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}

	// Slít
	int* merged = merge(arrays, sizes, k);

	if (merged == nullptr) {
		cerr << "Error merging arrays." << endl;
		for (int i = 0; i < k; i++) {
			delete[] arrays[i];
			arrays[i] = nullptr;
		}
		delete[] arrays;
		delete[] sizes;
		return 1;
	}

	// Zapsat data do souboru	
	ofstream output_file(output_name);
	if (!output_file) {
		cerr << "Error opening output file: " << output_name << endl;
		delete[] merged;
		for (int i = 0; i < k; i++) {
			delete[] arrays[i];
			arrays[i] = nullptr;
		}
		delete[] arrays;
		delete[] sizes;
		return 1;
	}

	int sum = 0;
	for (int i = 0; i < k; i++) {
		sum += sizes[i];
	}

	cout << endl << "Merged array:" << endl;
	for (int i = 0; i < sum; i++) {
		cout << merged[i] << endl;
		output_file << merged[i] << endl;
	}

	// Cleaning up
	for (int i = 0; i < k; i++) {
		delete[] arrays[i];
		arrays[i] = nullptr;
	}
	delete[] merged;
	delete[] arrays;
	delete[] sizes;

	return 0;
}