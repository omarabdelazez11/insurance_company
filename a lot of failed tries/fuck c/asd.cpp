#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_POLICIES 100
#define MAX_CUSTOMERS 100
#define MAX_CLAIMS 100
#define MAX_FUTURE_POLICIES 100

// Define structures
typedef struct {
    char username[50];
    char email[100];
    char password_hash[65];
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

// Function prototypes
void registerUser();
void login();
void createPolicy();
void createFuturePolicy();
void addCustomer();
void initiateClaim();
void viewClaims();
void generateReport();
void changePassword(int userIndex);
void saveData();
void loadData();
void hashPassword(const char* password, char* hash);
void collectCustomerInfo();

void hashPassword(const char* password, char* hash) {
    unsigned long hash_value = 5381;
    int c;
    while ((c = *password++))
        hash_value = ((hash_value << 5) + hash_value) + c; // hash * 33 + c
    snprintf(hash, 65, "%lx", hash_value);
}

int main() {
    // Initialize admin user
    strcpy(users[num_users].username, "omar");
    strcpy(users[num_users].email, "omar@example.com");
    hashPassword("1234", users[num_users].password_hash);
    strcpy(users[num_users].role, "admin");
    num_users++; // Increment number of users
    
    loadData(); // Load existing data from files if available
    
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
                saveData(); // Save data before exiting
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
    printf("Enter email: ");
    scanf("%s", users[num_users].email);
    char password[50];
    printf("Enter password: ");
    scanf("%s", password);
    hashPassword(password, users[num_users].password_hash);
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
    char password_hash[65];
    hashPassword(password, password_hash);
    int found = 0; // Flag to indicate if user is found
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password_hash, password_hash) == 0) {
            found = 1; // User found
            printf("Login successful. Welcome, %s!\n", username);
            // Proceed with user-specific menu options
            // (Admin, Agent, Customer)
            // Implement the menu here based on user role
            int user_choice;
            do {
                if (strcmp(users[i].role, "admin") == 0) {
                    printf("Admin Menu:\n");
                    printf("1. Register User\n");
                    printf("2. Create Policy\n");
                    printf("3. Add Customer\n");
                    printf("4. Initiate Claim\n");
                    printf("5. View Claims\n");
                    printf("6. Generate Report\n");
                    printf("7. Change Password\n");
                    printf("8. Collect Customer Info\n");
                    printf("9. Logout\n");
                    printf("10. Create Future Policy\n");
                } else if (strcmp(users[i].role, "agent") == 0) {
                    printf("Agent Menu:\n");
                    printf("1. Create Policy\n");
                    printf("2. Add Customer\n");
                    printf("3. Initiate Claim\n");
                    printf("4. View Claims\n");
                    printf("5. Change Password\n");
                    printf("6. Collect Customer Info\n");
                    printf("7. Logout\n");
                } else if (strcmp(users[i].role, "customer") == 0) {
                    printf("Customer Menu:\n");
                    printf("1. View Policies\n");
                    printf("2. Initiate Claim\n");
                    printf("3. View Claims\n");
                    printf("4. Change Password\n");
                    printf("5. Logout\n");
                }
                printf("Enter your choice: ");
                if (scanf("%d", &user_choice) != 1) {
                    printf("Invalid choice. Please enter a number.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    continue;
                }
                switch (user_choice) {
                    case 1:
                        if (strcmp(users[i].role, "admin") == 0) registerUser();
                        else if (strcmp(users[i].role, "agent") == 0) createPolicy();
                        else if (strcmp(users[i].role, "customer") == 0) viewClaims();
                        else printf("Invalid choice.\n");
                        break;
                    case 2:
                        if (strcmp(users[i].role, "admin") == 0) createPolicy();
                        else if (strcmp(users[i].role, "agent") == 0) addCustomer();
                        else if (strcmp(users[i].role, "customer") == 0) initiateClaim();
                        else printf("Invalid choice.\n");
                        break;
                    case 3:
                        if (strcmp(users[i].role, "admin") == 0) addCustomer();
                        else if (strcmp(users[i].role, "agent") == 0) initiateClaim();
                        else if (strcmp(users[i].role, "customer") == 0) viewClaims();
                        else printf("Invalid choice.\n");
                        break;
                    case 4:
                        if (strcmp(users[i].role, "admin") == 0) initiateClaim();
                        else if (strcmp(users[i].role, "agent") == 0) viewClaims();
                        else if (strcmp(users[i].role, "customer") == 0) changePassword(i);
                        else printf("Invalid choice.\n");
                        break;
                    case 5:
                        if (strcmp(users[i].role, "admin") == 0) viewClaims();
                        else if (strcmp(users[i].role, "agent") == 0) changePassword(i);
                        else if (strcmp(users[i].role, "customer") == 0) printf("Logging out.\n");
                        else printf("Invalid choice.\n");
                        break;
                    case 6:
                        if (strcmp(users[i].role, "admin") == 0) changePassword(i);
                        else if (strcmp(users[i].role, "agent") == 0) collectCustomerInfo();
                        else printf("Invalid choice.\n");
                        break;
                    case 7:
                        if (strcmp(users[i].role, "admin") == 0) collectCustomerInfo();
                        else if (strcmp(users[i].role, "agent") == 0) printf("Logging out.\n");
                        else printf("Invalid choice.\n");
                        break;
                    case 8:
                        if (strcmp(users[i].role, "admin") == 0) printf("Logging out.\n");
                        else printf("Invalid choice.\n");
                        break;
                    case 9:
                        if (strcmp(users[i].role, "admin") == 0) printf("Logging out.\n");
                        else printf("Invalid choice.\n");
                        break;
                    case 10:
                        if (strcmp(users[i].role, "admin") == 0) createFuturePolicy();
                        else printf("Invalid choice.\n");
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while ((strcmp(users[i].role, "admin") == 0 && user_choice != 9) || 
                     (strcmp(users[i].role, "agent") == 0 && user_choice != 7) || 
                     (strcmp(users[i].role, "customer") == 0 && user_choice != 5));
            break; // Exit for-loop if user is found and logged in
        }
    }
    if (!found) {
        printf("Invalid username or password.\n");
    }
}


void createPolicy() {
    if (num_policies >= MAX_POLICIES) {
        printf("Cannot create more policies.\n");
        return;
    }
    printf("Enter policy type: ");
    scanf("%s", policies[num_policies].type);
    printf("Enter premium amount: ");
    scanf("%f", &policies[num_policies].premium_amount);
    printf("Enter start date (YYYY-MM-DD): ");
    scanf("%s", policies[num_policies].start_date);
    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%s", policies[num_policies].end_date);
    printf("Enter beneficiary: ");
    scanf("%s", policies[num_policies].beneficiary);
    policies[num_policies].policy_id = num_policies + 1;
    num_policies++;
    printf("Policy created successfully.\n");
}

void createFuturePolicy() {
    if (num_future_policies >= MAX_FUTURE_POLICIES) {
        printf("Cannot create more future policies.\n");
        return;
    }
    printf("Enter future policy type: ");
    scanf("%s", future_policies[num_future_policies].type);
    printf("Enter premium amount: ");
    scanf("%f", &future_policies[num_future_policies].premium_amount);
    printf("Enter start date (YYYY-MM-DD): ");
    scanf("%s", future_policies[num_future_policies].start_date);
    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%s", future_policies[num_future_policies].end_date);
    printf("Enter beneficiary: ");
    scanf("%s", future_policies[num_future_policies].beneficiary);
    future_policies[num_future_policies].future_policy_id = num_future_policies + 1;
    num_future_policies++;
    printf("Future policy created successfully.\n");
}

void addCustomer() {
    if (num_customers >= MAX_CUSTOMERS) {
        printf("Cannot add more customers.\n");
        return;
    }
    printf("Enter customer name: ");
    scanf("%s", customers[num_customers].name);
    printf("Enter contact info: ");
    scanf("%s", customers[num_customers].contact_info);
    customers[num_customers].customer_id = num_customers + 1;
    customers[num_customers].num_policies = 0;
    num_customers++;
    printf("Customer added successfully.\n");
}

void initiateClaim() {
    if (num_claims >= MAX_CLAIMS) {
        printf("Cannot initiate more claims.\n");
        return;
    }
    printf("Enter customer ID: ");
    scanf("%d", &claims[num_claims].customer_id);
    printf("Enter claim type: ");
    scanf("%s", claims[num_claims].type);
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", claims[num_claims].date);
    printf("Enter description: ");
    scanf("%s", claims[num_claims].description);
    strcpy(claims[num_claims].status, "Pending");
    claims[num_claims].claim_id = num_claims + 1;
    num_claims++;
    printf("Claim initiated successfully.\n");
}

void viewClaims() {
    for (int i = 0; i < num_claims; i++) {
        printf("Claim ID: %d\n", claims[i].claim_id);
        printf("Customer ID: %d\n", claims[i].customer_id);
        printf("Type: %s\n", claims[i].type);
        printf("Date: %s\n", claims[i].date);
        printf("Description: %s\n", claims[i].description);
        printf("Status: %s\n\n", claims[i].status);
    }
}

void generateReport() {
    printf("Generating report...\n");
    printf("Total users: %d\n", num_users);
    printf("Total policies: %d\n", num_policies);
    printf("Total customers: %d\n", num_customers);
    printf("Total claims: %d\n", num_claims);
}

void changePassword(int userIndex) {
    char old_password[50];
    char new_password[50];
    printf("Enter old password: ");
    scanf("%s", old_password);
    char old_password_hash[65];
    hashPassword(old_password, old_password_hash);
    if (strcmp(users[userIndex].password_hash, old_password_hash) == 0) {
        printf("Enter new password: ");
        scanf("%s", new_password);
        hashPassword(new_password, users[userIndex].password_hash);
        printf("Password changed successfully.\n");
    } else {
        printf("Incorrect old password.\n");
    }
}

void saveData() {
    // Implement data saving to files
}

void loadData() {
    // Implement data loading from files
}

void collectCustomerInfo() {
    // Implement customer info collection
}
