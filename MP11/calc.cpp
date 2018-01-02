#include <cmath>
#include "calc.h"
using namespace std;
// By: Zain Paya (zpaya2)
// introduction paragraph
// this MP heavily used the concept of classes and objects in c++.. through the
// use of inheritance and virtual functions. We were tasked to create a
// calculater with the use of these concepts and basic knowledge of arithmetics.
// I have to say that this material was not efficiently taught... I learned all the
// concepts from an alternative professor, professor youtube. Honestly these c++
// concepts should have been taught more slowly with clear examples.... in the
// end it doesn't matter because I got the knowledge. 

// RealNumber, ComplexNumber and RationalNumber inherit from base Number class.


//==============NUMBER===============//
Number::Number(){}

Number::~Number(){}

double Number::magnitude(){return 0.0;}

void Number::print(){}

Number Number::operator + (const Number& arg)
{
    Number result;
    return result;
}

Number Number::operator - (const Number& arg)
{
    Number result;
    return result;
}

Number Number::operator * (const Number& arg)
{
    Number result;
    return result;
}

Number Number::operator / (const Number& arg)
{
    Number result;
    return result;
}

void Number::set_value(double rval){}

void Number::set_value(double rval, double ival){}



//=============real=====================//
//constructors for real number
RealNumber::RealNumber()
{
    realComponent = 0.0;
}

RealNumber::RealNumber(double rval)
{
    realComponent = rval;
}

//return the magnitiude of the real number
double RealNumber::magnitude()
{
    return abs(realComponent);
}

//print real number out
void RealNumber::print(){
    cout << "RealNumber: " << realComponent << "\n" << endl;
}

//real + real
RealNumber RealNumber::operator + (const RealNumber& arg)
{   
    //code here

    
    RealNumber result;
    result.realComponent = this->realComponent + arg.realComponent;
    return result;
}

//real - real
RealNumber RealNumber::operator - (const RealNumber& arg)
{
    //code here
    
    RealNumber result;
    result.realComponent = this->realComponent - arg.realComponent;
    return result;
}

//real * real
RealNumber RealNumber::operator * (const RealNumber& arg)
{
    //code here
    RealNumber result;
    result.realComponent = this->realComponent * arg.realComponent;
    return result;
}

//real/real
RealNumber RealNumber::operator / (const RealNumber& arg)
{
    //code here
    RealNumber result;
    result.realComponent = this->realComponent / arg.realComponent;
    return result;
}

//set the value for real number
void RealNumber::set_value (double rval)
{
    //code here
    realComponent = rval;
}



//=============complex================//

ComplexNumber::ComplexNumber()
{
    imagComponent = 0.0;
}

ComplexNumber::ComplexNumber(double rval, double ival)
{
    //code here
    realComponent = rval;
    imagComponent = ival;
}

//return the magnitude of the complex number
double ComplexNumber::magnitude(){
    //code here
        double Magnitude = sqrt ( (realComponent*realComponent) + (imagComponent*imagComponent));
    return Magnitude;
}
//print the complexnumber
void ComplexNumber::print(){
    //code here
    //out << "realComponent: " << realComponent << "\n" << endl; 
    // cout << "imagComponent: " << imagComponent << "\n" << endl;
    cout << "ComplexNumber: " << realComponent <<" + " <<  imagComponent << "i" << "\n" << endl;
}

//imag + imag
ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    //code here
    ComplexNumber result;
    result.realComponent = this->realComponent + arg.realComponent;
    result.imagComponent = this->imagComponent + arg.imagComponent;
    return result;
}

//imag - imag
ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    //code here
    ComplexNumber result;
    result.realComponent = this->realComponent - arg.realComponent;
    result.imagComponent = this->imagComponent - arg.imagComponent;
    return result;
}

//imag * imag
ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    //code here
    // basically factoring out the 2 complex numbers thus for the real
    // component, you would multiply both real values together and add that to
    // the negative of the imaginary times the complexconjugate. for the
    // imaginary component you multiply the real and imaginary terms together
    // in both of the complex numbers and add them together.
    ComplexNumber result;
    result.realComponent = (this->realComponent * arg.realComponent) - (this->imagComponent * arg.imagComponent);
    result.imagComponent = (this->imagComponent * arg.realComponent) + (this->realComponent * arg.imagComponent);
    return result;
}

