#include<iostream>

class ProductId{
 
	private:
		int Id;
		char Name;
	public : 
		Product Id() {Id=0;} 
		
	};
Add_Products(); 

int main() 
{	int option; 
	cout<<"Enter 1 to add Products, 2 to Modify Products, 3 to delete products"<<endl;
	cin>>option;

		if (option ==1){
				cout<<" Adding products: "<<endl; 
				Add_Products();			 	
				}
		if (option ==2){
				cout<<" Modify products: "<<endl; 
				Modify_Products();			 	
				}
		if (option ==1){
				cout<<" Deleting products: "<<endl; 
				Delete_Products();			 	
				}
		else		{
			cout<<" Invalid products: "<<endl; 	
	             		}
		


	cout<<"Enter product Key: 
return 0; 
}

Add_Products()
{		
	int number;
	char name;
	cout<< /t <<"YOU ARE GOING TO ADD PRODUCTS"<<endl;	
	cout<<"Enter product ID"<<endl; 
	cin>>number>>endl;
	cout<<"Enter product Name: "<<endl;
	cin>>name>>endl; 
//how to tranfer tis into the class? 
}
	
Modify_Products()
{
	cout<< /t <<"YOU ARE GOING TO MODIFY PRODUCTS"<<endl;	
	cout<<"Enter product ID"<<endl; 
	//accesing class varaibales and modifying them; 
}

Delete_Products()
{
	cout<< /t <<"YOU ARE GOING TO DELETE PRODUCTS"<<endl;	
	cout<<"Enter product ID"<<endl; 
	cin>>number>>endl;
	//finding the class and destroying it,....Destructors??
	
}
}
