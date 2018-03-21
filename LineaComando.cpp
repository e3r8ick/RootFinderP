//============================================================================
// Name        : LineaComando.cpp
// Author      : Erick
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/algorithm/string.hpp>

int main(int ac, char* av[])
{
    //variables
    double poly[ac-2];

    std::cout << "Polinomio: \n";
    for (int i(1); i != ac-3; ++i){
        poly[i-1] = atof(av[i]);
        if(i==1){
            std::cout << av[i];
        }else if(i==2){
            std::cout << " + ";
            std::cout << av[i]<<"x";
        }else{
            std::cout << " + ";
            std::cout << av[i]<<"x^"<<i-1;
        }
    }
    std::cout << "\n";
    std::cout << "Orden: " << ac-5<< "\n";
    std::cout << "Método: " << av[ac-3] << "\n";

    if(strcmp(av[ac-2],"D")==0 || strcmp(av[ac-2],"F")==0){
        if(strcmp(av[ac-2],"D")==0){
            std::cout << "Precisión: Double" << "\n";
        }else{
            std::cout << "Precisión: Float" << "\n";
        }
    }else{
        std::cout << "La Precisión " << av[ac-2] << " no está soportada \n";
    }
    if(strcmp(av[ac-1],"S")==0 || strcmp(av[ac-1],"N")==0){
        if(strcmp(av[ac-1],"S")==0 ){
            std::cout << "Pulir: Si" << "\n";
        }else{
            std::cout << "Pulir: No" << "\n";
        }
    }else{
        std::cout << "El valor de Pulir " << av[ac-1] << " no es soportado\n";
    }

}
