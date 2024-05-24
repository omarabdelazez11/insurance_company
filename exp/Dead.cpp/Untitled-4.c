#include <stdio.h>
/*
// Define the structure to hold insurance data
typedef struct {
    double premiumsEarned;
    double claimsPaid;
    double operatingExpenses;
    double renewedPolicies;
    double totalPoliciesAtStart;
    double netAssets;
    double netPremiumsWritten;
    double netIncome;
    double shareholdersEquity;
    double investmentIncome;
    double claimsSettled;
    double claimsReceived;
} InsuranceData;

// Function to calculate Loss Ratio
double calculateLossRatio(InsuranceData data) {
    return (data.claimsPaid / data.premiumsEarned) * 100;
}

// Function to calculate Expense Ratio
double calculateExpenseRatio(InsuranceData data) {
    return (data.operatingExpenses / data.premiumsEarned) * 100;
}

// Function to calculate Combined Ratio
double calculateCombinedRatio(InsuranceData data) {
    return calculateLossRatio(data) + calculateExpenseRatio(data);
}

// Function to calculate Retention Ratio
double calculateRetentionRatio(InsuranceData data) {
    return (data.renewedPolicies / data.totalPoliciesAtStart) * 100;
}

// Function to calculate Solvency Ratio
double calculateSolvencyRatio(InsuranceData data) {
    return (data.netAssets / data.netPremiumsWritten) * 100;
}

// Function to calculate Return on Equity (ROE)
double calculateROE(InsuranceData data) {
    return (data.netIncome / data.shareholdersEquity) * 100;
}

// Function to calculate Investment Income Ratio
double calculateInvestmentIncomeRatio(InsuranceData data) {
    return (data.investmentIncome / data.premiumsEarned) * 100;
}

// Function to calculate Claims Settlement Ratio
double calculateClaimsSettlementRatio(InsuranceData data) {
    return (data.claimsSettled / data.claimsReceived) * 100;
}

// Function to calculate Operating Profit Margin
double calculateOperatingProfitMargin(InsuranceData data) {
    double operatingProfit = data.premiumsEarned - data.claimsPaid - data.operatingExpenses;
    return (operatingProfit / data.premiumsEarned) * 100;
}

// Function to calculate Net Profit Margin
double calculateNetProfitMargin(InsuranceData data) {
    return (data.netIncome / data.premiumsEarned) * 100;
}

// Function to get input data from the user
InsuranceData getInsuranceDataFromUser() {
    InsuranceData data;
    
    printf("Enter Premiums Earned: ");
    scanf("%lf", &data.premiumsEarned);

    printf("Enter Claims Paid: ");
    scanf("%lf", &data.claimsPaid);

    printf("Enter Operating Expenses: ");
    scanf("%lf", &data.operatingExpenses);

    printf("Enter Renewed Policies: ");
    scanf("%lf", &data.renewedPolicies);

    printf("Enter Total Policies at Start: ");
    scanf("%lf", &data.totalPoliciesAtStart);

    printf("Enter Net Assets: ");
    scanf("%lf", &data.netAssets);

    printf("Enter Net Premiums Written: ");
    scanf("%lf", &data.netPremiumsWritten);

    printf("Enter Net Income: ");
    scanf("%lf", &data.netIncome);

    printf("Enter Shareholders' Equity: ");
    scanf("%lf", &data.shareholdersEquity);

    printf("Enter Investment Income: ");
    scanf("%lf", &data.investmentIncome);

    printf("Enter Claims Settled: ");
    scanf("%lf", &data.claimsSettled);

    printf("Enter Claims Received: ");
    scanf("%lf", &data.claimsReceived);

    return data;
}

int main() {
    InsuranceData data = getInsuranceDataFromUser();

    // Calculate and print KPIs
    printf("\n=== KPIs ===\n");
    printf("Loss Ratio: %.2f%%\n", calculateLossRatio(data));
    printf("Expense Ratio: %.2f%%\n", calculateExpenseRatio(data));
    printf("Combined Ratio: %.2f%%\n", calculateCombinedRatio(data));
    printf("Retention Ratio: %.2f%%\n", calculateRetentionRatio(data));
    printf("Solvency Ratio: %.2f%%\n", calculateSolvencyRatio(data));
    printf("Return on Equity (ROE): %.2f%%\n", calculateROE(data));
    printf("Investment Income Ratio: %.2f%%\n", calculateInvestmentIncomeRatio(data));
    printf("Claims Settlement Ratio: %.2f%%\n", calculateClaimsSettlementRatio(data));
    printf("Operating Profit Margin: %.2f%%\n", calculateOperatingProfitMargin(data));
    printf("Net Profit Margin: %.2f%%\n", calculateNetProfitMargin(data));

    return 0;
}*/
//////////////////////////////////////////////////////////////////////kpis
#include <stdio.h>
#include <string.h>

