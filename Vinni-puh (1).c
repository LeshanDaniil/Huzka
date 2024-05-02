#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_PRODUCTS 100

struct User {
    int id;
    char name[100];
};

struct Product {
    int userId;
    char name[100];
    char model[100];
    int price;
};

int main() {
    FILE *usersFile = fopen("in_1.txt", "r");
    FILE *productsFile = fopen("in_2.txt", "r");
    FILE *outputFile = fopen("out.txt", "w");

    if (usersFile == NULL || productsFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    struct User users[MAX_USERS];
    struct Product products[MAX_PRODUCTS];

    int numUsers = 0;
    int numProducts = 0;

    //читаем пользователей из файла
    while (fscanf(usersFile, "%d %s", &users[numUsers].id, users[numUsers].name) == 2) {
        numUsers++;
    }

    //читаем товары из файла
    while (fscanf(productsFile, "%d %s %s %d", &products[numProducts].userId, products[numProducts].name, 
                                                products[numProducts].model, &products[numProducts].price) == 4) {
        numProducts++;
    }

    //считаем стоимость
    for (int i = 0; i < numUsers; i++) {
        int totalCost = 0;
        for (int j = 0; j < numProducts; j++) {
            if (users[i].id == products[j].userId) {
                totalCost += products[j].price;
            }
        }
        fprintf(outputFile, "%s %d\n", users[i].name, totalCost);
    }

    fclose(usersFile);
    fclose(productsFile);
    fclose(outputFile);

    return 0;
}
