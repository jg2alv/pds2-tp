#include <iostream>
#include <string>

#include "Jogador.hpp"
#include "Sistema.hpp"
#include "ClassePai.hpp"

int main()
{
    Sistema* sistema = new Sistema();

    while (1)
    {
        std::string comando;
        std::cin >> comando;
        Comando comandoAnalisado = sistema->AnalisarComando(comando);

        switch (comandoAnalisado)
        {
        case Comando::CJ: {
            std::string apelido, nome;
            std::cin >> apelido >> nome;
            std::cout << apelido << std::endl;
            break;
        }
        
        case Comando::RJ:
            break;

        case Comando::LJ:
            break;

        case Comando::EP:
            break;

        case Comando::FS:
            break;

        case Comando::IN:
            break;
        }
    }

    free(sistema);

    return 0;
}
