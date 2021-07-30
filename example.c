#include <stdio.h>
#include "de_int.h"

// param set
typedef struct param{
  int cc;
  double sd;
  double complex sz;
}PM;

// test func
double funcd1(double x,void *pa); 
double complex funcz1(double x,void *pa);
double funcd2(double x,void *pa);
double complex funcz2(double x,void *pa);

int main()
{
  PM pa;
  double complex Iz;
  double Id;
  double a,b;
  double eps=1.0e-15;
  double err;

  a=1.1;
  b=1.2;
  printf("a = %g, b = %g\n",a,b);
  printf("I    = int_a^b 1/(cos(x)*cos(x)) dx\n");
  printf("     = %15.14e ( = tan(b)-tan(a) )\n",tan(b)-tan(a));
  pa.cc=0;
  Id=deintd(funcd1,a,b,&pa,eps,&err); 
  printf("I_de = %15.14e, err = %g, function call = %d\n\n",Id,err,pa.cc);

  printf("a = %g, b = %g\n",a,b);
  printf("I    = int_a^b exp(i*x) dx\n");
  Iz=-I*(cexp(b*I)-cexp(a*I));
  printf("     = %15.14e %+15.14e i ( = -i*(exp(b*i)-exp(a*i)) )\n",creal(Iz),cimag(Iz));
  pa.cc=0;
  Iz=deintz(funcz1,a,b,&pa,eps,&err);
  printf("I_de = %15.14e %+15.14e i, err = %g, function call = %d\n\n",creal(Iz),cimag(Iz),err,pa.cc);
  
  a=0.0;
  pa.sd=4.0;
  printf("a = %g, b -> infinity, s = %g\n",a,pa.sd);
  printf("I    = int_a^b exp(-s*x) dx ( Laplace transform )\n");
  printf("     = %15.14e ( = 1/s )\n",1.0/pa.sd);
  pa.cc=0;
  Id=deintid(funcd2,a,&pa,eps,&err);
  printf("I_dei= %15.14e, err = %g, function call = %d\n\n",Id,err,pa.cc);
  
  pa.sz=4.0+2*I;
  printf("a = %g, b -> infinity, s = %g %+g i\n",a,creal(pa.sz),cimag(pa.sz));
  printf("I    = int_a^b x*exp(-s*x) dx ( Laplace transform )\n");
  Iz=1.0/(pa.sz*pa.sz);
  printf("     = %15.14e %+15.14e i ( = 1/(s*s) )\n",creal(Iz),cimag(Iz));
  pa.cc=0;
  Iz=deintiz(funcz2,a,&pa,eps,&err);
  printf("I_dei= %15.14e %+15.14e i, err = %g, function call = %d\n",creal(Iz),cimag(Iz),err,pa.cc);

  return 0;
}	

double funcd1(double x,void *pa)
{
  PM *t=(PM *)pa;
  t->cc+=1;
  
  return 1.0/(cos(x)*cos(x));
}

double complex funcz1(double x,void *pa)
{
  PM *t=(PM *)pa;
  t->cc+=1;
  
  return cexp(I*x);
}

double funcd2(double x,void *pa)
{
  PM *t=(PM *)pa;
  t->cc+=1;
  
  return exp(-t->sd*x);
}

double complex funcz2(double x,void *pa)
{
  PM *t=(PM *)pa;
  t->cc+=1;
  
  return x*cexp(-t->sz*x);
}
