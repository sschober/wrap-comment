#include <unistd.h>
#include <iostream>
#include "string-utils.h"
using namespace std;

#define   FILL_CHAR      ' '
#define   PADDING       1

int main(int argc, char *argv[]){
  string commentString = "#";
  int wrapColumn       = 80;
  bool unwrap          = false;
  int opt;
  while( (opt = getopt(argc, argv, "d:w:u")) != -1 ){
    switch(opt){
      case 'd':
        commentString = string( optarg );
        break;
      case 'w':
        wrapColumn = atoi( optarg );
        break;
      case 'u':
        unwrap = true;
        break;
      default:
        cerr << "Usage: " << argv[0]
          << " [-d '<comment string>'] [-w <wrap column>]"
          << endl;
        exit(EXIT_FAILURE);
    }
  }
  list<string> codeLines;
  string comment;
  size_t maxCodeLine = 0;

  string line;
  while(getline(cin, line)){                              // Wir lesen STDIN Zeile
    size_t commentCharIdx = line.find(commentString);     // für Zeile ein und splitten
    string code = rtrim(line.substr(0, commentCharIdx )); // jede in einen Code-Teil
    if(code.size() > maxCodeLine){                        // und einen Kommentarteil
      maxCodeLine = code.size();                          // auf. Die Code-Zeilen
    }                                                     // fügen wir zu _einer_
    if(! code.empty() && ! isWhiteSpace(code) ){          // langen Zeile zusammen,
      codeLines.push_back(code);                          // die Code-Zeilen speichern
    }                                                     // wir in einem Vektor.
    if( string::npos != commentCharIdx ){
      comment +=
        line.substr(
            commentCharIdx+commentString.size(),
            string::npos
        );
    }
  }

  maxCodeLine += PADDING; // Zur längsten Zeile fügen wir noch einen Abstand hinzu

  size_t commentLength = wrapColumn - maxCodeLine; // Wie lange darf ein Kommentar
                                                   // längstens sein?

  list<string> commentWords = split( comment ); // Wir splitten die Kommentarzeile
                                                // in Wörter auf

  do {                                                 // Konzeptionell laufen wir
    string newLine;                                    // hier über die vorher gesammelten
    if( ! codeLines.empty() ){                         // Code-Zeilen und fügen
      newLine += codeLines.front();                    // so lange Kommentarwörter
      codeLines.pop_front();                           // zur aktuellen Zeile hinzu,
    }                                                  // bis die maximale Zeilenlänge
    if( ! commentWords.empty() ) {                     // erreicht ist. Falls nach
      if( unwrap ){                                    // Abarbeiten aller Code-Zeilen
        commentWords.clear();                          // noch Kommentarwörter übrig
        newLine.append(1, FILL_CHAR);                  // sind werden diese in der
        newLine.append(commentString);                 // selben Einrückung weiter
        newLine.append(1, FILL_CHAR);                  // in leeren Zeilen fortgesetzt.
        newLine.append( comment );
      }
      else {
        size_t padding = maxCodeLine - newLine.size();
        newLine.append(padding, ' ');
        newLine.append(commentString);
        do {
          newLine.append(1, FILL_CHAR);
          newLine.append( commentWords.front() );
          commentWords.pop_front();
          if(commentWords.empty()) break;
        } while(newLine.size() < wrapColumn );
      }
    }
    cout << newLine << endl;
  } while(
      ! codeLines.empty() ||
      ! commentWords.empty()
      );
}
