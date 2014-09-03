#include <unistd.h>
#include <iostream>
#include "string-utils.h"
#include <tuple>
using namespace std;

#define   FILL_CHAR      ' '

string padParentheses( string line, int padding = 1 ){
  string result;
  for( size_t i = 0; i < line.size(); i++){
    if( ')' == line[i]){
      if( ! (i - 1 > 0 &&
            ( ')' == line[i-1] ||
              '(' == line[i-1] ))){
        result.append(padding, FILL_CHAR);
      }
      result.append(1,line[i]);
    }
    else if( '(' == line[i] ){
      result.append(1,line[i]);
      if( ! (i + 1 < line.size() && 
            ( '(' == line[i+1] ||
              ')' == line[i+1] ))){
        result.append(padding, FILL_CHAR);
      }
    }
    else {
      result.append(1,line[i]);
    }
  }
  return result;
}

int main(int argc, char *argv[]){
  int padding = 1;
  int opt;
  while( (opt = getopt(argc, argv, "p:")) != -1 ){
    switch(opt){
      case 'p':
        padding = atoi( optarg );
        break;
      default:
        cerr << "Usage: " << argv[0]
          << " [-d '<comment string>']"
          << endl;
        exit(EXIT_FAILURE);
    }
  }
  string line;
  while(getline(cin, line)){
    cout << padParentheses(line,padding) << endl;
  }

}


