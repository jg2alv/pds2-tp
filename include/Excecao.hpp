#ifndef EXCECAO_HPP
#define EXCECAO_HPP

#include <string>
#include <exception>
#include <iostream>

class Excecao : public std::runtime_error {
private: 
    std::string _mensagem; 
  
public: 
    Excecao(std::string mensagem);
    const char* what() const throw();
};

#endif