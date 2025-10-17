/*
   This file automatically generates the sample events and save them
   Created By: Daniel Tapia Takaki, Pramil Paudel
   @University of Kansas
   Kansas, USA
*/

#include <cmath>
#include <fstream>
#include <random>
#include <string>
#include <iostream>
#include <iomanip>

inline double PI() { return std::acos(-1.0); }

struct Angles { double ctheta; double phi; };

inline Angles sample_angles(std::mt19937_64& gen,
    std::uniform_real_distribution<double>& Ucos,
    std::uniform_real_distribution<double>& Uphi)
{
    Angles a;
    a.ctheta = Ucos(gen);
    a.phi = Uphi(gen);
    return a;
}

inline void vec_from_angles(double pabs, double ctheta, double phi,
    double& px, double& py, double& pz)
{
    const double stheta = std::sqrt(std::max(0.0, 1.0 - ctheta * ctheta));
    px = pabs * stheta * std::cos(phi);
    py = pabs * stheta * std::sin(phi);
    pz = pabs * ctheta;
}

inline void GenerateIsotropicEvents(
    int N, double p, double m,
    const std::string& events_file = "events.csv",
    const std::string& cosTheta_file = "cosTheta.csv",
    const std::string& phi_file = "phi.csv",
    unsigned long long seed = std::random_device{}())
{
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> Ucos(-1.0, 1.0);     // for cosθ
    std::uniform_real_distribution<double> Uphi(0.0, 2.0 * PI()); // for φ

    std::ofstream fev(events_file.c_str());
    std::ofstream fct(cosTheta_file.c_str());
    std::ofstream fph(phi_file.c_str());
    if (!fev || !fct || !fph) {
        std::cerr << "Error: could not open output file(s)\n";
        return;
    }

    fev.setf(std::ios::fixed); fev << std::setprecision(10);
    fct.setf(std::ios::fixed); fct << std::setprecision(10);
    fph.setf(std::ios::fixed); fph << std::setprecision(10);

    const double E = std::sqrt(p * p + m * m);

    for (int i = 0; i < N; ++i) {
        // particle 1
        Angles a1 = sample_angles(rng, Ucos, Uphi);
        double px1, py1, pz1;
        vec_from_angles(p, a1.ctheta, a1.phi, px1, py1, pz1);

        // particle 2
        Angles a2 = sample_angles(rng, Ucos, Uphi);
        double px2, py2, pz2;
        vec_from_angles(p, a2.ctheta, a2.phi, px2, py2, pz2);

        // event file: only 4-vectors
        fev << px1 << ", " << py1 << ", " << pz1 << ", " << E << ", "
            << px2 << ", " << py2 << ", " << pz2 << ", " << E << "\n";

        // save cos(theta) and phi
        fct << a1.ctheta << "\n";
        fct << a2.ctheta << "\n";

        fph << a1.phi << "\n";
        fph << a2.phi << "\n";
    }

    std::cout << "Generated " << N << " isotropic events.\n"
        << "  -> events   : " << events_file << "\n"
        << "  -> cosTheta : " << cosTheta_file << "  (range -1 to 1)\n"
        << "  -> phi      : " << phi_file << "  (range 0 to ~6.283)\n";
}