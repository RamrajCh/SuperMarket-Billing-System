#include<iostream>
using namespace std;

class Product{

	private:
		int id;
		char name[25];
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

void Add_Products();
void Modify_Products();
//void Delete_Products();


int main()
{	int option;
	cout<<"Enter 1 to add Products, 2 to Modify Products, 3 to delete products"<<endl;
	cin>>option;
	switch(option){
		case 1:
				cout<<" Adding products: "<<endl;
				Add_Products();
				break;
		case 2:
				cout<<" Modify products: "<<endl;
				//Modify_Products();
break;

		case 3:
				cout<<" Deleting products: "<<endl;
				//Delete_Products();
break;

		default:
			cout<<" Invalid number "<<endl;

}


return 0;
}

void Add_Products()
{

	Product P;
	cout<< '\t' <<"YOU ARE GOING TO ADD PRODUCTS"<<endl;
	cout<<"Enter product id"<<endl;
	P.id_set();
	cout<<"Enter product Name: "<<endl;
	P.name_set();


}

void Modify_Products()
{
	cout<< /t <<"YOU ARE GOING TO MODIFY PRODUCTS"<<endl;
	cout<<"Enter product Name"<<endl;
	//accesing class varaibales and modifying them;
	char prod;
	int nid,nprice;
	cout <<"Enter product name :/t";
	cin <<prod;
	cout<<"enter new id and price";
    prod.id_set();
	prod.price_set();
}

/*void Delete_Products()
{
	cout<< /t <<"YOU ARE GOING TO DELETE PRODUCTS"<<endl;
	cout<<"Enter product id"<<endl;
	cin>>number>>endl;
	//finding the class and destroying it,....Destructors??

}
}
*/
