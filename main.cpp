#include<bits/stdc++.h>
#include <iostream>
#include<string>
#include<vector>

using namespace std;

const int groundrooms=200;  // appointing a room as a first patient || complete some error cases for functions(check it)
const int firstrooms=150;
const int secondrooms=150;

class node{
public:
    string name;
    int age;
    int room_number;
    int floor;
    int dd;
    int mm;
    int yy;
    bool allotted;
    bool enquiry;

    node* next;
    node(int value,string str,int r_no,int date,int month,int year) // constructor
    {
        age=value;
        name=str;
        room_number=r_no;
        dd=date;
        mm=month;
        yy=year;
        allotted=false;
        next = NULL;
    }
};

class Quarantine{
private:
    node* head=NULL;
    int g=0,f=0,s=0;  // used for room number allottment
    int r_g=0,r_f=0,r_s=0;  // used for room enquiry
    bool room_status[501]={0};
   // bool enquiry=false;
    int count=0;
    int patient_count=0;
    void insertattail(node* &head,int val,string st,int date,int month,int year)
    {
        node* n= new node(val,st,-1,date,month,year);  // -1 => no room has been allotted yet
        if(head==NULL){
            head=n;
            return;
        }
        node* temp=head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=n;
    }

    void display(node* head)
    {
        if(head==NULL){
            cout<<"\t All the Patients have been Discharged"<<endl;
            return;
        }

        node* temp=head;
        if(head!=NULL){
            while(temp!=NULL){
                for(int i=0;i<20;i++){
                    cout<<"~._.~"<<" ";
                }
                cout<<endl;

                cout<<" "<<"Name: "<<temp->name<<endl;
                cout<<" "<<"Age: "<<temp->age<<endl;
                /*cout<<"Gender: "<<temp->gender<<endl;
                cout<<"Address: "<<temp->address<<endl;
                cout<<"Destination: "<<temp->destination;*/
                cout<<" "<<"Floor number: "<<temp->floor<<endl;
                cout<<" "<<"Room number: "<<temp->room_number<<endl;

                for(int i=0;i<20;i++){
                    cout<<"~._.~"<<" ";
                }
                cout<<endl;

                temp=temp->next;
            }

        }
    }
public:
    void Add_patient(int n)
    {
        string name;
        /*string gender;
        string address;
        string destination;*/
        int age;
        int date,month,year;
        patient_count++;

        if(n==0){
            cout<<"\t No Patient was Added"<<endl;
        }

        for(int i=0;i<n;i++){
            cout<<" "<<"Name: ";
            getline(cin>> ws,name);
            cout<<" "<<"Age: ";
            cin>>age;
            while(age<18){
                if(age > 0 && age < 18){
                    cout<<" "<<"----------"<<"\t People of Entered age are not Allowed \t"<<"----------"<<endl;
                    cout<<"Please ,enter the valid allowed AGE: ";
                    cin>>age;
                }
                if(age<=0){
                    cout<<"\t Invalid Age entered"<<endl;
                    cout<<"Please ,Enter the Valid Age: ";
                    cin>>age;
                }
            }

          /*cout<<"Gender: ";
            cin>>gender;
            cout<<"Address: ";
            cin>>address;
            cout<<"Destination: ";
            cin>>destination;*/
            cout<<" "<<"Arrival Date (dd_mm_yy)"<<endl;
            cin>>date>>month>>year;
            insertattail(head,age,name,date,month,year);  // gender,address,destination
        }
    }

    void Display_details()
    {
        display(head);
    }

    int allott_room(int age)
    {
        if(age>=60 && g<groundrooms){
            g++;
            room_status[g]=true;
            return g ;
        }
        else if((age>=40 && age<60) && f<firstrooms){
            f++;
            room_status[f+groundrooms]=true;
            return f+groundrooms;
        }
        else if(age<40 && s<secondrooms){
            s++;
            room_status[s+groundrooms+firstrooms]=true;
            return s+groundrooms+firstrooms ;
        }
        return -1;
    }

    int allott_floor(int age)
    {
        if(age>=60){
            return 0;
        }
        else if(age>=40 && age<60){
            return 1;
        }
        else{
            return 2;
        }
    }

    void allot(node* &head)
    {
        node* temp=head;
        while(temp->allotted!=false){
            temp=temp->next;
            if(temp==NULL){
                cout<<"\t Room has been already allotted"<<endl;
                return;
            }
        }

        while(temp!=NULL && temp->allotted==false){

            temp->room_number=allott_room(temp->age);
            temp->floor=allott_floor(temp->age);
            temp->allotted= true;
            temp->enquiry=true;

            temp=temp->next;
        }

    }

