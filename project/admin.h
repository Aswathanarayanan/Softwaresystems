#ifndef ADMIN_FUNCTIONS
#define ADMIN_FUNCTIONS

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

#include "./customer.h"
#include "./account.h"
#include "./admin_cred.h"

bool loginhandler(bool isadmin, int connFD, struct Customer *ptrToCustomerID){
    if(isadmin){
        char writebuffer[1000],readbuffer[1000];
        int r_bytes,w_bytes;
        //strcpy(writebuffer,);
        w_bytes=write(connFD,"Enter the Login ID\n",sizeof("Enter the Login ID\n"));
        
        bzero(readbuffer, sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        printf("%s",readbuffer);

        if(strcmp(ADMIN_LOGIN_ID,readbuffer)==0){
            bzero(writebuffer, sizeof(writebuffer));
            w_bytes=write(connFD,"Enter the Password\n",sizeof("Enter the Password\n"));
            
            bzero(readbuffer, sizeof(readbuffer));
            r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
            printf("%d",r_bytes);
            if(strcmp(ADMIN_PASSWORD,readbuffer)==0)
                return true;
        }

    }
    return false;
}

int addcustomer(int connFD,int acc_num){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;

    struct Customer newcustomer, previouscustomer;

    int cus_fd = open("./customer.txt", O_RDONLY);
    if (cus_fd == -1 && errno == ENOENT)
    {
        newcustomer.id = 0;
    }
    else
    {
        int offset = lseek(cus_fd, -sizeof(struct Customer), SEEK_END);
        if (offset == -1)
        {
            perror("Error seeking to last Customer record!");
            return false;
        }

        struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Customer), getpid()};
        int lockingStatus = fcntl(cus_fd, F_SETLKW, &lock);
        if (lockingStatus == -1)
        {
            perror("Error obtaining read lock on Customer record!");
            return false;
        }

        r_bytes = read(cus_fd, &previouscustomer, sizeof(struct Customer));
        if (r_bytes == -1)
        {
            perror("Error while reading Customer record from file!");
            return false;
        }

        lock.l_type = F_UNLCK;
        fcntl(cus_fd, F_SETLK, &lock);

        close(cus_fd);

        newcustomer.id = previouscustomer.id + 1;
    }

    w_bytes=write(connFD,"Enter the customer name\n",sizeof("Enter the customer name\n"));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

    strcpy(newcustomer.name,readbuffer);

    w_bytes=write(connFD,"Enter the gender\n",sizeof("Enter the gender\n"));
    bzero(readbuffer, sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

    if(readbuffer[0]=='M' || readbuffer[0]=='F' || readbuffer[0]=='O'){
        newcustomer.gender=readbuffer[0];
    }
    else{

    }/////////////////////////////

    w_bytes=write(connFD,"Enter the phonenumber\n",sizeof("Enter the phonenumber\n"));
    bzero(readbuffer, sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
    strcpy(newcustomer.ph,readbuffer);

    w_bytes=write(connFD,"Enter the address\n",sizeof("Enter the address\n"));
    bzero(readbuffer, sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
    strcpy(newcustomer.address,readbuffer);

    w_bytes=write(connFD,"Enter the age\n",sizeof("Enter the age\n"));
    bzero(readbuffer, sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
    newcustomer.age=atoi(readbuffer);

    strcpy(newcustomer.login,newcustomer.name);
    strcat(newcustomer.login,"-");
    sprintf(writebuffer,"%d",newcustomer.id);
    strcat(newcustomer.login,writebuffer);

    w_bytes=write(connFD,"Enter the password\n",sizeof("Enter the password\n"));
    bzero(readbuffer, sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
    strcpy(newcustomer.password,readbuffer);///////////////////to hide pass

    newcustomer.account=acc_num;

    cus_fd = open("./customer.txt", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
    w_bytes = write(cus_fd, &newcustomer, sizeof(newcustomer));

    close(cus_fd);

    bzero(writebuffer,sizeof(writebuffer));
    w_bytes=write(connFD,"Customer added.. type \"continue\"\n",sizeof("Customer added.. type \"continue\"\n"));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

    return newcustomer.id;
}

bool addaccount(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;
    struct Account newaccount, prevaccount;

    int acc_fd = open("./account.txt", O_RDONLY);
    if (acc_fd == -1 && errno == ENOENT)
    {
        newaccount.accountNumber = 0;
    }
    else
    {
        int offset = lseek(acc_fd, -sizeof(struct Account), SEEK_END);
        if (offset == -1)
        {
            perror("Error seeking to last Account record!");
            return false;
        }

        struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};
        int lockingStatus = fcntl(acc_fd, F_SETLKW, &lock);
        
        r_bytes = read(acc_fd, &prevaccount, sizeof(struct Account));
        if (r_bytes == -1)
        {
            perror("Error while reading Account record from file!");
            return false;
        }

        lock.l_type = F_UNLCK;
        fcntl(acc_fd, F_SETLK, &lock);

        close(acc_fd);

        newaccount.accountNumber = prevaccount.accountNumber + 1;
    }
    w_bytes=write(connFD,"Is it joint account? (Y/N)\n",sizeof("Is it joint account? (Y/N)\n"));
    bzero(readbuffer, sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

    newaccount.owners[0]=addcustomer(connFD,newaccount.accountNumber);
    
    if(strcmp(readbuffer,"Y")==0){
        newaccount.owners[1]=addcustomer(connFD,newaccount.accountNumber);
    }
    else{
        newaccount.owners[1]=-1;
    }
    newaccount.balance=0;
    acc_fd = open("./account.txt", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
     w_bytes = write(acc_fd, &newaccount, sizeof(struct Account));
    close(acc_fd);
    w_bytes = write(connFD, "Added account...Redirecting to main menu...type \"continue\"\n", sizeof("Added account...Redirecting to main menu...type \"continue\"\n"));
    r_bytes = read(connFD, readbuffer, sizeof(readbuffer)); // Dummy read
}

bool adminhandler(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;
    if(loginhandler(true,connFD,NULL)){
        //strcpy(writebuffer,);
        while(1){
            w_bytes=write(connFD,"Login Admin Success!!\n1. Get Customer Details\n2. Get Account Details\n3. Add Account\n4. Delete Account\n5. Modify Customer Information\n6. To exit\nEnter your choice\n",sizeof("Login Admin Success!!\n1. Get Customer Details\n2. Get Account Details\n3. Add Account\n4. Delete Account\n5. Modify Customer Information\n6. To exit\nEnter your choice\n"));

            bzero(readbuffer,sizeof(readbuffer));
            r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
            int opt=atoi(readbuffer);
            switch (opt)
            {
                case 1:
                    //w_bytes=write(connFD,"get_details",sizeof("get_details"));
                    //get_customer_details(connFD, -1);
                    break;
                case 2:
                    //get_account_details(connFD, NULL);
                    break;
                case 3:
                    addaccount(connFD);
                    break;
                case 4:
                    //delete_account(connFD);
                    break;
                case 5:
                    //modify_customer_info(connFD);
                    break;
                default:
                    //writeBytes = write(connFD, ADMIN_LOGOUT, strlen(ADMIN_LOGOUT));
                    return false;
            }
        }

    }
    else{
        w_bytes=write(connFD,"Invalid credentials",sizeof("Invalid credentials"));
    }
    return true;
}

#endif