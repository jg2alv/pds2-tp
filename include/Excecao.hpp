#ifndef EXCECAO_HPP
#define EXCECAO_HPP

#include <string>
#include <exception>

using namespace std;

class Excecao : public exception {
private: 
    string mensagem; 
  
public: 
    Excecao(string mensagem);
    const char* what() const throw();
};

#endif