//
// Created by roberto on 08/04/24.
//

#include "arquivo.h"


void menu (){
    contato_t* lista_contatos = criar_contato(100);
    carregar_contatos(lista_contatos);
    int indice_edit, indice_del;
    int opcao;
    char nome[100], telefone[15], email[50];
    printf("==================LISTA DE CONTATOS==================");
    while (true) {
        printf("\nMenu:\n");
        printf("1. Adicionar novo contato\n");
        printf("2. Visualizar todos os contatos\n");
        printf("3. Buscar por um contato\n");
        printf("4. Editar informações de um contato\n");
        printf("5. Excluir um contato\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do contato: ");
                getchar(); // Limpa o buffer do teclado
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remove a quebra de linha do final do nome
                printf("Digite o email do contato: ");
                scanf("%49s", email);
                printf("Digite o telefone do contato: ");
                scanf("%14s", telefone);
                if (adicionar_pessoa(lista_contatos, nome, email, telefone) == true){
                    printf("Contato adicionado\n");
                } else {
                    printf("A lista de contatos está cheia.\n");
                }
                salvar_contatos(lista_contatos);
                break;
            case 2: {
                if (lista_contatos->total == 0){
                    printf("A lista de contatos está vazia\n");
                }else{
                    imprimir_contatos(lista_contatos);
                }
            }
                break;
            case 3:
                printf("Digite o nome (ou parte do nome) do contato que deseja buscar: ");
                char seq[100];
                scanf("%s", seq);
                int resultados[5];
                int contagem = buscar_contato(lista_contatos, seq, resultados);
                if(contagem > 0){
                    printf("Resultados da busca por '%s':\n", seq);
                    for (int i = 0; i < contagem; ++i) {
                        printf("%-2d | %-24s | %-15s | %s\n", resultados[i],
                               lista_contatos->vetor[resultados[i]].nome,
                               lista_contatos->vetor[resultados[i]].email,
                               lista_contatos->vetor[resultados[i]].telefone
                        );
                    }
                } else{
                    printf("Não foi encontrada nenhuma pessoa com '%s'\n", seq);
                }
                break;
            case 4:
                getchar();
                printf("Digite o indice do contato que deseja editar: ");
                scanf("%d", &indice_edit);
                printf("Digite o novo nome do contato: ");
                scanf("%99s", nome);
                printf("Digite o novo email do contato: ");
                scanf("%49s", email);
                printf("Digite o novo telefone do contato: ");
                scanf("%14s", telefone);
                if(editar_contato(lista_contatos, indice_edit, nome, email, telefone) == 1){
                    printf("Contato editado\n");
                } else{
                    printf("Contato não encontrado\n");
                }
                salvar_contatos(lista_contatos);
                break;
            case 5:
                printf("Digite o indice do contato que deseja excluir: ");
                scanf("%d", &indice_del);
                if(excluir_contato(lista_contatos, indice_del) == 1){
                    printf("Contato excluido\n");
                } else{
                    printf("Contato não encontrado\n");
                }
                salvar_contatos(lista_contatos);
                break;
            case 6:
                printf("Saindo do programa...\n");
                free(lista_contatos->vetor);
                free(lista_contatos);
                return;
            default:
                printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
        }
    }

}
