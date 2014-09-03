#include <string>
#include <list>

using namespace std;

string rtrim( string str ){                   // Wir initialisieren eine Laufvariable
  size_t i = str.size();                      // mit dem Ende des Strings und zählen
  while( i > 0 && isspace(str[i-1])) { --i; } // bis zum ersten Nichtleerzeichen
  return str.erase(i,string::npos);           // zurück. Dann löschen wir alles
}                                             // ab diesem Index.
string ltrim( string str ){
  size_t i = 0;
  while( i < str.size() && isspace(str[i]) ){ ++i; }
  return str.erase(0,i);
}
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

