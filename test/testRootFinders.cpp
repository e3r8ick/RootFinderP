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

namespace anpi {
  namespace test {

    /// Square of a number
    template<typename T>
    inline T sqr(const T x) { return x*x; }

    /// First testing function for roots |x|=e^(-x)
    template<typename T>
    T t1(const T x)  { return std::abs(x)-std::exp(-x); }

    /// Second testing function for roots e^(-x²) = e^(-(x-3)²/3 )
    template<typename T>
    T t2(const T x) { return std::exp(-x*x) - std::exp(-sqr(x-T(3))/T(3)); }

    /// Third testing function for roots x² = atan(x)
    template<typename T>
    T t3(const T x)  { return x*x-std::atan(x); }

    enum TestIntervalMode {
      TestInterval,
      DoNotTestInterval
    };
    
    /// Test the given closed root finder
    template<typename T>
    void rootTest(const std::function<T(const std::function<T(T)>&,
                                        T,
                                        T,
                                        const T)>& solver,
                  const TestIntervalMode testInterval=TestInterval) {

      
      for (T eps=T(1)/T(10); eps>static_cast<T>(1.0e-7); eps/=T(10)) {
        T sol = solver(t1<T>,T(0),T(2),eps);
        BOOST_CHECK(std::abs(t1<T>(sol))<eps);
        sol = solver(t2<T>,T(0),T(2),eps);
        BOOST_CHECK(std::abs(t2<T>(sol))<eps);
        sol = solver(t3<T>,T(0),T(0.5),eps);
        BOOST_CHECK(std::abs(t3<T>(sol))<eps);
      }
    }

      } // test
}  // anpi

BOOST_AUTO_TEST_SUITE( RootFinder )

BOOST_AUTO_TEST_CASE(Bisection) 
{
  anpi::test::rootTest<float>(anpi::rootBisection<float>);
  anpi::test::rootTest<double>(anpi::rootBisection<double>);
}


BOOST_AUTO_TEST_SUITE_END()
