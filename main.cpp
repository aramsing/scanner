#include <list>
#include <bits/stdc++.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <istream>
#include <malloc.h>
#include <stdio.h>
#include <string>


using namespace std;

// Global Variables
list<string> tokenList; // Token linked list
int comment = 0;

// Check for Error in Token List
bool findError() {
  list<string>::iterator it;
  for (it = tokenList.begin(); it != tokenList.end(); it++) {
    string token = *it;
    if (!token.compare("error")) {
      return 1;
    }
  }
  return 0;
}

// Print List
void printList() {
  list<string>::iterator it = tokenList.begin();
  while (1) {
    cout << *it;
    it++;
    if (it != tokenList.end()) {
      cout << ", ";
    }
    else {
      break;
    }
  }
}

// Character Scanner
string charScanner(int ascii){
  switch(ascii){
    case 65 ... 90:
    case 97 ... 122:
      return "id";
      break;
    case 48 ... 57:
      return "number";
      break;
    case 40:
      return "lpara";
      break;
    case 41:
      return "rpara";
      break;
    case 42:
      return "times";
      break;
    case 43:
      return "plus";
      break;
    case 45:
      return "minus";
      break;
    case 47:
      return "div";
      break;
    case 32:
      break; //space
    case 58:
      break;
    case 61:
      break;
    case 46:
      return "decimal";
      break; 
    default:
      return "error";
}
}

// Scanner of File
string scanner(ifstream &file) {
  int acele;
  int acele2;
  char ele;
  char ele2;
  string word;
  string tokenType;
  int decimal = 0;
  while(!(file.eof())){
    file >> word;
    for(int j = 0; j<word.length(); j++){
      ele = word.at(j);
      acele = (int)ele;
      if (word[j+1] != NULL) {
        ele2 = word[j+1];
        acele2 = (int)ele2;
      }
      else{
        
      }
      if (comment == 1) {
        string s1(1, ele);
        string s2(1, ele2);
        string type1 = s1 + s2;
        if (!type1.compare("*/")){
          comment = 0;
          j++;
          tokenType = "";
        }
      }
      else if(!word.compare("read")){
        return "read";
      }
      else if(!word.compare("write")){
        return "write";
      }
      else if (tokenType.empty()) {
        tokenType = charScanner(acele);
        if (acele == 42) {
          return tokenType;
        }
        else {}
      }
      else if (!tokenType.compare("id")) {
        string type2 = charScanner(acele);
        if (type2.compare("id") && type2.compare("number")) {
          return "error";
        }
      }
      else if (!tokenType.compare("number")) {
        string type2 = charScanner(acele);
        if (type2.compare("number") || (!type2.compare("decimal") && (decimal == 1)) || type2.compare("decimal")) {
          return "error";
        }
        else if (!type2.compare("decimal")) {
          decimal++;
        }
      }
      else if (!tokenType.compare("lpara") || !tokenType.compare("rpara") || !tokenType.compare("minus") || !tokenType.compare("plus") || !tokenType.compare("times")) {
        if (acele != NULL) {
          return "error";
        }
        else {}
      }
      else if (!tokenType.compare("div")) {
        if (acele2 == 42) {
          comment = 1;
          tokenType = "";
        }
        else if (acele != NULL) {
          return "error";
        }
        else {}
      }
    }
    if (!tokenType.compare("div")) {
      if(comment == 1){
        return "";
      }
      else{
        return "div";
      }
    }
    else if (comment == 1) {
      return "";
    }
    else {
      return tokenType;
    }
  }
}

int main(void) {
  // Read file input into queued structures
  ifstream file;
  file.open("input.txt");
  if (!file) {
    cout << "File cannot be opened." << endl;
    return 0;
  }

  while (!file.eof()) { // while file not end of file
    string token = scanner(file); // Add tokens to list
    if (token.compare("")) {
      tokenList.push_back(token);
    }
    else{
    }
    if (findError()) { // Check if there is an invalid token
      cout << "error." << endl;
      return 0;
    }
  }

  // Print list of tokens 
  cout << "(";
  printList();
  cout << ")" << endl;
  
  file.close();
  return 0;
}