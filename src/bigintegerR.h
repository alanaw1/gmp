/*! \file bigintegerR.h
 *  \brief header for C++ functions used with R
 *
 *  \version 1
 *
 *  \date Created: 2006   
 *  \date Last modified: Time-stamp: <2006-06-11 20:32:59 antoine>
 *
 *
 *  \note Licence: GPL
 */

#ifndef BIGINTEGERRRRRRR_HEADER_
#define BIGINTEGERRRRRRR_HEADER_ 1

#include "bigvec.h"

#ifndef T_BIGMOD_BINARY_OPERATION
#define T_BIGMOD_BINARY_OPERATION 1
/// A pointer to a binary operator for bigintegers
typedef bigmod (*biginteger_binary_fn)(const bigmod&, const bigmod&);
#endif

#ifndef T_BIGMOD_BINARY_OPERATION_LOGICAL
#define T_BIGMOD_BINARY_OPERATION_LOGICAL 1
typedef bool (*biginteger_logical_binary_fn)(const biginteger&, const biginteger&);
#endif

/**
 * \brief set of function usefull for manipulation of SEXP and bigvec
 */
namespace bigintegerR{

  /** \brief create a vector of bigmod, all without a modulus.
   */
  bigvec create_vector(SEXP param);

  /**
   * \brief create a vector of bigmod
   */
  bigvec create_bignum(SEXP param);

  /**
   * \brief create a vector of int
   */
  std::vector<int> create_int(SEXP param) ;


  /**
   * \brief export vector of biginteger to R value
   */
  SEXP create_SEXP(const std::vector<biginteger>& v) ;

  /**
   * \brief export bigvec to R value
   */
  SEXP create_SEXP(const bigvec & v);
  
  SEXP biginteger_binary_operation(SEXP a, SEXP b, biginteger_binary_fn f);

  SEXP biginteger_logical_binary_operation(SEXP a, SEXP b, biginteger_logical_binary_fn f);

  bool lt(const biginteger& lhs, const biginteger& rhs);
  
  bool gt(const biginteger& lhs, const biginteger& rhs) ;

  bool lte(const biginteger& lhs, const biginteger& rhs);

  bool gte(const biginteger& lhs, const biginteger& rhs);

  bool eq(const biginteger& lhs, const biginteger& rhs);

  bool neq(const biginteger& lhs, const biginteger& rhs);

  /** \brief return va[b] */
  bigvec biginteger_get_at_C(bigvec va,SEXP b);
}


extern "C"
{
  /**
   * \brief Addition of a and b
   */
  SEXP biginteger_add(SEXP a, SEXP b);

  /**
   * \brief Subtraction of a and b
   */
  SEXP biginteger_sub(SEXP a, SEXP b);

  /**
   * \brief Multiplication of a and b
   */
  SEXP biginteger_mul(SEXP a, SEXP b);

  /**
   * \brief Quotient of a / b
   */
  SEXP biginteger_div(SEXP a, SEXP b);

  /**
   * \brief Modulus of a % b
   */
  SEXP biginteger_mod(SEXP a, SEXP b);

  /**
   * \brief Power of base a to exponent b
   */
  SEXP biginteger_pow(SEXP a, SEXP b);

  /**
   * \brief Inverse from a mod b
   */
  SEXP biginteger_inv(SEXP a, SEXP b);

  /**
   * \brief Greatest common divisor of a and b
   */
  SEXP biginteger_gcd(SEXP a, SEXP b);

  /**
   * \brief Least common multiply of a and b
   */
  SEXP biginteger_lcm(SEXP a, SEXP b);
    
  /**
   * \brief Sets the intern modulus of a to b
   */
  SEXP biginteger_setmod(SEXP a, SEXP b);

   
  /**
   * \brief Return from vector a all elements specified in vector b
   */
  SEXP biginteger_get_at(SEXP a, SEXP b);
    
  /**
   * \brief Return a vector with the values from src specified by 
   * idx to sequentiell values from "value".
   */
  SEXP biginteger_set_at(SEXP src, SEXP idx, SEXP value);
    
  /**
   * \brief Convert from an long value or a string into biginteger.
   *
   * If you want a modulus-set-bigint, just use 
   * as.biginteger(value, modulus)
   */
  SEXP biginteger_as(SEXP a, SEXP mod);

  /**
   * \brief Convert from a biginteger vector to a character string vector.
   */
  SEXP biginteger_as_character(SEXP a,SEXP b);

  /**
   * \brief Convert from a biginteger vector to a real vector.
   */
  SEXP biginteger_as_numeric(SEXP a);

  /**
   * \brief Return the length of the vector
   */
  SEXP biginteger_length(SEXP a);

  /**
   * \brief Returns a resized vector cut at end or filled with NA.
   */
  SEXP biginteger_setlength(SEXP vec, SEXP value);

  /**
   * \brief Return whether the parameter is NA
   */
  SEXP biginteger_is_na(SEXP a);


  /**
   * \brief Return sign of a
   */
  SEXP biginteger_sgn(SEXP a) ;

  /**
   * \brief Return whether a < b
   */
  SEXP biginteger_lt(SEXP a, SEXP b);
    
  /**
   * \brief Return whether a > b
   */
  SEXP biginteger_gt(SEXP a, SEXP b);
    
  /**
   * \brief Return whether a <= b
   */
  SEXP biginteger_lte(SEXP a, SEXP b);
    
  /**
   * \brief Return whether a >= b
   */
  SEXP biginteger_gte(SEXP a, SEXP b);
    
  /**
   * \brief Return whether a == b
   */
  SEXP biginteger_eq(SEXP a, SEXP b);
    
  /**
   * \brief Return whether a != b
   */
  SEXP biginteger_neq(SEXP a, SEXP b);

  /**
   * \brief For function c()
   */
  SEXP biginteger_c(SEXP args) ;
  
  /** \brief for function cbind()
   */

  SEXP biginteger_cbind(SEXP args) ;

  /**
   * \brief Create vector as n times x
   */
  SEXP biginteger_rep(SEXP x, SEXP times) ;

  /**
   * \brief Return if a is prime with a proba test
   */
  SEXP biginteger_is_prime(SEXP a, SEXP reps) ;  

  /**
   * \brief Return next prime with a proba test
   */
  SEXP biginteger_nextprime(SEXP a) ;


  /**
   * \brief Return absolute value of a
   */
  SEXP biginteger_abs(SEXP a) ;

  /**
   * \brief Return bezoult coefficients
   */
  SEXP biginteger_gcdex(SEXP a, SEXP b) ;

  /** 
   * \brief Random number generation
   */ 
  SEXP biginteger_rand_u (SEXP nb ,SEXP length,SEXP newseed, SEXP ok);

  /**
   * \brief Give size of integer 
   */
  SEXP biginteger_sizeinbase (SEXP x, SEXP exp);


  /**
   * \brief Compute Fibonacci number
   */
  SEXP fibnum(SEXP n) ;

  /**
   * \brief Compute Fibonacci number
   */

  SEXP fibnum2(SEXP n) ;
  /**
   * \brief Compute lucas number
   */
  SEXP lucnum(SEXP n) ;

  /**
   * \brief Compute lucas number
   */
  SEXP lucnum2(SEXP n) ;

}



#endif
