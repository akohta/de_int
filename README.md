# de_int
This is the numerical integration program using double exponential transformation. 
This code can calculate the integral from a to b and the integral from a to infinity shown by the following formulae.
It also supports the integration of complex functions.
I made it to integrate a complex function which has a singular point.

$$I = \int_a^b f(x) \\, dx$$
$$I = \int_a^\infty f(x) \\, dx$$
$f(x)$ needs to be analytic within the integral region.  


## Usage of the example code
 1. type 'make' command to compile.
 2. type './example.out' to run.
 
Please see de_int.h for detail of functions, example.c for detail of function usages.


## Regarding the examples
- example.c
  - Example 1  
    $$I = \int_a^b \frac{1}{\cos^2 x} \\,dx = \tan b - \tan a $$
  - Example 2
    $$I = \int_a^b \exp(ix) \\,dx = -i(\exp(ib)-\exp(ia)) $$
  - Example 3
    $$I(s) = \int_0^{\infty} \exp(-sx) \\,dx = \frac{1}{s}, \\ \\ \\ s > 0 $$
  - Example 4
    $$I(s) = \int_0^{\infty} x \\, \exp(-sx) \\,dx = \frac{1}{s^2}, \\ \\ \\ \Re s > 0 $$

   Examples 3 and 4 are known as Laplace transform related to the Heaviside step function.

- example2.c
  - Example 1 for straight line integral
  
    $$\begin{eqnarray}
    I &=& \int_C z^2 \\, dz, \\ \\ \\ C(t)=at+b, \\, 0 \le t \le 1,\\
      &=& a \left( \frac{a^2}{3} + ab +b^2 \right).
    \end{eqnarray}$$
    
  - Example 2 for straight line integral
  
    $$\begin{eqnarray}
    I &=& \int_C \bar{z} \\, dz, \\ \\ \\ C(t)=at+b, \\, 0 \le t \le t, \\
      &=& a \left( \frac{1}{2} \bar{a} + \bar{b} \right).
    \end{eqnarray}$$
 
  - Example 1 for contour integral
 
    $$\begin{eqnarray}
    I &=& \oint_C \frac{\sin z}{z^3 (z-2)} \\, dz, \\ \\ \\ C : |z-2|=1, \\
      &=& 2 \pi i \\, \mathrm{Res}\left( \frac{\sin z}{z^3 (z-2)}, z=2 \right),\\ 
      &=& \frac{\pi i}{4} \sin 2.
    \end{eqnarray}$$
    
  - Example 2 for contour integral
 
    $$\begin{eqnarray}
    I &=& \oint_C \frac{\sin z}{z^3 (z-2)} \\, dz, \\ \\ \\ C : |z|=1, \\
      &=& 2 \pi i \\, \mathrm{Res}\left( \frac{\sin z}{z^3 (z-2)}, z=0 \right),\\
      &=& -\frac{\pi i}{2}.
    \end{eqnarray}$$


## Tips for improper integral  
  In the case of the upper or lower limit of the integration is a singular point, change the variables so that 0 is the singular point.
  This is to avoid a	loss of significant digits near the singular point. 
  When a is a singular point
  $$I = \int_a^b f(x) \\, dx = \int_0^{b-a} f(t+a) \\, dt, \\ \\ \\ x=t+a.$$


## Reference
Takahasi, Hidetosi, and Masatake Mori. "Double exponential formulas for numerical integration." Publications of the Research Institute for Mathematical Sciences 9.3 (1974): 721-741.


2022/08/05 Added examples of complex line integrals.
