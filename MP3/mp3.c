#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double abs_double(double y)
 	{ 
    //Change this to return the absolute value of y i.e |y|

	if(y<0){
		y= y*-1;
		} 
	return y;
   	}


double fx_val(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the polynomial at the value x
		double fx;		//function fx
		
	//edit this later!!!!!!!!!!!!!!!!!!!!!!!!!!!	
		fx= (a*x*x*x*x)+(b*x*x*x)+(c*x*x)+(d*x)+e;
				
    return fx;
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the derivative of the polynomial at the value x
   		double dfx;		// first derivative (dfx)
		
	dfx= (4*a*x*x*x)+(3*b*x*x)+(2*c*x)+d;
	 return dfx;
}

double fx_ddval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the double derivative of the polynomial at the value x
	double   ddfx;		//second derivative (ddfx)
		ddfx= (12*a*x*x)+(6*b*x)+(2*c); 
 return ddfx;
}


int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
    //Change this to return the upper bound on the number of roots of the polynomial in the interval (l, r)
    
// equation for x=(x+l)
//initializing necessary variables

	
	double q=1;
	int VL=0;
	int VR=0;
	double t1;
	double t2;
	double t3;
	double t4;
	double t5;
	double t6;
	double t7;
	double t8;
	double t9;
	
	t1= a*pow(q,4);
	t2= (((4*a*l)+b)*pow(q,3));
	t3= (((6*a*pow(l,2))+(3*b*l)+c)*pow(q,2));
	t4= (((4*a*pow(l,3))+(3*b*pow(l,2))+(2*c*l)+d)*q);
	t5= (((a*pow(l,4))+(b*pow(l,3))+(c*pow(l,2))+(d*l)+e));
					//(Vl is calculated)
//sign variation count for (x= x+l)..
	
if((t1>0 && t2<0) || (t1<0 && t2>0))
{
       VL=VL+1;
}
if((t2>0 && t3<0) || (t2<0 && t3>0))
{
        VL=VL+1;
}
if((t3>0 && t4<0) || (t3<0 && t4>0))
{
        VL=VL+1;
}
if((t4>0 && t5<0) || (t4<0 && t5>0))
{
        VL=VL+1;
}

	//equation for  x=(x+r)

	t6= (((4*a*r)+b)*pow(q,3));			
	t7= (((6*a*pow(r,2))+(3*b*r)+c)*pow(q,2));
	t8= (((4*a*pow(r,3))+(3*b*pow(r,2))+(2*c*r)+d)*q);
	t9= (((a*pow(r,4))+(b*pow(r,3))+(c*pow(r,2))+(d*r)+e));
					//(Vr is calculated)
//sign variations for x=(x=r)	
	
if((t1>0 && t6<0) || (t1<0 && t6>0))
{
	VR=VR+1;
}
if((t6>0 && t7<0) || (t6<0 && t7>0))
{	
	VR=VR+1;
}
if((t7>0 && t8<0) || (t7<0 && t8>0))
{
	VR=VR+1;
}
if((t8>0 && t9<0) || (t8<0 && t9>0))
{
	VR=VR+1;
}
	
// |Vl-Vr|


double LR=abs_double(VL-VR);
	 
return LR;
}


double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the root found starting from the initial point x using Halley's method
	double Xnew;

	int n=0;
		while(n<10000){
			
		
		double	f1= fx_val(a,b,c,d,e,x);
		double  f2= fx_dval(a,b,c,d,e,x);
		double  f3= fx_ddval(a,b,c,d,e,x);
		Xnew= 	x - ((2*f1*f2) / ( (2*f2*f2 ) - (f1*f3) ));
		if(abs_double (Xnew-x) <= 0.000001){
		
			return Xnew;
		}
	
		x= Xnew;
		n=n+1;
		}
		
	



	 return -1;
}


int main(int argc, char **argv)
{
	double a, b, c, d, e, l, r;
	FILE *in;

	if (argv[1] == NULL) {
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &a);
	fscanf(in, "%lf", &b);
	fscanf(in, "%lf", &c);
	fscanf(in, "%lf", &d);
	fscanf(in, "%lf", &e);
	fscanf(in, "%lf", &l);
	fscanf(in, "%lf", &r);
    
    //The values are read into the variable a, b, c, d, e, l and r.
    //You have to find the bound on the number of roots using rootbound function.
    //If it is > 0 try to find the roots using newrfind function.
    //You may use the fval, fdval and fddval funtions accordingly in implementing the halleys's method.
    
    
    fclose(in);
   if(rootbound(a,b,c,d,e,r,l) ==0){ 	//checking if the |VL-VR| is equal to 0 which would mean no root in the interval
	printf("the polynomial has no roots in the given interval.\n");
  } 
	else
	{
	double x;	
	double answer;		
	for(x = l;x <= r;x= x+0.5)
	 {
			

		answer = newrfind_halley(a,b,c,d,e,x);		// calling newrfind_halley function

		if(answer==-1)
		printf("no root found.\n");			// as stated in newrfind_halley function, -1 correlates to n>100000 which means no root found
		else 
			printf("Root found: %lf\n", answer);	//if anything else, that means the root is found
	 }
	}
    return 0;		//done
}

