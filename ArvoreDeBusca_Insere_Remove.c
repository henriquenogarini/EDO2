#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no* direita;
    struct no* esquerda;
} NoArv;

NoArv* buscar(NoArv* raiz, int num) {
    if (raiz) {
        if (num == raiz->valor)
            return raiz;
        else if (num < raiz->valor)
            return buscar(raiz->esquerda, num);
        else
            return buscar(raiz->direita, num);
    }
    return NULL;
}

void imprimir_versao_1(NoArv* raiz) {
    if (raiz) {
        printf("%d\n\t", raiz->valor);
        imprimir_versao_1(raiz->esquerda);
        imprimir_versao_1(raiz->direita);
    }
}

void imprimir_versao_2(NoArv* raiz) {
    if (raiz) {
        imprimir_versao_2(raiz->esquerda);
        printf("%d\n\t", raiz->valor);
        imprimir_versao_2(raiz->direita);
    }
}

void inserir(NoArv** raiz, int num) {
    NoArv* aux = *raiz;
    while (aux) {
        if (num < aux->valor)
            raiz = &aux->esquerda;
        else
            raiz = &aux->direita;
        aux = *raiz;
    }
    aux = (NoArv*)malloc(sizeof(NoArv));
    aux->valor = num;
    aux->esquerda = NULL;
    aux->direita = NULL;
    *raiz = aux;
}

NoArv* remover(NoArv* raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        if (raiz->valor == chave) {
            if (raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            } else {
                if (raiz->esquerda != NULL && raiz->direita != NULL) {
                    NoArv* aux = raiz->esquerda;
                    while (aux->direita != NULL)
                        aux = aux->direita;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                } else {
                    NoArv* aux;
                    if (raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                }
            }
        } else {
            if (chave < raiz->valor)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                raiz->direita = remover(raiz->direita, chave);
            return raiz;
        }
    }
}

int main() {
    NoArv* busca;
    NoArv* raiz = NULL;
    int opcao, valor;

    do {
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Buscar\n\t4 - Remover\n");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("\n\tDigite um valor: ");
            scanf("%d", &valor);
            inserir(&raiz, valor);
            break;
        case 2:
            printf("\n\t Primeira impressao: \n\t");
            imprimir_versao_1(raiz);
            printf("\n");
            printf("\n\t Segunda impressao(Forma ordenada): \n\t");
            imprimir_versao_2(raiz);
            printf("\n");
            break;
        case 3:
            printf("\n\tDigite um valor: ");
            scanf("%d", &valor);
            busca = buscar(raiz, valor);
            if (busca)
                printf("\n\tValor Encontrado : %d\n", busca->valor);
            else
                printf("\n\tValor nao encontrado!\n");
            break;
        case 4:
            printf("\t");
            imprimir_versao_2(raiz);
            printf("\n\tDigite o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        default:
            if (opcao != 0)
                printf("\n\tOpcao Invalida !\n");
        }
    } while (opcao != 0);
    return 0;
}
