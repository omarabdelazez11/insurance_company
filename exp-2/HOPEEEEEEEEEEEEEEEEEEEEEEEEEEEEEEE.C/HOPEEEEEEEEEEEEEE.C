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
    
          char name[MAX_NAME_LENGTH];
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


///////////Policy policies[MAX_POLICIES];
int num_policies = 0;
CustomerRecord customers[MAX_CUSTOMERS];
int num_customers = 0;
Claim claims[MAX_CLAIMS];
int num_claims = 0;





/// ////////////////////////////////////////////////////
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
/////////////////////////////////////////////


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
    fprintf(file, "Type: %s\n", policy->policyType);
    fprintf(file, "Coverage Amount: $%.2f\n", policy->coverageAmount);
    fprintf(file, "Premium: $%.2f per %s\n", policy->premium, policy->period);
    fprintf(file, "Duration: %d years\n\n", policy->duration);

    fprintf(file, "Financial Summary:\n");
    fprintf(file, "-------------------\n");
    fprintf(file, "Total Claims Cost: $%.2f\n", policy->claimsCost);
    fprintf(file, "Total Operating Expenses: $%.2f\n", policy->operatingExpenses);
    fprintf(file, "Profit: $%.2f\n\n", policy->profit);

    fprintf(file, "Coverage Details:\n");
    fprintf(file, "-----------------\n");
    fprintf(file, "Covered: Natural disasters, Theft, Accidents\n");
    fprintf(file, "Not Covered: Intentional damages, Negligence (e.g., leaving keys in the car),\n");
    fprintf(file, "             Fraudulent claims\n\n");

    fprintf(file, "Approval:\n");
    fprintf(file, "---------\n");
    fprintf(file, "I, %s, hereby acknowledge that I have reviewed the terms of this insurance contract "
                    "and understand the coverage details, premium, duration, and payment period. I agree "
                    "to the terms outlined in this contract and authorize the insurance company to proceed "
                    "with the policy as described above.\n\n", policy->customer.name);

    fprintf(file, "Signature: _________________________\n");
    fprintf(file, "Date: _____________________________\n");

    fclose(file);
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
//
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
//
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
//
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
//
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
void creatPolicy (){
  InsurancePolicy policy;
    getPolicyDetails(&policy);
    savePolicyToCSV(&policy);
    writeFormalContract(&policy);

}

void addCustomer() {
    if (num_customers >= MAX_CUSTOMERS) {
        printf("Cannot add more customers.\n");
        return;
    }

    CustomerRecord new_customer;
    new_customer.customer_id = num_customers + 1;
    new_customer.num_policies = 0;

    printf("Enter customer name: ");
    scanf("%s", new_customer.name);
    printf("Enter contact info: ");
    scanf("%s", new_customer.contact_info);

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
    scanf(" %[^\n]", new_claim.description);  // Use " %[^\n]" to read until newline
    strcpy(new_claim.status, "Pending");

    claims[num_claims] = new_claim;
    num_claims++;
    printf("Claim initiated successfully.\n");
}

void viewClaims() {
    printf("Claims:\n");
    for (int i = 0; i < num_claims; i++) {
        printf("Claim ID: %d\n", claims[i].claim_id);
        printf("Customer ID: %d\n", claims[i].customer_id);
        printf("Type: %s\n", claims[i].type);
        printf("Date: %s\n", claims[i].date);
        printf("Description: %s\n", claims[i].description);
        printf("Status: %s\n\n", claims[i].status);
    }
}
#define MAX_PASSWORD_LENGTH 50

// Define the User structure
typedef struct {
    char username[50];
    char password[MAX_PASSWORD_LENGTH];
    char role[20];
} User;

 

// Function prototypes
void changePassword(int userIndex);

void changePassword(int userIndex) {
    char new_password[MAX_PASSWORD_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    printf("Enter new password: ");
    scanf("%s", new_password);

    printf("Confirm new password: ");
    scanf("%s", confirm_password);

    if (strcmp(new_password, confirm_password) != 0) {
        printf("Passwords do not match. Please try again.\n");
        return;
    }

    // Update the password if the confirmation matches
    strcpy(users[userIndex].password, new_password);
    printf("Password changed successfully.\n");
}




















int main() {
 printf("vv");
    return 0;
}

