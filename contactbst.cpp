//
//  contactbst.cpp
//  CMS
//
//  Created by Pavly Halim on 13/11/2022.
//

#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include "contactbst.h"
#include "contact.h"

//======================================
ContactBST::ContactBST()
{
    root = NULL;
}

//======================================
ContactBST::~ContactBST()
{
    delete root;
}

//======================================
Node* ContactBST::getRoot()
{
    return root;
}

//======================================
void ContactBST::add(Node* ptr,string key, Contact *data)
{
    //check for the input key and convert it to lowercase to make it case insensitive
    for (int i = 0; i < key.length(); i++)
    {
        key[i] = tolower(key[i]);
    }

	//case 1 tree/subtree is empty
	if(root == nullptr)
	{
		root = new Node(key, data);
	}
	//case 2 if the key is less than the key of the current node 
	else if(key < ptr->getKey())
	{
		//if the left child is empty, insert the key here
		if(ptr->left == nullptr)
		{
			ptr->left = new Node(key, data);
			ptr -> left -> parent = ptr;
			
		}
		//else recursively insert the key in the left subtree
		else
		{
			add(ptr->left, key, data);
		}
	}
	//case 3 if the key is greater than the key of the current node 
	else if(key > ptr->getKey())
	{
		//if the right child is empty, insert the key 
		if(ptr->right == nullptr)
		{
			ptr->right = new Node(key, data);
			ptr->right -> parent = ptr;

		}
		//else recursively insert the key in the right subtree

		else
		{
			add(ptr->right, key, data);
		}
	}
	//case 4 if the key is equal to the key of the current node 
	else
	{
		ptr->contactVector.push_back(data);
	}
}

//======================================
void ContactBST::update(Node* ptr, string key)
{
    int choice, selection;
    string newkey, newFirstName, newLastName, newPhoneNumber, newEmailAddress, newCity, newCountry;

    //check for the input key and convert it to lowercase to make it case insensitive
    for (int i = 0; i < key.length(); i++)
    {
        key[i] = tolower(key[i]);
    }
    //search for the key in the tree and find the record
    Node* temp = searchFor(ptr, key);
    temp -> print();
    

    cout << "Enter the number of the contact you want to update: ";
    string choi;
    getline(cin, choi);
    choice = stoi(choi);
    
    //check if the choice is valid
    while (choice < 1 || choice > temp -> contactVector.size())
    {
        cout << "Invalid choice. Please choose again: ";
        getline(cin, choi);
        choice = stoi(choi);
    }
    choice = choice - 1;
    Contact* contact = temp -> contactVector.at(choice);
    
    //ask the user to choose the attribute to update
    cout << "Choose the attribute to update: 1)first name 2)last name 3)email 4)phone  5)city 6)country:" << endl;
    string sele;
    getline(cin, sele);
    selection = stoi(sele);
    
    //check if the selection is valid
    while (selection < 1 || selection > 6)
    {
        cout << "Invalid selection. Please choose again: ";
        getline(cin, sele);
        selection = stoi(sele);
    } 
    if (selection == 1)
    {
        cout << "Enter the new first name: ";
        string newFirstName;
        getline(cin, newFirstName);
        newkey = newFirstName + " " + contact->lname;
        contact -> fname = newFirstName;
        if (temp-> contactVector.size() == 1){
            remove(temp, key);
        }
        else{
            temp->contactVector.erase(choice);
        }

        add(root, newkey, contact);

    }
    //case 2 update the last name
    else if (selection == 2)
    {
        cout << "Enter the new last name: ";
        string newLastName;
        getline(cin, newLastName);
        // contact -> lname = newLastName;
        newkey = contact->fname + " " + newLastName;
        contact -> lname = newLastName;
        if (temp-> contactVector.size() == 1){
            remove(temp, key);
        }
        else{
            temp->contactVector.erase(choice);
        }

        add(root, newkey, contact);
    }
    //case 3 update the email
    else if (selection == 3)
    {
        cout << "Enter the new email: ";
        string newEmail;
        getline(cin, newEmail);
        
        //check if the email is valid
        while (newEmail.empty())
			{
				cout<<"Email cannot be empty. Enter again: ";
				getline(cin,newEmail);
			}
		while (newEmail.find("@") == string::npos || newEmail.find(".") == string::npos)
			{
				cout<<"Email should contain @ and . characters. Enter again: ";
				getline(cin,newEmail);
			}
        contact -> email = newEmail;
    }
    //case 4 update the phone
    else if (selection == 4)
    {
        cout << "Enter the new phone: ";
        string newPhone;
        getline(cin, newPhone);
        
        //check if the phone is valid
        while (newPhone.empty())
			{
				cout<<"Phone number cannot be empty. Enter again: ";
				getline(cin,newPhone);
			}
			while (newPhone.find_first_not_of("0123456789") != string::npos)
			{
				cout<<"Phone number should contain only digits. Enter again: ";
				getline(cin,newPhone);
			}
			
			while(newPhone.length() < 8 || newPhone.length() > 15 && newPhone.find_first_not_of("0123456789") != string::npos && (newPhone[0] != '0' && newPhone[0] != '+'))
			{
				
				cout<<"Phone number should be more than 8 digits and less than 15 digits long and should not contain any special characters and should start with 0 or +. Enter again: ";
				getline(cin,newPhone);
			}

        contact -> primaryPhone = newPhone;
    }
    //case 5 update the city
    else if (selection == 5)
    {
        cout << "Enter the new city: ";
        string newCity;
        getline(cin, newCity);
        contact -> city = newCity;
    }
    //case 6 update the country
    else if (selection == 6)
    {
        cout << "Enter the new country: ";
        string newCountry;
        getline(cin, newCountry);
        contact -> country = newCountry;
    }
}


