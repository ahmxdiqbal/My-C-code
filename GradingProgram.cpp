/****************************************************************************************
* Multiple Test Grading program
*
* This program gets a file's name, opens the file, and sends it to a function to reads
* its contents into an array of dynamically allocated pointers to structs.
* 
* It then prints a menu and gives the user the choice of the information that he/she 
* and the manner in which it should be displayed. 
* 
* The user can have it sorted  alphabetically and display all of the data, sort it by
* average grade(highest first) and display all of the data, or to find and display the
* data of a specific student given his/her student ID number.
*
* The program will then print the menu and allow the user to access the data another
* way. It will keep repeating until the user responds with a 0 to the menu options 
*
* Written by Ahmed Iqbal for CS1337.009, assignment 4, starting March 12, 2021.
* NetID: axi180011
****************************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// declaring and initializing the member variables inside of Student
struct Student
{
   int ID = 0;
   string name = " ";
   int grade1 = 0;
   int grade2 = 0;
   int grade3 = 0;
   double average = 0;
};

// function prototypes
void getFile(ifstream& inFile);
int fillArray(ifstream& inFile, Student* studentArr[]);
void deleteArray(Student* studentArr[], int count);
void sortArray(Student* studentArr[], int count, int field);
void showMenu();
void displayArray(Student* studentArr[], int count);
void studentLookUp(Student* studentArr[], int count, int ID);

int main()
{
   // declaring integer, ifstream, and Student variables
   int field;
   ifstream inFile;
   Student* studentArr[100];

   // calling the getFile and fillArray funtions to get the file,
   // ascertain that it opened correctly, and fill the array properly
   getFile(inFile);
   int count = fillArray(inFile, studentArr);

   // loop iterates until a 0, the sentinel value, is entered
   do
   {
      // displaying the menu options
      showMenu();

      // input validation loop to ascertain a valid meu choice was selected
      do
      {
         cout << "Please enter one of the above menu options: ";
         cin >> field;
         cout << endl;

      } while (field != 0 && field != 1 && field != 2 && field != 3);

      // using menu input to decide what to do with the data
      switch (field)
      {
         // sorts and displays all data alphabetically
      case 1:
         sortArray(studentArr, count, field);
         displayArray(studentArr, count);
         break;

         // sorts and displays all data by average(highest first)
      case 2:
         sortArray(studentArr, count, field);
         displayArray(studentArr, count);
         break;

         // finds and displays the student's data whose ID number is entered by the user
      case 3:
         int ID;
         cout << "Please enter the ID of the student you are searching for: ";
         cin >> ID;
         cout << endl;
         studentLookUp(studentArr, count, ID);
         break;

      default:
         break;
      }

   } while (field != 0);

   // calling an function to delete all the elements of the array
   deleteArray(studentArr, count);

   inFile.close();

   return 0;
} // end function main


// In this function, we get a filename from the user, and we open it and ascertain that it has opened properly
//
// Inputs:   an ifstream object
// Outputs:  none
void getFile(ifstream& inFile)
{
   string fileName;

   // string will be changed to display error message after the first invalid entry(if it comes to that)
   string error = "Please";

   do
   {
      // using getline in case the file's name has spaces in it
      cout << error << " enter an existing file's name" << endl;
      getline(cin, fileName);
      cout << endl;

      inFile.open(fileName);

      // changing the error string so that every subsequent time, it displays an error message
      error = "Error. Please";

      // the do-while loop only loops if the file fails to open
   } while (!inFile);
}


// In this function, we read the data from the opened file into an array of pointers to Students
//
// Inputs:   an ifstream object, array of pointers to Students
// Outputs:  an integer variable
int fillArray(ifstream& inFile, Student* studentArr[])
{
   int count = 0;

   // simultaineouly dynamically allocating a Student variable and reading in the ID number
   while ((studentArr[count] = new Student) && (inFile >> studentArr[count]->ID))
   {
      // reading in the rest of the data into the Student variable, including calculating the average
      inFile >> studentArr[count]->name;
      inFile >> studentArr[count]->grade1 >> studentArr[count]->grade2 >> studentArr[count]->grade3;

      studentArr[count]->average = ((studentArr[count]->grade1 + studentArr[count]->grade2 + studentArr[count]->grade3)/3.0);
      
      count++;
   }
   return count;
}


// In this function, we display a menu containing option on what to do with the data to the user
//
// Inputs:   none
// Outputs:  none
void showMenu()
{
   cout << "1. Print list of student information sorted alphabetically" << endl
      << "2. Print list of student information sorted by average grade(highest first)" << endl
      << "3. Enter student ID to look up specific information" << endl << endl;
}


// In this function, we sort the array 2 different ways, alphabetically or by average grade(highest first),
// depending on the desired output of the user, using the bubble sort
//
// Inputs:   an array of pointers to Students, the integer count, the integer field
// Outputs:  none
void sortArray(Student* studentArr[], int count, int field)
{
   // bool flag to let us know if any swaps have occured(if not, sort is finished)
   bool swapFlag;
   Student* temp;

   do
   {
      swapFlag = false;

      // for loop to traverse the untill the penultimate element of the array
      for (int ix = 0; ix < count - 1; ix++)
      {
         // sorting alphabetically
         if (field == 1)
         {
            // determining if a element is alphabetically greater than the next element, and if so, swapping them
            if (studentArr[ix]->name > studentArr[ix + 1]->name)
            {
               temp = studentArr[ix];
               studentArr[ix] = studentArr[ix + 1];
               studentArr[ix + 1] = temp;

               // setting loop control variabile to do another iteration
               swapFlag = true;
            }
         }
         
         // sorting by average grade(highest first)
         if (field == 2)
         {
            // determining if a element is less than the next element, and if so, swapping them
            if (studentArr[ix]->average < studentArr[ix + 1]->average)
            {
               temp = studentArr[ix];
               studentArr[ix] = studentArr[ix + 1];
               studentArr[ix + 1] = temp;

               // setting loop control variabile to do another iteration
               swapFlag = true;
            }
         }
      }
      // loop will iterate until no swaps are done(until array is fully sorted)
   } while (swapFlag);
}


// In this function, we display the array with proper formatting and headers
//
// Inputs:   an array of pointers to Students, the integer count
// Outputs:  none
void displayArray(Student* studentArr[], int count)
{
   // printing the headers in the desired formatting
   cout << setw(12) << "ID number" << setw(20) << "Student Name" << setw(9) << "Test 1"
      << setw(9) << "Test 2" << setw(9) << "Test 3" << setw(9) << "Average" << endl;

   // printing the information of each student(sorted as desired) line by line
   for (int ix = 0; ix < count; ix++)
   {
      cout << setw(12) << studentArr[ix]->ID << setw(20) << studentArr[ix]->name << setw(9) << studentArr[ix]->grade1
         << setw(9) << studentArr[ix]->grade2 << setw(9) << studentArr[ix]->grade3 << setw(9) << fixed 
         << setprecision(2) << studentArr[ix]->average << endl;
   }
   cout << endl;
}


// In this function, we look up and print a student's information given his/her student ID.
// If the student is not found, we display a message saying that.
//
// Inputs:   an array of pointers to Students, the integer count, the integer ID
// Outputs:  none
void studentLookUp(Student* studentArr[], int count, int ID)
{
   bool found = false;
   int ix = 0;

   // walking throught he array until we find the studentthat was requested or until we reach the end of the array
   while (!found && ix < count)
   {
      // printing the student's information if the Id numbers match
      if (studentArr[ix]->ID == ID)
      {
         cout << setw(12) << "ID number" << setw(20) << "Student Name" << setw(9) << "Test 1"
            << setw(9) << "Test 2" << setw(9) << "Test 3" << setw(9) << "Average" << endl;

         cout << setw(12) << studentArr[ix]->ID << setw(20) << studentArr[ix]->name << setw(9) << studentArr[ix]->grade1
            << setw(9) << studentArr[ix]->grade2 << setw(9) << studentArr[ix]->grade3 << setw(9) << fixed
            << setprecision(2) << studentArr[ix]->average << endl;

         // letting the loop know a match was found
         found = true;
      }
      ix++;
   }

   // printing message if the student was not found
   if (!found)
   {
      cout << "The student you are looking is not in the file." << endl;
   }

   cout << endl;
}


// In this function, we delete every dynamically allocated element of the of the array using a for loop
//
// Inputs:   an array of pointers to Students, the integer count
// Outputs:  none
void deleteArray(Student* studentArr[], int count)
{
   // for loop to traverse the array and delete the elements one by one
   for (int ix = 0; ix < count; ix++)
   {
      delete studentArr[ix];
   }
}
