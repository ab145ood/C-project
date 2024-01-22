#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <conio.h>

#define MAX_Entity 100
#define MAX_Name 50
#define MAX_ID 10
#define MAX_grade 4

struct student
{
    char name[MAX_Name];
    char id[MAX_ID];
    char grade[MAX_grade];
    int checks;
    char firstletter;
};


unsigned int mID = 7;

FILE *data; // the file to store and read data

// Prototype
void display_student_submenu();
void display_menu();
int add_student(struct student s[]);
int update_student(struct student s[]);
int delete_student(struct student s[]);
void display_all_students(struct student s[]);
int search_by_id(struct student s[]);
int check_validID(struct student s[]);
int check_validGrade(struct student s[]);
int check_validName(struct student s[]);
void openFile();
int readFile(struct student s[]);
void saveToFIle(struct student s[]);
void init(struct student s[]);

int main()
{
    struct student students[MAX_Entity];
    init(students);
    readFile(students);
    int repeat = 1;
    int submenu_choice, choice;

    while (repeat == 1)
    {
        display_menu();
        scanf(" %d", &choice);
        while (fgetc(stdin) != '\n')
            ; // Clear any extra input from the input buffer

        if (choice == 0)
            continue;

        switch (choice)
        {
        case 1:
            do
            {
                display_student_submenu();
                scanf("%d", &submenu_choice);
                while (fgetc(stdin) != '\n')
                    ; // Clear any extra input from the input buffer

                if (submenu_choice == 0)
                    continue;

                switch (submenu_choice)
                {
                case 1:
                    add_student(students);
                    break;
                case 2:
                    update_student(students);

                    break;
                case 3:
                    delete_student(students);
                    break;
                case 4:
                    display_all_students(students);
                    break;
                case 5:
                    repeat = search_by_id(students);
                    break;
                case 6:
                    break;
                default:
                    printf("\t\t*** Wrong Choice ***\n");
                }
            } while (submenu_choice != 6);
            break;

        case 2:
            // prompt user to enter new id length
            printf("\t\tEnter new ID length from 1 to 9:");
            scanf(" %u", &mID);
            while (fgetc(stdin) != '\n')
                ; // Clear any extra input from the input buffer
            break;

        case 3:
            printf("\t\t*** Goodbye *** \n");
            repeat = 0;
            break;

        default:
            printf("\t\t*** Wrong Choice ***\n");
        }
    }

    return 0;
}

void display_menu()
{
    printf("\n\t\t>>>>>>> Student Management System <<<<<<<\n");
    printf("%40s", "Main Menu\n");
    printf("\t\t\t====================\n\t\t\t[1] - Students.\n");
    printf("\t\t\t[2] - Change ID length.\n");
    printf("\t\t\t[3] - Exit.\n\t\t\t====================\n");
    printf("\t\t\tEnter your choice:");
}

void display_student_submenu()
{
    printf("\n\n");
    printf("%45s", ">>>>>>STUDENTS<<<<<<\n");
    printf("\t\t\t====================\n\t\t\t[1]- Add Student\n");
    printf("\t\t\t[2]- Update Student\n");
    printf("\t\t\t[3]- Delete Student\n");
    printf("\t\t\t[4]- Display All Students\n");
    printf("\t\t\t[5]- Search by ID/Number\n");
    printf("\t\t\t[6]- Back\n\t\t\t====================\n");
    printf("\t\t\tEnter your choice: ");
}

