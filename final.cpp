
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

// prototypes
void part1();
int part2();
void part3();
void print_stack(stack<string> Orginal);

int main () {
  string run;

  // display my information
  cout << "------------------------------------------------------------------" << '\n';
  cout << "      Name      : AJ Albrecht" << '\n';
  cout << "      Assignment: Final Project" << '\n';
  cout << "      Due Date  : 12/19" << '\n';
  cout << "-------------------------------------------------------------------" << '\n';

  // run each portion of the program
  part1();

  std::cout << '\n'  <<"Run Part 2?" << '\n';
  std::cin >> run;
  if (run == "y" || run == "Y") {
    part2();
  }

  part3();
  //if (accepted == 1) { part3(parsedString); }
}

void part1() {
  fstream inputFile;
  fstream outputFile;
  string input;
  string output;
  int isComment;
  int spaceCount;
  int exitLoop = 0;

  inputFile.open("finalp1.txt");
  outputFile.open("finalp2.txt");
  std::cout << '\n' << "finalp1.txt" << '\n';
  isComment = 0;
  spaceCount = 1;

  while (getline(inputFile, input)) { // get each line from file
    std::cout << input << "\n";
    // numbers used in if stament are connected to ther ASCII values
    for (size_t i = 0; i < input.size(); i++) {
      if (exitLoop == 1) { std::cout << "/* message */" << '\n'; }
      char c = input[i];
      char d = input[i-1]; // charcter to left of curent character
      char e = input[i+1]; // character to right of curent character

      char f = input[i+2];
      char g = input[i+3];
      char h = input[i+4];

      if ((42 == (int)c && 42 == (int)e) || (42 == (int)c && 42 == (int)d)) {
        // stop reading this portion, it is part of a comment
        if (isComment < 3) { isComment++; }
        else { isComment = 0; }
      }
      else if ((118 == (int)c) && (97 == (int)e) && (114 == (int)f) && (isComment == 0)) {
        // push var as a single line
        output.push_back(input[i]);
        output.push_back(input[i+1]);
        output.push_back(input[i+2]);
        output.push_back(' ');
        outputFile << output << "\n";
        output.erase();
        spaceCount = 1;
        break;
      }
      else if ((98 == (int)c) && (101 == (int)e) && (103 == (int)f) && (105 == (int)g) && (110 == (int)h) && (isComment == 0)) {
        // push begin as a single line
        output.push_back(input[i]);
        output.push_back(input[i+1]);
        output.push_back(input[i+2]);
        output.push_back(input[i+3]);
        output.push_back(input[i+4]);
        output.push_back(' ');
        outputFile << output << "\n";
        output.erase();
        spaceCount = 1;
        break;
      }
      else if ((101 == (int)c) && (110 == (int)e) && (100 == (int)f) && (46 == (int)g) && (isComment == 0)) {
        // push end. as a signle line
        output.push_back(input[i]);
        output.push_back(input[i+1]);
        output.push_back(input[i+2]);
        output.push_back(input[i+3]);
        output.push_back(' ');
        outputFile << output << "\n";
        output.erase();
        spaceCount = 1;
        exitLoop = 1;
        break;
      }
      else if (((43 == (int)c) || (61 == (int)c) || (44 == (int)c) || (40 == (int)c) || (41 == (int)c)) && (isComment == 0)) {
        // add in + - = ( or ) and add a spaces on either side if needs it
        if ((32 != (int)d) && (34 != (int)e)) { output.push_back(' '); }
        output.push_back(input[i]);
        if ((32 != (int)e) && (41 != (int)c) && (34 != (int)e)) { output.push_back(' '); } // dont add a space to ) as the ; will anyways
        spaceCount = 0;
      } else if ((32 == (int)c) && (spaceCount == 0) && (isComment == 0)) {
        // add a space to the line, and prevent future spaces form being added until the next token
        output.push_back(input[i]);
        spaceCount = 1;
      } else if ((32 == (int)c) && (spaceCount == 1) && (isComment == 0)) {
        // extra spaces are ignored
      } else if ((59 == (int)c) && (isComment == 0)) {
        // submit a new line to new data.txt since a semicolon was detected
        if (32 != (int)d) { output.push_back(' '); }
        output.push_back(input[i]);
        if (32 != (int)e) { output.push_back(' '); }
        outputFile << output << "\n";
        output.erase();
        spaceCount = 1;
      } else if (isComment == 0) {
        // none of the above special conditions are true, add the charcter to new file normaly
        output.push_back(input[i]);
        spaceCount = 0;
      }
    }
  }
  inputFile.close();
  outputFile.close();

  // read newdata.txt from the begining
  outputFile.open("finalp2.txt");
  std::cout << '\n'  << "finalp2.txt" << '\n';
  while (getline(outputFile, output)) {
    std::cout << output << '\n';
  }
  outputFile.close();
}

