#include "Menu.h"
#include <iostream>
#include "Comanda.h"
#include "Cliente.h"
#include "Delivery.h"
#include "Pedido.h"
#define MAX_CMD 20
#define MAX_PRATO 11


using namespace std;

Menu::Menu() /* No construtor no menu, � especificado a inicializa��o das comandas recebendo "nullptr", ou seja,
                comanda vazias. */
{
    for(int i = 0; i < MAX_CMD; i++){
        this->client[i] = nullptr;
    }
}

Menu::~Menu()
{
    //dtor
}

int Menu::opcao1(int tPedidos){
    int prato, quantidade, i;
    std::string identidade;  /* Na op��o 1, � criada uma nova comanda, nesse metodo � perguntado qual o prato e a
                                 quantidade de pratos desejada. Logo depois, � criado o pedido e a comanda atual, que �
                                 salva na primeira comanda que recebe "nullptr", ou seja, a primeira comanda vazia. */

    cout << "Digite o numero do prato desejado: " << endl;
    cin >> prato;
    if(prato <= 0 || prato > MAX_PRATO){
        setErro(prato);
        return 0;
    }
    cout << "Quantidade do prato: " << endl;
    cin >> quantidade;
    if(quantidade <= 0){
        setErro(quantidade);
        return 0;
    }
    cout << "Id do Cliente: " << endl;
    cin >> identidade;


    Pedido* pdd = new Pedido();
    pdd->setPrato(prato);
    pdd->setQuantidade(quantidade);
    Cliente* clie = new Cliente(identidade);

    for(i = 0; i < MAX_CMD; i++){
        if(client[i] == nullptr){
            this->client[i] = clie;
            break;
        }
    }

    return 0;
}

int Menu::opcao2(){        /* Na op��o 2, � adicionado um novo pedido em uma comanda que ja existe. A primeira coisa �
                               perguntar em qual comanda vai ser adicionado  o pedido, onde se a comanda for invalida, �
                               informado que a op��o foi invalida. */
    int numeroComanda;
    cout << "Numero da comanda para adicionar o pedido: " << endl;
    cin >> numeroComanda;

    if(this->client[numeroComanda] != nullptr){
        int prato, quantidade;

        cout << "Digite o numero do prato desejado: " << endl;
        cin >> prato;
        cout << "Quantidade do prato: " << endl;
        cin >> quantidade;

        Pedido* pdd = new Pedido(prato, quantidade); // Se a op��o da comanda for valida, � realizado um novo pedido
                                                     // Dentro da comanda "numeroComanda".
        client[numeroComanda]->addPedido(pdd);
    } else {
        cout << "op invalida" << endl;
    }
    return 0;
}

int Menu::opcao3(){
    int numeroComanda, item;

    cout << "Numero da comanda para fechar o pedido: " << endl;
    cin >> numeroComanda;

    cout << "Numero do item que deseja fechar: " << endl;
    cin >> item;

    if(client[numeroComanda] != nullptr || client[numeroComanda] < 0){
        if(client[numeroComanda]->getPedidos(item) != nullptr || client[numeroComanda]->getPedidos(item) < 0){                           /* Na op��o 3, � perguntado novamente
                                                                                          qual a comanda desejada e o item(pedido)
                                                                                          para ser retirado, onde se as op��es forem validas o
                                                                                          metodo fecharUmItem vai ser chamado */
            client[numeroComanda]->fecharUmItem(cmd[numeroComanda]->getPedidos(item));
        } else {
            cout << "Pedido invalido" << endl;
        }
    } else {
        cout << "Comanda invalida" << endl;
    }

    return 0;
}
int Menu::opcao4(){
    int numeroComanda;

    cout << "Numero da comanda para fechar: " << endl;
    cin >> numeroComanda;

    if(numeroComanda >= 0 && numeroComanda <= MAX_CMD){ // Na op��o 4, a comanda volta a receber "nullptr" ja que ela foi fechada.
        client[numeroComanda] = nullptr;
    }

    client[numeroComanda]->setOrdem(0);

    return 0;
}
int Menu::opcao5(int tPedidos){
    int prato, quantidade, i;
    string endereco, contato;

    cout << "Digite o numero do prato desejado: " << endl;
    cin >> prato;
    if(prato <= 0 || prato > 10){
        setErro(prato);
        return 0;
    }
    cout << "Quantidade do prato: " << endl;
    cin >> quantidade;
    if(quantidade <= 0){
        setErro(quantidade);
        return 0;
    }
    getchar();
    cout << "Endereco do pedido: " << endl;
    getline(cin, endereco);
    cout << "Contato do cliente: " << endl;
    cin >> contato;

    /* Na op��o 5, apenas � requisitado os atributos necessarios para chamar o delivery. */

    Pedido* pdd[10] = new Pedido(prato, quantidade);
    for(i = 0; i < 10; i++){
        cout << "Digite 0 para finalizar" << endl;

        pdd[i]->setPrato(prato);
        pdd[i]->setQuantidade(quantidade);

        cout << "Digite o numero do prato desejado: " << endl;
        cin >> prato;
        if(prato <= 0 || prato > 10){
            setErro(prato);
            break;
        }
        cout << "Quantidade do prato: " << endl;
        cin >> quantidade;
        if(quantidade <= 0){
            setErro(quantidade);
            break;
        }
        Delivery* deli = new Delivery(pdd[i], endereco, contato);
    }


    return 0;
}

void Menu::setErro(int e){
    erro = e;
}

int Menu::getErro(){
    return erro;
}

/*void Menu::exibePedidos(){
    int primeiro = 10000, imprimiu = 1;

    for (size_t i = 0; i < MAX_MESA; i++)     // Define a mesa com menor ordem e maior prioridade
    {
        if (comanda[i].ordem != 0 && primeiro > comanda[i].ordem)  // primeira itera��o para permitir compara��es
        {
            primeiro = comanda[i].ordem;
        }
    }

    cout << "\n-----------------------------------------------------\n";

    while (imprimiu)    //confere se a impres�o de todas as comandas est� completa
    {
        imprimiu = 0;
        for (size_t i = 0; i < MAX_MESA ; i++)  //procura as mesas na ordem correta e imprime-as
        {
            if (comanda[i].ordem == primeiro)
            {
                primeiro++;
                imprimiu = 1;

                cout << "\nPedido N.: " << comanda[i].ordem << " ----- Mesa: " << i+1 << endl;  // cabe�alho

                for (size_t j = 0; j < MAX_PRATOS; j++)     //imprime pedidos da mesa
                {
                    if (comanda[i].quantidade[j] > 0)
                    {
                        cout << "        -> " << comanda[i].quantidade[j] << " " << comanda[i].pedido[j] << endl;
                    }
                }
            }
        }
    }
    cout << "\n-----------------------------------------------------\n";
} */
