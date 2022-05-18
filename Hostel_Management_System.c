// call library and header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>



//declaring the function (untuk kemudahan code)
void menu();
void newstudents();
void close();
void edit();
void sorter();
void checker_students();
void delete_residents();
void view_residents();
bool digit_checker();



int mainexit;
// define the structures
struct{
    char name[30];
    char matricnumber[10];
    char email[30];
    char age[1000];
    int room_no;
    char phone[16];
    int month,day,year;
    char block_name[10];

}check,add,upd,sort; 

// to check if the user enter wrong input
bool digit_checker(char key[]){
    for(int i=0;i< strlen(key);i++){
        if(isdigit(key[i])==0){
            printf("\n----Wrong Input !! Please input an integer----\n");
            return false;
        }
    }
    return true;
}
// main screen
//********************************************************************************************
void menu(){
    system("clear");
        int user_choice;
        printf("\n\n\t\t**********************************************\n");
        printf("\t\t*                                            *\n");
        printf("\t\t*              +--------------+              *\n");
        printf("\t\t*              |    Hostel    |              *\n");
        printf("\t\t*              |  Management  |              *\n");
        printf("\t\t*              |    System    |              *\n");
        printf("\t\t*              +--------------+              *\n");
        printf("\t\t*                                            *\n");
        printf("\t\t**********************************************\n\n\n");

        printf("\n>>>>>>>>\tEnter Hostel Residents Details--> 1 \t\t\t<<<<<<<<");
        printf("\n>>>>>>>>\tUpdate Hostel Residents Details--> 2 \t\t\t<<<<<<<<");
        printf("\n>>>>>>>>\tResidents Hostel Personal Information Checker--> 3 \t<<<<<<<<");
        printf("\n>>>>>>>>\tList of Hostel Building--> 4 \t\t\t\t<<<<<<<<");
        printf("\n>>>>>>>>\tView All Residents --> 5 \t\t\t\t<<<<<<<<");
        printf("\n>>>>>>>>\tRemove Existing Residents's Information--> 6 \t\t<<<<<<<<");
        printf("\n>>>>>>>>\tExit The System--> 0 \t\t\t\t\t<<<<<<<<");
        printf("\n\n\t Enter Your Choice:");
        scanf("%d",&user_choice);
       

        if(user_choice == 1){
            newstudents();
        }
        else if(user_choice == 2){
            edit();
        }
        else if(user_choice == 3){
            checker_students(); // students information
        }
        else if(user_choice == 4){
            sorter(); // hostel punya
        }
        else if(user_choice == 5){
            view_residents();
        }
        else if(user_choice == 6){
            delete_residents();
        }
        else if(user_choice == 0){
            close();
        }
        else{
            printf("\n\n\t\t**Wrong Input --- Go Back to Main Menu**\n\n");
            menu();
        }
       

}
//********************************************************************************************
// new students
void newstudents(){
    system("clear");
    FILE *hosteldata,*block;

    hosteldata=fopen("hostel-record.dat","a+");
    matricnumber:
    

    printf("\n\t\t\t--------ADD RESIDENTS DATA-------\n");
    printf("\nEnter Matric Number :");
    scanf("%s",check.matricnumber);
    // check sama dah ada data lum
  
    while (fscanf(hosteldata,"%s %s %d/%d/%d %s %s %s %s %d\n", add.matricnumber,add.name, &add.day, &add.month, &add.year, add.age, add.phone, add.email, add.block_name, &add.room_no)!=EOF)
    {
        if (strcmp(check.matricnumber,add.matricnumber)==0) {
           
        
        }
        printf("\t\t----These Matric Number already be used!----\n");
        goto matricnumber;
    }     
       
     strcpy(add.matricnumber,check.matricnumber);
    printf("\nEnter The Name: ");
    scanf("%s",add.name);
    printf("\nEnter The Date of Birth (Format: dd/mm/yyyy): ");
    scanf("%d/%d/%d",&add.day,&add.month,&add.year);
    do{
        printf("\nEnter The Age : ");
        scanf("%s",add.age);}
    while (!digit_checker(add.age));
    printf("\nEnter The Phone Number (Example : 60179811234): ");
    scanf("%s",add.phone);
    printf("\nEnter The Email :");
    scanf("%s",add.email);
    printf("\nEnter The Block Name (A-1, A-2): ");
    scanf("%s",add.block_name);
    printf("\nEnter The Room Number(Example : 1-300):");
    scanf("%d",&add.room_no); 
    
    fprintf(hosteldata,"%s %s %d/%d/%d %s %s %s %s %d\n",add.matricnumber,add.name, add.day, add.month, add.year, add.age, add.phone, add.email, add.block_name, add.room_no);
    
    // add resident new id to block list
    if(strcmp(add.block_name,"A-1")==0)
    {
        block=fopen("A-1.dat","a+");
        fprintf(block, "%s\n",add.matricnumber);
        fclose(block);
    }
    else if(strcmp(add.block_name,"A-2")==0)
    {
        block=fopen("A-2.dat","a+");
        fprintf(block, "%s\n",add.matricnumber);
        fclose(block);
    }
    
    fclose(hosteldata);

    printf("\n\t\t\t----Resident Added Successfully!----");
    add_invalid:
    printf("\n\n\tEnter New Resident -->1\n\n\tBack to Main Menu -->2\n\n\t Exit Program -->0 \n");
    printf("\n\n\tEnter Your Choice :");
    scanf("%d",&mainexit);

    if(mainexit==1){
        newstudents();
    }
    else if (mainexit==2){
        menu();
    }
    else if(mainexit==0){
        close();
    }
    else{
        printf("\n\t\t\t\t     ----Invalid Input!----\n");
        goto add_invalid;
    }
}

