#include <iostream>
#include <cfloat>
#include <algorithm>
#include "Estado.hpp"
#include "EstadoJogoDaVelha.hpp"

#include <list>

#define MAX_PROFUNDIDADE 9

EstadoJogoDaVelha * melhor;
double melhorH = -DBL_MAX;

using namespace std;

// Implementação do Minimax
double minimax(EstadoJogoDaVelha * atual, bool jogadorMax, double alpha, double beta, int profundidade){

    // Verifica se estamos no estado terminal ou atingimos a profundidade máxima
    if(atual->eTerminal() || profundidade == 0){
        // Temos um terminal, devemos calcular a função de avaliação.
        return atual->valorHeuristico();
    }

    // Valor heurístico do estado.
    double h;
    
    if(jogadorMax){
        // é a vez do MAX
        
        // Inicializar o valor com menos infinito
        h = -DBL_MAX;

        // Expandir os filhos de MAX
        list<EstadoJogoDaVelha * > filhos = atual->getFilhos();
        // Andar por cada filho.
        for(list<EstadoJogoDaVelha *>::iterator it = filhos.begin(); it != filhos.end(); it++){
            h = max(h, minimax(*it, false, alpha, beta, profundidade - 1));
            alpha = max(h, alpha);

            // Estou olhando a raiz.
            if(profundidade == MAX_PROFUNDIDADE){
                // Melhor jogada avaliada da IA.
                if(h > melhorH){
                    melhorH = h;
                    // Apontando para o filho da raíz com maior h propagado.
                    melhor = *it;
                }
            }

            // PODA!
            if(alpha >= beta)
                return h;
        }


    }else{
        // é a vez do MIN
        
        // Inicializar o valor com mais infinito
        h = DBL_MAX;

        // Expandir os filhos de MIN
        list<EstadoJogoDaVelha * > filhos = atual->getFilhos();
        // Andar por cada filho.
        for(list<EstadoJogoDaVelha * >::iterator it = filhos.begin(); it != filhos.end(); it++){
            h = min(h, minimax(*it, true, alpha, beta, profundidade - 1));
            beta = min(h, beta);

            // PODA!
            if(alpha >= beta)
                return h;
        }
    }
    return h;
}



int main(){

    int tabuleiro[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    EstadoJogoDaVelha * atual = new EstadoJogoDaVelha(tabuleiro, true); 


    atual->printTabuleiro();

    atual = atual->jogaHumano();
    cout << "Jogada do Humano: " << endl;
    atual->printTabuleiro(); 


    while(!atual->eTerminal()){
        melhorH = -DBL_MAX;
        int valor = minimax(atual, true, -DBL_MAX, DBL_MAX, MAX_PROFUNDIDADE);
        
        // Apontar a jogada da IA.
        atual = melhor;
        cout << "Jogada da IA: " << endl;
        atual->printTabuleiro(); 
        cout << endl;

        if(atual->eTerminal())
            break;

        atual = atual->jogaHumano();
        cout << "Jogada do Humano: " << endl;
        atual->printTabuleiro(); 
        cout << endl;
    }

    cout << "Jogo encerrado!" << endl;
    if(atual->valorHeuristico() > 0){
        cout << "IA VENCEU!!!" << endl;
    }else if(atual->valorHeuristico() < 0){
        cout << "HUMANO VENCEU!!!" << endl;
    }else{
        cout << "EMPATOU!!!" << endl;
    }
    return 0;
}