int add_student(struct student students[])
{
    printf("\n\t\t####################### Add Student #######################\n");
    int choice = 0, sign = false, index;
    size_t lenn, leni, leng, strcsn, strcsi, strcsg; // len(length) for each input same with strcs

    // Display rules for entering student information
    printf("\t\tSTUDENT INFO RULES!\n\t\t+++++++++++++++++++++++++++\n");
    sleep(1);
    printf("\t\tFULL NAME MUST BE LESS THAN 50 LETTERS AND MORE THAN 8!\n");
    sleep(1);
    printf("\t\tID MUST BE %d DIGITS!(changable)\n", mID);
    sleep(1);
    printf("\t\tGRADE MUST BE FROM 0 TO 100 AND ROUNDED TO THE NEAREST INTEGER!\n");
    sleep(1);
    printf("\t\t++++++++++++++++++++++++++\n");

    for (index = 0; index < MAX_Entity; index++)
    {
        if (students[index].checks == 0)
        {
            while (!sign)
            {
                // prompt user to enter full name and validate it
                printf("%s", "\t\tEnter Student Full Name:");
                fgets(students[index].name, MAX_Name, stdin);          
                sign = check_validName(names[index]); // function return true if valid or false if not
                lenn = strlen(names[index]);
                strcsn = strcspn(names[index], "\n");
                names[index][strcsn] = '\0';        // clearing \n
                if (lenn >= 49) // if true means there is extra character in input buffer
                    while (fgetc(stdin) != '\n')
                        ; // to clear extra character in input buffer
                if (sign == false)
                {
                    continue; // name not valid
                }
                else
                    break;
            }

            sign = false; // to enter next loop

            // Prompt user to enter student's ID and validate it
            while (!sign)
            {
                printf("%s", "\t\tEnter Student ID :");
                fgets(ids[index], MAX_ID, stdin);
                strcsi = strcspn(ids[index], "\n");
                ids[index][strcsi] = '\0';        // clearing \n
                sign = check_validID(ids[index]); // function return true if valid or false if not
                leni = strlen(ids[index]);
                if (leni >= 9) // if true means there is extra character in input buffer
                    while (fgetc(stdin) != '\n')
                        ; // to clear extra character in input buffer  // NOLINT
                if (sign == false)
                {
                    continue; // id not valid
                }
                else
                    break;
            }

            sign = false; // to enter next loop

            // Prompt user to enter student's grade and validate it
            while (!sign)
            {
                printf("%s", "\t\t  Enter Student Grade :");
                fgets(grades[index], MAX_grade, stdin);
                strcsg = strcspn(grades[index], "\n");
                grades[index][strcsg] = '\0';           // clearing \n
                sign = check_validGrade(grades[index]); // function return true if valid or false if not
                leng = strlen(grades[index]);
                if (leng >= 3) // if true means there is extra character in input buffer
                    while (fgetc(stdin) != '\n')
                        ; // to clear extra character in input buffer
                if (sign == false)
                {
                    continue; // grade not valid
                }
                else
                    break;
            }

            number[index] = index + 1; // index starts from 0 but student number start from 1
            sign = false;              // to enter next loop

            // Ask user if they want to continue adding students or exit
            while (!sign)
            {
                printf("%s", "\n\t\tDo you wish to continue?\n\t\t 1 for Yes\n\t\t 0 for No \n\t\t :");
                scanf(" %d", &choice);
                while (fgetc(stdin) != '\n')
                    ; // to clear extra character in input buffer
                if (choice == 1)
                    break;
                else if (choice == 0)
                {
                    saveToFIle();
                    return true;
                }
                else
                {
                    printf("\t\tInvalid choice");
                    continue;
                }
            }
        }
        else if (index == MAX_Entity - 1)
        {
            printf("\t\tNo more students storing capabilities");
            break;
        }
    }
}

