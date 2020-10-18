/***********************************************************************************
Author:       Ahmed Iqbal
Course:       CS1336.110
Date:         10/18/2020
Assignment:   Lab #5 Part #2
Complier:     Visual C++ 2019

Description:  This program calculates the number of meters sound can travel
              through the medium given the medium and seconds traveled.
***********************************************************************************/


#include <iostream>
#include <iomanip>
#include <string> // calling string class to enable use of string variables

using namespace std;

int main()
{
   // declaring variable used for input collection and calulations
   unsigned int medium;
   double seconds;
   double meters;

   // using string to be able to convert from unsigned int value back into the corresponding medium
   string outputMedium;

   // prompting user to enter medium and reading enter number into appropriate variable
   cout << "Select the medium that sound is traveling through:\n";
   cout << "1 Carbon Dioxide\n2 Air\n3 Helium\n4 Hydrogen\n";
   cin >> medium;

   // using if statement to test if the entered medium is valid
   if (medium == 1 || medium == 2 || medium == 3 || medium == 4)
   {
      // promting user to enter number of seconds and reading entered value into appropriate varibale
      cout << "Enter time (in seconds)\n";
      cin >> seconds;

      // using if statement to test whether entered seconds value is valid
      if (seconds >= 0 && seconds <= 30)
      {
         // if else if structure to perform caluculations based on the medium entered.
         // additionally storing the medium name in a string variable to have one output 
         // statement at the end instead of one in every if else if statement
         if (medium == 1)
         {
            meters = seconds * 258.0;
            outputMedium = "Carbon Dioxide: ";
         }
         else if (medium == 2)
         {
            meters = seconds * 331.5;
            outputMedium = "Air: ";
         }
         else if (medium == 3)
         {
            meters = seconds * 972.0;
            outputMedium = "Helium: ";
         }
         else if (medium == 4)
         {
            meters = seconds * 1270.0;
            outputMedium = "Hydrogen: ";
         }

         // outputting calulated value of distance to the console
         // setting different places after decimal point values as per assignment requirements
         cout << outputMedium << fixed << setprecision(3) << seconds << " seconds\n";
         cout << "Traveled " << fixed << setprecision(4) << meters << " meters\n";
      }

      // using else clause to output message in case entered seconds value is invalid
      else
         cout << "The time must be between 0.000 and 30.000 (inclusive)\n";
   }

   // using else clause to output message in case entered medium is invalid
   else
      cout << "The menu value is invalid. Please run the program again.\n";

} // end function main