#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 8
#define MAX_USERS 100
#define MAX_POLICIES 100
#define MAX_CUSTOMERS 100
#define MAX_CLAIMS 100

// Define structures
typedef struct {
    char username[50];
    char password[50];
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

// Global variables
User users[MAX_USERS];
int num_users = 0;
Policy policies[MAX_POLICIES];
int num_policies = 0;
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
Claim claims[MAX_CLAIMS];
int num_claims = 0;

void encryptData(unsigned char* plaintext, int plaintext_len, unsigned char* key)
{
    for (int i = 0; i < plaintext_len; i++) {
        plaintext[i] = plaintext[i] ^ key[i % KEY_SIZE];
    }
}

void decryptData(unsigned char* ciphertext, int ciphertext_len, unsigned char* key)
{
    for (int i = 0; i < ciphertext_len; i++) {
        ciphertext[i] = ciphertext[i] ^ key[i % KEY_SIZE];
    }
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
}

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
            // After successful login, allow access to the system
            // You can place the menu display code here
            return;
        }
    }
    printf("Invalid username or password.\n");
}

void createPolicy() {
    // Policy creation logic
}

void addCustomer() {
    // Add customer logic
}

void initiateClaim() {
    // Claim initiation logic
}

void viewClaims() {
    // Display claims
}

void generateReport() {
    // Report generation logic
}

void saveData() {
    // Save users data
    FILE* usersFile = fopen("users.csv", "w");
    if (usersFile == NULL) {
        printf("Error opening users.csv file.\n");
        return;
    }
    fprintf(usersFile, "username,password,role\n");
    for (int i = 0; i < num_users; i++) {
        fprintf(usersFile, "%s,%s,%s\n", users[i].username, users[i].password, users[i].role);
    }
    fclose(usersFile);

    // Save policies data
    // Similarly, save policies, customers, and claims data to CSV files
}

void loadData() {
    // Load data from files
}

int main()
{
    unsigned char* plaintext = (unsigned char*)"This is the secret message to encrypt!";
    unsigned char key[KEY_SIZE] = { 'k', 'e', 'y', 'f', 'o', 'r', 'x', 'o' };
    int plaintext_len = strlen((char*)plaintext);

    // Encrypt the data
    encryptData(plaintext, plaintext_len, key);

    printf("Ciphertext is: %s\n", plaintext);

    // Decrypt the data
    decryptData(plaintext, plaintext_len, key);

    printf("Decrypted text is: %s\n", plaintext);

    // Implement the rest of the insurance management system here

    return 0;
}
