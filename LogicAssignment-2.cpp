#include <string>
#include <iostream>

using namespace std;


string proof[100];
int n;												//number of lines in the proof
int ans[100];                                       //initializing an array that stores 1 or 0 at the corresponding index based on wether line in proof is valid or not
string statement[100];                              //initializing an array that stores statement part of each corresponding line in the proof
string rule[100];                                   //initializing an array that stores rule part of each corresponding line in the proof
int line1[100];                                     //initializing an array that stores line 1  of each corresponding line in the proof
int line2[100];                                     //initializing an array that stores line 2 of each corresponding line in the proof

void splitline(string,int);                         //function to split a line in the proof into statement ,rule ,line 1 and line 2
void rule_check(string , int);                      //function to check the rule of the line in the proof and make the corresponding function call
void premise(string, int);                          //function to check validity if the rule is a premise
void andintroduction(string, int);                  //function to check validity if the rule is an AND introductoin
void andelimination_1(string, int);                 //function to check validity if the rule is an AND elimination 1
void andelimination_2(string, int);                 //function to check validity if the rule is an AND elimination 2 
void orintroduction_1(string, int);                 //function to check validity if the rule is an OR introduction 1
void orintroduction_2(string, int);                 //function to check validity if the rule is an OR introduction 2
void implieselimination(string, int);               //function to check validity if the rule is an implies elimination
void modustollens(string, int);                     //function to check validity if the rule is a Modus Tollens 

int linevalue(string str){
    if(str=="P"){
        return -1;
    }
    else if(str=="^e1"||str=="^e2")
    {
        return -2;
    }
    else if(str=="Vi"){
        return -3;
    }
    return 0;
}

void splitline(string arr,int i){							//this function splits proof line into statement, rule, line1 and line2 or proof
	
	string tempstring,s1,s2;
    int s3=0;
    int s4=0;
    int temp=0; 
    for(int i=0;i<arr.length();i++){
        tempstring+=arr[i];									//creating a temp string to temporarily store contents before every '/'
        if(arr[i+1]=='/'){
            
            switch(temp){
                case 0:
                    s1= tempstring;							//assigning the temp string tp s1, s2 and s3 respectively	
                    break;
                case 1: 
                    s2= tempstring;
                    break;
                case 2:
                    s3= stoi(tempstring);
                    break;
            }
            temp++;
            tempstring = "";
            i++;
        }
    }
    if(temp==1){
        s2=tempstring;
        s3=s4=linevalue(tempstring);
    }
    else if(temp==2){
        s3= stoi(tempstring);
        s4 = 0;
    }
    else if(temp==3){
       s4 = stoi(tempstring);
    }

    statement[i] = s1;									//assigning statemnt line
    rule[i] = s2;                                       //assigning rule line
    line1[i]= s3;										//assigning line1 of proof				
    line2[i]=s4;										//assigning line2 of proof
	
}



void rule_check(string arr,int i)
{
	if (arr[0]=='P')                                   //if the rule is premise makes a premise() function call
    {
        premise(proof[i],i);
    }
    
    else if((arr[0]=='^')&&(arr[1]=='i'))
    {
        andintroduction(statement[i],i);               //if the rule is AND introduction makes a andintroduction() function call
    }
    
    else if((arr[0]=='^')&&(arr[1]=='e')&&(arr[2]=='1'))
    {
        andelimination_1(statement[i],i);              //if the rule is AND elimination 1 makes a andelimination_1() function call
    }
    
    else if((arr[0]=='^')&&(arr[1]=='e')&&(arr[2]=='2'))
    {
        andelimination_2(statement[i],i);              //if the rule is AND elimination 2 makes a andelimination_2() function call
    }
    
    else if((arr[0]=='v')&&(arr[1]=='i')&&(arr[2]=='1'))
    {
        orintroduction_1(statement[i],i);             //if the rule is OR introduction 1 makes a orintroduction_1() function call  
    }
    
    else if((arr[0]=='v')&&(arr[1]=='i')&&(arr[2]=='2'))
    {
        orintroduction_2(statement[i],i);             //if the rule is OR introduction 2 makes a orintroduction_2() function call  
    }
    
    else if((arr[0]=='-')&&(arr[1]=='>')&&(arr[2]=='e'))
    {
        implieselimination(statement[i],i);           //if the rule is an implies elimination ,makes a implieselimination() function call
     }
    
    else if((arr[0]=='M')&&(arr[1]=='T'))
    {
        modustollens(statement[i],i);                  //if the rule is Modus Tollens ,makes a modustollens() function call
    }
}

