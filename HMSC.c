#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function declarations
void add();
void list();
void edit();
void delete1();
void search();
void login();

struct CustomerDetails { // Structure declaration
    char roomnumber[10];
    char name[20];
    char address[25];
    char phonenumber[15];
    char nationality[15];
    char email[20];
    char period[10];
    char arrivaldate[10];
} s;

void login() {
    int attempts = 0;
    char uname[20], pword[10];
    const char user[20] = "vnshk&vshn";
    const char pass[10] = "maihuna";
    char c;

    do {
        system("clear");
        printf("\n  **************************  LOGIN FORM  **************************  ");
        printf(" \n                       ENTER USERNAME: ");
        scanf("%19s", uname);  // Limit input size to prevent overflow
        getchar();  // Clear the newline character from the input buffer

        printf(" \n                       ENTER PASSWORD: ");
        int i = 0;
        while (i < 9) {  // Allow space for the null terminator
            c = getchar();
            if (c == '\n') break;  // Stop at newline
            pword[i] = c;
            printf("*");  // Print asterisk for each character entered
            i++;
        }
        pword[i] = '\0';  // Null-terminate the string

        if (strcmp(uname, user) == 0 && strcmp(pword, pass) == 0) {
            printf("\n\n\n       WELCOME !!!! LOGIN IS SUCCESSFUL");
            getchar();  // Wait for any key press
            break;
        } else {
            printf("\n        SORRY !!!!  LOGIN IS UNSUCCESSFUL");
            attempts++;
            getchar();  // Wait for any key press to clear input buffer
        }
    } while (attempts < 3);

    if (attempts >= 3) {
        printf("\nSorry, you have entered the wrong username and password three times!!!");
        getchar();  // Wait for any key press
    }

    system("clear");
}

int main() {
    int i;
    char choice;
    time_t t;
    time(&t);

    system("clear"); // Clear screen in Linux
    printf(" -------------------------------------------------------------------------\n");
    printf("|                                                                         |\n");
    printf("|                         WELCOME TO HOTEL DESERT CAVE                    |\n");
    printf("|                                                                         |\n");
    printf(" -------------------------------------------------------------------------\n");

    printf("\t\t*************************************************\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*       -----------------------------           *\n");
    printf("\t\t*        WELCOME TO HOTEL DESERT CAVE           *\n");
    printf("\t\t*       -----------------------------           *\n");
    printf("\t\t*************************************************\n\n\n");
    for (i = 0; i < 80; i++) printf("-");
    printf("\nCurrent date and time : %s", ctime(&t));
    for (i = 0; i < 80; i++) printf("-");
    printf(" \n Press any key to continue:");

    getchar(); // Wait for user input
    system("clear");
    login();
    system("clear");
    while (1) {
        system("clear");
        for (i = 0; i < 80; i++) printf("-");
        printf("\n   ******************************  |MAIN MENU|  ***************************** \n");
        for (i = 0; i < 80; i++) printf("-");
        printf("\n\n");
        printf("\t\t *Please enter your choice for menu*:\n\n");
        printf(" \n Enter 1 -> Book a room");
        printf("\n Enter 2 -> View Customer Record");
        printf(" \n Enter 3 -> Delete Customer Record");
        printf(" \n Enter 4 -> Search Customer Record");
        printf(" \n Enter 5 -> Edit Record");
        printf(" \n Enter 6 -> Exit");
        printf("\n");
        for (i = 0; i < 80; i++) printf("-");
        printf("\nCurrent date and time : %s", ctime(&t));
        for (i = 0; i < 80; i++) printf("-");
        printf("\n");
        choice = getchar();
        getchar(); // Consume newline character
        choice = toupper(choice);
        switch (choice) {
            case '1':
                add();
                break;
            case '2':
                list();
                break;
            case '3':
                delete1();
                break;
            case '4':
                search();
                break;
            case '5':
                edit();
                break;
            case '6':
                system("clear");
                printf("\n\n\t *****THANK YOU*****");
                printf("\n\t FOR TRUSTING OUR SERVICE");
                exit(0);
                break;
            default:
                system("clear");
                printf("Incorrect Input");
                printf("\n Press any key to continue");
                getchar();
        }
    }
}

