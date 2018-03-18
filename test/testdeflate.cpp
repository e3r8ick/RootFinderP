/**
 * Copyright (C) 2017 
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 *
 * @Author: Pablo Alvarado
 * @Date  : 10.02.2018
 */

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <exception>
#include <cstdlib>
#include <complex>
#include <functional>
#include <cmath>
#include "deflate.hpp"

using namespace boost::math::tools;
namespace anpi
{
  namespace test
  {

    template <typename T>
    void testDeflate(){
        polynomial<double> res {{0}};
        polynomial<double> const poly{{-6, 13, -6, -3, 2 }};
        polynomial<T> sol = deflate(poly, T(1), res);
        std::cout << res[0] << std::endl;
        BOOST_CHECK(res[0]  == 0);

    }

  } // test
} // anpi

BOOST_AUTO_TEST_SUITE(RootFinder)
BOOST_AUTO_TEST_CASE(DEFLATE){
    anpi::test::testDeflate<double>();
}
BOOST_AUTO_TEST_SUITE_END()