// Define the structure for an insurance policy
typedef struct {
    char name[20];
    int bodilyInjuryPerPerson;
    int bodilyInjuryPerAccident;
    int propertyDamage;
    int collisionCoverage;
    int comprehensiveCoverage;
    int medicalPayments;
    int uninsuredMotoristPerPerson;
    int uninsuredMotoristPerAccident;
    int personalInjuryProtection;
    int roadsideAssistance;
    int rentalCarReimbursement;
    int accidentForgiveness;
    int newCarReplacement;
    int gapInsurance;
    float safeDriverDiscount;
    float multiPolicyDiscount;
    float antiTheftDeviceDiscount;
    float goodStudentDiscount;
    float multiCarDiscount;
    float loyaltyDiscount;
} InsurancePolicy;

// Function to create a Basic insurance policy
InsurancePolicy createBasicPolicy() {
    InsurancePolicy policy;
    strcpy(policy.name, "Basic");
    policy.bodilyInjuryPerPerson = 50000;
    policy.bodilyInjuryPerAccident = 100000;
    policy.propertyDamage = 25000;
    policy.collisionCoverage = 0;
    policy.comprehensiveCoverage = 0;
    policy.medicalPayments = 0;
    policy.uninsuredMotoristPerPerson = 0;
    policy.uninsuredMotoristPerAccident = 0;
    policy.personalInjuryProtection = 0;
    policy.roadsideAssistance = 1;
    policy.rentalCarReimbursement = 0;
    policy.accidentForgiveness = 0;
    policy.newCarReplacement = 0;
    policy.gapInsurance = 0;
    policy.safeDriverDiscount = 5.0;
    policy.multiPolicyDiscount = 5.0;
    policy.antiTheftDeviceDiscount = 0.0;
    policy.goodStudentDiscount = 0.0;
    policy.multiCarDiscount = 0.0;
    policy.loyaltyDiscount = 0.0;
    return policy;
}

// Function to create a Premium insurance policy
InsurancePolicy createPremiumPolicy() {
    InsurancePolicy policy;
    strcpy(policy.name, "Premium");
    policy.bodilyInjuryPerPerson = 100000;
    policy.bodilyInjuryPerAccident = 300000;
    policy.propertyDamage = 50000;
    policy.collisionCoverage = 1;
    policy.comprehensiveCoverage = 1;
    policy.medicalPayments = 5000;
    policy.uninsuredMotoristPerPerson = 0;
    policy.uninsuredMotoristPerAccident = 0;
    policy.personalInjuryProtection = 0;
    policy.roadsideAssistance = 1;
    policy.rentalCarReimbursement = 30;
    policy.accidentForgiveness = 0;
    policy.newCarReplacement = 0;
    policy.gapInsurance = 0;
    policy.safeDriverDiscount = 10.0;
    policy.multiPolicyDiscount = 10.0;
    policy.antiTheftDeviceDiscount = 5.0;
    policy.goodStudentDiscount = 5.0;
    policy.multiCarDiscount = 0.0;
    policy.loyaltyDiscount = 0.0;
    return policy;
}

// Function to create a Platinum insurance policy
InsurancePolicy createPlatinumPolicy() {
    InsurancePolicy policy;
    strcpy(policy.name, "Platinum");
    policy.bodilyInjuryPerPerson = 250000;
    policy.bodilyInjuryPerAccident = 500000;
    policy.propertyDamage = 100000;
    policy.collisionCoverage = 1;
    policy.comprehensiveCoverage = 1;
    policy.medicalPayments = 10000;
    policy.uninsuredMotoristPerPerson = 100000;
    policy.uninsuredMotoristPerAccident = 300000;
    policy.personalInjuryProtection = 10000;
    policy.roadsideAssistance = 2;
    policy.rentalCarReimbursement = 50;
    policy.accidentForgiveness = 1;
    policy.newCarReplacement = 1;
    policy.gapInsurance = 1;
    policy.safeDriverDiscount = 15.0;
    policy.multiPolicyDiscount = 15.0;
    policy.antiTheftDeviceDiscount = 10.0;
    policy.goodStudentDiscount = 10.0;
    policy.multiCarDiscount = 10.0;
    policy.loyaltyDiscount = 5.0;
    return policy;
}

// Function to display an insurance policy
void displayPolicy(InsurancePolicy policy) {
    printf("Insurance Policy: %s\n", policy.name);
    printf("Bodily Injury Liability: %d per person / %d per accident\n", policy.bodilyInjuryPerPerson, policy.bodilyInjuryPerAccident);
    printf("Property Damage Liability: %d per accident\n", policy.propertyDamage);
    printf("Collision Coverage: %s\n", policy.collisionCoverage ? "Yes" : "No");
    printf("Comprehensive Coverage: %s\n", policy.comprehensiveCoverage ? "Yes" : "No");
    printf("Medical Payments: %d\n", policy.medicalPayments);
    printf("Uninsured Motorist Coverage: %d per person / %d per accident\n", policy.uninsuredMotoristPerPerson, policy.uninsuredMotoristPerAccident);
    printf("Personal Injury Protection: %d\n", policy.personalInjuryProtection);
    printf("Roadside Assistance: %d\n", policy.roadsideAssistance);
    printf("Rental Car Reimbursement: %d per day\n", policy.rentalCarReimbursement);
    printf("Accident Forgiveness: %s\n", policy.accidentForgiveness ? "Yes" : "No");
    printf("New Car Replacement: %s\n", policy.newCarReplacement ? "Yes" : "No");
    printf("Gap Insurance: %s\n", policy.gapInsurance ? "Yes" : "No");
    printf("Safe Driver Discount: %.1f%%\n", policy.safeDriverDiscount);
    printf("Multi-Policy Discount: %.1f%%\n", policy.multiPolicyDiscount);
    printf("Anti-Theft Device Discount: %.1f%%\n", policy.antiTheftDeviceDiscount);
    printf("Good Student Discount: %.1f%%\n", policy.goodStudentDiscount);
    printf("Multi-Car Discount: %.1f%%\n", policy.multiCarDiscount);
    printf("Loyalty Discount: %.1f%%\n", policy.loyaltyDiscount);
}

