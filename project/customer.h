#ifndef CUSTOMER_FUNCTIONS
#define CUSTOMER_FUNCTIONS

#include <stdio.h>     
#include <unistd.h>    
#include <string.h>    
#include <stdbool.h>   
#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <stdlib.h>    
#include <errno.h>
#include<string.h> 
#include <sys/ipc.h>
#include <sys/sem.h>


#include "./admin.h"
#include "./customer_struct.h"
#include "./account_struct.h"

struct Customer loggedincustomer;
int semIdentifier;

//bool getcustomerdetails(int connFD,int customerid);

bool logincustomerhandler(int connFD,struct Customer *ptrToCustomerID){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;
    w_bytes=write(connFD,"Enter the Login ID\n",sizeof("Enter the Login ID\n"));

    struct Customer customer;
    
    bzero(readbuffer, sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
    //printf("%s",readbuffer);

    char tempbuffer[1000];
    bzero(tempbuffer, sizeof(tempbuffer));
    strcpy(tempbuffer, readbuffer);
    strtok(tempbuffer, "-");
    int ID = atoi(strtok(NULL, "-"));

    int cus_fd=open("./customer.txt",O_RDONLY);
    off_t offset = lseek(cus_fd, ID * sizeof(struct Customer), SEEK_SET);
    
    bool userfound=false;
    if (offset >= 0)
    {
        struct flock lock = {F_RDLCK, SEEK_SET, ID * sizeof(struct Customer), sizeof(struct Customer), getpid()};

        int lockingStatus = fcntl(cus_fd, F_SETLKW, &lock);
        if (lockingStatus == -1)
        {
            perror("Error obtaining read lock on customer record!");
            return false;
        }

        r_bytes = read(cus_fd, &customer, sizeof(struct Customer));
        if (r_bytes == -1)
        {
            perror("Error reading customer record from file!");
        }

        lock.l_type = F_UNLCK;
        fcntl(cus_fd, F_SETLK, &lock);
        if (strcmp(customer.login, readbuffer) == 0)
            userfound = true;

        close(cus_fd);
    }
    if(userfound){
        w_bytes=write(connFD,"Enter the password*\n",sizeof("Enter the password*\n"));
        bzero(readbuffer, sizeof(readbuffer));
        r_bytes = read(connFD, readbuffer, sizeof(readbuffer));

        if(strcmp(customer.password,readbuffer)==0){
            *ptrToCustomerID=customer;
            return true;
        }
    }
    return false;
}

bool getbalance(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;

    struct Account account;
    account.accountNumber = loggedincustomer.account;

    if(getaccountdetails(connFD,&account)){
        sprintf(writebuffer,"Your account balance is ₹ %ld\n.. Type \"continue\".. \n",account.balance);
        w_bytes=write(connFD,writebuffer,sizeof(writebuffer));

        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
    }
    else{
        write(connFD,"Invalid account!! .. Type \"Exit\"\n",sizeof("Invalid account!! .. Type \"Exit\"\n"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        return false;
    }
    return true;
}

bool deposit(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;

    struct Account account;
    account.accountNumber = loggedincustomer.account;

    long int amount = 0;

    //lock cs
    struct sembuf semOp;
    semOp.sem_flg = SEM_UNDO;
    semOp.sem_op = -1;
    semOp.sem_num = 0;
    int semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while locking critical section");
        return false;
    }
    
    if(getaccountdetails(connFD,&account)){
        w_bytes=write(connFD,"Enter the amount to be deposited \n",sizeof("Enter the amount to be deposited \n"));

        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

        amount=atol(readbuffer);
        if(account.balance>=0){
            account.balance+=amount;

            int acc_fd=open("./account.txt",O_WRONLY);
            off_t offset = lseek(acc_fd, account.accountNumber * sizeof(struct Account), SEEK_SET);

            struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};
            int lockingStatus = fcntl(acc_fd, F_SETLKW, &lock);

            w_bytes=write(acc_fd,&account,sizeof(account));

            lock.l_type = F_UNLCK;
            fcntl(acc_fd, F_SETLK, &lock);
            write(connFD,"Amount deposited..Type \"continue\" \n",sizeof("Amount deposited..Type \"continue\" \n"));

            bzero(readbuffer,sizeof(readbuffer));
            r_bytes=read(connFD,readbuffer,sizeof(readbuffer));


            //unlock cs
            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
        }
        else{
             write(connFD,"Invalid account!! .. Type \"Exit\"\n",sizeof("Invalid account!! .. Type \"Exit\"\n"));
            bzero(readbuffer,sizeof(readbuffer));
            r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

            //unlock cs
            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);

            return false;
        }

    }
    else{
        write(connFD,"Invalid account!! .. Type \"Exit\"\n",sizeof("Invalid account!! .. Type \"Exit\"\n"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

        //unlock cs
        semOp.sem_op = 1;
        semop(semIdentifier, &semOp, 1);

        return false;
    }

    return true;
}

bool withdraw(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;

    struct Account account;
    account.accountNumber = loggedincustomer.account;

    long int amount=0;

    //lock cs
    struct sembuf semOp;
    semOp.sem_flg = SEM_UNDO;
    semOp.sem_op = -1;
    semOp.sem_num = 0;
    int semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while locking critical section");
        return false;
    }
    
    if(getaccountdetails(connFD,&account)){
        w_bytes=write(connFD,"Enter the amount to withdraw \n",sizeof("Enter the amount to withdraw \n"));

        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

        amount=atol(readbuffer);
        if(amount != 0 && account.balance - amount >= 0){
            account.balance-=amount;

            int acc_fd=open("./account.txt",O_WRONLY);
            off_t offset = lseek(acc_fd, account.accountNumber * sizeof(struct Account), SEEK_SET);

            struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};
            int lockingStatus = fcntl(acc_fd, F_SETLKW, &lock);

            w_bytes=write(acc_fd,&account,sizeof(account));

            lock.l_type = F_UNLCK;
            fcntl(acc_fd, F_SETLK, &lock);
            write(connFD,"Amount debited..Type \"continue\" \n",sizeof("Amount debited..Type \"continue\" \n"));

            bzero(readbuffer,sizeof(readbuffer));
            r_bytes=read(connFD,readbuffer,sizeof(readbuffer));


            //unlock cs
            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
        }
        else{
            write(connFD,"Insufficient balance .. Type \"continue\"\n",sizeof("Insufficient balance .. Type \"continue\"\n"));
            bzero(readbuffer,sizeof(readbuffer));
            r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
            
            //unlock cs
            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
            
            return false;
        }
    }
    else{
        write(connFD,"Invalid account!! .. Type \"Exit\"\n",sizeof("Invalid account!! .. Type \"Exit\"\n"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

        //unlock cs
        semOp.sem_op = 1;
        semop(semIdentifier, &semOp, 1);

        return false;
    }

    return true;
}

bool changepassword(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;

    //lock cs
    struct sembuf semOp = {0, -1, SEM_UNDO};
    semop(semIdentifier, &semOp, 1);

    write(connFD,"Enter the old password*\n",sizeof("Enter the old password*\n"));
    bzero(readbuffer,sizeof(readbuffer));
    read(connFD,readbuffer,sizeof(readbuffer));

    if(strcmp(readbuffer,loggedincustomer.password)==0){
        write(connFD,"Enter the new password*\n",sizeof("Enter the new password*\n"));
        bzero(readbuffer,sizeof(readbuffer));
        read(connFD,readbuffer,sizeof(readbuffer));
        char tempbuffer[1000];

        write(connFD,"Re-enter the new password*\n",sizeof("Re-enter the new password*\n"));
        bzero(tempbuffer,sizeof(tempbuffer));
        read(connFD,tempbuffer,sizeof(tempbuffer));

        if(strcmp(readbuffer,tempbuffer)==0){

            strcpy(loggedincustomer.password,readbuffer);

            int cus_fd=open("./customer.txt",O_WRONLY);
            off_t offset = lseek(cus_fd, loggedincustomer.id * sizeof(struct Customer), SEEK_SET);

            struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct Customer), getpid()};
            int lockingStatus = fcntl(cus_fd, F_SETLKW, &lock);
            if (lockingStatus == -1)
            {
                perror("Error obtaining write lock on customer record!");
                semOp.sem_op = 1;
                int semopStatus = semop(semIdentifier, &semOp, 1);
                if (semopStatus == -1)
                {
                    perror("Error while operating on semaphore!");
                    _exit(1);
                }
                return false;
            }

            w_bytes=write(cus_fd,&loggedincustomer,sizeof(loggedincustomer));

            lock.l_type = F_UNLCK;
            lockingStatus = fcntl(cus_fd, F_SETLK, &lock);

            close(cus_fd);

            w_bytes=write(connFD,"Password successfully changed!!..type \"continue\" \n",sizeof("Password successfully changed!!..type \"continue\" \n"));
            bzero(readbuffer,sizeof(readbuffer));
            read(connFD,readbuffer,sizeof(readbuffer));

            //unlock cs
            semOp.sem_op = 1;
            int semopStatus = semop(semIdentifier, &semOp, 1);
            if (semopStatus == -1)
            {
                perror("Error while operating on semaphore!");
                _exit(1);
            }
            return true;

        }
        else{
            w_bytes=write(connFD,"Re-enterd password doesnt match ..type \"continue\" \n",sizeof("Re-enterd password doesnt match ..type \"continue\" \n"));
            bzero(readbuffer,sizeof(readbuffer));
            read(connFD,readbuffer,sizeof(readbuffer));
        }

    }
    else{
        w_bytes=write(connFD,"Incorrect password entered ..type \"continue\" \n",sizeof("Incorrect password entered ..type \"continue\" \n"));
        bzero(readbuffer,sizeof(readbuffer));
        read(connFD,readbuffer,sizeof(readbuffer));
    }

    semOp.sem_op = 1;
    int semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }
    return false;
}

