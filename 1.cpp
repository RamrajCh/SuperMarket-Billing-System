#include<iostream>

class Product{

	private:
		int id;
		char name[25];
		float price;
	public :
		Product() {id=0;}
		void id_set(void) {cin>>id;}		//setter of id
		void name_set(void) {cin>>name;}	//Setter of Character
		//int get_id(void) {return id;}
		//char get_name(void) {return name;}
		friend void Add_Products();
		friend void Modify_Products();
		//friend void Delete_Products();

	};

Modify_Products()
{
	cout<< /t <<"YOU ARE GOING TO MODIFY PRODUCTS"<<endl;
	cout<<"Enter product Name"<<endl;
	//accesing class varaibales and modifying them;
	Product *prod;
	int nid,nprice;
	cout <<"Enter product name :/t";
	cin << *prod;
	cout<<"enter new id and price";
    	cin<<*prod.id;					//pointer can access the private members of a class
	cin<<*prod.price;
}