#pragma once
#include "Common.h"
#include "Const.h"

using namespace std;

class ADCInfo
{
private:
    TFile *dataFile;
public:
    Element type;

    //TString histName;

    //TH1I *hist;
    UInt_t nEntries;
    vector<Int_t> ADCChannel;
    vector<TDatime> measuredTime;
    Double_t measurementTimeRootFile;
    Double_t measurementTimeScaler;
    Double_t measurementTimeTrue; 
    UInt_t nEntriesScaler;
    UInt_t rebin;


    ADCInfo(TFile *rootFile, Element type, UInt_t measurementTime, UInt_t nEntries, UInt_t rebin)
    {
        dataFile = rootFile;
        this->type = type;
        this->measurementTimeScaler = measurementTime;
        nEntriesScaler = nEntries;
        this->rebin = rebin;
        
        TTree *tree = (TTree*)dataFile->Get(Constants::TREE_NAME);
        this->nEntries = tree->GetEntriesFast();
        measurementTimeTrue = measurementTimeScaler * ((Double_t)this->nEntries / (Double_t)nEntriesScaler);


        // Get ADC Channel
        TLeaf *leaf = tree->GetLeaf(Constants::LEAF_NAME_ADC);

        for (Int_t i = 0; i < this->nEntries; i++)
        {
            tree->GetEntry(i);
            //cout << leaf->GetValue() << endl;
            ADCChannel.push_back(leaf->GetValue());
        }

        // Get Time
        leaf = tree->GetLeaf(Constants::LEAF_NAME_TIME);

        for (Int_t i = 0; i < this->nEntries; i++)
        {
            tree->GetEntry(i);
            //cout << leaf->GetValue() << endl;
            measuredTime.push_back(TDatime(Constants::DATE, leaf->GetValue()));
        }
        measurementTimeRootFile = measuredTime[this->nEntries - 1].Convert() - measuredTime[0].Convert();

    }

    //ADCInfo(const ADCInfo &obj)
    //{
    //    this->dataFile = obj.dataFile;
    //    this->type = obj.type;
    //    this->nEntries = obj.nEntries;
    //    this->ADCChannel = obj.ADCChannel;
    //    this->measuredTime = obj.measuredTime;



    //}

    //~ADCInfo()
    //{

    //}



};