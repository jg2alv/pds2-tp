#ifndef EXCECAO_HPP
#define EXCECAO_HPP

#include <string>
#include <exception>
#include <iostream>


/**
 * \brief Classe de exceções genérica usada em todo o projeto.
 *
 * Essa é uma classe derivada de `std::runtime_error` que é lançada por diferentes partes do programa e capturada a fim de mostrar uma mensagem de erro.
 */
class Excecao : public std::runtime_error {
private: 
    std::string _mensagem; 
  
public: 
    Excecao(std::string mensagem);
    const char* what() const throw();
};

#endif
