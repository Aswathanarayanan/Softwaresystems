#ifndef CUSTOMER_RECORD
#define CUSTOMER_RECORD

struct Customer
{
    int id;
    char name[25];
    char gender;
    char ph[10];
    char address[100];
    int age;
    // Login Credentials
    char login[30]; // Format : name-id (name will the first word in the structure member `name`)
    char password[30];
    int account; 
};

#endif