    int length(node* head)   // length of list
    {
        int l=0;
        node* temp=head;
        while(temp!=NULL){
            l++;
            temp=temp->next;
        }
        return l;
    }
    void Room_and_Floor_allottment(int n)
    {
        int l1;
        l1=length(head);

        if(l1==0){
            cout<<"\t No patients left"<<endl;
            count=0;
            return;
        }
        count++;
        if(count==1 && l1==n){
            allot(head);
            return;
        }
        else if(l1>n){
            allot(head);
            n=l1;
            return;
        }
        else{
            cout<<"\t Room has been already allotted"<<endl;
            return;
        }
    }

    void floor_enquiry()
    {
        node* temp=head;
        if(temp==NULL){
            cout<<"\t No patients left"<<endl;
            cout<<" "<<"||"<<"Rooms available on ground floor: "<<groundrooms-r_g<<"||"<<endl;
            cout<<" "<<"||"<<"Rooms available on first  floor: "<<firstrooms-r_f<<"||"<<endl;
            cout<<" "<<"||"<<"Rooms available on second floor: "<<secondrooms-r_s<<"||"<<endl;
            return;
        }
        while(temp->enquiry!=true){
            temp=temp->next;
            if(temp==NULL){
                cout<<" "<<"||"<<"Rooms available on ground floor: "<<groundrooms-r_g<<"||"<<endl;
                cout<<" "<<"||"<<"Rooms available on first  floor: "<<firstrooms-r_f<<"||"<<endl;
                cout<<" "<<"||"<<"Rooms available on second floor: "<<secondrooms-r_s<<"||"<<endl;
                return;
            }
        }

            while(temp!=NULL && temp->enquiry==true){
                if(temp->age >=60 && temp->allotted==true){
                    r_g++;
                    temp->enquiry=false;
                }

                else if((temp->age<60 && temp->age>=40) && temp->allotted==true){
                    r_f++;
                    temp->enquiry=false;
                }

                else if((temp->age>=18 && temp->age<40) && temp->allotted==true){
                    r_s++;
                    temp->enquiry=false;
                }

                temp=temp->next;
            }

        cout<<" "<<"||"<<"Rooms available on ground floor: "<<groundrooms-r_g<<"||"<<endl;
        cout<<" "<<"||"<<"Rooms available on first  floor: "<<firstrooms-r_f<<"||"<<endl;
        cout<<" "<<"||"<<"Rooms available on second floor: "<<secondrooms-r_s<<"||"<<endl;
    }

    void Find_detail_of_a_room_number(int roomnumber)
    {
        if(roomnumber>groundrooms+firstrooms+secondrooms ){
            cout<<"\t Room not Found "<<endl;
            return;
        }
        else if(room_status[roomnumber]==false){
            cout<<"\t Room is VACANT"<<endl;
            return;
        }

        node* temp=head;
        while(temp!=NULL){

            if(temp->room_number==roomnumber){
                for(int i=0;i<20;i++){
                    cout<<"_~.~_"<<" ";
                }
                cout<<endl;

                cout<<" "<<"Name: "<<temp->name<<endl;
                cout<<" "<<"Age: "<<temp->age<<endl;
                cout<<" "<<"Floor Number: "<<temp->floor<<endl;

                for(int i=0;i<20;i++){
                    cout<<"_~.~_"<<" ";
                }
                cout<<endl;

                return;
            }
            temp=temp->next;
        }

    }

    void check_room_status(int room_no)
    {

        node* temp=head;

        while(temp!=NULL){
            if(room_no==temp->room_number){
                cout<<"---"<<endl;

                if(room_status[temp->room_number])   // 1=> true
                    cout<<"|"<<"FILLED"<<"|"<<endl;

                cout<<"---"<<endl;
                return;
            }
            temp=temp->next;
        }

        cout<<"---"<<endl;

        if(!(room_status[room_no]))      // (!0)=> false
            cout<<"VACANT"<<endl;

        cout<<"---"<<endl;
    }

