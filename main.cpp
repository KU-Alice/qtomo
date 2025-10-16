/*
   This file tells about angle calculation and shows how to use and call the system
   Created By: Daniel Tapia Takaki, Pramil Paudel
   @University of Kansas
   Kansas, USA
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include "AngleCalc.h"
#include "TLorentzVector.h"
#include "randomEventGenerator.cpp"
#include "anglePlotter.cpp"

struct Pair {
	std::array<double, 4> v1;
	std::array<double, 4> v2;
};

int runAngleCalculator(const char* fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Error: cannot open data.csv\n";
		return 1;
	}

	std::vector<Pair> pairs;
	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) continue;
		std::stringstream ss(line);
		Pair p;
		char c;
		if (ss >> p.v1[0] >> c >> p.v1[1] >> c >> p.v1[2] >> c >> p.v1[3]
			>> c >> p.v2[0] >> c >> p.v2[1] >> c >> p.v2[2] >> c >> p.v2[3]) {
			pairs.push_back(p);
		}
		else {
			std::cerr << "Skipping malformed line: " << line << "\n";
		}
	}
	file.close();
	std::ofstream cosOut("updated_theta_list.csv");
	std::ofstream phiOut("updated_phi_list.csv");
	if (!cosOut.is_open()) {
		std::cerr << "Error: cannot open cosTheta_list.txt\n";
		return 1;
	}
	if (!phiOut.is_open()) {
		std::cerr << "Error: cannot open cosTheta_list.txt\n";
		return 1;
	}

	AngleCalc calc;
	for (size_t i = 0; i < pairs.size(); ++i) {
		const auto& p = pairs[i];
		std::cout << "---- Pair " << i << " ----\n";
		std::cout << "v4 = (" << p.v1[0] << ", " << p.v1[1] << ", " << p.v1[2] << ", " << p.v1[3] << ")\n";
		std::cout << "v5 = (" << p.v2[0] << ", " << p.v2[1] << ", " << p.v2[2] << ", " << p.v2[3] << ")\n";
		TLorentzVector v4(p.v1[0], p.v1[1], p.v1[2], p.v1[3]);
		TLorentzVector v5(p.v2[0], p.v2[1], p.v2[2], p.v2[3]);
		calc.AngleCalculator_DT(v5, v4);

		std::cout << "cosTheta_CS = " << calc.ct_dt << "\n" << "phi_CS = " << calc.phi_dt << "\n\n";
		cosOut << std::setprecision(10) << calc.ct_dt << "\n";
		phiOut << std::setprecision(10) << calc.phi_dt << "\n";
	}
	cosOut.close();
	std::cout << "Saved cosTheta_CS values to phi_list.txt\n";

	const char* cos_before = "cos_theta_list.csv";
	const char* cos_after = "updated_theta_list.csv";
	const char* phi_before = "cos_phi_list.csv";
	const char* phi_after = "updated_phi_list.csv";
	const int   bins = 100;

	plot_angles_after(cos_after, phi_after, bins);
	compare_angles(cos_before, cos_after, phi_before, phi_after, bins);
	return 0;
}

void runFromShortSample() {
	runAngleCalculator("data.csv");
}

void generateSampleAndRun() {
	GenerateIsotropicEvents(10000, 50.0, 0.105658, "events.csv", "cos_theta_list.csv", "cos_phi_list.csv");
	runAngleCalculator("events.csv");
}

AngleCalc calculateAngle(TLorentzVector v4, TLorentzVector v5) {
	AngleCalc calc;
	calc.AngleCalculator_DT(v5, v4);
	return calc;
	
}

int main() {
	//Use this code to run inbuild examples from the code
	//runFromShortSample();
	//generateSampleAndRun();
	
	// You can pass your data as PX, PY, PZ, and E pair as following;
	// Just update the value and run the code.
	TLorentzVector v4(21.691, -12.223, -7.6778, 26.055);
	TLorentzVector v5(30.149, 27.176, -27.178, 48.848);
	AngleCalc calc = calculateAngle(v4, v5);
	std::cout << "Cos Theta CS = " << calc.ct_dt << "\n" << "Phi CS = " << calc.phi_dt << "\n\n";
	return 0;
}
