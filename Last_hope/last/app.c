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
#define MAX_COVERAGE_1_OPTIONS 10
// Define structures
typedef struct {
    char username[50];
    char password[50];
    char role[20];
} User;

typedef struct {
    char name[50];
    int id;
    int age;
    char gender[10];
} Customer;

typedef struct {
    int policy_id;
    char type[20];
    union {
        struct {
            char vehicleType[20];
            char location[50];
            char usage[20];
            char coverageLevel[20];
        } carPolicy;
        struct {
            double homeValue;
            double rebuildingCost;
            char location[50];
            int homeAge;
            char condition[20];
            char constructionMaterials[20];
            char coverageLevel[20];
        } homePolicy;
        struct {
            char geographicLocation[50];
            char tobaccoUse[10];
            char coverageLevel[20];
            int familySize;
            char healthStatus[20];
        } healthPolicy;
        struct {
            char healthHistory[100];
            char lifestyle[50];
            char occupation[50];
            char coverageLevel[20];
        } lifePolicy;
    } details;
} Policy;

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

// Global variables
User users[MAX_USERS];
int num_users = 0;
Policy policies[MAX_POLICIES];
int num_policies = 0;
CustomerRecord customers[MAX_CUSTOMERS];
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
void viewPolicies(int customer_id);
void handleAdminMenu(int userIndex);
void handleAgentMenu(int userIndex);
void handleCustomerMenu(int userIndex);

void scanCarPolicyDetails(Policy *policy);
void scanHomePolicyDetails(Policy *policy);
void scanHealthPolicyDetails(Policy *policy);
void scanLifePolicyDetails(Policy *policy);

void saveUsersToCSV(FILE *file);
void savePoliciesToCSV(FILE *file);
void saveCustomersToCSV(FILE *file);
void saveClaimsToCSV(FILE *file);
void loadUsersFromCSV(FILE *file);
void loadPoliciesFromCSV(FILE *file);
void loadCustomersFromCSV(FILE *file);
void loadClaimsFromCSV(FILE *file);
typedef struct {
    char name[MAX_NAME_LENGTH];
    int age_1;
    char address[MAX_ADDRESS_LENGTH];
    char gender;
    char insuranceType[20];
    double cost;
    double premium;
    int premiumPeriod; // in months
    struct tm startDate;
    struct tm endDate;
    int extraCoverage_1s[MAX_COVERAGE_1_OPTIONS];
    int numExtraCoverage_1s;
} Insurance;

// Global variables to track the company's financials
double totalIncome = 0.0;
double totalExpenses = 0.0;

// Expense rates per insurance type
double homeInsuranceExpense = 1000.0;
double carInsuranceExpense = 800.0;
double lifeInsuranceExpense = 500.0;
double healthInsuranceExpense = 700.0;

// Additional expenses
double taxes = 500.0;
double payroll = 2000.0;
double utilities = 300.0;
double lostProfits = 1000.0;
double advertising = 400.0;
double rent = 1500.0;

double calculatePremium(double cost, int premiumPeriod, int numExtraCoverage_1s) {
    double extraCoverage_1Cost = 50.0 * numExtraCoverage_1s;
    return (cost + extraCoverage_1Cost) / premiumPeriod;
}

void calculateEndDate(struct tm *startDate, int premiumPeriod, struct tm *endDate) {
    *endDate = *startDate;
    endDate->tm_mon += premiumPeriod;
    mktime(endDate); // Normalize the time structure
}

void printInstallmentSchedule(struct tm startDate, int premiumPeriod, double premium) {
    struct tm paymentDate = startDate;
    for (int i = 0; i < premiumPeriod; ++i) {
        paymentDate.tm_mon += 1;
        mktime(&paymentDate);
        printf("Installment %d: %02d-%02d-%d Amount: $%.2f\n", i + 1, paymentDate.tm_mday, paymentDate.tm_mon + 1, paymentDate.tm_year + 1900, premium);
    }
}

void updateTotalIncomeAndExpenses(Insurance *insurance) {
    totalIncome += (insurance->premium * insurance->premiumPeriod);
    if (strcmp(insurance->insuranceType, "home") == 0) {
        totalExpenses += homeInsuranceExpense;
    } else if (strcmp(insurance->insuranceType, "car") == 0) {
        totalExpenses += carInsuranceExpense;
    } else if (strcmp(insurance->insuranceType, "life") == 0) {
        totalExpenses += lifeInsuranceExpense;
    } else if (strcmp(insurance->insuranceType, "health") == 0) {
        totalExpenses += healthInsuranceExpense;
    }
    totalExpenses += taxes + payroll + utilities + lostProfits + advertising + rent;
}

