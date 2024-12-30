#include <TCanvas.h>
#include <TGraph.h>
#include <TF1.h>
#include <TRandom.h>
#include <TMath.h>

/*** * * ***/

struct typePlotLine {
    int color;
    int width;
};

struct typePlotX {
    double min;
    double max;
};

struct typePlot {
    std::string name;
    std::string formula;
    typePlotLine line;
    typePlotX x;
};

int main() {
    // canvas

    TCanvas *canvas;

    // canvas : init
    // canvas : init : plot
    TF1 *canvasInitPlot;

    // canvas : plots
    std::vector<typePlot> plots;

    /*** * * ***/

    // canvas

    canvas = new TCanvas("canvas", "Plot of f(x) = x * sin(x)", 800, 600);

    // canvas : init
    // canvas : init : plot
    canvasInitPlot = new TF1("f", "x*cos(x)", 0, 1'000);
    canvasInitPlot->SetLineWidth(0);
    canvasInitPlot->Draw(); // all the rest drawnings need to be called with "SAME"

    // canvas : plots

    plots = {
        // decoration
        {"decoration1", "(x*cos(x)) * 1.01", {kViolet, 3}, {0, 1000}}, // decoration of leaves group A
        {"decoration2", "(x*cos(x)) / 1.99", {kAzure, 3}, {0, 1000}}, // decoration of leaves group C
        // leaves
        {"leaves1", "x*cos(x)", {kGreen, 3}, {0, 1000}}, // leaves group A
        {"leaves2", "(x*sin(x)) * -1", {kGreen, 1}, {0, 1000}}, // leaves group B
        {"leaves3", "(x*cos(x)) / 2", {kGreen, 8}, {0, 1000}}, // leaves group C
        // branches
        {"branches1", "(x*cos(x))", {kGray, 1}, {0, 1000}},
        // trunk
        {"trunk1", "(x*cos(x)) / 10", {kWhite, 8}, {0, 1000}},
        {"trunk2", "1", {kGray, 1}, {0, 1000}},
        // hat
        {"hat1Part1", "x*cos(x)", {kGray, 8}, {0, 20}},
        {"hat1Part2", "x*cos(x)", {kRed, 8}, {20, 70}},
        {"hat1Part3", "x*cos(x)", {kGray, 8}, {70, 90}}
    };

    /*** * * ***/

    // canvas

    // canvas : plots

    for (const auto& plot : plots) {
        TF1* f = new TF1(
            plot.name.c_str(),
            plot.formula.c_str(),
            plot.x.min,
            plot.x.max
        );

        f->SetLineColor(plot.line.color);
        f->SetLineWidth(plot.line.width);

        f->Draw("SAME");
    }

    // canvas : update

    canvas->Update();

    /*** * * ***/

    return 0;
}
