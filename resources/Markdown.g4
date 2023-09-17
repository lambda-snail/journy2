grammar Markdown;

markdown        : EOL* block*;

block           : (code_stream_blk | paragraph | header) (EOL+ | EOF); // code_stream before paragraph

raw_stream      : (WORD BLANK*)+ ;
italics_stream  : ITALICS_ENVELOPE BLANK* w_stream ITALICS_ENVELOPE BLANK*;
bold_stream     : BOLD_ENVELOPE BLANK* w_stream BOLD_ENVELOPE BLANK*;
code_stream_inl : CODE_ENVELOPE w_stream CODE_ENVELOPE ;

code_stream_blk : CODE_ENVELOPE w_stream CODE_ENVELOPE ; // Re-label

w_stream        : (italics_stream | bold_stream | code_stream_inl | WORD BLANK*)+? | WORD;

header          : HEADER_START+ BLANK* raw_stream;
paragraph       : w_stream ;

//fragment ALNUM          : [a-zA-Z0-9] ;
fragment ALNUM          : ~[`_*#\n\r\f\t ] | (ESCAPE_CHAR '`') ; // 'alnum' here means any char not white space or reserved by markdown
ESCAPE_CHAR             : '\\' ;
HEADER_START            : '#' ;

BLANK                   : (' ' | '\t') -> skip ;
EOL                     : ('\n' | '\r\f');
WHITESPACE              : EOL | BLANK ;

WORD                    : (ALNUM)+ ;
BOLD_ENVELOPE           : '*' ;
ITALICS_ENVELOPE        : '_' ;
CODE_ENVELOPE           : '`' ;