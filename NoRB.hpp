
#ifndef NO_RB_HPP
#define NO_RB_HPP

#include <vector>
#include <iostream>

#define RB_RUBRO true
#define RB_NEGRO false

template <typename T>
class NoRB {
 private:
    T* dado_;            //!< Atributo onde é guardado o valor representado pelo nó
    NoRB<T>* esquerda_;  //!< Atributo que aponta para menor nó descendente
    NoRB<T>* direita_;   //!< Atributo que aponta para maior nó descendente
    NoRB<T>* pai_;       //!< Atributo que aponta para nó ascendente
    bool cor_;           //!< Atributo que indica a cor do nó

    std::vector<NoRB<T>*> elementos_;

    // Retorna o avô do nó argumento.
    NoRB<T>* Avo(NoRB<T>* n) {
        if (n != nullptr && n->pai_ != nullptr) {
            std::cout << "Avo (" << *n->pai_->pai_->getDado() << ") obtido." << std::endl;
            return n->pai_->pai_;
        } else {
            std::cout << "Avo inexistente." << std::endl;
            return nullptr;
        }
    }

    // Retorna o tio do nó argumento.
    NoRB<T>* Tio(NoRB<T>* n) {
        NoRB<T>* avo = Avo(n);

        // Sem avô, sem tio.
        if (avo == nullptr) return nullptr;

        if (n->pai_ == avo->esquerda_) {
            std::cout << "Tio eh filho da direita" << std::endl;
            return avo->direita_;
        } else {
            std::cout << "Tio eh filho da esquerda." << std::endl;
            return avo->esquerda_;
        }
    }

 public:
    explicit NoRB(const T& dado)
        : dado_(new T(dado)), esquerda_(nullptr), direita_(nullptr),
          pai_(nullptr), cor_(true) {
    }

    virtual ~NoRB() {
        if (esquerda_) {
            esquerda_->~NoRB();
        }
        if (direita_) {
            direita_->~NoRB();
        }
    }

    // Retorna um ponteiro para o dado do nó.
    T* getDado() {
        return dado_;
    }

    // Retorna um ponteiro para o nó ascendente.
    NoRB<T>* getPai() {
        return pai_;
    }

    // Retorna a "cor" do nó. Black = true.
    bool getCor() {
        return cor_;
    }

    // Retorna o vetor de elementos.
    // Usado para imprimir os percursos.
    std::vector<NoRB<T>*> getElementos() {
        return elementos_;
    }

    // Retorna um ponteiro para o nó-filho da esquerda.
    NoRB<T>* getEsquerda() {
        return esquerda_;
    }

    // Retorna um ponteiro para o nó-filho da direita.
    NoRB<T>* getDireita() {
        return direita_;
    }

    // Busca um dado na árvore recursivamente. Caso seja encontrado,
    // retorna um ponteiro para este dado.
    T* busca(const T& dado, NoRB<T>* arv) {
        if (arv == nullptr) {
            throw 10;
        } else {
            if (dado == *(arv->dado_)) {
                return arv->dado_;
            } else if (dado < *(arv->dado_)) {
                return busca(dado, arv->esquerda_);
            } else {
                return busca(dado, arv->direita_);
            }
        }
    }

    // Faz uma rotação à direita usando o nó fornecido como pivô
    NoRB<T>* rotacaoSimplesDireita(NoRB<T>* n) {
        NoRB<T> *pai, *raiz;

        std::cout << "---- Rotacao simples a direita" << std::endl;

        pai = n->pai_;
        raiz = n->esquerda_;
        raiz->pai_ = pai;

        // Atualiza o nó rotacionado
        n->esquerda_ = raiz->direita_;
        if (n->esquerda_) {
            n->esquerda_->pai_ = n;
        }

        // Atualiza a nova raiz
        raiz->direita_ = n;
        raiz->direita_->pai_ = raiz;

        // Atualiza o pai da nova raiz
        // Se o pai não existir, então raiz é a nova Raiz da árvore
        if (pai) {
            if (n == pai->esquerda_) {
                pai->esquerda_ = raiz;
            } else {
                pai->direita_ = raiz;
            }
        }
        return raiz;
    }

