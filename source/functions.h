
namespace functions {

thread_local system_t* system = NULL;

void cdown() { system_cdown( system ); }
void cup() { system_cup( system ); }
void cleft() { system_cleft( system ); }
void cright() { system_cright( system); }
void curs_on() { system_curs_on( system ); }
void curs_off() { system_curs_off( system ); }
void set_curs( int top, int base ) { system_set_curs( system, top, base ); }
void home() { system_home( system ); }
void inverse_on() { system_inverse_on( system ); }
void inverse_off() { system_inverse_off( system ); }
void under_on() { system_under_on( system ); }
void under_off() { system_under_off( system ); }
void shade_on() { system_shade_on( system ); }
void shade_off() { system_shade_off( system ); }
void locate( int x, int y ) { system_locate( system, x, y ); }
void paper( int color ) { system_paper( system, color ); }
void pen( int color ) { system_pen( system, color ); }
void println() { system_print( system, "" ); }
void print( char const* str ) { system_print( system, str ); }
void write( char const* str ) { system_write( system, str ); }
void centre( char const* str ) { system_centre( system, str ); }
int scrn() { return system_scrn( system ); }
void square( int wx, int wy, int border ) { system_square( system, wx, wy, border ); }
char const* tab( int n ) { return system_tab( system, n ); }
void writing( int effect ) { system_writing( system, effect ); }
int xcurs() { return system_xcurs( system ); }
int ycurs() { return system_ycurs( system ); }
int xtext( int x ) { return system_xtext( system, x ); }
int ytext( int y ) { return system_ytext( system, y ); }
int xgraphic( int x ) { return system_xgraphic( system, x ); }
int ygraphic( int y ) { return system_ygraphic( system, y ); }


char const* str( int a )
    {
    static char temp[ 256 ];
    ::snprintf( temp, 255, "%d", a ); 
    return temp; 
    }

char const* strf( float a )
    {
    static char temp[ 256 ];
    ::snprintf( temp, 255, "%f", a ); 
    return temp; 
    }

char const* strb( bool a )
    {
    static char temp[ 256 ];
    ::snprintf( temp, 255, "%s", a ? "True" : "False" ); 
    return temp; 
    }

float rnd( int a ) { (void) a; return ( (float) rand() ) / (float)( RAND_MAX + 1 ); }
int intf( float a ) { return (int) a;  }
int ints( int a ) { return a; }
int intc( char const* a ) { return atoi( a );  }
float flt( int a ) { return (float) a; }


FILE* files[ 16 ]; // TODO: Move file handles into system_t

void fopen( int n , char const* x )
    {
    if( n < 0 || n >=16 ) return;
    struct stat st;
    if( stat( x, &st ) >= 0 )
        files[ n ] = ::fopen( x, "r+" );
    else
        files[ n ] = ::fopen( x, "w+" );
    }

void frestore( int n )
    {
    if( n < 0 || n >=16 ) return;
    fseek( files[ n ], 0, SEEK_SET );
    }

char const* fread( int n )
    {
    if( n < 0 || n >=16 ) return 0;
    static char str[ 256 ];
    fgets( str, 256, files[ n ] );
    return str; 
    }

void fwrite( int n, char const* x )
    {
    if( n < 0 || n >=16 ) return;
    fprintf( files[ n ], "%s\n", x );
    fflush( files[ n ] );
    }

int abs( int a ) { return ::abs( a ); }
int sqr( int a ) { return (int) sqrtf( (float) a ); }

char const* input() { system_input_mode( system ); return ""; }
void loadsong( int song, char const* filename ) { system_loadsong( system, song, filename ); }
void playsong( int song ) { system_playsong( system, song ); }
void stopsong() { system_stopsong( system ); }
void loadpalette( char const* filename ) { system_load_palette( system, filename ); }
void loadsprite( int data_index, char const* filename ) { system_load_sprite( system, data_index, filename ); }
void sprite( int spr_index, int x, int y, int data_index ) { system_sprite( system, spr_index, x, y, data_index ); }
void say( char const* text ) { system_say( system, text ); }
void spritepos( int spr_index, int x, int y ) { system_sprite( system, spr_index, x, y ); }
void waitvbl() { system_waitvbl( system ); }
void loadsound( int data_index, char const* filename ) { system_load_sound( system, data_index, filename ); }
void playsound( int sound_index, int data_index ) { system_play_sound( system, sound_index, data_index ); }


static struct { char const* signature; vm_func_t func; } host_functions[] = 
    {
    { "Proc CDOWN()", vm_proc< cdown > },
    { "Proc CUP()", vm_proc< cup > },
    { "Proc CLEFT()", vm_proc< cleft > },
    { "Proc CRIGHT()", vm_proc< cright > },
    { "Proc CURSON()", vm_proc< curs_on > },
    { "Proc CURSOFF()", vm_proc< curs_off > },
    { "Proc SETCURS( Integer, Integer )", vm_proc< set_curs, int, int > },
    { "Proc HOME()", vm_proc< home > },
    { "Proc INVERSEON()", vm_proc< inverse_on > },
    { "Proc INVERSEOFF()", vm_proc< inverse_off > },
    { "Proc UNDERON()", vm_proc< under_on > },
    { "Proc UNDEROFF()", vm_proc< under_off > },
    { "Proc SHADEON()", vm_proc< shade_on > },
    { "Proc SHADEOFF()", vm_proc< shade_off > },
    { "Proc LOCATE( Integer, Integer )", vm_proc< locate, int, int > },
    { "Proc PAPER( Integer )", vm_proc< paper, int > },
    { "Proc PEN( Integer )", vm_proc< pen, int > },
    { "Proc PRINT()", vm_proc< println > },
    { "Proc PRINT( String )", vm_proc< print, char const* > },
    { "Proc WRITE( String )", vm_proc< write, char const* > },
    { "Proc CENTRE( String )", vm_proc< centre, char const* > },
    { "Func Integer SCRN()", vm_func< int, scrn > },
    { "Proc SQUARE( Integer, Integer, Integer )", vm_proc< square, int, int, int > },
    { "Func String TAB( Integer )", vm_func< char const*, tab, int > },
    { "Proc WRITING( Integer )", vm_proc< writing, int > },
    { "Func Integer XCURS()", vm_func< int, xcurs > },
    { "Func Integer YCURS()", vm_func< int, ycurs > },
    { "Func Integer XTEXT( Integer )", vm_func< int, xtext, int > },
    { "Func Integer YTEXT( Integer )", vm_func< int, ytext, int > },
    { "Func Integer XGRAPHIC( Integer )", vm_func< int, xgraphic, int > },
    { "Func Integer YGRAPHIC( Integer )", vm_func< int, ygraphic, int > },
    
