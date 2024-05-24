#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures
typedef struct {
    char type[20];
    int count;
} Policy;

typedef struct {
    char status[20];
} Claim;

// Global variables (sample data)
Policy policies[] = {
    {"Car", 50},
    {"Home", 30},
    {"Health", 20}
};
int num_policies = 3;

Claim claims[] = {
    {"Pending"},
    {"Approved"},
    {"Rejected"}
};
int num_claims = 3;

// Function to calculate net profit (sample implementation)
double calculateNetProfit() {
    // Sample implementation, replace with actual logic
    double income = 10000.0;
    double expenses = 5000.0;
    return income - expenses;
}

void calculateKPIs() {
    // Calculate KPIs based on data
    int totalPolicies = 0;
    for (int i = 0; i < num_policies; i++) {
        totalPolicies += policies[i].count;
    }

    int totalCustomers = 100; // Sample value
    int totalClaims = num_claims;
    double netProfit = calculateNetProfit();
    int pendingClaims = 0;
    // Calculate pending claims
    for (int i = 0; i < num_claims; i++) {
        if (strcmp(claims[i].status, "Pending") == 0) {
            pendingClaims++;
        }
    }

    // Write KPIs to CSV file
    FILE *kpiFile = fopen("kpi.csv", "w");
    if (kpiFile != NULL) {
        fprintf(kpiFile, "Metric,Value\n");
        fprintf(kpiFile, "Total Policies,%d\n", totalPolicies);
        fprintf(kpiFile, "Total Customers,%d\n", totalCustomers);
        fprintf(kpiFile, "Total Claims,%d\n", totalClaims);
        fprintf(kpiFile, "Net Profit,%.2f\n", netProfit);
        fprintf(kpiFile, "Pending Claims,%d\n", pendingClaims);
        fclose(kpiFile);
    } else {
        printf("Error: Could not create KPI file.\n");
    }
}

int main() {
    calculateKPIs();
    printf("KPIs calculated and saved to kpi.csv.\n");
    return 0;
}