int update_student(struct student s)
{
    printf("\t\t####################### Update Student #######################\n");
    int index = search_by_id(); // function return index for student if found
    int choice;
    char new[50];
    if (index == -1)
    {
        return false; // -1 means student not found so return false
    }
    else
    {
        size_t strcs;
        int breaker = 0;
        do
        {
            // prompt user to choose which attribute to change
            printf("\t\twhat do you want to change ?\n\t\t [1]-ID\n\t\t [2]-Name\n\t\t [3]-Grade\n\t\t Select number:");
            scanf("%d", &choice);
            while (fgetc(stdin) != '\n')
                ; // to clear extra character in input buffer

            switch (choice)
            {
            case 1:
                while (!breaker)
                {
                    printf("\t\tEnter new ID:"); // prompt user to enter new name
                    fgets(new, MAX_ID, stdin);
                    strcs = strcspn(new, "\n");
                    new[strcs] = '\0'; // to clear \n
                    if (strlen(new) >= 7)
                    {
                        while (fgetc(stdin) != '\n')
                            ; // to clear extra character in input buffer
                    }
                    breaker = check_validID(new); // function return true if valid or false if not
                    if (breaker == false)
                    {
                        break;
                    }
                    else
                    {
                        strcpy(, new); // replace old string
                    }
                    break;
                }
                break;

            case 2:
                // prompt user to enter new name
                while (!breaker)
                {
                    printf("\t\tEnter new Name:");
                    fgets(new, MAX_Name, stdin);
                    strcs = strcspn(new, "\n");
                    new[strcs] = '\0'; // to clear \n
                    if (strlen(new) >= 49)
                    { // if true means there is extra character in input buffer
                        while (fgetc(stdin) != '\n')
                            ; // to clear extra character in input buffer
                    }
                    breaker = check_validName(new); // function return true if valid or false if not
                    if (breaker == false)
                    {
                        break; // name not valid
                    }
                    else
                    {
                        strcpy(names[index], new); // replace old string
                    }
                    break;
                }
                break;

            case 3:
                // prompt user to enter new grade
                while (!breaker)
                {
                    printf("\t\tEnter new Grade:");
                    fgets(new, MAX_grade, stdin);
                    strcs = strcspn(new, "\n");
                    new[strcs] = '\0'; // to clear \n
                    if (strlen(new) >= 3)
                    { // if true means there is extra character in input buffer
                        while (fgetc(stdin) != '\n')
                            ; // to clear extra character in input buffer
                    }
                    breaker = check_validGrade(new);
                    if (breaker == false)
                    {
                        break; // grade not valid
                    }
                    else
                    {
                        strcpy(grades[index], new); // replace old string
                    }
                    break;
                }
                break;

            default:
                printf("\t\tWrong choice!\n");
                break;
            }
        } while (breaker == false);

        fclose(fopen("data.txt", "w")); // to clear file
        for (int i = 0; i < MAX_Entity; i++)
        {
            checks[i] = 0; // mark every entity as not written in file
        }
        saveToFIle();
    }
}

int delete_student(struct student s)
{
    printf("\t\t####################### Delete Student #######################\n");
    int index, temp, choice;
    index = search_by_id(); // function return student index if found or -1 if not
    if (index == -1)
        return false; //-1 means student not found
    else
    {
        // ask user if this student is the one they are looking for
        while (true)
        {
            printf("\t\tAre you sure you want to delete this student ?\n\t\t1/yes \n\t\t0/no");
            scanf("%d", &choice);
            while (fgetc(stdin) != '\n')
                ; // to clear extra character in input buffer
            if (choice == 1 || choice == 0)
                break;
            else
            {
                printf("\t\tInvalid choice\n");
            }
        }
        if (!choice)
            return false; // if false means 0
        // initializing the student to null
        names[index][0] = '\0';
        ids[index][0] = '\0';
        grades[index][0] = '\0';
        for (; index < MAX_Entity; index++)
        {
            if (number[index + 1] == 0 && index != MAX_Entity - 1)
            {
                number[index] = 0; // if no more students make the current student null then break
                names[index][0] = '\0';
                ids[index][0] = '\0';
                grades[index][0] = '\0';
                break;
            }
            names[index][0] = '\0'; // make student null to change with next student
            ids[index][0] = '\0';
            grades[index][0] = '\0';
            strcpy(names[index], names[index + 1]); // copying the next student to the current student
            strcpy(ids[index], ids[index + 1]);
            strcpy(grades[index], grades[index + 1]);
            number[index + 1] -= 1; // replacing deleted student number in array to the next student
            temp = number[index];
            number[index] = number[index + 1];
            number[index + 1] = temp;
            for (size_t i = strlen(names[index]); i > 0; i--)
            {
                if (!isalpha(names[index][i]))
                {
                    names[index][i] = '\0'; // to clear extra space characters that comes after copying
                }
            }
        }
        printf("\t\t Student Deleted!!\n");
        fclose(fopen("data.txt", "w")); // to clear file
        for (int i = 0; i < MAX_Entity; i++)
        {
            checks[i] = 0; // to mark every student as not written in file
        }
        saveToFIle();
    }
}

