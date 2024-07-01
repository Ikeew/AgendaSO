#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAX_NOME 50
#define TAMANHO_MAX_TELEFONE 20

typedef struct {
    char nome[TAMANHO_MAX_NOME];
    char telefone[TAMANHO_MAX_TELEFONE];
} Contato;

/*------------------------------*/

/* VERIFICA SE O CONTATO EXISTE */

int contatoExiste(const Contato *contatos, int size, const char *nome) {
    for (int i = 0; i < size; i++) {
        if (strcmp(contatos[i].nome, nome) == 0) {
            return 1;
        }
    }
    return 0;
}

/*--------------------*/

/* ADICIONA O CONTATO */

void adicionarContato(Contato *contatos, int *size) {
    char nome[TAMANHO_MAX_NOME];
    char telefone[TAMANHO_MAX_TELEFONE];
    printf("Digite o nome do contato: ");
    scanf(" %[^\n]", nome);
    limparBuffer();
    if (contatoExiste(contatos, *size, nome)) {              /* Verifica se o contato existe */
        printf("Contato ja existe, digite 2 para pesquisa.\n");
        return;
    }
    printf("Digite o telefone do contato: ");
    scanf(" %[^\n]", telefone);
    limparBuffer();
    strcpy(contatos[*size].nome, nome);
    strcpy(contatos[*size].telefone, telefone);
    (*size)++;
}

/*--------------------*/

/* PESQUISA O CONTATO */

void pesquisarContato(const Contato *contatos, int size) {
    char nomePesquisa[TAMANHO_MAX_NOME];
    printf("Digite o nome do contato a procurar: ");
    scanf(" %[^\n]", nomePesquisa);
    limparBuffer();
    for (int i = 0; i < size; i++) {
        if (strcmp(contatos[i].nome, nomePesquisa) == 0) {
            printf("Nome: %s, Telefone: %s\n", contatos[i].nome, contatos[i].telefone);
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

/*------------------*/

/* EXCLUI O CONTATO */
void excluirContato(Contato *contatos, int *size) {
    char nomeExcluir[TAMANHO_MAX_NOME];
    printf("Digite o nome do contato a excluir: ");
    scanf(" %[^\n]", nomeExcluir);
    limparBuffer();
    for (int i = 0; i < *size; i++) {
        if (strcmp(contatos[i].nome, nomeExcluir) == 0) {
            contatos[i] = contatos[*size - 1];
            (*size)--;
            printf("Contato excluído.\n");
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

/*-----------------*/


/* SALVA O CONTATO */

void salvarContatos(const Contato *contatos, int size) {
    FILE *file = fopen("/root/AgendaSO/contatos.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir file.\n");
        return;
    }
    fwrite(&size, sizeof(int), 1, file);
    fwrite(contatos, sizeof(Contato), size, file);
    fclose(file);
}


/*-------------------*/


/* CARREGA O CONTATO */

void carregarContatos(Contato *contatos, int *size) {
    FILE *file = fopen("/root/AgendaSO/contatos.dat", "rb");
    if (file == NULL) {
        *size = 0;
        return;
    }
    fread(size, sizeof(int), 1, file);
    fread(contatos, sizeof(Contato), *size, file);
    fclose(file);
}

/*----------------*/


/* LIMPA O BUFFER */

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/*------------------*/



int main() {
    Contato contatos[50];
    int size = 0;
    int opcao;

    carregarContatos(contatos, &size);

    do {
        printf("\n1. Adicionar Contato\n");
        printf("2. Pesquisar Contato\n");
        printf("3. Excluir Contato\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                adicionarContato(contatos, &size);
                break;
            case 2:
                pesquisarContato(contatos, size);
                break;
            case 3:
                excluirContato(contatos, &size);
                break;
            case 4:
                salvarContatos(contatos, size);
                printf("Dados salvos.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 4);

    return 0;
}
