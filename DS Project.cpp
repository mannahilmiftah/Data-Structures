#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<typeinfo>
#include<iomanip>
#include<vector>
#include <iterator>
#include<map>
#include<algorithm>
#include <bits/stdc++.h>
using namespace std;

class Node{
	string category;
	string brand;
	float price;
	int view;
	int purchase;
	int cart;
	Node* left;
	Node* right;
public:
	Node(string c, string b, float p):category(c), view(0), purchase(0),cart(0),  brand(b), price(p), left(NULL),right(NULL){}
	//copyTree
	Node(string b, float pr, int v, int p, int c, Node* l = NULL, Node* r = NULL):view(v), purchase(p), cart(c),  brand(b), price(pr), left(l),right(r){}
	//phone Node
	Node(string b, Node* r = NULL):view(0), purchase(0), cart(0), brand(b), right(r){}
	friend class BST;
	
};
class categoryNode{
	string brand;
	int view;
	int purchase;
	int cart;
	categoryNode* right;
public:
	categoryNode():brand(" "), view(0), purchase(0),cart(0), right(NULL){}
	categoryNode(string b):brand(b), view(0), purchase(0),cart(0), right(NULL){}
	friend class categoryList;
};
class listNode{
	string category_code;
	int count;
	listNode *next;
	public:
		listNode():category_code(""), count(0), next(NULL){}
		listNode(string cc, int c, listNode* n):category_code(cc), count(c), next(n){}
		listNode(string cc):category_code(cc), count(0), next(NULL){}
		friend class unique_category;
};
class categoryList{
	categoryNode* head;
public:
	categoryList():head(NULL){}
	
	void setHead(categoryNode* h){
		head = h;
	}
	
	categoryNode* getHead() const{
		return head;
	}
	
	categoryList(const categoryList& v){
		categoryNode* p1;
		categoryNode* p2;
		if(v.head == NULL){
			head=NULL;
		}
		else{
			head=new categoryNode();
			head->brand=v.head->brand;
			head->view=v.head->view;
			head->purchase=v.head->purchase;
			head->cart=v.head->cart;
			p1=head;
			p2=v.head->right;
		}
		while(p2){
			p1->right= new categoryNode();
			p1=p1->right;
			p1->brand=p2->brand;
			p1->view=p2->view;
			p1->purchase=p2->purchase;
			p1->cart=p2->cart;
			p2=p2->right;
		}
		p1->right=0;
	}
	
	categoryList&  operator=(categoryList rhs){
		swap(rhs.head,head);
		return *this;
	}
	
	void deletelist(){
		categoryNode* current=head;
		while(current!=NULL){
			categoryNode* next=current->right;
			delete current;
			current=next;
		}
		head=NULL;
	}
	
	~categoryList(){
		deletelist();
	}
	
	bool searchBrand(string e, string b){
		categoryNode* current = head;
		while(current->right != NULL){
			if(current->brand == b){
				if(e == "view")
					current->view++;
				else if(e == "purchase")
					current->purchase++;
				else if(e == "cart")
					current->cart++;
				return true;
			}
			current = current->right;
		}
		return false;
	}
	
	void insertCategory(string e, string b){
		if(head != NULL){
			if(!searchBrand(e, b)){
				categoryNode* newNode = new categoryNode(b);
				categoryNode* current = head;
				while(current->right != NULL)
					current = current->right;
				current->right = newNode;
				if(e == "view")
					current->view++;
				else if(e == "purchase")
					current->purchase++;
				else if(e == "cart")
					current->cart++;
			}
		}
		else{
			categoryNode* newNode = new categoryNode(b);
			head = newNode;	
			if(e == "view")
				newNode->view++;
			else if(e == "purchase")
				newNode->purchase++;
			else if(e == "cart")
				newNode->cart++;		
		}		
	}
	
	void printCategory(){
		categoryNode* current = head;
		while(current != NULL){
			if(current->brand.length() < 8)
	    		cout << current->brand << "\t\t"  << current->view << "\t\t" << current->cart << "\t\t" << current->purchase << endl;
	    	else
	    		cout << current->brand << "\t"  << current->view << "\t\t" << current->cart << "\t\t" << current->purchase << endl;
	    	cout << "--------------------------------------------------------------------------------" << endl; 
			current = current->right;
		}
	}
	
