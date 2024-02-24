#include <bits/stdc++.h>

//Moath AbdAlbaqi 1210125 sec:1

using namespace std;
int n,m;//n represents the number of processes, m is the number of recources types.

int read(int[], int [][100], int[][100]);//reading the csv file.
void PrintThings(int[], int [][100], int[][100]);//printing the read values.
void DetectionAlgo(int[], int [][100], int[][100]);//detection algorithm.

int main() {
    int flag;//this flag is to decide if the files are consistent or no.
    int available[100],allocation[100][100],request[100][100];

    cout<<"Reading the Files..."<<endl;
    cout<<"It's assumed that the file names are as follows, Available, Request, Allocation."<<endl;

    flag = read(available,request, allocation);

    if(flag==1){cout<<"There is an error While reading, Check the number of processes and recourses in the files. ";return 0;}
    cout<<"\nReading done, This is the contents of the files:"<<endl;

    PrintThings(available,request, allocation);//printing the read values.

    DetectionAlgo(available,request, allocation);//detection algorithm.

    return 0;
}


int read(int available[100], int request[100][100], int allocation[100][100]){
    int numberOfLines1=0,numberOfLines2=0,flag=0;
    int numberOfColumns1=0,numberOfColumns2=0,numberOfColumns3=0;
    FILE *fr;
     fr=fopen("Available.csv","r");//opening the first file.

     char line[100];int numofrows1=0;
     int i=0,j=0;
            while(fgets(line,100,fr)){//iterate all lines one by one.
                if(i==0){i++;continue;}//Don't read the first line, Because its containing the name of resources.
                numofrows1++;
                char *token = strtok(line, ",");//splitting the line into substrings according to ',' .
                while (token != NULL)
                {
                    available[j]= atoi(token);j++;
                    token = strtok(NULL, ",");
                }
            }
    numberOfColumns1=j;//done
    fclose(fr);
//available reading done.................

    fr=fopen("Request.csv","r");//open the second file.

            i=0;j=0;int s=0,f=0;
    while(fgets(line,1000,fr)){numberOfLines1++;s=0;
        if(i==0){i++;continue;}//Don't read the first line.

        char *token = strtok(line, ",");
        while (token != NULL){
           if(s==0){s++;token = strtok(NULL, ",");//cout<<token;
               continue;}//Don't read the first column.
            request[f][j]= atoi(token);j++;
            token = strtok(NULL, ",");
        }
        if(f!=0){
            if(j!=numberOfColumns2){return 1;}
        }
        f++;
        if(j>numberOfColumns2)numberOfColumns2=j;//assining a value to numberofrows.
        j=0;
    }
    fclose(fr);
//request reading done.................

    fr=fopen("Allocation.csv","r");//open the third file.

    i=0;j=0;s=0;f=0;
    while(fgets(line,100,fr)){numberOfLines2++;s=0;
        if(i==0){i++;continue;}//Don't read the first column.

        char *token = strtok(line, ",");
        while (token != NULL)
        {
            if(s==0){s++;token = strtok(NULL, ",");
                continue;}//Don't read the first column.

            allocation[f][j]= atoi(token);j++;
            token = strtok(NULL, ",");
        }
        if(f!=0){
            if(j!=numberOfColumns2){return 1;}
        }
        f++;
        if(j>numberOfColumns3)numberOfColumns3=j;//assining a value to numberofrows.
        j=0;
    }
    fclose(fr);

    if((numberOfColumns1 == numberOfColumns2) && (numberOfColumns1 == numberOfColumns3) && (numberOfColumns2 == numberOfColumns3)) m=numberOfColumns3;
    else flag=1;//this means that the files are inconsistent.
    if(numberOfLines2!= numberOfLines1)flag=1;//this means that the files are inconsistent.
    else n=numberOfLines1-1;
    if(numofrows1>1)flag = 1;
    //allocation reading done...

return flag;
}

void PrintThings(int available[100], int request[100][100], int allocation[100][100]){

    int i,j;
    cout << "Process\tAllocation\tRequest \tAvailable";
    for ( i=0; i < n; i++){// for all process, print the allocation and request, and print the available matrix.
        cout << "\nP" <<i+1<< "       ";
        for (j = 0; j < m; j++){
            cout << allocation[i][j] << " ";
            }
        cout << " \t";
        for (j = 0; j < m; j++){
            cout << request[i][j] << " ";
            }
        cout << " \t";
        if (i == 0)
        {
            for (j = 0; j < m; j++)
                cout << available[j] << " ";
        }
    }
}

void DetectionAlgo(int available[100], int request[100][100], int allocation[100][100]){
    int finish[100]={0}, flag = 1,c;
    int dead[100];//here will the deadlocked processes be.
    int nodead[100];//here will the nondeadlocked processes be.
    int j;
    int fornodead = 0;

    while(flag) {
        flag=0;

        for (int p = 0; p < n; p++) {//processes loop
            c = 0;
            for (int reso = 0; reso < m; reso++) {//resourses loop.   m loop
                if ((finish[p] == 0) && (request[p][reso] <= available[reso])) {
                    c++;// if c equal m, then all request of a specific process is less than or equal to available.
                    if (c == m) {//if enter this, that mean that this process can do its job (the request is less than available).

                        for (int reso = 0; reso < m; reso++) available[reso] += allocation[p][reso];//change the available matrix to it's new value.

                        finish[p] = 1;//the process p has finished its job.
                        nodead[fornodead] = p + 1;fornodead++;
                        flag=1;//to check all processes again if there is a process its finish =0 to test them.
                            //this flag mean also, that if a process does its job, that means that the available matrix has changed
                            //and we need to test all processes that has finish = 0 again to check if it can do its job or no.
                    }

                }
            }

        }
}

j=0;int countertotestdead=0;//if this counter is bigger than 0, that means that there is a deadlock.
for(int i=0;i<n;i++){
    if(finish[i]==0){dead[j]=i+1;j++;countertotestdead++;}
    }

if(countertotestdead > 0) flag=0;//deadlock
else flag =1;//no deadlock

if(flag==0){
        cout<<"\nDeadLock\nDeadlocked Processes are --> ";
        for(int i=0;i<j;i++){ cout<<"P"<<dead[i];if(i!=j-1)cout<<",";}cout<<endl;
    }

else {
    cout<<"\nNo DeadLock\n"<<"With sequence <";
    for(int i=0;i<fornodead;i++){
        cout<<"P"<<nodead[i];
        if(i!=fornodead-1)cout<<",";
       }
    cout<<">\n";
   }
}
