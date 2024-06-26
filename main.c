#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_PHONE_LEN 20

typedef struct {
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
} Contact;
void addContact(Contact *contacts, int *size) {
    if (*size >= 100) {
        printf("Agenda cheia.\n");
        return;
    }
    printf("Digite o nome do contato: ");
    scanf(" %[^\n]", contacts[*size].name);
    printf("Digite o telefone do contato: ");
    scanf(" %[^\n]", contacts[*size].phone);
    (*size)++;
}

void searchContact(const Contact *contacts, int size) {
    char searchName[MAX_NAME_LEN];
    printf("Digite o nome do contato a procurar: ");
    scanf(" %[^\n]", searchName);
    for (int i = 0; i < size; i++) {
        if (strcmp(contacts[i].name, searchName) == 0) {
            printf("Nome: %s, Telefone: %s\n", contacts[i].name, contacts[i].phone);
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

void deleteContact(Contact *contacts, int *size) {
    char deleteName[MAX_NAME_LEN];
    printf("Digite o nome do contato a excluir: ");
    scanf(" %[^\n]", deleteName);
    for (int i = 0; i < *size; i++) {
        if (strcmp(contacts[i].name, deleteName) == 0) {
            contacts[i] = contacts[*size - 1];
            (*size)--;
            printf("Contato excluído.\n");
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

void saveContacts(const Contact *contacts, int size) {
    FILE *file = fopen("C:/Users/ikikl/OneDrive/Documents/GitHub/AgendaSO/contatos.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    fwrite(&size, sizeof(int), 1, file);
    fwrite(contacts, sizeof(Contact), size, file);
    fclose(file);
}

void loadContacts(Contact *contacts, int *size) {
    FILE *file = fopen("C:/Users/ikikl/OneDrive/Documents/GitHub/AgendaSO/contatos.dat", "rb");
    if (file == NULL) {
        *size = 0;
        return;
    }
    fread(size, sizeof(int), 1, file);
    fread(contacts, sizeof(Contact), *size, file);
    fclose(file);
}

int main() {
    Contact contacts[100];
    int size = 0;
    int option;

    loadContacts(contacts, &size);

    do {
        printf("\n1. Adicionar Contato\n");
        printf("2. Pesquisar Contato\n");
        printf("3. Excluir Contato\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addContact(contacts, &size);
            break;
            case 2:
                searchContact(contacts, size);
            break;
            case 3:
                deleteContact(contacts, &size);
            break;
            case 4:
                saveContacts(contacts, size);
            printf("Dados salvos. Saindo...\n");
            break;
            default:
                printf("Opção inválida.\n");
        }
    } while (option != 4);

    return 0;
}

/* asjkdhqugxdahjsxgfhjsd */

/* comentarios do henrique */


