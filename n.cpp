#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  string input1;
  string input2;
  string operation;
  vector <int> transition1;
  vector <int> transition2;
  vector <int> exitt;
  vector <int> division;
  int index1;
  int index2;
  int buffer = 0;
  
  cout << "Введите первое число: ";
  getline(cin, input1);
  
  for (int index = 0; index < input1.length(); ++index) {
    transition1.push_back(input1[index] - '0');
  }
  
  cout << "Введите операцию: ";
  getline(cin, operation);
  
  if (operation != "+" && operation != "-" && operation != "*" && operation != "/" && operation != ">" && operation != "<" && operation != "=") {
    cout << "Неправильный ввод";
    return 0;
  }
  
  cout << "Введите второе число: ";
  getline(cin, input2);
  
  for (int index = 0; index < input2.length(); ++index) {
    transition2.push_back(input2[index] - '0');
  }
  
  cout << "\nРезультат: ";
  
  if (transition1.size() > transition2.size()) {
    for (int index = 0; index < transition1.size() - transition2.size(); ++index) {
      transition2.insert(transition2.begin(), 0);
    }
  }
  if (transition1.size() < transition2.size()) {
    for (int index = 0; index < transition2.size() - transition1.size(); ++index) {
      transition1.insert(transition1.begin(), 0);
    }
  }
  
  if (operation == "=") {
    for (int index = 0; index < transition1.size(); ++index) {
      if (transition1[index] != transition2[index]) {
        buffer = 0;
        break;
      } else {
        buffer = 1;
      }
    }
    
    cout << buffer;
  }
  
  if (operation == "<") {
    for (int index = 0; index < transition1.size(); ++index) {
      if (transition1[index] < transition2[index]) {
        buffer = 1;
        break;
      } else if (transition1[index] > transition2[index]) {
        buffer = 0;
        break;
      } else {
        buffer = 0;
      }
    }
  }
  
  if (operation == ">") {
    for (int index = 0; index < transition1.size(); ++index) {
      if (transition1[index] > transition2[index]) {
        buffer = 1;
        break;
      } else if (transition1[index] < transition2[index]) {
        buffer = 0;
        break;
      } else {
        buffer = 0;
      }
    }
  }
  
  if (operation == "+") {
    for (int index = transition1.size() - 1; index >= 0; --index) {
      exitt.insert(exitt.begin(), transition1[index] + transition2[index]);
      
      if (exitt.size() > 1) {
        exitt[0] += exitt[1] / 10;
        exitt[1] %= 10;
      }
    }
    
    for (int index = 0; index < exitt.size(); ++index) {
      cout << exitt[index];
    }
  }
  
  if (operation == "-") {
    for (int index = 0; index < transition1.size(); ++index) {
      if (transition1[index] > transition2[index]) {
        buffer = 1;
        break;
      }
      if (transition1[index] < transition2[index]) {
        buffer = -1;
        break;
      }
    }
    
    if (buffer == 0) {
      cout << 0;
      return 0;
    }
    
    if (buffer == 1) {
      for (int index = transition1.size() - 1; index >= 0; --index) {
        exitt.insert(exitt.begin(), transition1[index] - transition2[index]);
        
        if (exitt.size() > 1) {
          if (exitt[1] < 0) {
            exitt[0] -= 1;
            exitt[1] += 10;
          }
        }
      }
    }
    
    if (buffer == -1) {
      for (int index = transition1.size() - 1; index >= 0; --index) {
       exitt.insert(exitt.begin(), transition2[index] - transition1[index]);
        
        if (exitt.size() > 1) {
          if (exitt[1] < 0) {
            exitt[0] -= 1;
            exitt[1] += 10;
          }
        }
      }
      
      cout << "-";
    }
    
    for (int index = 0; index < exitt.size(); ++index) {
      cout << exitt[index];
    }
  }
  
  if (operation == "*") {
    while (exitt.size() < transition1.size() + transition2.size()) {
      exitt.push_back(0);
    }
    
    for (index1 = transition1.size(); index1 > 0; --index1) {
      for (index2 = transition2.size(); index2 > 0; -- index2) {
        exitt[index1 + index2 - 1] += transition1[index1 - 1] * transition2[index2 - 1];
        if (exitt[index1 + index2 - 1] >= 10) {
          exitt[index1 + index2 - 2] += exitt[index1 + index2 - 1] / 10;
          exitt[index1 + index2 - 1] %= 10;
        } 
      }
    }
    
    for (int index = 0; index < exitt.size(); ++index) {
      if (exitt[index] != 0) {
        buffer = 1;
      }
      
      if (buffer == 1) {
        cout << exitt[index];
      }
    }
  }
  
  if (operation == "/") {
   exitt.insert(exitt.begin(), 0);
    while (buffer == 0) {
      if (division.size() < transition2.size()) {
        for (int index = 0; index < transition2.size(); ++index) {
          division.insert(division.end(), transition2[index]);
        }
      } else {
        for (int index = transition2.size() - 1; index >= 0; --index) {
          division[division.size() - transition2.size() + index] += transition2[index];
        }
        
        for (int index = division.size() - 1; index >= 0; -- index) {
          if (division[index] >= 10) {
            if (index == 0) {
              division.insert(division.begin(), division[0] / 10);
              division[index + 1] %= 10;
            }
            else {
              division[index - 1] += division[index] / 10;
              division[index] %= 10;
            }
          }
        }
      }
      
      if (division.size() == transition1.size()) {
        for (int index = 0; index < transition1.size(); ++index) {
          if (transition1[index] < division[index]) {
            buffer = 1;
            break;
          } else if (transition1[index] > division[index]) {
            buffer = 0;
            break;
          } else {
            buffer = 0;
          }
        }
      } else if (division.size() > transition1.size()) {
        buffer = 1;
      }
      
      if (buffer == 0) {
        exitt[exitt.size() - 1] += 1;
        for (int index = exitt.size() - 1; index >= 0; --index) {
          if (exitt[index] >= 10) {
            if (index == 0) {
              exitt.insert(exitt.begin(), exitt[0] / 10);
              exitt[index + 1] %= 10;
            } else {
              exitt[index - 1] += exitt[index] / 10;
              exitt[index] %= 10;
            }
          }
        }
      }
    }
    for (int index = 0; index < exitt.size(); ++index)
    cout << exitt[index];
  }

  return 0;
}