double calculateNetProfit() {
    return totalIncome - totalExpenses;
}

void inputInsuranceDetails(Insurance *insurance) {
    printf("Enter name: ");
    fgets(insurance->name, MAX_NAME_LENGTH, stdin);
    insurance->name[strcspn(insurance->name, "\n")] = '\0'; // Remove newline character

    printf("Enter age_1: ");
    scanf("%d", &insurance->age_1);

    printf("Enter address: ");
    getchar(); // To consume leftover newline character
    fgets(insurance->address, MAX_ADDRESS_LENGTH, stdin);
    insurance->address[strcspn(insurance->address, "\n")] = '\0'; // Remove newline character

    printf("Enter gender (M/F): ");
    scanf(" %c", &insurance->gender);

    printf("Enter insurance type (home/car/life/health): ");
    scanf("%s", insurance->insuranceType);

    printf("Enter cost: ");
    scanf("%lf", &insurance->cost);

    printf("Enter premium period (months): ");
    scanf("%d", &insurance->premiumPeriod);

    printf("Enter number of extra coverage_1s: ");
    scanf("%d", &insurance->numExtraCoverage_1s);

    for (int i = 0; i < insurance->numExtraCoverage_1s; ++i) {
        printf("Enter extra coverage_1 %d: ", i + 1);
        scanf("%d", &insurance->extraCoverage_1s[i]);
    }

    printf("Enter start date (dd mm yyyy): ");
    int day, month, year;
    scanf("%d %d %d", &day, &month, &year);
    insurance->startDate.tm_mday = day;
    insurance->startDate.tm_mon = month - 1;
    insurance->startDate.tm_year = year - 1900;
    insurance->startDate.tm_hour = 0;
    insurance->startDate.tm_min = 0;
    insurance->startDate.tm_sec = 0;
    mktime(&insurance->startDate);

    insurance->premium = calculatePremium(insurance->cost, insurance->premiumPeriod, insurance->numExtraCoverage_1s);
    calculateEndDate(&insurance->startDate, insurance->premiumPeriod, &insurance->endDate);

    // Update the company's financials
    updateTotalIncomeAndExpenses(insurance);
}

