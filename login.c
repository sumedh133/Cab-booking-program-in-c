#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define max_unsize 20
#define max_passsize 20
#define MAX_LOCATIONS 100

char username[max_unsize];//global username variable
int price_per_km=10;
struct Book 
{
	char name[max_unsize];
	char pickup[50];
	char dropoff[50];
	float dist;
	float total;
	
};
struct User//structure to store user info
{
    char username[max_unsize];
    char password[max_passsize];

};
struct Location//structure to store location info
 {
    char name[50];
    int available;
    float dist;
}; 
void printlocations()
{
	printf("\t\t\t\t\tLOCATION LIST\n\n");
	struct Location locations[MAX_LOCATIONS];
    int num_locations = 0;
    int i;
    
	// Read locations from file
    FILE *fp = fopen("locations.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return ;
    }
    while (fscanf(fp, "%s %d %f", locations[num_locations].name, &locations[num_locations].available, &locations[num_locations].dist) != EOF) {
        num_locations++;
    }
    fclose(fp);

    // Print available locations
	int k=1;
    for (i = 0; i < num_locations; i++) {
        printf("\t\t\t\t%d. %s (cabs=%d)\n", k, locations[i].name,locations[i].available);
        k++;
    }
    printf("\n");
    if(num_locations==0)
    printf("\t\t\t\tNo locations currently available\n\n");
    fclose(fp);
    return;
}
void removeLocations()
{
	sleep(1);
	system("cls");
	printf("\t\t\t\t\tREMOVING LOCATIONS\n");
	struct Location locations[MAX_LOCATIONS];
    int num_locations = 0;
    int i;

    // Read locations from file
    FILE *fp = fopen("locations.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return ;
    }
    while (fscanf(fp, "%s %d %f", locations[num_locations].name, &locations[num_locations].available, &locations[num_locations].dist) != EOF) {
        num_locations++;
    }
    fclose(fp);

    // Print available locations
    if(num_locations==0)
    printf("\t\t\t\tno available locations");
    int k=1;
    printf("\t\t\t\tAvailable locations:\n");
    for (i = 0; i < num_locations; i++) 
	{
        printf("\t\t\t\t%d. %s\t(cabs=%d)\n", k, locations[i].name,locations[i].available);
        k++;
    }
    
    fclose(fp);
    
    //writing a file with the location specified by the location removed
    FILE *fr=fopen("locations.txt","w");
    int index;
    printf("\t\t\t\tEnter which location u want to delete:");
    scanf("%d",&index);
    for(i=0;i<num_locations;i++)
    {
    	if(i==index-1)
    	continue;
    	fprintf(fr,"%s %d %f",locations[i].name,1,locations[i].dist);
	} 
	fclose(fr);   
	return;    
}
void addLocations()
{
	sleep(1);
	system("cls");
	printf("\t\t\t\t\tADDING LOCATIONS\n\n");
	
	loc:
	printf("\t\t\t\tEnter name of location:");
	struct Location add;	
	scanf("%s",add.name);
	printf("\t\t\t\tEnter distance:");
	scanf("%f",&add.dist);	
	int choice;	
	FILE* fp = fopen("locations.txt", "a");			
	fprintf(fp,"%s %d %f",add.name,2,add.dist);//storing location in
	fclose(fp);
	option:
	printf("\t\t\t\tWould you like to:\n\t\t\t\t[1].Enter another location or\n\t\t\t\t[2].Exit\n\t\t\t\t");
	scanf("\t\t\t\t%d",&choice);
	switch(choice)
	{
		case 1:
			goto loc;
			break;
		case 2:
			printf("\t\t\t\tThank you\n");
			break;
		default:
			printf("\t\t\t\tIvalid input\n");
			goto option;					
	}		
	return;	
}
void registerUser() 
{
	sleep(1);
	system("cls");
	printf("\t\t\t\t\tUSER REGISTRATION\n\n");
	struct User user;  
	printf("\t\t\t\tEnter your username (maximum %d characters): ",max_unsize);
	scanf("%s", user.username);   
	printf("\t\t\t\tEnter a password (maximum %d characters): ", max_passsize);
	scanf("%s", user.password); 
	
	//storing username and password   
    FILE* fp = fopen("users.txt", "a");    
    fprintf(fp, "%s %s\n", user.username, user.password);   
    fclose(fp);
    printf("\t\t\t\tRegistration successful!\n");
    return;
}
void loginAdmin() 
{
	sleep(1);
	system("cls");
	printf("\t\t\t\t\tADMIN LOGIN\n\n");
    struct User admin;
    int p=0;
    char password[max_passsize];
    char ch;
   
    printf("\t\t\t\tEnter your username: ");
    scanf("%s",username);
       
    printf("\t\t\t\tEnter your password: ");
    do
    {
        password[p]=getch();
        if(password[p]=='\b')
        {
        	printf("\b \b");
        	p=p-2;
    	}
		else     
        printf("*");
        p++;
    }
    while(password[p-1]!='\r');
    password[p-1]='\0';
    printf("\n\n");
	 
    FILE* fp = fopen("admin.txt", "r");    
    if(fp == NULL) 
	{
        printf("\t\t\t\tAdmin data fp does not exist.\n");
        return;
    }   
    //checking admin usernames and passwords
    while(fscanf(fp, "%s %s", admin.username, admin.password) == 2)
	{        
        if(strcmp(admin.username, username) == 0 && strcmp(admin.password, password) == 0) 
		{
            printf("\t\t\t\tLogin successful!\n");
            start1:
            sleep(1);
            system("cls");
            printf("\n\n\t\t\t\t\tADMIN OPTIONS\n\n");
            start:
            printf("\t\t\t\t1. Add locations\n");
    		printf("\t\t\t\t2. Remove locations\n");
    		printf("\t\t\t\t3. View available locations\n");
    		printf("\t\t\t\t4. Exit\n");
    		printf("\t\t\t\tEnter your choice: ");
    		int choice;
    		scanf("\t\t\t\t%d", &choice); 
			printf("\n"); 		
    		switch(choice) 
			{
				case 1:
            		addLocations();
            		goto start1;
            		break;
        		case 2:
            		removeLocations();
            		goto start1;
            		break; 
				case 3:
					printlocations();
					goto start;
					break;      
        		case 4:
            		printf("\t\t\t\tGoodbye!\n");
            		exit(15);
           			break;
        		default:
            		printf("\t\t\t\tInvalid input.\n\n");
            		goto start;
    			}
            fclose(fp);
            return;
        }
    }
    printf("\t\t\t\tInvalid ID\n");  
    exit(12);
    
    fclose(fp);
    return;
}
void loginUser() 
{
	sleep(1);
	system("cls");
	printf("\t\t\t\t\tUSER LOGIN\n\n");
    struct User user;
    int p=0;
    
    char password[max_passsize];   
    printf("\t\t\t\tEnter your username: ");
    scanf("%s", username);   
    printf("\t\t\t\tEnter your password: ");
    do
    {
        password[p]=getch();
        if(password[p]=='\b')
        {
        	printf("\b \b");
        	p=p-2;
    	}
    	else
        printf("*");
        p++;
    }
    while(password[p-1]!='\r');
    password[p-1]='\0';
	printf("\n"); 
    FILE* fp = fopen("users.txt", "r");    
    if(fp == NULL) 
	{
        printf("\t\t\t\tUser data fp does not exist.\n");
        return;
    }   
    //checking existing usernames and passwords
    while(fscanf(fp, "%s %s", user.username, user.password) == 2)
	{        
        if(strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) 
		{
            printf("\n\t\t\t\tLogin successful!\n");
            fclose(fp);
            return;
        }
    }
    printf("\t\t\t\tInvalid user.\n");  
    //option to register if no username and password matches
    printf("\t\t\t\tPress [1].to Register as new user or [2].to exit\n\t\t\t\t");
    int a;
    scanf("%d",&a);
    if(a==1)
    registerUser();
    else if(a==2)
    {
    	printf("\t\t\t\tGoodbye!");
    	exit(10);
    }
    else("\t\t\t\tinvalid choice");
    fclose(fp);
}
void book()
{
	sleep(1);
	system("cls");
	printf("\t\t\t\t\tCAB BOOKING\n\n");
	FILE *fp, *bill_fp;
    struct Location locations[MAX_LOCATIONS];
    struct Book book;
    int num_locations = 0;
    int i;

    // Read locations from file
    fp = fopen("locations.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return ;
    }
    while (fscanf(fp, "%s %d %f", locations[num_locations].name, &locations[num_locations].available, &locations[num_locations].dist) != EOF) {
        num_locations++;
    }
    fclose(fp);

    // Print available locations
    printf("\t\t\t\tlocations with cabs available:\n");
    for (i = 0; i < num_locations; i++) {
    	if(locations[i].available>=1)    	
        printf("\t\t\t\t%d. %s (cabs=%d)\n", i+1, locations[i].name,locations[i].available);
    }

    // Get pickup location from user
    int pickup_index = 0;
    while (pickup_index < 1 || pickup_index > num_locations) {
        printf("\t\t\t\tEnter pickup location number: ");
        scanf("%d", &pickup_index);
        if(pickup_index < 1 || pickup_index > num_locations)
        printf("\t\t\t\tInvalid input enter again: ");
    }
    struct Location pickup = locations[pickup_index-1];
    pickup.available--;
    locations[pickup_index-1]=pickup;

    // Get dropoff location from user
    int dropoff_index = 0;
    while (dropoff_index < 1 || dropoff_index > num_locations) {
        printf("\t\t\t\tEnter dropoff location number: ");
        scanf("%d", &dropoff_index);
        if(dropoff_index < 1 || dropoff_index > num_locations)
        printf("\t\t\t\tInvalid input enter again: ");
    }
    struct Location dropoff = locations[dropoff_index-1];
    dropoff.available++;
    locations[dropoff_index-1]=dropoff;

    // Calculate distance and bill amount
    float distance = abs(dropoff.dist - pickup.dist);
    float bill_amount = distance * price_per_km;

    // Update file with new location availability
    fp = fopen("locations.txt", "w");
    for (i = 0; i < num_locations; i++) {
        fprintf(fp, "%s %d %f", locations[i].name, locations[i].available, locations[i].dist);
    }
    fclose(fp);
    
    //print bill
    printf("\t\t\t\t\tBILL\n" );
    printf("\t\t\t\tUsername: %s\n", username);
    printf("\t\t\t\tPickup: %s\n", pickup.name);
    printf("\t\t\t\tDropoff: %s\n", dropoff.name);
    printf("\t\t\t\tDistance: %.2f km\n", distance);
    printf("\t\t\t\tTotal amount: %.2f rupees\n\n", bill_amount);

    // Store bill in file
    bill_fp = fopen("bill.txt", "a");
    if (bill_fp == NULL) {
        printf("Error opening file\n");
        return ;
    }
    fprintf(bill_fp, "%s %s %s %f %f", username,pickup.name,dropoff.name,distance,bill_amount);
    fclose(bill_fp);

    printf("\t\t\t\tBill generated and stored in file\n\n");
    return;
}
void cancel()
{
	sleep(1);
	system("cls");
	printf("\t\t\t\t\tCANCEL BOOKINGS\n\n");
	struct Book book[100];
	int i=1;
	int cnt=1;
	int num=0;
	FILE *fp=fopen("bill.txt","r");
	while(fscanf(fp,"%s %s %s %f %f",&book[num].name,&book[num].pickup,&book[num].dropoff,&book[num].dist,&book[num].total)==5)
	{//storing information which has same username
		num++;
	}
	int k=1;
	for(i=0;i<num;i++)
	{
		if(strcmp(username,book[i].name)==0)
		{
		printf("\t\t\t\t%d.Username: %s\n",i+1,book[i].name);
    	printf("\t\t\t\t   Pickup: %s\n", book[i].pickup);
    	printf("\t\t\t\t   Dropoff: %s\n", book[i].dropoff);
    	printf("\t\t\t\t   Distance: %.2f km\n", book[i].dist);
    	printf("\t\t\t\t   Total amount: %.2f rupees\n\n", book[i].total);
    	cnt=0;
   	 	}
	}
	if(cnt==1)
	printf("\t\t\t\tNo bookings under this username\n\n");
	else{
		FILE *fr=fopen("bill.txt","w");
    	int index;
    	printf("\t\t\t\tEnter number of booking u want to delete:");
    	scanf("%d",&index);
    	for(i=0;i<num;i++)
    	{
    		if(i==index-1)
    		continue;//storing all bills except the one user wants deleted
 	   		fprintf(fr, "%s %s %s %f %f",book[i].name,book[i].pickup,book[i].dropoff,book[i].dist,book[i].total);;
		} 
		fclose(fr); 
	}
	return;	
}
void viewBookings()
{
	sleep(1);
	system("cls");
	printf("\t\t\t\t\tPRIOR BOOKINGS\n\n");
	struct Book book[100];
	int i=1;
	int num=0;
	FILE *fp=fopen("bill.txt","r");
	while(fscanf(fp,"%s %s %s %f %f",&book[num].name,&book[num].pickup,&book[num].dropoff,&book[num].dist,&book[num].total)==5)
	{//storing information which has same username
		if(strcmp(book[num].name,username)==0)
		num++;
	}
	if(num==0)
	printf("\t\t\t\tno prior bookings\n\n");
	for(i=0;i<num;i++)
	{
		printf("\t\t\t\t%d.Username: %s\n",i+1,book[i].name);
    	printf("\t\t\t\t   Pickup: %s\n", book[i].pickup);
    	printf("\t\t\t\t   Dropoff: %s\n", book[i].dropoff);
    	printf("\t\t\t\t   Distance: %.2f km\n", book[i].dist);
    	printf("\t\t\t\t   Total amount: %.2f rupees\n\n", book[i].total);
	}
	return;
}
int main() 
{		
    int choice;
	start:   
	printf("\t\t\t\tWelcome to XYZ cab booking\n\n");
    printf("\t\t\t\t1. User Login\n");
    printf("\t\t\t\t2. User Register\n");
    printf("\t\t\t\t3. Admin Login\n");
    printf("\t\t\t\t4. View available locations\n");
    printf("\t\t\t\t5. Exit\n");
    printf("\t\t\t\tEnter your choice: ");
    scanf("\t\t\t\t%d", &choice);

    switch(choice) 
	{
		case 1:
            loginUser();
            break;
        case 2:
            registerUser();
            break;   
		case 3:
			loginAdmin();
			exit(1);
			break;
		case 4:
			printlocations();
			goto start;
			break;     
        case 5:
            printf("\t\t\t\tGoodbye!\n");
            exit(11);
            break;
        default:
            printf("\t\t\t\tInvalid input.\n");
            goto start;
    }
    sleep(1);
    system("cls");
    
	book:
    printf("\t\t\t\t\tUSER MENU\n\n");
    book1:
    printf("\t\t\t\t1. Book a cab\n");
    printf("\t\t\t\t2. Cancel a booking\n");
    printf("\t\t\t\t3. View prior bookings\n");
    printf("\t\t\t\t4. Exit\n");
    printf("\t\t\t\tEnter your choice: ");
    int choice1;
    scanf("\t\t\t\t%d",&choice1);
    
    switch(choice1) 
	{
		case 1:
            book();
            goto book1;
            break;
        case 2:
            cancel();
            goto book1;
            break;
		case 3:
            viewBookings();
            goto book1;
            break;        
        case 4:
            printf("\t\t\t\tGoodbye!\n");
            exit(12);
            break;
        default:
            printf("\t\t\t\tInvalid input.\n");            
            goto book;
        }       
	return 0;
}


