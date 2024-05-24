#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define constants
#define MAX_USERS 100
#define MAX_POLICIES 100
#define MAX_CUSTOMERS 100
#define MAX_CLAIMS 100
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 200
#define MAX_COVERAGE_1_OPTIONS 10

// Define structures
typedef struct {
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
    char role[MAX_NAME_LENGTH];
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
            char healthStatus[50];
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

// Function prototypes
int authenticate(User users[], int num_users);
void handleAdminMenu(User users[], int userIndex);
void handleAgentMenu(User users[], int userIndex);
void handleCustomerMenu(User users[], int userIndex);
void registerUser(User users[], int *num_users);
void changePassword(User users[], int userIndex);
// Other function prototypes...

// Global variables
User users[MAX_USERS];
int num_users = 0;


// Global variables
User users[MAX_USERS];
int num_users = 0;
Policy policies[MAX_POLICIES];
int num_policies = 0;
CustomerRecord customers[MAX_CUSTOMERS];
int num_customers = 0;

Claim claims[MAX_CLAIMS];
int num_claims = 0;

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

// Function prototypes
void run();
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

double calculatePremium(double cost, int premiumPeriod, int numExtraCoverage_1s);
void calculateEndDate(struct tm *startDate, int premiumPeriod, struct tm *endDate);
void printInstallmentSchedule(struct tm startDate, int premiumPeriod, double premium);
void updateTotalIncomeAndExpenses(Insurance *insurance);
double calculateNetProfit();
void inputInsuranceDetails(Insurance *insurance);
void printInsuranceDetails(Insurance insurance);

void generateCSVReport(int reportType);
void generateHTMLReport(int reportType);

void login() {
    char username[50];
    char password[50];
    printf("Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    int i;
    for (i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful.\n");
            if (strcmp(users[i].role, "admin") == 0) {
                handleAdminMenu(i);
            } else if (strcmp(users[i].role, "agent") == 0) {
                handleAgentMenu(i);
            } else if (strcmp(users[i].role, "customer") == 0) {
                handleCustomerMenu(i);
            }
            return;
        }
    }
    printf("Login failed. Invalid username or password.\n");
}

void createPolicy() {
    printf("Enter policy details:\n");
    printf("Type (car/home/health/life): ");
    char type[20];
    scanf("%s", type);
    strcpy(policies[num_policies].type, type);
    policies[num_policies].policy_id = num_policies + 1;
    if (strcmp(type, "car") == 0) {
        scanCarPolicyDetails(&policies[num_policies]);
    } else if (strcmp(type, "home") == 0) {
        scanHomePolicyDetails(&policies[num_policies]);
    } else if (strcmp(type, "health") == 0) {
        scanHealthPolicyDetails(&policies[num_policies]);
    } else if (strcmp(type, "life") == 0) {
        scanLifePolicyDetails(&policies[num_policies]);
    }
    num_policies++;
}

void addCustomer() {
    printf("Enter customer details:\n");
    printf("Name: ");
    char name[100];
    scanf("%s", name);
    strcpy(customers[num_customers].name, name);
    printf("Contact Info: ");
    char contact_info[100];
    scanf("%s", contact_info);
    strcpy(customers[num_customers].contact_info, contact_info);
    printf("Number of policies: ");
    int num_policies;
    scanf("%d", &num_policies);
    customers[num_customers].num_policies = num_policies;
    printf("Enter policy ids:\n");
    for (int i = 0; i < num_policies; i++) {
        scanf("%d", &customers[num_customers].policy_ids[i]);
    }
    num_customers++;
}

void initiateClaim() {
    printf("Enter claim details:\n");
    printf("Customer ID: ");
    int customer_id;
    scanf("%d", &customer_id);
    claims[num_claims].customer_id = customer_id;
    printf("Type: ");
    char type[50];
    scanf("%s", type);
    strcpy(claims[num_claims].type, type);
    printf("Date: ");
    char date[20];
    scanf("%s", date);
    strcpy(claims[num_claims].date, date);
    printf("Description: ");
    char description[200];
    scanf("%s", description);
    strcpy(claims[num_claims].description, description);
    strcpy(claims[num_claims].status, "pending");
    num_claims++;
}

void viewClaims() {
    printf("Claims:\n");
    for (int i = 0; i < num_claims; i++) {
        printf("Claim ID: %d\n", claims[i].claim_id);
        printf("Customer ID: %d\n", claims[i].customer_id);
        printf("Type: %s\n", claims[i].type);
        printf("Date: %s\n", claims[i].date);
        printf("Description: %s\n", claims[i].description);
        printf("Status: %s\n", claims[i].status);
    }
}

void generateReport() {
    printf("Choose report type:\n");
    printf("1. Customers, Agents, Policies, Premiums, Claims\n");
    printf("2. KPIs\n");
    int reportType;
    scanf("%d", &reportType);
    
    printf("Generating CSV report...\n");
    generateCSVReport(reportType);

    printf("Generating HTML report...\n");
    generateHTMLReport(reportType);
}

void changePassword(int userIndex) {
    printf("Change Password\n");
    printf("Enter new password: ");
    scanf("%s", users[userIndex].password);
    printf("Password changed successfully.\n");
}

void saveData() {
    FILE *file;
    file = fopen("data.csv", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    saveUsersToCSV(file);
    savePoliciesToCSV(file);
    saveCustomersToCSV(file);
    saveClaimsToCSV(file);
    fclose(file);
}

void loadData() {
    FILE *file;
    file = fopen("data.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    loadUsersFromCSV(file);
    loadPoliciesFromCSV(file);
    loadCustomersFromCSV(file);
    loadClaimsFromCSV(file);
    fclose(file);
}

void viewPolicies(int customer_id) {
    printf("Policies for customer ID: %d\n", customer_id);
    for (int i = 0; i < num_customers; i++) {
        if (customers[i].customer_id == customer_id) {
            for (int j = 0; j < customers[i].num_policies; j++) {
                int policy_id = customers[i].policy_ids[j];
                for (int k = 0; k < num_policies; k++) {
                    if (policies[k].policy_id == policy_id) {
                        printf("Policy ID: %d\n", policies[k].policy_id);
                        printf("Type: %s\n", policies[k].type);
                        if (strcmp(policies[k].type, "car") == 0) {
                            printf("Vehicle Type: %s\n", policies[k].details.carPolicy.vehicleType);
                            printf("Location: %s\n", policies[k].details.carPolicy.location);
                            printf("Usage: %s\n", policies[k].details.carPolicy.usage);
                            printf("Coverage Level: %s\n", policies[k].details.carPolicy.coverageLevel);
                        } else if (strcmp(policies[k].type, "home") == 0) {
                            printf("Home Value: %.2f\n", policies[k].details.homePolicy.homeValue);
                            printf("Rebuilding Cost: %.2f\n", policies[k].details.homePolicy.rebuildingCost);
                            printf("Location: %s\n", policies[k].details.homePolicy.location);
                            printf("Home Age: %d\n", policies[k].details.homePolicy.homeAge);
                            printf("Condition: %s\n", policies[k].details.homePolicy.condition);
                            printf("Construction Materials: %s\n", policies[k].details.homePolicy.constructionMaterials);
                            printf("Coverage Level: %s\n", policies[k].details.homePolicy.coverageLevel);
                        } else if (strcmp(policies[k].type, "health") == 0) {
                            printf("Geographic Location: %s\n", policies[k].details.healthPolicy.geographicLocation);
                            printf("Tobacco Use: %s\n", policies[k].details.healthPolicy.tobaccoUse);
                            printf("Coverage Level: %s\n", policies[k].details.healthPolicy.coverageLevel);
                            printf("Family Size: %d\n", policies[k].details.healthPolicy.familySize);
                            printf("Health Status: %s\n", policies[k].details.healthPolicy.healthStatus);
                        } else if (strcmp(policies[k].type, "life") == 0) {
                            printf("Health History: %s\n", policies[k].details.lifePolicy.healthHistory);
                            printf("Lifestyle: %s\n", policies[k].details.lifePolicy.lifestyle);
                            printf("Occupation: %s\n", policies[k].details.lifePolicy.occupation);
                            printf("Coverage Level: %s\n", policies[k].details.lifePolicy.coverageLevel);
                        }
                    }
                }
            }
        }
    }
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
        printf("8. Save Data\n");
        printf("9. Load Data\n");
        printf("10. Logout\n");
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
                saveData();
                break;
            case 9:
                loadData();
                break;
            case 10:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 10);
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
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

void handleCustomerMenu(int userIndex) {
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
                viewPolicies(userIndex);
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
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
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
    printf("Enter tobacco use: ");
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
    fprintf(file, "username,password,role\n");
    for (int i = 0; i < num_users; i++) {
        fprintf(file, "%s,%s,%s\n", users[i].username, users[i].password, users[i].role);
    }
}

void savePoliciesToCSV(FILE *file) {
    fprintf(file, "policy_id,type,details\n");
    for (int i = 0; i < num_policies; i++) {
        fprintf(file, "%d,%s,", policies[i].policy_id, policies[i].type);
        if (strcmp(policies[i].type, "car") == 0) {
            fprintf(file, "%s,%s,%s,%s\n", policies[i].details.carPolicy.vehicleType, policies[i].details.carPolicy.location, policies[i].details.carPolicy.usage, policies[i].details.carPolicy.coverageLevel);
        } else if (strcmp(policies[i].type, "home") == 0) {
            fprintf(file, "%.2f,%.2f,%s,%d,%s,%s,%s\n", policies[i].details.homePolicy.homeValue, policies[i].details.homePolicy.rebuildingCost, policies[i].details.homePolicy.location, policies[i].details.homePolicy.homeAge, policies[i].details.homePolicy.condition, policies[i].details.homePolicy.constructionMaterials, policies[i].details.homePolicy.coverageLevel);
        } else if (strcmp(policies[i].type, "health") == 0) {
            fprintf(file, "%s,%s,%s,%d,%s\n", policies[i].details.healthPolicy.geographicLocation, policies[i].details.healthPolicy.tobaccoUse, policies[i].details.healthPolicy.coverageLevel, policies[i].details.healthPolicy.familySize, policies[i].details.healthPolicy.healthStatus);
        } else if (strcmp(policies[i].type, "life") == 0) {
            fprintf(file, "%s,%s,%s,%s\n", policies[i].details.lifePolicy.healthHistory, policies[i].details.lifePolicy.lifestyle, policies[i].details.lifePolicy.occupation, policies[i].details.lifePolicy.coverageLevel);
        }
    }
}

void saveCustomersToCSV(FILE *file) {
    fprintf(file, "customer_id,first_name,last_name,email,phone,num_policies,policy_ids\n");
    for (int i = 0; i < num_customers; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%d,", customers[i].customer_id, customers[i].first_name, customers[i].last_name, customers[i].email, customers[i].phone, customers[i].num_policies);
        for (int j = 0; j < customers[i].num_policies; j++) {
            fprintf(file, "%d", customers[i].policy_ids[j]);
            if (j < customers[i].num_policies - 1) {
                fprintf(file, ";");
            }
        }
        fprintf(file, "\n");
    }
}



void saveData() {
    FILE *file = fopen("insurance_data.csv", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    saveUsersToCSV(file);
    savePoliciesToCSV(file);
    saveCustomersToCSV(file);
    saveClaimsToCSV(file);
    fclose(file);
    printf("Data saved successfully.\n");
}

void loadUsersFromCSV(FILE *file) {
    char line[256];
    fgets(line, sizeof(line), file); // Skip header line
    num_users = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        strcpy(users[num_users].username, token);
        token = strtok(NULL, ",");
        strcpy(users[num_users].password, token);
        token = strtok(NULL, ",");
        strcpy(users[num_users].role, token);
        num_users++;
    }
}




int main() {
    // Example data for testing
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "adminpass");
    strcpy(users[0].role, "admin");
    num_users = 1;

    int userIndex = authenticate();
    if (userIndex == -1) {
        printf("Authentication failed.\n");
        return 1;
    }

    if (strcmp(users[userIndex].role, "admin") == 0) {
        handleAdminMenu(userIndex);
    } else if (strcmp(users[userIndex].role, "agent") == 0) {
        handleAgentMenu(userIndex);
    } else if (strcmp(users[userIndex].role, "customer") == 0) {
        handleCustomerMenu(userIndex);
    } else {
        printf("Unknown role: %s\n", users[userIndex].role);
    }

    return 0;
}
