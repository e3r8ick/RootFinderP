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
#include "RootBisection.hpp"

namespace anpi
{
  namespace test
  {

    /// Square of a number
    template <typename T>
    inline T sqr(const T x) { return x * x; }

    /// First testing function for roots |x|=e^(-x)
    template <typename T>
    T t1(const T x) { return std::abs(x) - std::exp(-x); }

    /// Second testing function for roots e^(-x²) = e^(-(x-3)²/3 )
    template <typename T>
    T t2(const T x) { return std::exp(-x * x) - std::exp(-sqr(x - T(3)) / T(3)); }

    /// Third testing function for roots x² = atan(x)
    template <typename T>
    T t3(const T x) { return x * x - std::atan(x); }

    /// Test the given closed root finder
    template <typename T>
    void rootTest(const std::function<T(const std::function<T(T)> &,
                                        T,
                                        T)> &solver)
    {
      T sol = solver(t1<T>, T(4), T(2));
      BOOST_CHECK(!std::isnan(sol));
      sol = solver(t1<T>, T(2), T(4));
      BOOST_CHECK(std::isnan(sol));
    }
  } // test
} // anpi

BOOST_AUTO_TEST_SUITE(RootFinder)

BOOST_AUTO_TEST_CASE(Bisection)
{
  anpi::test::rootTest<float>(anpi::rootBisection<float>);
  anpi::test::rootTest<double>(anpi::rootBisection<double>);
}

BOOST_AUTO_TEST_SUITE_END()