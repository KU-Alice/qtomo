// compare_angles_normalized.cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cctype>

#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TMath.h"

// --------- helpers ---------
static void trim(char* s) {
    char* p = s;
    while (*p && std::isspace(static_cast<unsigned char>(*p))) ++p;
    if (p != s) std::memmove(s, p, std::strlen(p) + 1);
    size_t n = std::strlen(s);
    while (n > 0 && std::isspace(static_cast<unsigned char>(s[n - 1]))) --n;
    s[n] = '\0';
}

static std::vector<double> load_values(const char* path) {
    std::vector<double> out;
    FILE* f = std::fopen(path, "r");
    if (!f) { std::cerr << "Error: cannot open " << path << "\n"; return out; }
    char line[4096];
    while (std::fgets(line, sizeof(line), f)) {
        trim(line);
        if (!line[0] || line[0] == '#') continue;
        for (char* c = line; *c; ++c) if (*c == ',') *c = ' ';
        char* p = line; char* endp = 0;
        double x = std::strtod(p, &endp);
        if (endp != p) out.push_back(x);
    }
    std::fclose(f);
    return out;
}

static TH1D* make_hist(const std::vector<double>& data,
    const char* name, const char* title,
    int bins, double xmin, double xmax)
{
    TH1D* h = new TH1D(name, title, bins, xmin, xmax);
    h->Sumw2(false);
    for (size_t i = 0; i < data.size(); ++i) h->Fill(data[i]);
    return h;
}

static void style_hist(TH1D* h, int line, int fill) {
    h->SetLineColor(line);
    h->SetLineWidth(2);
    h->SetFillColorAlpha(fill, 0.35);
}

static void compare_angles(const char* cos_before_file,
    const char* cos_after_file,
    const char* phi_before_file,
    const char* phi_after_file,
    int bins)
{
    gStyle->SetOptStat(0);

    std::vector<double> cos_before = load_values(cos_before_file);
    std::vector<double> cos_after = load_values(cos_after_file);
    std::vector<double> phi_before = load_values(phi_before_file);
    std::vector<double> phi_after = load_values(phi_after_file);

    std::cout << "Loaded cosθ before: " << cos_before.size() << " from " << cos_before_file << "\n";
    std::cout << "Loaded cosθ after : " << cos_after.size() << " from " << cos_after_file << "\n";
    std::cout << "Loaded φ before   : " << phi_before.size() << " from " << phi_before_file << "\n";
    std::cout << "Loaded φ after    : " << phi_after.size() << " from " << phi_after_file << "\n";

    const bool kNormalize = true;
    const bool kLogY = false;
    const int  rebin = 1;

    // ---- cos(theta) ----
    const double cmin = -1.0, cmax = 1.0;
    TH1D* hC_before = make_hist(cos_before, "hC_before", "cos(#theta);cos(#theta);Events", bins, cmin, cmax);
    TH1D* hC_after = make_hist(cos_after, "hC_after", "cos(#theta);cos(#theta);Events", bins, cmin, cmax);
    if (rebin > 1) { hC_before->Rebin(rebin); hC_after->Rebin(rebin); }

    style_hist(hC_before, kBlue + 1, kAzure + 1);
    style_hist(hC_after, kRed + 1, kPink - 4);

    if (kNormalize) {
        double i1 = hC_before->Integral("width");
        double i2 = hC_after->Integral("width");
        if (i1 > 0) hC_before->Scale(1.0 / i1);
        if (i2 > 0) hC_after->Scale(1.0 / i2);
        hC_before->GetYaxis()->SetTitle("Probability density");
    }
    else {
        hC_before->GetYaxis()->SetTitle("Events");
    }

    double ymaxC = std::max(hC_before->GetMaximum(), hC_after->GetMaximum());
    hC_before->SetMaximum(ymaxC * 1.25);
    hC_before->SetMinimum(0);

    TCanvas* c1 = new TCanvas("c1", "cos(theta) comparison", 900, 650);
    if (kLogY) c1->SetLogy();
    hC_before->Draw("HIST");
    hC_after->Draw("HIST SAME");
    TLegend* leg1 = new TLegend(0.65, 0.75, 0.88, 0.88);
    leg1->AddEntry(hC_before, "Before", "f");
    leg1->AddEntry(hC_after, "After", "f");
    leg1->SetBorderSize(0);
    leg1->Draw();
    c1->SaveAs("cosTheta_comparison_hist.png");

    // ---- phi ----
    const double pmin = 0.0, pmax = TMath::TwoPi();
    TH1D* hP_before = make_hist(phi_before, "hP_before", "#phi;#phi (radians);Events", bins, pmin, pmax);
    TH1D* hP_after = make_hist(phi_after, "hP_after", "#phi;#phi (radians);Events", bins, pmin, pmax);
    if (rebin > 1) { hP_before->Rebin(rebin); hP_after->Rebin(rebin); }

    style_hist(hP_before, kBlue + 1, kAzure + 1);
    style_hist(hP_after, kRed + 1, kPink - 4);

    if (kNormalize) {
        double i1 = hP_before->Integral("width");
        double i2 = hP_after->Integral("width");
        if (i1 > 0) hP_before->Scale(1.0 / i1);
        if (i2 > 0) hP_after->Scale(1.0 / i2);
        hP_before->GetYaxis()->SetTitle("Probability density");
    }
    else {
        hP_before->GetYaxis()->SetTitle("Events");
    }

    double ymaxP = std::max(hP_before->GetMaximum(), hP_after->GetMaximum());
    hP_before->SetMaximum(ymaxP * 1.25);
    hP_before->SetMinimum(0);

    TCanvas* c2 = new TCanvas("c2", "phi comparison", 900, 650);
    if (kLogY) c2->SetLogy();
    hP_before->Draw("HIST");
    hP_after->Draw("HIST SAME");
    TLegend* leg2 = new TLegend(0.65, 0.75, 0.88, 0.88);
    leg2->AddEntry(hP_before, "Before", "f");
    leg2->AddEntry(hP_after, "After", "f");
    leg2->SetBorderSize(0);
    leg2->Draw();
    c2->SaveAs("phi_comparison_hist.png");

    std::cout << "Saved normalized histograms: cosTheta_comparison_hist.png, phi_comparison_hist.png\n";
}


