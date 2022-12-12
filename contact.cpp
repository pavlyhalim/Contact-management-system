//
//  contact.cpp
//  CMS
//
//  Created by Pavly Halim on 13/11/2022.
//

#include <stdio.h>
#include "contact.h"

//build a constructor
Contact::Contact(string firstname, string lastname, string email, string phone, string city, string country, bool isFav)
{
    this -> fname = firstname;
    this -> lname = lastname;
    this -> email = email;
    this -> primaryPhone = phone;
    this -> city = city;
    this -> country = country;
    this -> isFav = isFav;

}