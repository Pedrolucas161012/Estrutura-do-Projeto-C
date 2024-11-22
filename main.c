#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Estrutura de usuário
typedef struct User {
    char username[MAX_LENGTH];
    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
    struct User* next;
    struct User* prev;
} User;

User* head = NULL;

// Função para adicionar um usuário à lista duplamente encadeada
void addUser(const char* username, const char* email, const char* password) {
    User* newUser = (User*)malloc(sizeof(User));
    if (newUser == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    strcpy(newUser->username, username);
    strcpy(newUser->email, email);
    strcpy(newUser->password, password);
    newUser->next = head;
    newUser->prev = NULL;

    if (head != NULL) {
        head->prev = newUser;
    }
    head = newUser;
}

// Função para remover um usuário da lista duplamente encadeada
void removeUser(const char* email) {
    User* current = head;

    while (current != NULL) {
        if (strcmp(current->email, email) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            free(current);
            printf("Usuário removido com sucesso.\n");
            return;
        }
        current = current->next;
    }
    printf("Usuário não encontrado.\n");
}

// Função para verificar login
int login(const char* email, const char* password) {
    User* current = head;

    while (current != NULL) {
        if (strcmp(current->email, email) == 0 && strcmp(current->password, password) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Função de cadastro de usuário
void cadastro() {
    char username[MAX_LENGTH];
    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
    char confirmPassword[MAX_LENGTH];

    printf("Digite seu nome de usuário: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Digite seu e-mail: ");
    fgets(email, MAX_LENGTH, stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Digite sua senha: ");
    fgets(password, MAX_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("Confirme sua senha: ");
    fgets(confirmPassword, MAX_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (strcmp(password, confirmPassword) == 0) {
        addUser(username, email, password);
        printf("Cadastro realizado com sucesso!\n");
    } else {
        printf("Senhas não coincidem. Tente novamente.\n");
    }
}

// Funções de conversão de temperatura
float celsiusToFahrenheit(float celsius) {
    return 1.8 * celsius + 32;
}

float fahrenheitToCelsius(float fahrenheit) {
    return (fahrenheit - 32) / 1.8;
}

// Exibe a explicação sobre as escalas de temperatura
void showTemperatureExplanation() {
    printf("\nA escala Celsius (°C) e a escala Fahrenheit (°F) são amplamente utilizadas.\n");
    printf("A relação entre elas pode ser expressa pela fórmula de conversão:\n");
    printf("F = 1.8 * C + 32\n");
}

// Função de conversão de temperatura
void temperatureConversion() {
    int choice;
    float temperature, result;

    while (1) {
        printf("\nEscolha uma opção de conversão de temperatura:\n");
        printf("1. Converter Celsius para Fahrenheit\n");
        printf("2. Converter Fahrenheit para Celsius\n");
        printf("3. Voltar ao menu principal\n");
        printf("Digite sua escolha: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            printf("Digite a temperatura em Celsius: ");
            scanf("%f", &temperature);
            getchar();
            result = celsiusToFahrenheit(temperature);
            printf("Temperatura em Fahrenheit: %.2f\n", result);
            showTemperatureExplanation();
        } else if (choice == 2) {
            printf("Digite a temperatura em Fahrenheit: ");
            scanf("%f", &temperature);
            getchar();
            result = fahrenheitToCelsius(temperature);
            printf("Temperatura em Celsius: %.2f\n", result);
            showTemperatureExplanation();
        } else if (choice == 3) {
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }
}

// Função principal
int main() {
    int choice;

    while (1) {
        printf("\nEscolha uma opção:\n");
        printf("1. Login\n");
        printf("2. Cadastro\n");
        printf("3. Remover Usuário\n");
        printf("4. Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            char email[MAX_LENGTH];
            char password[MAX_LENGTH];

            printf("Digite seu e-mail: ");
            fgets(email, MAX_LENGTH, stdin);
            email[strcspn(email, "\n")] = '\0';

            printf("Digite sua senha: ");
            fgets(password, MAX_LENGTH, stdin);
            password[strcspn(password, "\n")] = '\0';

            if (login(email, password)) {
                printf("Login bem-sucedido!\n");
                temperatureConversion();
            } else {
                printf("E-mail ou senha incorretos. Tente novamente.\n");
            }
        } else if (choice == 2) {
            cadastro();
        } else if (choice == 3) {
            char email[MAX_LENGTH];
            printf("Digite o e-mail do usuário a ser removido: ");
            fgets(email, MAX_LENGTH, stdin);
            email[strcspn(email, "\n")] = '\0';
            removeUser(email);
        } else if (choice == 4) {
            // Libera a memória alocada
            User* current = head;
            while (current != NULL) {
                User* temp = current;
                current = current->next;
                free(temp);
            }
            head = NULL;
            printf("Saindo do programa.\n");
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }
    return 0;
}