     void Find_detail_by_name()
     {
        node* temp=head;
        cout<<"~~~~~~~~~~Enter the name of the patient: ";
        string str;
        getline(cin>> ws,str);
        while(temp!=NULL){
            if(temp->name==str){
                for(int i=0;i<20;i++){
                    cout<<"_~.~_"<<" ";
                }
                cout<<endl;

                //cout<<" "<<"Name: "<<temp->name<<endl;
                cout<<" "<<"Age: "<<temp->age<<endl;
                /*cout<<"Gender: "<<temp->gender<<endl;
                cout<<"Address: "<<temp->address<<endl;
                cout<<"Destination: "<<temp->destination;
                cout<<"Floor number: "<<temp->floor<<endl;*/
                cout<<" "<<"Room number: "<<temp->room_number<<endl;

                for(int i=0;i<20;i++){
                    cout<<"_~.~_"<<" ";
                }
                cout<<endl;

                return;
            }
            temp=temp->next;
        }

        cout<<"\t Record not found (either the patient has been discharged or was never admitted)"<<endl;
    }

    void Discharge_at_head(node* &head)  // For patient at head or if the list contains only one patient(thus it will behave as head and tail)
    {
        node* todischarge=head;
        int dis_age=head->age;
        room_status[head->room_number]=false;
        head=head->next;

        delete todischarge;

        if(dis_age >= 60){
            r_g--;
        }
        else if(dis_age >= 40 && dis_age < 60){
            r_f--;
        }
        else{
            r_s--;
        }

        cout<<" "<<"Discharging...................Completed"<<endl;
    }

    void Discharge(node* &head,string dis_name)  // Discharging => all the information of the patient will also be deleted (limitation)
    {
        node* temp=head;
        int dis_age;

        while(temp->next->name!=dis_name){

            temp=temp->next;

            if(temp->next == NULL){                 // check if name does not found
                cout<<"\t Entered Patient not found"<<endl;
                return ;
            }
        }

        dis_age=temp->next->age;
        room_status[temp->next->room_number]=false;
        node* todischarge = temp->next;
        temp->next=temp->next->next;

        delete todischarge;

        if(dis_age >= 60){
            r_g--;
        }
        else if(dis_age >= 40 && dis_age < 60){
            r_f--;
        }
        else{
            r_s--;
        }

        cout<<" "<<"Discharging...................Completed"<<endl;
    }

    void Discharge_by_name()
    {
        string dis_name;
        cout<<" "<<"Enter Patient's Name user want to discharge: "<<endl;
        getline(cin>> ws,dis_name);

        if(head==NULL){
            if(patient_count>0){
                cout<<" "<<"All the patients have been discharged"<<endl;
                return;
            }
            else{
                cout<<"\t No Patient has been added yet"<<endl;
                return;
            }
        }

        if(dis_name==head->name && head->next!= NULL){
            Discharge_at_head(head);
        }
        else if(head->next==NULL){
            Discharge_at_head(head);
        }
        else{
            Discharge(head,dis_name);
        }
    }

    void Discharge_date()
    {
        cout<<" "<<"Enter the Name of Patient"<<endl;
        int dd1,mm1,yy1;
        string dis_name;
        getline(cin>> ws,dis_name);

        node* temp=head;

            while(temp!=NULL)
            {
                if(temp->name==dis_name){
                    if(temp->mm==1 || temp->mm==3 || temp->mm==5 || temp->mm==7 || temp->mm==8 || temp->mm==10 || temp->mm==12 ){
                        if(temp->dd+14>31){
                            dd1=(temp->dd + 14) - 31;
                            mm1=temp->mm + 1;
                        }
                        else{
                            dd1=temp->dd+14;
                            mm1=temp->mm;
                        }
                    }
                    else if(temp->mm==4 || temp->mm==6 || temp->mm==9 || temp->mm==11){
                        if(temp->dd+14>30){
                            dd1=(temp->dd + 14) - 30;
                            mm1 = temp->mm + 1;
                        }
                        else{
                            dd1 = temp->dd+14;
                            mm1=temp->mm;
                        }
                    }
                    else if(temp->mm==2){
                        if((2000+temp->yy)%4!=0){
                            if(temp->dd+14>28){
                                    dd1=(temp->dd + 14)-28;
                                    mm1=temp->mm+1;
                                }
                            else{
                                dd1=temp->dd+14;
                                mm1=temp->mm;
                            }
                        }
                        else{
                            if(temp->dd+14>29){
                                dd1=(temp->dd + 14)-29;
                                mm1=temp->mm;
                            }
                            else{
                                dd1=temp->dd+14;
                                mm1=temp->mm;
                            }
                        }
                    }
                    if(mm1>12){
                        mm1=1;
                        yy1=temp->yy + 1;
                    }
                    else{
                        yy1=temp->yy;
                    }

                cout<<" "<<"Discharge date"<<endl;
                cout<<"||-> "<<"dd: "<<dd1<<" "<<"mm: "<<mm1<<" "<<"yy: 20"<<yy1<<" <-||"<<endl;

                return;
            }
            temp=temp->next;
        }

        cout<<"\t Patient with entered name 'NOT FOUND'"<<endl;
    }

