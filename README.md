# Bank Management System  
### Mini Project – File Handling in C Programming

---

## Objective
This mini project focuses on developing and enhancing a **Bank Management System** using the **C programming language**. The project demonstrates the use of **structures**, **functions**, **binary file handling**, and **random-access files** to perform various banking operations efficiently.

Students are expected to understand the existing system, improve the code, add new features, and optimize the program while following proper coding practices.

---

## Project Description

The Bank Management System is a menu-driven console application that allows users to:

- Create new bank accounts
- Deposit money
- Withdraw money
- Transfer money between accounts
- Check account balance
- Display all customer accounts
- Delete accounts
- View transaction history

The system permanently stores account records using binary files and maintains transaction logs using text files.

---

## Features Implemented

### Core Features
- Account Creation
- Deposit Functionality
- Withdraw Functionality
- Balance Checking
- Account Deletion
- Display All Accounts

---

### Advanced Features Added
- Money Transfer Between Accounts
- Transaction History
- Invalid Input Checking
- Insufficient Balance Validation
- File Initialization
- Random Access File Handling
- Persistent Data Storage

---

## Files Used

| File Name | Purpose |
|---|---|
| `bank.c` | Main source code |
| `bank.dat` | Binary file storing account details |
| `transactions.txt` | Stores transaction history |
| `README.md` | Project documentation |

---

## Structure Used

```c
struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[15];
    double balance;
};

Concepts Used
1. Structures
2. Functions
3. File Handling
4. Binary Files
5. Random Access Files
6. fseek()
7. fread()
8. fwrite()
9. Menu Driven Programming

=========================
   BANK MANAGEMENT
=========================
1. Create Account
2. Deposit
3. Withdraw
4. Transfer Money
5. Check Balance
6. Display Accounts
7. Delete Account
8. Transaction History
9. Exit
=========================

Tasks Performed
1. Compiled and executed the program successfully.
2. Tested all banking operations.
3. Added new customer accounts and verified stored records.
4. Implemented transaction history functionality.
5. Added display accounts functionality.
6. Improved error handling and validations.
7. Optimized file handling operations.

=========================
Logical Errors fixed
1. Issues Identified
2. Improper use of while(!feof())
3. Missing account validation
4. No insufficient balance checking
5. Missing file initialization
6. Lack of transaction tracking

=========================
Improvements Made
1. Added proper file reading conditions
2. Added account range validation
3. Added balance validation before withdrawal
4. Added transaction history file
5. Added safer file operations
6. Error Handling Implemented

=========================
The system checks for:
1. Invalid account numbers
2. Duplicate accounts
3. Invalid deposit/withdraw amounts
4. Insufficient balance
5. File opening failures
6. Missing accounts

========================
Advantages of the Project
1. Beginner-friendly
2. Demonstrates real-world banking logic
3. Uses permanent data storage
4. Efficient file handling
5. Modular design
6. Easy to extend with new features

======================
Future Enhancements

Possible future improvements include:
1. Login System
2. Password Protection
3. GUI Interface
4. Database Integration
5. Date and Time Tracking
6. ATM Simulation
7. Interest Calculation
8. Encryption

======================
Conclusion

The Bank Management System successfully demonstrates the implementation of banking operations using C programming and random-access file handling. The project helped in understanding practical applications of structures, functions, binary files, and modular programming concepts.This project provides a strong foundation for developing more advanced banking and database-driven applications in the future.