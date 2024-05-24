#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 100
#define MAX_POLICIES 100
#define MAX_CUSTOMERS 100
#define MAX_CLAIMS 100
#define MAX_FUTURE_POLICIES 100

// Define structures
typedef struct {
    char username[50];
    char email[100];
    char password [65];
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

typedef struct {
    int future_policy_id;
    char type[50];
    float premium_amount;
    char start_date[20];
    char end_date[20];
    char beneficiary[100];
} FuturePolicy;

// Global variables
User users[MAX_USERS];
int num_users = 0;
Policy policies[MAX_POLICIES];
int num_policies = 0;
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
Claim claims[MAX_CLAIMS];
int num_claims = 0;
FuturePolicy future_policies[MAX_FUTURE_POLICIES];
int num_future_policies = 0;


//functions for register and login
void registerUser();
void login();
void viewPolicies(int customer_id);
void handleAdminMenu(int userIndex);
void handleAgentMenu(int userIndex);
void handleCustomerMenu(int userIndex);
//end of them

void createPolicy();
void addCustomer();
void initiateClaim();
void viewClaims();
void generateReport();
void changePassword(int userIndex);

int main (){
    return 0;
}

//code writting for login and register
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
            if (strcmp(users[i].role, "admin") == 0) {
                handleAdminMenu(i);
            } else if (strcmp(users[i].role, "agent") == 0) {
                handleAgentMenu(i);
            } else if (strcmp(users[i].role, "customer") == 0) {
                handleCustomerMenu(i);
            } else {
                printf("Unknown role. Access denied.\n");
            }
            return;
        }
    }
    printf("Invalid username or password.\n");
}

int isValidEmail(const char *email) {
    int atCount = 0, dotCount = 0;
    for (const char *ptr = email; *ptr != '\0'; ptr++) {
        if (*ptr == '@') {
            atCount++;
        } else if (*ptr == '.' && ptr > email && *(ptr + 1) != '\0') {
            dotCount++;
        }
    }
    return atCount == 1 && dotCount >= 1;
}

int isValidPassword(const char *password) {
    int hasLetter = 0, hasSpecial = 0, len = strlen(password);
    if (len < 8) return 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(password[i])) hasLetter = 1;
        else if (!isalnum(password[i])) hasSpecial = 1;
    }
    return hasLetter && hasSpecial;
}

void registerUser() {
    if (num_users >= MAX_USERS) {
        printf("Cannot register more users.\n");
        return;
    }

    User *newUser = &users[num_users];

    printf("Enter username: ");
    scanf("%49s", newUser->username);

    char email[50];
    do {
        printf("Enter email: ");
        scanf("%49s", email);
        if (!isValidEmail(email)) {
            printf("Invalid email format. Please enter a valid email.\n");
        }
    } while (!isValidEmail(email));
    strcpy(newUser->email, email);

    char password[50];
    do {
        printf("Enter password: ");
        scanf("%49s", password);
        if (!isValidPassword(password)) {
            printf("Password must be at least 8 characters long, contain at least one letter and one special character.\n");
        }
    } while (!isValidPassword(password));
    strcpy(newUser->password, password);

    int roleChoice;
    do {
        printf("Choose role: \n1. Admin 2. \nAgent \n3. Customer\n");
        scanf("%d", &roleChoice);
        if (roleChoice < 1 || roleChoice > 3) {
            printf("Invalid choice. Please choose a valid role.\n");
        }
    } while (roleChoice < 1 || roleChoice > 3);
    strcpy(newUser->role, (roleChoice == 1) ? "admin" : (roleChoice == 2) ? "agent" : "customer");

    num_users++;
    printf("User registered successfully.\n");
}

void handleAdminMenu(int userIndex) {
    int choice;
    do {
        printf("Admin Menu:\n");
        printf("1. Register User\n");
        printf("2. Create Policy\n");
        printf("3. Add Customer\n");
        printf("4. Initiate Claim\n");
        printf("5. View Claims\n");
        printf("6. Generate Report\n");
        printf("7. Change Password\n");
        printf("8. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                createPolicy();
                break;
            case 3:
                addCustomer();
                break;
            case 4:
                initiateClaim();
                break;
            case 5:
                viewClaims();
                break;
            case 6:
                generateReport();
                break;
            case 7:
                changePassword(userIndex);
                break;
            case 8:
                printf("Logging out.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);
}

void handleAgentMenu(int userIndex) {
    int choice;
    do {
        printf("Agent Menu:\n");
        printf("1. Create Policy\n");
        printf("2. Add Customer\n");
        printf("3. Initiate Claim\n");
        printf("4. View Claims\n");
        printf("5. Change Password\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createPolicy();
                break;
            case 2:
                addCustomer();
                break;
            case 3:
                initiateClaim();
                break;
            case 4:
                viewClaims();
                break;
            case 5:
                changePassword(userIndex);
                break;
            case 6:
                printf("Logging out.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

void handleCustomerMenu(int userIndex) {
    int customer_id;
    for (int i = 0; i < num_customers; i++) {
        if (strcmp(users[userIndex].username, customers[i].name) == 0) {
            customer_id = customers[i].customer_id;
            break;
        }
    }

    int choice;
    do {
        printf("Customer Menu:\n");
        printf("1. View Policies\n");
        printf("2. Initiate Claim\n");
        printf("3. View Claims\n");
        printf("4. Change Password\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                viewPolicies(customer_id);
                break;
            case 2:
                initiateClaim();
                break;
            case 3:
                viewClaims();
                break;
            case 4:
                changePassword(userIndex);
                break;
            case 5:
                printf("Logging out.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}



















