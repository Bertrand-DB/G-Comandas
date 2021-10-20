#include "Comanda.h"
#include <iostream>
#include <stddef.h>
#include <string>
#include "Pedido.h"
#define MAX_CMD 20

Comanda::Comanda(){

}

Comanda::Comanda(Pedido* pedid)
{
    this->pedidos[0] = pedid;         // � criado o primeiro pedido da comanda
    for(int i = 1; i < MAX_CMD; i++){
        this->pedidos[i] = nullptr;   // E todos os outros pedidos recebem null
    }
}

Comanda::~Comanda()
{
    for(int i = 0; i < MAX_CMD; i++){
        this->pedidos[i] = nullptr;
    }
}

void Comanda::addPedido(Pedido* pedid){
    int i;
    for(i = 0; i < MAX_CMD; i++){
        if(pedidos[i] == nullptr)
            break;
    }
    this->pedidos[i] = pedid;    // Para adicionar um pedido, � verificado qual endere�o dentro do array est� vazio
                                 // Depois de achar o espa�o, � criado o novo pedido
}

Pedido* Comanda::getPedidos(int i){
    return this->pedidos[i];
}

void Comanda::fecharUmItem(Pedido* pedid){
    for(int i = 0; i < MAX_CMD; i++){
        if(pedidos[i] == pedid){
            pedidos[i] = nullptr; // Para fechar um item � atribuido null novamente para o pedido selecionado.
        }
    }
}

int Comanda::setQuantidade(int quantidade, std::string prato){

    for (size_t i = 0; i < 10 ; i++)
    {
        if (pedidos[i]->getStrPrato().find(prato) != std::string::npos)
        {
            pedidos[i]->setQuantidade(quantidade);
            return 0;
        }
    }
    return 1;
}

void Comanda::setOrdem(int o){
    ordem = o;
}
int Comanda::getOrdem(){
    return ordem;
}