    void Allott_patient_to_particular_room()
    {
        int room_num;

        if(patient_count==0 || head==NULL){
            cout<<"\t For adding Patient to particular room , the list should not be empty"<<endl;
            return;
        }

        cout<<" "<<"Allott Patient to a particular Room"<<endl;
        cout<<" "<<"Enter the Room number user want to fill: ";

        cin>>room_num;
        while(room_num>groundrooms+firstrooms+secondrooms){
            cout<<"\t PLEASE ENTER A VALID ROOM NUMBER: ";
            cin>>room_num;
        }

        bool room_check=false;
        while(room_check!=true){
            if(room_status[room_num]==true){
                cout<<"Room has already been Occupied"<<endl;
                cout<<" "<<"Re-enter a vacant room"<<endl;
                cin>>room_num;
            }
            else{
                room_check=true;
            }
        }

        bool correct_age=false;

        string name;
        /*string gender;
        string address;
        string destination;*/
        int age;
        int date,month,year;

        node* temp=head;

        while(temp->next!=NULL){
            temp=temp->next;
        }

        cout<<" "<<"Name: ";
        getline(cin>> ws,name);

        cout<<" "<<"Age: ";
        cin>>age;
        while(correct_age==false){
            if(room_num<=groundrooms){
                if(age<60){
                    cout<<" "<<"Please enter a valid Age -> It should be more than or equal to 60 years"<<endl;
                    cin>>age;
                }
                else{
                    correct_age=true;
                }
            }
            else if(room_num>groundrooms && room_num<=(groundrooms+firstrooms)){
                if(age<40 || age>60){
                    cout<<" "<<"Please enter a valid Age -> It should be more than or equal 40 years and less than 60 years"<<endl;
                    cin>>age;
                }
                else{
                    correct_age=true;
                }
            }
            else if(room_num>(groundrooms+firstrooms) && room_num<=(groundrooms+firstrooms+secondrooms)){
                if(age>40 || age<18){
                    cout<<" "<<"Please enter a valid Age -> It should be more than or equal to 18 years and less than 40 years"<<endl;
                    cin>>age;
                }
                else{
                    correct_age=true;
                }
            }
        }

        /*cout<<"Gender: ";
        cin>>gender;
        cout<<"Address: ";
        cin>>address;
        cout<<"Destination: ";
        cin>>destination;*/

        cout<<" "<<"Arrival Date (dd-mm-yy)"<<endl;
        cin>>date>>month>>year;

        node* n= new node(age,name,room_num,date,month,year);

        temp->next=n;
        temp=temp->next;

        room_status[temp->room_number]=true;
        temp->allotted=true;

        if(age>=60){
            temp->floor=0;
        }
        else if(age>=40 && age<60){
            temp->floor=1;
        }
        else{
            temp->floor=2;
        }
    }

