grammar MyGrammar;

// E ::= ++S E1 | S E2 | I
// E1 ::= ε | = E
// E2 ::= ε | = E | ++

ee: PLUSPLUS STR e1 | STR e2 | INT;
e1: EQUAL ee |;
e2: EQUAL ee | PLUSPLUS |;

WHITESPACE: [' '\r\t\n] -> skip;
STR: [a-zA-Z_][a-zA-Z0-9_]*;
PLUSPLUS: '++';
EQUAL: '=';
INT: [0-9];

//a=b=++c