	void printcategory(){
		categoryNode* current = head;
		int i = 0;
		while(i < 5){			
			cout << current->brand << endl; 
			current = current->right;
			i++;
		}
	}

	void removeDuplicates(){
		categoryNode *p1, *p2, *dup;
		p1 = head;
		while(p1 != NULL && p1->right != NULL){
			p2 = p1;
			while(p2->right != NULL){
				if(p1->brand == p2->right->brand){
					p2->right = p2->right->right;
				}
				else
					p2 = p2->right;
			}
			p1 = p1->right;
		}
	}

	categoryNode* merge(categoryNode* first, categoryNode* second, string choice){
		categoryNode* merged = new categoryNode();
		categoryNode* temp = new categoryNode();
		merged = temp;
		while(first != NULL && second != NULL){
			if(choice == "view"){
				if(first->view >= second->view){
					temp->right = first;
					first = first->right;
				}
				else{
					temp->right = second;
					second = second->right;
				}
			}
			else if(choice == "cart"){
				if(first->cart >= second->cart){
					temp->right = first;
					first = first->right;
				}
				else{
					temp->right = second;
					second = second->right;
				}
			}
			else if(choice == "purchase"){
				if(first->purchase >= second->purchase){
					temp->right = first;
					first = first->right;
				}
				else{
					temp->right = second;
					second = second->right;
				}
			}
			temp = temp->right;
		}
		
		while(first != NULL){
			temp->right = first;
			first = first->right;
			temp = temp->right;
		}
		
		while(second != NULL){
			temp->right = second;
			second = second->right;
			temp = temp->right;
		}
		return merged->right;
	}
	
	categoryNode* Middle(categoryNode* current){
		categoryNode* slow = current;
		categoryNode* fast = current->right;
		while(slow->right != NULL && (fast != NULL && fast->right != NULL)){
			slow = slow->right;
			fast = fast->right->right;
		}
		return slow;
	}

	categoryNode* mergeSort(categoryNode* current, string choice){
		if(current->right == NULL)
			return current;
		categoryNode* mid = new categoryNode();
		categoryNode* head_2 = new categoryNode();
		categoryNode* first;
		categoryNode* second;
		mid = Middle(current);
		head_2 = mid->right;
		mid->right = NULL;
		categoryNode* listHead = merge(mergeSort(current, choice), mergeSort(head_2, choice), choice);
		return listHead;
	}
};

class unique_category{
	listNode *head;
	int size = 0;
	public:
		unique_category():head(NULL){}
		
		unique_category(const unique_category &v){
			listNode* p1;
			listNode* p2;
			if(v.head == NULL){
				head=NULL;
			}
			else{
				head=new listNode();
				head->category_code=v.head->category_code;
				head->count=v.head->count;
				p1=head;
				p2=v.head->next;
			}
			while(p2){
				p1->next= new listNode();
				p1=p1->next;
				p1->category_code=p2->category_code;
				p1->count=p2->count;
				p2=p2->next;
			}
			p1->next=0;
		}
		
		void deletecatagorylist(){
			listNode* current=head;
			while(current!=NULL){
				listNode* next=current->next;
				delete current;
				current=next;
			}
				head=NULL;
		}
		~unique_category(){
			deletecatagorylist();
		}
		
