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
#include <boost/math/tools/polynomial.hpp>
using namespace boost::math::tools;

int main() {

  // Put your main code in here
  polynomial<double> res {{0}};
  polynomial<double> const a{{1.0, 0, 8.0, 1.0}};
  polynomial<double> const b = anpi::deflate(a, 3.0, res);  
  std::cout << "Residuo: " << res[0] << std::endl;
  for (int i = b.size() ; i >= 0; --i ){
    std::cout <<b[i];
    std::cout << ",";
  }
  std::cout << std::endl;
  
  return EXIT_FAILURE;
}
  
