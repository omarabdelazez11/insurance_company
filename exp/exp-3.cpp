#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_POLICIES 100
#define MAX_CUSTOMERS 100
#define MAX_CLAIMS 100

// Define structures
typedef struct {
    char username[50];
    char password[50];
    char role[20];
} User;

typedef struct {
    int policy_id;
    char type[50];
    float premium_amount;
    char start_date[20];
    char end_date[20];
    char beneficiary[100];
} Policy;

typedef struct {
    int customer_id;
    char name[100];
    char contact_info[100];
    int policy_ids[MAX_POLICIES];
    int num_policies;
} Customer;

typedef struct {
    int claim_id;
    int customer_id;
    char type[50];
    char date[20];
    char description[200];
    char status[20];
} Claim;

// Global variables
User users[MAX_USERS];
int num_users = 0;
Policy policies[MAX_POLICIES];
int num_policies = 0;
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
Claim claims[MAX_CLAIMS];
int num_claims = 0;

// Function prototypes
void registerUser();
void login();
void createPolicy();
void addCustomer();
void initiateClaim();
void viewClaims();
void generateReport();
void changePassword(int userIndex);
void saveData();
void loadData();

int main() {
    loadData();

    int choice;
    do {
        printf("\nInsurance Management System\n");
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                saveData();
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 2);

    return 0;
}

void registerUser() {
    if (num_users >= MAX_USERS) {
        printf("Cannot register more users.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", users[num_users].username);
    printf("Enter password: ");
    scanf("%s", users[num_users].password);
    printf("Enter role (admin/agent/customer): ");
    scanf("%s", users[num_users].role);

    num_users++;
    printf("User registered successfully.\n");
}

void login() {
    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int i;
    for (i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful. Welcome, %s!\n", username);
            int choice;
            do {
                if (strcmp(users[i].role, "admin") == 0) {
                    // Display admin menu options
                    printf("Admin Menu:\n");
                    printf("1. Register User\n");
                    printf("2. Create Policy\n");
                    printf("3. Add Customer\n");
                    printf("4. Initiate Claim\n");
                    printf("5. View Claims\n");
                    printf("6. Generate Report\n");
                    printf("7. Change Password\n");
                    printf("8. Logout\n");
                } else if (strcmp(users[i].role, "agent") == 0) {
                    // Display agent menu options
                    printf("Agent Menu:\n");
                    printf("1. Create Policy\n");
                    printf("2. Add Customer\n");
                    printf("3. Initiate Claim\n");
                    printf("4. View Claims\n");
                    printf("5. Change Password\n");
                    printf("6. Logout\n");
                } else if (strcmp(users[i].role, "customer") == 0) {
                    // Display customer menu options
                    printf("Customer Menu:\n");
                    printf("1. View Policies\n");
                    printf("2. Initiate Claim\n");
                    printf("3. View Claims\n");
                    printf("4. Change Password\n");
                    printf("5. Logout\n");
                }
                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        if (strcmp(users[i].role, "admin") == 0) {
                            registerUser();
                        } else if (strcmp(users[i].role, "agent") == 0) {
                            createPolicy();
                        } else if (strcmp(users[i].role, "customer") == 0) {
                            // View Policies function to be implemented
                        } else {
                            printf("Invalid choice.\n");
                        }
                        break;
                    case 2:
                        if (strcmp(users[i].role, "admin") == 0 || strcmp(users[i].role, "agent") == 0) {
                            addCustomer();
                        } else if (strcmp(users[i].role, "customer") == 0) {
                            initiateClaim();
                        } else {
                            printf("Invalid choice.\n");
                        }
                        break;
                    case 3:
                        if (strcmp(users[i].role, "admin") == 0 || strcmp(users[i].role, "agent") == 0) {
                            initiateClaim();
                        } else if (strcmp(users[i].role, "customer") == 0) {
                            viewClaims();
                        } else {
                            printf("Invalid choice.\n");
                        }
                        break;
                    case 4:
                        if (strcmp(users[i].role, "admin") == 0 || strcmp(users[i].role, "agent") == 0 || strcmp(users[i].role, "customer") == 0) {
                            viewClaims();
                        } else {
                            printf("Invalid choice.\n");
                        }
                        break;
                    case 5:
                        if (strcmp(users[i].role, "admin") == 0) {
                            generateReport();
                        } else if (strcmp(users[i].role, "agent") == 0 || strcmp(users[i].role, "customer") == 0) {
                            changePassword(i);
                        } else {
                            printf("Invalid choice.\n");
                        }
                        break;
                    case 6:
                        if (strcmp(users[i].role, "admin") == 0) {
                            changePassword(i);
                        } else if (strcmp(users[i].role, "agent") == 0) {
                            printf("Logging out.\n");
                        } else {
                            printf("Invalid choice.\n");
                        }
                        break;
                    case 7:
                        if (strcmp(users[i].role, "admin") == 0) {
                            printf("Logging out.\n");
                        } else {
                            printf("Invalid choice.\n");
                        }
                        break;
                    case 8:
                        if (strcmp(users[i].role, "admin") == 0) {
                            printf("Logging out.\n");
                        } else {
                            printf("Invalid choice.\n");
                        }
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while ((strcmp(users[i].role, "admin") == 0 && choice != 8) ||
                     (strcmp(users[i].role, "agent") == 0 && choice != 6) ||
                     (strcmp(users[i].role, "customer") == 0 && choice != 5));
            return;
        }
    }
    printf("Invalid username or password.\n");
}

void createPolicy() {
    if (num_policies >= MAX_POLICIES) {
        printf("Cannot create more policies.\n");
        return;
    }

    Policy new_policy;
    new_policy.policy_id = num_policies + 1;
    printf("Enter policy type: ");
    scanf("%s", new_policy.type);
    printf("Enter premium amount: ");
    scanf("%f", &new_policy.premium_amount);
    printf("Enter start date (YYYY-MM-DD): ");
    scanf("%s", new_policy.start_date);
    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%s", new_policy.end_date);
    printf("Enter beneficiary: ");
    scanf("%s", new_policy.beneficiary);

    policies[num_policies] = new_policy;
    num_policies++;
    printf("Policy created successfully.\n");
}

void addCustomer() {
    if (num_customers >= MAX_CUSTOMERS) {
        printf("Cannot add more customers.\n");
        return;
    }

    Customer new_customer;
    new_customer.customer_id = num_customers + 1;
    printf("Enter customer name: ");
    scanf("%s", new_customer.name);
    printf("Enter contact info: ");
    scanf("%s", new_customer.contact_info);
    new_customer.num_policies = 0; // Initialize with no policies

    customers[num_customers] = new_customer;
    num_customers++;
    printf("Customer added successfully.\n");
}

void initiateClaim() {
    if (num_claims >= MAX_CLAIMS) {
        printf("Cannot initiate more claims.\n");
        return;
    }

    Claim new_claim;
    new_claim.claim_id = num_claims + 1;
    printf("Enter customer ID: ");
    scanf("%d", &new_claim.customer_id);
    printf("Enter claim type: ");
    scanf("%s", new_claim.type);
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", new_claim.date);
    printf("Enter description: ");
    scanf("%s", new_claim.description);
    printf("Enter status: ");
    scanf("%s", new_claim.status);

    claims[num_claims] = new_claim;
    num_claims++;
    printf("Claim initiated successfully.\n");
}

void viewClaims() {
    if (num_claims == 0) {
        printf("No claims to display.\n");
        return;
    }

    for (int i = 0; i < num_claims; i++) {
        printf("Claim ID: %d\n", claims[i].claim_id);
        printf("Customer ID: %d\n", claims[i].customer_id);
        printf("Type: %s\n", claims[i].type);
        printf("Date: %s\n", claims[i].date);
        printf("Description: %s\n", claims[i].description);
        printf("Status: %s\n", claims[i].status);
        printf("------------------------\n");
    }
}

void generateReport() {
    // Report generation logic
}

void changePassword(int userIndex) {
    char currentPassword[50];
    char newPassword[50];
    char confirmPassword[50];

    printf("Enter current password: ");
    scanf("%s", currentPassword);

    if (strcmp(users[userIndex].password, currentPassword) != 0) {
        printf("Current password is incorrect.\n");
        return;
    }

    printf("Enter new password: ");
    scanf("%s", newPassword);
    printf("Confirm new password: ");
    scanf("%s", confirmPassword);

    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("Passwords do not match. Try again.\n");
        return;
    }

    strcpy(users[userIndex].password, newPassword);
    printf("Password changed successfully.\n");
}