		void addatend(string s){
			int flag=0;
			listNode *newnode=new listNode(s);
			if(head==NULL){
				head=newnode;
				head->count++;
				return;
			}
			listNode *temp=head;
			while(temp->next!=NULL){
				if(temp->category_code==s){
					flag=1;
					temp->count++;
				}
				temp=temp->next;
			}
			if(!flag)
			{
				temp->next=newnode;
			    temp=newnode;
			    temp->count++;
			}
			size++;
			return;
		}
		void removeduplicates(){
		listNode *temp1, *temp2;
		temp1 = head;
		while(temp1 != NULL && temp1->next != NULL){
			temp2 = temp1;
			while(temp2->next != NULL){
				if(temp1->category_code == temp2->next->category_code){
					temp2->next = temp2->next->next;
				}
				else
					temp2 = temp2->next;
			}
			temp1 = temp1->next;
		}
	}
		void sort()
        {
        	string s;
            listNode *temp=head;
            listNode *temp1;
            while(temp!=NULL)
            {
                temp1=temp->next;
                while(temp1!=NULL)
                {
                	string a=checkstring(temp1->category_code);
                	string b=checkstring(temp->category_code);
                    if(a<b)
                    {
                        s=temp1->category_code;
                        temp1->category_code=temp->category_code;
                        temp->category_code=s;
                    }
                    temp1=temp1->next;
                }
                temp=temp->next;
            }
        }
        string checkstring(string s)
        {
            string s1=s;
            for(int i=0;i<s.length();i++)
            {
                if(s[i]>='A' && s[i]<='Z')
                s1[i]=s[i]+32;
            }
            return s1;
        }
		void display(){
			listNode *curr = head;
			if(head == NULL){
				cout << "List is empty\n" << endl;
			}
			cout << "Categories\t\tItems Present" << endl;
			cout << "---------------------------------------------------" << endl;
			while(curr->next != NULL){
				if(curr->category_code.length() < 8)
		    		cout << curr->category_code << "\t\t"  << curr->count << endl;
		    	else
		    		cout << curr->category_code << "\t\t"  << curr->count << endl;
		    	cout << "--------------------------------------------------------------------------------" << endl; 
				curr = curr->next;
			}
			cout << "\t\t\t\t\tTotal Items: " << size << endl;
			cout << "--------------------------------------------------------------------------------" << endl; 
		}
};

class BST{
	Node* root;
public:
	BST():root(NULL){}
	
	Node* copyTree(Node* t){
		Node* newlptr, *newrptr;
		if(t == 0)
			return 0;
		if(t->left != 0)
			newlptr = copyTree(t->left);
		else
			newlptr = 0;
		if(t->right != 0)
			newrptr = copyTree(t->right);
		else
			newrptr = 0;

		Node* newnode = new Node(t->brand,t->price, t->view, t->purchase, t->cart, newlptr,newrptr);

		return newnode;
	}
	
	BST& operator = (const BST& rhs){
		if (this == &rhs)
			return *this;
		deleteTree(rhs.root);
		root = copyTree(rhs.root);
		return *this;
	}
	
	void deleteTree(Node* root){
		if (root){
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
			root = 0;
		}
	}
	
	Node* getRoot() const{
		return root;
	}
	
	bool search(string c, string e, string b, string p){
		Node* current = root;
		Node* parent = NULL;
		while(current != NULL){
			if(b == current->brand){
				if(e == "view")
					current->view++;
				else if(e == "purchase")
					current->purchase++;
				else if(e == "cart")
					current->cart++;
				current->price += stof(p);
				return true;
			}
			else if(b > current->brand){
				parent = current;
				current = current->right;
			}
			else{
				parent = current;
				current = current->left;
			}
		}
		return false;			
	}
	
	void Insert(string c, string e, string b, string p){	
		if(root != NULL){
			if(!search(c, e, b, p)){
				//insertion
				if(b != ""){
					Node* newNode = new Node(c, b, stof(p));
					Node* current = root;
					Node* prev = NULL;
					while(current != NULL){
						if(current->brand > b){
							prev = current;
							current = current->left;
						}
						else if(current->brand < b){
							prev = current;
							current = current->right;
						}
					}
					
					if(prev->brand > b)
						prev->left = newNode;
					else
						prev->right = newNode;
					if(e=="view")
						newNode->view++;
					else if(e=="cart")
						newNode->cart++;
					else if(e=="purchase")
						newNode->purchase++;
				}
				
			}			
		}
		else{
			Node* newNode = new Node(c, b, stof(p));
			if(e=="view")
				newNode->view++;
			else if(e=="cart")
				newNode->cart++;
			else if(e=="purchase")
				newNode->purchase++;
			root = newNode;
		}	
		return;	
	}
	void InOrder(Node* root, map<string, int>& brandsView, map<string, int>& brandsCart, map<string, int>& brandsPurchase ){
		if(!root)
			return;
		InOrder(root->left, brandsView, brandsCart, brandsPurchase);
		brandsView.insert(pair<string, int>(root->brand, root->view));	
		brandsCart.insert(pair<string, int>(root->brand, root->cart));
		brandsPurchase.insert(pair<string, int>(root->brand, root->purchase));    
    	InOrder(root->right, brandsView, brandsCart, brandsPurchase);
	}
	void InOrder(Node* root){
	    	if (!root) 
	        	return;
	    	InOrder(root->left);
	    	if(root->brand.length() < 8)
	    		cout << root->brand << "\t\t"  << root->view << "\t\t" << root->cart << "\t\t" << root->purchase << "\t\t" << root->price << endl;
	    	else
	    		cout << root->brand << "\t"  << root->view << "\t\t" << root->cart << "\t\t" << root->purchase << "\t\t" << root->price << endl;
	    	cout << "--------------------------------------------------------------------------------" << endl;
	    	InOrder(root->right);
		}
};
bool cmp(pair<string, int>&a, pair<string, int>&b){
	return a.second > b.second;
}

