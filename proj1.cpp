/*****************************************                                      
** File:    proj1.cpp                                                           
** Project: CMSC 202 Proj 1, Spring 2024                                        
** Author:  Adam OWOLABI                                                        
** Date:    2/14/24                                                             
** Section: section 41                                                               
** E-mail:  AOWOLAB1@gl.umbc.edu                                                
**                                                                              
** This file contains the proj1 file                                            
** This program reads a file and makes the user guess a puzzle of phrases by    
** entering a letter.                                                           
**                                                                              
**                                                                              
***********************************************/
//** must have 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace	std;


const int LENGTH_OF_FILE = 48;   //constant for the length of file to be read
const int ASCII_NUM = 256;  //length of ascii values       
const string FILE_NAME = "proj1_data.txt";  //file name to be read from
const int SMALLEST_UPPERCASE_ASCII = 64;  //capital A ascii values used for input validation   
const int BIGGEST_UPPERCASE_ASCII = 91;  //capital Z ascii values. used for input calidation
const int ASCII_DIFFERENCE = 32;   //difference between uppercase and lowerase ascii
const int MIN = 0;       //smallest minimum                            


//functions prototypes

//-------------------------------------------------------
// Name: loadFile
// Desc: load the input file
// PreCondition:  requires that a fileName is valid and in the same folder
// PostCondition: updates the arrays of puzzle and categories
//---------------------------------------------------------
void loadFile(int fileLength, string fileName, string puzzleArr[], string categoryArr[]);

//-------------------------------------------------------
// Name: getAnswer
// Desc: 
// PreCondition:  requires a seed and max values of random number
// PostCondition: return a random value
//---------------------------------------------------------
int getAnswer(int max);

//-------------------------------------------------------
// Name: getInput
// Desc: get input of lowercases 
// PreCondition:  requires that puzzle is hidden and category is display to user
// PostCondition: Returns the upercase acii value of the lower letter guessed
//---------------------------------------------------------
int getInput(int guessed[]);

//-------------------------------------------------------
// Name: inPuzzle
// Desc: decide if it's in puzzle
// PreCondition:  requires that a puzzle has been randomly selected
// PostCondition: 
//---------------------------------------------------------
void inPuzzle(char puzzle[], int upperLetterAscii, int sizePuzzle, char puzzleCopy[], int guessed[]);

//-------------------------------------------------------
// Name: isCompleted
// Desc: decide if puzzle is completed
// PreCondition:  requires puzzle has been updated and no same puzzle is passsed.
// PostCondition: Returns true or false if puzzle is completely guessed
//---------------------------------------------------------
bool isCompleted(char puzzle[], char puzzleCopy[], int charLength);

//-------------------------------------------------------
// Name: printPuzzle
// Desc: prints puzzle when done.
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
void printPuzzle(char puzzle[]);




int main(){
    //3 arrays, 1 for categories, 1 to store list of puzzles, ! to store all characters guessed. 
    string categoryArr[LENGTH_OF_FILE/2];
    string puzzleArr[LENGTH_OF_FILE/2];
    int guessed[ASCII_NUM] = {0};
    int sizePuzzle = 0;
    int randomValue = 0;
    char underscore = '_';
    bool flag = false;
    int upperLetterAscii = 0;
    int charLength;
    int i = 0;

    //welcome statements
    cout << "Welcome to UMBC Fortune Wheel!" << endl;
    cout <<  LENGTH_OF_FILE/2 << " puzzles loaded." << endl;
    

    loadFile(LENGTH_OF_FILE, FILE_NAME, puzzleArr, categoryArr);

    //get a random number to be used to llok up puzzle and category
    //[0,23] between 0-23 included
    randomValue = getAnswer((LENGTH_OF_FILE/2)-1); 

    //hint of what category puzzle is in:
    cout << "Category is: " << categoryArr[randomValue] << endl;
   

    //convert puzzle c-string 
    string strPuzzle = puzzleArr[randomValue];


    sizePuzzle = strPuzzle.length();
    cout << "Size is: " << sizePuzzle << endl;
    
    //now that we know the length of char, define them.
    char puzzle[sizePuzzle + 1];
    char puzzleCopy[sizePuzzle + 1];

    charlength = sizeof(puzzle)/sizeof(char);

     //manually copy string to a c-string: 
    while(i < sizePuzzle && strPuzzle[i] != '\0' ){
        puzzle[i] = strPuzzle[i];
        puzzleCopy[i] = strPuzzle[i];
        i++;
    }

    //add nullterminaotr to the last index of c-strings
    puzzle[sizePuzzle] = '\0';
    puzzleCopy[sizePuzzle] = '\0';
  
    cout << "seePuzz: " << strPuzzle << endl;

    //replace the letters with underscores
    for(int i = 0; i < sizePuzzle; i++){
        if(puzzle[i] != ' '){
            puzzle[i] = underscore;
        }
    }
    //print underscore/updated filled puzzle
    printPuzzle(puzzle); 

    //if flag is not currently true, don't stop runnning code. flag is true only when there're no undescores.
    while(flag != true){
        upperLetterAscii = getInput(guessed);
        inPuzzle(puzzle, upperLetterAscii, sizePuzzle, puzzleCopy, guessed);
        //if no underscore exists, stop the code;
        flag = isCompleted(puzzle, puzzleCopy, charLength);
     
    }


    //goodbye statement
    cout << "you won!" << endl;
}

