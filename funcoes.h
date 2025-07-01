/*
Bruno Carvalho Santana Rocha
Danilo Campos Deichmann
Filipe Ciríaco Marcelino do Nascimento 
José Marcos Bittencourt Oliveira Prado
Sophia Damm Zogaib Mardones
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct filme {
    char nomeFilme[50];
    char sinopse[300];
    int duracao;
    int lancamento;
    struct filme *prox; 
} tipoFilme;

typedef struct genero{
    tipoFilme *fim;
    char nomeGenero[50];
    char descricao[150];
    int quantFilmes;
    struct genero *prox,*ant;
}tipoGenero;

typedef struct tipoLista{
    int qntd;
    tipoGenero *inicio;
    tipoGenero *fim;
}tipoLista;

void limparTela();
void pausar();
void limpaBuffer();
void limpaBufferInteligente(char* string);
void inicializa(tipoLista *lista);
void cadastrarGenero(tipoLista *lista);
void generosCadastrados(tipoLista *lista);
tipoGenero* pesquisaGenero(tipoLista *lista);
void cadastrarFilme(tipoLista *lista);
void exibirTodosFilmes(tipoLista *lista);
void exibirFilmesPorGenero(tipoLista *lista);
void removerFilme(tipoLista *lista);
void pesquisaFilme(tipoLista *lista);
void exibirFilme(tipoFilme *filme);
void freeMultilista(tipoLista *lista);

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    #ifdef _WIN32
        system("pause");
    #else
        printf("Pressione ENTER para continuar...");
        getchar();
        printf("\n");
    #endif
}

void limpaBuffer(){
    int c;
    while(((c = getchar()) != '\n') && (c != EOF));
}

void limpaBufferInteligente(char* string) {
    if (strcspn(string, "\n") < strlen(string)){
        string[strcspn(string,"\n")] = '\0';
    } 
    else {
        limpaBuffer();
    }
}

void inicializa(tipoLista *lista){
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->qntd = 0;
}

/*
Funções para gêneros 
*/
void cadastrarGenero (tipoLista *lista) {
    tipoGenero *novoGenero = (tipoGenero*) malloc(sizeof(tipoGenero));
    if (!novoGenero){ //Verifica se a memória foi alocada
        printf("Infelizmente, seu genero nao foi alocado de forma adequada. :(\n");
        return;
    }  
    printf("Digite o nome do genero: \n");
    fgets(novoGenero->nomeGenero,sizeof(novoGenero->nomeGenero),stdin);
    limpaBufferInteligente(novoGenero->nomeGenero);
    
    printf("Digite o descricao do genero: \n");
    fgets(novoGenero->descricao,sizeof(novoGenero->descricao),stdin);
    limpaBufferInteligente(novoGenero->descricao);
    
    novoGenero->quantFilmes = 0;
    novoGenero->fim = NULL;
    lista->qntd++;

    if(!lista->inicio) {
        novoGenero->prox = NULL;
        novoGenero->ant = NULL;
        lista->inicio = novoGenero;
        lista->fim = novoGenero;
        return;
    }
    novoGenero->prox = lista->inicio;
    lista->inicio->ant = novoGenero;
    novoGenero->ant = NULL;
    lista->inicio = novoGenero;

    printf("Genero inserido! \n");
}

void generosCadastrados(tipoLista *lista){
    tipoGenero* aux = lista->inicio;
    if(!aux){
        printf("Lista vazia!");
        return ;
    }
    printf("Generos disponiveis\n");
    while(aux){
        printf("%s\n", aux->nomeGenero);
        aux = aux->prox;
    }
}

tipoGenero* pesquisaGenero(tipoLista *lista){
    generosCadastrados(lista);
    char nomeG[50];

    printf("Digite um genero: \n");
    fgets(nomeG,sizeof(nomeG),stdin);
    limpaBufferInteligente(nomeG);

    tipoGenero* atual = lista->inicio;

    while(atual){
        if(strcmp(nomeG, atual->nomeGenero) == 0) return atual;
        atual = atual->prox;
    }
    return NULL;
}

/*
Funções para filmes
*/
void cadastrarFilme(tipoLista *lista){
    tipoGenero* genero = pesquisaGenero(lista);

    if(!genero){
        printf("Genero nao encontrado!\n");
        return;
    }
    
    tipoFilme *novoFilme = (tipoFilme*) malloc(sizeof(tipoFilme));
    if (!novoFilme){ //Verifica se a memória foi alocada
        printf("Infelizmente, seu filme nao foi alocado de forma adequada. :(\n");
    }  

    printf("Digite o nome do filme: \n");
    fgets(novoFilme->nomeFilme,sizeof(novoFilme->nomeFilme),stdin);
    limpaBufferInteligente(novoFilme->nomeFilme);

    printf("Digite a descricao do filme: \n");
    fgets(novoFilme->sinopse,sizeof(novoFilme->sinopse),stdin);
    limpaBufferInteligente(novoFilme->sinopse);

    printf("Digite a duracao do filme em minutos: \n");
    scanf("%d", &novoFilme->duracao);
    getchar();

    printf("Digite o ano de lancamento do filme: \n");
    scanf("%d", &novoFilme->lancamento);
    getchar();

    genero->quantFilmes++;
    if(!genero->fim){
        genero->fim = novoFilme;
        novoFilme->prox = novoFilme;
        return;
    } 
    tipoFilme* aux = genero->fim;                                                                
    novoFilme->prox = aux->prox;
    aux->prox = novoFilme;
    genero->fim = novoFilme;
}

