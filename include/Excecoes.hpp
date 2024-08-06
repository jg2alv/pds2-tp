#ifndef EXCECAO_HPP
#define EXCECAO_HPP

#include <string>
#include <exception>

class Excecao : public std::runtime_error {
private: 
    std::string _mensagem; 
  
public: 
    Excecao(std::string mensagem);
    const char* what() const throw();
};

class ExcecaoDoJogoDaVelha : public Excecao {
private: 
    std::string _mensagem; 
  
public: 
    ExcecaoDoJogoDaVelha(std::string mensagem);
    const char* what() const throw();
};

class ExcecaoDoLig4 : public Excecao {
private: 
    std::string _mensagem; 
  
public: 
    ExcecaoDoLig4(std::string mensagem);
    const char* what() const throw();
};

class ExcecaoDoReversi : public Excecao {
private: 
    std::string _mensagem; 
  
public: 
    ExcecaoDoReversi(std::string mensagem);
    const char* what() const throw();
};

class ExcecaoDoSistema : public Excecao {
private: 
    std::string _mensagem; 
  
public: 
    ExcecaoDoSistema(std::string mensagem);
    const char* what() const throw();
};

class ExcecaoDoXadrez : public Excecao {
private: 
    std::string _mensagem; 
  
public: 
    ExcecaoDoXadrez(std::string mensagem);
    const char* what() const throw();
};

#endif
