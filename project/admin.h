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

#include "./customer_struct.h"
#include "./account_struct.h"
#include "./admin_cred.h"

bool loginadminhandler(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;
    //strcpy(writebuffer,);
    w_bytes=write(connFD,"Enter the Login ID\n",sizeof("Enter the Login ID\n"));
    
    bzero(readbuffer, sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
    //printf("%s",readbuffer);

    if(strcmp(ADMIN_LOGIN_ID,readbuffer)==0){
        bzero(writebuffer, sizeof(writebuffer));
        w_bytes=write(connFD,"Enter the Password*\n",sizeof("Enter the Password*\n"));
        
        bzero(readbuffer, sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        printf("%d",r_bytes);
        if(strcmp(ADMIN_PASSWORD,readbuffer)==0)
            return true;
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

    w_bytes=write(connFD,"Enter the password*\n",sizeof("Enter the password*\n"));
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
    w_bytes=write(connFD,"Enter Intial amount to be deposited\n",sizeof("Enter Intial amount to be deposited\n"));
    bzero(readbuffer, sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

    int amount=atoi(readbuffer);
    newaccount.balance=amount;

    acc_fd = open("./account.txt", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
     w_bytes = write(acc_fd, &newaccount, sizeof(struct Account));
    close(acc_fd);

    bzero(writebuffer,sizeof(writebuffer));
    sprintf(writebuffer,"Added account..Account number: %d\nRedirecting to main menu...type \"continue\"\n",newaccount.accountNumber);
    //w_bytes = write(connFD, "Added account...Redirecting to main menu...type \"continue\"\n", sizeof("Added account...Redirecting to main menu...type \"continue\"\n"));
    w_bytes=write(connFD,writebuffer,sizeof(writebuffer));
    r_bytes = read(connFD, readbuffer, sizeof(readbuffer)); // Dummy read
}

bool getaccountdetails(int connFD,struct Account *customeraccount){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;
    struct Account account;
    int acc_fd;
    int accountnum;

    if(customeraccount==NULL){
        w_bytes=write(connFD,"Enter the account NUmber\n",sizeof("Enter the account Number\n"));

        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

        accountnum=atoi(readbuffer);
    }
    else
        accountnum=customeraccount->accountNumber;

    acc_fd=open("./account.txt",O_RDONLY);
    if(acc_fd==-1){
        w_bytes=write(connFD,"Error in openning account file,..Type\"Exit\"\n",sizeof("Error in openning account file,..Type\"Exit\"\n"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        return false;
    }
    int offset = lseek(acc_fd, accountnum * sizeof(struct Account), SEEK_SET);
    if (offset == -1 && errno == EINVAL){
        w_bytes=write(connFD,"Account number doesnt exists,..Type\"Exit\"\n",sizeof("Account number doesnt exists,..Type\"Exit\"\n"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        return false;
    }
    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};

    int lockingStatus = fcntl(acc_fd, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error obtaining read lock on account record!");
        return false;
    }
    r_bytes=read(acc_fd,&account,sizeof(struct Account));
     lock.l_type = F_UNLCK;
    fcntl(acc_fd, F_SETLK, &lock);

    //to copy the account details (used in customer file)
    if(customeraccount!=NULL){
        *customeraccount=account;
        return true;
    } //////////////////////////////////////////used in customer

    bzero(writebuffer,sizeof(writebuffer));
    sprintf(writebuffer,"----Account Details----\nAccount Number:%d\n Account Owner ID:%d\n",account.accountNumber,account.owners[0]);
    char tempbuffer[1000];
    
    if(account.owners[1]!=-1){
        sprintf(tempbuffer,"Account Owner ID:%d\n",account.owners[1]);
        strcat(writebuffer,tempbuffer);
    }
    bzero(tempbuffer,sizeof(tempbuffer));
    sprintf(tempbuffer,"Account balance:%ld\n..type \"continue\"..\n",account.balance);
    strcat(writebuffer,tempbuffer);
    w_bytes=write(connFD,writebuffer,sizeof(writebuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

    return true;
}

bool getcustomerdetails(int connFD,int customerid){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;
    struct Customer customer;
    int cus_fd;
    struct flock lock = {F_RDLCK, SEEK_SET, 0, sizeof(struct Account), getpid()};

    if(customerid==-1){
        w_bytes=write(connFD,"Enter the customer id to get the details\n",sizeof("Enter the customer id to get the details\n"));

        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        
        customerid=atoi(readbuffer);
    }

    cus_fd=open("./customer.txt",O_RDONLY);

    if(cus_fd==-1){
        w_bytes=write(connFD,"Customer doesnt exists,..Type \"Exit\" \n",sizeof("Customer doesnt exists,..Type \"Exit\" \n"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        return false;
    }
    int offset = lseek(cus_fd, customerid * sizeof(struct Customer), SEEK_SET);
    if (errno == EINVAL)
    {
        w_bytes=write(connFD,"Customer doesnt exists,..Type\"Exit\"\n",sizeof("Customer doesnt exists,..Type\"Exit\"\n"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        return false;
    }
    lock.l_start = offset;
    int lockingStatus = fcntl(cus_fd, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the Customer file!");
        return false;
    }

    r_bytes=read(cus_fd,&customer,sizeof(customer));

    lock.l_type = F_UNLCK;
    fcntl(cus_fd, F_SETLK, &lock);
    
    bzero(writebuffer,sizeof(writebuffer));
    sprintf(writebuffer,"--Customer details--\nID:%d\nName:%s\nGender:%c\nPhone number:%s\nAddress:%s\nAge:%d\nAccount number:%d\nLogin id:%s\n..type \"continue\" \n",customer.id,customer.name,customer.gender,customer.ph,customer.address,customer.age,customer.account,customer.login);
    w_bytes=write(connFD,writebuffer,sizeof(writebuffer));

    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
    return true;
}

bool deleteaccount(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;
    struct Account account;

    w_bytes=write(connFD,"Enter the Account number to be deleted\n",sizeof("Enter the Account number to be deleted\n"));
    
    bzero(readbuffer,sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

    int accnum=atoi(readbuffer);

    int acc_fd=open("./account.txt",O_RDONLY);
    if(acc_fd==-1){
        w_bytes=write(connFD,"Error in openning account file,..Type\"Exit\"\n",sizeof("Error in openning account file,..Type\"Exit\"\n"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        return false;
    }
    int offset = lseek(acc_fd, accnum * sizeof(struct Account), SEEK_SET);
    if (offset == -1 && errno == EINVAL){
        w_bytes=write(connFD,"Account number doesnt exists,..Type\"Exit\"\n",sizeof("Account number doesnt exists,..Type\"Exit\"\n"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        return false;
    }
    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};
    int lockingStatus = fcntl(acc_fd, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error obtaining read lock on Account record!");
        return false;
    }

    r_bytes = read(acc_fd, &account, sizeof(struct Account));
    lock.l_type = F_UNLCK;
    fcntl(acc_fd, F_SETLK, &lock);

    close(acc_fd);
    bzero(writebuffer, sizeof(writebuffer));

    if(account.balance==0){
        acc_fd=open("./account.txt",O_WRONLY);

        offset = lseek(acc_fd, accnum * sizeof(struct Account), SEEK_SET);
        lock.l_type = F_WRLCK;
        lock.l_start = offset;

        int lockingStatus = fcntl(acc_fd, F_SETLKW, &lock);
        if (lockingStatus == -1)
        {
            perror("Error obtaining write lock on the Account file!");
            return false;
        }
        w_bytes=write(acc_fd,NULL,0);
        lock.l_type = F_UNLCK;
        fcntl(acc_fd, F_SETLK, &lock);

        bzero(writebuffer,sizeof(writebuffer));
        w_bytes=write(connFD,"Account deleted..type\"continue\"\n",sizeof("Account deleted..type\"continue\"\n"));
    }
    else{
        bzero(writebuffer,sizeof(writebuffer));
        w_bytes=write(connFD,"Account cannot be deleted..type \"continue\" \n",sizeof("Account cannot be deleted..type \"continue\" \n"));
    }

    bzero(readbuffer,sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

    return true;

}

bool modifycustomerdetails(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;
    struct Customer customer;

    off_t offset;
    w_bytes=write(connFD,"Enter the customer ID whose details to be modified\n",sizeof("Enter the customer ID whose details to be modified\n"));

    bzero(readbuffer,sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
    
    int cusid= atoi(readbuffer);

    int cus_fd=open("./customer.txt",O_RDONLY);
    if(cus_fd==-1){
        w_bytes=write(connFD,"Customer doesnt exists,..Type \"Exit\" \n",sizeof("Customer doesnt exists,..Type \"Exit\" \n"));
        bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
         bzero(readbuffer,sizeof(readbuffer));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        return false;
    }

    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Customer), getpid()};
    int lockingStatus = fcntl(cus_fd, F_SETLKW, &lock);

    r_bytes=read(cus_fd,&customer,sizeof(struct Customer));

    lock.l_type = F_UNLCK;
    fcntl(cus_fd, F_SETLK, &lock);

    close(cus_fd);

    w_bytes=write(connFD,"Select the field that is to be modified\n1.Name\n2.Gender\n3.Phone number\n4.Address\n5.Age\n",sizeof("Select the field that is to be modified\n1.Name\n2.Gender\n3.Phone number\n4.Address\n5.Age\n"));

    bzero(readbuffer,sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

    int opt=atoi(readbuffer);
    bzero(readbuffer, sizeof(readbuffer));
    switch (opt)
    {
    case 1:
        w_bytes=write(connFD,"Enter the new name\n",sizeof("Enter the new name\n"));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

        strcpy(customer.name,readbuffer);
        break;
    case 2:
        w_bytes=write(connFD,"Enter the gender\n",sizeof("Enter the gender\n"));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        customer.gender=readbuffer[0];
        break;
    case 3:
        w_bytes=write(connFD,"Enter the phone number\n",sizeof("Enter the phone number\n"));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        strcpy(customer.ph,readbuffer);
        break;
    case 4:
        w_bytes=write(connFD,"Enter the Address\n",sizeof("Enter the Address\n"));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        strcpy(customer.address,readbuffer);
        break;
    case 5:
        w_bytes=write(connFD,"Enter the Age\n",sizeof("Enter the Age\n"));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        customer.age=atoi(readbuffer);
        break;
    default:
        w_bytes=write(connFD,"Invalid option ..type \"continue\" \n",sizeof("Invalid option ..type \"continue\" \n"));
        r_bytes=read(connFD,readbuffer,sizeof(readbuffer));
        return false;
        break;
    }
    cus_fd=open("./customer.txt",O_WRONLY);
    offset = lseek(cus_fd, cusid * sizeof(struct Customer), SEEK_SET);

    lock.l_type = F_WRLCK;
    lock.l_start = offset;
    lockingStatus = fcntl(cus_fd, F_SETLKW, &lock);

    w_bytes=write(cus_fd,&customer,sizeof(struct Customer));
    lock.l_type = F_UNLCK;
    fcntl(cus_fd, F_SETLKW, &lock);

    close(cus_fd);

    w_bytes=write(connFD,"Modified customer details..type \"continue\" \n",sizeof("Modified customer details..type \"continue\" \n"));

    bzero(readbuffer,sizeof(readbuffer));
    r_bytes=read(connFD,readbuffer,sizeof(readbuffer));

    return true;
}

bool adminhandler(int connFD){
    char writebuffer[1000],readbuffer[1000];
    int r_bytes,w_bytes;
    if(loginadminhandler(connFD)){
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
                    getcustomerdetails(connFD, -1);
                    break;
                case 2:
                    getaccountdetails(connFD, NULL);
                    break;
                case 3:
                    addaccount(connFD);
                    break;
                case 4:
                    deleteaccount(connFD);
                    break;
                case 5:
                    modifycustomerdetails(connFD);
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