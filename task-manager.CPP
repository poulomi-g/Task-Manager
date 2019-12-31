
//Header Files used
#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>



//Classes used

class date{
    public:
    int dateNum;
    int dateMonth;
};

//Task system class
class taskSystem{
    date due;
    date assigned;
    char personAssigned[30];
    char taskAssigned[150];
    char status[20];
    int taskKey;

public:

    //Function for accepting records
    void getData(){
	cout<<"\n\nEnter special task key for new task: ";
	cin>>taskKey;
    cout<<endl;
	cout<<"\nTask to be assigned to: ";
	gets(personAssigned);
    cout<<endl;
	cout<<"Task to be assigned: ";
	gets(taskAssigned);
    cout<<endl;
	cout<<"Date due (DD/MM)\nDate: ";
	cin>>due.dateNum;
	cout<<"Month: ";
	cin>>due.dateMonth;
    cout<<endl;
	cout<<"Date assigned(DD/MM)\nDate: ";
	cin>>assigned.dateNum;
	cout<<"Month: ";
	cin>>assigned.dateMonth;
	strcpy(status,"UNDONE");
    cout<<endl;
	cout<<"\n\nDATA LOGGED.";
    }

    //Function for displaying records
    void putData(){
	cout<<"\nAssigned to: ";
	puts(personAssigned);
	cout<<"\t\t\tCURRENT STATUS: ";
	puts(status);
	cout<<"\nTask: ";
	puts(taskAssigned);
	cout<<"\nTASK KEY: "<<taskKey;
	cout<<"\t\tDue date: "<<due.dateNum<<" / "<<due.dateMonth;
	cout<<"\t\tDate assigned: "<<assigned.dateNum<<" / "<<assigned.dateMonth<<endl;
    }

    //Functions for returning private data values
    int returnKey(){
	       return taskKey;
    }

    char* returnName(){
	       return personAssigned;
    }

    char* returnStatus(){
	       return status;
    }

    //Function for modifying status
    void newStatus(char* newStat){
	       strcpy(status, newStat);
    }

};

//Object declarations
taskSystem t, t1;
fstream fs, temp;


//Function prototypes
void loginMenu();
void employeeMenu();
void employerMenu();

//Main Welcome Screen
void menuScreen(){


	do{
    	clrscr();

    	cout<<"\n\n\n\n\n\n\t\tWelcome to TASK MANAGER v1.0. Choose your designation: \n\n\t\t\t1.Employer\n\t\t\t2.Employee\n\t\t\t3.Quit\n";

    	int choice;
    	cout<<"\n\t\tYour Choice: ";
    	cin>>choice;

    	if(choice==1){
    		clrscr();
    	    loginMenu();
    	}
    	else if(choice==2){
    		clrscr();
    		employeeMenu();
    	}
    	else
    	   exit(0);

	}while(1);
}

