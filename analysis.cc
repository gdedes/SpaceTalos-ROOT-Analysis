// C++ includes
#include <iostream>
#include <stdexcept>
#include <string>


// ROOT includes
#include "TApplication.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TEnv.h"
#include "TError.h" 
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"

#include "TTree.h"
#include "TFile.h"


using namespace std;





int main(int argc, char **argv)
{
  // User settings:
  bool SPARTAN_xsecvalidation = false;    
  bool SPARTAN_LET = false;    
  bool FinFET_LET = true;    
  bool ATMEL_LET = false;    
  bool ATMEL_p_validation = false;
  bool SEU_multiplicity = false;
      
      
      
  //#################################################
  // root handling
  //#################################################
  TApplication theApp("App", &argc, argv);
  gROOT->Reset("a");

  // define the level of statistics display
  gStyle->SetOptStat( kFALSE );
  //gStyle->SetOptFit( 1111 );
  //gStyle->SetOptStat( 1111111 );  //adjust statistics box

  // some environment variables
  gStyle->SetPalette(1);
  gEnv->SetValue("TFile.Recover", 0); // if a file is corrupted we do not want ROOT trying to repair it
  TH1::AddDirectory( kFALSE );          // we do not want the histograms associated with a specific file

  // define for what kind of errors the application crashes
  //gErrorIgnoreLevel=kSysError;        
  gErrorIgnoreLevel = kError;


  
  try
    {
          
      if (SPARTAN_xsecvalidation){
            // open the ROOT file
            //TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-GEANT4-project/build/Output_p20MeV_SV2umelgammaproton_hadElasticbiasingLayerAbove_100M.root", "READ" ); //
            //TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-GEANT4-project/build-short/Output.root", "READ" ); //
            //TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-merge2/SpaceTalos-GEANT4-project/build/OutputHighStat.root", "READ" ); //
            TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-GEANT4-project/build/Output.root", "READ" ); //
            //TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-merge2/SpaceTalos-GEANT4-project/build/Output.root", "READ" ); //
            //TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-merge2/SpaceTalos-GEANT4-project/build/Output1M_SPARTAN_singleSV_20MeV_LivermoreTest.root", "READ" ); //

            if( rfile->IsZombie() ) throw runtime_error( "unable to open file" );
            
            // file 3
            TCanvas* canvasXSproton = new TCanvas;
            canvasXSproton->cd();
            canvasXSproton->SetLogy();
            canvasXSproton->SetLogx();
            
            TH1D* histXS2 = (TH1D*)rfile->Get( "XSenergy" );
            
            histXS2->GetXaxis()->SetRangeUser(1,20000);
            histXS2->GetYaxis()->SetRangeUser(1E-20,1E-1);
            histXS2->SetLineWidth(5);
            histXS2->SetLineColor(kBlack);
            histXS2->Draw( "hist L" );

            
            rfile->Close();
      }
      
      if (SPARTAN_LET){

      /////////////////
            TCanvas* canvasXSLET_SPARTAN = new TCanvas;
            canvasXSLET_SPARTAN->cd();
            canvasXSLET_SPARTAN->SetLogy();


            double LET_SPARTAN[3] = {0.101, 0.493, 4.146};
            double Xsec_SPARTAN[3] = {7.500e-14, 1.060e-10, 8.961e-10};
            TGraph *XsecLETgraph_SPARTAN = new TGraph(3,LET_SPARTAN,Xsec_SPARTAN);
            XsecLETgraph_SPARTAN->SetTitle("SPARTAN cross section validation");
            XsecLETgraph_SPARTAN->SetMarkerColor(1);
            XsecLETgraph_SPARTAN->SetMarkerStyle(21);
            XsecLETgraph_SPARTAN->GetXaxis()->SetTitle("LET (MeV*cm2/mg)");
            XsecLETgraph_SPARTAN->GetXaxis()->SetRangeUser(0,5.5);
            XsecLETgraph_SPARTAN->GetYaxis()->SetRangeUser(1E-14,1E-8);
            //XsecLETgraph_SPARTAN->GetYaxis()->SetTitle("Xse");
            XsecLETgraph_SPARTAN->Draw("AP");
      }
      /////////////////      
      if (FinFET_LET){

            TCanvas* canvasXSLET_FinFET = new TCanvas;
            canvasXSLET_FinFET->cd();
            canvasXSLET_FinFET->SetLogy();


            double LET_FinFET[6] = {2.5, 6.0, 16.0, 25.0, 33.0, 50.0};
            //double Xsec_FinFET_low[6] = {2.8701019e-11, 2.8791428e-11, 2.8726387e-11, 2.8885078e-11, 2.8746605e-11, 2.8972054e-11};
            //double Xsec_FinFET_low[6] = {2.8792763e-11, 2.8843117e-11, 2.8729820e-11, 2.8847694e-11, 2.8753090e-11, 2.8856277e-11}; // 80nm
            double Xsec_FinFET_low[6] = {2.8746414e-11,2.8784561e-11, 2.9156685e-11, 2.9466629e-11, 3.0191994e-11, 2.8856277e-11}; // 80n, small cuts
            double Xsec_FinFET_high[6] = {8.5645294e-12, 2.5916672e-11, 2.8484535e-11, 2.8716850e-11, 2.8622627e-11, 2.8968048e-11};
            TGraph *XsecLETgraph_FinFET_low = new TGraph(6,LET_FinFET,Xsec_FinFET_low);
            XsecLETgraph_FinFET_low->SetTitle("ATMEL ion cross section validation");
            XsecLETgraph_FinFET_low->SetMarkerColor(2);
            XsecLETgraph_FinFET_low->SetLineColor(2);
            XsecLETgraph_FinFET_low->SetMarkerStyle(20);
            XsecLETgraph_FinFET_low->SetMarkerSize(2);
            XsecLETgraph_FinFET_low->GetXaxis()->SetTitle("LET (MeV*cm2/mg)");
            XsecLETgraph_FinFET_low->GetXaxis()->SetRangeUser(0,130.);
            XsecLETgraph_FinFET_low->GetYaxis()->SetRangeUser(1E-12,4E-9);
            //XsecLETgraph_FinFET->GetYaxis()->SetTitle("Xse");
            XsecLETgraph_FinFET_low->Draw("APL");
            TGraph *XsecLETgraph_FinFET_high = new TGraph(6,LET_FinFET,Xsec_FinFET_high);
            XsecLETgraph_FinFET_high->SetMarkerColor(2);
            XsecLETgraph_FinFET_high->SetLineColor(2);
            XsecLETgraph_FinFET_high->SetMarkerStyle(24);
            XsecLETgraph_FinFET_high->SetMarkerSize(2);
            XsecLETgraph_FinFET_high->GetXaxis()->SetRangeUser(0,130.);
            XsecLETgraph_FinFET_high->GetYaxis()->SetRangeUser(1E-12,4E-9);
            XsecLETgraph_FinFET_high->Draw("same LP");
            //TMultiGraph  *mg_FinFET  = new TMultiGraph();
            //mg_FinFET->Add(XsecLETgraph_FinFET_low);
            //mg_FinFET->Add(XsecLETgraph_FinFET_high);
            //mg_FinFET->GetXaxis()->SetLimits(0,130.);
            //mg_FinFET->GetYaxis()->SetLimits(1E-12,4E-9);
            //mg_FinFET->Draw("ALP");

      }
            /////////////////
      if (ATMEL_LET){

            TCanvas* canvasXSLET_ATMEL = new TCanvas;
            canvasXSLET_ATMEL->cd();
            canvasXSLET_ATMEL->SetLogy();


            double LET_ATMEL[4] = {2.000, 6.460, 24.169, 47.079};
            double Xsec_ATMEL[4] = {1.125e-11, 6.880e-08, 1.021e-07, 1.024e-07};
            //double Xsec_ATMEL[4] = {1.125e-11, 6.5e-09, 8.87e-08, 1.024e-07};
            TGraph *XsecLETgraph_ATMEL = new TGraph(4,LET_ATMEL,Xsec_ATMEL);
            XsecLETgraph_ATMEL->SetTitle("ATMEL ion cross section validation");
            XsecLETgraph_ATMEL->SetMarkerColor(2);
            XsecLETgraph_ATMEL->SetMarkerStyle(21);
            XsecLETgraph_ATMEL->GetXaxis()->SetTitle("LET (MeV*cm2/mg)");
            XsecLETgraph_ATMEL->GetXaxis()->SetRangeUser(0,130.);
            XsecLETgraph_ATMEL->GetYaxis()->SetRangeUser(1E-12,1E-6);
            //XsecLETgraph_ATMEL->GetYaxis()->SetTitle("Xse");
            XsecLETgraph_ATMEL->Draw("AP");
      }


///////////////////
      if (ATMEL_p_validation){
      
            TCanvas* canvasXSLET_ATMEL_p = new TCanvas;
            canvasXSLET_ATMEL_p->cd();
            canvasXSLET_ATMEL_p->SetLogy();


            double E_ATMEL_p[8] = {12.0, 15.0, 20.0, 50.0, 70.0, 100.0, 150., 250.};
            ////double Xsec_ATMEL_p[10] = {0, 0, 1.0e-14, 5.0e-14, 4.000e-14, 9.5e-14, 2.5e-14, 5.0e-14, 5.0e-14, 9.5e-14}; // single SV, chinese paper
            double Xsec_ATMEL_p[8] = {1.56097236e-14, 1.72681625e-14, 2.61622135e-14, 3.60395949e-14, 0, 2.81598355e-14, 3.20522354e-14, 3.1548691e-11}; // thesis, no protonInelBiasing
            TGraph *XsecEgraph_ATMEL_p = new TGraph(8,E_ATMEL_p,Xsec_ATMEL_p);
            XsecEgraph_ATMEL_p->SetName("gr1");
            XsecEgraph_ATMEL_p->SetTitle("ATMEL proton cross section validation");
            XsecEgraph_ATMEL_p->SetMarkerColor(2);
            XsecEgraph_ATMEL_p->SetMarkerStyle(21);
            XsecEgraph_ATMEL_p->SetMarkerSize(1.5);
            XsecEgraph_ATMEL_p->GetXaxis()->SetTitle("Energy (MeV)");
            XsecEgraph_ATMEL_p->GetXaxis()->SetRangeUser(0,500.);
            XsecEgraph_ATMEL_p->GetYaxis()->SetRangeUser(1E-15,1E-12);
            //XsecEgraph_ATMEL_p->GetYaxis()->SetTitle("Xse");
            XsecEgraph_ATMEL_p->Draw("AP");      

            double E_ATMEL_p2[8] = {12.0, 15.0, 20.0, 50.0, 70.0, 100.0, 150., 250.};
            double Xsec_ATMEL_p2[8] = {2.47107687e-14, 3.37780979e-14, 3.54327400e-14, 4.81545131e-14, 0, 3.30460313e-14, 3.70143723e-14, 3.06007701e-14}; 
            TGraph *XsecEgraph_ATMEL_p2 = new TGraph(8,E_ATMEL_p2,Xsec_ATMEL_p2);
            XsecEgraph_ATMEL_p2->SetName("gr2");
            XsecEgraph_ATMEL_p2->SetTitle("ATMEL proton cross section validation");
            XsecEgraph_ATMEL_p2->SetMarkerColor(1);
            XsecEgraph_ATMEL_p2->SetMarkerStyle(21);
            XsecEgraph_ATMEL_p2->SetMarkerSize(1.5);
            XsecEgraph_ATMEL_p2->GetXaxis()->SetTitle("Energy (MeV)");
            XsecEgraph_ATMEL_p2->GetXaxis()->SetRangeUser(0,500.);
            XsecEgraph_ATMEL_p2->GetYaxis()->SetRangeUser(1E-15,1E-12);
            //XsecEgraph_ATMEL_p->GetYaxis()->SetTitle("Xse");
            XsecEgraph_ATMEL_p2->Draw("same P");

            
            auto legend = new TLegend(0.1,0.7,0.48,0.9);
            legend->AddEntry("gr1","2.5um, 300keV, w p inel bias 1000","p");
            legend->AddEntry("gr2","2.5um, 200keV, w p inel bias 1000","p");
            //legend->AddEntry("gr3","4um, 419keV, w/ inel bias","p");
            //legend->AddEntry("gr4","4um, 382keV, w/ inel bias","p");
            legend->Draw();
      
      }
      
      if (SEU_multiplicity){
            //TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-merge2/SpaceTalos-GEANT4-project/build/Output.root", "READ" );
            //TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalosRegionBiasing/SpaceTalos-GEANT4-project/build/Output.root", "READ" );
            //TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-GEANT4-project/build/Output_124Xe_16MeV_0p1fC_80nm.root", "READ" );
            TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-GEANT4-project/build/Output_124Xe_16MeV_0p1fC_80nm_smallCuts.root", "READ" );
            //TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-merge2/SpaceTalos-GEANT4-project/build/Output10M_ATMEL_8banksChip_100MeV_90deg.root", "READ" );
            //TFile* rfile = new TFile( "/home/dedes/Work/OwnProjects/CLion/SpaceTalos-merge2/SpaceTalos-GEANT4-project/build/Output_ATMEL_1M_PROBAII_AP9_90deg_satcage.root", "READ" );
            
            
            TCanvas* canvasAtLeastOne = new TCanvas;
            canvasAtLeastOne->cd();
            canvasAtLeastOne->SetLogy();
            
            TH1D* histAtLeastOne = (TH1D*)rfile->Get( "SEEperEvent" );
            
            histAtLeastOne->GetXaxis()->SetRangeUser(0,2);
            //histAtLeastOne->GetYaxis()->SetRangeUser(1E-22,1E-8);
            histAtLeastOne->SetLineWidth(5);
            histAtLeastOne->SetLineColor(kBlack);
            histAtLeastOne->Draw( "hist" );
            
            
            //double area_mm2 = 19.*19.; // SPARTAN top mm2!
            //double area_mm2 = 19.*1.29; // SPARTAN side mm2!
            //double area_mm2 = 58.37; // ATMEL top mm2!
            //double area_mm2 = 0.101; // ATMEL side mm2!
            double area_mm2 = 0.00049283072; // FinFET top cm2!
            cout << "Simulation with " << histAtLeastOne->GetEntries() << " particles" << endl;
            cout << "Number of events with at least 1 SEU = " << histAtLeastOne->GetBinContent(2) << endl; // bin with value 1
            cout << "Rate of at least 1 SEU = " << histAtLeastOne->GetBinContent(2)/histAtLeastOne->GetEntries() << endl;
            cout << "Rate of at least 1 SEU / fluence (cm2/bit) = " << histAtLeastOne->GetBinContent(2)*area_mm2/histAtLeastOne->GetEntries() << endl;


            TCanvas* canvasMultiple = new TCanvas;
            canvasMultiple->cd();
            canvasMultiple->SetLogy();            

            TH1D* histMultiple = (TH1D*)rfile->Get( "MultiplicitySEEperEvent" );
            
            histMultiple->GetXaxis()->SetRangeUser(0,10);
            //histAtLeastOne->GetYaxis()->SetRangeUser(1E-22,1E-8);
            histMultiple->SetLineWidth(5);
            histMultiple->SetLineColor(kBlack);
            histMultiple->Draw( "hist" );
            
            double SEE_sum = 0.;
            for (int i=2; i<10; i++){
                  cout << histMultiple->GetBinContent(i) << endl;
                  SEE_sum += double(i-1)*(histMultiple->GetBinContent(i)); 
            }
            
            cout << "Sum of SEU = " << SEE_sum << endl; // bin with value 1
            cout << "Rate of SEU = " << SEE_sum/histMultiple->GetEntries() << endl;
            cout << "Rate of SEU / fluence = " << SEE_sum*area_mm2/histMultiple->GetEntries() << endl;

/*
            TCanvas* canvasTID = new TCanvas;
            canvasTID->cd();
            canvasTID->SetLogy();            

            TH1D* histTID = (TH1D*)rfile->Get( "TIDperEvent" );
            
            histTID->GetXaxis()->SetRangeUser(0,5);
            histTID->SetLineWidth(5);
            histTID->SetLineColor(kBlack);
            histTID->Draw( "hist" );
            
            TAxis *xaxis = histTID->GetXaxis();
            //cout << histTID->GetBinContent(1) << " @ " << xaxis->GetBinCenter(1) << endl;
                        
            double TID_sum = 0.;
            for (int i=1; i<3; i++){
                  //cout << histTID->GetBinContent(i) << endl;
                  cout << histTID->GetBinContent(i) << " x " << xaxis->GetBinCenter(i) << " = " << (xaxis->GetBinCenter(i))*(histTID->GetBinContent(i)) << endl;
                  TID_sum += (xaxis->GetBinCenter(i))*(histTID->GetBinContent(i)); 
            }
            
            cout << "Sum of TID = " << TID_sum << endl;
            cout << "Rate of TID = " << TID_sum/histMultiple->GetEntries() << endl;
            // 1043.5435 MeV
            // 16.359757 MeV
            //cout << "Rate of TID / fluence = " << SEE_sum*area_mm2/histMultiple->GetEntries() << endl;
*/            
            rfile->Close();
      }
    }
  catch( exception &e )
    {
      cerr << "\n\nERROR: " << e.what() << endl;
      return 0;
    }

  if(!gROOT->IsBatch()) theApp.Run();

  return 0;
}