    // Faz uma rotação à esquerda usando o nó fornecido como pivô
    NoRB<T>* rotacaoSimplesEsquerda(NoRB<T>* n) {
        NoRB<T> *pai, *raiz;

        std::cout << "---- Rotacao simples a esquerda" << std::endl;

        pai = n->pai_;
        raiz = n->direita_;
        raiz->pai_ = pai;

        // Atualiza o nó rotacionado
        n->direita_ = raiz->esquerda_;
        if (n->direita_) {
            n->direita_->pai_ = n;    
        }
        
        // Atualiza a nova raiz
        raiz->esquerda_ = n;
        raiz->esquerda_->pai_ = raiz;

        // Atualiza o link do pai da nova raiz, caso ela não seja
        // a raiz da árvore.
        if (pai) {
            if (n == pai->esquerda_) {
                pai->esquerda_ = raiz;
            } else {
                pai->direita_ = raiz;
            }
        }
        

        return raiz;
    }

    NoRB<T>* correcaoEsquerdaInsercao(NoRB<T>* arv, NoRB<T>* pai, NoRB<T>* avo);

    NoRB<T>* correcaoDireitaInsercao(NoRB<T>* arv, NoRB<T>* pai, NoRB<T>* avo);

    NoRB<T>* correcaoEsquerdaRemocao(NoRB<T>* n);

    NoRB<T>* correcaoDireitaRemocao(NoRB<T>* n);

    // Insere um novo elemento na árvore
    NoRB<T>* inserir(const T& dado, NoRB<T>* arv) {
        
        // Cria um novo nó
        NoRB<T>* novo = new NoRB(dado);

        // Insere o nó como na árvore BST
        arv->inserirBST(novo);


        std::cout << "\n\nNovo dado (" << *novo->getDado() << ") inserido..." << std::endl;
        std::cout << "----------------------------------------------" << std::endl;
        inserirCaso1(novo);  // Verifica cada caso
        std::cout << "Retornou ao inserir principal" << std::endl;
        
        // Verifica se arv ainda é a raiz
        while (arv->pai_ != nullptr) {
            arv = arv->pai_;
        }
        return arv;
    }

    // Insere o novo nó na árvore como se fosse uma BST
    void inserirBST(NoRB<T>* n) {
        if (*n->dado_ >= *dado_) {
            if (direita_) {
                direita_->inserirBST(n);
            } else {
                direita_ = n;
                n->pai_ = this;
                n->cor_ = false;
            }
        } else {
            if (esquerda_) {
                esquerda_->inserirBST(n);
            } else {
                esquerda_ = n;
                n->pai_ = this;
                n->cor_ = false;
            }
        }
    }


    // Caso 1: o pai do nó inserido é BLACK
    // ------------------------------------
    void inserirCaso1(NoRB<T>* n) {

        std::cout << "---- Caso 1" << std::endl;

        if (n->pai_->cor_ == false) {
            std::cout << "O pai (" << *n->pai_->getDado() << ") eh vermelho." << std::endl;
            inserirCaso2(n);
        } else {
            std::cout << "O pai (" << *n->pai_->getDado() << ") eh preto." << std::endl;
        }
        std::cout << "Terminou caso 1" << std::endl;
    }

    // Caso 2: o pai e o tio são RED
    // -----------------------------
    void inserirCaso2(NoRB<T>* n) {

        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "---- Caso 2" << std::endl;

        NoRB<T> *avo;
        NoRB<T> *tio = Tio(n);

        // O tio existe e é RED
        if (tio != nullptr && tio->cor_ == false) {
            std::cout << "O tio (" << *tio->getDado() << ") eh vermelho." << std::endl;
            n->pai_->cor_ = true;  // Pai -> BLACK
            tio->cor_ = true;      // Tio -> BLACK
            avo = Avo(n);          // Pai é RED, então avô existe
            avo->cor_ = false;     // Avô -> RED
            inserirCasoRaiz(avo);  // Prop. 2 & 4 podem ter sido violadas
        } else {
            std::cout << "O tio eh preto ou folha." << std::endl;
            inserirCaso3(n);       // Tio é BLACK ou folha
        }
        std::cout << "Terminou caso 2" << std::endl;
    }

    // Caso 3: pai é RED, tio é BLACK.
    // -------------------------------
    // O nó é filho da direita dum pai que é filho da esquerda e vice-versa.
    void inserirCaso3(NoRB<T>* n) {

        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "---- Caso 3" << std::endl;

        NoRB<T> *avo = Avo(n);
        NoRB<T> *tmp = n;

        if (n == n->pai_->direita_ && n->pai_ == avo->esquerda_) {
            std::cout << "No eh filho da direita dum pai da esquerda" << std::endl;
            n = rotacaoSimplesEsquerda(n->pai_);
            tmp = n->esquerda_;
        } else if (n == n->pai_->esquerda_ && n->pai_ == avo->direita_) {
            std::cout << "No eh filho da esquerda dum pai da direita" << std::endl;
            n = rotacaoSimplesDireita(n->pai_);
            tmp = n->direita_;
        }
        inserirCaso4(tmp);
        std::cout << "Terminou caso 3" << std::endl;
    }

