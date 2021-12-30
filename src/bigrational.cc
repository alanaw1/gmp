/*! \file bigrational.cc
 *  \brief Implementation of class bigrational
 *
 *  \version 1
 *
 *  \date Created: 12/12/04
 *  \date Last modified: Time-stamp: <2014-07-10 08:31:28 antoine>
 *
 *  \author Antoine Lucas (adapted from biginteger class made by
 *                         Immanuel Scholz)
 *
 *  \note Licence: GPL (>= 2)
 */

#define USE_RINTERNALS
#define R_NO_REMAP   // avoid collisions with stl definitions

#include "bigrational.h"
#include "bigrationalR.h"
#include <Rinternals.h>

#include <stdio.h>
#include <vector.h>

using std::string;


bigrational & bigrational::operator= (const bigrational& rhs)
{
  if(this != &rhs)
    {
      mpq_set(value, rhs.getValueTemp());
      na= rhs.na;
    }
  return(*this);

}


/**
 * \brief Print value
 */
std::string bigrational::str(int b) const
{
  if (isNA())
    return "NA";

  unsigned int totSize = mpz_sizeinbase(mpq_numref(value),b) + \
    mpz_sizeinbase(mpq_denref(value),b) + 3 ;
  char* buf = new char[totSize];
  mpq_get_str(buf, b, value);
  std::string s = buf;
  delete [] buf;
  return s;

}


/* \brief  simplify n/d (use of mpq_canonical)
 *
 */
void  bigrational::simplify ()
{
  mpq_canonicalize(value);
}


// size of numerator !!
size_t bigrational::raw_size() const
{
  if (isNA())
    return sizeof(int);

  int numb = 8*sizeof(int);

  return sizeof(int) * (2 + (mpz_sizeinbase(mpq_numref(value),2)+numb-1) / numb);
}

// set numerator
bigrational::bigrational(void* raw):
  value(),
  na(true)
{
  mpz_t tmpVal;
  mpz_init(tmpVal);
  mpz_t_sentry val_s(tmpVal);

  mpq_init(value);

  int* r = (int*)raw;
  if (r[0]>0)
    {
      mpz_import(tmpVal, r[0], 1, sizeof(int), 0, 0, &r[2]);
      if(r[1]==-1)
	mpz_neg(tmpVal,tmpVal);
      na = false;
      mpq_set_z(value,tmpVal);
    }

}

bigrational operator+(const bigrational& lhs, const bigrational& rhs)
{
  return bigrationalR::create_bigrational(lhs, rhs, mpq_add);
}

/**
 * \brief Return  a - b
 */
bigrational operator-(const bigrational& lhs, const bigrational& rhs)
{
  return bigrationalR::create_bigrational(lhs, rhs, mpq_sub);
}

/**
 * \brief Return  a * b
 */
bigrational operator*(const bigrational& lhs, const bigrational& rhs)
{
  return bigrationalR::create_bigrational(lhs, rhs, mpq_mul);
}

/**
 * \brief Return  a / b
 */
bigrational operator/(const bigrational& lhs, const bigrational& rhs)
{

  return bigrationalR::create_bigrational(lhs, rhs, mpq_div, false);
}

/**
 * \brief Return  a ^ b
 */
bigrational operator^(const bigrational& lhs, const biginteger& rhs)
{
  // if (base == 1  or  exp == 0)  return 1
  if((!lhs.isNA() && !mpq_cmp_si(lhs.getValueTemp(), 1,1)) ||
     (!rhs.isNA() && !mpz_cmp_si(rhs.getValueTemp(), 0)))
    return bigrational(1);
  if (lhs.isNA() || rhs.isNA())
    return bigrational();

  return bigrationalR::create_bigrational_z(lhs, rhs, bigrationalR::mpqz_pow);
}

/**
 * \brief Return  conv( a, b )
 */
bigrational operatorCONV(const bigrational& lhs, const bigrational& rhs)
{
  /* get sizes of each vector */
  int n_xa = lhs.size();
  int n_xb = rhs.size();

  /* initialize big rational of size */
  bigrational xab(n_xa + n_xb - 1);
  
  /* fill in the entries */
  Rcpp::Range r(0, n_xb-1);
  for (int i=0; i<n_xa; i++, r++) {
    xab[r] = bigrationalR::create_bigrational(xab[r], bigrationalR::create_bigrational(lhs[i], rhs, mpq_mul), mpq_add);
  }

  /* return */
  return xab;
}

//
bool operator!=(const bigrational& lhs, const bigrational& rhs)
{
  if(rhs.isNA() || lhs.isNA())
    return(false); // SHOULD RETURN NA

  return(mpq_cmp(lhs.getValueTemp(),rhs.getValueTemp()) != 0);
}

bool operator>(const bigrational& lhs, const bigrational& rhs)
{
  if(rhs.isNA() || lhs.isNA())
    return(false); // SHOULD RETURN NA

  return(mpq_cmp(lhs.getValueTemp(),rhs.getValueTemp()) > 0);
}

bool operator<(const bigrational& lhs, const bigrational& rhs)
{
  if(rhs.isNA() || lhs.isNA())
    return(false); // SHOULD RETURN NA

  return(mpq_cmp(lhs.getValueTemp(),rhs.getValueTemp()) < 0);
}

/**
 * \brief Well... an heritage from biginteger class, this should be
 * integrated earlier... put denominator & simplify if there is not.
 */
// R  as.bigq() :
bigrational set_denominator(const bigrational& lhs, const bigrational& rhs)
{
  return bigrationalR::create_bigrational(lhs, rhs, mpq_div, false);
}

// return 1/x
bigrational bigrational::inv()
{
  if(isNA())
    return(bigrational());

  mpq_t tmpVal;
  mpq_init(tmpVal);
  mpq_t_sentry val_s(tmpVal);

  mpq_inv(tmpVal,value);

  return(bigrational(tmpVal));
}
