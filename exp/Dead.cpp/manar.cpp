#include <stdio.h>
#include <string.h>

// Define structure for customer details
struct Customer {
    int age;
    char gender[10];
    char occupation[50];
    char contactInfo[100];
    char previousInsurance[100];
};

// Define structure for car insurance policy
struct CarPolicy {
    struct Customer customer;
    char vehicleType[20];
    char location[50];
    char usage[20];
    char coverageLevel[20];
};

// Define structure for home insurance policy
struct HomePolicy {
    struct Customer customer;
    double homeValue;
    double rebuildingCost;
    char location[50];
    int homeAge;
    char condition[20];
    char constructionMaterials[20];
    char coverageLevel[20];
};

// Define structure for health insurance policy
struct HealthPolicy {
    struct Customer customer;
    char geographicLocation[50];
    char tobaccoUse[10];
    char coverageLevel[20];
    int familySize;
    char healthStatus[20];
};

// Define structure for life insurance policy
struct LifePolicy {
    struct Customer customer;
    char healthHistory[100];
    char lifestyle[50];
    char occupation[50];
    char coverageLevel[20];
};

// Function to scan customer details
void scanCustomerDetails(struct Customer *customer) {
    printf("Enter customer's age: ");
    scanf("%d", &customer->age);

    printf("Enter customer's gender (male, female, other): ");
    scanf("%s", customer->gender);

    printf("Enter customer's occupation: ");
    scanf(" %[^\n]%*c", customer->occupation);

    printf("Enter customer's contact information: ");
    scanf(" %[^\n]%*c", customer->contactInfo);

    printf("Enter any previous insurance policies: ");
    scanf(" %[^\n]%*c", customer->previousInsurance);
}

// Function to scan car policy details and calculate premium
void scanCarPolicyDetails(struct CarPolicy *policy) {
    scanCustomerDetails(&policy->customer);

    printf("Enter vehicle type (e.g., sedan, SUV, truck): ");
    scanf("%s", policy->vehicleType);

    printf("Enter location (e.g., urban, rural): ");
    scanf("%s", policy->location);

    printf("Enter usage (personal, commuting): ");
    scanf("%s", policy->usage);

    printf("Enter coverage level (basic, standard, premium): ");
    scanf("%s", policy->coverageLevel);

    // Calculate premium
    int premium = 500; // Base premium
    if (policy->customer.age < 25) {
        premium += 200;
    }
    premium += 150; // Placeholder for driving history factor
    if (strcmp(policy->vehicleType, "sports car") == 0) {
        premium += 300;
    }
    if (strcmp(policy->location, "urban") == 0) {
        premium += 100;
    }
    if (strcmp(policy->usage, "commuting") == 0) {
        premium += 50;
    }
    premium += 50; // Placeholder for credit score factor

    printf("Car Insurance Policy created successfully!\n");
    printf("Total Premium: $%d\n", premium);
}

// Function to scan home policy details and calculate premium
void scanHomePolicyDetails(struct HomePolicy *policy) {
    scanCustomerDetails(&policy->customer);

    printf("Enter home value: ");
    scanf("%lf", &policy->homeValue);

    printf("Enter rebuilding cost: ");
    scanf("%lf", &policy->rebuildingCost);

    printf("Enter location (e.g., urban, rural, natural disaster-prone): ");
    scanf("%s", policy->location);

    printf("Enter home age (in years): ");
    scanf("%d", &policy->homeAge);

    printf("Enter condition of the home (new, good, fair, poor): ");
    scanf("%s", policy->condition);

    printf("Enter construction materials (e.g., brick, wood, fire-resistant): ");
    scanf("%s", policy->constructionMaterials);

    printf("Enter coverage level (basic, standard, premium): ");
    scanf("%s", policy->coverageLevel);

    // Calculate premium
    int premium = 700; // Base premium
    if (policy->rebuildingCost > 300000) {
        premium += 300;
    }
    if (strcmp(policy->location, "natural disaster-prone") == 0) {
        premium += 250;
    }
    if (policy->homeAge > 30) {
        premium += 100;
    }
    if (strcmp(policy->constructionMaterials, "fire-resistant") == 0) {
        premium -= 50;
    }
    premium -= 100; // Placeholder for security systems factor
    premium += 200; // Placeholder for coverage level factor

    printf("Home Insurance Policy created successfully!\n");
    printf("Total Premium: $%d\n", premium);
}

// Function to scan health policy details and calculate premium
void scanHealthPolicyDetails(struct HealthPolicy *policy) {
    scanCustomerDetails(&policy->customer);

    printf("Enter geographic location: ");
    scanf("%s", policy->geographicLocation);

    printf("Enter tobacco use (yes, no): ");
    scanf("%s", policy->tobaccoUse);

    printf("Enter coverage level (basic, standard, premium): ");
    scanf("%s", policy->coverageLevel);

    printf("Enter family size: ");
    scanf("%d", &policy->familySize);

    printf("Enter health status (excellent, good, fair, poor): ");
    scanf("%s", policy->healthStatus);

    // Calculate premium
    int premium = 300; // Base premium
    if (policy->customer.age > 45) {
        premium += 150;
    }
    premium += 50; // Placeholder for higher healthcare cost region
    if (strcmp(policy->tobaccoUse, "yes") == 0) {
        premium += 200;
    }
    premium += 250; // Placeholder for plan type and coverage level factor
    if (policy->familySize > 1) {
        premium += 100;
    }
    premium += 50; // Placeholder for health status factor

    printf("Health Insurance Policy created successfully!\n");
    printf("Total Premium: $%d\n", premium);
}

// Function to scan life policy details and calculate premium
void scanLifePolicyDetails(struct LifePolicy *policy) {
    scanCustomerDetails(&policy->customer);

    printf("Enter health and medical history: ");
    scanf(" %[^\n]%*c", policy->healthHistory);

    printf("Enter lifestyle (e.g., active, sedentary, occasional smoker): ");
    scanf("%s", policy->lifestyle);

    printf("Enter occupation: ");
    scanf("%s", policy->occupation);

    printf("Enter coverage level (basic, standard, premium): ");
    scanf("%s", policy->coverageLevel);

    // Calculate premium
    int premium = 200; // Base premium
    if (policy->customer.age > 35) {
        premium += 100;
    }
    premium += 50; // Placeholder for minor health issues factor
    if (strcmp(policy->customer.gender, "female") == 0) {
        premium -= 20;
    }
    if (strcmp(policy->lifestyle, "occasional smoker") == 0) {
        premium += 50;
    }
    premium += 200; // Placeholder for higher coverage amount factor
    premium += 30; // Placeholder for family medical history factor

    printf("Life Insurance Policy created successfully!\n");
    printf("Total Premium: $%d\n", premium);
}

int main() {
    int choice;
    printf("Select the type of policy to create:\n");
    printf("1. Car Insurance\n");
    printf("2. Home Insurance\n");
    printf("3. Health Insurance\n");
    printf("4. Life Insurance\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: {
            struct CarPolicy carPolicy;
            scanCarPolicyDetails(&carPolicy);
            break;
        }
        case 2: {
            struct HomePolicy homePolicy;
            scanHomePolicyDetails(&homePolicy);
            break;
        }
        case 3: {
            struct HealthPolicy healthPolicy;
            scanHealthPolicyDetails(&healthPolicy);
            break;
        }
        case 4: {
            struct LifePolicy lifePolicy;
            scanLifePolicyDetails(&lifePolicy);
            break;
        }
        default:
            printf("Invalid choice!\n");
            break;
    }

 return 0;
}
