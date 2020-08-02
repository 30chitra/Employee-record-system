#include <stdio.h> ///for input output functions like printf, scanf
#include <stdlib.h>///for standard library functions
#include <conio.h>///getch() is a function of this library
#include <windows.h> /// for windows functions
#include <string.h>  ///string operations

/** List of Global Variable */
COORD coord = {0,0}; /// top-left corner of window

/**
    function : gotoxy
    @param input: x and y coordinates
    @param output: moves the cursor in specified position of console
*/
void gotoxy(int x,int y)
{
    coord.X = x;///this is for x coordinate
    coord.Y = y;///this is for y coordinate
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

/** Main function started */

int main()
{ 
    FILE *fp, *ft; /// file pointers
   

    /** structure that represent a employee */
    struct employee
    {
        char name[40]; ///name of employee
        int age; /// age of employee
        float bs; /// basic salary of employee
    };

    struct employee e; /// structure variable creation
    char more, ch;///variables  for your choice and for entering another  record
    char empname[40]; /// string to store name of the employee

    long int recsize; /// size of each record of employee

    /** open the file in binary read and write mode
    * if the file EMP.DAT already exists then it open that file in read write mode
    * if the file doesn't exit it simply create a new copy
    */
    fp = fopen("EMPLOYEE.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMPLOYEE.DAT","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }
    	system("color 30");///this changes the background plus font colour that is of text
	int r,q;
	gotoxy(30,20);///moves to position 30,20
	printf("EMPLOYEE RECORD SYSTEM");
	printf("\n                     *****************************************\n");
	gotoxy(32,36);///moves to position 30,36
	printf("LOADING....");
	gotoxy(32,38);///moves to position 32,38
	for(r=1;r<=25;r++)///for loop for the loading bar
	{for(q=0;q<=100000000;q=q+2);
	{printf("%c",177);
	}
	}
	system("color 85");///changes background and font colour
    /// sizeo of each record i.e. size of structure variable e
    recsize = sizeof(e);

    /// infinite loop continues untile the break statement encounter
    while(1)
    {
        system("cls"); ///clear the console window
        gotoxy(25,6);///moves to position 25,6
        printf("      EMPLOYEE  RECORD  SYSTEM  ");
        gotoxy(20,8);///moves to position 20,8
        printf("\n=================================================================================\n");
        gotoxy(30,10); /// move the cursor to postion 30, 10 from top-left corner
        printf("1. Add Record"); /// option for add record
        gotoxy(30,12);///moves to position 30,12
        printf("\n                          ________________________________\n");
        gotoxy(30,14);///moves to position 30,14
		printf("2. List Records"); /// option for showing existing record
        gotoxy(30,16);///moves to position 30,16
        printf("\n                          ________________________________\n");
		gotoxy(30,18);///moves to position 30,18
        printf("3. Modify Records"); /// option for editing record
        gotoxy(30,20);///moves to position 30,20
        printf("\n                          ________________________________\n");
        gotoxy(30,22);///moves to position 30,22
        printf("4. Delete Records"); /// option for deleting record
        gotoxy(30,24);///moves to position 30,24
        printf("\n                          ________________________________\n");
        gotoxy(30,26);///moves to position 30,26
		printf("5. Exit"); /// exit from the program
        gotoxy(30,28);///moves to position 30,28
        printf("\n                          ________________________________\n");
        gotoxy(30,30);///moves to position 30,30
		printf("Your Choice: "); /// enter the choice 1, 2, 3, 4, 5
        fflush(stdin); /// flush the input buffer
        ch  = getche(); /// get the input from keyboard
        switch(ch)///cases for your choice enetered
        {
        case '1':  /// if user press 1
            system("cls");
            system("color 6f");///changes background and font colour
            fseek(fp,0,SEEK_END); /// search the file and move cursor to end of the file
            /// here 0 indicates moving 0 distance from the end of the file

            more = 'y';///sets the permission to enter to yes first
            printf("                          ADDITION OF RECORDS");
            printf("\n_______________________________________________________________________________\n");
            while(more == 'y')  /// if user want to add another record
            {   
                
                printf("\nEnter name: ");
                scanf("%s",e.name);///input the name of employee
                printf("\n---------------------------------------\n");
                
                printf("\nEnter age: ");
                scanf("%d", &e.age);///input the age of employee
                printf("\n---------------------------------------\n");
                
                printf("\nEnter basic salary $: ");
                scanf("%f", &e.bs);///input the salary
                printf("\n---------------------------------------\n");

                fwrite(&e,recsize,1,fp); /// write the record in the file

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                more = getche();///whether to input record more than once
                printf("\n-----------------------------------------------------------------------------\n");
            }
            break;///jumps out of the following case
        case '2':
            system("cls");
            system("color df");///changes background and font colour
            rewind(fp); ///this moves file cursor to start of the file
            printf("                               LIST  OF  ALL  RECORDS");
            printf("\n________________________________________________________________________________\n");
            while(fread(&e,recsize,1,fp)==1)  /// read the file and fetch the record one record per fetch
            {
                printf("\n# name of employee=%s \n age of employee=%d \n salary of employee=$%.2f \n\n",e.name,e.age,e.bs); /// print the name, age and basic salary
                printf("\n--------------------------------------------------------\n");
            }
            getch();
            break;///jumps out of case 2 

        case '3':  /// if user press 3 then do editing existing record
            system("cls");
            system("color a4");///changes background and font colour
            more = 'y';///sets to yes for the permission
            printf("                              MODIFICATION   OF   RECORD");
            printf("\n_________________________________________________________________________________\n");
            while(more == 'y')///loop runs only whem choice is yes
            {   
                printf("Enter the employee name to modify: ");
                scanf("%s", empname);///enters name whose data is to be modified
                printf("\n----------------------------------\n");
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)  /// fetch all record from file
                {
                    if(strcmp(e.name,empname) == 0)  ///if entered name matches with that in file
                    {
                        printf("\nEnter new name,age and basic salary:\n ");
                        printf("---------------------------------\n");
                        scanf("%s%d%f",e.name,&e.age,&e.bs);///modify record
                        printf("\n----------------------------------\n");
                        fseek(fp,-recsize,SEEK_CUR); /// move the cursor 1 step back from current position
                        fwrite(&e,recsize,1,fp); /// override the record
                        break;///jumps out of case3
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                more = getche();///input the choice for modifying more record
                printf("\n------------------------------------------------------------------------------\n");
            }
            break;///jumps out of the loop
        case '4':
        	system("color 65");///changes baclground and font colour
            system("cls");
            more = 'y';///sets permission to yes
            printf("                              DELETION  OF  RECORD");
            printf("\n__________________________________________________________________________________\n");
            while(more == 'y')
            {   
                printf("\nEnter name of employee to delete: ");
                scanf("%s",empname);///enter the name whose record is to be deleted
                printf("-------------------------------------\n");
                ft = fopen("Temp.dat","wb");  /// create a intermediate file for temporary storage
                rewind(fp); /// move record to starting of file
                while(fread(&e,recsize,1,fp) == 1)  /// read all records from file
                {
                    if(strcmp(e.name,empname) != 0)  /// if the entered record match
                    {
                        fwrite(&e,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                    }
                }
                fclose(fp);///close the file
                fclose(ft);
                remove("EMPLOYEE.DAT"); /// remove the orginal file
                rename("Temp.dat","EMPLOYEE.DAT"); /// rename the temp file to original file name
                fp = fopen("EMPLOYEE.DAT", "rb+");
                
                printf("Delete another record(y/n)");
                
                fflush(stdin);
                more = getche();///input permission to delete more records
                printf("\n------------------------------------------------------------------------------\n");
            }
            break;///jumps out of case 4
        case '5':
            fclose(fp);  /// close the file
            exit(0); /// exit from the program
        }
    }
    return 0;
}
