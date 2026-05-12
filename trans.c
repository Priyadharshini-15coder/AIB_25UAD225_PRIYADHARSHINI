// BANK MANAGEMENT SYSTEM WITH TRANSACTION HISTORY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

// structure definition
struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[15];
    double balance;
};

// function prototypes
unsigned int enterChoice(void);

void initializeFile(FILE *fPtr);

void createAccount(FILE *fPtr);
void depositAmount(FILE *fPtr);
void withdrawAmount(FILE *fPtr);
void transferMoney(FILE *fPtr);
void checkBalance(FILE *fPtr);
void displayAccounts(FILE *fPtr);
void deleteAccount(FILE *fPtr);

void saveTransaction(unsigned int accountNum,
                     char type[],
                     double amount,
                     double balance);

void transactionHistory(void);

int main()
{
    FILE *cfPtr;

    // open existing file
    cfPtr = fopen("bank.dat", "rb+");

    // create file if not exists
    if (cfPtr == NULL)
    {
        cfPtr = fopen("bank.dat", "wb+");

        if (cfPtr == NULL)
        {
            printf("File could not be opened.\n");
            return 1;
        }

        initializeFile(cfPtr);
    }

    unsigned int choice;

    while ((choice = enterChoice()) != 9)
    {
        switch (choice)
        {
        case 1:
            createAccount(cfPtr);
            break;

        case 2:
            depositAmount(cfPtr);
            break;

        case 3:
            withdrawAmount(cfPtr);
            break;

        case 4:
            transferMoney(cfPtr);
            break;

        case 5:
            checkBalance(cfPtr);
            break;

        case 6:
            displayAccounts(cfPtr);
            break;

        case 7:
            deleteAccount(cfPtr);
            break;

        case 8:
            transactionHistory();
            break;

        default:
            printf("Invalid choice\n");
        }
    }

    fclose(cfPtr);

    printf("Program exited successfully.\n");

    return 0;
}

// initialize file with blank records
void initializeFile(FILE *fPtr)
{
    struct clientData blankClient = {0, "", "", 0.0};

    rewind(fPtr);

    for (int i = 0; i < MAX_ACCOUNTS; i++)
    {
        fwrite(&blankClient,
               sizeof(struct clientData),
               1,
               fPtr);
    }
}

// menu
unsigned int enterChoice(void)
{
    unsigned int choice;

    printf("\n=========================\n");
    printf("   BANK MANAGEMENT\n");
    printf("=========================\n");
    printf("1. Create Account\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Transfer Money\n");
    printf("5. Check Balance\n");
    printf("6. Display Accounts\n");
    printf("7. Delete Account\n");
    printf("8. Transaction History\n");
    printf("9. Exit\n");
    printf("=========================\n");

    printf("Enter your choice: ");
    scanf("%u", &choice);

    return choice;
}

// create account
void createAccount(FILE *fPtr)
{
    struct clientData client = {0, "", "", 0.0};

    unsigned int accountNum;

    printf("Enter account number (1 - 100): ");
    scanf("%u", &accountNum);

    if (accountNum < 1 || accountNum > MAX_ACCOUNTS)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum != 0)
    {
        printf("Account already exists.\n");
        return;
    }

    printf("Enter Last Name First Name Initial Balance:\n");

    scanf("%14s %14s %lf",
          client.lastName,
          client.firstName,
          &client.balance);

    client.acctNum = accountNum;

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fwrite(&client,
           sizeof(struct clientData),
           1,
           fPtr);

    fflush(fPtr);

    saveTransaction(client.acctNum,
                    "ACCOUNT CREATED",
                    client.balance,
                    client.balance);

    printf("Account created successfully.\n");
}

// deposit amount
void depositAmount(FILE *fPtr)
{
    struct clientData client;

    unsigned int accountNum;

    double amount;

    printf("Enter account number: ");
    scanf("%u", &accountNum);

    if (accountNum < 1 || accountNum > MAX_ACCOUNTS)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum == 0)
    {
        printf("Account not found.\n");
        return;
    }

    printf("Enter deposit amount: ");
    scanf("%lf", &amount);

    if (amount <= 0)
    {
        printf("Invalid amount.\n");
        return;
    }

    client.balance += amount;

    fseek(fPtr,
          -(long)sizeof(struct clientData),
          SEEK_CUR);

    fwrite(&client,
           sizeof(struct clientData),
           1,
           fPtr);

    fflush(fPtr);

    saveTransaction(client.acctNum,
                    "DEPOSIT",
                    amount,
                    client.balance);

    printf("Deposit successful.\n");

    printf("Updated Balance = %.2f\n",
           client.balance);
}

// withdraw amount
void withdrawAmount(FILE *fPtr)
{
    struct clientData client;

    unsigned int accountNum;

    double amount;

    printf("Enter account number: ");
    scanf("%u", &accountNum);

    if (accountNum < 1 || accountNum > MAX_ACCOUNTS)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum == 0)
    {
        printf("Account not found.\n");
        return;
    }

    printf("Enter withdraw amount: ");
    scanf("%lf", &amount);

    if (amount <= 0)
    {
        printf("Invalid amount.\n");
        return;
    }

    if (client.balance - amount < 0)
    {
        printf("Insufficient balance.\n");
        return;
    }

    client.balance -= amount;

    fseek(fPtr,
          -(long)sizeof(struct clientData),
          SEEK_CUR);

    fwrite(&client,
           sizeof(struct clientData),
           1,
           fPtr);

    fflush(fPtr);

    saveTransaction(client.acctNum,
                    "WITHDRAW",
                    amount,
                    client.balance);

    printf("Withdrawal successful.\n");

    printf("Updated Balance = %.2f\n",
           client.balance);
}