//Menu screen for the Employee
void employeeMenu(){
    cout<<"\n\t\t\t\tEMPLOYER MENU\n\n\n\n\tPlease enter your name: ";
    char name[20], cname[20];
    gets(name);

    clrscr();
    cout<<"\n\n\nGood day, "<<name;

    cout<<". What would you like to do today?\n\n\n\t1. Show all tasks assigned to me\n\t2. Show all undone tasks\n\t3. Show all completed tasks\n\t4. Status updation\n\t5. Exit\n\nYour choice: ";

    int choice;
    cin>>choice;

    //Showing all tasks
    if (choice == 1){
    	clrscr();

    	fs.open("task.dat", ios::in|ios::binary);


    	while (fs.read((char*)&t, sizeof(t))){
            strcpy(cname, t.returnName());
    	    if ((strcmp(cname,name) == 0)){
                cout<<"----------------------------------------------------------------------------";
    			t.putData();
                cout<<"----------------------------------------------------------------------------";
    			cout<<"Press enter for next record";
    			getch();
    	    }
    	}
    	fs.close();
    	cout<<"\n\nEnd of all available records. Press any key to return to menu.";
    	getch();
    	menuScreen();
    }

    //Showing undone tasks
    else if (choice == 2){
    	clrscr();

    	fs.open("task.dat", ios::in|ios::binary);

    	while (fs.read((char*)&t, sizeof(t))){

    	    if ((strcmp(t.returnName(),name)==0) && (strcmp(t.returnStatus(),"UNDONE")==0)){
                cout<<"----------------------------------------------------------------------------";
    			t.putData();
                cout<<"----------------------------------------------------------------------------";
    			cout<<"Press enter for next record";
    			getch();
    	    }
    	}
    	fs.close();
    	cout<<"\n\nEnd of all available records. Press any key to return to menu.";
    	getch();
    	menuScreen();
    }

    //Showing done tasks
    else if (choice == 3){
    	clrscr();

    	fs.open("task.dat", ios::in|ios::binary);

    	while (fs.read((char*)&t, sizeof(t))){

    	    if ((strcmp(t.returnName(),name)==0) && (strcmp(t.returnStatus(),"DONE")==0)){
                cout<<"----------------------------------------------------------------------------";
    			t.putData();
                cout<<"----------------------------------------------------------------------------";
    			cout<<"Press enter for next record";
    			getch();
    	    }
    	}

    	fs.close();
    	cout<<"\n\nEnd of all available records. Press any key to return to menu.";
    	getch();
    	menuScreen();
    }

    //Status updation function
    else if (choice == 4){

    	clrscr();
    	fs.open("task.dat", ios::in|ios::binary);
    	temp.open("temp.dat", ios::out|ios::binary);

    	cout<<"\n\n\n\tEnter key of record to edit: ";
    	int searchKey;
    	cin>>searchKey;

    	while ( fs.read((char*)&t1, sizeof(t))){
        	if(!fs.eof()){
        		if (t1.returnKey()==searchKey){
        		    cout<<"\n\nTask found. New status for this task: ";
        		    char newStat[20];
        		    gets(newStat);

        		    t1.newStatus(newStat);
        		    temp.write((char*)&t1, sizeof(t1));
        		}


        		else{
        		    temp.write((char*)&t1, sizeof(t1));
                }
    	    }
        }

    	fs.close();
    	temp.close();
    	remove("task.dat");
    	rename("temp.dat", "task.dat");
        clrscr();
    	cout<<"\n\n\n\t\tTask has been modified. Press any key to return to menu.";
    	getch();
    	menuScreen();

        }

        else if(choice == 5){
        	cout<<"Exiting system...";
        	getch();
        	exit(0);
        }

        else{
        	cout<<"Invalid input. Press any key to return to menu";
        	getch();
        	menuScreen();
        }
    }


// Log in screen for employer
void loginMenu(){
    clrscr();
    cout<<"\n\n\n\n\n\t\t\t\tEMPLOYER LOGIN\n\n\t\tEnter password to view Employer Functions.\n\n\t\t\t     Password: ";
    char pass[20];
    gets(pass);

    ifstream pfs;

    pfs.open("PASS.txt");
    char pw[20];
    while(!pfs.eof()){
    	pfs>>pw;

    	pfs.close();

    	if(strcmp(pw,pass)==0)
    	   employerMenu();
    	else{
    		cout<<"\n\n\t\t\tInvalid password. Returning to menu.";
    		getch();
    		menuScreen();
    	}
    }

    pfs.close();
}







//Function for making new password
void newPassword(){
    clrscr();

    ofstream pfs;
    pfs.open("pass.txt", ios::trunc);
    char newp[20];
    cout<<"\n\t\t\t\tCHANGE PASSWORD\n\n\n\n\tEnter new password (Under 20 characters): ";
    gets(newp);
    pfs<<newp;
    pfs.close();
}

//Function for creating new task
void createTask(){
    clrscr();
    cout<<"\n\t\t\t\tCREATE TASK\n\n";
    fs.open("task.dat", ios::out|ios::binary|ios::app);
    char response;

    t.getData();
    fs.write((char*)&t, sizeof(t));

    getch();
    fs.close();
}

//Function for printing all tasks
void printAll(){
    clrscr();
    fs.open("task.dat", ios::in|ios::binary);

    while(fs.read((char*)&t, sizeof(t))){
	cout<<"----------------------------------------------------------------------------";
	t.putData();
	cout<<"----------------------------------------------------------------------------";
	getch();
    }

    cout<<"\n\nEnd of records. Press any key to return to menu.";
    getch();
    fs.close();
}

//Function for deleting task
void deleteTask(){
    clrscr();
    cout<<"\n\t\t\t\tDELETE TASK\n\n\n";
    int searchKey;
    cout<<"\n\t\t\tEnter task key to be deleted: ";
    cin>>searchKey;

    fs.open("task.dat", ios::in|ios::binary);
    temp.open("temp.dat", ios::out|ios::binary);

    while(fs.read((char*)&t, sizeof(t))){
	if (t.returnKey() != searchKey){
	    temp.write((char*)&t, sizeof(t));
	}
	else{
	    cout<<"\n\t\t\t   Record found and deleted.";
	    getch();
	}
    }

    fs.close();
    temp.close();

    remove("task.dat");
    rename("temp.dat","task.dat");
}