//======================================
//find the minimum 
Node* ContactBST::findMin(Node *ptr)
{
	//case 1 if the tree/subtree is empty
	if(ptr == nullptr)
	{
		return nullptr;
	}
	//case 2 if the left child is empty, the current node is the minimum
	else if(ptr->left == nullptr)
	{
		return ptr;
	}
	//case 3 if the left child is not empty, recursively find the minimum in the left subtree
	else
	{
		return findMin(ptr->left);
	}
}

//======================================
void ContactBST::remove(Node* ptr, string key)
{
       int index = 0;

    //case 1 empty 
	if(ptr == nullptr)
	{
		cout<<"Key does not exist"<<endl;
        return;
	}

    //check if the size is equal to 1 then assign 0 to the index
    if (ptr->contactVector.size() > 1 )
    {
       ptr = searchFor(ptr,key);
       ptr->print();
       cout << "Enter the index of the contact you want to delete: ";
       std::string ind;
       getline(cin, ind);
       index = std::stoi(ind);
       if (index > ptr->contactVector.size())
       {
           cout << "Invalid index" << endl;
           return;
       }
       index = index - 1;
        ptr->contactVector.erase(index);
       return;
    }
    
	// case 2 
	if (key < ptr->getKey())
	{
		remove(ptr->left, key);
        cout << "Contact deleted successfully" << endl;

	}
	//case 3 
	else if(key > ptr->getKey())
	{
		remove(ptr-> right, key);
	}
	//case 4
	else if(key == ptr-> key)
    {
        //case 4.1 if the node has no children
        if(ptr->left == nullptr && ptr->right == nullptr)
        {
            //if the node is the left child of its parent
            if(ptr->parent->left == ptr)
            {
                ptr->parent->left = nullptr;
            }
            //if the node is the right child of its parent
            else
            {
                ptr->parent->right = nullptr;
            }
            // ptr->contactVector.erase(index);
        }
        //case 4.2 if the node has one child
        else if(ptr->left == nullptr || ptr->right == nullptr)
        {
            //if the node is the left child of its parent
            if(ptr->parent->left == ptr)
            {
                //if the node has a left child
                if(ptr->left != nullptr)
                {
                    ptr->parent->left = ptr->left;
                    ptr->left->parent = ptr->parent;
                }
                //if the node has a right child
                else
                {
                    ptr->parent->left = ptr->right;
                    ptr->right->parent = ptr->parent;
                }
            }
            //if the node is the right child of its parent
            else
            {
                //if the node has a left child
                if(ptr->left != nullptr)
                {
                    ptr->parent->right = ptr->left;
                    ptr->left->parent = ptr->parent;
                }
                //if the node has a right child
                else
                {
                    ptr->parent->right = ptr->right;
                    ptr->right->parent = ptr->parent;
                }
            }
            ptr->contactVector.erase(index);
        }
        //case 4.3 if the node has two children
        else
        {
            //find the minimum in the right subtree
            Node *min = findMin(ptr->right);
            //replace the key of the node with the key of the minimum
            ptr->key = min->key;
            //remove the minimum
            remove(min, min->key);
        }
        delete ptr;
    }
}

