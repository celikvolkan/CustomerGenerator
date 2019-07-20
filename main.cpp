#include <iostream>
#include <fstream>
#include <string>
//#include <cstring>
#include <cstdlib>
#include <ctime>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define CUSTOMER_LIST_SIZE	(100)

using namespace std;
string FirstName = "FName.txt";
string SurName = "SName.txt";
string CustomerList = "CustomerList.txt";

//bool check_customer_existence(string &rstFile, string st);

int main(int argc, char** argv) {
	
	ifstream fFName, fSName;	
	fstream fCustomer;
	string fname, sname, customer, tempBuffer;
	int i, j, randNo1, randNo2, fNameCounter, sNameCounter, regenerationCounter = 0, customerCounter = CUSTOMER_LIST_SIZE;
	
	fstream f1;
	
	fNameCounter = sNameCounter = 0;
		
	fFName.open(FirstName.c_str());
	if(!fFName.is_open()){
		cerr << "Error in first name file opening\n";
		exit(EXIT_FAILURE);
	}
		
	while(getline(fFName, fname)){
		//cout << fname << endl;
		//cout << "file1 pointer " << fFName.tellg() << endl;
		++fNameCounter;
	}	
	cout << "First name amount: " << fNameCounter << endl << endl;
	
	fSName.open(SurName.c_str());
	if(!fSName.is_open()){
		cerr << "Error in surname file opening\n";
		exit(EXIT_FAILURE);
	}	
	while(getline(fSName, sname)){
		//cout << sname << endl;
		++sNameCounter;
	}	
	cout << "Surname amount: " << sNameCounter << endl;	
	
	/****** Creating Customer List File ******/	
	fCustomer.open(CustomerList.c_str(), ios_base::out | ios_base::in | ios_base::trunc);
	if(!fCustomer.is_open()){
		cerr << "Error in output file opening\n";
		exit(EXIT_FAILURE);
	}
	srand(time(0));
	cout << endl;
	while(customerCounter--)
	{
		REGENERATE:
		randNo1 = rand() % fNameCounter + 1;
		fFName.clear();
		fFName.seekg(0, ios_base::beg);
		for(i=0; i < randNo1; i++){		
			getline(fFName, fname);			
		}	
		
		randNo2 = rand() % sNameCounter + 1;
		fSName.clear();
		fSName.seekg(0, ios_base::beg);		
		for(i=0; i < randNo2; i++){		
			getline(fSName, sname);
		}
		
		customer = fname + " " + sname + "\n";	
		//if ( true == check_customer_existence(tempBuffer, customer) ){		
		if( tempBuffer.find(customer) != string::npos ){
			if(++regenerationCounter < 10){
				cout << "\t" << regenerationCounter << ". regeneration for " << customer;			
				goto REGENERATE;
			}
		}
		regenerationCounter = 0;
		cout << CUSTOMER_LIST_SIZE - customerCounter << " " << customer;
		tempBuffer += customer;
		// müþterinin yanýna numarasýný da ekle.			
	}
	fCustomer << tempBuffer;
	
	fFName.close();
	fSName.close();
	fCustomer.close();
	
	return 0;
}
/*
bool check_customer_existence(string &rstFile, string st)
{
	string line;
	
	while(){		
		getline(rstFile, line);
		if(line == st)
			return true;			
	}
	return false;	
}
*/