// Search Function
void searchTasks(){
    clrscr();
    cout << "\n\t\t\t\tSEARCH TASKS\n\n\n\tHow do you wish to search?\n\t\t1. Task Key\n\t\t2. By name\n\t\t3. By status\n\n\t\tYour choice: ";
    int option;
    cin >> option;

    fs.open("task.dat", ios::in|ios::binary);

    if (option == 1){
    	clrscr();
    	cout << "\n\t\t\t\tSEARCH BY KEY";
    	int searchKey;
    	cout<<"\n\n\t\t\tKey to look for: ";
    	cin>>searchKey;

        clrscr();

    	while(fs.read((char*)&t, sizeof(t))){
    		if (t.returnKey() == searchKey){
                cout<<"----------------------------------------------------------------------------";
    			t.putData();
                cout<<"----------------------------------------------------------------------------";
    		    cout<<"\n\nPress enter for next record";
    		    getch();
    		}
    	   }
           cout<<"\n\nEnd of records. Returning to menu..";
           getch();
    }

    if (option == 2){
    	clrscr();
    	cout<< "\n\t\t\t\tSEARCH BY NAME\n\n";
    	char searchName[20];
    	cout<<"\n\t\t\tTasks assigned to: ";
    	gets(searchName);

        clrscr();

    	while (fs.read((char*)&t, sizeof(t))){

    	    if (strcmpi(t.returnName(),searchName)==0){
                cout<<"----------------------------------------------------------------------------";
    			t.putData();
                cout<<"----------------------------------------------------------------------------";
    			cout<<"Press enter for next record";
    			getch();
    	    }
    	}
        cout<<"End of records. Returning to menu..";
        getch();
    }

    if (option == 3){
    	clrscr();
    	cout<< "\n\t\t\t\tSEARCH BY STATUS\n\n";
    	char searchStatus[20];
    	cout<<"\n\t\t\tSearch for UNDONE/DONE/WIP: ";
    	gets(searchStatus);

    	while (fs.read((char*)&t, sizeof(t))){

    	    if (strcmpi(t.returnStatus(),searchStatus)==0){
                cout<<"----------------------------------------------------------------------------";
    			t.putData();
                cout<<"----------------------------------------------------------------------------";
    			cout<<"Press enter for next record";
    			getch();
    	    }
    	}
        cout<<"End of records. Returning to menu..";
        getch();
    }
    fs.close();
}

// Modify Function
void modifyTask(){
    clrscr();
    cout<<"\n\t\t\t\tMODIFY TASK\n\n";
    fs.open("task.dat", ios::in|ios::binary);
    temp.open("temp.dat", ios::out|ios::binary);

    cout<<"\n\t\t\tEnter key of record to edit: ";
    int searchKey;
    cin>>searchKey;

    clrscr();

    while ( fs.read((char*)&t1, sizeof(t))){
	if(!fs.eof()){
		if (t1.returnKey()==searchKey){
		    cout<<"\n\nRe-enter data";
		    t1.getData();
		    temp.write((char*)&t1, sizeof(t1));
		}
	}

	else
	    temp.write((char*)&t1, sizeof(t1));

    }

    fs.close();
    temp.close();
    remove("task.dat");
    rename("temp.dat", "task.dat");

    cout<<"\n\nTask modified. Press any key to return to menu.";
    getch();
}


//Menu for employer
void employerMenu(){
    do{
	clrscr();

	cout<<"\n\n\n\n\n\n\t\tGood day! What would you like to do today?\n\n\t\t\t1.Create Task\n\t\t\t2.Delete Task\n\t\t\t3.Search task\n\t\t\t4.Modify Task\n\t\t\t5.View all tasks\n\t\t\t6.Set a new Password\n\t\t\t7.Quit\n\n\t\tYour choice: ";

    int choice;
	cin>>choice;

	if(choice==1)
	    createTask();

	else if (choice==2){
	    deleteTask();
	}

	else if(choice==3){
	    searchTasks();
	}

	else if(choice==4){
	    modifyTask();
	}

	else if(choice == 5){
	    printAll();
	}

	else if( choice == 6){
	    newPassword();
	}


	else
	    menuScreen();
    }while(1);
}

//Main function
void main(){
	clrscr();

    ofstream pfs;
	pfs.open("pass.txt", ios::trunc);
	pfs<<"DEFAULT";

    pfs.close();

	cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t      TASK MANAGEMENT SYSTEM\n\n\t\t\t\t Made by Poulomi";
	getch();
	menuScreen();
	getch();
}
