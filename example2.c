#include <stdio.h>
#include "de_int.h"

// parameter set
typedef struct param{
  int cc;              // counter of function calls 
  
  double r;            // parameter for contour integral
  double complex a,b;  // parameter for line integral
  double complex (*func_ptr)(double complex z); // function pointer   
}PM;

// function prototype 
double complex integrand_c1(double t,void *pa); // for straight line integral ( c(t) = a * t + b )  
double complex integrand_c2(double t,void *pa); // for contour integral ( |z - a| = r, c(t) = a + r * exp(i*t) )
double complex f1(double complex z); // f(z)=z^2.
double complex f2(double complex z); // f(z)=conjugate(z).
double complex f3(double complex z); // f(z)=sin(z)/(z^3*(z-2)).


int main()
{
  PM pa;
  double complex Iz,Ia;
  double eps,err;
  
  eps=1.0e-15;
  
  printf("--- example of straight line integral ---\n");
  printf("1. compute int z^2 dz along the straight line from b to a+b.\n");
  pa.a=1.0+1.0*I;  // set the straight line parameter
  pa.b=0.1-0.1*I;  // c(t) = a * t + b, t = 0 to 1.
  pa.func_ptr=&f1; // select function. f(z)=z^2
  pa.cc=0;         // reset function call counter
  printf("a = % g %+g i, b = % g %+g i.\n",creal(pa.a),cimag(pa.a),creal(pa.b),cimag(pa.b));
  Iz=deintz(integrand_c1,0.0,1.0,&pa,eps,&err);
  printf("I = % 15.14e %+15.14e i, err = %g, function calls = %d\n",creal(Iz),cimag(Iz),err,pa.cc);
  Ia=pa.a*(pa.a*pa.a/3.0+pa.a*pa.b+pa.b*pa.b); // analytical solution
  printf("  = % 15.14e %+15.14e i (analytical solution)\n",creal(Ia),cimag(Ia));
  
  printf("2. compute int conjugate(z) dz along the straight line from b to a+b.\n");
  pa.cc=0;         // reset function call counter
  pa.func_ptr=&f2; // f(z) = conjugate(z).
  printf("a = % g %+g i, b = % g %+g i.\n",creal(pa.a),cimag(pa.a),creal(pa.b),cimag(pa.b));
  Iz=deintz(integrand_c1,0.0,1.0,&pa,eps,&err);
  printf("I = % 15.14e %+15.14e i, err = %g, function calls = %d\n",creal(Iz),cimag(Iz),err,pa.cc);
  Ia=pa.a*(0.5*conj(pa.a)+conj(pa.b)); // analytical solution
  printf("  = % 15.14e %+15.14e i (analytical solution)\n\n",creal(Ia),cimag(Ia));
  
  
  printf("--- example of contour integral ---\n");
  printf("1. compute oint sin(z)/(z^3 * (z-2)) dz along the circle |z-2| = 1.\n");
  pa.a=2.0;        // set the circle parameter 
  pa.r=1.0;        // c(t) = a + r * exp(i*t), t=-pi to pi 
  pa.func_ptr=&f3; // f(z) = sin(z)/(z^3 * (z-2)).
  pa.cc=0;         // reset function call counter
  printf("a = % g %+g i, r = % g.\n",creal(pa.a),cimag(pa.a),pa.r);
  Iz=deintz(integrand_c2,-M_PI,M_PI,&pa,eps,&err);
  printf("I = % 15.14e %+15.14e i, err = %g, function calls = %d\n",creal(Iz),cimag(Iz),err,pa.cc);
  Ia=2.0*M_PI*I*sin(2.0)/8.0; // analytical solution
  printf("  = % 15.14e %+15.14e i (analytical solution)\n",creal(Ia),cimag(Ia));
  
  printf("2. compute oint sin(z)/(z^3 * (z-2)) dz along the circle |z| = 1.\n");
  pa.a=0.0;        // set the circle parameter 
  pa.r=1.0;        // c(t) = a + r * exp(i*t), t=-pi to pi 
  pa.func_ptr=&f3; // f(z) = sin(z)/(z^3 * (z-2)).
  pa.cc=0;         // reset function call counter
  printf("a = % g %+g i, r = % g.\n",creal(pa.a),cimag(pa.a),pa.r);
  Iz=deintz(integrand_c2,-M_PI,M_PI,&pa,eps,&err);
  printf("I = % 15.14e %+15.14e i, err = %g, function calls = %d\n",creal(Iz),cimag(Iz),err,pa.cc);
  Ia=-2.0*M_PI*I/4.0; // analytical solution
  printf("  = % 15.14e %+15.14e i (analytical solution)\n",creal(Ia),cimag(Ia));
  
  return 0;
}

double complex integrand_c1(double t,void *pa)
{
  PM *pm=(PM*)pa;
  double complex z;
  
  pm->cc++;
  z=pm->a*t+pm->b;
  return pm->func_ptr(z)*pm->a;
}

double complex integrand_c2(double t,void *pa)
{
  PM *pm=(PM*)pa;
  double complex z,rce; 
  
  pm->cc++;
  rce=pm->r*cexp(I*t); 
  z=pm->a+rce;
  
  return pm->func_ptr(z)*I*rce;
}

double complex f1(double complex z)
{
  return z*z;
}

double complex f2(double complex z)
{
  return conj(z);
}

double complex f3(double complex z)
{
  return csin(z)/(z*z*z*(z-2.0));
}
