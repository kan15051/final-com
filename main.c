#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct userinfo{
    char FirstName[100];
    char LastName[100];
    char UserName[100];
    char PassWord[100];
    char HouseNO[100];
    char Village[100];
    char Lane[100];
    char Road[100];
    char SubDistrict[100];
    char District[100];
    char Province[100];
    char PostalCode[10];
}UserInfo;

void GetUserInfo(UserInfo*);

void ShowUserInfo(UserInfo);

int CheckExist(char*);

void CreateAccout();

void OpenUserInfo(char*, UserInfo*);

int CheckPass(char*, char*);

int main(){
    char command[10];
    char username[100];
    char filename[100];
    int status=0;
    UserInfo User;
    while(1){
        fgets(command,10,stdin);
        command[strlen(command)-1]='\0';
        if(!strcmp("help",command)){
            printf("register        for account register\nlogin           for login\nlogout          for logout\nshowinfo        show user infomation\nexit            exit the program\n");
        }
        else if(!strcmp("register",command)){
            CreateAccout();
        }
        else if(!strcmp("login",command)){
            char password[100];
            printf("Enter Username: ");
            fgets(username,10,stdin);
            username[strlen(username)-1]='\0';
            printf("Enter Password: ");
            fgets(password,10,stdin);
            strcpy(filename,username);
            strcat(filename,".bin");
            password[strlen(password)-1]='\0';
            status=CheckPass(username, password);
            if(status){
                OpenUserInfo(username, &User);
            }
        }
        else if(!strcmp("showinfo",command)){
            if(status){
                ShowUserInfo(User);
            }
            else{
                printf("Please Login\n");
            }
        }
        else if(!strcmp("logout",command)){
            strcpy(username,"\0");
            strcpy(filename,"\0");
            status=0;
            if(status==0){
                printf("Logout successful\n");
            }

        }
        else if(!strcmp("exit",command)){
            break;
        }
        else{
            printf("1\n");
        }
    }
}

void GetUserInfo(UserInfo* User){
    printf("Enter Firstname: ");
    fgets(User->FirstName,sizeof(User->FirstName),stdin);//firstname
    User->FirstName[strlen(User->FirstName)-1]='\0';
    printf("Enter Lastname: ");
    fgets(User->LastName,100,stdin);//lastname
    User->LastName[strlen(User->LastName)-1]='\0';
    printf("Enter Username: ");
    fgets(User->UserName,100,stdin);//username
    User->UserName[strlen(User->UserName)-1]='\0';
    printf("Enter Password: ");
    fgets(User->PassWord,100,stdin);//password
    User->PassWord[strlen(User->PassWord)-1]='\0';
    printf("Please Fill Your Adress\n");
    printf("House Number: ");
    fgets(User->HouseNO,100,stdin);//houseno.
    User->HouseNO[strlen(User->HouseNO)-1]='\0';
    printf("Village: ");
    fgets(User->Village,100,stdin);//village
    User->Village[strlen(User->Village)-1]='\0';
    printf("Lane: ");
    fgets(User->Lane,100,stdin);//lane
    User->Lane[strlen(User->Lane)-1]='\0';
    printf("Road: ");
    fgets(User->Road,100,stdin);//road
    User->Road[strlen(User->Road)-1]='\0';
    printf("Sub-district: ");
    fgets(User->SubDistrict,100,stdin);//subdistrict
    User->SubDistrict[strlen(User->SubDistrict)-1]='\0';
    printf("District: ");
    fgets(User->District,100,stdin);//district
    User->District[strlen(User->District)-1]='\0';
    printf("Province: ");
    fgets(User->Province,100,stdin);//province
    User->Province[strlen(User->Province)-1]='\0';
    printf("Postal Code: ");
    fgets(User->PostalCode,100,stdin);//postalcode
    User->PostalCode[strlen(User->PostalCode)-1]='\0';
}

void ShowUserInfo(UserInfo User){
    printf("Enter Firstname: ");
    puts(User.FirstName);
    printf("Enter Lastname: ");
    puts(User.LastName);
    printf("Enter Username: ");
    puts(User.UserName);
    printf("Enter Password: ");
    puts(User.PassWord);
    printf("Please Fill Your Adress\n");
    printf("House Number: ");
    puts(User.HouseNO);
    printf("Village: ");
    puts(User.Village);
    printf("Lane: ");
    puts(User.Lane);
    printf("Road: ");
    puts(User.Road);
    printf("Sub-district: ");
    puts(User.SubDistrict);
    printf("District: ");
    puts(User.District);
    printf("Province: ");
    puts(User.Province);
    printf("Postal Code: ");
    puts(User.PostalCode);
}

int CheckExist(char* filename){
    FILE *fptr;
    if(fptr=fopen(filename,"rb")){
        fclose(fptr);
        return 1;
    }
    else{
        return 0;
    }
}

void CreateAccout(){
    UserInfo User;
    GetUserInfo(&User);
    char FileName[100];
    strcpy(FileName,User.UserName);
    strcat(FileName,".bin");
    FILE *fptr;
    if(CheckExist(FileName)){
        printf("Account is Already Exist\n");
    }
    else{
        fptr = fopen(FileName,"wb");
        fwrite(&User, sizeof(User), 1, fptr);
        printf("Create account successful\n");
        fclose(fptr);
    }
}

void OpenUserInfo(char* Username, UserInfo* User){
    char filename[100];
    FILE *fptr;
    strcpy(filename,Username);
    strcat(filename,".bin");
    fptr = fopen(filename, "rb");
    fread(User, sizeof(*User), 1, fptr);
    fclose(fptr);
}

int CheckPass(char* Username, char* Password){
    char Filename[100];
    UserInfo temp;
    FILE *fptr;

    strcpy(Filename, Username);
    strcat(Filename, ".bin");
    if(!CheckExist(Filename)){
        printf("Username or Password is incorrect\n");
        return 0;
    }
    fptr=fopen(Filename,"rb");
    fread(&temp,sizeof(temp),1,fptr);
    fclose(fptr);
    if(!strcmp(Username,temp.UserName)){
        if(!strcmp(Password, temp.PassWord)){
            printf("Login successful\n");
            return 1;
        }
        printf("Username or Password is incorrect\n");
        return 0;
    }
    else{
        printf("Username or Password is incorrect\n");
        return 0;
    }
}