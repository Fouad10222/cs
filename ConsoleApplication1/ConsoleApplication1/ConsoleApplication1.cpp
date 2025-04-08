#include <iostream>
#include <cctype>
#include <string>

using namespace std;

// Global declarations
int charClass; // Store character class like LETTER 
string lexeme; // holds the lexeme  
char nextChar; //  store the next character to be processed
int lexLen; // store the length of the lexeme 
int token; //  store the current token
int nextToken; // 

// Character classes
#define LETTER 0 // represent letter
#define DIGIT 1 // represent Digit
#define UNKNOWN 99 //represent unknown character

// Token codes
#define INT_LIT 10  // Integer 
#define IDENT 11   // variable names
#define ASSIGN_OP 20 // (=)
#define ADD_OP 21 // (+)
#define SUB_OP 22 // (-)
#define MULT_OP 23 // (*)
#define DIV_OP 24 // (/)
#define LEFT_PAREN 25 // (()
#define RIGHT_PAREN 26 // ())

// Function declarations
void addChar(); // fun to add char 
void getChar(); // fun read the next char
void getNonBlank(); // 
int lex(); // main fun of the lex
int lookup(char ch); // Fun to lookup operators 

int main() {
    cout << "Enter the arithmetic expression: ";

    // Start reading input from user
    getChar(); // get char from input
    do {
        lex();
    } while (nextToken != EOF); //Continue if token is not EOF

    return 0;
}

// lookup - a function to lookup operators and parentheses and return the token
int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar(); //Add char to lexeme
        nextToken = LEFT_PAREN; // set left_Paren
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN; // set right_paren
        break;
    case '+':
        addChar();
        nextToken = ADD_OP; // set add operation
        break;
    case '-':
        addChar();
        nextToken = SUB_OP; //set sub operation 
        break;
    case '*':
        addChar();
        nextToken = MULT_OP; // set mult operation 
        break;
    case '/':
        addChar();
        nextToken = DIV_OP; // set div operation
        break;
    default:
        addChar();
        nextToken = EOF;  //unknown char 
        break;
    }
    return nextToken; //Return token type
}

// addChar - a function to add nextChar to lexeme
void addChar() {
    if (lexLen <= 98) { //check if lexeme has space to add more char
        lexeme += nextChar; // add char 
        lexLen++; // increment the length of the lexeme 
    }
    else {
        cerr << "Error - lexeme is too long" << endl; // if lexeme is overflow
    }
}

// getChar - a function to get the next character of input and determine its character class
void getChar() {
    cin.get(nextChar); // Read one character from user input
    if (cin) { // check if char was read
        if (isalpha(nextChar)) { // check if char letter
            charClass = LETTER;
        }
        else if (isdigit(nextChar)) { // check if char digit 
            charClass = DIGIT;
        }
        else {
            charClass = UNKNOWN; // if char is unknown
        }
    }
    else {
        charClass = EOF; // End of input
    }
}

// getNonBlank - a function to call getChar until it returns a non-whitespace character
void getNonBlank() {
    while (isspace(nextChar)) { // check if char is whitespace
        getChar();
    }
}

// lex - a simple lexical analyzer for arithmetic expressions
int lex() {
    lexLen = 0;
    lexeme.clear();
    getNonBlank(); // Skip whitespace
    switch (charClass) {
        // Parse identifiers
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) { // if the char is a letter or digit
            addChar();
            getChar();
        }
        nextToken = IDENT; //Set  token type to identifier
        break;

        // Parse integer literals
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {// if char is digit
            addChar();
            getChar();
        }
        nextToken = INT_LIT; //Set token type to int
        break;

        // Parentheses and operators
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;

        // EOF
    case EOF:
        nextToken = EOF; //Set nextToken to EOF
        lexeme = "EOF";
        break;
    }
    cout << "Next token is: " << nextToken << ", Next lexeme is: " << lexeme << endl;
    return nextToken;
}
