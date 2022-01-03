# gmp
:exclamation: This is a read-only mirror of the CRAN R package repository.  gmp — Multiple Precision Arithmetic. Homepage: https://forgemia.inra.fr/sylvain.jasson/gmp  

This local version will contain methods for convolving vectors of big rationals.

**Test Package**

*Note: This requires R to be installed on your local PC.*
1. Git clone / copy this repo into your local PC.
2. On the terminal, navigate to directory containing the `gmp` repo. 
3. Type `R CMD build gmp`; this builds the package. You should see `gmp_0.6-2.1.tar.gz` located in the current working directory.
4. *(Test installation on local PC)* Type `R CMD INSTALL gmp_0.6-2.1.tar.gz`; this installs the package. 
5. *(Test usage in R)* Type `R`. Type `install.packages("gmp_0.6-2.1.tar.gz")`. Type `library(gmp)`.


**(12/30/21)** 
Add `operatorCONV` in `bigrational.cc`. Package no longer compiles. Error seems to be with `bigrational`s not having "size" attributes or indexing. Now I'm not sure how `add.bigq` in **R** works for two vectors (e.g., `add.bigq(as.bigq(c(1,2,3)),as.bigq(c(4,5)))`). According to source code `add.bigq` calls `bigrational_add`, which is a two-variable function with `bigrational` arguments. Given that `add.bigq` works perfectly fine when its arguments are vectors, why doesn't `operatorCONV` work?   

**(1/3/22)**
Good news - got a version of `conv.bigq` working. I accomplish this via the following steps:
- Create a back-end C++ function `bigrational_conv`. This requires editing the following files
    - `src/bigrationalR.cc`: define `bigrational_conv`. This is similar to how a bunch of `bigrational_` back-end methods are defined.
    - `src/bigrationalR.h`: declare the function in header file. 
- Give R access to back-end C++ function by defining `conv.bigq`. This requires editing the following files
    - `R/bigq.R`: stub to call all back-end / underlying C++ functions. Define `conv.bigq` here.
    - `src/init.cc`: ensures registration of `conv.bigq`.
    - `NAMESPACE`: DynLib stuff that also ensures registration of `conv.bigq`.

Hurray! Now the bad news. The function `conv.bigq` turns out to be very slow! I am surprised, given that I expected static compiling in C++ to manifest in huge speed gains when compared against R's dynamic compiling. 