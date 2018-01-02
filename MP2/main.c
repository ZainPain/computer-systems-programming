// in this code we are tying to solve a differential equation with a numerical technique.
// overall this lab was easy however there were some bracket mistakes initially in the code
// which was kind of annoying to find.
// 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	double omega1, omega2, omegac, T, dt;
	int N, method;

	//Scan the inputs from the user.
	scanf("%lf %lf %lf %d", &omega1, &omega2, &omegac, &method);
	
	T = 3 * 2 * M_PI / omega1;      // Total time
    	N = 20 * T / (2 * M_PI / omega2);   // Total number of time steps
    	dt = T / N;             // Time step

	if (method == 1) {
		int i;
		double Voutnew = 0, Voutcur = 0, Voutprev = 0;

		//Write your code here!
for(i=0 ; i<N; i++){

		double d1 = 1/(sqrt(2)*dt*omegac);
		double d2 = 1/((dt*dt)*(omegac*omegac));
		double A1 = 1/(d1+d2);	// simplifying equation by having a single term
		double B1 = ((2*d2)-1)*Voutcur;	// same as above
		double B2 = (d1- d2)*Voutprev;	// same as above
		double S1 = sin(omega1*i*dt);	//the two sin terms
		double S2 = .5*sin(omega2*i*dt);
		Voutnew = A1*(B1+B2+S1+S2);
	Voutprev = Voutcur; // the n value is stored into Voutprev
	Voutcur = Voutnew; // n+1 value is stored into Voutcur
	
		printf("%lf\n", Voutcur);
	}	
}



	//	 Method number 2 corresponds to the Runge-Kutta method (only for challenge).
	else if (method == 2) {
		
		//Write your code here for the challenge problem.
		
	double	Voutnew=0;  //setting all variables to 0 initially
	double	Voutcur=0;	
        double	Voutnew2=0;
	double	Voutcur2=0;
	int i;        // equivalent of n 
	 for(i=0;i<N;i++){
	double	C1= sin(omega1*i*dt) + .5*sin(omega2*i*dt);// sin terms
	double	m1=(omegac*omegac)*C1-((omegac*omegac)*Voutcur)-(omegac*sqrt(2)*Voutcur2);
	double	m2= m1*(1+(dt/2));// all the m terms
	double	m3= m1 + ((m2 *dt)/2);
	double	m4= m1 + (m3*dt);
			Voutnew2 = Voutcur2 + ((dt/6)*(m1+(2*m2)+(2*m3)+m4));
	double	K1=Voutcur2;	//all the k terms
	double	K2=Voutcur2 + ((K1*dt)/2);
	double	K3=Voutcur2 + ((K2*dt)/2);
	double	K4=Voutcur2 + (K3*dt);
			Voutnew = Voutcur + ((dt/6)*(K1+(2*K2)+(2*K3)+K4));// the main eq.
			Voutcur=Voutnew;// the n+1 Vout is stored in current Vout
			Voutcur2=Voutnew2;// same as above
		printf("%lf\n", Voutcur);			
				}
		}
	
	else {
		printf("Incorrect method number.\n");
		return -1;
	}

	return 0;
 }
