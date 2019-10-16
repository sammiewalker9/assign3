/*
Sammie Walker
2315055
swalker@chapman.edu
CPSC 350 - 03
Assignment 3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "GenStack.h"
using namespace std;


int main(int argc, char **argv){
  if(argc>1){
    try{

      // check is going to be the file to check
      string check = argv[1];

      while(true){
        char delimiter;
        GenStack<int> q; // create an instance of the class so we can call the function to balance
        int runTest = q.checkDelimiters(check);

        // ask user if they would like to keep cheeking other files
        char userInput;
        cout << "Would you like to check another file? If so type Y, if not type N to exit program. " << endl;
        lineNumber = 0;
        cin >> userInput;

        if(userInput == 'N'){
          exit(EXIT_FAILURE);
        }
        else if(userInput == 'Y'){
          string userFile;
          cout << "Enter the name of the file you would like to check: " << endl;
          cin >> userFile;
          check = userFile;
        }
        else{
          cout << "Error. Exiting program. " << endl;
        }
        }
      }
      catch (const std::bad_alloc&){
        return -1;
      }
      catch(std::exception& e){
        std::cerr << "Some other standard error caught." << endl;
        return -1;
      }
    }
  }
