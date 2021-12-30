# gmp
:exclamation: This is a read-only mirror of the CRAN R package repository.  gmp — Multiple Precision Arithmetic. Homepage: https://forgemia.inra.fr/sylvain.jasson/gmp  

This local version will contain methods for convolving vectors of big rationals.

**(12/30/21)** 
Add `operatorCONV` in `bigrational.cc`. Package no longer compiles. Error seems to be with `bigrational`s not having "size" attributes or indexing. Now I'm not sure how `add.bigq` in **R** works for two vectors (e.g., `add.bigq(as.bigq(c(1,2,3)),as.bigq(c(4,5)))`). According to source code `add.bigq` calls `bigrational_add`, which is a two-variable function with `bigrational` arguments. Given that `add.bigq` works perfectly fine when its arguments are vectors, why doesn't `operatorCONV` work?   

