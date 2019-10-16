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
using namespace std;

template <class X>
class GenStack{
public:
  GenStack();
  GenStack(int maxSize); // overloading constructor defines maxSize
  ~GenStack(); // desctuctor
  int getSize();

  // core functions O(1)
  void push(X d);
  X pop();
  X peek(); // aka top()
  X checkDelimiters(string fileToCheck);
  X copyStack();

  // helper functions
  bool isFull();
  bool isEmpty();

  // variables
  int size;
  int top;
  int maxSize;

  // declaring pointer to memory address of our type X
  // so when we do initialize it, variable going to get initialized to the first part of the array
  // initialize at run time not compile time
  X *myArray;

};

template <class X>
// default constructor
GenStack<X>::GenStack(){
  // initialization
  myArray = new X[size];
  maxSize = size;
  top = -1;
}

template <class X>
GenStack<X>::GenStack(int maxSize){
  myArray = new X[maxSize];
  size = maxSize;
  top = -1;
}

template <class X>
GenStack<X>::~GenStack(){
  // lets you build some character
  // research this
}

template <class X>
void GenStack<X>::push(X d){
  // need to check error/boundary check
  if (isFull()){
    cout << "Stack full, creating a new one with double the memory. ";
    copyStack();
  }
  cout << "Inserting: " << d << endl;
  myArray[++top] = d; // preincrement so that it will add before it evaluates top, will make top 0 first
}

template <class X>
X GenStack<X>::pop(){ // returns and removes
  // error checking, make sure its not empty
  if (isEmpty()){
    cout << "Stack empty. Exiting program. ";
    exit(EXIT_FAILURE);
  }
  cout << "Removing: " << top << endl;
  return myArray[top--];
}

template <class X>
X GenStack<X>::peek(){ // returns value but doesnt remove
  // check if empty
  if (!isEmpty()){
    return myArray[top];
  }
  else
    exit(EXIT_FAILURE);
}

template <class X>
bool GenStack<X>::isFull(){
  return (top == size-1); // returns true or false. returns true if top == size -1 (128 - 1)
}

template <class X>
bool GenStack<X>::isEmpty(){
  return (top == -1);
}

template <class X>
int GenStack<X>::getSize(){ // rerturns the size of the stack
  return top + 1;
}

template <class X>
X GenStack<X>::copyStack(){ // if stack is full create a new one with double the size to add to
  if(isFull()){
    size = size * 2;
  }
}


// varaiable to store which line we are in so we can tell the user where the error is
int lineNumber = 0;

template <class X>
X GenStack<X>::checkDelimiters(string fileToCheck){
  string line;
  ifstream inFile;
  inFile.open(fileToCheck);
  GenStack<char> delimiterStack(5); // create a stack of characters to put delimiters into. make initial size 5

  bool keepGoing = true; // make false when file is balanced
  while(keepGoing){
    while(getline(inFile, line, '\n')){ // use function getline to read in each line one by one, seperated by new lines
      lineNumber+=1;
      for(int i = 0; i < line.length(); i++){
        if(line[i] == '(' || line[i] == '{' || line[i] == '['){ // if we hit a character that's an open delimiter, push it into the stack
          delimiterStack.push(line[i]);
        }
        else if(line[i] == ')' || line[i] == '}' || line[i] == ']'){
          if(delimiterStack.isEmpty()){ // if the stack is empty there is no open delimiter in it
            cout << "This delimiter doesn't have a pair. You're missing it's match in the beginning of the file: " << line << endl;
          }
          else{

            // if the top of the stack contains a '(' :
            if(delimiterStack.peek() == '('){
              if(line[i] == ')'){ // if the '(' has a matching close ')' then remove the open one from the stack because it's balanced
                delimiterStack.pop();
              }
              // check for the other types of close delimteres and tell user which one they used
              else if(line[i] == '}'){
                cout << "Expected ) and found } in line " << lineNumber << endl;
                exit(EXIT_FAILURE);
              }
              else if(line[i] == ']'){
                cout << "Expected ) and found } in line " << lineNumber << endl;
                exit(EXIT_FAILURE);
              }
            }

            // if the top of the stack contains a '{' :
            else if(delimiterStack.peek() == '{'){
              if(line[i] == '}'){
                delimiterStack.pop();
              }
              else if(line[i] == ')'){
                cout << "Expected } and found ) in line " << lineNumber << endl;
                exit(EXIT_FAILURE);
              }
              else if(line[i] == ']'){
                cout << "Expected } and found ] in line " << lineNumber << endl;
                exit(EXIT_FAILURE);
              }
            }

            // if the top of the stack contains a '[' :
            else if(delimiterStack.peek() == '['){
              if(line[i] == ']'){
                delimiterStack.pop();
              }
              else if(line[i] == ')'){
                cout << "Expected ] and found ) in line " << lineNumber << endl;
                exit(EXIT_FAILURE);
              }
              else if(line[i] == '}'){
                cout << "Expected ] and found } in line " << lineNumber << endl;
                exit(EXIT_FAILURE);
              }
            }
            else{
              cout << "ERROR" << endl;

            }
          }
        }
      }
    }

    if(delimiterStack.isEmpty()){ // if there are no delimiters in the stack, then all have been popped and are balanced.
      cout << "All the delimiters in your file are balanced. " << endl;
      keepGoing = false; // break the while loop because delimiters are balanced
    }

    else{
    }
  }
}
