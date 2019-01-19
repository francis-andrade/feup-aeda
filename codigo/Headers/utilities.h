/**
  @file utilities.h
  @author Francisco Andrade
  @author João Almeida

  Contains some utility functions useful all around the Project
*/

//USED WITH SYSTEM(CLEAR) FOR MULTI-OS CLEAR CONSOLE
#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#ifndef UTILITIES_H
#define UTILITIES_H

#include<iostream>
#include <string>
#include<vector>
#include "Date.h"

using namespace std;

/**
  @brief Eliminates extra spaces in string
  @param s String to have spaces removed
  @return String without extra spaces
  @details It removes all spaces in the beggining and in the end, if there are spaces between the characteres
  @details they are transformed into a single space
*/
string removespaces(string s);
/**
  @brief Calculates how old is a person born on a given Date
  @param birth Date to use in calculations
  @return How old that person is
*/
int actualage(Date birth);
/**
  @brief Calculates whether or not the given year was/is a Leap Year
  @param year Year to use in calculations
  @return True if year is a Leap Year
*/
bool Isleap(int year);
/**
  @brief Checks if given string is an Integer
  @param s String to be checked
  @return True if string only contains numbers
  @details From http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
*/
bool isInteger(const string & s);
/**
  @brief Converts an integer into a String
  @param s String to be converted
  @return Integer that was in string
*/
int convint(string s);//converts an integer to a string

#endif