//======================================
//Find and returns the node with key
Node* ContactBST::searchFor(Node* ptr,string key)
{
    //make the input lowercase to match the key in the tree
    transform(key.begin(), key.end(), key.begin(), ::tolower);

    //case 1 if the tree/subtree is empty
    if(ptr == nullptr)
    {
        return nullptr;
    }
    //case 2 if the key is equal to the key of the current node
    else if(key == ptr->getKey())
    {
        return ptr;
    }
    //case 3 if the key is less than the key of the current node
    else if(key < ptr->getKey())
    {
        //if the left child is empty, then the key is not in the tree
        if(ptr->left == nullptr)
        {
            return nullptr;
        }
        //else recursively search the left subtree
        else
        {
            return searchFor(ptr->left, key);
        }
    }
    //case 4 if the key is greater than the key of the current node
    else
    {
        //if the right child is empty, then the key is not in the tree
        if(ptr->right == nullptr)
        {
            return nullptr;
        }
        //else recursively search the right subtree
        else
        {
            return searchFor(ptr->right, key);
        }
    }
    //print the data of the key
    return nullptr;

}
//======================================
//Mark a contact as favorite 
bool ContactBST::markFav(string key)
{
    int index = 0;
    Node* ptr = searchFor(root, key);
    if (ptr == nullptr)
    {
        cout << "The contact you are trying to mark as favorite does not exist." << endl;
    }
    else
    {
        
        ptr->contactVector.at(index)->isFav = true;
        return true;
    }
    return false;
}

//======================================
//Unmark a contact as favorite
bool ContactBST::unmarkFav(string key)
{
    Node* ptr = searchFor(root, key);
    int index = 0;
    if (ptr == nullptr)
    {
        cout << "The contact you are trying to unmark as favorite does not exist." << endl;
    }
    else
    {
        ptr->contactVector.at(index)->isFav = false;
       
        return true;
    }
    return false;
}

//======================================
//Recursive method that prints the data at nodes in an ascending order
void ContactBST::printASC(Node* ptr)
{
    //if the current node is not empty
    if (ptr != nullptr)
    {
        //recursively traverse the left subtree
        printASC(ptr->left);
        //print the data of the current node
        for (int i = 0; i < ptr->contactVector.size(); i++)
        {
            cout<<"First Name: "<<ptr->contactVector.at(i)->fname<<endl;
            cout << "Last Name: " << ptr->contactVector.at(i)->lname << endl;
            cout << "Phone Number: " << ptr->contactVector.at(i)->primaryPhone << endl;
            cout << "Email: " << ptr->contactVector.at(i)->email << endl;
            cout << "City: " << ptr->contactVector.at(i)->city << endl;
            cout << "Favorite: " << ptr->contactVector.at(i)->isFav << endl;
            cout << endl;
        }
        //recursively traverse the right subtree
        printASC(ptr->right);
        }
}

