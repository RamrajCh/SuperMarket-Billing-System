#include<iostream>

class ProductId{

	private:
		int Id;
		char Name;
		int price;
	public :
		ProductId() {Id=0;}

	};

Modify_Products()
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
