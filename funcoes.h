/*
Bruno Carvalho Santana Rocha
Danilo Campos Deichmann
Filipe Ciríaco Marcelino do Nascimento 
Jose Marcos Bittencourt Oliveira Prado
Sophia Damm Zogaib Mardones
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Tipo que define um no de lista circular (lista de filmes)
typedef struct filme {
    char nomeFilme[50];
    char sinopse[300];
    int duracao;
    int lancamento;
    struct filme *prox; 
} tipoFilme;

//Tipo que define um no de lista duplamente encadeada (lista de generos) e no cabeça de lista circular (lista de filmes)
typedef struct genero{
    tipoFilme *fim;
    char nomeGenero[50];
    char descricao[150];
    int quantFilmes;
    struct genero *prox,*ant;
}tipoGenero;

//Tipo que define um no cabeca de lista duplamente encadeada (multilista)
typedef struct tipoLista{
    int qntd;
    tipoGenero *inicio;
    tipoGenero *fim;
}tipoLista;

//Prototipos das funcoes:
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

//Funcao para limpar o terminal
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//Funcao para pausar a execucao do programa
void pausar() {
    #ifdef _WIN32
        system("pause");
    #else
        printf("Pressione ENTER para continuar...");
        getchar();
        printf("\n");
    #endif
}

//Funcao que limpa o buffer
void limpaBuffer(){
    int c;
    while(((c = getchar()) != '\n') && (c != EOF));
}

//Funcao que limpa: o buffer ou a formatacao da string que foi recebida por um fgets
void limpaBufferInteligente(char* string) {
    //Se '\n' for encontrado na string, limpa a string
    int i;
    if ((i = strcspn(string, "\n")) < strlen(string)){ 
        string[i] = '\0';
    } 
    //Se nao, ha lixo no buffer, que a funcao limpaBuffer() remove
    else { 
        limpaBuffer();
    }
}

//Funcao para inicializar cada campo do no cabeça da multilita
void inicializa(tipoLista *lista){
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->qntd = 0;
}

/* Funcoes para generos */
void cadastrarGenero (tipoLista *lista) {
    tipoGenero *novoGenero = (tipoGenero*) malloc(sizeof(tipoGenero));
    if (!novoGenero){ //Verifica se a memoria foi alocada
        printf("Infelizmente, seu genero nao foi alocado de forma adequada. :(\n");
        return;
    }

    //Recebe os dados do genero e inicializa os campos do struct com os valores devidos.  
    printf("Digite o nome do genero: \n");
    fgets(novoGenero->nomeGenero,sizeof(novoGenero->nomeGenero),stdin);
    limpaBufferInteligente(novoGenero->nomeGenero);
    
    printf("Digite o descricao do genero: \n");
    fgets(novoGenero->descricao,sizeof(novoGenero->descricao),stdin);
    limpaBufferInteligente(novoGenero->descricao);
    
    novoGenero->quantFilmes = 0;
    novoGenero->fim = NULL;
    lista->qntd++;

    //Começa as verificacoes para o cadastro do genero:
    //Caso a lista esteja vazia:
    if(!lista->inicio) {
        //Direciona os ponteiros corretamente
        novoGenero->prox = NULL; 
        novoGenero->ant = NULL; 
        //Adiciona no inicio
        lista->inicio = novoGenero;
        lista->fim = novoGenero;
        printf("Genero inserido! \n");
        return;
    }
    //Caso a lista nao esteja vazia:
    //Direciona os ponteiros corretamente
    novoGenero->prox = lista->inicio;
    lista->inicio->ant = novoGenero;
    novoGenero->ant = NULL;
    //Adiciona no inicio
    lista->inicio = novoGenero;
    printf("Genero inserido! \n");
}

void generosCadastrados(tipoLista *lista){ /* Sendo passado a lista de generos como argumento */
    tipoGenero* aux = lista->inicio; /* Aux apontando para o primeiro genero*/
    if(!aux){ /* Caso nao encontre, essa lista esta vazia */
        printf("Lista vazia!");
        return ;
    }
    printf("Generos disponiveis\n");
    while(aux){ /* Enquanto aux e diferente de nulo, printe e passe para o prox. */
        printf("%s\n", aux->nomeGenero);
        aux = aux->prox; /* associa o aux ao proximo */
    }
}

tipoGenero* pesquisaGenero(tipoLista *lista){
    generosCadastrados(lista); /* Utiliza a funcao para printar todos os generos cadastrados*/
    char nomeG[50];

    printf("Digite um genero: \n");
    fgets(nomeG,sizeof(nomeG),stdin); 
    limpaBufferInteligente(nomeG);

    tipoGenero* atual = lista->inicio; /* Cria um tipoGenero e associa para o inicio da lista */

    while(atual){ /* Roda caso o atual nao seja NULL, ou seja, enquanto a lista contem algum elemento */
        if(strcmp(nomeG, atual->nomeGenero) == 0) return atual; /* Caso o nome passado pelo usuario seja igual ao nome do genero, retorne a lista desse genero */
        atual = atual->prox; /* Associa o atual para o proximo elemento */
    }
    return NULL;
}

