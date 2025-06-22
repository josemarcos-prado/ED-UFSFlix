/*
Bruno Carvalho Santana Rocha
Danilo Campos Deichmann
Filipe Ciríaco Marcelino do Nascimento 
José Marcos Bittencourt Oliveira Prado
Sophia Damm Zogaib Mardones
*/

#include "funcoes.h"

int main(){
    int op;
    tipoLista lista;
    inicializa(&lista);
    do{
        printf("\n      Menu UFSflix");
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
        case 6: exibirFilmesPorGenero(&lista);
            break;
        case 0: 
            freeMultilista(&lista);
            break;
        default:
            printf("Comando não reconhecido");
        }
     printf("\n\n\n\n");
    }while(op != 0);
    return 0;
}