int main() {
    InsurancePolicy basicPolicy = createBasicPolicy();
    InsurancePolicy premiumPolicy = createPremiumPolicy();
    InsurancePolicy platinumPolicy = createPlatinumPolicy();

    printf("=== Basic Policy ===\n");
    displayPolicy(basicPolicy);
    printf("\n");

    printf("=== Premium Policy ===\n");
    displayPolicy(premiumPolicy);
    printf("\n");

    printf("=== Platinum Policy ===\n");
    displayPolicy(platinumPolicy);
    printf("\n");

    return 0;
}
/////////////////////////////////////////////////////////////////////car/car/car/car

/*Sure! Here are three different car insurance packages—Basic, Premium, and Platinum—each offering varying levels of coverage and benefits.

1. Basic Package
Coverage:

Liability Insurance: Covers bodily injury and property damage to others.
Bodily Injury Liability: $50,000 per person / $100,000 per accident
Property Damage Liability: $25,000 per accident
Benefits:

Legal Defense: Coverage for legal costs if sued
Roadside Assistance: Limited to emergency towing and minor repairs
Exclusions:

No coverage for the insured's vehicle damage
No medical payments for the insured
Discounts:

Safe driver discount: 5%
Multi-policy discount: 5%
2. Premium Package
Coverage:

Liability Insurance: Enhanced limits
Bodily Injury Liability: $100,000 per person / $300,000 per accident
Property Damage Liability: $50,000 per accident
Collision Insurance: Covers damage to the insured’s car from a collision
Comprehensive Insurance: Covers non-collision-related damage (theft, vandalism, natural disasters)
Benefits:

Medical Payments: Up to $5,000 per person
Roadside Assistance: Includes towing, tire change, lockout service, and fuel delivery
Rental Car Reimbursement: Up to $30 per day for 30 days
Exclusions:

Deductible applies for collision and comprehensive claims (typically $500)
Discounts:

Safe driver discount: 10%
Multi-policy discount: 10%
Anti-theft device discount: 5%
Good student discount: 5%
3. Platinum Package
Coverage:

Liability Insurance: Maximum limits
Bodily Injury Liability: $250,000 per person / $500,000 per accident
Property Damage Liability: $100,000 per accident
Collision Insurance: Full coverage with lower deductible options ($250)
Comprehensive Insurance: Full coverage with lower deductible options ($250)
Uninsured/Underinsured Motorist Coverage: $100,000 per person / $300,000 per accident
Personal Injury Protection (PIP): Up to $10,000 per person
Benefits:

Medical Payments: Up to $10,000 per person
Roadside Assistance: Comprehensive service including hotel accommodation if stranded
Rental Car Reimbursement: Up to $50 per day for 30 days
Accident Forgiveness: No premium increase after the first at-fault accident
New Car Replacement: Replaces the car with a new one if totaled within the first year or 15,000 miles
Gap Insurance: Covers the difference between the car’s value and the remaining loan amount if totaled
Exclusions:

Minimal exclusions, mostly related to illegal activities or non-disclosed modifications
Discounts:

Safe driver discount: 15%
Multi-policy discount: 15%
Anti-theft device discount: 10%
Good student discount: 10%
Multi-car discount: 10%
Loyalty discount: 5%
Comparison Summary:
Feature	Basic Package	Premium Package	Platinum Package
Liability Coverage	50/100/25	100/300/50	250/500/100
Collision Coverage	No	Yes	Yes
Comprehensive Coverage	No	Yes	Yes
Medical Payments	No	Up to $5,000	Up to $10,000
Roadside Assistance	Limited	Full	Comprehensive
Rental Car Reimbursement	No	Up to $30/day	Up to $50/day
Uninsured/Underinsured Motorist	No	No	100/300
Personal Injury Protection (PIP)	No	No	Up to $10,000
Accident Forgiveness	No	No	Yes
New Car Replacement	No	No	Yes
Gap Insurance	No	No	Yes
Deductibles	N/A	$500	$250
Discounts	5-10%	5-10%	5-15%
These packages provide a range of options to suit different needs and budgets, from basic liability coverage to comprehensive protection with additional benefits.
*/