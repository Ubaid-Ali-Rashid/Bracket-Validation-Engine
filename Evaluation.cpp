#include <iostream>
#include <string>
using namespace std;

// Node structure for LinkedList based Stack
struct Node {
    char bracket;   // stores the bracket character
    int position;   // stores the position of bracket in sequence
    Node* next;     // pointer to next node
};

// Stack implemented using LinkedList
class Stack {
    Node* top;      // pointer to top of stack
    int size;       // tracks size of stack

public:
    // initialize empty stack
    Stack() {
        top = NULL;
        size = 0;
    }

    // push bracket and its position onto stack
    void push(char bracket, int pos) {
        Node* newNode = new Node();  // create new node
        newNode->bracket = bracket;    // store bracket
        newNode->position = pos;        // store position
        newNode->next = top;        // link to previous top
        top = newNode;    // update top
        size++;
    }

    // remove top node from stack
    void pop() {
        if(top == NULL) return;         // nothing to pop
        Node* temp = top;               // hold reference to delete
        top = top->next;         // move top down
        delete temp;                    // free memory
        size--;
    }

    // return bracket at top without removing
    char peekBracket() {
        if(top == NULL) return '?';     // empty stack
        return top->bracket;
    }

    // return position at top without removing
    int peekPosition() {
        if(top == NULL) return -1;      // empty stack
        return top->position;
    }

    // check if stack is empty
    bool isEmpty() {
        return top == NULL;
    }

    // get current size of stack
    int getSize() {
        return size;
    }
};

// Error structure to store error info
struct Error {
    string type;      // error type: MISPLACED, MISSING, EXTRA
    char bracket;   // which bracket caused error
    int position;  // where in sequence
    string detail;    // detailed message
};

// Validator class handles all bracket checking logic
class Validator {
    string seq;           // input sequence
    Stack stk;           // linkedlist based stack
    Error errors[100];   // array to store all errors found
    int errorCount;    // how many errors found

public:
    // initialize with zero errors
    Validator() {
        errorCount = 0;
    }

    // set new sequence and reset state for fresh validation
    void setSequence(string s) {
        seq = s;
        errorCount = 0;
        while(!stk.isEmpty()) stk.pop();  // clear stack for new input
    }

    // check if character is an opening bracket
    bool isOpening(char c) {
        return c == '(' || c == '[' || c == '{';
    }

    // check if character is a closing bracket
    bool isClosing(char c) {
        return c == ')' || c == ']' || c == '}';
    }

    // return the expected closing bracket for a given opening bracket
    char getMatch(char c) {
        if(c == '(') return ')';
        if(c == '[') return ']';
        if(c == '{') return '}';
        return '?';
    }

    // main validation logic using stack
    void validate() {
        for(int i = 0; i < seq.length(); i++) {
            char c = seq[i];   // current character

            if(isOpening(c)) {
                stk.push(c, i);    // push opening bracket onto stack
            }
            else if(isClosing(c)) {

                if(stk.isEmpty()) {
                    // stack empty means no opening bracket exists for this closing one
                    errors[errorCount].type = "EXTRA BRACKET";
                    errors[errorCount].bracket  = c;
                    errors[errorCount].position = i + 1;
                    errors[errorCount].detail = "No opening bracket exists for '" + string(1,c) + "' at position " + to_string(i+1);
                    errorCount++;
                }
                else {
                    char topBracket = stk.peekBracket();    // get top bracket
                    int topPos = stk.peekPosition();   // get top position
                    stk.pop();                              // remove from stack

                    if(getMatch(topBracket) != c) {
                        // closing bracket doesnt match the opening bracket on top
                        errors[errorCount].type = "MISPLACED BRACKET";
                        errors[errorCount].bracket = c;
                        errors[errorCount].position = i + 1;
                        errors[errorCount].detail = "Found '" + string(1,c) + "' but expected '" + string(1,getMatch(topBracket)) + "' to close '" + string(1,topBracket) + "' opened at position " + to_string(topPos+1);
                        errorCount++;
                    }
                    // else: matched correctly, no error
                }
            }
            // non-bracket characters are ignored
        }

        // anything left in stack has no closing bracket
        while(!stk.isEmpty()) {
            char topBracket = stk.peekBracket();    // get unmatched bracket
            int  topPos = stk.peekPosition();   // get its position
            stk.pop();                              // remove from stack

            errors[errorCount].type = "MISSING BRACKET";
            errors[errorCount].bracket = topBracket;
            errors[errorCount].position = topPos + 1;
            errors[errorCount].detail = "No closing bracket for '" + string(1,topBracket) + "' opened at position " + to_string(topPos+1);
            errorCount++;
        }
    }

    // display results to user
    void display() {
        cout << "\nSequence : " << seq << "\n";

        if(errorCount == 0) {
            // no errors found
            cout << "Result   : VALID - All brackets matched correctly.\n";
        }
        else {
            // print all errors found
            cout << "Result   : INVALID - " << errorCount << " error(s) found.\n\n";
            for(int i = 0; i < errorCount; i++) {
                cout << "Error " << i+1 << ":\n";
                cout << "  Type     : " << errors[i].type     << "\n";
                cout << "  Bracket  : " << errors[i].bracket  << "\n";
                cout << "  Position : " << errors[i].position << "\n";
                cout << "  Detail   : " << errors[i].detail   << "\n\n";
            }
        }
    }
};

int main() {
    Validator v;    // create validator object
    string input;   // user input sequence
    char opt = ' '; // loop control


    while(opt != 'q') {
        cout << "\nEnter sequence (or 'q' to quit): ";
        cin >> input;

        if(input == "q") { opt = 'q'; break; }  // quit condition

        v.setSequence(input);   // set sequence in validator
        v.validate();           // run validation
        v.display();            // show results
    }

    cout << "Goodbye!\n";
    return 0;
}