void premise(string arr,int i){
    ans[i] = 1;                                       //since premise is always valid the corresponding entry in the ans array is made 1
}

void andintroduction(string arr, int i){               
	int leftbrackets = 0,rightbrackets = 0;
	string s1,s2;
	int j = 1;
	while(j<arr.length() && !(arr[j]=='^'&& (leftbrackets  == rightbrackets))){
		if(arr[j]=='('){                                //counts the number of left brackets
			leftbrackets++;
		}
		if(arr[j]==')'){
			rightbrackets++;                            //counts the number of right brackets 
		}
		s1 = s1 + arr[j];                               //s1 is the string to th left of ^
		j++;
	}
	j++;
	for(;j<arr.length()-1;j++){
		
		s2 = s2 + arr[j];                           //s2 is the string to the right of ^
	}
	
	if(s1.compare(statement[line1[i]])==0 && s2.compare(statement[line2[i]]) == 0){  
		ans[i] = 1;                                     //if both the conditions are satisfied corresponding entry in the ans array is made 1
	}
	else{
		ans[i] = 0;                                     //if either one of the conditions aren't satisfied then the entry in the ans array is made 0
	}
}

void andelimination_1(string arr, int i){
    int a;
    a = line1[i];
    string arr1 = statement[a];
    int leftbrackets = 0,rightbrackets = 0;
	string s1,s2;
	int j = 1;
	while(j<arr1.length() && !(arr1[j]=='^'&& (leftbrackets  == rightbrackets))){
		if(arr1[j]=='('){                                //counts the number of left brackets
			leftbrackets++;
		}
		if(arr1[j]==')'){
			rightbrackets++;                            //counts the number of right brackets 
		}
		s1 = s1 + arr1[j];                               //s1 is the string to th left of ^
		j++;
	}
	j++;
	for(;j<arr1.length()-1;j++){
		
		s2 = s2 + arr1[j];                           //s2 is the string to the right of ^
	}
	
    if(s1.compare(arr)){                            //if both the conditions are satisfied corresponding entry in the ans array is made 1
		ans[i] = 1;
	}
	else{
		ans[i] = 0;                                 //if either one of the conditions aren't satisfied then the entry in the ans array is made 0
	}
    
    
	
}

void andelimination_2(string arr, int i){
    int a;
    a = line1[i];
    string arr1 = statement[a];
    int leftbrackets = 0,rightbrackets = 0;
	string s1,s2;
	int j = 1;
	while(j<arr1.length() && !(arr1[j]=='^'&& (leftbrackets  == rightbrackets))){
		if(arr1[j]=='('){                                //counts the number of left brackets
			leftbrackets++;
		}
		if(arr1[j]==')'){
			rightbrackets++;                            //counts the number of right brackets 
		}
		s1 = s1 + arr1[j];                               //s1 is the string to th left of ^
		j++;
	}
	j++;
	for(;j<arr1.length()-1;j++){
		
		s2 = s2 + arr1[j];                           //s2 is the string to the right of ^
	}
    if(s2.compare(arr)){                                        //if both the conditions are satisfied corresponding entry in the ans array is made 1
		ans[i] = 1;
	}
	else{
		ans[i] = 0;                                             //if either one of the conditions aren't satisfied then the entry in the ans array is made 0
	}
    
	
}

void orintroduction_1(string arr, int i){
    int leftbrackets = 0,rightbrackets = 0;
	string s1,s2;
	int j = 1;
	while(j<arr.length() && !(arr[j]=='v'&& (leftbrackets  == rightbrackets))){
		if(arr[j]=='('){                                //counts the number of left brackets
			leftbrackets++;
		}
		if(arr[j]==')'){
			rightbrackets++;                            //counts the number of right brackets 
		}
		s1 = s1 + arr[j];                               //s1 is the string to th left of ^
		j++;
	}
	j++;
	for(;j<arr.length()-1;j++){
		
		s2 = s2 + arr[j];                           //s2 is the string to the right of ^
	}
	if(s1.compare(statement[line1[i]]) == 0){                       //if both the conditions are satisfied corresponding entry in the ans array is made 1
		ans[i] = 1;
	}
	else{
		ans[i] = 0;                                                 //if either one of the conditions aren't satisfied then the entry in the ans array is made 0
	}
}

