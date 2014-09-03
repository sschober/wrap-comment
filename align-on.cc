#include <unistd.h>
#include <iostream>
#include "string-utils.h"
#include <tuple>
using namespace std;

#define   FILL_CHAR      ' '
#define   PADDING       1

int main(int argc, char *argv[]){
  string delimString = "=";
  int opt;
  while( (opt = getopt(argc, argv, "d:w:")) != -1 ){
    switch(opt){
      case 'd':
        delimString = string( optarg );
        break;
      default:
        cerr << "Usage: " << argv[0]
          << " [-d '<comment string>']"
          << endl;
        exit(EXIT_FAILURE);
    }
  }
  list<tuple<string,string,bool>> lines;
  list<string> leftLines;
  list<string> rightLines;
  string comment;
  size_t maxCodeLine = 0;

  string line;
  while(getline(cin, line)){                              // Wir lesen STDIN Zeile
    tuple<string,string,bool> lineEntry;
    size_t commentCharIdx = line.find(delimString);     // für Zeile ein und splitten
    if( string::npos == commentCharIdx ){
      lines.push_back( make_tuple(
            line, "", false));
      continue;
    }
    string left = rtrim(line.substr(0, commentCharIdx )); // jede in einen Code-Teil
    string right = ltrim(line.substr(
          commentCharIdx+delimString.size(),
          string::npos
          ));
    if(left.size() > maxCodeLine){                        // und einen Kommentarteil
      maxCodeLine = left.size();                          // auf. Die Code-Zeilen
    }                                                     // fügen wir zu _einer_
    lines.push_back( make_tuple(
          left, right, true ));
  }

  maxCodeLine += PADDING; // Zur längsten Zeile fügen wir noch einen Abstand hinzu

  for( tuple<string,string,bool> line : lines ){
    string left( get<0>(line) );
    string right( get<1>(line) );
    if( get<2>(line) ){
      size_t padding = maxCodeLine - left.size();
      if( 0 < padding ){
        left.append( padding, ' ');
        left.append( delimString );
        if( ! right.empty() && ! isWhiteSpace( right ))
          left.append( PADDING, ' ');
      }
    }
    left.append( right );
    cout << left << endl;
  }
}