void display_all_students(struct student s)
{
    printf("\t\t############## Display All Students ##################\n");
    printf("\t\tNumber | ID      | Grade | Name\n");
    for (int i = 0; i < MAX_Entity; i++)
    {
        if (number[i] == 0)
            break; // if number 0 means no more students
        else
        {
            printf("\t\t%2d     | %7s | %3s   | %s\n", number[i], ids[i], grades[i], names[i]);
        }
    }
}

int search_by_id(students->name, students->id, students->grade, students->checks, students->firstletter)
{
    printf("\n\t\t~~~~~~~~~~~~~~~~~~~~~ Search by ID/Number ~~~~~~~~~~~~~~~~~~~~~\n");
    char aid[MAX_ID], snum[4]; // the id the user enter will be stored here
    int num, choice;
    bool breaker = 0;
    int sign = 2, index;
    size_t len;
    while (!breaker)
    {
        // prompt user to chose what to search by
        printf("\t\tDo you wish to search by id or student number\n\t\t1:ID\n\t\t2:number\n\t\t:");
        scanf("%d", &choice);
        while (fgetc(stdin) != '\n')
            ; // to clear extra input in input buffer
        switch (choice)
        {
        case 1:
            while (!breaker)
            {
                printf("%s", "\n\t\tEnter ID to search :");
                fgets(aid, MAX_ID, stdin);
                size_t strc;
                strc = strcspn(aid, "\n");
                aid[strc] = '\0'; // to make \n = \0
                len = strlen(aid);
                if (len >= 9)
                    while (fgetc(stdin) != '\n')
                        ;                  // to get clear extra characters in input buffer
                sign = check_validID(aid); // function return true if valid or false if not
                if (sign == 0)
                    continue;
                else
                {
                    for (index = 0; index < MAX_Entity; index++)
                    {
                        sign = strcmp(aid, ids[index]); // strcmp compares the strings and return 0 if identical
                        if (sign == 0)
                        {
                            printf("\t\t    Student Found !\n");
                            printf("\t\tNumber | ID      | Grade | Name\n");
                            printf("\t\t%2d     | %7s | %3s   | %s\n", number[index], ids[index], grades[index],
                                   names[index]);
                            return index; // to use the index of found student
                        }
                    }
                    // ask the user if they want to try again
                    breaker = 1;
                    while (breaker == 1)
                    {
                        printf("\t\tStudnet not found do you wish to try again ? 1/yes , 0/no");
                        int choice;
                        scanf("%d", &choice);
                        while (fgetc(stdin) != '\n')
                            ; // to clear extra character in input buffer
                        switch (choice)
                        {
                        case 0:
                            return -1; // to know there is no student
                        case 1:
                            breaker = 0;
                            break;
                        default:
                            printf("\t\tInvalid input\n");
                        }
                    }
                }
            }
        case 2:
            while (!breaker)
            {
                printf("\t\tEnter Student Number:");
                fgets(snum, 3, stdin); // store in string first to validate the input
                int strc;
                strc = strcspn(snum, "\n");
                snum[strc] = '\0'; // to make \n = \0
                len = strlen(snum);
                if (len >= 2)
                    while (fgetc(stdin) != '\n')
                        ; // to get clear extra characters in input buffer
                size_t i;
                for (i = 0; i < len; i++)
                {
                    if (!isdigit(snum[i]))
                    {
                        printf("\t\t  number must be from 0 to 100 \n");
                        sign = 0; // to know to loop
                        break;
                    }
                    else if (i == len - 1)        // means it is the last loop
                        num = strtof(snum, NULL); // to compare to student number
                }
                if (sign == 0)
                    continue;

                if (num > 0 && num <= 100)
                {
                    for (index = 0; index < MAX_Entity; index++)
                    {
                        if (number[index] == 0)
                        {
                            break; // if true means no more students
                        }
                        else if (number[index] == num)
                        {
                            printf("\t\t    Student Found !\n");
                            printf("\t\tNumber | ID      | Grade | Name\n");
                            printf("\t\t%2d     | %7s | %3s   | %s\n", number[index], ids[index], grades[index],
                                   names[index]);
                            return index; // to use the index of found student
                        }
                    }
                    while (!breaker)
                    {
                        printf("\t\tStudent not found !\n\t\tDo you wish to try again ?\n\t\t1:yes\n\t\t0:no\n\t\t:");
                        int ans;
                        scanf("%d", &ans);
                        while (fgetc(stdin) != '\n')
                            ; // to clear extra input in input buffer
                        if (ans == 1)
                        {
                            sign = 1; // to know to loop
                            break;
                        }
                        else if (ans == 0)
                        {
                            return -1; // means no found
                        }
                        else
                        {
                            printf("\t\tInvalid choice!\n");
                        }
                    }
                    if (sign == 1)
                        break;
                }
                else
                {
                    printf("\t\tNumber must be from 0 to 100\n");
                    continue;
                }
            }
        default:
            printf("\t\tInvalid choice");
            continue;
        }
    }
}
int check_validID(struct student s)
{
    size_t index;
    for (index = 0; index < strlen(id); index++)
    {
        if (strlen(id) == mID)
        { // length of id must be equal to mID
            if (!isdigit(id[index]))
            {
                printf("\t\t  ID must be %d digits\n", mID);
                return false;
            }
        }
        else
        {
            printf("\t\t  ID must be %d digits\n", mID);
            return false;
        }
    }
    return true;
}

