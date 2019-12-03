typedef struct arvore Arvore;

Arvore * criar();
void destruir(Arvore * arv);
void inserir(Arvore * arv, int valor);
void remover(Arvore * arv, int valor);
int getCountNo(Arvore * arv);
int getMemory(Arvore * arv);
void save(Arvore * arv);

void imprimir(Arvore * arv);