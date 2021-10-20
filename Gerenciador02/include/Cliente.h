#ifndef CLIENTE_H
#define CLIENTE_H
#include <string>
#include "Comanda.h"

class Cliente // Os dados dos clientes s�o necessarios para o delivery, j� que no restaurante o controle vai ser feito pela comanda.
{
    public:
        Cliente(std::string identidade);
        Cliente();
        ~Cliente();
        Comanda cmd;

        void setIdentidade(std::string id);
        std::string getIdentidade(std::string id);


    protected:
        std::string identidade;
    private:
};

#endif // CLIENTE_H
