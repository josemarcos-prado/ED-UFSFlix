/*
Bruno Carvalho Santana Rocha
Danilo Campos Deichmann
Filipe Ciríaco Marcelino do Nascimento 
José Marcos Bittencourt Oliveira Prado
Sophia Damm Zogaib Mardones
*/

#include "funcoes.h"

int main(){
    limparTela();
    int op;
    tipoLista lista;
    inicializa(&lista);
    do{
        //limparTela();
        printf("\n--------------\n Menu UFSflix\n--------------");
        printf("\n0 - Finalizar");
        printf("\n1 - Cadastrar Genero");
        printf("\n2 - Mostrar lista de generos cadastrados");
        printf("\n3 - Cadastrar filme");
        printf("\n4 - Remover filme");
        printf("\n5 - Exibir filme especifico, pesquisado por nome");
        printf("\n6 - Exibir dados de todos os filmes de determinado genero");
        printf("\nDigite sua opcao: ");
        scanf("%d",&op);
        getchar();
        switch(op){
        case 1:
            cadastrarGenero(&lista);
            break;
        case 2:
            generosCadastrados(&lista);
            break;
        case 3:
            cadastrarFilme(&lista);
            break;
        case 4: removerFilme(&lista);
            break;
        case 5: pesquisaFilme(&lista);
            break;
        case 6: 
            limparTela();
            exibirFilmesPorGenero(&lista);
            pausar();
            break;
        case 0: 
            freeMultilista(&lista);
            break;
        default:
            printf("Comando nao reconhecido");
        }
        pausar();
        
    }while(op != 0);
    return 0;
}