# de_int
This is the numerical integration program using double exponential transformation. 
This code can calculate the integral from a to b and the integral from a to infinity shown by the following formulae.
It also supports the integration of complex functions.
I made it to integrate a complex function which has a singular point.

<img src="https://latex.codecogs.com/gif.latex?I=\int_a^bf(x)\,dx">  
<img src="https://latex.codecogs.com/gif.latex?I=\int_a^{\infty}f(x)\,dx">  

<img src="https://latex.codecogs.com/gif.latex?f(x)"> needs to be analytic within the integral region.  


## Usage of the example code
 1. type 'make' command to compile.
 2. type './example.out' to run.
 
Please see de_int.h for detail of functions, example.c for detail of function usages.


## Regarding the examples
- Example 1  
  <img src="https://latex.codecogs.com/gif.latex?I=\int_a^b\frac{1}{\cos^2(x)}\,dx=\tan(b)-\tan(a)">
  
- Example 2  
  <img src="https://latex.codecogs.com/gif.latex?I=\int_a^b\exp(ix)\,dx=-i(\exp(ib)-\exp(ia))">
  
- Example 3  
  <img src="https://latex.codecogs.com/gif.latex?I(s)=\int_0^{\infty}\exp(-sx)\,dx=\frac{1}{s}">, 
  <img src="https://latex.codecogs.com/gif.latex?s>0">

- Example 4  
  <img src="https://latex.codecogs.com/gif.latex?I(s)=\int_0^{\infty}x\exp(-sx)\,dx=\frac{1}{s^2}">, 
  <img src="https://latex.codecogs.com/gif.latex?\Re{s}>0">

Examples 3 and 4 are known as Laplace transform related to the Heaviside step function.


## Reference
Takahasi, Hidetosi, and Masatake Mori. "Double exponential formulas for numerical integration." Publications of the Research Institute for Mathematical Sciences 9.3 (1974): 721-741.
