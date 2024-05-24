#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_POLICIES 100
#define MAX_CUSTOMERS 100
#define MAX_CLAIMS 100
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 200
#define MAX_POLICY_TYPE 50
#define MAX_PERIOD_LENGTH 20
#define MAX_COVERAGE_1_OPTIONS 10
#define MAX_PASSWORD_LENGTH 100
#define MAX_POLICIES 100

// Define structures
typedef struct {
    int customer_id;
    char policyType[50];
    char period[20];
    int duration;
    float coverageAmount;
    float premium;
    float claimsCost;
    float operatingExpenses;
    float profit;
} InsurancePolicy;

// Declare the global policies array
InsurancePolicy policies[MAX_POLICIES];
int num_policies = 0;

// Other function declarations and code...
// Define structures
typedef struct {
    char username[50];
    char password[50];
    char role[20];
} User;

typedef struct {
    int customer_id;
    char name[100];
    char contact_info[100];
    int policy_ids[MAX_POLICIES];
    int num_policies;
} CustomerRecord;

typedef struct {
    int claim_id;
    int customer_id;
    char type[50];
    char date[20];
    char description[200];
    char status[20];
} Claim;

typedef struct {
    char name[50];
    int id;
    int age;
    char gender[10];
    char occupation[50];
    char contactInfo[100];
    char previousInsurance[100];
} Customer;

typedef struct {
    Customer customer;
    char policyType[100];
    double coverageAmount;
    double premium;
    int duration;  // Duration in years
    char period[1000];  // Payment period (e.g., monthly, annually)
    double claimsCost;
    double operatingExpenses;
    double profit;
} InsurancePolicy;

// Global variables
User users[MAX_USERS];
int num_users = 0;
int num_policies = 0;
CustomerRecord customers[MAX_CUSTOMERS];
int num_customers = 0;
Claim claims[MAX_CLAIMS];
int num_claims = 0;

// Function declarations
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
void viewPolicies(int customer_id);
void handleAdminMenu(int userIndex);
void handleAgentMenu(int userIndex);
void handleCustomerMenu(int userIndex);
void getInput(char* prompt, char* input, int size);
void getCustomerDetails(Customer* customer);
double calculatePremium(const char* policyType, double coverageAmount, Customer* customer);
void getPolicyDetails(InsurancePolicy* policy);
void savePolicyToCSV(InsurancePolicy* policy);
void writeFormalContract(InsurancePolicy* policy);
void saveUsersToCSV();
void loadUsersFromCSV();
void saveCustomersToCSV();
void loadCustomersFromCSV();
void saveClaimsToCSV();
void loadClaimsFromCSV();
void savePoliciesToCSV();
void loadPoliciesFromCSV();

