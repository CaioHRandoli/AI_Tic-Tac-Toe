#ifndef ESTADO_VELHA
#define ESTADO_VELHA

#include "Estado.hpp"
#include <list>
#include <iostream>
#include <cstdlib>

class EstadoJogoDaVelha{

public:
    EstadoJogoDaVelha(int tabuleiro[], bool max);

    // Serve para verificar se o estado atual é terminal.
    bool eTerminal();
    // Retorna o valor da função de avaliação dos estados terminais.
    double valorHeuristico();
    // Função expansão de estados
    list<EstadoJogoDaVelha *> getFilhos();

    bool isMax();
    void setJogador(bool jogador);

    void printTabuleiro();

    EstadoJogoDaVelha * jogaHumano();

private:
    bool jogador;
    int tabuleiro[9];
    list <EstadoJogoDaVelha *> filhos;

};
#endif