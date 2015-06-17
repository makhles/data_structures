#include <iostream>
#include <assert.h>
#include "NoRB.hpp"

#define NELEM 10

int main(int argc, char* argv[]) {

    NoRB<int>* arv = new NoRB<int>(5);

    std::cout << "Starting..." << std::endl;

    int i;
    for (i = 0; i < NELEM; i++) {
        arv = arv->inserir(i, arv);
        //std::cout << "NOVO DADO INSERIDO: " << *arv->getDado() << std::endl;
    }

    arv->emOrdem(arv);
    std::vector<NoRB<int>* > elementos = arv->getElementos();
    
    std::cout << "Elementos:" << std::endl;
    for (i = 0; i < NELEM+1; i++) {
        std::cout << *(elementos[i]->getDado()) << " ";
    }
    std::cout << std::endl;

    delete arv;
    return 0;
}