void getInput(char* prompt, char* input, int size) {
    printf("%s", prompt);
    fgets(input, size, stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove newline character
}

void getCustomerDetails(Customer* customer) {
    char ageInput[10];

    getInput("Enter customer's name: ", customer->name, MAX_NAME_LENGTH);
    getInput("Enter customer's age: ", ageInput, 10);
    customer->age = atoi(ageInput);
    getInput("Enter customer's gender (male, female, other): ", customer->gender, 10);
    getInput("Enter customer's occupation: ", customer->occupation, 50);
    getInput("Enter customer's contact information: ", customer->contactInfo, 100);
    getInput("Enter any previous insurance policies: ", customer->previousInsurance, 100);
}

double calculatePremium(const char* policyType, double coverageAmount, Customer* customer) {
    double premium = 0.0;

    if (strcmp(policyType, "Car Insurance") == 0) {
        premium = 500; // Base premium
        if (customer->age < 25) premium += 200;
        premium += 150; // Placeholder for driving history factor
        premium += 100; // Placeholder for vehicle type factor
        premium += 50;  // Placeholder for location factor
        premium += 50;  // Placeholder for credit score factor
    } else if (strcmp(policyType, "Home Insurance") == 0) {
        premium = 700; // Base premium
        if (coverageAmount > 300000) premium += 300;
        premium += 250; // Placeholder for location factor
        premium += 100; // Placeholder for home age factor
        premium -= 50;  // Placeholder for construction materials factor
        premium += 200; // Placeholder for coverage level factor
    } else if (strcmp(policyType, "Health Insurance") == 0) {
        premium = 300; // Base premium
        if (customer->age > 45) premium += 150;
        premium += 50;  // Placeholder for higher healthcare cost region
        premium += 200; // Placeholder for tobacco use factor
        premium += 250; // Placeholder for plan type and coverage level factor
        premium += 100; // Placeholder for family size factor
        premium += 50;  // Placeholder for health status factor
    } else if (strcmp(policyType, "Life Insurance") == 0) {
        premium = 200; // Base premium
        if (customer->age > 35) premium += 100;
        premium += 50;  // Placeholder for minor health issues factor
        premium -= 20;  // Placeholder for gender factor
        premium += 50;  // Placeholder for lifestyle factor
        premium += 200; // Placeholder for higher coverage amount factor
        premium += 30;  // Placeholder for family medical history factor
    }

    return premium;
}

void getPolicyDetails(InsurancePolicy* policy) {
    char coverageInput[20];
    char policyChoiceInput[10];
    char durationInput[10];
    int policyChoice;

    getCustomerDetails(&policy->customer);

    printf("Enter policy type (1: Car Insurance, 2: Home Insurance, 3: Health Insurance, 4: Life Insurance): ");
    fgets(policyChoiceInput, 10, stdin);
    policyChoice = atoi(policyChoiceInput);

    switch (policyChoice) {
        case 1:
            strcpy(policy->policyType, "Car Insurance");
            break;
        case 2:
            strcpy(policy->policyType, "Home Insurance");
            break;
        case 3:
            strcpy(policy->policyType, "Health Insurance");
            break;
        case 4:
            strcpy(policy->policyType, "Life Insurance");
            break;
        default:
            printf("Invalid policy type!\n");
            exit(1);
    }

    getInput("Enter coverage amount: ", coverageInput, 20);
    policy->coverageAmount = atof(coverageInput);
    getInput("Enter duration of the policy (in years): ", durationInput, 10);
    policy->duration = atoi(durationInput);
    getInput("Enter payment period (e.g., monthly, annually): ", policy->period, 100);

    policy->premium = calculatePremium(policy->policyType, policy->coverageAmount, &policy->customer);
    printf("Policy created successfully!\n");
    printf("Total Premium: $%.2f\n", policy->premium);

    // Prompt for additional financial details
    getInput("Enter the total claims cost over the contract period: ", coverageInput, 20);
    policy->claimsCost = atof(coverageInput);
    getInput("Enter the total operating expenses over the contract period: ", coverageInput, 20);
    policy->operatingExpenses = atof(coverageInput);
    policy->profit = (policy->premium * policy->duration) - (policy->claimsCost + policy->operatingExpenses);
}

void savePolicyToCSV(InsurancePolicy* policy) {
    FILE *file = fopen("policies.csv", "a");
    if (file == NULL) {
        printf("Could not open file to save policy.\n");
        return;
    }

    fprintf(file, "%s,%s,%d,%s,%s,%s,%.2f,%.2f,%d,%s,%.2f,%.2f,%.2f\n", 
            policy->customer.name, policy->customer.occupation, policy->customer.age, 
            policy->customer.gender, policy->customer.contactInfo, 
            policy->customer.previousInsurance, policy->coverageAmount, 
            policy->premium, policy->duration, policy->period, 
            policy->claimsCost, policy->operatingExpenses, policy->profit);
    fclose(file);
}

void writeFormalContract(InsurancePolicy* policy) {
    FILE *file = fopen("contract.txt", "w");
    if (file == NULL) {
        printf("Could not open file to write contract.\n");
        return;
    }

    fprintf(file, "Formal Insurance Contract\n");
    fprintf(file, "========================\n\n");
    fprintf(file, "Customer Details:\n");
    fprintf(file, "-----------------\n");
    fprintf(file, "Name: %s\n", policy->customer.name);
    fprintf(file, "Age: %d\n", policy->customer.age);
    fprintf(file, "Gender: %s\n", policy->customer.gender);
    fprintf(file, "Occupation: %s\n", policy->customer.occupation);
    fprintf(file, "Contact Info: %s\n", policy->customer.contactInfo);
    fprintf(file, "Previous Insurance: %s\n\n", policy->customer.previousInsurance);

    fprintf(file, "Policy Details:\n");
    fprintf(file, "---------------\n");
    fprintf(file, "Policy Type: %s\n", policy->policyType);
    fprintf(file, "Coverage Amount: $%.2f\n", policy->coverageAmount);
    fprintf(file, "Premium: $%.2f\n", policy->premium);
    fprintf(file, "Duration: %d years\n", policy->duration);
    fprintf(file, "Payment Period: %s\n\n", policy->period);

    fprintf(file, "Financial Summary:\n");
    fprintf(file, "------------------\n");
    fprintf(file, "Total Claims Cost: $%.2f\n", policy->claimsCost);
    fprintf(file, "Total Operating Expenses: $%.2f\n", policy->operatingExpenses);
    fprintf(file, "Projected Profit: $%.2f\n", policy->profit);

    fclose(file);
    printf("Formal contract written to contract.txt\n");
}

void registerUser() {
    if (num_users >= MAX_USERS) {
        printf("User registration limit reached.\n");
        return;
    }

    char username[50];
    char password[50];
    char role[20];

    getInput("Enter username: ", username, 50);
    getInput("Enter password: ", password, 50);
    getInput("Enter role (admin, agent, customer): ", role, 20);

    strcpy(users[num_users].username, username);
    strcpy(users[num_users].password, password);
    strcpy(users[num_users].role, role);

    num_users++;
    saveUsersToCSV();

    printf("User registered successfully.\n");
}

void login() {
    char username[50];
    char password[50];
    int userIndex = -1;

    getInput("Enter username: ", username, 50);
    getInput("Enter password: ", password, 50);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("Invalid username or password.\n");
        return;
    }

    printf("Login successful.\n");

    if (strcmp(users[userIndex].role, "admin") == 0) {
        handleAdminMenu(userIndex);
    } else if (strcmp(users[userIndex].role, "agent") == 0) {
        handleAgentMenu(userIndex);
    } else if (strcmp(users[userIndex].role, "customer") == 0) {
        handleCustomerMenu(userIndex);
    } else {
        printf("Unknown role.\n");
    }
}

