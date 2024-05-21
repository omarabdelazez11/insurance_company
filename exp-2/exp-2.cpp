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
    char password_hash[65];  // Adjusted length to store hashed password without OpenSSL
    char role[20];
} User;

typedef struct {
    int policy_id;
    char type[50];
    float premium_amount;
    char start_date[20];
    char end_date[20];
    char beneficiary[100];
    char owner[100];
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

int main (){
    return 0;
}