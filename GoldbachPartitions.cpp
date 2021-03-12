/*************************************************************************************
* Author:       Ahmed Iqbal
* Course:       CS1336.010
* Date:         11/16/2020
* Assignment:   Lecture Homework #9 Exercise #1
* Complier:     Visual C++ 2019
*
* Description:  This program prints out all of the binary GoldBach partitions for
*               even numbers from 4 to 100. it also prints out all of the ternary 
*               GoldBach partitions for all numbers from 6 to 100
*************************************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

// creating prototypes
bool isPrime(int prime);
void nextPrime(int& number);

int main()
{
   // ***************************************************************************************************************
   // * I combined Ex1 and Bonus 2 into the same code because they both deal with the same conjecture.
   // ***************************************************************************************************************

   // declaring and initializing variables used for both Conjectures
   int x, y, z, count = 0, maxCount = 0, maxPartitions = 0;

   // printing header
   cout << "*******************************************************************************************" << endl
      << "**********************************Binary GoldBach Partitions*******************************" << endl
      << "*******************************************************************************************" << endl << endl;
   
   // setting for loop to increment by 2 from 4 up until 100
   for (int i = 4; i <= 100; i += 2)
   {
      // re-initializing x and y to 2 each iteration
      x = 2, y = 2;

      // printing one "Even integer" per iteration
      cout << "Even integer " << setw(3) << i;
      
      // printing out partition and incrementing count if partition is met
      if (i == (x + y) && x >= y)
      {
         cout << " = [" << x << " + " << y << "]";
         count++;
      }

      else 
      {
         // setting while loop to run as long as a partition is not met and x is
         // less than or equal to 97 (highest prime number less than 100)
         while (i != (x + y) && x <= 97)
         {
            // incrementing x until x is the next prime number
            nextPrime(x);

            // printing out partition and incrementing count if partition is now met and
            // if x is greater than y (to avoid permutations of the same partition)
            if (i == (x + y) && (x >= y))
            {
               cout << " = [" << x << " + " << y << "]";
               count++;
            }

            else
            {
               // setting while loop to run as long as a partition is not met and y is
               // less than or equal to 97 (highest prime number less than 100)
               while (i != (x + y) && y <= 97)
               {
                  // incrementing y until y is the next prime number
                  nextPrime(y);

                  // printing out partition and incrementing count if partition is now met and
                  // if x is greater than y (to avoid permutations of the same partition)
                  if (i == (x + y) && (x >= y))
                  {
                     cout << " = [" << x << " + " << y << "]";
                     count++;
                  }
               }
            }
            // re-initializing y to 2 for next iteration
            y = 2;
         }
      }

      // setting count equal to maxCount and maxPartitions equal to i (iteration) if count is great than maxCount
      if (count > maxCount)
      {
         maxCount = count;
         maxPartitions = i;
      }

      // resetting count to 0 each iteration
      count = 0;

      cout << endl << endl;
   }
   
   // printing out the even integer with the most partitions
   cout << "The even integer with the greatest number of binary partitions is " << maxPartitions << endl << endl;

   // ***************************************************************************************************************
   // * This is the bonus assignment that prints out ternary paritions. I took the "at least" requirement to heart
   // * and printed out all possible ternary partitions. Enjoy ;^)
   // ***************************************************************************************************************

   // re-initializing variable to 0
   count = 0, maxCount = 0, maxPartitions = 0;

   // printing header
   cout << "*******************************************************************************************" << endl
      << "*********************************Ternary GoldBach Partitions*******************************" << endl
      << "*******************************************************************************************" << endl << endl;

   // setting for loop to increment by 1 from 6 up until 100
   for (int i = 6; i <= 100; i++)
   {
      // re-initializing x and y to 2 each iteration
      x = 2, y = 2, z = 2;

      // printing one "Integer" per iteration
      cout << "Integer " << setw(3) << i;

      // printing out partition and incrementing count if partition is met
      if (i == (x + y + z) && x <= 97)
      {
         cout << " = [" << x << " + " << y << " + " << z << "]";
         count++;
      }

      else
      {
         // setting while loop to run as long as a partition is not met and x is
         // less than or equal to 97 (highest prime number less than 100)
         while (i != (x + y + z) && x <= 97)
         {
            // incrementing x until x is the next prime number
            nextPrime(x);

            if (i == (x + y + z) && (x >= y) && (y >= z))
            {
               cout << " = [" << x << " + " << y << " + " << z << "]";
               count++;
               
            }

            else
            {
               // setting while loop to run as long as a partition is not met and y is
               // less than or equal to 97 (highest prime number less than 100)
               while (i != (x + y + z) && y <= 97)
               {
                  // calling nextPrime to get 
                  nextPrime(y);

                  if (i == (x + y + z) && (x >= y) && (y >= z))
                  {
                     cout << " = [" << x << " + " << y << " + " << z << "]";
                     count++;
                     
                  }

                  else
                  {
                     // setting while loop to run as long as a partition is not met and z is
                     // less than or equal to 97 (highest prime number less than 100)
                     while (i != (x + y + z) && z <= 97) 
                     {
                        // incrementing z until z is the next prime number
                        nextPrime(z);

                        if (i == (x + y + z) && (x >= y) && (y >= z))
                        {
                           cout << " = [" << x << " + " << y << " + " << z << "]";
                           count++;
                        }
                     }
                  }
                  // re-initializing z to 2 for next iteration
                  z = 2;
               }
            }
            // re-initializing y to 2 for next iteration
            y = 2;
         }
      }

      // setting count equal to maxCount and maxPartitions equal to i (iteration) if count is great than maxCount
      if (count > maxCount)
      {
         maxCount = count;
         maxPartitions = i;
      }

      // resetting count to 0 each iteration
      count = 0;

      cout << endl << endl;
   }

   // printing out the integer with the most partitions
   cout << "The integer with the greatest number of ternary partitions is " << maxPartitions << endl << endl;

   return 0;

} // end function main

/****************************************************************************
* Function: isPrime(int prime)
* Descr:    This function takes an int as an input and divides it by every
*           number from 2 to int - 1 to check whether it is prime. If the
*           number is divisible by any of those numbers, isPrime() returns
*           a false value.
* Input:    prime
*           The integer input.
* Return:   a bool value.
****************************************************************************/
bool isPrime(int currNum)
{
   // declaring and initializing isPrime to true as default
   bool isPrime = true;

   // setting for loop to run 2 to "currNum" - 1 times
   for (int i = 2; i <= currNum - 1; i++)
   {
      // if currNum is divisible by i, the function returns false
      if (currNum % i == 0)
      {
         isPrime = false;
         break;
      }
   }
   // if isPrime isn't change by now, the number is a prime
   return isPrime;
}


/****************************************************************************
* Function: nextPrime(int& number)
* Descr:    This function increments x until x is the next prime number
* Input:    the reference integer number
* Return:   nothing.
****************************************************************************/
void nextPrime(int& number)
{
   number++;
   // as long as number is not prime, it will be incremented
   while (!isPrime(number))
   {
      number++;
   }
}