/* Funcoes para filmes*/
void cadastrarFilme(tipoLista *lista){
    tipoGenero* genero = pesquisaGenero(lista);

    if(!genero){
        printf("Genero nao encontrado!\n");
        return;
    }
    
    tipoFilme *novoFilme = (tipoFilme*) malloc(sizeof(tipoFilme));
    if (!novoFilme){ //Verifica se a memoria foi alocada
        printf("Infelizmente, seu filme nao foi alocado de forma adequada. :(\n");
        return;
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
    printf("Filmes no Catalogo: \n");
    tipoGenero *atualG = lista->inicio;
    tipoFilme *atualF;
    int cont = 1;
    for(int i = 0; i<lista->qntd; i++){
        atualF = atualG->fim;
        for(int j = 0; j<atualG->quantFilmes; j++){
            printf("%d - %s \n", cont++, atualF->nomeFilme);
            atualF = atualF->prox;
        }
        atualG = atualG->prox;
    }

    if(cont == 1) printf("Lista Vazia \n");
}

void exibirFilmesPorGenero(tipoLista *lista){ /* Recebe como argumento, a multilista principal */
    tipoGenero* genero = pesquisaGenero(lista); /* Devolve a lista de filmes pertecentes ao genero escolhido pelo usuario */

    if(!genero){ /* Caso o genero seja nulo, o algoritmo nao encontrou o genero passado */
        printf("Genero nao encontrado \n");
        return;
    }

    if(genero->fim == NULL){ /* Caso a lista contem um fim igual a nulo, ele somente foi iniciado e nao possui qualquer filme */
        printf("Nenhum filme cadastrado neste genero. \n");
        return;
    }
    
    tipoFilme* atual = genero->fim->prox; /* Como essa lista e circular, e criado um ponteiro do tipoFilme em que o mesmo aponta ao elemento seguinte do fim dessa lista, ou seja, o inicio da lista.*/
    
    printf("\nFilmes cadastrados do Genero %s: \n", genero->nomeGenero);
    do{
        exibirFilme(atual); /* Simples funcao que recebendo um tipoFilme, printa o nome, sinopse, duracao, tempo do filme e ano de lançamento utilizando a formatacao padrao*/
        atual = atual->prox;
    }while(atual != genero->fim->prox); /* Caso o atual nao seja o inicio da lista, continue no laço */
    printf("\n");
}

/* 
 * Funcao: removerFilme
 * Objetivo: Remove um filme do catalogo, buscando pelo nome informado.
 * Parâmetros:
 *   - lista: no cabeça para a lista de generos, cada genero contem uma lista de filmes.
 */
void removerFilme(tipoLista *lista){
    // Exibe os filmes disponíveis no catalogo
    exibirTodosFilmes(lista);

    // Le o nome do filme a ser removido
    char nomeBusca[50];
    printf("Digite o nome do filme: ");
    fgets(nomeBusca,sizeof(nomeBusca),stdin);
    limpaBufferInteligente(nomeBusca);

    // Ponteiros para percorrer os generos e filmes
    tipoGenero  *atualG = lista->inicio; 
    tipoFilme   *atualF; 
    int         achou = 0;

    // Percorre cada genero na lista
    for(int i = 0; i<lista->qntd; i++){ 

        // Começa pelo último filme cadastrado (lista circular)
        atualF = atualG->fim;

         /* Percorre todos os filmes do genero atual (atualG)
          * Note que se o genero estiver vazio, atualF = NULL,
          * porem, nesse caso atualG->quantFilmes e igual a 0 e o for nao sera executado e nao havera falha de segmentacao */
        for(int j = 0; j<atualG->quantFilmes; j++){
            //Comparamos o nome do autalF->prox com o nome que buscamos
            if(strcmp(atualF->prox->nomeFilme, nomeBusca) == 0 ){
                achou = 1;
                break; 
            }
            atualF = atualF->prox;
        }
        // Se encontrou, interrompe a busca
        if(achou) {
            printf("Filme removido com sucesso!\n");            
            break;
        }
        atualG = atualG->prox;
    }

     // Caso o filme nao tenha sido encontrado durante a busca
    if(!achou){
        printf("Filme nao encontrado\n");
        return;
    }

    // Ponteiro para o filme a ser removido (atualF->prox)
    tipoFilme *alvo = atualF->prox; 

    // Remove o alvo da lista encadeada
    atualF->prox = alvo->prox;
    
    // Ajusta o ponteiro 'fim' do genero, se necessario
    if(alvo == alvo->prox){ 
        // Era o único filme no genero
        atualG->fim = NULL;
    }else if(alvo == atualG->fim) {
        // Se removemos o último filme, atualizamos 'fim' para atualF
        atualG->fim = atualF;
    }
    
    atualG->quantFilmes--;
     // Libera a memoria do filme removido
    free(alvo);
}

void pesquisaFilme(tipoLista *lista){
    char nomeBusca[50];
    if(!lista){
        printf("Lista Vazia, filme nao encontrado");
        return;
    }
    exibirTodosFilmes(lista);
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