bool customerhandler(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;
    if(logincustomerhandler(connFD,&loggedincustomer)){
        key_t semKey = ftok("./customer.txt", loggedincustomer.account); // Generate a key based on the account number hence, different customers will have different semaphores

        union semun
        {
            int val; // Value of the semaphore
        } semSet;

        int semctlStatus;
        semIdentifier = semget(semKey, 1, 0);
        if (semIdentifier == -1)
        {
            semIdentifier = semget(semKey, 1, IPC_CREAT | 0700); // Create a new semaphore
            if (semIdentifier == -1)
            {
                perror("Error while creating semaphore!");
                _exit(1);
            }

            semSet.val = 1; // Set a binary semaphore
            semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
            if (semctlStatus == -1)
            {
                perror("Error while initializing a binary sempahore!");
                _exit(1);
            }
        }

        while(1){

            w_bytes=write(connFD,"Login Customer Sucess!!\n1. Get Customer Details\n2. Deposit Money\n3. Withdraw Money\n4. Get Balance\n5. Change Password\n6. to exit\n Enter your choice\n",sizeof("Login Customer Sucess!!\n1. Get Customer Details\n2. Deposit Money\n3. Withdraw Money\n4. Get Balance\n5. Change Password\n6. to exit\n Enter your choice\n"));

            bzero(readbuffer,sizeof(readbuffer));
            r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

            int opt=atoi(readbuffer);
            switch (opt)
            {
            case 1:
                getcustomerdetails(connFD, loggedincustomer.id);
                break;
            case 2:
                deposit(connFD);
                break;
            case 3:
                withdraw(connFD);
                break;
            case 4:
                getbalance(connFD);
                break;
            case 5:
                changepassword(connFD);
                break;
            default:
                w_bytes=write(connFD,"Exiting\n~",sizeof("Exiting\n~"));
                break;
            }
        }
    }
    else{
        w_bytes=write(connFD,"Invalid credentials..type \"Exit\"\n~",sizeof("Invalid credentials..type \"Exit\"\n~"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        return false;
    }
}

#endif