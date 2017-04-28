#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Node{

public:
	int value;
	char *name;
	Node **children;
	int childCount;

	Node(): value(-1), name(NULL), children(NULL), childCount(0){
	}

	~Node(){
		for(int i=0; i< childCount; i++){
			delete children[i];
		}
		delete [] children;
	}
	
		friend class Trie;
	
	
};

class Trie{

public:
	bool insertNumber(Node *root, long int number, char*string){
		if(number== 0){	
			return true;
		}
		
		int currentDigit= number% 10;

		if(root-> children== NULL){
			root-> children= new Node*[10];
			root-> children[0]= new Node;

			root-> children[0]-> value= currentDigit;
			root-> childCount+= 1;
			
			number/= 10;

			if(insertNumber(root-> children[root-> childCount- 1], number, string)){
				root-> children[root-> childCount-1]->name= new char[strlen(string)+ 1];
				strcpy(root->children[(root->childCount)-1]->name, string);
			}

			return false;
		}

		for(int i=0; i< root-> childCount; i++){
			if(root-> children[i]-> value== currentDigit){
				number/= 10;
				insertNumber((root-> children[i]), number, string);
				return false;
			}
		}

		root-> children[root-> childCount]= new Node;
		root-> children[root-> childCount]-> value= currentDigit;
		root-> childCount+= 1;
		number/= 10;
		
		if(insertNumber(root-> children[root-> childCount- 1], number, string)){
			root-> children[root-> childCount-1]->name= new char[strlen(string)+ 1];
			strcpy(root->children[(root->childCount)-1]->name, string);
		}

		
		return false;

}

void search(Node *root, long int number){
	if(root-> childCount== 0){
		cout<< "contact name is:";
		cout<< " "<< root-> name<< endl;
	}

	int currentDigit= number% 10;

	for(int i=0; i< root-> childCount; i++){
		if(root-> children[i]-> value== currentDigit){
			number/= 10;
			// cout<< currentDigit;
			search((root-> children[i]), number);			
		}
	}

	return ;
}

void print(Node *root){
	cout<< root-> childCount;
	if(root-> childCount== 0){
		return	;
	}

	for(int i=0; i< root-> childCount; i++){
		cout<< root-> children[i]->value<< " ";
	}

	cout<< endl;

	for(int i=0; i< root-> childCount; i++){
		print((root-> children[i]));
	}

}

};




int main(){
	Node *root;
	root= new Node;
	Trie t;
	int q;
	long int n;
	char name[40];
	bool stop= false;
	char ch;

	while(1){
		cout<< "Enter your Query"<< endl;
		cout<< "1) Enter new contact."<< endl;
		cout<< "2) Search a contact."<< endl;
		cout<< "3) Exit."<< endl;
		
		cin>> q;
		ch= cin.get();

		switch(q){
			case 1: cout<< "Enter the name of contact"<< endl;
					cin.getline(name, 40);
					cout<< "Enter the contact number"<< endl;
					cin>> n;
					t.insertNumber(root, n, name);
					break;

			case 2: cout<< "Enter the contact number"<< endl;
					cin>> n;
					t.search(root, n);
					break;

			case 3: stop= true;
					break;	

			default: cout<<"invalid entry"<< endl;					
		}

		if(stop){
			break;
		}
		q=0;
	}
	
	
	delete root;

	return 0;
}