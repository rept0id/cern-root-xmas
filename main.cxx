#include <vector>
#include <string>

// CERN ROOT
#include <TF1.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TObjArray.h>
#include <TROOT.h>
#include <TApplication.h>
#include "TRootCanvas.h"

/*** * * ***/

// interpreted
bool interpreted;

// canvas

TCanvas *canvas;

// TF Definitions

struct TFDefLine {
    int color;
    int width;
};

struct TFDefX {
    double min;
    double max;
};

struct TFDef {
    std::string name;
    std::string formula;
    TFDefLine line;
    TFDefX x;
};

std::vector<TFDef> tfsDefs;

/*** * * ***/

void canvasInit() {
    TF1 *canvasInitTF;

    /*** * * ***/

    canvas->cd();

    /*** * * ***/

    canvasInitTF = new TF1("f", "x*cos(x)", 0, 1000);
    canvasInitTF->SetLineWidth(0);
    canvasInitTF->DrawCopy();

    /*** * * ***/

    delete canvasInitTF;

    /*** * * ***/

    canvas->Update();
}

/*** * * ***/

int main(int argc, char** argv) {
    TApplication app("App", &argc, argv);

    // canvas

    canvas = new TCanvas("canvas", "Plot of f(x) = x * sin(x)", 842, 595);
    canvas->Connect("Closed()", "TCanvas", canvas, "Delete()");

    // TF Definitions

    tfsDefs = {
        {"decoration1", "(x*cos(x)) * 1.01", {kViolet, 3}, {0, 1000}},
        {"decoration2", "(x*cos(x)) / 1.99", {kAzure, 3}, {0, 1000}},
        {"leaves1", "x*cos(x)", {kGreen, 3}, {0, 1000}},
        {"leaves2", "(x*sin(x)) * -1", {kGreen, 1}, {0, 1000}},
        {"leaves3", "(x*cos(x)) / 2", {kGreen, 8}, {0, 1000}},
        {"branches1", "(x*cos(x))", {kGray, 1}, {0, 1000}},
        {"trunk1", "(x*cos(x)) / 10", {kWhite, 8}, {0, 1000}},
        {"trunk2", "1", {kGray, 1}, {0, 1000}},
        {"hat1Part1", "x*cos(x)", {kGray, 8}, {0, 20}},
        {"hat1Part2", "x*cos(x)", {kRed, 8}, {20, 70}},
        {"hat1Part3", "x*cos(x)", {kGray, 8}, {70, 90}}
    };

    /*** * * ***/

    canvasInit();

    for (const TFDef tfDef : tfsDefs) {
        TF1* tf;

        /*** * * ***/

        tf = new TF1(
            tfDef.name.c_str(),
            tfDef.formula.c_str(),
            tfDef.x.min,
            tfDef.x.max
        );

        tf->SetLineColor(tfDef.line.color);
        tf->SetLineWidth(tfDef.line.width);

        // tf->ResetBit(kMustCleanup);
        // tf->ResetBit(kCanDelete);

        /*** * * ***/

        canvas->cd();
        tf->DrawCopy("SAME");

        /*** * * ***/

        delete tf;

        /*** * * ***/

        canvas->Update();
    }

    canvas->SaveAs("res.pdf");

    /*** * * ***/

    app.Run();

    /*** * * ***/

    return 0;
}
