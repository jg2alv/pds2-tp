#ifndef EXCECAO_HPP
#define EXCECAO_HPP

#include <string>
#include <exception>

class Excecao : public std::exception {
private: 
    std::string _mensagem; 
  
public: 
    Excecao(std::string mensagem);
    const char* what() const throw();
};

#endif