//======================================
//Recursive method that prints the data at nodes in a descending order
void ContactBST::printDES(Node* ptr)
{
    //if the current node is not empty
    if (ptr != nullptr)
    {
        //recursively traverse the right subtree
        printDES(ptr->right);
        //print the data of the current node
        for (int i = 0; i < ptr->contactVector.size(); i++)
        {
            cout << "First Name: " << ptr->contactVector.at(i)->fname << endl;
            cout << "Last Name: " << ptr->contactVector.at(i)->lname << endl;
            cout << "Phone Number: " << ptr->contactVector.at(i)->primaryPhone << endl;
            cout << "Email: " << ptr->contactVector.at(i)->email << endl;
            cout << "City: " << ptr->contactVector.at(i)->city << endl;
            cout << "Favorite: " << ptr->contactVector.at(i)->isFav << endl;
            cout << endl;
        }
        //recursively traverse the left subtree
        printDES(ptr->left);
    }
}

//======================================
//Print the favorite data at nodes in an ascending order
void ContactBST::printFav(Node* ptr)
{
    
    {
        //if the current node is not empty
        if (ptr != nullptr)
        {
            //recursively print the left subtree
            printFav(ptr->left);
            //print the data of the current node
            for (int i = 0; i < ptr->contactVector.size(); i++)
            {
               if (ptr->contactVector.at(i)->isFav == true)
               {
                   cout << "First Name: " << ptr->contactVector.at(i)->fname << endl;
                   cout << "Last Name: " << ptr->contactVector.at(i)->lname << endl;
                   cout << "Phone Number: " << ptr->contactVector.at(i)->primaryPhone << endl;
                   cout << "Email: " << ptr->contactVector.at(i)->email << endl;
                   cout << "City: " << ptr->contactVector.at(i)->city << endl;
                   cout << "Favorite: " << ptr->contactVector.at(i)->isFav << endl;
                   cout << endl;
               }
            }
            //recursively print the right subtree
            printFav(ptr->right);
        }
    }
}

//======================================
//Load all the contacts from the CSV file to the BST
int ContactBST::importCSV(string path)
{
    //open the file
    ifstream file(path);
    //if the file is open
    if (file.is_open())
    {
        string line;
        stringstream ss;
        string fname, lname, primaryPhone, email, city, country;
        string key;
        bool isFav; 
        int count = 0;

        //while the file is not empty
        while (getline(file, line))
        {

            //split the line by comma
            ss << line;
            getline(ss, fname  , ',');
            getline(ss, lname, ',');
            getline(ss, primaryPhone, ',');
            getline(ss, email, ',');
            getline(ss, city, ',');
            getline(ss, country, ',');

            //convert the boolean of isFav to string
            getline(ss, key, ',');
            if (key == "1")
            {
                isFav = true;
            }
            else
            {
                isFav = false;
            }
            
            //insert the contact to the BST
            Contact* contact = new Contact(fname, lname, primaryPhone, email, city, country, isFav);
            count++;
            key = fname + " " + lname;

            add(root, key, contact);
            ss.str("");
            ss.clear();
        }
        //close the file
        file.close();
        cout << count << " contacts have been imported successfully." << endl;
        return 1;

    }
    //if the file is not open
    else
    {
        cout << "The file is not open." << endl;
        return 0;
    }
}

//======================================
//export the contacts to a CSV file using recursion where ptr is a pointer to the root of the tree/subtree
int ContactBST::exportCSV(Node* ptr,string path)
{
   static int count = 0;
    //open the file
    ofstream file(path, ios::app);
    //if the file is open
    if (file.is_open())
    {
        //if the current node is not empty
        if (ptr != nullptr)
        {
            //recursively traverse the left subtree
           exportCSV(ptr->left, path);
            //print the data of the current node
            for (int i = 0; i < ptr->contactVector.size(); i++)
            {
                file << ptr->contactVector.at(i)->fname << ",";
                file << ptr->contactVector.at(i)->lname << ",";
                file << ptr->contactVector.at(i)->primaryPhone << ",";
                file << ptr->contactVector.at(i)->email << ",";
                file << ptr->contactVector.at(i)->city << ",";
                file << ptr->contactVector.at(i)->country << ",";
                if (ptr->contactVector.at(i)->isFav == true)
                {
                    file << "1";
                }
                else
                {
                    file << "0";
                }
                file << endl;
                count++;
            }
            //recursively traverse the right subtree
            exportCSV(ptr->right , path);  
        }
    //close the file
    file.close();
    }
      return count;
}