// transfer money
void transferMoney(FILE *fPtr)
{
    struct clientData sender;
    struct clientData receiver;

    unsigned int senderAcc;
    unsigned int receiverAcc;

    double amount;

    printf("Enter sender account number: ");
    scanf("%u", &senderAcc);

    printf("Enter receiver account number: ");
    scanf("%u", &receiverAcc);

    if (senderAcc < 1 || senderAcc > MAX_ACCOUNTS ||
        receiverAcc < 1 || receiverAcc > MAX_ACCOUNTS)
    {
        printf("Invalid account number.\n");
        return;
    }

    // read sender
    fseek(fPtr,
          (senderAcc - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&sender,
          sizeof(struct clientData),
          1,
          fPtr);

    // read receiver
    fseek(fPtr,
          (receiverAcc - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&receiver,
          sizeof(struct clientData),
          1,
          fPtr);

    if (sender.acctNum == 0 || receiver.acctNum == 0)
    {
        printf("One or both accounts not found.\n");
        return;
    }

    printf("Enter transfer amount: ");
    scanf("%lf", &amount);

    if (amount <= 0)
    {
        printf("Invalid amount.\n");
        return;
    }

    if (sender.balance < amount)
    {
        printf("Insufficient balance.\n");
        return;
    }

    sender.balance -= amount;

    receiver.balance += amount;

    // update sender
    fseek(fPtr,
          (senderAcc - 1) * sizeof(struct clientData),
          SEEK_SET);

    fwrite(&sender,
           sizeof(struct clientData),
           1,
           fPtr);

    // update receiver
    fseek(fPtr,
          (receiverAcc - 1) * sizeof(struct clientData),
          SEEK_SET);

    fwrite(&receiver,
           sizeof(struct clientData),
           1,
           fPtr);

    fflush(fPtr);

    saveTransaction(sender.acctNum,
                    "TRANSFER SENT",
                    amount,
                    sender.balance);

    saveTransaction(receiver.acctNum,
                    "TRANSFER RECEIVED",
                    amount,
                    receiver.balance);

    printf("Transfer successful.\n");
}

// check balance
void checkBalance(FILE *fPtr)
{
    struct clientData client;

    unsigned int accountNum;

    printf("Enter account number: ");
    scanf("%u", &accountNum);

    if (accountNum < 1 || accountNum > MAX_ACCOUNTS)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum == 0)
    {
        printf("Account not found.\n");
        return;
    }

    printf("\nAccount Number : %u\n",
           client.acctNum);

    printf("Customer Name  : %s %s\n",
           client.firstName,
           client.lastName);

    printf("Balance        : %.2f\n",
           client.balance);
}

// display all accounts
void displayAccounts(FILE *fPtr)
{
    struct clientData client;

    rewind(fPtr);

    printf("\n%-10s%-15s%-15s%-15s\n",
           "Account",
           "Last Name",
           "First Name",
           "Balance");

    printf("-----------------------------------------------------\n");

    while (fread(&client,
                  sizeof(struct clientData),
                  1,
                  fPtr) == 1)
    {
        if (client.acctNum != 0)
        {
            printf("%-10u%-15s%-15s%-15.2f\n",
                   client.acctNum,
                   client.lastName,
                   client.firstName,
                   client.balance);
        }
    }
}

// delete account
void deleteAccount(FILE *fPtr)
{
    struct clientData client;

    struct clientData blankClient = {0, "", "", 0.0};

    unsigned int accountNum;

    printf("Enter account number to delete: ");
    scanf("%u", &accountNum);

    if (accountNum < 1 || accountNum > MAX_ACCOUNTS)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum == 0)
    {
        printf("Account does not exist.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fwrite(&blankClient,
           sizeof(struct clientData),
           1,
           fPtr);

    fflush(fPtr);

    saveTransaction(accountNum,
                    "ACCOUNT DELETED",
                    0,
                    0);

    printf("Account deleted successfully.\n");
}

// save transaction into file
void saveTransaction(unsigned int accountNum,
                     char type[],
                     double amount,
                     double balance)
{
    FILE *tPtr;

    tPtr = fopen("transactions.txt", "a");

    if (tPtr == NULL)
    {
        printf("Transaction file could not be opened.\n");
        return;
    }

    fprintf(tPtr,
            "Account: %u | Type: %s | Amount: %.2f | Balance: %.2f\n",
            accountNum,
            type,
            amount,
            balance);

    fclose(tPtr);
}

// display transaction history
void transactionHistory(void)
{
    FILE *tPtr;

    char ch;

    tPtr = fopen("transactions.txt", "r");

    if (tPtr == NULL)
    {
        printf("No transaction history found.\n");
        return;
    }

    printf("\n=========== TRANSACTION HISTORY ===========\n\n");

    while ((ch = fgetc(tPtr)) != EOF)
    {
        printf("%c", ch);
    }

    printf("\n===========================================\n");

    fclose(tPtr);
}