#ifndef fir_include
#define fir_include

#include <iostream>
#include <fstream>
using namespace std;
class sequence
{
public:
    sequence(int _number_of_samples=0, float* _sample_values=NULL);//default
    sequence(const sequence& s);//copy constructor
    const sequence& operator=(const sequence& s);//assignment operator
    ~sequence();//destructor
    void set_all_sample_values_to_zero();//set all the values zero
    int get_number_of_samples()const;//get number of samples
    float get_sample_value(int sample_index)const;//get sample value
    void set_sample_value(int sample_index, float new_sample_value);//change the value
    friend istream& operator>>(istream& in,sequence &V);
    friend ostream& operator<<(ostream& out,sequence &V);
    sequence operator+(const sequence& s);//overloading +
    sequence& operator+=(const sequence& s);//overloading +=
private:
    int number_of_samples;
    float *sample_values;
};

class FIR
{
public:
    FIR(int _number_of_samples=0, float* _sample_values=NULL);//default
    FIR(const FIR& c);//copy constructor
    const FIR& operator=(const FIR& c);//assignment operator
    ~FIR();//destructor
    void set_all_sample_values_to_zero();//set all the values zero
    int get_number_of_samples();//get number of samples
    float get_sample_value(int sample_index);//get sample value
    void set_sample_value(int sample_index, float new_sample_value);//change the value
    friend istream& operator>>(istream& in,FIR& c);
    friend ostream& operator<<(ostream& out,FIR& c);
    FIR operator+(const FIR& c);//overloading +
    sequence apply_filter(const sequence& input);
private:
    int number_of_samples;
    float *sample_values;
};

#endif
