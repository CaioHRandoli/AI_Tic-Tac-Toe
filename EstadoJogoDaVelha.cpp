#include "EstadoJogoDaVelha.hpp"    



EstadoJogoDaVelha::EstadoJogoDaVelha(int tabuleiro[], bool max){

    this->jogador = max;
    for(int i = 0; i < 9; i++){
        this->tabuleiro[i] = tabuleiro[i];
    }
}

EstadoJogoDaVelha * EstadoJogoDaVelha::jogaHumano(){
    int indice = -1;
    bool valido = false;

    int copia[9];
        for(int j = 0; j < 9; j++)
            copia[j] = this->tabuleiro[j];

    cout << "Selecionar a célula da sua jogada " << endl;
    while(!valido){
        cin >> indice;
        if(this->tabuleiro[indice] == 0){
            copia[indice] = -1;
            valido = true;
        }else{
            cout << "Posicao inválida" << endl;
        }
    }

    return new EstadoJogoDaVelha(copia, true);


}

 // Serve para verificar se o estado atual é terminal.
 bool EstadoJogoDaVelha::eTerminal(){
     int restantes = 0;

     for(int i = 0; i < 9; i++)
        if(this->tabuleiro[i] == 0)
            restantes++;

    if(restantes == 0)
        return true;

            //horizontal
     return this->tabuleiro[0] + this->tabuleiro[1] + this->tabuleiro[2] == 3  || 
            this->tabuleiro[0] + this->tabuleiro[1] + this->tabuleiro[2] == -3 ||
            this->tabuleiro[3] + this->tabuleiro[4] + this->tabuleiro[5] == 3  || 
            this->tabuleiro[3] + this->tabuleiro[4] + this->tabuleiro[5] == -3 ||
            this->tabuleiro[6] + this->tabuleiro[7] + this->tabuleiro[8] == 3  || 
            this->tabuleiro[6] + this->tabuleiro[7] + this->tabuleiro[8] == -3 ||
            // vertical
            this->tabuleiro[0] + this->tabuleiro[3] + this->tabuleiro[6] == 3  || 
            this->tabuleiro[0] + this->tabuleiro[3] + this->tabuleiro[6] == -3 ||
            this->tabuleiro[1] + this->tabuleiro[4] + this->tabuleiro[7] == 3  || 
            this->tabuleiro[1] + this->tabuleiro[4] + this->tabuleiro[7] == -3 ||
            this->tabuleiro[2] + this->tabuleiro[5] + this->tabuleiro[8] == 3  || 
            this->tabuleiro[2] + this->tabuleiro[5] + this->tabuleiro[8] == -3 ||
            // diagonais
            this->tabuleiro[0] + this->tabuleiro[4] + this->tabuleiro[8] == 3  || 
            this->tabuleiro[0] + this->tabuleiro[4] + this->tabuleiro[8] == -3 ||
            this->tabuleiro[2] + this->tabuleiro[4] + this->tabuleiro[6] == 3  || 
            this->tabuleiro[2] + this->tabuleiro[4] + this->tabuleiro[6] == -3;
 }

// Retorna o valor da função de avaliação dos estados terminais.
double EstadoJogoDaVelha::valorHeuristico(){
    double horizontalSuperior = this->tabuleiro[0] + this->tabuleiro[1] + this->tabuleiro[2]; 
    double horizontalCentral  = this->tabuleiro[3] + this->tabuleiro[4] + this->tabuleiro[5]; 
    double horizontalInferior  = this->tabuleiro[6] + this->tabuleiro[7] + this->tabuleiro[8];
    
    double verticalEsquerda = this->tabuleiro[0] + this->tabuleiro[3] + this->tabuleiro[6];
    double verticalCentral  = this->tabuleiro[1] + this->tabuleiro[4] + this->tabuleiro[7];
    double verticalDireita  = this->tabuleiro[2] + this->tabuleiro[5] + this->tabuleiro[8];

    double diagonalPrincipal = this->tabuleiro[0] + this->tabuleiro[4] + this->tabuleiro[8];
    double diagonalSecundaria = this->tabuleiro[2] + this->tabuleiro[4] + this->tabuleiro[6];

    if(horizontalSuperior == 3 || horizontalCentral == 3 || horizontalInferior == 3 || 
       verticalEsquerda == 3  || verticalCentral == 3 || verticalDireita == 3 ||
       diagonalPrincipal == 3 || diagonalSecundaria == 3)
        return 1;

    if(horizontalSuperior == -3 || horizontalCentral == -3 || horizontalInferior == -3 || 
       verticalEsquerda == -3  || verticalCentral == -3 || verticalDireita == -3 ||
       diagonalPrincipal == -3 || diagonalSecundaria == -3)
        return -1;

    return 0;
}
// Função expansão de estados
list<EstadoJogoDaVelha *> EstadoJogoDaVelha::getFilhos(){
    // As possíveis jogadas.
    for(int i = 0; i < 9; i++){
        int copia[9];
        for(int j = 0; j < 9; j++)
            copia[j] = this->tabuleiro[j];
        
        if(copia[i] == 0){
            if(jogador == true)
                copia[i] = 1;
            else
                copia[i] = -1;

            EstadoJogoDaVelha * novo = new EstadoJogoDaVelha(copia, !this->jogador);
            filhos.push_back(novo);
        }
    }
        
    return this->filhos;
}

bool EstadoJogoDaVelha::isMax(){
    return this->jogador;
}
    
void EstadoJogoDaVelha::setJogador(bool jogador){
    this->jogador = jogador;
}

void EstadoJogoDaVelha::printTabuleiro(){

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(this->tabuleiro[i * 3 + j] == 1)
                cout << " O ";
            else if(this->tabuleiro[i * 3 + j] == -1)
                cout << " x ";
            else
                cout << "   ";
            if(j < 2)
                cout << "|";
        }
        cout << endl;
    }
}