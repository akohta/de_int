#include <stdio.h>
#include "de_int.h"

// parameter set
typedef struct param{
  int cc;            // counter of function calls 
  double sd;         // constant coefficient for Example 3
  double complex sz; // constant coefficient for Example 4
}PM;

// function prototype of the integrand
double funcd1(double x,void *pa);         // Example 1
double complex funcz1(double x,void *pa); // Example 2
double funcd2(double x,void *pa);         // Example 3
double complex funcz2(double x,void *pa); // Example 4

int main()
{
  PM pa;
  double complex Iz;
  double Id;
  double a,b;
  double eps=1.0e-15;
  double err;

  printf("-- Example 1 --\n");
  a=1.1; // set lower limit
  b=1.2; // set upper limit
  printf("a = %g, b = %g\n",a,b);
  printf("I    = int_a^b 1/(cos(x)*cos(x)) dx\n");
  printf("     = %15.14e ( = tan(b)-tan(a) )\n",tan(b)-tan(a)); // analytical solution
  pa.cc=0; // reset function call counter
  Id=deintd(funcd1,a,b,&pa,eps,&err); 
  printf("I_de = %15.14e, err = %g, function call = %d\n\n",Id,err,pa.cc);

  printf("-- Example 2 --\n");
  printf("a = %g, b = %g\n",a,b);
  printf("I    = int_a^b exp(i*x) dx\n");
  Iz=-I*(cexp(b*I)-cexp(a*I));
  printf("     = %15.14e %+15.14e i ( = -i*(exp(b*i)-exp(a*i)) )\n",creal(Iz),cimag(Iz)); // analytical solution
  pa.cc=0; // reset function call counter
  Iz=deintz(funcz1,a,b,&pa,eps,&err);
  printf("I_de = %15.14e %+15.14e i, err = %g, function call = %d\n\n",creal(Iz),cimag(Iz),err,pa.cc);

  printf("-- Example 3 --\n");
  a=0.0;    // set lower limit 
  pa.sd=4.0;// set constant coefficient of integrand
  printf("a = %g, b -> infinity, s = %g\n",a,pa.sd);
  printf("I    = int_a^b exp(-s*x) dx ( Laplace transform )\n");
  printf("     = %15.14e ( = 1/s )\n",1.0/pa.sd); // analytical solution
  pa.cc=0; // reset function call counter
  Id=deintid(funcd2,a,&pa,eps,&err);
  printf("I_dei= %15.14e, err = %g, function call = %d\n\n",Id,err,pa.cc);

  printf("-- Example 4 --\n");
  pa.sz=4.0+2*I; // set constant coefficient of integrand
  printf("a = %g, b -> infinity, s = %g %+g i\n",a,creal(pa.sz),cimag(pa.sz));
  printf("I    = int_a^b x*exp(-s*x) dx ( Laplace transform )\n");
  Iz=1.0/(pa.sz*pa.sz);
  printf("     = %15.14e %+15.14e i ( = 1/(s*s) )\n",creal(Iz),cimag(Iz)); // analytical solution
  pa.cc=0; // reset function call counter
  Iz=deintiz(funcz2,a,&pa,eps,&err);
  printf("I_dei= %15.14e %+15.14e i, err = %g, function call = %d\n",creal(Iz),cimag(Iz),err,pa.cc);

  return 0;
}	

// integrand of Example 1
double funcd1(double x,void *pa)
{
  PM *t=(PM *)pa;
  t->cc+=1;
  
  return 1.0/(cos(x)*cos(x));
}

// integrand of Example 2
double complex funcz1(double x,void *pa)
{
  PM *t=(PM *)pa;
  t->cc+=1;
  
  return cexp(I*x);
}

// integrand of Example 3
double funcd2(double x,void *pa)
{
  PM *t=(PM *)pa;
  t->cc+=1;
  
  return exp(-t->sd*x);
}

// integrand of Example 4
double complex funcz2(double x,void *pa)
{
  PM *t=(PM *)pa;
  t->cc+=1;
  
  return x*cexp(-t->sz*x);
}
