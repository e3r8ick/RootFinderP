/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 *
 * @Author: 
 * @Date  : 24.02.2018
 */

#include <cstdlib>
#include <iostream>
#include "deflate.hpp"
#include "deflate2.hpp"
#include "muller.hpp"
#include <boost/math/tools/polynomial.hpp>
using namespace boost::math::tools;

int main() {

  polynomial<double> const poli({-12,-13,0,1});
  double x = anpi::muller(poli, 0.0, 0.1, true);
  std::cout << x << std::endl;
  return EXIT_SUCCESS;
  
  //polynomial<double> const pol{{-18,9,7,1,1}};
  //std::complex<double> root = anpi::muller(pol, std::complex<double>(0.0), std::complex<double>(1.0), std::complex<double>(-1.0));
  //std::cout << root.real() << "+ i" << root.imag() << std::endl;
  //double root = anpi::muller(poli, 0.0, 3.0, -1.0);
  //std::cout << root << std::endl;
}
  