int part2() {
  fstream outputFile;
  string currentString;
  string currentTerminal;
  string output;

  string Table[24][34] = {{"", "p",	"i",	"v",	"s",	"q",	"z",	"t",	"(",	")",	"+",	"-",	"*",	"/",	",",	":",	";",	"=",	"1",	"2",	"3",	"4",	"5",	"6",	"7",	"8",	"9",	"0",	"a",	"b",	"c",	"d",	"f"	"w"},
  {"A",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"I=E;",	"I=E;",	"I=E;",	"I=E;",	"I=E;",	"I=E;"},
  {"B",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"C:J;",	"C:J;",	"C:J;",	"C:J;",	"C:J;",	"C:J;"},
  {"C",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"IG",	"IG",	"IG",	"IG",	"IG",	"IG"},
  {"D",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"1",	"2",	"3",	"4",	"5",	"6",	"7",	"8",	"9",	"0",	"",	"",	"",	"",	"",	"",},
  {"E",	"",	"",	"",	"",	"",	"",	"",	"TQ",	"",	"TQ",	"TQ",	"",	"",	"",	"",	"",	"",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ",	"TQ"},
  {"F",	"",	"",	"",	"",	"",	"",	"",	"(E)",	"",	"N",	"N",	"",	"",	"",	"",	"",	"",	"N",	"N",	"N",	"N",	"N",	"N",	"N",	"N",	"N",	"N",	"I",	"I",	"I",	"I",	"I",	"I"},
  {"G",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	",C",	"e",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	""},
  {"H",	"",	"",	"",	"",	"",	"U",	"e",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"U",	"U",	"U",	"U",	"U",	"U"},
  {"I",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"LY",	"LY",	"LY",	"LY",	"LY",	"LY"},
  {"J",	"",	"I",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	""},
  {"L",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"a",	"b",	"c",	"d",	"f",	"w"},
  {"N",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"SDZ",	"SDZ",	"",	"",	"",	"",	"",	"",	"SDZ",	"SDZ",	"SDZ",	"SDZ",	"SDZ",	"SDZ",	"SDZ",	"SDZ",	"SDZ",	"SDZ",	"",	"",	"",	"",	"",	""},
  {"O",	"",	"",	"",	"",	"q",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"e",	"e",	"e",	"e",	"e",	"e"},
  {"P",	"pI;vBsUt",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	""},
  {"Q",	"",	"",	"",	"",	"",	"",	"",	"",	"e",	"+TQ",	"-TQ",	"",	"",	"",	"",	"e",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	""},
  {"R",	"",	"",	"",	"",	"",	"",	"",	"",	"e",	"e",	"e",	"*FR",	"/FR",			"e",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	""},
  {"S",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"+",	"-",	"-",	"-",	"-",	"-",	"-",	"-",	"e",	"e",	"e",	"e",	"e",	"e",	"e",	"e",	"e",	"e",	"",	"",	"",	"",	"",	""},
  {"U",	"",	"",	"",	"",	"",	"",	"",	"FR",	"",	"FR",	"FR",	"-",	"-",	"-",	"-",	"-",	"-",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR",	"FR"},
  {"V",	"",	"",	"",	"",	"",	"VH",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"VH",	"VH",	"VH",	"VH",	"VH",	"VH"},
  {"W",	"",	"",	"",	"",	"",	"W",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"A",	"A",	"A",	"A",	"A",	"A"},
  {"X",	"",	"",	"",	"",	"",	"z(OI);",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	""},
  {"Y",	"",	"",	"",	"",	"",	"",	"",	"",	"e",	"e",	"e",	"e",	"e",	"e",	"e",	"e",	"e",	"DY",	"DY",	"DY",	"DY",	"DY",	"DY",	"DY",	"DY",	"DY",	"DY",	"LY",	"LY",	"LY",	"LY",	"LY",	"LY"},
  {"Z",	"",	"",	"",	"",	"",	"",	"",	"",	"e",	"e",	"e",	"e",	"e",	"",	"",	"e",	"",	"DZ",	"DZ",	"DZ",	"DZ",	"DZ",	"DZ",	"DZ",	"DZ",	"DZ",	"DZ",	"",	"",	"",	"",	"",	""}};
  stack<string> Stack;
  bool Continue;
  bool valid = 1;
  string Push_String;
  string Temp_String;
  string Current_Char;
  int Char_Number = -1;
  int Char_Table_Pos;
  string Current_State;
  int State_Table_Pos;

  string Word;
  string StringS = "";

  // Parse the string for the two other functions to use
  outputFile.open("finalp2.txt");
  while (getline(outputFile, output)) {
    for (size_t i = 0; i < output.size(); i++) {
      char b = output[i];
      if ((59 == (int)b)) { // respond to semicolon and iput
        currentString.push_back(output[i]);
        currentTerminal.erase();
        break;
      }
      else if ((32 != (int)b)) { currentString.push_back(output[i]); currentTerminal.push_back(output[i]); } // respond to regular charter and append
      else { // respond to end of token and use
        if (currentTerminal == "program") {
          currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back();
          //currentString.push_back('p');
          currentTerminal.erase();
        } else if (currentTerminal == "var") {
          currentString.pop_back(); currentString.pop_back(); currentString.pop_back();
          currentString.push_back('v');
          currentTerminal.erase();
        } else if (currentTerminal == "begin") {
          currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back();
          currentString.push_back('s');
          currentTerminal.erase();
        } else if (currentTerminal == "end.") {
          currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back();
          currentString.push_back('t');
          currentTerminal.erase();
        } else if (currentTerminal == "integer") {
          currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back();
          currentString.push_back('i');
          currentTerminal.erase();
        } else if (currentTerminal == "write") {
          currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back();
          currentString.push_back('z');
          currentTerminal.erase();
        } else if (currentTerminal.find("value") != std::string::npos) {
          currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back(); currentString.pop_back();
          currentString.push_back('q');
          currentTerminal.erase();
        } else {
          currentTerminal.erase();
        }
      }
    }
  }
  //std::cout << currentString << '\n';
  outputFile.close();
  Word = currentString;

  // push intial stack values
  Stack.push("t");
  Stack.push("P");
  std::cout << "Tracing " << Word << '\n';

  // as long as the word is good, check each charcter
  for (size_t i = 0; i < Word.length(); i++) {
    if (valid == false) {
      std::cout << "This expression is not included in the gramar" ;
      break;
    }

    Current_Char = Word[++Char_Number];
    // get input row number
    for (size_t i = 1; i < 35; i++) {if (Table[0][i] == Current_Char) {Char_Table_Pos = i;}}

    // While the charcter has not been found, keep looking
    Continue = true;
    while (Continue == true) {
      Current_State = Stack.top();
      std::cout << "Pop: " << Current_State;
      Stack.pop();

      if (Current_State == "e") {
        Stack.pop(); // If Lamda is read, pop an extra character of the stack
      } else if (Current_State == "") {
        std::cout << "    Fallied to find-> " << Current_Char <<'\n';
        valid = false;  // An empty box was read. The gramar is incorect.
        break;
      } else if (Current_State == Current_Char){
        std::cout << "      Match-> " << Current_State << '\n'; // match was found
        break;
      } else {

        // get state row number
        for (size_t i = 1; i < 35; i++) {if (Table[i][0] == Current_State) {State_Table_Pos = i;}}

        // push the contents of the box in revers order into the stack
        Push_String = Table[State_Table_Pos][Char_Table_Pos];
        std::cout << "      Go to: [" << Current_State << "," << Current_Char << "] = " << Push_String;
        std::cout << "      Push: " ;
        for (size_t i = Push_String.length()-1; i > -1 ; i--) {
          Temp_String = Push_String[i];
          if (Temp_String != "L") {
            Stack.push(Temp_String);
            std::cout << Temp_String;
          } else {
            std::cout << "nothing";
          }
        }
        print_stack(Stack);
        std::cout << "" << '\n';
      }
    }
  }
  std::cout << '\n';

  return 1;
}

void part3 () {
  fstream outputFile;
  string parsedString[100];
  int tokenCount = 0;
  string currentString;
  string output;

  fstream inputFile;
  string input;
  int state;

  // Parse the string for the two other functions to use
  outputFile.open("finalp2.txt");
  while (getline(outputFile, output)) {
    for (size_t i = 0; i < output.size(); i++) {
      char b = output[i];
      if ((59 == (int)b)) { // respond to semicolon and iput
        currentString.push_back(output[i]);
        parsedString[tokenCount] = currentString;
        tokenCount++;
        currentString.erase();
        break;
      }
      else if ((32 != (int)b)) { currentString.push_back(output[i]); } // respond to regular charter and append
      else { // respond to end of token and use
        parsedString[tokenCount] = currentString;
        tokenCount++;
        currentString.erase();
      }
    }
  }
  outputFile.close();

  outputFile.open("finalp3.cpp");
  // change the program into c++
  // add initial statments
  outputFile << "#include <iostream>" << '\n';
  outputFile << "using namespace std;" << '\n';
  outputFile << "int main()" << '\n';
  outputFile << "{" << '\n';
  output.erase();
  output = "int ";

  // add all integers
  for (size_t i = 4; i < 100; i++) {
    string a = parsedString[i];
    if (a != ":") { output = output + a + " "; }
    else { state = i; output = output + ";"; break; }
  }
  outputFile << output << '\n';
  output.erase();

  // add main code
  state = state + 4; // exactly 4 space every time
  output = output + "   ";
  for (size_t i = state; i < 100; i++) {
    string a = parsedString[i];
    if (a == ";") {
      output = output + " ;";
      outputFile << output << '\n';
      output.erase();
      output = output + "   ";
    } else if (a == "write") {
      output = output + "cout<<";
      i = i + 2; // skips (
      a = parsedString[i];
      if (a.find("value=") != string::npos) {
        output = output + " \"value=\"<<";
        i = i + 2;
        a = parsedString[i];
        output = output + a + "<<endl";
        i++;
      } else {
        output = output + a + "<<endl";
        i++;
      }
    } else {
      output = output + a + " ";
    }
  }
  outputFile << "   return 0;" << '\n';
  outputFile << "}" << '\n';

  outputFile.close();


  // read finalp3.txt from the begining
  outputFile.open("finalp3.cpp");
  std::cout << '\n'  << "finalp3.cpp" << '\n';
  while (getline(outputFile, output)) {
    std::cout << output << '\n';
  }
  outputFile.close();
}

// print stack for part 2 function
void print_stack(stack<string> Original) {
  stack<string> Print_Stack;
  // Create a new stack with the orginal stack contents backwords
  // This will allow the print mesage to be in the right order
  std::cout << "      ";
  while (Original.empty() == false) {
    Print_Stack.push(Original.top());
    Original.pop();
  }
  std::cout << "Stack-> " ;
  while (Print_Stack.empty() == false) {
    std::cout << Print_Stack.top();
    Print_Stack.pop();
  }
}