void exibirTodosFilmes(tipoLista *lista){
    tipoGenero *atualG = lista->inicio;
    tipoFilme *atualF;
    int cont = 1;
    for(int i = 0; i<lista->qntd; i++){
        if(!atualG->fim) continue;
        atualF = atualG->fim;
        for(int j = 0; j<atualG->quantFilmes; j++){
            printf("%d - %s \n", cont++, atualF->nomeFilme);
            atualF = atualF->prox;
        }
        atualG = atualG->prox;
    }

    if(cont == 1) printf("Lista Vazia \n");
}

void exibirFilmesPorGenero(tipoLista *lista){
    tipoGenero* trg = pesquisaGenero(lista);

    if(!trg){
        printf("Genero nao encontrado \n");
        return;
    }

    if(trg->fim == NULL){
        printf("Nenhum filme cadastrado neste genero. \n");
        return;
    }
    
    tipoFilme* atual = trg->fim;
    
    printf("\nFilmes cadastrados do Genero %s: \n", trg->nomeGenero);
    do{
        atual = atual->prox;
        exibirFilme(atual);
    }while(atual != trg->fim);
    printf("\n");
}

void removerFilme(tipoLista *lista){
    printf("Filmes no Catalogo: \n");
    exibirTodosFilmes(lista);
    
    char nomeBusca[50];
    printf("Digite o nome do filme: ");
    fgets(nomeBusca,sizeof(nomeBusca),stdin);
    limpaBufferInteligente(nomeBusca);

    tipoGenero *atualG = lista->inicio;
    tipoFilme *atualF;
    int achou = 0;

    for(int i = 0; i<lista->qntd; i++){
        if(!atualG->fim) continue;
        atualF = atualG->fim;
        for(int j = 0; j<atualG->quantFilmes; j++){
            if(strcmp(atualF->prox->nomeFilme, nomeBusca) == 0 ){
                achou = 1;
                break;
            }
            atualF = atualF->prox;
        }
        if(achou) {
            printf("Filme removido\n");            
            break;
        }
        atualG = atualG->prox;
    }

    if(!achou){
        printf("Filme nao encontrado\n");
        return;
    }

    tipoFilme *trg = atualF->prox;          
    tipoFilme *next = trg->prox;
    atualF->prox = next;
    
    if(trg == next){
        atualG->fim = NULL;
    }else if(trg == atualG->fim) {
        atualG->fim = atualF;
    }
    atualG->quantFilmes--;
    free(trg);
}

void pesquisaFilme(tipoLista *lista){
    char nomeBusca[50];
    if(!lista){
        printf("Lista Vazia, filme nao encontrado");
        return;
    }
    printf("Digite o nome do filme (exatamente igual): ");
    fgets(nomeBusca,sizeof(nomeBusca),stdin);
    limpaBufferInteligente(nomeBusca);
    
    tipoGenero* atualGenero = lista -> inicio;
    int achou = 0;
    for (int i = 0; i < lista->qntd; i++) { 
        tipoFilme* atualFilme = atualGenero->fim;        
        for (int j = 0; j < atualGenero->quantFilmes; j++) {
            if (strcmp(atualFilme->nomeFilme, nomeBusca) == 0){
                exibirFilme(atualFilme);
                achou = 1;
                break;
            }
            atualFilme = atualFilme->prox;
        }
        atualGenero = atualGenero->prox;
    }
    if(!achou) {
        printf("Nao achou o filme %s", nomeBusca);
    }
}

void exibirFilme(tipoFilme* filme){
    printf("====================\nNome: %s\nSinopse: %s\nDuracao: %d minutos\nAno de lancamento: %d\n====================\n", filme->nomeFilme, filme->sinopse, filme->duracao, filme->lancamento);
}

void freeMultilista(tipoLista *lista){
    tipoGenero* atualGenero = lista -> inicio;
    for (int i = 0; i < lista->qntd; i++) { 
        tipoFilme* atualFilme = atualGenero->fim;        
        for (int j = 0; j < atualGenero->quantFilmes; j++) {
            tipoFilme* auxFilme = atualFilme;
            atualFilme = atualFilme->prox;
            free(auxFilme);
        }
        tipoGenero* auxGenero = atualGenero;
        atualGenero = atualGenero->prox;
        free(auxGenero);
    }
}