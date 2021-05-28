#ifndef extern_
  #define extern_ extern
#endif

//Use this to count the lines of the file for debugging statements
extern_ int Line;
//Stores the character to putback
extern_ int Putback;
extern_ FILE *Infile;
extern_ FILE *Outfile;
extern_ struct token Token;