void sort(map<string, int> &brands){
	vector<pair<string, int>> a;
	for(auto& it: brands){
		a.push_back(it);
	}
	sort(a.begin(), a.end(), cmp);
	int i = 0;
	for(auto& it: a){
		if(i < 5)
			cout << it.first << "\t" << it.second << endl;
		i++;
	}
}
void headMessage(const char* title){
    system("cls");
    cout << "\t\t\t###########################################################################";
    cout << "\n\t\t\t############                                                   ############";
    cout << "\n\t\t\t############             MULTICATEGORY STORE                   ############";
    cout << "\n\t\t\t############                                                   ############";
    cout << "\n\t\t\t###########################################################################";
    cout << "\n\t\t\t---------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t" << title;
    cout << "\n\t\t\t---------------------------------------------------------------------------\n";
    return;
}
void start(){
    headMessage("DATA STRUCTURES PROJECT");
    cout << endl;
    cout << "\n\t\t\t\t  ********************************************************\n";
    cout << "\n\t\t\t\t        =============================================";
    cout << "\n\t\t\t\t        =                  WELCOME                  =";
    cout << "\n\t\t\t\t        =                    TO                     =";
    cout << "\n\t\t\t\t        =               MULTICATEGORY               =";
    cout << "\n\t\t\t\t        =                  STORE                    =";
    cout << "\n\t\t\t\t        =============================================";
    cout << "\n\n\t\t\t\t  ********************************************************\n";
    cout << "\n\n\n\t\t\t Press Enter to continue.....";    
    int c=cin.get();
    cout << "\n\n\n\t\t\t Reading FILE 2019-Oct....." << endl;
    return;
}

