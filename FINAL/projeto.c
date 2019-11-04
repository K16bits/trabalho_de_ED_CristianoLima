#include <stdio.h>
#include <stdlib.h>

typedef struct bloco{
    int linhas;
    int quant;
    struct bloco *proximo;
}Bloco; //LISTA DAS LETRAS

typedef struct nodo{
    char letra;
    struct bloco *inicio; // Ligação das letras
    struct nodo *prox; //ligação dos nodos de letras
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

char adicionar(list *l, char key){
    Nodo *new = (Nodo*)malloc(sizeof(Nodo));
    new->letra = key;  //adicionar letras
    new->prox = l->head; //apontar para um novo nodo
    l->head = new; // inico
    l->tam++;
}

int adicionar2(Nodo *p,list *l,int linhas, int rep){ //Adicionando os nodos a letra
    Bloco *new = malloc(sizeof(Bloco));
    new->linhas = linhas;
    new->quant = rep;
    new->proximo = p->inicio;
    p->inicio = new;
    //printf("NEW Letra: %c linha: %d | rep: %d\n",p->letra,new->linhas,new->quant);
}

void imprimir(list *l){ //print das letras sem repetir 
    printf("------- Nodo de letras -------\n");
    for(Nodo *p = l->head; p!= NULL; p = p->prox){
        printf("Letra: %c\n",p->letra);
       }
    printf("--------------\n");
}

int procurar(list *l, char x){ // procura se a letra já existe no nodo
    for(Nodo *aux = l->head; aux != NULL; aux = aux->prox){
        if(aux->letra == x){
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
        for(Bloco *aux = ant->inicio ; aux != NULL; aux = aux->proximo){ //limpar os nodos das letras
                free(aux);
            }
        p = p->prox;
        free(ant);
    }
    free(l);
}

void run(Nodo *p,list *l){  //ler todo o arquivo passando as referencias
    FILE *arquivo;
    arquivo = fopen("texto.txt","r");
    int rep = 0;
    int linha = 0;
    char letras2;
    
    while(letras2 != EOF){
        letras2 = getc(arquivo);
        if(letras2 == p->letra){
            rep+=1;
        }else if(letras2 == ' '){
            continue;
        }else if(letras2 == '\n'||letras2 == EOF){
            if(rep == 0){
                linha++;
            }else{
                //COMPLETANDO O BLOCO
                adicionar2(p,l,linha,rep);
                linha++;
                rep = 0;
            }
        }
    }
}
int main(){
    FILE *arquivo;
    arquivo = fopen("texto.txt","r");
    char letras;
    char palavra[50] = {};
    int i;
    list *l = criar(); // Lista iniciada

    while(letras != EOF){ // ler o arquivo para fazer os nodos sem repetição 
        letras = getc(arquivo);
        if(letras == EOF)
            break;
        if(letras == ' '){
            continue;
        }else if(letras == '\n'){
            list *l = criar(); // Lista iniciada 2X
            continue;
            }

        palavra[i] = letras;
        if(!(procurar(l,letras))){  //bolean no Nodo, se existe !?
            continue;
        }else
            adicionar(l,letras);
        i++;
    }
    imprimir(l); // Listar as letras sem repetição
    rewind(arquivo);
    
    for(Nodo *p = l->head ; p != NULL ; p = p->prox){
        printf("---- PERCORRENDO OS NODOS ----\n");
        printf("Letra: %c\n",p->letra);
        run(p,l);
        for(Bloco *aux = p->inicio ; aux != NULL ; aux = aux->proximo){ // percorrendo os nodos das letras
            printf("(%d,%d) ",aux->linhas,aux->quant); // tá printando invertido porque está no estilo de fila
        }
        printf("---- FIM DO NODO ----\n");
        printf("\n");
    }
    fclose(arquivo); // Fechar o arquivo
    clear(l);
}