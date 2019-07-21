#include <iostream>
#include <fstream>
#include <string>
//#include <cstring>
#include <cstdlib>
#include <ctime>
#include <sstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define CUSTOMER_LIST_SIZE	(20000)

using namespace std;
string FirstName = "FName.txt";
string SurName = "SName.txt";
string CustomerList = "CustomerList.txt";

int main(int argc, char** argv) {
	
	ifstream fFName, fSName;	
	fstream fCustomer;
	string fname, sname, customer, tempBuffer;
	string const telnobase = "053"; 
	int telno[4],  i, j, randNo1, randNo2, fNameCounter, sNameCounter, regenerationCounter = 0, customerCounter = CUSTOMER_LIST_SIZE;
	//bool regnoflag = false;
	fNameCounter = sNameCounter = 0;
		
	fFName.open(FirstName.c_str());
	if(!fFName.is_open()){
		cerr << "Error in first name file opening\n";
		exit(EXIT_FAILURE);
	}
		
	while(getline(fFName, fname)){
		++fNameCounter;
	}	
	cout << "First name amount: " << fNameCounter << endl << endl;
	
	fSName.open(SurName.c_str());
	if(!fSName.is_open()){
		cerr << "Error in surname file opening\n";
		exit(EXIT_FAILURE);
	}	
	while(getline(fSName, sname)){
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
		REGENERATE_NAME:
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
		
		customer = fname + " " + sname;			
		if( tempBuffer.find(customer) != string::npos ){
			if(++regenerationCounter < 10){
				//cout << "\t" << regenerationCounter << ". regeneration for " << customer << endl;			
				goto REGENERATE_NAME;
			}
		}
		regenerationCounter = 0;
		
		REGENERATE_TEL_NO:
		stringstream *pss = new stringstream ;
		/* Add tel no 053x xxx xx xx */
		pss->fill('0');
		telno[0] = rand() % 10;
		*pss << telnobase << telno[0] << ' ';
		
		pss->width(3);
		telno[1] = rand() % 1000;
		*pss << telno[1] << ' ';
		
		pss->width(2);
		telno[2] = rand() % 100;
		*pss << telno[2] << ' ';
		
		pss->width(2);
		telno[3] = rand() % 100;
		*pss << telno[3];
		
		//telno control
		if( tempBuffer.find(pss->str()) != string::npos ){
			if(++regenerationCounter < 10){
				cout << "\t" << regenerationCounter << ". regeneration for " << pss->str() << "****************" << endl;
				//regnoflag = true;			
				goto REGENERATE_TEL_NO;
			}
		}		
		regenerationCounter = 0;
		
		customer += "\t" + pss->str();
		delete pss;
		
		customer += "\n";
		cout << CUSTOMER_LIST_SIZE - customerCounter << " " << customer;
		tempBuffer += customer;	
	}
	fCustomer << tempBuffer;
	
	fFName.close();
	fSName.close();
	fCustomer.close();
	
	//if(true == regnoflag)
	//	cout << "Regeneration for no worked!!\n";
	
	return 0;
}