void menu(){
	bool flag2 = false, flag4 = false;
	int choice = 0;	            
	BST b;
	unique_category cat;
	categoryList pl, pl1, pl2, pl3;
	map<string, int> brandsView;
  	map<string, int> brandsCart;
  	map<string, int> brandsPurchase;
  	vector<int> chunked;
	ifstream fin;
	fin.open("2019-Oct.csv");
	string line;
	getline(fin, line);
	string word;
	string e;
	string category;
	vector<vector<string>> chunked_line;
	vector<string> chunks;
	int read = 0;
	while(read < 3000000){
    	getline(fin, line);
    	stringstream s(line);
    	while(getline(s, word, ',')){
    		chunks.push_back(word);
		}
		chunked_line.push_back(chunks);
		chunks.clear();
		read++;
	}
	do{
		int i = 0, j = 0;
		headMessage("      MAIN MENU");
		cout << "\n\n\n\t\t1.DETAILS OF BRANDS";
		cout << "\n\t\t2.DETAILS OF SPECIFIC PRODUCTS";
		cout << "\n\t\t3.PRODUCTS AVAILABLE IN STORE";
		cout << "\n\t\t4.TOP 5 BRAND NAMES ON THE BASIS OF EVENT TYPE";
		cout << "\n\n\n\t\tENTER CHOICE=> ";
		cin >> choice;
		
        switch(choice)
        {
        case 1:
        	
            system("CLS");
            for(int i = 0; i < chunked_line.size(); i++)
            	b.Insert(chunked_line[i][4], chunked_line[i][1], chunked_line[i][5], chunked_line[i][6]);
			
		    read = 0;
		    cout << "Brand\t\tViews\t\tCarts\t\tPurchased\tTotal Sales"<< endl;
	        cout << "--------------------------------------------------------------------------------" << endl;
		    b.InOrder(b.getRoot());
		    cout << "\n--------------------------------------------------------------------------------" << endl;
		    b.InOrder(b.getRoot(), brandsView, brandsCart, brandsPurchase);
			cout << "\n-----------------------------5 MOST VIEWED BRANDS ------------------------------\n";
			sort(brandsView);
			cout << "\n-----------------------------5 MOST CARTED BRANDS ------------------------------\n";
			sort(brandsCart);
			cout << "\n---------------------------5 MOST PURCHASED BRANDS -----------------------------\n";
			sort(brandsPurchase);
		    cout << endl;
		    system("PAUSE");
            break;
        case 2:
        	
		    cout<<"\t\tENTER THE CATEGORY YOU WANT TO SEARCH: ";
		    cin>>category;
		    system("CLS");
		    for(int i = 0; i < chunked_line.size(); i++){
		    	if(chunked_line[i][4] == category){
		    		if(chunked_line[i][5]!="")
		    			pl.insertCategory(chunked_line[i][1], chunked_line[i][5]);
		    		flag2 = true;
				}	    		
			}
			if(flag2 == false)
				cout << "Category doesn't exist";
			pl.removeDuplicates();
		    pl.printCategory();
		    cout << endl;
			system("PAUSE");
            break;
        case 3:
            system("CLS");
            for(int i = 0; i < chunked_line.size(); i++){
		    	if(chunked_line[i][4] != ""){
		    		if(chunked_line[i][5] != "")
		    			cat.addatend(chunked_line[i][4]);
				}	    		
			}
			cat.removeduplicates();
			cat.sort();
			cat.display();
			cout << endl;
			system("PAUSE");
            break;
		case 4:
			cout << "\t\tENTER THE CATEGORY YOU WANT TO SEARCH: ";
		    cin >> category;
		    cout << "\t\tENTER EVENT TYPE (view/cart/purchase): ";
			cin >> e;
			if(e != "view" || e != "purchase" || e != "cart")
				cout << "Wrong Input !!!" << endl;
				
		    system("CLS");
		    for(int i = 0; i < chunked_line.size(); i++){
		    	if(chunked_line[i][4] == category){
		    		if(chunked_line[i][5] != "")
		    			pl2.insertCategory(chunked_line[i][1], chunked_line[i][5]);
		    		flag4 = true;
				}	    		
			}
			if(flag4 != false){
				pl2.removeDuplicates();
				if(e=="view"){
					cout << "\n-------------5 MOST VIEWED BRANDS IN YOUR DESIRED CATEGORY--------------\n";
				    pl3.setHead(pl2.mergeSort(pl2.getHead(), "view"));
				    pl3.printcategory();
				}
				else if(e=="cart"){
					cout << "\n-------------5 MOST CARTED BRANDS IN YOUR DESIRED CATEGORY--------------\n";
				    pl3.setHead(pl2.mergeSort(pl2.getHead(), "cart"));
				    pl3.printcategory();
				}	
			    else if(e=="purchase"){
			    		cout << "\n-------------5 MOST PURCHASED BRANDS IN YOUR DESIRED CATEGORY-----------\n";
				    pl3.setHead(pl2.mergeSort(pl2.getHead(), "purchase"));
				    pl3.printcategory();
				}
				else{
					cout << "Wrong Input!!";
				}
			    cout << endl;
			}
			else
				cout << "Category doesn't exist" << endl;			
		    system("PAUSE");
		    break;
		case 0:
        	cout << "\n\n\n\t\t\tTHANK YOU!!!\n\n\n\n\n";
            exit(0);
            break;
        default:
            cout << "\n\n\n\t\t\tINVALID INPUT!!! Try again...";
        }                                  
    }while(choice!=0);
    return;
}

int main(){
	start();                                                       
	menu();
	return 0;
}