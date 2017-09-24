    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ncurses.h>


#ifdef _WIN32
/// WIN
#include <windows.h>
int termsize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 0;
    printf("OS: Windows \n" );
    printf("columns: %d\n", columns);
    printf("rows: %d\n", rows);
}
#else
/// LINUX
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
int termsize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("OS: Linux \n" );
    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
}
#endif





////////////////////////////////////////////////////////////////////
char *strrlf(char *str) 
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if (str[i] != '\n' && str[i] != '\n') 
        ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}
////////////////////////////////////////////////////////////////////
char *strcut( char *str , int myposstart, int myposend )
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}








int rows, cols;


///////////////////////////////////////////////////////////
void drawinput( char *mytext )
{
     getmaxyx( stdscr, rows, cols);
     int fooj; 

     for ( fooj = 0 ; fooj <= cols-1;  fooj++)
       mvaddch( rows-3, fooj , ACS_HLINE );

     mvprintw( rows-2, 0, "I:> %s" , strrlf( mytext ) );
}





///////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{
   printf("Hello to ninputbox demo !\n");
   termsize();

   char cwd[PATH_MAX];
   initscr();			
   curs_set( 0 );
   int gameover; 
   gameover = 0;
   char ch ; 
   char charo[PATH_MAX]; int foo ; 
   char strmsg[PATH_MAX];
   strncpy( strmsg, "", PATH_MAX );

   getmaxyx( stdscr, rows, cols);
   while ( gameover == 0)
   {
           getmaxyx( stdscr, rows, cols);

           erase();
           drawinput( strmsg );
	   refresh(); // <- not necessary
           ch = getch();

		  if ( ch == 127  ) 
		  {
                           //foo = snprintf( charo, PATH_MAX , "%s%c",  strmsg, ch );
			   strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );
		  }

	          else if (
			(( ch >= 'a' ) && ( ch <= 'z' ) ) 
		        || (( ch >= 'A' ) && ( ch <= 'Z' ) ) 
		        || (( ch >= '1' ) && ( ch <= '9' ) ) 
		        || (( ch == '0' ) ) 
		        || (( ch == '~' ) ) 
		        || (( ch == '!' ) ) 
		        || (( ch == '&' ) ) 
		        || (( ch == '=' ) ) 
		        || (( ch == ':' ) ) 
		        || (( ch == ';' ) ) 
		        || (( ch == '<' ) ) 
		        || (( ch == '>' ) ) 
		        || (( ch == ' ' ) ) 
		        || (( ch == '|' ) ) 
		        || (( ch == '#' ) ) 
		        || (( ch == '?' ) ) 
		        || (( ch == '+' ) ) 
		        || (( ch == '/' ) ) 
		        || (( ch == '\\' ) ) 
		        || (( ch == '.' ) ) 
		        || (( ch == '$' ) ) 
		        || (( ch == '%' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '{' ) ) 
		        || (( ch == '}' ) ) 
		        || (( ch == '(' ) ) 
		        || (( ch == ')' ) ) 
		        || (( ch == ']' ) ) 
		        || (( ch == '[' ) ) 
		        || (( ch == '*' ) ) 
		        || (( ch == '"' ) ) 
		        || (( ch == '@' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '_' ) ) 
		        || (( ch == '^' ) ) 
		        || (( ch == '\'' ) ) 
	             ) 
		  {
                           foo = snprintf( charo, PATH_MAX , "%s%c",  strmsg, ch );
			   strncpy( strmsg,  charo ,  PATH_MAX );
		  }
		  
		  else if ( ch == 10 ) 
		  {
			   gameover = 1 ; 
		  }


   }

   curs_set( 1 );
   endwin();		

   printf( "%s\n" , strmsg );

   return 0;
}