    { "Func String STR( Integer )", vm_func< char const*, str, int > },
    { "Func String STR( Real )", vm_func< char const*, strf, float > },
    { "Func String STR( Bool )", vm_func< char const*, strb, bool > },
    { "Func Real RND( Integer )", vm_func< float, rnd, float > },
    { "Func Integer INT( Real )", vm_func< int, intf, float > },
    { "Func Integer INT( Integer )", vm_func< int, ints, int > },
    { "Func Integer INT( String )", vm_func< int, intc, char const* > },
    { "Func Real FLT( Integer )", vm_func< float, flt, int > },
    { "Proc FOPEN( Integer, String )", vm_proc< fopen, int, char const* > },
    { "Proc FRESTORE( Integer )", vm_proc< frestore, int > },
    { "Func String FREAD( Integer )", vm_func< char const*, fread, int> },
    { "Proc FWRITE( Integer, String )", vm_proc< fwrite, int, char const* > },
    { "Func String INPUT()", vm_func< char const*, input > },
    { "Func Integer ABS( Integer )", vm_func< int, abs, int > },
    { "Func Integer SQR( Integer )", vm_func< int, sqr, int > },
    { "Proc LOADSONG( Integer, String )", vm_proc< loadsong, int, char const* > },
    { "Proc PLAYSONG( Integer )", vm_proc< playsong, int > },
    { "Proc STOPSONG()", vm_proc< stopsong > },
    { "Proc LOADPALETTE( String )", vm_proc< loadpalette, char const* > },
    { "Proc LOADSPRITE( Integer, String )", vm_proc< loadsprite, int, char const* > },
    { "Proc SPRITE( Integer, Integer, Integer, Integer )", vm_proc< sprite, int, int, int, int > },
    { "Proc SPRITE( Integer, Integer, Integer )", vm_proc< spritepos, int, int, int > },
    { "Proc WAITVBL()", vm_proc< waitvbl > },
    { "Proc SAY( String )", vm_proc< say, char const* > },
    { "Proc LOADSOUND( Integer, String )", vm_proc< loadsound, int, char const* > },
    { "Proc PLAYSOUND( Integer, Integer )", vm_proc< playsound, int, int > },
    };

} /* namespace functions */