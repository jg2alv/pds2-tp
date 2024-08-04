#ifndef JOGODAVELHA_HPP
#define JOGODAVELHA_HPP

#include <vector>
#include <string>

#include "Jogo.hpp"
#include "Jogador.hpp"

class JogoDaVelha : public Jogo {
private:
    bool tabuleiroCheio() const;
    bool jogada_valida(const Jogada &jogada) const;
    void realizar_jogada(const Jogada &jogada);

public:
    JogoDaVelha(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2);
    JogoDaVelha(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2, std::vector<std::vector<char>> tabuleiro);
    ~JogoDaVelha();

    virtual std::string getNome() const override;
    virtual void imprimirTabuleiro(std::ostream& out) const override;
    virtual bool formatoCorreto(std::string possivel_jogada) const override;
    virtual bool jogadaValida(std::string possivel_jogada) const override;
    virtual void realizarJogada(std::string possivel_jogada) override;
    virtual bool verificarVitoria(Jogador const&) const override;
    virtual bool verificarEmpate() const override;
};

#endif