//********************************************************************************************
//edit resident information
void edit(){
    system("clear");
    int user_choice,test_record=0;  // nak periksa maklumat yang sudah
    FILE *hosteldata,*new;
    hosteldata=fopen("hostel-record.dat","r");
    new=fopen("new.dat","w");

    printf("\n\t\t\t--------UPDATE RESIDENTS INFORMATION-------\n");
    printf("\nEnter the matric number of the students :");
    scanf("%s",check.matricnumber);

    while (fscanf(hosteldata,"%s %s %d/%d/%d %s %s %s %s %d\n",  add.matricnumber,add.name, &add.day, &add.month, &add.year, add.age, add.phone, add.email, add.block_name, &add.room_no)!=EOF)

    {     

         if(strcmp(add.matricnumber,check.matricnumber)==0){
             matric_user:
             test_record=1;
             printf("\nWhich data you want to change ?\n\tRoom No.-> 1\n\tPhone -> 2\n\tEmail -> 3\n\tCancel edit -> 4\n");
             printf("\n\tEnter Your Choice : ");
             scanf("%d", &user_choice);

             if(user_choice==1){
                printf("Enter new room no. : ");
                scanf("%d",&check.room_no);
                fprintf(new,"%s %s %d/%d/%d %s %s %s %s %d\n",add.matricnumber,add.name, add.day, add.month, add.year, add.age, add.phone, add.email, add.block_name, check.room_no);
                printf("\n\t\t\t----Change Successful and Saved!----\n");

             }
             else if(user_choice==2){
                 printf("Enter the new phone number : ");
                 scanf("%s",check.phone);
                 fprintf(new,"%s %s %d/%d/%d %s %s %s %s %d\n",add.matricnumber,add.name, add.day, add.month, add.year, add.age, check.phone, add.email, add.block_name, add.room_no);
                 printf("\n\t\t\t----Change Successful and Saved!----\n");
             }
             else if(user_choice==3){
                 printf("Enter the new email : ");
                 scanf("%s",check.email);
                 fprintf(new,"%s %s %d/%d/%d %s %s %s %s %d\n",add.matricnumber,add.name, add.day, add.month, add.year, add.age, add.phone, check.email, add.block_name, add.room_no);
                 printf("\n\t\t\t----Change Successful and Saved!----\n");
                 
             }
             else if(user_choice==4){
                 goto cancel_edit;
             }
             else{
                 printf("\n\n\t\t\t----Sorry!! Please enter the available options----\n");
                 goto matric_user;
             }
             
         }
         else{
             cancel_edit:
             fprintf(new,"%s %s %d/%d/%d %s %s %s %s %d\n",add.matricnumber,add.name, add.day, add.month, add.year, add.age, add.phone, add.email, add.block_name, add.room_no);
         }
            
    }
    fclose(hosteldata);
    fclose(new);
    remove("hostel-record.dat");
    rename("new.dat","hostel-record.dat");

                    if(test_record!=1)
                        printf("\n\t\t\t  ----The matric number was not found!----\a\a\a\n");
                    
                    edit_invalid:
                    printf("\n\tEdit other information -> 1\n\tReturn to Main Menu -> 2\n\tExit Program ->0\n");
                    printf("\n\n\tEnter Your Choice :");
                    scanf("%d",&mainexit);
                    if(mainexit==1){
                        edit();
                    }
                    else if(mainexit==2){
                        menu();
                    }
                    else if(mainexit==0){
                        close();
                    }
                    else{
                        printf("\n\t\t\t\t     ----Invalid Input!----\n");
                        goto edit_invalid;
                    }

}
//********************************************************************************************
// end program
void close(){
    system("clear");
     printf("\n\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t\t(  *       *        *         *        *     )\n");
        printf("\t\t)              +--------------+       BYE    (\n");
        printf("\t\t(      *       |   Closing    |    *         )\n");
        printf("\t\t)     BYE      |     The      |           *  (\n");
        printf("\t\t(    *     *   |    System    |      *       )\n");
        printf("\t\t)              +--------------+        *     (\n");
        printf("\t\t(       *        *        *       * BYE    * )\n");
        printf("\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
        exit(0);

}
//********************************************************************************************
// sortlist-hostel program
void sorter()
{
    system("clear");
    int choice,test=0;

    printf("\n\t\t\t--------LIST OF RESIDENTS FOR EVERY BLOCK-------\n");
    choice:
    printf("Select any number (1 or 2):\n\n\t\tPick 1 for Block A-1 \n\t\tPick 2 for Block A-2\n\n");
    printf("Enter here: ");
    scanf("%d",&choice);
    printf("\n");
    FILE *fp, *block;
    
        if  (choice == 1)
            block=fopen("A-1.dat","a+");
        else if(choice == 2)
            block=fopen("A-2.dat","a+");
        else{
            printf("\n\t\t\t----Sorry!! Please enter the available options----\n\n");
            goto choice;
        } 


    while(fscanf(block,"%s\n",check.matricnumber)!=EOF)
    {
        fp=fopen("hostel-record.dat","r");
        while(fscanf(fp,"%s %s %d/%d/%d %s %s %s %s %d\n",  sort.matricnumber,sort.name, &sort.day, &sort.month, &sort.year, sort.age, sort.phone, sort.email, sort.block_name, &sort.room_no)!=EOF)
        {
            if(strcmp(check.matricnumber,sort.matricnumber)==0)
            {
                
                if(test==1)
                {
                    printf("Following is the list of residents in the selected Block:\n");
		            printf("\n\tMATRIC NO.\t   NAME\t\tAGE\tROOM NO.\tEMAIL\t\t\tPHONE No.\n");

                }
                printf("\n\t%8s\t%8s\t%s\t%d\t\t%s\t\t%10s", sort.matricnumber,sort.name, sort.age, sort.room_no, sort.email, sort.phone);
           		test++;
            }
        }
        fclose(fp);
    }
    fclose(block);

    if (test==0){
        printf("\n\t\t\t\t      ----NO RECORDS!!----\n");

    }
            

    sorter_invalid:
    printf("\n\t\tWatch other information -> 1\n\t\tReturn to Main Menu -> 2\n\t\tExit Program ->0\n");
    printf("\n\n\t\tEnter Your Choice :");
    scanf("%d",&mainexit);

    if  (mainexit ==1){
        sorter();
    }
    else if(mainexit==2){
        menu();
    }
    else if(mainexit==0){
        close();
    }
    else{
        printf("\n\t\t\t\t     ----Invalid Input!----\n");
        goto sorter_invalid;
    }


}
//********************************************************************************************
// checker students informattion program
void checker_students()
{
    system("clear");
    FILE *view;
    view=fopen("hostel-record.dat","r"); 
    int test=0;

    //try_again:
    printf("\n\t\t\t--------RESIDENTS PERSONAL INFORMATION CHECKER-------\n");
    printf("\nEnter the matric number of the resident : ");
    scanf("%s",check.matricnumber);

    printf("\nMATRIC NO.\t\tNAME\t\tPHONE\t\tEMAIL\t\t\tAGE\t\tBIRTHDAY\t\tBLOCK\t\tROOM NO.\n");

    while(fscanf(view,"%s %s %d/%d/%d %s %s %s %s %d",  add.matricnumber,add.name, &add.day, &add.month, &add.year, add.age, add.phone, add.email, add.block_name, &add.room_no)!=EOF)
        {
            if(strcmp(add.matricnumber,check.matricnumber)==0){
                printf("\n%8s\t   %10s\t\t%10s\t%10s\t\t%s\t\t%d/%d/%d\t\t%s\t\t%d\n",add.matricnumber,add.name,add.phone,add.email,add.age,add.day,add.month,add.year, add.block_name, add.room_no);
                test++;
            }
            
            
        }
    fclose(view);

    if (test==0)
        {   
            printf("\n\t\t\t\t\t\t\t      ----NO RECORDS!!----\n");}

    check_invalid:
    printf("\n\tCheck other resident -> 1\n\tReturn to Main Menu -> 2\n\tExit Program ->0\n");
    printf("\n\n\tEnter Your Choice : ");
    scanf("%d",&mainexit);

    if(mainexit==1){
        checker_students();
    }
    else if(mainexit==2){
        menu();
    }
    else if(mainexit==0){
        close();
    }
    else{
    printf("\n\t\t\t\t     ----Invalid Input!----\n");
        goto check_invalid;
    }
}
//********************************************************************************************
// delete students informattion program
void delete_residents()
{
	system("clear");
   FILE *hosteldata,*new,*copy,*read,*block,*block1;
    //view=fopen("hostel-record.dat","r");
    int test_record,user_choice=0;
    hosteldata=fopen("hostel-record.dat","r");
    new=fopen("new.dat","w");
    char c;
    
    printf("\n\t\t\t--------DELETE RESIDENT DATA-------\n");
    printf("Enter the matric number of student :");
    scanf("%s",check.matricnumber);
    while (fscanf(hosteldata,"%s %s %d/%d/%d %s %s %s %s %d\n",  add.matricnumber,add.name, &add.day, &add.month, &add.year, add.age, add.phone, add.email, add.block_name, &add.room_no)!=EOF)
   {
        if(strcmp(add.matricnumber,check.matricnumber)==0){
            
            printf("\nMATRIC NO.\t\t\tNAME\t\t\tPHONE\t\tEMAIL\t\tBIRTHDAY\n");
            printf("\n%8s\t\t%10s\t\t%10s\t\t%10s\t%d/%d/%d\n",add.matricnumber,add.name,add.phone,add.email,add.day,add.month,add.year);
            matric_user:
            printf("\n\n\tAre you sure want to delete?\n\tYes -> 1\n\tNo ->2\n");
            printf("\n\tEnter Your Choice : ");
            scanf("%d", &user_choice);

            if(user_choice==1){  
            test_record=1;
            printf("\nRecord deleted successfully\n");
            
            }
            else if(user_choice==2){
                test_record=1;
                cancel_just_join:
                
            }
            else{
                printf("\n\n\t\t\t----Sorry!! Please enter the available options----\n");
                
                 goto matric_user;
            }
        }
        else{
            cancel_just_join:
            fprintf(new,"%s %s %d/%d/%d %s %s %s %s %d\n",add.matricnumber,add.name, add.day, add.month, add.year, add.age, add.phone, add.email, add.block_name, add.room_no);
        }
       
    
    }
    
    fclose(hosteldata);
    fclose(new);
    remove("hostel-record.dat");
    rename("new.dat","hostel-record.dat");
    remove("A-2.dat");
    remove("A-1.dat");

    copy=fopen("hostel-record.dat","r");
    
    while (fscanf(copy,"%s %s %d/%d/%d %s %s %s %s %d\n",  add.matricnumber,add.name, &add.day, &add.month, &add.year, add.age, add.phone, add.email, add.block_name, &add.room_no)!=EOF){

        if(strcmp(add.block_name,"A-1")==0)
    {
        block=fopen("A-1.dat","a+");
        fprintf(block, "%s\n",add.matricnumber);
        fclose(block);
        
    }
    else if(strcmp(add.block_name,"A-2")==0)
    {
        block1=fopen("A-2.dat","a+");
        fprintf(block1, "%s\n",add.matricnumber);
        fclose(block1);
    }

    }
    fclose(copy);
 
    if(test_record!=1)
	printf("\n\t\t\t----The matric number not found!!----\a\a\a\n");

    delete_residents_invalid:
    printf("\n\t\tDelete other information -> 1\n\t\tReturn to Main Menu -> 2\n\t\tExit Program ->0\n");
    printf("\n\n\t\tEnter Your Choice :");
    scanf("%d",&mainexit);

    if  (mainexit ==1){
        delete_residents();
    }
    else if(mainexit==2){
        menu();
    }
    else if(mainexit==0){
        close();
    }
        {	
        	printf("\n\t\t\t\t     ----Invalid Input!----\n");
            goto delete_residents_invalid;
		}
}
//********************************************************************************************
// view residents
void view_residents()
{
    //function to display all students of a hostel 
    system("clear");
    FILE *view;
    view=fopen("hostel-record.dat","r");
    int test_record=0;

    printf("\n\t\t\t--------ALL RESIDENTS INFORMATION-------\n");
    printf("\nMATRIC NO.\tNAME\t\tBLOCK\t\tROOM NO.\t\tPHONE\n");

    while(fscanf(view,"%s %s %d/%d/%d %s %s %s %s %d\n",add.matricnumber,add.name, &add.day, &add.month, &add.year, add.age, add.phone, add.email, add.block_name, &add.room_no)!=EOF)
       {
           printf("\n%s\t\t%s\t\t%s\t\t %d\t\t\t %s",add.matricnumber,add.name,add.block_name,add.room_no,add.phone);
           test_record++;
       }
    fclose(view);
    
    if (test_record==0)
        {   
            printf("\n\t\t\t       ----NO RECORDS!!----\n");}

    view_residents_invalid:
    printf("\n\n\n\t\tReturn to Main Menu -> 1\n\t\tExit Program ->0\n");
    printf("\n\n\t\tEnter Your Choice :");
    scanf("%d",&mainexit);

    if  (mainexit ==1){
        menu();
    }
    else if(mainexit==0){
        close();
    }
    else  {	
        	printf("\n\t\t\t\t     ----Invalid Input!----\n");
            goto view_residents_invalid;
		}

}

//********************************************************************************************
// run the program
int main(){
    system("clear");
    menu();
    exit (0);
}