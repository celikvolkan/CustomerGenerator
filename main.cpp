#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define CUSTOMER_LIST_SIZE	(100)

using namespace std;
string FirstName = "FName.txt";
string SurName = "SName.txt";
string CustomerList = "CustomerList.txt";

int main(int argc, char** argv) {
	
	ifstream fFName, fSName;	
	ofstream fCustomer;
	string fname, sname, customer;
	int i, j, randNo1, randNo2, fNameCounter, sNameCounter, customerCounter = CUSTOMER_LIST_SIZE;
	
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
	fCustomer.open(CustomerList.c_str(), ios_base::out);
	if(!fCustomer.is_open()){
		cerr << "Error in output file opening\n";
		exit(EXIT_FAILURE);
	}
	srand(time(0));
	cout << endl;
	while(customerCounter--)
	{
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
		// bu isimli müsteri daha önce yaratýlmýþ mý, kontrol et!
		
		cout << CUSTOMER_LIST_SIZE - customerCounter << " " << customer;
		fCustomer << customer;
		// müþterinin yanýna numarasýný da ekle.			
	}
	
	fFName.close();
	fSName.close();
	fCustomer.close();
	
	return 0;
}