void orintroduction_2(string arr, int i){
    int leftbrackets = 0,rightbrackets = 0;
	string s1,s2;
	int j = 1;
	while(j<arr.length() && !(arr[j]=='^'&& (leftbrackets  == rightbrackets))){
		if(arr[j]=='('){                                //counts the number of left brackets
			leftbrackets++;
		}
		if(arr[j]==')'){
			rightbrackets++;                            //counts the number of right brackets 
		}
		s1 = s1 + arr[j];                               //s1 is the string to th left of ^
		j++;
	}
	j++;
	for(;j<arr.length()-1;j++){
		
		s2 = s2 + arr[j];                           //s2 is the string to the right of ^
	}
    if(s2.compare(statement[line1[i]]) == 0){                       //if both the conditions are satisfied corresponding entry in the ans array is made 1
		ans[i] = 1;
	}
	else{
		ans[i] = 0;                                                 //if either one of the conditions aren't satisfied then the entry in the ans array is made 0
	}	
}

void implieselimination(string arr, int i){
    int a;
    a = line1[i];
    string arr1 = statement[a];
    int leftbrackets = 0,rightbrackets = 0;
	string s1,s2;
	int j = 1;
	while(j<arr1.length() && !(arr1[j]=='-'&& (leftbrackets  == rightbrackets))){
		if(arr1[j]=='('){                                //counts the number of left brackets
			leftbrackets++;
		}
		if(arr1[j]==')'){
			rightbrackets++;                            //counts the number of right brackets 
		}
		s1 = s1 + arr1[j];                               //s1 is the string to th left of ^
		j++;
	}
	j++;
	j++;
	for(;j<arr1.length()-1;j++){
		
		s2 = s2 + arr1[j];                           //s2 is the string to the right of ^
	}
    if(s1.compare(statement[line2[i]]) == 0 && s2.compare(arr)==0){                 //if both the conditions are satisfied corresponding entry in the ans array is made 1
		ans[i] = 1;
	}
	else{
		ans[i] = 0;                                                               //if either one of the conditions aren't satisfied then the entry in the ans array is made 0
	}

}

void modustollens(string arr, int i){
    int a;
    a = line1[i];
    string arr1 = statement[a];
    int leftbrackets = 0,rightbrackets = 0;
	string s1="~",s2="~";
	int j = 1;
	while(j<arr1.length() && !(arr1[j]=='-'&& (leftbrackets  == rightbrackets))){
		if(arr1[j]=='('){                                //counts the number of left brackets
			leftbrackets++;
		}
		if(arr1[j]==')'){
			rightbrackets++;                            //counts the number of right brackets 
		}
		s1 = s1 + arr1[j];                               //s1 is the string to th left of ^
		j++;
	}
	j++;
	j++;
	for(;j<arr1.length()-1;j++){
		
		s2 = s2 + arr1[j];                           //s2 is the string to the right of ^
	}
    if(s2.compare(statement[line2[i]]) == 0 && s1.compare(arr)==0){                 //if both the conditions are satisfied corresponding entry in the ans array is made 1
		ans[i] = 1;
	}
	else{
		ans[i] = 0;                                                                 //if either one of the conditions aren't satisfied then the entry in the ans array is made 0
	}
    
	
}




int main(){
	cout << "enter the number of lines in the proof:";
	cin >> n ;

	for(int i = 1;i <= n;i++)											
	{ 
	   cin >> proof[i];
	}

	for(int i=1;i<=n;i++){	   
		splitline(proof[i],i);     
		
	}
	for(int i=1;i<=n;i++){	   
		rule_check(rule[i],i);     
	}
	

	int count = 0;

	for(int a = 1;a <= n;a++)
	{
	   if(ans[a] == 1){
		   count++;
	   }
	}
	
	cout<<"__________________________________________________________________________________________________"<<endl;
	cout<< "STATEMENT\tRULE\t\tLINE1\t\tLINE2\t"<<endl;
	
	for(int i=1;i<=n;i++)
	{
		cout<<statement[i]<< "\t\t"<<rule[i]<<"\t\t"<<line1[i]<<"\t\t"<<line2[i]<<"\t\t"<<ans[i]<<endl;
	}

	if(count == n){
		printf("This proof is Valid!!!");
	}
	
	else{
	    printf("This proof is Invalid");
	}

	
	
	return 0;
}