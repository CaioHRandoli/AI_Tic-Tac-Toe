#ifndef ESTADO_HPP
#define ESTADO_HPP

#include <list>

using namespace std;

class Estado{

public:    
    // Serve para verificar se o estado atual é terminal.
    virtual bool eTerminal() = 0;
    // Retorna o valor da função de avaliação dos estados terminais.
    virtual double valorHeuristico() = 0;
    // Função expansão de estados
    virtual list<Estado *> getFilhos() = 0;

};

#endif