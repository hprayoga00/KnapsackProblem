#include<iostream>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

float objectivefunction(int nilai, int berat) {
	return nilai*1.0 / berat;
}

void main() {
	srand(time(0));
	string fileName;
	cout << "Masukkan nama file : ";
	cin >> fileName;
	ifstream file;
	file.open(fileName);
	if (file.is_open()) {
		// get isi file
		int jumBenda, kapasitas;
		file >> jumBenda;
		file >> kapasitas;
		int** data = new int*[jumBenda];
		for (int i = 0; i < jumBenda; i++) {
			data[i] = new int[3];
		}
		for (int i = 0; i < jumBenda; i++) {
			file >> data[i][0]; //nilai
			file >> data[i][1]; //berat
			data[i][2] = 0; // belum diambil
		}

		// declare tas
		int** knapsack = new int*[jumBenda];
		for (int i = 0; i < jumBenda; i++) {
			knapsack[i] = new int[3];
		}

		// hill climbing
		// ke random start
		int start = rand() % jumBenda; 
		//int start = 3;
		cout << start << endl;
		int beratTas = 0;
		int semuaItemValue = 0; // sebagai objective function dari semua item
		int jumlahIsiTas = 0;
		for (int i = start; i < jumBenda && beratTas < kapasitas; i++) {
			if (data[i][1] + beratTas <= kapasitas) {
				knapsack[jumlahIsiTas][0] = data[i][0]; //nilai
				knapsack[jumlahIsiTas][1] = data[i][1]; //berat
				knapsack[jumlahIsiTas][2] = i; // index
				beratTas += data[i][1];
				semuaItemValue += data[i][0];
				data[i][2] = 1; // dimasukkan ke dalam tas
				jumlahIsiTas++;
			}
		}
		for (int i = 0; i < jumlahIsiTas; i++) {
			cout << knapsack[i][0] << " " << knapsack[i][1] << " " << endl;
		}

		// climbing
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < jumlahIsiTas; i++) {
				for (int j = 0; j < jumBenda; j++) {
					if (data[j][2] == 0) {
						int kapasitasBaru = beratTas - knapsack[i][1] + data[j][1];
						if (kapasitasBaru <= kapasitas) {
							int semuaItemValueBaru = semuaItemValue - knapsack[i][0] + data[j][0];
							if (semuaItemValueBaru > semuaItemValue) {
								if (objectivefunction(knapsack[i][0], knapsack[i][1]) < objectivefunction(data[j][0], data[j][1])) {
									knapsack[i][0] = data[j][0];
									knapsack[i][1] = data[j][1];
									data[knapsack[i][2]][2] = 0;
									data[j][2] = 1;
									semuaItemValue = semuaItemValueBaru;
									beratTas = kapasitasBaru;
								}						
							}
						}
					}
				}
			}
		}

		cout << "Hasil : " << endl;

		ofstream outputFile;
		outputFile.open("knapsackOutput.txt");
		outputFile << semuaItemValue << " " << beratTas << "\n";
		for (int i = 0; i < jumBenda; i++) {
			outputFile << data[i][2] << endl;
		}
		outputFile.close();
		cout << semuaItemValue << " " << beratTas << endl;
		file.close();
	}
	else {
		cout << "File Doesn't Exist" << endl;
	}
}