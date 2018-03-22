/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 *
 * @Author: 
 * @Date  : 24.02.2018
 */

#include "laguerre.hpp"
#include <cstdlib>
#include <iostream>
#include "deflate.hpp"
#include "deflate2.hpp"
#include "muller.hpp"
#include <boost/math/tools/polynomial.hpp>
using namespace boost::math::tools;

int main(int ac, char *av[])
{
  /*
  polynomial<double> const poli({-1,-2,3});
  std::array<double, 3> roots;
  anpi::muller(poli, 0.0, 0.1, true, roots);
  for (int i = 0; i< 3; i++){
    std::cout << roots[i] << std::endl;
  }
  double root = anpi::laguerre(poli, 0.1);
  std::cout << root << std::endl;
  return EXIT_SUCCESS;

*/
  //variables
  bool pulir;

  if (strcmp(av[ac - 1], "S") == 0 || strcmp(av[ac - 1], "N") == 0)
  {
    if (strcmp(av[ac - 1], "S") == 0)
    {
      pulir = true;
    }
    else
    {
      pulir = false;
    }
  }
  else
  {
    std::cout << "El valor de Pulir " << av[ac - 1] << " no es soportado\n";
    return EXIT_FAILURE;
  } //end pulir

  if (strcmp(av[ac - 2], "D") == 0 || strcmp(av[ac - 2], "F") == 0)
  {
    if (strcmp(av[ac - 2], "D") == 0)
    {
      double poly[ac - 4];
      for (int i(1); i != ac - 3; ++i)
      {
        poly[i - 1] = atof(av[i]);
      }

      polynomial<double> poli = polynomial<double>(poly, (uint)ac - 2);
      double roots[ac - 5];
      if (strcmp(av[ac - 3], "muller") == 0)
      {
        if (std::isnan(anpi::muller(poli, 0.0, 0.1, true, roots, ac-5)))
        {
          std::cout << "No se encontró raíz" << std::endl;
          return EXIT_FAILURE;
        }
        else
        {
          for (int i = 0; i < ac - 5; i++)
          {
            std::cout << roots[i] << std::endl;
            return 1;
          }
        }
      }
      else if (strcmp(av[ac - 3], "laguerre") == 0)
      {
        if (std::isnan(anpi::laguerre(poli, 0.0, 0.1, true, roots, ac-5)))
        {
          std::cout << "No se encontró raíz" << std::endl;
          return EXIT_FAILURE;
        }
        else
        {
          for (int i = 0; i < ac - 5; i++)
          {
            std::cout << roots[i] << std::endl;
            return 1;
          }
        }
      }
      else
      {
        std::cout << "El método " << av[ac - 3] << " no existe. Seleccione muller o laguerre." << std::endl;
        return EXIT_FAILURE;
      }
    }
    else
    {
      float poly[ac - 4];
      for (int i(1); i != ac - 3; ++i)
      {
        poly[i - 1] = atof(av[i]);
      }
      polynomial<float> poli = polynomial<float>(poly, (uint)ac - 2);
      float roots[ac - 5];
    }
  }
  else
  {
    std::cout << "La Precisión " << av[ac - 2] << " no está soportada \n";
    return EXIT_FAILURE;
  } //End crear polinomio
}