void createPolicy() {
    InsurancePolicy policy;
    getPolicyDetails(&policy);
    savePolicyToCSV(&policy);
    writeFormalContract(&policy);
}

void addCustomer() {
    if (num_customers >= MAX_CUSTOMERS) {
        printf("Customer limit reached.\n");
        return;
    }

    CustomerRecord customer;

    customer.customer_id = num_customers + 1;
    getInput("Enter customer's name: ", customer.name, 100);
    getInput("Enter customer's contact information: ", customer.contact_info, 100);

    customer.num_policies = 0;
    customers[num_customers] = customer;
    num_customers++;

    saveCustomersToCSV();

    printf("Customer added successfully.\n");
}

void initiateClaim() {
    if (num_claims >= MAX_CLAIMS) {
        printf("Claim limit reached.\n");
        return;
    }

    Claim claim;
    char customerIdInput[10];
    char claimIdInput[10];

    claim.claim_id = num_claims + 1;

    getInput("Enter customer ID: ", customerIdInput, 10);
    claim.customer_id = atoi(customerIdInput);

    getInput("Enter claim type: ", claim.type, 50);
    getInput("Enter claim date: ", claim.date, 20);
    getInput("Enter claim description: ", claim.description, 200);
    strcpy(claim.status, "Pending");

    claims[num_claims] = claim;
    num_claims++;

    saveClaimsToCSV();

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

void viewPolicies(int customer_id) {
    FILE *file = fopen("policies.csv", "r");
    if (file == NULL) {
        printf("Could not open policies file.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        if (atoi(token) == customer_id) {
            printf("Customer ID: %s\n", token);
            printf("Name: %s\n", strtok(NULL, ","));
            printf("Occupation: %s\n", strtok(NULL, ","));
            printf("Age: %s\n", strtok(NULL, ","));
            printf("Gender: %s\n", strtok(NULL, ","));
            printf("Contact Info: %s\n", strtok(NULL, ","));
            printf("Previous Insurance: %s\n", strtok(NULL, ","));
            printf("Coverage Amount: %s\n", strtok(NULL, ","));
            printf("Premium: %s\n", strtok(NULL, ","));
            printf("Duration: %s\n", strtok(NULL, ","));
            printf("Payment Period: %s\n", strtok(NULL, ","));
            printf("Total Claims Cost: %s\n", strtok(NULL, ","));
            printf("Operating Expenses: %s\n", strtok(NULL, ","));
            printf("Profit: %s\n\n", strtok(NULL, ","));
        }
    }
    fclose(file);
}

void generateReport() {
    double totalPremiums = 0;
    double totalClaimsCost = 0;
    double totalOperatingExpenses = 0;
    double totalProfit = 0;

    FILE *file = fopen("policies.csv", "r");
    if (file == NULL) {
        printf("Could not open policies file.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        for (int i = 0; i < 8; i++) token = strtok(NULL, ",");  // Skip to premium
        totalPremiums += atof(token);

        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        totalClaimsCost += atof(token);

        token = strtok(NULL, ",");
        totalOperatingExpenses += atof(token);

        token = strtok(NULL, ",");
        totalProfit += atof(token);
    }
    fclose(file);

    printf("Total Premiums: $%.2f\n", totalPremiums);
    printf("Total Claims Cost: $%.2f\n", totalClaimsCost);
    printf("Total Operating Expenses: $%.2f\n", totalOperatingExpenses);
    printf("Total Profit: $%.2f\n", totalProfit);
}

void changePassword(int userIndex) {
    char newPassword[50];
    getInput("Enter new password: ", newPassword, 50);
    strcpy(users[userIndex].password, newPassword);
    saveUsersToCSV();
    printf("Password changed successfully.\n");
}

void saveUsersToCSV() {
    FILE *file = fopen("users.csv", "w");
    if (file == NULL) {
        printf("Could not open users file to save.\n");
        return;
    }

    for (int i = 0; i < num_users; i++) {
        fprintf(file, "%s,%s,%s\n", users[i].username, users[i].password, users[i].role);
    }
    fclose(file);
}

void loadUsersFromCSV() {
    FILE *file = fopen("users.csv", "r");
    if (file == NULL) {
        printf("Could not open users file to load.\n");
        return;
    }

    num_users = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^,\n]", users[num_users].username, users[num_users].password, users[num_users].role);
        num_users++;
    }
    fclose(file);
}