    void Occupied_room_list()
    {
        node* temp=head;
        if(temp==NULL){
            cout<<"\t All Rooms are VACANT"<<endl;
        }
        while(temp!=NULL){
            cout<<temp->room_number<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }

    void sort_list()
    {
        node* current=head;
        node* index=NULL;

        if(head==NULL){
            return;
        }
        else{
            while(current!=NULL){
                index=current->next;

                while(index!=NULL){
                    if(current->room_number>index->room_number){           // swaping all the contents
                        swap(current->room_number,index->room_number);
                        swap(current->age,index->age);
                        swap(current->name,index->name);
                        swap(current->floor,index->floor);
                    }
                    index=index->next;
                }
                current=current->next;
            }
        }

        display(head);
    }

    void re_display_options()
    {
        cout<<"1.---------- To add the information of patients                                                ----------"<<endl;
        cout<<"2.---------- Room Allotment                                                                    ----------"<<endl;
        cout<<"3.---------- Displaying the details of all the patients                                        ----------"<<endl;
        cout<<"4.---------- To check Rooms available on each floor                                            ----------"<<endl;
        cout<<"5.---------- To find details of a room by entering room number                                 ----------"<<endl;
        cout<<"6.---------- To check the status of room by entering room number(0-empty || 1-filled)          ----------"<<endl;
        cout<<"7.---------- To find Details of the given patient by entering his/her name                     ----------"<<endl;
        cout<<"8.---------- To Discharge a patient by entering his/her Name                                   ----------"<<endl;
        cout<<"9.---------- To know the Discharge Date(after 14 days of admission) by entering Patient's Name ----------"<<endl;
        cout<<"10.--------- To alott patient a particular room of his/her choice                              ----------"<<endl;
        cout<<"11.--------- To display the list of Occupied Rooms                                             ----------"<<endl;
        cout<<"12.--------- To sort the list with room numbers                                                ----------"<<endl;
        cout<<"13.--------- To Re-display the options                                                         ----------"<<endl;
        cout<<"14.--------- EXIT                                                                              ----------"<<endl;

    }

};

int main()
{
    Quarantine system;
    char choice;

    cout<<"~~~~~~~~~~~~~~~~~~~~2. WELCOME TO NIT SILCHAR QUARANTINE CENTRE ~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"1.---------- To add the information of patients                                                ----------"<<endl;
    cout<<"2.---------- Room Allotment                                                                    ----------"<<endl;
    cout<<"3.---------- Displaying the details of all the patients                                        ----------"<<endl;
    cout<<"4.---------- To check Rooms available on each floor                                            ----------"<<endl;
    cout<<"5.---------- To find details of a room by entering room number                                 ----------"<<endl;
    cout<<"6.---------- To check the status of room by entering room number(0-empty || 1-filled)          ----------"<<endl;
    cout<<"7.---------- To find Details of the given patient by entering his/her name                     ----------"<<endl;
    cout<<"8.---------- To Discharge a patient by entering his/her Name                                   ----------"<<endl;
    cout<<"9.---------- To know the Discharge Date(after 14 days of admission) by entering Patient's Name ----------"<<endl;
    cout<<"10.--------- To alott patient a particular room of his/her choice                              ----------"<<endl;
    cout<<"11.--------- To display the list of Occupied Rooms                                             ----------"<<endl;
    cout<<"12.--------- To sort the list with room numbers                                                ----------"<<endl;
    cout<<"13.--------- To Re-display the options                                                         ----------"<<endl;
    cout<<"14.--------- EXIT                                                                              ----------"<<endl;

    do{
        int option;
        cout<<"Enter the option: ";
        cin>>option;
        switch(option)
        {
        case 1:
            cout<<"\t Enter number of patients you want to add: ";
            int n;
            cin>>n;

            system.Add_patient(n);
            break;
        case 2:
            cout<<"Room Allottment"<<endl;
            system.Room_and_Floor_allottment(n);
            break;
        case 3:
            system.Display_details();
            break;
        case 4:
            system.floor_enquiry();
            break;
        case 5:
            int roomnumber;
            cout<<"Enter Room number whose details to be retrieved: "<<endl;
            cin>>roomnumber;
            while(roomnumber>groundrooms+firstrooms+secondrooms){
                if(roomnumber>groundrooms+firstrooms+secondrooms){
                    cout<<"\t INVALID ROOM NUMBER \n Please Enter a VALID ROOM NUMBER: "<<endl;
                    cin>>roomnumber;
                }
            }
            system.Find_detail_of_a_room_number(roomnumber);
            break;
        case 6:
            int room_no;
            cout<<"----------To check the status of room(0-empty || 1-filled)----------"<<endl;
            cout<<"~~~~~~~~~~Enter the Room number: ";
            cin>>room_no;
            while(room_no>groundrooms+firstrooms+secondrooms){
                if(room_no>groundrooms+firstrooms+secondrooms){
                    cout<<"\t INVALID ROOM NUMBER \n Please Enter a VALID ROOM NUMBER: "<<endl;
                    cin>>room_no;
                }
            }
            system.check_room_status(room_no);
            break;
        case 7:
            cout<<"----------To find Details of the given patient by entering his/her name----------"<<endl;
            system.Find_detail_by_name();
            break;
        case 8:
            cout<<"---------- To Discharge a patient by Name ----------"<<endl;
            system.Discharge_by_name();
            break;
        case 9:
            cout<<"----------To know the Discharge Date-----------"<<endl;
            system.Discharge_date();
            break;
        case 10:
            system.Allott_patient_to_particular_room();
            break;
        case 11:
            system.Occupied_room_list();
            break;
        case 12:
            system.sort_list();
            break;
        case 13:
            system.re_display_options();
            break;
        case 14:
            cout<<"~`~`~`~`~`~`~`~`~`~`THANK YOU`~`~`~`~`~`~`~`~`~`~"<<endl;
            return 0;
        default:
            cout<<" "<<"Wrong option entered \n \t Please enter a correct option"<<endl;
            break;
        }
        cout<<"Do you want to continue \n Enter 'y' for YES and Enter 'any key' for NO: ";
        cin>>choice;
    }while(choice=='y');

    return 0;
}
