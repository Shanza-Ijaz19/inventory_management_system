#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

// Product structure
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Product;

// Function prototypes
void addProduct(Product products[], int *count);
void displayProducts(Product products[], int count);
void searchProduct(Product products[], int count);
void updateProduct(Product products[], int count);
void deleteProduct(Product products[], int *count);
void saveToFile(Product products[], int count);
void loadFromFile(Product products[], int *count);

int main() {
    Product products[MAX_PRODUCTS];
    int count = 0;
    int choice;

    // Load existing data from file at program start
    loadFromFile(products, &count);

    while(1) {
        printf("\n====================================\n");
        printf("       INVENTORY MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search Product\n");
        printf("4. Update Product\n");
        printf("5. Delete Product\n");
        printf("6. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addProduct(products, &count); break;
            case 2: displayProducts(products, count); break;
            case 3: searchProduct(products, count); break;
            case 4: updateProduct(products, count); break;
            case 5: deleteProduct(products, &count); break;
            case 6: 
                saveToFile(products, count);
                printf("\nData saved successfully. Exiting program...\n");
                return 0;
            default: printf("\nInvalid choice! Try again.\n");
        }
    }
    return 0;
}

// ADD PRODUCT
void addProduct(Product products[], int *count) {
    if(*count >= MAX_PRODUCTS) {
        printf("\nInventory full! Cannot add more products.\n");
        return;
    }
    printf("\nEnter Product ID: ");
    scanf("%d", &products[*count].id);
    printf("Enter Product Name: ");
    scanf(" %[^\n]", products[*count].name);  // read string with spaces
    printf("Enter Quantity: ");
    scanf("%d", &products[*count].quantity);
    printf("Enter Price: ");
    scanf("%f", &products[*count].price);
    (*count)++;
    printf("\nProduct added successfully!\n");
}

// DISPLAY PRODUCTS
void displayProducts(Product products[], int count) {
    if(count == 0) {
        printf("\nNo products available.\n");
        return;
    }
    printf("\n-------------------------------------------------\n");
    printf("| %-5s | %-20s | %-8s | %-8s |\n", "ID", "Name", "Quantity", "Price");
    printf("-------------------------------------------------\n");
    for(int i=0; i<count; i++) {
        printf("| %-5d | %-20s | %-8d | %-8.2f |\n",
               products[i].id, products[i].name, products[i].quantity, products[i].price);
    }
    printf("-------------------------------------------------\n");
}

// SEARCH PRODUCT
void searchProduct(Product products[], int count) {
    if(count == 0) {
        printf("\nInventory empty.\n");
        return;
    }
    int id, found=0;
    printf("\nEnter Product ID to search: ");
    scanf("%d", &id);
    for(int i=0; i<count; i++) {
        if(products[i].id == id) {
            printf("\nProduct Found:\n");
            printf("ID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n",
                   products[i].id, products[i].name, products[i].quantity, products[i].price);
            found = 1;
            break;
        }
    }
    if(!found)
        printf("\nProduct not found.\n");
}

// UPDATE PRODUCT
void updateProduct(Product products[], int count) {
    if(count == 0) {
        printf("\nInventory empty.\n");
        return;
    }
    int id, found=0;
    printf("\nEnter Product ID to update: ");
    scanf("%d", &id);
    for(int i=0; i<count; i++) {
        if(products[i].id == id) {
            printf("\nEnter new Product Name: ");
            scanf(" %[^\n]", products[i].name);
            printf("Enter new Quantity: ");
            scanf("%d", &products[i].quantity);
            printf("Enter new Price: ");
            scanf("%f", &products[i].price);
            printf("\nProduct updated successfully!\n");
            found = 1;
            break;
        }
    }
    if(!found)
        printf("\nProduct not found.\n");
}

// DELETE PRODUCT
void deleteProduct(Product products[], int *count) {
    if(*count == 0) {
        printf("\nInventory empty.\n");
        return;
    }
    int id, found=0;
    printf("\nEnter Product ID to delete: ");
    scanf("%d", &id);
    for(int i=0; i<*count; i++) {
        if(products[i].id == id) {
            for(int j=i; j<*count-1; j++) {
                products[j] = products[j+1];
            }
            (*count)--;
            printf("\nProduct deleted successfully!\n");
            found = 1;
            break;
        }
    }
    if(!found)
        printf("\nProduct not found.\n");
}

// SAVE TO FILE
void saveToFile(Product products[], int count) {
    FILE *f = fopen("inventory.txt", "w");
    if(f == NULL) {
        printf("\nError opening file!\n");
        return;
    }
    for(int i=0; i<count; i++) {
        fprintf(f, "%d,%s,%d,%.2f\n",
                products[i].id, products[i].name,
                products[i].quantity, products[i].price);
    }
    fclose(f);
}

// LOAD FROM FILE
void loadFromFile(Product products[], int *count) {
    FILE *f = fopen("inventory.txt", "r");
    if(f == NULL) return;  // File doesn't exist yet
    while(fscanf(f, "%d,%49[^,],%d,%f\n",
                 &products[*count].id, products[*count].name,
                 &products[*count].quantity, &products[*count].price) == 4) {
        (*count)++;
        if(*count >= MAX_PRODUCTS) break;
    }
    fclose(f);
}

