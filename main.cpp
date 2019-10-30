/*
 * This program implements simple FIR filter processing procedure.
 * Given input signal and FIR coefficients,then the output will be onvolution result of input and coefficient
 * Author: Chen Ji
 */

#include "fir.h"
#include <iostream>
#include <fstream>
#include <sstream>
//Declaration
void Intro();
string promptForFile(ifstream& stream, const string& prompt = "Please Enter file name: ",
                     const string& reprompt = "Unable to open that file.  Try again. ");

int main()
{
    sequence inputSignal, outputSignal;
    FIR filter;

    Intro(); //welcome line
    ifstream fileInput;
    // read file into inputSignal Sequence
    cout<<"***********Reading in input signal**************"<<endl;
    string filename = promptForFile(fileInput);
    fileInput>>inputSignal;
    cout<<"The Input signal is: "<<inputSignal<<endl;
    fileInput.close();
    cout<<"***********Reading in FIR coefficient**************"<<endl;
    filename = promptForFile(fileInput);
    fileInput>>filter;
    cout<<"The FIR coefficients: "<<filter<<endl;
    outputSignal=filter.apply_filter(inputSignal);
    cout<<"Output signal is:"<<outputSignal<<endl;
    return 0;
}

/*
 * Welcome line:Digital Filter
 */
void Intro(){
    cout<<"*****************************DIGITAL FILTER******************************"<<endl;//welcome line
}

/*
 * Prompts for a file.
 * If file is found, the stream is opened and filename returned.
 * If file is not found, the user is reprompted.
 *
 * Parameter: stream that will be opened, prompt and reprompt
 * Return: string of the valid file the user types.
 */
string promptForFile(ifstream& stream, const string& prompt, const string& reprompt){
    while(true){
        cout<<prompt;
        string filename;
        if(!getline(cin, filename))
            throw domain_error("getline: End of input reached while waiting for line.");
        if(!filename.empty()){
            stream.open(filename);
            if (stream.good()) return filename;
            stream.clear();
        }
        cerr << reprompt << endl;
    }
}