void add() {
    FILE *f;
    char test;
    f = fopen("add.txt", "a+");
    if (f == 0) {
        f = fopen("add.txt", "w+");
        system("clear");
        printf("Please hold on while we set up our database in your computer!!");
        printf("\n Process completed, press any key to continue!! ");
        getchar();
    }

    while (1) {
        system("clear");
        printf("\n Enter Customer Details:");
        printf("\n**************************");
        printf("\n Enter Room number : ");
        scanf("%s", s.roomnumber);
        printf("Enter Name : ");
        scanf("%s", s.name);
        printf("Enter Address : ");
        scanf("%s", s.address);
        printf("Enter Phone Number : ");
        scanf("%s", s.phonenumber);
        printf("Enter Nationality : ");
        scanf("%s", s.nationality);
        printf("Enter Email : ");
        scanf("%s", s.email);
        printf("Enter Period('x' days) : ");
        scanf("%s", s.period);
        printf("Enter Arrival date(dd/mm/yyyy) : ");
        scanf("%s", s.arrivaldate);
        fwrite(&s, sizeof(s), 1, f);
        fflush(f); // Ensure data is written to file
        printf("\n\n1 Room is successfully booked!!");
        printf("\n Press ESC key to exit, any other key to add another customer detail:");
        test = getchar();
        if (test == 27) // ASCII code for ESC key
            break;
    }
    fclose(f);
}

void list() {
    FILE *f;
    int i;
    if ((f = fopen("add.txt", "r")) == NULL)
        exit(0);
    system("clear");
    printf("ROOM    ");
    printf("NAME\t ");
    printf("ADDRESS ");
    printf("PHONENUMBER ");
    printf("NATIONALITY ");
    printf("EMAIL ");
    printf("PERIOD ");
    printf("ARRIVALDATE \n");

    for (i = 0; i < 118; i++)
        printf("-");
    while (fread(&s, sizeof(s), 1, f) == 1) {
        printf("\n%s \t%s \t%s \t%s \t%s \t%s \t%s \t%s", s.roomnumber, s.name, s.address, s.phonenumber, s.nationality, s.email, s.period, s.arrivaldate);
    }
    printf("\n");
    for (i = 0; i < 118; i++)
        printf("-");

    fclose(f);
    getchar();
}

void delete1() {
    FILE *f, *t;
    int i = 1;
    char roomnumber[20];
    if ((t = fopen("temp.txt", "w")) == NULL)
        exit(0);
    if ((f = fopen("add.txt", "r")) == NULL)
        exit(0);
    system("clear");
    printf("Enter the Room Number of the hotel to be deleted from the database: \n");
    scanf("%s", roomnumber);
    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            i = 0;
            continue;
        } else {
            fwrite(&s, sizeof(s), 1, t);
        }
    }
    fclose(f);
    fclose(t);
    if (i == 1) {
        printf("\n\n Records of Customer in this Room number not found!!");
        getchar();
    } else {
        remove("add.txt");
        rename("temp.txt", "add.txt");
        printf("\n\n The Customer is successfully removed....");
        getchar();
    }
}

void search() {
    FILE *f;
    char roomnumber[20];
    int flag = 1;
    f = fopen("add.txt", "r+");
    if (f == 0)
        exit(0);
    system("clear");
    printf("Enter Room number of the customer to search: \n");
    scanf("%s", roomnumber);
    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            flag = 0;
            printf("\n\tRecord Found\n ");
            printf("\nRoom Number:\t%s", s.roomnumber);
            printf("\nName:\t%s", s.name);
            printf("\nAddress:\t%s", s.address);
            printf("\nPhone number:\t%s", s.phonenumber);
            printf("\nNationality:\t%s", s.nationality);
            printf("\nEmail:\t%s", s.email);
            printf("\nPeriod:\t%s", s.period);
            printf("\nArrival date:\t%s", s.arrivaldate);
            printf("\n\n");
            break;
        }
    }
    if (flag == 1) {
        printf("\n\tRequested Customer could not be found!");
    }
    getchar();
    fclose(f);
}

void edit() {
    FILE *f;
    int k = 1;
    char roomnumber[20];
    long int size = sizeof(s);
    if ((f = fopen("add.txt", "r+")) == NULL)
        exit(0);
    system("clear");
    printf("Enter Room number of the customer to edit:\n\n");
    scanf("%s", roomnumber);
    getchar(); // Consume newline character
    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            k = 0;
            printf("\nEnter Room Number     :");
            scanf("%s", s.roomnumber);
            printf("\nEnter Name           :");
            scanf("%s", s.name);
            printf("\nEnter Address        :");
            scanf("%s", s.address);
            printf("\nEnter Phone number :");
            scanf("%s", s.phonenumber);
            printf("\nEnter Nationality :");
            scanf("%s", s.nationality);
            printf("\nEnter Email :");
            scanf("%s", s.email);
            printf("\nEnter Period :");
            scanf("%s", s.period);
            printf("\nEnter Arrival date :");
            scanf("%s", s.arrivaldate);
            fseek(f, -size, SEEK_CUR);
            fwrite(&s, sizeof(s), 1, f);
            fflush(f); // Ensure data is written to file
            break;
        }
    }
    if (k == 1) {
        printf("\n\nTHE RECORD DOESN'T EXIST!!!!");
        fclose(f);
        getchar();
    } else {
        fclose(f);
        printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!");
        getchar();
    }
}
