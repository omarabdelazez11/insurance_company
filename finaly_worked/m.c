#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMERS 100

// Structure to represent a customer
struct Customer {
    int id;
    char name[50];
    char policy[20];
};

// Array to store customer records
struct Customer customers[MAX_CUSTOMERS];

// Variable to keep track of the number of customers
int numCustomers = 0;

// Function to add a new customer
void addCustomer() {
    if (numCustomers >= MAX_CUSTOMERS) {
        printf("Maximum number of customers reached.\n");
        return;
    }

    struct Customer newCustomer;

    printf("Enter customer ID: ");
    scanf("%d", &newCustomer.id);
    printf("Enter customer name: ");
    scanf("%s", newCustomer.name);
    printf("Enter customer policy: ");
    scanf("%s", newCustomer.policy);

    customers[numCustomers++] = newCustomer;
}

// Function to search for a customer by ID
void searchCustomer(int id) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == id) {
            printf("Customer found:\n");
            printf("ID: %d\n", customers[i].id);
            printf("Name: %s\n", customers[i].name);
            printf("Policy: %s\n", customers[i].policy);
            return;
        }
    }
    printf("Customer with ID %d not found.\n", id);
}

// Function to delete a customer by ID
void deleteCustomer(int id) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == id) {
            for (int j = i; j < numCustomers - 1; j++) {
                customers[j] = customers[j + 1];
            }
            numCustomers--;
            printf("Customer with ID %d deleted.\n", id);
            return;
        }
    }
    printf("Customer with ID %d not found.\n", id);
}

// Function to update customer policy by ID
void updatePolicy(int id) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == id) {
            printf("Enter new policy for customer with ID %d: ", id);
            scanf("%s", customers[i].policy);
            printf("Policy updated for customer with ID %d.\n", id);
            return;
        }
    }
    printf("Customer with ID %d not found.\n", id);
}

int main() {
    int choice, id;

    do {
        printf("\nInsurance Company Management System\n");
        printf("1. Add Customer\n");
        printf("2. Search Customer\n");
        printf("3. Delete Customer\n");
        printf("4. Update Customer Policy\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                printf("Enter customer ID to search: ");
                scanf("%d", &id);
                searchCustomer(id);
                break;
            case 3:
                printf("Enter customer ID to delete: ");
                scanf("%d", &id);
                deleteCustomer(id);
                break;
            case 4:
                printf("Enter customer ID to update policy: ");
                scanf("%d", &id);
                updatePolicy(id);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

   return 0;
}
