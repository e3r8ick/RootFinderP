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

  polynomial<double> const poli({0.600002,-6.10002,0.90001,1});
  std::array<double, 3> roots;
  anpi::muller(poli, 0.0, 0.1, true, roots);
  for (int i = 0; i < 3; ++i){
    
    std::cout << roots[i] << std::endl;
  }
  return EXIT_SUCCESS;
}