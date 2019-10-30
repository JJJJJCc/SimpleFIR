#include"fir.h"

sequence::sequence(int _number_of_samples, float* _sample_values)//sequence constructor with default value
{
    number_of_samples=_number_of_samples;
    sample_values=new float[number_of_samples];
    for(int i=0;i<number_of_samples;++i) sample_values[i]=0;
}

sequence::sequence(const sequence& s):number_of_samples(s.number_of_samples)//copy constructor
{
    sample_values=new float[number_of_samples];
    for(int i=0;i<number_of_samples;++i) sample_values[i]=s.sample_values[i];
}

const sequence& sequence::operator=(const sequence& s)//operator assignment
{
    if(this==&s) return(*this);
    if(number_of_samples!=s.number_of_samples)
    {
        number_of_samples=s.number_of_samples;
        delete[] sample_values;
        sample_values=new float[number_of_samples];
    }
    for(int i=0;i<number_of_samples;i++) sample_values[i]=s.sample_values[i];
    return(*this);
}

sequence::~sequence() //destructor;if array has already empty, needn't delete;if has value, delete
{
    if(sample_values!=NULL) delete []sample_values;
}

void sequence::set_all_sample_values_to_zero()//set the all the samples to zero
{
    for(int i=0;i<number_of_samples;++i) sample_values[i]=0;
}

int sequence::get_number_of_samples()const  //sequence member function to return number of the samples
{
    return number_of_samples;
}

float sequence::get_sample_value(int sample_index)const //sequence member function to return a sample value
{
    return sample_values[sample_index];
}

void sequence::set_sample_value(int sample_index, float new_sample_value)//set values to the sample array
{
    sample_values[sample_index]=new_sample_value;
}

sequence sequence::operator+(const sequence& s)//overload +operator
{
    sequence sum(number_of_samples+s.number_of_samples);//declare a sequence sum and set the sample number
    for(int i=0;i<number_of_samples;++i) sum.sample_values[i]=sample_values[i]; //set sample values
    for(int i=number_of_samples;i<sum.number_of_samples;++i) sum.sample_values[i]=s.sample_values[i-number_of_samples];
    return sum;
}

sequence& sequence::operator+=(const sequence& s)//overload +=operator
{
    sequence original=*this;   //copy the original sequence to a new sequence
    delete[]sample_values;   //delete the original sequence
    number_of_samples+=s.number_of_samples;    //create new sequence
    sample_values=new float [number_of_samples];
    for(int i=0;i<number_of_samples-s.number_of_samples;++i) sample_values[i]=original.sample_values[i];   //set new sample values to the new sequence
    for(int i=number_of_samples-s.number_of_samples;i<number_of_samples;++i) sample_values[i]=sample_values[i-number_of_samples+s.number_of_samples];
    return *this;
}

ostream& operator<<(ostream& out,sequence &V)   //overload <<
{

    for(int i=0;i<V.number_of_samples;++i)
    {
        out<<V.sample_values[i]<<"  ";
    }
    return(out);
}

istream& operator>>(istream& in,sequence &V)//overload >>
{
    in>>V.number_of_samples;
    V.sample_values=new float[V.number_of_samples];
    for(int i=0;i<V.number_of_samples;++i)
    {
        in>>V.sample_values[i];
    }
    return(in);
}
FIR::FIR(int  _number_of_samples, float* _sample_values)//constructor
{
    number_of_samples=_number_of_samples;
    sample_values=new float[number_of_samples];
}

FIR::FIR(const FIR& s):number_of_samples(s.number_of_samples)//copy constructor
{
    sample_values=new float[number_of_samples];
    for(int i=0;i<number_of_samples;++i) sample_values[i]=s.sample_values[i];
}

const FIR& FIR::operator=(const FIR& s)//assignment operator
{
    if(this==&s) return(*this);
    if(number_of_samples!=s.number_of_samples)
    {
        number_of_samples=s.number_of_samples;
        delete[] sample_values;
        sample_values=new float[number_of_samples];
    }
    for(int i=0;i<number_of_samples;i++) sample_values[i]=s.sample_values[i];
    return(*this);
}

FIR::~FIR() //destructor
{
    if(sample_values!=NULL) delete []sample_values;
}

void FIR::set_all_sample_values_to_zero()//set values to zero
{
    for(int i=0;i<number_of_samples;++i) sample_values[i]=0;
}

int FIR::get_number_of_samples()  //get number of samples
{
    return number_of_samples;
}

float FIR::get_sample_value(int sample_index) //get sample value
{
    return sample_values[sample_index];
}

void FIR::set_sample_value(int sample_index, float new_sample_value)//set values for a object in FIR
{
    sample_values[sample_index]=new_sample_value;
}

ostream& operator<<(ostream& out,FIR &c)//overload operator <<
{
    for(int i=0;i<c.number_of_samples;++i)
    {
        out<<c.sample_values[i]<<"  ";
    }
    return(out);
}

istream& operator>>(istream& in,FIR &c)//overload operator>>
{
    in>>c.number_of_samples;
    c.sample_values=new float[c.number_of_samples];
    for(int i=0;i<c.number_of_samples;++i)
    {
        in>>c.sample_values[i];
    }
    return(in);
}

sequence FIR::apply_filter(const sequence &input)//apply filter
 {
     sequence Vout(input.get_number_of_samples()+number_of_samples-1); //set the number of samples
     for(int i=0;i<input.get_number_of_samples();++i)//when the number of sample is smaller and equal to the number of input
     {
         float value=0.;
         for(int j=0;j<=i;++j)
         {
             if(j>=number_of_samples) {break;}
             value+=input.get_sample_value(i-j)*sample_values[j];
         }
         Vout.set_sample_value(i,value);
     }
     for(int i=input.get_number_of_samples();i<(input.get_number_of_samples()+number_of_samples-1);++i)//when the number of sample is larger than the number of input
     {
         float value=0.;
         for(int j=input.get_number_of_samples()-1;j>i-number_of_samples;--j)
         {
             value+=input.get_sample_value(j)*sample_values[i-j];
         }
         Vout.set_sample_value(i,value);
     }
     return Vout;
 }