void saveCustomersToCSV() {
    FILE *file = fopen("customers.csv", "w");
    if (file == NULL) {
        printf("Could not open customers file to save.\n");
        return;
    }

    for (int i = 0; i < num_customers; i++) {
        fprintf(file, "%d,%s,%s,%d\n", customers[i].customer_id, customers[i].name, customers[i].contact_info, customers[i].num_policies);
        for (int j = 0; j < customers[i].num_policies; j++) {
            fprintf(file, "%d,", customers[i].policy_ids[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void loadCustomersFromCSV() {
    FILE *file = fopen("customers.csv", "r");
    if (file == NULL) {
        printf("Could not open customers file to load.\n");
        return;
    }

    num_customers = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%[^,],%d", &customers[num_customers].customer_id, customers[num_customers].name, customers[num_customers].contact_info, &customers[num_customers].num_policies);
        for (int i = 0; i < customers[num_customers].num_policies; i++) {
            fscanf(file, "%d,", &customers[num_customers].policy_ids[i]);
        }
        num_customers++;
    }
    fclose(file);
}

void savePoliciesToCSV() {
    FILE *file = fopen("policies.csv", "w");
    if (file == NULL) {
        printf("Could not open policies file to save.\n");
        return;
    }

    for (int i = 0; i < num_policies; i++) {
        fprintf(file, "%d,%s,%s,%d,%s,%.2f,%.2f,%.2f,%.2f\n", 
                policies[i].customer_id, 
                policies[i].policyType, 
                policies[i].period, 
                policies[i].duration, 
                policies[i].policyType, 
                policies[i].coverageAmount, 
                policies[i].premium, 
                policies[i].claimsCost, 
                policies[i].operatingExpenses, 
                policies[i].profit);
    }
    fclose(file);
}


void loadPoliciesFromCSV() {
    FILE *file = fopen("policies.csv", "r");
    if (file == NULL) {
        printf("Could not open policies file to load.\n");
        return;
    }

    num_policies = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%[^,],%d,%[^,],%f,%f,%f,%f,%f", 
               &policies[num_policies].customer_id, 
               policies[num_policies].policyType, 
               policies[num_policies].period, 
               &policies[num_policies].duration, 
               policies[num_policies].policyType, 
               &policies[num_policies].coverageAmount, 
               &policies[num_policies].premium, 
               &policies[num_policies].claimsCost, 
               &policies[num_policies].operatingExpenses, 
               &policies[num_policies].profit);
        num_policies++;
    }
    fclose(file);
}

void saveClaimsToCSV() {
    FILE *file = fopen("claims.csv", "w");
    if (file == NULL) {
        printf("Could not open claims file to save.\n");
        return;
    }

    for (int i = 0; i < num_claims; i++) {
        fprintf(file, "%d,%d,%s,%s,%s,%s\n", claims[i].claim_id, claims[i].customer_id, claims[i].type, claims[i].date, claims[i].description, claims[i].status);
    }
    fclose(file);
}

void loadClaimsFromCSV() {
    FILE *file = fopen("claims.csv", "r");
    if (file == NULL) {
        printf("Could not open claims file to load.\n");
        return;
    }

    num_claims = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%d,%[^,],%[^,],%[^,],%[^,\n]", &claims[num_claims].claim_id, &claims[num_claims].customer_id, claims[num_claims].type, claims[num_claims].date, claims[num_claims].description, claims[num_claims].status);
        num_claims++;
    }
    fclose(file);
}

void handleAdminMenu(int userIndex) {
    while (1) {
        printf("Admin Menu:\n");
        printf("1. Register User\n");
        printf("2. Add Customer\n");
        printf("3. View Claims\n");
        printf("4. Generate Report\n");
        printf("5. Change Password\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                addCustomer();
                break;
            case 3:
                viewClaims();
                break;
            case 4:
                generateReport();
                break;
            case 5:
                changePassword(userIndex);
                break;
            case 6:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void handleAgentMenu(int userIndex) {
    while (1) {
        printf("Agent Menu:\n");
        printf("1. Create Policy\n");
        printf("2. Initiate Claim\n");
        printf("3. View Claims\n");
        printf("4. Change Password\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                createPolicy();
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
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void handleCustomerMenu(int userIndex) {
    while (1) {
        printf("Customer Menu:\n");
        printf("1. View Policies\n");
        printf("2. Change Password\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                viewPolicies(users[userIndex].username);
                break;
            case 2:
                changePassword(userIndex);
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    loadUsersFromCSV();
    loadCustomersFromCSV();
    loadPoliciesFromCSV();
    loadClaimsFromCSV();

    while (1) {
        printf("Insurance Management System\n");
        printf("1. Login\n");
        printf("2. Register User\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
