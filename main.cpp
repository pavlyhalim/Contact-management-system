
//=================================================================================
// Name         : DS Assignment#2 
// Author       : 
// Version      : 1.0
// Date Created : 07-11-2022
// Date Modified: 
// Description  : Starter Code for Contact Management System using BST Tree in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include "myvector.h"
#include "contact.h"
#include "contactbst.h"
//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"remove <key>       :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markFav <key>      :Mark as favourite"<<endl
		<<"unmarkFav <key>    :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printFav           :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================
//==========================================================

int main()
{   
    ContactBST bst;
	string command;
	string key;
	string path;
	string fname, lname, email, phone, city, country;
	bool isFav;
	listCommands();
	string user_input;
	string parameter;

	do
	{
		cout<<">";
		getline(cin,user_input);
		
		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);

        if(command=="import")
        {
            bst.importCSV(parameter);
        }
        else if(command=="export")
        {
			int c = bst.exportCSV(bst.getRoot(), parameter); cout << c << " records have been exported successfully" << endl;
			//clear the counter after each export manually

        }
        else if(command=="add")
{
			cout<<"Enter the first name: ";
			getline(cin,fname);
			while (fname.empty())
			{
				cout<<"First name cannot be empty. Enter again: ";
				getline(cin,fname);
			}
			while (fname.length() < 3 || fname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos)
			{
				cout<<"First name should be at least 3 characters long and should not contain any special characters. Enter again: ";
				getline(cin,fname);
			}
			cout<<"Enter the last name: ";
			getline(cin,lname);
			while (lname.empty())
			{
				cout<<"Last name cannot be empty. Enter again: ";
				getline(cin,lname);
			}
			while (lname.length() < 3 || lname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos)
			{
				cout<<"Last name should be at least 3 characters long and should not contain any special characters. Enter again: ";
				getline(cin,lname);
			}
			cout<<"Enter the email: ";
			getline(cin,email);
			while (email.empty())
			{
				cout<<"Email cannot be empty. Enter again: ";
				getline(cin,email);
			}
			while (email.find("@") == string::npos || email.find(".") == string::npos)
			{
				cout<<"Email should contain @ and . characters. Enter again: ";
				getline(cin,email);
			}
			cout<<"Enter the phone number: ";
			getline(cin,phone);
			while (phone.empty())
			{
				cout<<"Phone number cannot be empty. Enter again: ";
				getline(cin,phone);
			}
			while (phone.find_first_not_of("0123456789") != string::npos)
			{
				cout<<"Phone number should contain only digits. Enter again: ";
				getline(cin,phone);
			}
			
			while(phone.length() < 8 || phone.length() > 15 && phone.find_first_not_of("0123456789") != string::npos && (phone[0] != '0' && phone[0] != '+'))
			{
				
				cout<<"Phone number should be more than 8 digits and less than 15 digits long and should not contain any special characters and should start with 0 or +. Enter again: ";
				getline(cin,phone);
			}

			cout<<"Enter the city: ";
			getline(cin,city);
			cout<<"Enter the country: ";
			getline(cin,country);
			cout<<"Do you want to add this contact in your favourite:(y/n) ";
			getline(cin,command);
			while (command != "y" && command != "n")
			{
				cout << "Invalid input. Do you want to add this contact in your favourite:(y/n) ";
				getline(cin, command);
			}
			if(command=="y")
				isFav=true;
			else
				isFav=false;

				Contact *ct = new Contact(fname,lname,email,phone,city,country,isFav);
				key = fname+" " + lname;
				bst.add(bst.getRoot(),key,ct);
		}
        else if(command=="edit")
        {
			while (parameter.empty())
			{
				cout << "Key cannot be empty. Enter again: ";
				getline(cin, parameter);
			}
			
			//check if the key exists
			if (bst.searchFor(bst.getRoot(), parameter) == NULL)
			{
				cout << "Contact not found" << endl;
			}
			else
			{
            bst.update(bst.getRoot(),parameter);
			}
        }
        else if(command=="remove")
        {
            bst.remove(bst.getRoot(),parameter);
        }
        else if(command=="searchFor")
        {
            Node *ptr = bst.searchFor(bst.getRoot(),parameter);
            if(ptr!=nullptr)
            {
                ptr->print();
            }
            else
            {
                cout<<"No record found"<<endl;
            }
        }
        else if(command=="markFav")
        {
            if(bst.markFav(parameter))
            {
                cout<<"Marked as favorite"<<endl;
            }
            else
            {
                cout<<"No record found"<<endl;
            }
        }
        else if(command=="unmarkFav")
        {
            if(bst.unmarkFav(parameter))
            {
                cout<<"Unmarked as favorite"<<endl;
            }
            else
            {
                cout<<"No record found"<<endl;
            }
        }
        else if(command=="printASC")
        {
			if(bst.getRoot() == nullptr)
			{
				cout<<"No records found"<<endl;
			}
			else
			{
            bst.printASC(bst.getRoot());
			}
        }
        else if(command=="printDES")
        {
			if (bst.getRoot() == nullptr)
			{
				cout << "No record found" << endl;
			}
			else
			{
            bst.printDES(bst.getRoot());
			}
        }
        else if(command=="printFav")
        {
			if (bst.getRoot() == nullptr)
			{
				cout << "No records found" << endl;
			}
			else
			{
            bst.printFav(bst.getRoot());
			}
        }
        else if(command=="help")
        {
            listCommands();
        }
        else if(command=="exit")
        {
            cout<<"Exiting..."<<endl;
            break;
        }
        else
        {
            cout<<"Invalid command. Type 'help' to see the list of available commands"<<endl;
        }
   } while(command!="exit");
    return 0;
}
