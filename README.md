# alignment-tools

A small set of tools working on plain-text meant to be used with vim as formatting filters.

All the tools read on `STDIN` and emit the mended text on `STDOUT`.

In general, you would use them in vim by highlighting some text in visual mode and then piping the marked text through theses tools by typing `:` (which yields the prompt `:'<'>`) followed by `!<toolname>`.

## align-on

Enables you to align on a delimiting character. Suppose you have code riddled with assignments:

    my $payload = "Hallo Welt!";
    my $encryptor = Uki::Common::Encryptor->new( publicKeyFile => "pub.key");
    my $indecipherableText = $encryptor->encrypt( $payload );
    my $decryptor = Uki::Common::Decryptor->new( privateKey => "priv.key" );

It might help to improve clarity by aligning all theses assignments on the rightmost `=` character:


    my $payload            = "Hallo Welt!";
    my $encryptor          = Uki::Common::Encryptor->new( publicKeyFile => "pub.key");
    my $indecipherableText = $encryptor->encrypt( $payload );
    my $decryptor          = Uki::Common::Decryptor->new( privateKey => "priv.key" );

### Usage

`align-on` takes the paramater `-d '<delimiter string>'`, which enables you to change the delimiting string. It defaults to `=`.


## wrap-comment

Enables you to create columnized comments. Assuming you have the following code and commentary:

    string rtrim( string str ){                   // Wir initialisieren eine Laufvariable mit dem Ende des Strings und zählen bis zum ersten Nichtleerzeichen zurück. Dann löschen wir alles ab diesem Index.
      size_t i = str.size();
      while( i > 0 && isspace(str[i-1])) { --i; }
      return str.erase(i,string::npos);
    }

`wrap-comment`'s effect would be like the following:

    string rtrim( string str ){                   // Wir initialisieren eine Laufvariable
      size_t i = str.size();                      // mit dem Ende des Strings und
      while( i > 0 && isspace(str[i-1])) { --i; } // zählen bis zum ersten Nichtleerzeichen
      return str.erase(i,string::npos);           // zurück. Dann löschen wir alles
    }                                             // ab diesem Index.

The longest line of source code determines the padding applied to
the commentaries.

### Usage

The `-d` option takes a comment delimiter string, which defaults to `#`.  In the example `-d '//'` was used.

The `-w` option can be used to set the wrap column (defaults to 80).

## Building

    make

## Installing

Adapt the path in the Makefile to your needs and call

    make install


## Author

Sven Schober <sven.schober@uni-ulm.de>
