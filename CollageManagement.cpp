#include<iostream>
#include<string.h>
#include<conio.h>
#include<fstream>
using namespace std;

class CollageInfo{
    private:
        char name[50];
        long rollNo;
        int semester;
        char branch[20];
        int cgpa;
    public:
        CollageInfo(){
            strcpy(name, "NULL");
            rollNo=0;
            semester=0;
            strcpy(branch, "NULL");
            cgpa=0;
        }
        void newEntry(){
            cout<<"\nEnter Student name: ";
            cin.ignore();
            cin.getline(name, 50);
            cout<<"Enter rollNo: ";
            cin>>rollNo;
            cout<<"Enter Current Semester: ";
            cin>>semester;
            cout<<"Enter Your branch: ";
            cin.ignore();
            cin.getline(branch,20);
            cout<<"Enter Your CGPA: ";
            cin>>cgpa;

        }
        void viewEntry(){
            cout<<name<<"    |    "<<rollNo<<"  |   "<<semester<<"  |   "<<branch<<"    |   "<<cgpa<<endl;
        }
        int storeNewEntry();
        void deleteEntry(char*);
        void viewAllEntry();
        void searchEntry(char *);
        void updateEntry(char *);
};

int CollageInfo::storeNewEntry(){
    if(rollNo==0 && name=="NULL"){
        cout<<"\nFailed to insert!!!!";
        return(0);      //indicate that insersion is unsuccessful.
    }
    else{
        ofstream fout;
        fout.open("account.txt", ios::app|ios::binary);
        fout.write((char*)this, sizeof(*this));
        fout.close();
        return(1);      //indicate that insersion is successful
    }
}

void CollageInfo::deleteEntry(char *t)
{
    ifstream fin;
    ofstream fout;
    fin.open("account.txt",ios::in | ios::binary);
    if(!fin)
        cout<<"File Not Found";
    else{
        fout.open("tempfile.txt",ios::out | ios::binary);
        fin.read((char *)this,sizeof(*this));
        while(!fin.eof())
        {
            if(strcmp(name,t))         //if user enter title match with caller object title then "strcmp(title,t)=0"
                fout.write((char*)this,sizeof(*this));
            fin.read((char *)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("account.txt");
        rename("tempfile.txt","account.txt");
    }
}

void CollageInfo::viewAllEntry(){
    ifstream fin;
    fin.open("account.txt", ios::in|ios::binary);
    if(!fin){
        cout<<"File Not Found!!!";
    }
    else{
        fin.read((char*)this, sizeof(*this));
        while (!fin.eof()){         //eof stand for end of file
            viewEntry();
            fin.read((char*)this, sizeof(*this));
        }
        fin.close();
    }
}

void CollageInfo::searchEntry(char *t)
{
    int counter=0;
    ifstream fin;
    fin.open("account.txt",ios::in|ios::binary);
    if(!fin)
        cout<<"\nFile Not Found";
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(!strcmp(t, name))
            {
                viewEntry();
                counter++;
            }
        fin.read((char*)this,sizeof(*this));
        }
        if(counter==0)
            cout<<"\nRecord Not found";
    }
    fin.close();
}

void CollageInfo::updateEntry(char *t){
    fstream file;
    file.open("account.txt", ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);      //it help to point from starting. ate(update) mode start pointing from last.
    file.read((char*)this, sizeof(*this));
    while (!file.eof())
    {
        if(!strcmp(t, name)){       //if it is same then it will return 0 that's why used '!'
            newEntry();
            file.seekp(file.tellp()-sizeof(*this));     //change the pointing position
            file.write((char*)this, sizeof(*this));
        }
        file.read((char*)this, sizeof(*this));
    }

}

int menu(){
    int choice;
    cout<<"\n\n****Welcome to CollageInfo Manager****\n\n";
    cout<<"1. New Entry\n";
    cout<<"2. Delete Entry\n";
    cout<<"3. View All Entries\n";
    cout<<"4. Search Entry\n";
    cout<<"5. Update Entry\n";
    cout<<"6. Exit\n";

    cout<<"\nEnter Your Choice: ";
    cin>>choice;
    return(choice);
}

int main(){
    CollageInfo p1;
    char name[50];

    system("color 0A");
    while (1)
    {
    switch (menu())
        {
        case 1:{
            system("cls");
            p1.newEntry();
            p1.storeNewEntry();
            system("cls");
            cout<<"\nNew Entry Done!!";
            break;
        }
        case 2:{
            system("cls");
            cout<<"\nEnter the name you want to delete: ";
            cin.ignore();
            cin.getline(name, 49);
            p1.deleteEntry(name);
            cout<<"\nEntry Deleted";
            system("cls");
            break;
        }
        case 3:{
            system("cls");
            p1.viewAllEntry();
            break;
        }
        case 4:{
            system("cls");
            cout<<"\nEnter the name you want to Search: ";
            cin.ignore();
            cin.getline(name, 49);
            p1.searchEntry(name);
            break;
        }
        case 5:{
            system("cls");
            p1.viewAllEntry();
            cout<<"\nEnter the name you want to Update: ";
            cin.ignore();
            cin.getline(name, 49);
            p1.updateEntry(name);
            system("cls");
            cout<<"\nUpdated Successfully!!";
            break;
        }
        case 6:
            cout<<"\nPress any key to exit";
            getch();
            exit(0);
            break;

        default:
            cout<<"\nInvalid Operation!!";
            break;
        }
        getch();
    }

}
