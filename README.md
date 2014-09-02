# wrap-comment

A small tool meant to be used with vim as a formatting filter for
comments.

Enables you to create columnized comments, like the following:

    string rtrim( string str ){                   // Wir initialisieren eine Laufvariable
      size_t i = str.size();                      // mit dem Ende des Strings und
      while( i > 0 && isspace(str[i-1])) { --i; } // zählen bis zum ersten Nichtleerzeichen
      return str.erase(i,string::npos);           // zurück. Dann löschen wir alles
    }                                             // ab diesem Index.

The longest line of source code determines the padding applied to
the commentaries.

## Usage

Assuming you have the following code and commentary:

    string rtrim( string str ){                   // Wir initialisieren eine Laufvariable mit dem Ende des Strings und zählen bis zum ersten Nichtleerzeichen zurück. Dann löschen wir alles ab diesem Index.
      size_t i = str.size();
      while( i > 0 && isspace(str[i-1])) { --i; }
      return str.erase(i,string::npos);
    }

Mark the function using visual mode and press `:`. After the prompt
of `:'<'>` type `!wrap-comment -d'//'`, which pipes the highlighted section
to the command and reads the result back in, replacing the
highlighted text with the command output.

The `-d` option takes a comment delimiter string (e.g. `#`, or as in the
example `//`).

The `-w` option can be used to set the wrap column (defaults to 80).

## Author

Sven Schober <sven.schober@uni-ulm.de>
