#include <unistd.h>
#include <iostream>
#include <string>
#include <list>
#include <tuple>
using namespace std;

#define   FILL_CHAR      ' '
#define   PADDING       1

string rtrim( string str ){                   // Wir initialisieren eine Laufvariable
  size_t i = str.size();                      // mit dem Ende des Strings und zählen
  while( i > 0 && isspace(str[i-1])) { --i; } // bis zum ersten Nichtleerzeichen
  return str.erase(i,string::npos);           // zurück. Dann löschen wir alles
}                                             // ab diesem Index.

bool isWhiteSpace( string str ){ // Wir löschen alle Leerzeichen im String. Wenn
  return rtrim(str).empty();     // er dann leer ist, bestand er nur aus Leerzeichen.
}

/**
 * Splitet `str` an `ws` auf und gibt Partikel/Wörter als Liste zurück
 */
list<string> split(  string str, const char *ws = " " ) { // Konzeptionell iterieren
  list<string> result;                                    // wir hier über `str`,
  size_t idx = 0;                                         // in dem wir immer wieder
  while( string::npos != ( idx = str.find(ws))){          // das nächste Leerzeichen
    string word = str.substr(0,idx);                      // (`ws`) suchen und von
    if( ! word.empty() ){                                 // 0 bis dort als neues
      result.push_back( word );                           // Wort zur Ergebnisliste
    }                                                     // hinzufügen.
    str = str.substr(idx+1, string::npos);
  }
  if( ! str.empty() ){
    result.push_back(str);
  }
  return result;
}

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
    string right = line.substr(
          commentCharIdx+delimString.size(),
          string::npos
          );
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
        left.append( 1, '=');
        left.append( PADDING, ' ');
      }
    }
    left.append( right );
    cout << left << endl;
  }
}

