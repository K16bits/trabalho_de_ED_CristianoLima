#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    char letra;
    int linha_letra;  // LINHA DO TEXTO 
    int quant;  // Quantidade de repetições
    struct nodo *prox;
}Nodo;

typedef struct List{
    Nodo *head;
    int tam;
}list;

int esta_vazio(list *l){
    return (l->tam == 0);
}

list *criar(){
    list *l = (list*)malloc(sizeof(list));
    l->tam = 0;
    l->head = NULL;
}

char adicionar(list *l, char key,int linha){
    Nodo *new = (Nodo*)malloc(sizeof(Nodo));
    new->letra = key;  //adicionar letras
    new->prox = l->head; //apontar para um novo nodo
    new->linha_letra = linha;
    new->quant = 1;
    l->head = new; // inico
    l->tam++;
}

void imprimir(list *l){
    printf("------- Nodo de letras -------\n");
    for(Nodo *p = l->head; p!= NULL; p = p->prox){
        printf("Letra: %c\n(%d,%d)",p->letra,p->linha_letra,p->quant);//+1 no print para ficar legivel aos olhos
        printf("\n");
       }
    printf("\n");
}

int procurar(list *l, char x,int pos ){
    for(Nodo *aux = l->head; aux != NULL; aux = aux->prox){
        if(aux->letra == x){
            aux->quant +=1;
            return 0;
            }
    }
    return 1;
}

void clear(list *l){
    Nodo *ant, *p;
    p = l->head;
    while(p != NULL){
        ant = p;
        p = p->prox;
        free(ant);
    }
    free(l);
}

void comp(list *l){  // não repetir 2x
    imprimir(l);
    clear(l);
}

int main(){
    FILE *arquivo;
    arquivo = fopen("texto.txt","r");
    char letras;
    char palavra[50] = {};
    int i = 0,linha = 0;

    list *l = criar(); // Lista iniciada

    while(letras != EOF){
        letras = getc(arquivo);
        if(letras == EOF)
            break;
        if(letras == ' '){
            continue;
            }
        if(letras == '\n'){
            linha+=1;
            comp(l);
            list *l = criar(); // Lista iniciada 2X
            continue;
            }

        palavra[i] = letras;
        if(!(procurar(l,letras,linha))){  //bolean no dic, se existe !?
            continue;
        }else
            adicionar(l,letras,linha);
        i++;
}
    fclose(arquivo); // Fechar o arquivo
    clear(l);
}