void loadFile(int fileLength, string fileName, string puzzleArr[], string categoryArr[]){

    ifstream inputStream;
    inputStream.open(fileName);

    string line;
    int lineNumber = 0;

    while(getline(inputStream, line)){
        lineNumber++;

        if(lineNumber % 2 == 1){
            categoryArr[lineNumber/2] = line;
        }
        else if(lineNumber % 2 == 0){
            puzzleArr[lineNumber/2 - 1] = line;
        }
    }
}

int getAnswer(int max){
    int randomVal = 0;
    srand(time(NULL));  //seed the random number 
    randomVal = rand() % (max - MIN + 1) + MIN;
    cout << "randomVal: " << randomVal << endl;
    return randomVal;

}

//validate guesses 
int getInput(int guessed[]){
    char letter;
    int upperLetterAsciiLocal;
    
        cout << "What lowercase letter would you like to try? "<< endl;
        cin >> letter;
        upperLetterAsciiLocal = letter - ASCII_DIFFERENCE;
        //convert to upperletter
    do{
        if(upperLetterAsciiLocal < SMALLEST_UPPERCASE_ASCII || upperLetterAsciiLocal > BIGGEST_UPPERCASE_ASCII){
            cout << "Invalid input, Enter an lowercase letter:" << endl;
            upperLetterAsciiLocal = 0;
            cin >> letter;
            upperLetterAsciiLocal = letter - ASCII_DIFFERENCE;
        }
    }while(upperLetterAsciiLocal < SMALLEST_UPPERCASE_ASCII || upperLetterAsciiLocal > BIGGEST_UPPERCASE_ASCII);

    //return index of a valid upperletter
    return upperLetterAsciiLocal;

}

void inPuzzle(char puzzle[], int upperLetterAscii, int sizePuzzle, char puzzleCopy[], int guessed[]){
    bool flagLocal = false;
    int count = 0;
   
    if(guessed[upperLetterAscii] != 1){
        for(int i = 0; i < sizePuzzle; i++){
        if(puzzleCopy[i] != char(upperLetterAscii)){
        }
    }

    for(int i = 0; i < sizePuzzle; i++){
        if(puzzleCopy[i] == char(upperLetterAscii)){
            count++;
            puzzle[i] = char(upperLetterAscii);
            flagLocal = true;  //change to true becasue the letter guessed is in the puzzle
            guessed[upperLetterAscii] = 1;//change the ascii counter to be 1;
        //replace the underscore with the actuall letter.
        }
    }

    if(flagLocal == false){
        cout << "No " << char(upperLetterAscii) << " found in puzzle" << endl;
        guessed[upperLetterAscii] = 1;//change the ascii counter to be 1;

    }else if(flagLocal == true){
        cout << count << " " << char(upperLetterAscii) << " found in puzzle." << endl;
        guessed[upperLetterAscii] = 1;//change the ascii counter to be 1;
        printPuzzle(puzzle);
    }
    }else {
        cout << char(upperLetterAscii) << " letter has been guessed"<< endl;
    }

     //check to see if a valid guess is in puzzle
}

bool isCompleted(char puzzle[], char puzzleCopy[], int charLength){
    for(int i = 0; i < charLength; i++){
            if(puzzle[i] != puzzleCopy[i]){
                return false;
            } 
    }
    return true;
}
void printPuzzle(char puzzle[]){
    cout << puzzle << endl;
}
   /*
    submit:
    cp proj1.cpp ~/cs202proj/proj1
    */