// --------- plotting (AFTER only) ---------
static void plot_angles_after(const char* cos_after_file,
    const char* phi_after_file,
    int bins)
{
    gStyle->SetOptStat(0);

    std::vector<double> cos_after = load_values(cos_after_file);
    std::vector<double> phi_after = load_values(phi_after_file);

    std::cout << "Loaded cosθ (after): " << cos_after.size() << " from " << cos_after_file << "\n";
    std::cout << "Loaded φ (after)   : " << phi_after.size() << " from " << phi_after_file << "\n";

    const bool kNormalize = true;
    const bool kLogY = false;
    const int  rebin = 1;

    // ---- cos(theta) ----
    const double cmin = -1.0, cmax = 1.0;
    TH1D* hC_after = make_hist(cos_after, "hC_after", "cos(#theta);cos(#theta);Events", bins, cmin, cmax);
    if (rebin > 1) hC_after->Rebin(rebin);

    style_hist(hC_after, kBlue + 1, kAzure + 1);

    if (kNormalize) {
        double i = hC_after->Integral("width");
        if (i > 0) hC_after->Scale(1.0 / i);
        hC_after->GetYaxis()->SetTitle("Probability density");
    }
    else {
        hC_after->GetYaxis()->SetTitle("Events");
    }

    hC_after->SetMaximum(hC_after->GetMaximum() * 1.25);
    hC_after->SetMinimum(0);

    TCanvas* c1 = new TCanvas("c1", "cos(theta)", 900, 650);
    if (kLogY) c1->SetLogy();
    // Clean title: no before/after wording
    hC_after->SetTitle("cos(#theta);cos(#theta);Probability density");
    hC_after->Draw("HIST");
    c1->SaveAs("cosTheta_hist.png");

    // ---- phi ----
    const double pmin = 0.0, pmax = TMath::TwoPi();
    TH1D* hP_after = make_hist(phi_after, "hP_after", "#phi;#phi (radians);Events", bins, pmin, pmax);
    if (rebin > 1) hP_after->Rebin(rebin);

    style_hist(hP_after, kRed + 1, kPink - 4);

    if (kNormalize) {
        double i = hP_after->Integral("width");
        if (i > 0) hP_after->Scale(1.0 / i);
        hP_after->GetYaxis()->SetTitle("Probability density");
    }
    else {
        hP_after->GetYaxis()->SetTitle("Events");
    }

    hP_after->SetMaximum(hP_after->GetMaximum() * 1.25);
    hP_after->SetMinimum(0);

    TCanvas* c2 = new TCanvas("c2", "phi", 900, 650);
    if (kLogY) c2->SetLogy();
    // Clean title: no before/after wording
    hP_after->SetTitle("#phi;#phi (radians);Probability density");
    hP_after->Draw("HIST");
    c2->SaveAs("phi_hist.png");

    std::cout << "Histograms Saved!!";
}
