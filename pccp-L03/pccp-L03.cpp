// pccp-L03.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "stdafx.h"
#include <string>  
#include <iostream> 
#include <fstream>
#include <vector>
#include "stdlib.h" 
#include <ctime>
#include <fstream>
#include <random>
#include <sstream>      // std::istringstream
#include <iterator>     // std::istream_iterator

using namespace std;

// for splitting string by commas
class WordDelimitedByCommas : public std::string
{};
// overload of operator to read until next comma
std::istream& operator >> (std::istream& is, WordDelimitedByCommas& output) {
	std::getline(is, output, ',');
	return is;
}
//return random char
char genRandom() {
	static const char alphanum[] =
		"0123456789"
		"!@#$%^&*"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	int stringLength = sizeof(alphanum) - 1;
	return alphanum[rand() % stringLength];
}

void printHelp() {
	cout << "mmDistPt.exe -i fileName -[h] [-v] -[w] [-p] [-g n,dx,dy,dz]" << endl;
	cout << "options:" << endl;
	cout << "    -i set the filename with the points. If -f option is set a new dataset is generated with this name" << endl;
	cout << "    -h \tprints help" << endl;
	cout << "    -v \tactivate additional outputs" << endl;
	cout << "    -w \twait before ending the programm for key press" << endl;
	cout << "    -p \tshow processing time" << endl;
	cout << "    -g  n,dx,dy,dz geneartes a new random dataset with n points and max. dx,dy,dz coordinates" << endl;
}

void generateRandomPointsAndWriteToFile(int numPoints, int dx, int dy, int dz) {

	ofstream myfile;
	myfile.open("cpp03.txt", ios::out);
	/* initialize random seed: */
	srand(time(NULL));

	//generates random coordinates from 0 to dx,dy and dz respectively
	for (int i = 0; i < numPoints; i++) {
		float rnd_x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/dx);
		float rnd_y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/dy);
		float rnd_z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/dz);

		//use random string as point identifier
		std::string Str;
		for (int z = 0; z < 10; z++)
		{
			Str += genRandom();
		}

		//writes random points with point identifier to file
		myfile << Str << ", " << rnd_x << ", " << rnd_y << ", " << rnd_z <<std::endl;
		Str = ' ';
	}
	myfile.close();
}


void openFileAndDoMinDistCalc() {

}

int main(int argc, char* argv[])
{
	bool printProcesTime = false;
	bool extendedOutput = false;
	bool waitBeforeTerminate = false;
	string filePath;
	int n;
	float dx, dy, dz;
	clock_t processTime;
	std::istringstream iss;


	if (argc < 2) {
		printHelp();
		return 0;
	}

	//handle input arguments
	for (int i = 1; i < argc; i++) {
		try {
			string argument = argv[i];

			if (argument == "-i") {
				filePath = argv[i + 1];
				i++;
			}

			else if (argument == "-g") {
				string temp = argv[i + 1];
				cout << temp << endl;
				//TODO split string by , and convert to n;dx,dy,dz
				std::istringstream iss(temp);
				std::vector<std::string> results((std::istream_iterator<WordDelimitedByCommas>(iss)),
					std::istream_iterator<WordDelimitedByCommas>());
			
				int _n = std::stoi(results[0]);
				int _dx = std::stoi(results[1]);
				int _dy = std::stoi(results[2]);
				int _dz = std::stoi(results[3]);

				generateRandomPointsAndWriteToFile(_n,_dx,_dy,_dz);
				i++;
		
			}
			else if (argument == "-h") {
				printHelp();
				break;
			}
			else if (argument == "-p") {
				printProcesTime = true;
			}
			else if (argument == "-v") {
				extendedOutput = true;
			}
			else if (argument == "-w") {
				waitBeforeTerminate = true;
			}
			else {
				cout << "unknown argument: " << argv[i] << endl;
			}
		}
		catch (exception e) {
			fprintf(stderr, "Error: in interpreting arguments %s \n", argv[i]);
		}

	}

	//start measuring process time if wanted
	if (printProcesTime) {
		processTime = clock();
	}

	//TODO place code here


	//print process time
	if (printProcesTime) {
		processTime = clock() - processTime;
		double time_taken = ((double)processTime) / CLOCKS_PER_SEC; // in seconds
		printf("\nThe process took %f seconds to execute \n\n", time_taken);
	}

	if (extendedOutput) {
		cout << "extended output" << endl;
	}

	//wait for input before exit
	if (waitBeforeTerminate) {
		cout << "Press any key to exit...";
		_getch();
	}


	return 0;
}