//imag/imag
ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    //code here
    // basically the numerator is multiplied by the complex conjugate and the
    // denominator is also multiplied by the complex conjugate because that way
    // the complex term in the denominator will cancel and a real term will be
    // left meaning that there is only a real and imaginary term on the
    // numerator.
    ComplexNumber result;
    result.realComponent = ((this->realComponent * arg.realComponent) - (this->imagComponent * (-arg.imagComponent)))/((arg.realComponent * arg.realComponent)-(arg.imagComponent * (-arg.imagComponent)));
    result.imagComponent = ((this->realComponent * (-arg.imagComponent)) + (this->imagComponent * arg.realComponent))/((arg.realComponent * arg.realComponent)-(arg.imagComponent * (-arg.imagComponent)));

    return result;
}

//set the complexnumber value
void ComplexNumber::set_value (double rval, double ival)
{
    //code here
    realComponent = rval;
    imagComponent = ival;
}







//=============rational================//

RationalNumber::RationalNumber()
{
    numerator = 0;
    denominator = 1;
}

RationalNumber::RationalNumber(int numer, int denom)
{
    RationalNumber::set_value(numer, denom);
}

//return the magnitude of the rational number
double RationalNumber::magnitude(){
    //code here
    return abs(numerator/denominator);
}

//print the rational number
void RationalNumber::print(){
    //code here
    cout << "RationalNumber: " << numerator << " / " << denominator << "\n" << endl;

}

//rational + rational
RationalNumber RationalNumber::operator + (const RationalNumber& arg)
{
    RationalNumber result;
    result.numerator = (this->numerator * arg.denominator) + (arg.numerator * this->denominator);   //getting common denominators...
    result.denominator = (this->denominator * arg.denominator);                                     //actually getting common denominators
        int finalfactor;
        finalfactor = RationalNumber::gcd(result.numerator,result.denominator);
    result.numerator = result.numerator / finalfactor;                                              //simplifying fraction
    result.denominator = result.denominator/ finalfactor;
    return result; 
}

//rational - rational
RationalNumber RationalNumber::operator - (const RationalNumber& arg)
{
    //code here
    RationalNumber result;
    result.numerator = (this->numerator * arg.denominator) - (arg.numerator * this-> denominator);
    result.denominator = (this->denominator * arg.denominator);
     int finalfactor;
        finalfactor = RationalNumber::gcd(result.numerator,result.denominator);
    result.numerator = result.numerator / finalfactor;                                              //simplifying fraction
    result.denominator = result.denominator/ finalfactor;

    return result; 
}

//rational * rational
RationalNumber RationalNumber::operator * (const RationalNumber& arg)
{
    //code here
    RationalNumber result;
    result.numerator = this->numerator * arg.numerator;                         //numerator * numerator
    result.denominator = this->denominator * arg.denominator;                   // denominator * denominator
         int finalfactor;                                                       // this is just term used to simplify fraction
         finalfactor = RationalNumber::gcd(result.numerator,result.denominator);
             result.numerator = result.numerator / finalfactor;                  //simplifying fraction
             result.denominator = result.denominator/ finalfactor;


    return result; 
}

//rational/rational
RationalNumber RationalNumber::operator / (const RationalNumber& arg)
{
    //code here
    RationalNumber result;
    result.numerator = this->numerator * arg.denominator;                       // numerator * denominator
    result.denominator = this->denominator * arg.numerator;                     // denominator * numerator
  int finalfactor;
        finalfactor = RationalNumber::gcd(result.numerator,result.denominator);
    result.numerator = result.numerator / finalfactor;                                              //simplifying fraction
    result.denominator = result.denominator/ finalfactor;


    return result; 
}

//set the rational number value
void RationalNumber::set_value (int numer, int denom)
{
    //code here
    int factor;
        factor = RationalNumber::gcd(numer, denom);      //calls gcd to determine greatest common factor
        numerator = numer / factor;
        if( denom < 0){
            numerator = numerator * -1;
            denominator = abs(denom) / factor;
        }
        if( denom == 0)
                denominator = 1;
        else
                denominator = denom / factor;


    
}


// helper function
int RationalNumber::gcd(int a, int b)
{
    //code here
                                                            //standard gcd
                                                            //function
            int d, e;
            d = abs(a);
            e = abs(b);
            
            while (d!=0) {int c=d; d=e%d; e=c;}
                return e;
    
}