int check_validGrade(char grade[])
{
    unsigned int index;
    float ngrade;
    size_t len;
    len = strlen(grade);
    ngrade = strtof(grade, NULL);
    for (index = 0; index < len; index++)
    {
        if (ngrade <= 100 && ngrade >= 0)
        {
            if (grade[index] == '\0')
                break;
            if (!isdigit(grade[index]))
            {
                printf("\t\tGrade must be DIGITS\n");
                return false;
            }
        }
        else
        {
            printf("\t\tGrade must be from 0 to 100\n");
            return false;
        }
    }
    return true;
}

int check_validName(struct student s)
{
    size_t index, len;
    len = strlen(name);
    if (len < 8)
    {
        printf("%s", "\t\tNAME MUST BE AT LEAST 8 LETTERS!!\n");
        return false;
    }

    for (index = 0; index < len; index++)
    {
        if (!isalpha(name[index]) && !isspace(name[index]) && name[index] != '\0')
        {
            printf("%s", "\t\tNAME MUST BE LETTERS!!\n");
            return false;
        }
        else
        {
            continue;
        }
    }
    return true;
}
void openFile()
{ // NOLINT
    data = fopen("data.txt", "a+");
    // fopen return null when error
    if (data == NULL)
    {
        printf("Error");
        exit(1);
    }
}
// to read data from file
int readFile(struct student s)
{
    int j;
    openFile();
    // loop to scan every line in file and store at array[i]
    for (int i = 0; i < MAX_Entity; i++)
    {
        // cppcheck-suppress invalidscanf
        j = fscanf(data, "%d | %s | %50[^|] | %s ", &number[i], ids[i], names[i], grades[i]);
        //%50[^|] this means to read upto 50 characters until you meet "|"
        if (j == -1)
        {
            break;
        }
        else if (j == 4)
        {
            checks[i] = 1; // to mark as written in file
        }
        else
            printf("Error reading from file Line number %d", i);
    }
    fclose(data);
    return 0;
}
// to save in file
void saveToFIle(struct student s)
{
    int fpri;
    printf("\t\t*** Saving to file.... ***\n");
    openFile();
    for (int i = 0; i < MAX_Entity; i++)
    {
        // if first letter from name is null then there is no more student
        if (number[i] == 0)
        {
            printf("\t\tSaved successfully\n");
            fclose(data);
            return;
        }
        // if checks = 1 it means student is already in file
        if (checks[i] == 1)
        {
            continue;
        }
        fpri = fprintf(data, "\n%d  | %s | %s | %s", number[i], ids[i], names[i], grades[i]);

        if (fpri < 0) // fprintf return negative number when error
            printf("Failed to print student %d\n", number[i]);
        checks[i] = 1;
    }
}
// to initialize all arrays to null in start of program
void init(struct student s)
{
    for (int i = 0; i < MAX_Entity; i++)
    {
        names[i][0] = '\0';
        ids[i][0] = '\0';
        grades[i][0] = '\0';
        number[i] = 0;
        checks[i] = 0;
    }
}
