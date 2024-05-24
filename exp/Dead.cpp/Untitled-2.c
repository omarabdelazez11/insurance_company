#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_POLICY_TYPE 50
#define MAX_PERIOD_LENGTH 20

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    char gender[10];
    char occupation[50];
    char contactInfo[100];
    char previousInsurance[100];
} Customer;

typedef struct {
    Customer customer;
    char policyType[MAX_POLICY_TYPE];
    double coverageAmount;
    double premium;
    int duration;  // Duration in years
    char period[MAX_PERIOD_LENGTH];  // Payment period (e.g., monthly, annually)
    double claimsCost;
    double operatingExpenses;
    double profit;
} InsurancePolicy;

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
    getInput("Enter payment period (e.g., monthly, annually): ", policy->period, MAX_PERIOD_LENGTH);

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

int main() {
    InsurancePolicy policy;
    getPolicyDetails(&policy);
    savePolicyToCSV(&policy);
    writeFormalContract(&policy);

    return 0;
}

