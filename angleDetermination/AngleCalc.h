#include <TLorentzVector.h>
#include <iostream>
#ifndef AngleCalc_H
#define AngleCalc_H

using namespace std;

class AngleCalc {
public:
	/*vector <float> costheta_dt;
	vector <float> phi_dt;
	vector <Double_t> costheta_cs;
	vector <Double_t> costheta_he;
	vector <float> phi_cs;
	vector <float> phi_he;*/
	float phi_he;
	float phi_cs;
	float ct_he;
	float ct_cs;
	float ct_dt;
	float phi_dt;
	void AngleCalculator_DT(TLorentzVector v1, TLorentzVector v2); // both phi and costheta
};
#endif
void AngleCalc::AngleCalculator_DT(TLorentzVector v4, TLorentzVector v5)

{


	//TLorentzVector v4;
	//TLorentzVector v5;
	//TLorentzVector pa(1.,0.,0,1); // projectile
	//TLorentzVector pb(1.,0., 0,-1); // target
	TLorentzVector pa(0., 0., 1., 1.); // projectile
	TLorentzVector pb(0., 0., -1., 1); // target

	Double_t px1 = v4.Px();
	Double_t py1 = v4.Py();
	Double_t pz1 = v4.Pz();



	Double_t px2 = v5.Px();
	Double_t py2 = v5.Py();
	Double_t pz2 = v5.Pz();



	//Unnormalized Q
	TLorentzVector Q;
	Q = v4 + v5;

	//printing the Q the sum

	/*cout << "Q = {"
		<< Q.Px() << ", "
		<< Q.Py() << ", "
		<< Q.Pz() << ", "
		<< Q.E()
		<< "}" << endl;*/

	//Compute mass, Pt and rapidity of the dilepton system
	//calculate Accoplanarity Angle

	//calculate z;
	TLorentzVector z;
	Double_t part1, part2;


	//Dot product: v1*v2 = t1*t2-x1*x2-y1*y2-z1*z2

	part1 = Q.Dot(pb);
	part2 = Q.Dot(pa);

	//cout << part1+part2 << endl;

	Double_t part3x = pa.X() * part1;
	Double_t part3y = pa.Y() * part1;
	Double_t part3z = pa.Z() * part1;
	Double_t part3e = pa.T() * part1;

	Double_t part4x = pb.X() * part2;
	Double_t part4y = pb.Y() * part2;
	Double_t part4z = pb.Z() * part2;
	Double_t part4e = pb.T() * part2;

	TLorentzVector part3(TVector3(part3x, part3y, part3z), part3e);
	TLorentzVector part4(TVector3(part4x, part4y, part4z), part4e);

	// Q=Q; pb=Pbar; pa=P; from paper

	//Un-normalized Z
	z = part3 - part4;

	//Normalized z
	//Float_t normz = TMath::Sqrt(-z * z);
	Double_t normz = TMath::Sqrt(-z.Dot(z));
	Double_t znx = z.X() / normz;
	Double_t zny = z.Y() / normz;
	Double_t znz = z.Z() / normz;
	Double_t zne = z.E() / normz;

	//Normalized z
	TLorentzVector zhat(TVector3(znx, zny, znz), zne);

	/*cout << "Normalized hatZ 4-Vector = {"
		<< zhat.Px() << ", "
		<< zhat.Py() << ", "
		<< zhat.Pz() << ", "
		<< zhat.E()
		<< "}" << endl;

	cout << "This is Zhat. Dot(Q): " << Q.Dot(zhat) << endl;
	cout << "HatZ Checking Mangnitude ( Normalization):" << zhat.Mag2() << endl;*/
	// calculate x
	TLorentzVector x;

	Double_t constant1 = (Q.Dot(Q)) / (2 * (Q.Dot(pa)));
	Double_t constant2 = (Q.Dot(Q)) / (2 * (Q.Dot(pb)));

	Double_t comp1x = pa.X() * constant1;
	Double_t comp1y = pa.Y() * constant1;
	Double_t comp1z = pa.Z() * constant1;
	Double_t comp1e = pa.T() * constant1;

	TLorentzVector comp1(TVector3(comp1x, comp1y, comp1z), comp1e);

	Double_t comp2x = pb.X() * constant2;
	Double_t comp2y = pb.Y() * constant2;
	Double_t comp2z = pb.Z() * constant2;
	Double_t comp2e = pb.T() * constant2;

	TLorentzVector comp2(TVector3(comp2x, comp2y, comp2z), comp2e);

	//Un-normalized x
	x = Q - comp1 - comp2;
	//normalize x
	Double_t normx = TMath::Sqrt(-x * x);
	Double_t xnx = x.X() / normx;
	Double_t xny = x.Y() / normx;
	Double_t xnz = x.Z() / normx;
	Double_t xne = x.E() / normx;

	//Normalized x
	TLorentzVector xhat(TVector3(xnx, xny, xnz), xne);


	// calculate y
	//TLorentzVector y;
	Double_t yone = pa.Y() * pb.Z() * Q.E() - pa.Z() * pb.Y() * Q.E() + pa.Z() * pb.E() * Q.Y() + pa.E() * pb.Y() * Q.Z() - pa.Y() * pb.E() * Q.Z() - pa.E() * pb.Z() * Q.Y();
	Double_t ytwo = -pa.Z() * pb.E() * Q.X() + pa.Z() * pb.X() * Q.E() - pa.X() * pb.Z() * Q.E() + pa.X() * pb.E() * Q.Z() - pa.E() * pb.X() * Q.Z() + pa.E() * pb.Z() * Q.X();
	Double_t ythree = pa.X() * pb.Y() * Q.E() - pa.Y() * pb.X() * Q.E() + pa.Y() * pb.E() * Q.X() - pa.X() * pb.E() * Q.Y() + pa.E() * pb.X() * Q.Y() - pa.E() * pb.Y() * Q.X();
	Double_t yfour = -pa.X() * pb.Y() * Q.Z() + pa.X() * pb.Z() * Q.Y() - pa.Z() * pb.X() * Q.Y() + pa.Z() * pb.Y() * Q.X() - pa.Y() * pb.Z() * Q.X() + pa.Y() * pb.X() * Q.Z();

	//Un-normalized y
	TLorentzVector y(TVector3(yone, ytwo, ythree), yfour);

	//normalize y
	Double_t normy = TMath::Sqrt(-y * y);
	Double_t ynx = y.X() / normy;
	Double_t yny = y.Y() / normy;
	Double_t ynz = y.Z() / normy;
	Double_t yne = y.E() / normy;

	//normalized y
	TLorentzVector yhat(TVector3(ynx, yny, ynz), yne);

	//Lepton momentum difference
	TLorentzVector diff;
	diff = (v5 - v4);
	Double_t diff2x = diff.X() / 2.;
	Double_t diff2y = diff.Y() / 2.;
	Double_t diff2z = diff.Z() / 2.;
	Double_t diff2e = diff.E() / 2.;
	TLorentzVector diff2(TVector3(diff2x, diff2y, diff2z), diff2e);

	//cout << "Lepton Momemtum Difference = {" << diff2.Px() << ", " << diff2.Py() << ", " << diff2.Pz() << ", " << diff2.E() << "}" << endl;

	//Normalize diff2
	Double_t norm2 = TMath::Sqrt(-diff2 * diff2);

	Double_t diff3x = diff2.X() / norm2;
	Double_t diff3y = diff2.Y() / norm2;
	Double_t diff3z = diff2.Z() / norm2;
	Double_t diff3e = diff2.E() / norm2;

	TLorentzVector diff3(TVector3(diff3x, diff3y, diff3z), diff3e);

	//computing the angles
	float cosThetaCS = zhat * diff3;
	float SinThetaCosPhiCS = xhat * diff3;
	float SinThetaSinPhiCS = yhat * diff3;
	//**************************************

  //Check that the CS frame was built correctly
  //cout << "for Q "<< endl;
  //cout << Q.Dot(x) << "--" << Q.Dot(y)  << "--" << Q.Dot(z) << endl;
  //cout << "for x y and z"<< endl;
  //cout << x.Dot(y) <<"--" << y.Dot(z)  << "--"  << x.Dot(z) << endl;


	float phi = atan2(SinThetaSinPhiCS, SinThetaCosPhiCS);
	if (phi >= 0) { phi = phi; }
	if (phi < 0) { phi = phi + 2 * TMath::Pi(); }

	//Make an ASCII fi  le as output

	if (isnan(cosThetaCS)) {
		cosThetaCS = 0.0;
	}

	if (isnan(phi)) {
		phi = 0.0;
	}
	ct_dt = cosThetaCS;
	phi_dt = phi;

}