void printInsuranceDetails(Insurance insurance) {
    printf("\nInsurance Details:\n");
    printf("Name: %s\n", insurance.name);
    printf("age_1: %d\n", insurance.age_1);
    printf("Address: %s\n", insurance.address);
    printf("Gender: %c\n", insurance.gender);
    printf("Insurance Type: %s\n", insurance.insuranceType);
    printf("Cost: $%.2f\n", insurance.cost);
    printf("Premium: $%.2f\n", insurance.premium);
    printf("Premium Period: %d months\n", insurance.premiumPeriod);
    printf("Start Date: %02d-%02d-%d\n", insurance.startDate.tm_mday, insurance.startDate.tm_mon + 1, insurance.startDate.tm_year + 1900);
    printf("End Date: %02d-%02d-%d\n", insurance.endDate.tm_mday, insurance.endDate.tm_mon + 1, insurance.endDate.tm_year + 1900);
    printf("Extra Coverage_1s: ");
    for (int i = 0; i < insurance.numExtraCoverage_1s; ++i) {
        printf("%d ", insurance.extraCoverage_1s[i]);
    }
    printf("\n");
    printInstallmentSchedule(insurance.startDate, insurance.premiumPeriod, insurance.premium);
}
void run(){

Insurance insurance;
    inputInsuranceDetails(&insurance);
    printInsuranceDetails(insurance);

    printf("\nCompany Financials:\n");
    printf("Total Income: $%.2f\n", totalIncome);
    printf("Total Expenses: $%.2f\n", totalExpenses);
    printf("Net Profit: $%.2f\n", calculateNetProfit());

}
int main() {
    loadData();
strcpy(users[num_users].username,"radwa");
    strcpy(users[num_users].password,"1234");
    strcpy(users[num_users].role,"admin");
    num_users++;
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
//
void createPolicy() {
    if (num_policies >= MAX_POLICIES) {
        printf("Cannot create more policies.\n");
        return;
    }

    Policy new_policy;
    new_policy.policy_id = num_policies + 1;
    printf("Select policy type:\n");
    printf("1. Car\n");
    printf("2. Home\n");
    printf("3. Health\n");
    printf("4. Life\n");
    int policyType;
    scanf("%d", &policyType);

    switch(policyType) {
        case 1:
            strcpy(new_policy.type, "car");
            scanCarPolicyDetails(&new_policy);
            break;
        case 2:
            strcpy(new_policy.type, "home");
            scanHomePolicyDetails(&new_policy);
            break;
        case 3:
            strcpy(new_policy.type, "health");
            scanHealthPolicyDetails(&new_policy);
            break;
        case 4:
            strcpy(new_policy.type, "life");
            scanLifePolicyDetails(&new_policy);
            break;
        default:
            printf("Invalid policy type.\n");
            return;
    }

    policies[num_policies] = new_policy;
    num_policies++;
    printf("Policy created successfully.\n");
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

void generateReport() {
    printf("Generating report...\n");

    int totalPolicies = num_policies;
    int totalCustomers = num_customers;
    int totalClaims = num_claims;
    int pendingClaims = 0;

    for (int i = 0; i < num_claims; i++) {
        if (strcmp(claims[i].status, "Pending") == 0) {
            pendingClaims++;
        }
    }

    printf("Total Policies: %d\n", totalPolicies);
    printf("Total Customers: %d\n", totalCustomers);
    printf("Total Claims: %d\n", totalClaims);
    printf("Pending Claims: %d\n", pendingClaims);
}

void changePassword(int userIndex) {
    char newPassword[50];
    printf("Enter new password: ");
    scanf("%s", newPassword);
    strcpy(users[userIndex].password, newPassword);
    printf("Password changed successfully.\n");
}

void saveData() {
    FILE *file;

    file = fopen("users.csv", "w");
    saveUsersToCSV(file);
    fclose(file);

    file = fopen("policies.csv", "w");
    savePoliciesToCSV(file);
    fclose(file);

    file = fopen("customers.csv", "w");
    saveCustomersToCSV(file);
    fclose(file);

    file = fopen("claims.csv", "w");
    saveClaimsToCSV(file);
    fclose(file);
}

void loadData() {
    FILE *file;

    file = fopen("users.csv", "r");
    if (file) {
        loadUsersFromCSV(file);
        fclose(file);
    }

    file = fopen("policies.csv", "r");
    if (file) {
        loadPoliciesFromCSV(file);
        fclose(file);
    }

    file = fopen("customers.csv", "r");
    if (file) {
        loadCustomersFromCSV(file);
        fclose(file);
    }

    file = fopen("claims.csv", "r");
    if (file) {
        loadClaimsFromCSV(file);
        fclose(file);
    }
}

void viewPolicies(int customer_id) {
    printf("Policies for customer ID %d:\n", customer_id);
    for (int i = 0; i < num_policies; i++) {
        for (int j = 0; j < customers[customer_id - 1].num_policies; j++) {
            if (policies[i].policy_id == customers[customer_id - 1].policy_ids[j]) {
                printf("Policy ID: %d\n", policies[i].policy_id);
                printf("Type: %s\n", policies[i].type);
                if (strcmp(policies[i].type, "car") == 0) {
                    printf("Vehicle Type: %s\n", policies[i].details.carPolicy.vehicleType);
                    printf("Location: %s\n", policies[i].details.carPolicy.location);
                    printf("Usage: %s\n", policies[i].details.carPolicy.usage);
                    printf("Coverage Level: %s\n\n", policies[i].details.carPolicy.coverageLevel);
                } else if (strcmp(policies[i].type, "home") == 0) {
                    printf("Home Value: %.2f\n", policies[i].details.homePolicy.homeValue);
                    printf("Rebuilding Cost: %.2f\n", policies[i].details.homePolicy.rebuildingCost);
                    printf("Location: %s\n", policies[i].details.homePolicy.location);
                    printf("Home Age: %d\n", policies[i].details.homePolicy.homeAge);
                    printf("Condition: %s\n", policies[i].details.homePolicy.condition);
                    printf("Construction Materials: %s\n", policies[i].details.homePolicy.constructionMaterials);
                    printf("Coverage Level: %s\n\n", policies[i].details.homePolicy.coverageLevel);
                } else if (strcmp(policies[i].type, "health") == 0) {
                    printf("Geographic Location: %s\n", policies[i].details.healthPolicy.geographicLocation);
                    printf("Tobacco Use: %s\n", policies[i].details.healthPolicy.tobaccoUse);
                    printf("Coverage Level: %s\n", policies[i].details.healthPolicy.coverageLevel);
                    printf("Family Size: %d\n", policies[i].details.healthPolicy.familySize);
                    printf("Health Status: %s\n\n", policies[i].details.healthPolicy.healthStatus);
                } else if (strcmp(policies[i].type, "life") == 0) {
                    printf("Health History: %s\n", policies[i].details.lifePolicy.healthHistory);
                    printf("Lifestyle: %s\n", policies[i].details.lifePolicy.lifestyle);
                    printf("Occupation: %s\n", policies[i].details.lifePolicy.occupation);
                    printf("Coverage Level: %s\n\n", policies[i].details.lifePolicy.coverageLevel);
                }
            }
        }
    }
}

void scanCarPolicyDetails(Policy *policy) {
    printf("Enter vehicle type: ");
    scanf("%s", policy->details.carPolicy.vehicleType);
    printf("Enter location: ");
    scanf("%s", policy->details.carPolicy.location);
    printf("Enter usage: ");
    scanf("%s", policy->details.carPolicy.usage);
    printf("Enter coverage level: ");
    scanf("%s", policy->details.carPolicy.coverageLevel);
}

void scanHomePolicyDetails(Policy *policy) {
    printf("Enter home value: ");
    scanf("%lf", &policy->details.homePolicy.homeValue);
    printf("Enter rebuilding cost: ");
    scanf("%lf", &policy->details.homePolicy.rebuildingCost);
    printf("Enter location: ");
    scanf("%s", policy->details.homePolicy.location);
    printf("Enter home age: ");
    scanf("%d", &policy->details.homePolicy.homeAge);
    printf("Enter condition: ");
    scanf("%s", policy->details.homePolicy.condition);
    printf("Enter construction materials: ");
    scanf("%s", policy->details.homePolicy.constructionMaterials);
    printf("Enter coverage level: ");
    scanf("%s", policy->details.homePolicy.coverageLevel);
}

void scanHealthPolicyDetails(Policy *policy) {
    printf("Enter geographic location: ");
    scanf("%s", policy->details.healthPolicy.geographicLocation);
    printf("Enter tobacco use (yes/no): ");
    scanf("%s", policy->details.healthPolicy.tobaccoUse);
    printf("Enter coverage level: ");
    scanf("%s", policy->details.healthPolicy.coverageLevel);
    printf("Enter family size: ");
    scanf("%d", &policy->details.healthPolicy.familySize);
    printf("Enter health status: ");
    scanf("%s", policy->details.healthPolicy.healthStatus);
}

void scanLifePolicyDetails(Policy *policy) {
    printf("Enter health history: ");
    scanf("%s", policy->details.lifePolicy.healthHistory);
    printf("Enter lifestyle: ");
    scanf("%s", policy->details.lifePolicy.lifestyle);
    printf("Enter occupation: ");
    scanf("%s", policy->details.lifePolicy.occupation);
    printf("Enter coverage level: ");
    scanf("%s", policy->details.lifePolicy.coverageLevel);
}

void saveUsersToCSV(FILE *file) {
    fprintf(file, "Username,Password,Role\n");
    for (int i = 0; i < num_users; i++) {
        fprintf(file, "%s,%s,%s\n", users[i].username, users[i].password, users[i].role);
    }
}

void savePoliciesToCSV(FILE *file) {
    fprintf(file, "PolicyID,Type,Details\n");
    for (int i = 0; i < num_policies; i++) {
        if (strcmp(policies[i].type, "car") == 0) {
            fprintf(file, "%d,%s,%s,%s,%s,%s\n", policies[i].policy_id, policies[i].type,
                    policies[i].details.carPolicy.vehicleType, policies[i].details.carPolicy.location,
                    policies[i].details.carPolicy.usage, policies[i].details.carPolicy.coverageLevel);
        } else if (strcmp(policies[i].type, "home") == 0) {
            fprintf(file, "%d,%s,%.2f,%.2f,%s,%d,%s,%s,%s\n", policies[i].policy_id, policies[i].type,
                    policies[i].details.homePolicy.homeValue, policies[i].details.homePolicy.rebuildingCost,
                    policies[i].details.homePolicy.location, policies[i].details.homePolicy.homeAge,
                    policies[i].details.homePolicy.condition, policies[i].details.homePolicy.constructionMaterials,
                    policies[i].details.homePolicy.coverageLevel);
        } else if (strcmp(policies[i].type, "health") == 0) {
            fprintf(file, "%d,%s,%s,%s,%s,%d,%s\n", policies[i].policy_id, policies[i].type,
                    policies[i].details.healthPolicy.geographicLocation, policies[i].details.healthPolicy.tobaccoUse,
                    policies[i].details.healthPolicy.coverageLevel, policies[i].details.healthPolicy.familySize,
                    policies[i].details.healthPolicy.healthStatus);
        } else if (strcmp(policies[i].type, "life") == 0) {
            fprintf(file, "%d,%s,%s,%s,%s,%s\n", policies[i].policy_id, policies[i].type,
                    policies[i].details.lifePolicy.healthHistory, policies[i].details.lifePolicy.lifestyle,
                    policies[i].details.lifePolicy.occupation, policies[i].details.lifePolicy.coverageLevel);
        }
    }
}

void saveCustomersToCSV(FILE *file) {
    fprintf(file, "CustomerID,Name,ContactInfo,NumPolicies,PolicyIDs\n");
    for (int i = 0; i < num_customers; i++) {
        fprintf(file, "%d,%s,%s,%d", customers[i].customer_id, customers[i].name, customers[i].contact_info, customers[i].num_policies);
        for (int j = 0; j < customers[i].num_policies; j++) {
            fprintf(file, ",%d", customers[i].policy_ids[j]);
        }
        fprintf(file, "\n");
    }
}

void saveClaimsToCSV(FILE *file) {
    fprintf(file, "ClaimID,CustomerID,Type,Date,Description,Status\n");
    for (int i = 0; i < num_claims; i++) {
        fprintf(file, "%d,%d,%s,%s,%s,%s\n", claims[i].claim_id, claims[i].customer_id, claims[i].type,
                claims[i].date, claims[i].description, claims[i].status);
    }
}

void loadUsersFromCSV(FILE *file) {
    char line[256];
    num_users = 0;
    fgets(line, sizeof(line), file); // Skip header line
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%s", users[num_users].username, users[num_users].password, users[num_users].role);
        num_users++;
    }
}

void loadPoliciesFromCSV(FILE *file) {
    char line[256];
    num_policies = 0;
    fgets(line, sizeof(line), file); // Skip header line
    while (fgets(line, sizeof(line), file)) {
        char type[20];
        sscanf(line, "%d,%[^,]", &policies[num_policies].policy_id, type);
        strcpy(policies[num_policies].type, type);

        if (strcmp(type, "car") == 0) {
            sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%s",
                   policies[num_policies].details.carPolicy.vehicleType,
                   policies[num_policies].details.carPolicy.location,
                   policies[num_policies].details.carPolicy.usage,
                   policies[num_policies].details.carPolicy.coverageLevel);
        } else if (strcmp(type, "home") == 0) {
            sscanf(line, "%d,%[^,],%lf,%lf,%[^,],%d,%[^,],%[^,],%s",
                   &policies[num_policies].details.homePolicy.homeValue,
                   &policies[num_policies].details.homePolicy.rebuildingCost,
                   policies[num_policies].details.homePolicy.location,
                   &policies[num_policies].details.homePolicy.homeAge,
                   policies[num_policies].details.homePolicy.condition,
                   policies[num_policies].details.homePolicy.constructionMaterials,
                   policies[num_policies].details.homePolicy.coverageLevel);
        } else if (strcmp(type, "health") == 0) {
            sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%s",
                   policies[num_policies].details.healthPolicy.geographicLocation,
                   policies[num_policies].details.healthPolicy.tobaccoUse,
                   policies[num_policies].details.healthPolicy.coverageLevel,
                   &policies[num_policies].details.healthPolicy.familySize,
                   policies[num_policies].details.healthPolicy.healthStatus);
        } else if (strcmp(type, "life") == 0) {
            sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%s",
                   policies[num_policies].details.lifePolicy.healthHistory,
                   policies[num_policies].details.lifePolicy.lifestyle,
                   policies[num_policies].details.lifePolicy.occupation,
                   policies[num_policies].details.lifePolicy.coverageLevel);
        }

        num_policies++;
    }
}

void loadCustomersFromCSV(FILE *file) {
    char line[256];
    num_customers = 0;
    fgets(line, sizeof(line), file); // Skip header line
    while (fgets(line, sizeof(line), file)) {
        int num_policies;
        sscanf(line, "%d,%[^,],%[^,],%d",
               &customers[num_customers].customer_id,
               customers[num_customers].name,
               customers[num_customers].contact_info,
               &num_policies);

        customers[num_customers].num_policies = num_policies;
        char *token = strtok(line, ",");
        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, ",");
        }

        for (int i = 0; i < num_policies; i++) {
            customers[num_customers].policy_ids[i] = atoi(token);
            token = strtok(NULL, ",");
        }

        num_customers++;
    }
}

void loadClaimsFromCSV(FILE *file) {
    char line[256];
    num_claims = 0;
    fgets(line, sizeof(line), file); // Skip header line
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%d,%[^,],%[^,],%[^,],%s", &claims[num_claims].claim_id, &claims[num_claims].customer_id,
               claims[num_claims].type, claims[num_claims].date, claims[num_claims].description, claims[num_claims].status);
        num_claims++;
 }
}