void saveData() {
    FILE *file = fopen("data.dat", "wb");
    if (!file) {
        printf("Error opening file for saving data.\n");
        return;
    }
    fwrite(&num_users, sizeof(int), 1, file);
    fwrite(users, sizeof(User), num_users, file);
    fwrite(&num_policies, sizeof(int), 1, file);
    fwrite(policies, sizeof(Policy), num_policies, file);
    fwrite(&num_customers, sizeof(int), 1, file);
    fwrite(customers, sizeof(Customer), num_customers, file);
    fwrite(&num_claims, sizeof(int), 1, file);
    fwrite(claims, sizeof(Claim), num_claims, file);
    fclose(file);
    printf("Data saved successfully.\n");
}

void loadData() {
    FILE *file = fopen("data.dat", "rb");
    if (!file) {
        printf("No data file found. Starting with empty data.\n");

        // Create an admin account if no data file exists
        strcpy(users[num_users].username, "omar");
        strcpy(users[num_users].password, "1234");
        strcpy(users[num_users].role, "admin");
        num_users++;

        return;
    }
    fread(&num_users, sizeof(int), 1, file);
    fread(users, sizeof(User), num_users, file);
    fread(&num_policies, sizeof(int), 1, file);
    fread(policies, sizeof(Policy), num_policies, file);
    fread(&num_customers, sizeof(int), 1, file);
    fread(customers, sizeof(Customer), num_customers, file);
    fread(&num_claims, sizeof(int), 1, file);
    fread(claims, sizeof(Claim), num_claims, file);
    fclose(file);
    printf("Data loaded successfully.\n");
}