    // Caso 4: pai é RED, tio é BLACK.
    // -------------------------------
    // O nó e seu pai são filhos da esquerda ou da direita.
    void inserirCaso4(NoRB<T>* n) {

        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "---- Caso 4" << std::endl;

        NoRB<T> *avo = Avo(n);
        n->pai_->cor_ = true;   // Pai -> BLACK
        avo->cor_ = false;      // Avô -> RED
        if (n == n->pai_->esquerda_) {
            rotacaoSimplesDireita(avo);
        } else {
            rotacaoSimplesEsquerda(avo);
        }
        std::cout << "Terminou caso 4" << std::endl;
    }

    // Caso raiz: o nó é a raiz da árvore
    // -----------------------------------
    void inserirCasoRaiz(NoRB<T>* n) {        

        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "---- Caso raiz" << std::endl;

        if (n->pai_ == nullptr) {            
            n->cor_ = true;  // Raiz -> BLACK
        } else {
            inserirCaso1(n);
        }
        std::cout << "Terminou caso raiz" << std::endl;
    }

    NoRB<T>* remover(NoRB<T>* n, const T& dado) {
        // Dado não encontrado
        if (n == nullptr) {
            return n;
        }

        // Dado encontrado
        if (dado == *(n->dado_)) {

            // Possui no máximo um filho
            if (!(n->esquerda_ && n->direita_)) {

                // Se não possuir o filho da esquerda, então possui no
                // máximo o filho da direita e vice-versa.
                NoRB<T>* filho = (n->esquerda_ ? n->esquerda_ : n->direita_);

                // Se o nó a ser deletado for RED, nada precisa ser feito.
                // Se for BLACK e o filho RED, o filho vira BLACK.
                // Se for BLACK e o filho LEAF, marca como DOUBLE BLACK.
                if (n->cor_) {
                    if (filho && !filho->cor_) {
                        filho->cor_ = true;
                    } else {
                        removerCaso1(filho);
                    }
                }
                delete n;
                return filho;
            } else {
                // Possui 2 filhos
                n->dado_ = minimo(n->direita_)->dado_;  // M. A. Weiss
                n->direita_ = remover(n->direita_, *(n->dado_));
            }
        } else {
            if (dado < *(n->dado_)) {
                n->esquerda_ = remover(n->esquerda_, dado);
            } else {
                n->direita_ = remover(n->direita_, dado);
            }
        }
    }


    // Caso 1: N é a nova raiz da árvore
    // ---------------------------------
    void removerCaso1(NoRB<T>* n) {
        if (n->pai_ != nullptr) {
            removerCaso2(n);
        }
    }

    // Caso 2: o irmão de N é RED
    // --------------------------
    void removerCaso2(NoRB<T>* n) {
        //if (
    }

    // Encontra e retorna o dado com o menor valor a partir
    // do nó fornecido.
    NoRB<T>* minimo(NoRB<T>* n) {
        if (n->esquerda_) {
            return minimo(n->esquerda_);
        } else {
            // Não possui filho à esquerda
            return n;
        }
    }

    // Ordena os nós no vetor de elementos segundo R-E-D
    void preOrdem(NoRB<T>* n) {
        // Insere primeiro a raiz
        elementos_.push_back(n);
        // ...depois o nó da esquerda
        if (n->esquerda_) {
            preOrdem(n->esquerda_);
        }
        // ... e por último o da direita
        if (n->direita_) {
            preOrdem(n->direita_);
        }
    }

    // Ordena os nós no vetor de elementos segundo E-R-D
    void emOrdem(NoRB<T>* n) {
        // Insere primeiro o nó da esquerda
        if (n->esquerda_) {
            emOrdem(n->esquerda_);
        }
        // ... depois a raiz
        elementos_.push_back(n);
        // ... e por último o da direita
        if (n->direita_) {
            emOrdem(n->direita_);
        }
    }

    // Ordena os nós no vetor de elementos segundo E-D-R
    void posOrdem(NoRB<T>* n) {
        // Insere primeiro o nó da esquerda
        if (n->esquerda_) {
            posOrdem(n->esquerda_);
        }
        // ... depois o da direita
        if (n->direita_) {
            posOrdem(n->direita_);
        }
        // ... e por último a raiz
        elementos_.push_back(n);
    }
};

#endif /* NO_RB_HPP */
