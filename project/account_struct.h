#ifndef ACCOUNT_RECORD
#define ACCOUNT_RECORD

struct Account
{
    int accountNumber;     // 0, 1, 2, ....
    int owners[2];         // Customer IDs
    long int balance;      // Amount of money in the account
};

#endif
