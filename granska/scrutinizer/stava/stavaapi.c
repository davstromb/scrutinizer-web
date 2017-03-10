/* R�ttstavningsprogram. Version 2.61  2004-10-31
   Copyright (C) 1990-2004
   Joachim Hollman och Viggo Kann
   joachim@algoritmica.se viggo@nada.kth.se
*/
#define VERSION "Stava version 2.61"
/* #define DEBUG testversion med debugm�jligheter (v�ljaren -D) */
/* #define MORFANALYS */ /* Morfologianalys med sammans�ttningsanalys */
/* #define ENGELSKA */ /* Engelsk stavningskontroll */
/* #define STATISTIK */ /* Skriv ut hashningsstatistik */
/* #define TAGGSTAVA */ /* Ordklasstagga orden */
/* #define NE */ /* NE-s�kning */
/* #define KOLLASAMMANSATT */ /* Ge statistik f�r (tv�leds)sammans�ttningar */

#define SVENSKA /* Svensk stavningskontroll */
#define RATTSTAVA /* V�ljaren -r som ger r�ttstavningsf�rslag kan anv�ndas */
#define CHOOSEBESTCOMPOUNDING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define wwwstatic static

#include "stava.h"
#include "rattstava.h"
#include "suffix.h"
#include "stavaconstants.h"

#include "stavaapi.h"

static float compfactor = 3.0; /* Skalfaktor vid sammans�ttningsanalys */

static const char *libpath; /* path to library directory, should end with / */
static unsigned char HUGEVAR ELtable[ELSIZE];
static unsigned char HUGEVAR FLtable[FLSIZE];
static unsigned char HUGEVAR ILtable[ILSIZE];
static unsigned char HUGEVAR ULtable[ULSIZE];
static unsigned char HUGEVAR XLtable[XLSIZE];
static char XLfilename[FILENAMELENGTH];
static char fyrgramfilename[FILENAMELENGTH];
static char ELfilename[FILENAMELENGTH];
static char FLfilename[FILENAMELENGTH];
static char ILfilename[FILENAMELENGTH];
static char ULfilename[FILENAMELENGTH];
static char SLfilename[FILENAMELENGTH];
char isLowerCase[256]; /* �r x en liten bokstav? */
char isUpperCase[256]; /* �r x en stor bokstav? */
char isVowel[256]; /* �r x en versal? */
char isDelim[256]; /* �r x en icke-bokstav? */
unsigned char toLowerCase[256]; /* omvandla stor till liten bokstav */
unsigned char toUpperCase[256]; /* omvandla stor till liten bokstav */
unsigned char *lowerCaseLetters; /* alla sm� bokst�ver */
unsigned char *upperCaseLetters; /* alla stora bokst�ver */
unsigned char *delimiters; /* alla icke-bokst�ver */
int xHtml = 0;
static int bindestreck;
static FILE *ordf;
static FILE *ELfp, *FLfp, *ILfp, *ULfp, *xELfp;
int xAndelser = 1, xForkortningar = 0, xNamn = 0, xDatatermer = 0;
int xTex = 0;
int xSammansatta = 1, xKort = 0;
int xTillatSIFogar = 1; /* Till�t s i vissa fogar, t ex FL FL s EL */
int xTillatSIAllaFogar = 0; /* Till�t t ex FL s FL EL */
int xAcceptCapitalWords = 1; /* Till�t ord med bara versaler */
int xDebug = 0;
int xPrintError = 1; /* Skriv ut felmeddelanden p� stderr */
char stavaerrorbuf[400]; /* buffer for last error message */

#define MAXNOOFCOMPOUNDS 20

int compoundSearch = 0; /* 1 under s�kning efter sammans�ttningar */

static char breakpossibilities[MAXNOOFCOMPOUNDS][LANGD];
static int breakposparts[MAXNOOFCOMPOUNDS];
static float breakposlen[MAXNOOFCOMPOUNDS];
static int noofcompounds = 0;
int xIntePetig = 1;
int xRattstavningsforslag = 0, xGenerateCompounds = 1, xMaxOneError = 1;
static char *gBreaks;

static int angettTeckenkod = 0; /* Talar om ifall teckenkod explicit angetts */
int x8bitar = ISOCODE; /* Anger teckenkod (ISOCODE, MACCODE, DOSCODE, 0) */
static unsigned char *bokstavsTabell;    /* �vers�ttning kod -> intern */
wwwstatic unsigned char *tillISOTabell;     /* �vers�ttning kod -> ISO Latin-1 */

#define get(f) getc(f)
#define unget(c,f) ungetc(c,f)
#define ENDOFFILE EOF

/* PrintErrorWithText prints an error containing a text argument. format is a 
  formating string containing the string %s */
void PrintErrorWithText(const char *format, const char *text)
{
  if (strlen(format) + strlen(text) >= 300) {
    if (strlen(format) >= 300) sprintf(stavaerrorbuf, "Ett fel har uppst�tt.\n");
    else sprintf(stavaerrorbuf, format, "<f�r l�ngt>");
  } else sprintf(stavaerrorbuf, format, text);
  if (xPrintError) fprintf(stderr, "%s", stavaerrorbuf);
}

/* WriteISO skriver ut en ASCII-textstr�ng �versatt till ISO Latin-1 */
void WriteISO(const unsigned char *s)
{ int ch;
  while (*s) {
    ch = intern_ISO[*s++];
    putchar(ch);
  }
}

/* sWriteISO skriver ut en ASCII-textstr�ng �versatt till ISO Latin-1 p� str�ng */
void sWriteISO(unsigned char *res, const unsigned char *s)
{ int ch;
  while (*s) {
    ch = intern_ISO[*s++];
    *res++ = ch;
  }
  *res = '\0';
}

/* StringWriteCompound skriver word med ordbrytningsmarkeringar i res */
/* breaks[0] f�r inte vara en ordbrytningsmarkering */
static void StringWriteCompound(unsigned char *res, const unsigned char *word, 
			  char *breaks)
{ 
  while (*word) {
    if (*breaks == 's') { *res++ = '|'; *res++ = 's'; *res++ = '|'; }
    else {
      if (*breaks == '|' && word[-1] != '-') *res++ = '|';
      *res++ = intern_ISO[*word];
    }
    if (*breaks == '<') {
      *res++ = '|';
      *res++ = intern_ISO[*word];
    }
    word++;
    breaks++;
  }
  *res = '\0';
}

/* WriteCompound skriver ut ett ord med ordbrytningsmarkeringar */
static void WriteCompound(const unsigned char *word, char *breaks)
{ 
  while (*word) {
    if (*breaks == 's') printf("|s|");
    else {
      if (*breaks == '|') putchar('|');
      putchar(intern_ISO[*word]);
    }
    if (*breaks == '<') {
      putchar('|');
      putchar(intern_ISO[*word]);
    }
    word++;
    breaks++;
  }
}

typedef unsigned long int ub4;   /* unsigned 4-byte quantities */

#define hashsize(n) ((ub4)1<<(n))
#define hashmask(n) (hashsize(n)-1)


/*
--------------------------------------------------------------------
mix -- mix 3 32-bit values reversibly.
For every delta with one or two bit set, and the deltas of all three
  high bits or all three low bits, whether the original value of a,b,c
  is almost all zero or is uniformly distributed,
* If mix() is run forward or backward, at least 32 bits in a,b,c
  have at least 1/4 probability of changing.
* If mix() is run forward, every bit of c will change between 1/3 and
  2/3 of the time.  (Well, 22/100 and 78/100 for some 2-bit deltas.)
mix() takes 36 machine instructions, but only 18 cycles on a superscalar
  machine (like a Pentium or a Sparc).  No faster mixer seems to work,
  that's the result of my brute-force search.  There were about 2^^68
  hashes to choose from.  I only tested about a billion of those.
--------------------------------------------------------------------
*/
#define mix(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

/*
--------------------------------------------------------------------
hash() -- hash a variable-length key into a 32-bit value
  k     : the key (the unaligned variable-length array of bytes)
  len   : the length of the key, counting by bytes
  level : can be any 4-byte value
Returns a 32-bit value.  Every bit of the key affects every bit of
the return value.  Every 1-bit and 2-bit delta achieves avalanche.
About 36+6len instructions.

The best hash table sizes are powers of 2.  There is no need to do
mod a prime (mod is sooo slow!).  If you need less than 32 bits,
use a bitmask.  For example, if you need only 10 bits, do
  h = (h & hashmask(10));
In which case, the hash table should have hashsize(10) elements.

If you are hashing n strings (ub1 **)k, do it like this:
  for (i=0, h=0; i<n; ++i) h = hash( k[i], len[i], h);

By Bob Jenkins, 1996.  74512.261@compuserve.com.  You may use this
code any way you wish, private, educational, or commercial.  It's free.

See http://ourworld.compuserve.com/homepages/bob_jenkins/evahash.htm
Use for hash table lookup, or anything where one collision in 2^32 is
acceptable.  Do NOT use for cryptographic purposes.
--------------------------------------------------------------------
*/

INLINE int InEL(const unsigned char *k,        /* the key */
		int length)   /* the length of the key */
{  register int len = length;
   register ub4 a,b,c;
   register ub4 h, olda, oldb;
   register int i = 0;

   /* Set up the internal state */
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = HASHINITVAL;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   olda = a; oldb = b;
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   h = c & hashmask(ELBITS);
   if (!(ELtable[h >> 3] & (1 << (int)(h & 7)))) {
      return 0;
   }
   for (i = 1; i < ELNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     h = c & hashmask(ELBITS);
     if (!(ELtable[h >> 3] & (1 << (int)(h & 7)))) {
        return 0;
     }
   }
   return 1;
}

/* InILorELbutnotUL kollar om ordet k med l�ngden length finns i
ordlistorna IL eller EL men inte i UL. I s� fall returneras 1.
Om ordet finns i UL returneras -1, annars returneras 0. */
INLINE int InILorELbutnotUL(const unsigned char *k,        /* the key */
		    int length)   /* the length of the key */
{  register int len = length;
   register ub4 a,b,c;
   register ub4 h, olda, oldb;
   ub4 ccache[ELNOOFHASH];
   register int i=0;
   register int j;
   int res = 0;

   /* Set up the internal state */
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = HASHINITVAL;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   olda = a; oldb = b;
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   ccache[0] = c;
   h = c & hashmask(ILBITS);
   if (!(ILtable[h >> 3] & (1 << (int)(h & 7)))) {
      goto checkEL;
   }
   for (i = 1; i < ILNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     ccache[i] = c;
     h = c & hashmask(ILBITS);
     if (!(ILtable[h >> 3] & (1 << (int)(h & 7)))) {
        goto checkEL;
     }
   }
   return 1;
 checkEL:
#if (ELNOOFHASH < ILNOOFHASH)
   if (i >= ELNOOFHASH) i = ELNOOFHASH - 1;
#endif
   for (j = 0; j <= i; j++) {
     h = ccache[j] & hashmask(ELBITS);
     if (!(ELtable[h >> 3] & (1 << (int)(h & 7)))) {
       goto checkUL;
     }     
   }
   i++;
   for (; i < ELNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     ccache[i] = c;
     h = c & hashmask(ELBITS);
     if (!(ELtable[h >> 3] & (1 << (int)(h & 7)))) goto checkUL;
   }
   res = 1;
 checkUL:
#if (ULNOOFHASH < ELNOOFHASH)
   if (i >= ULNOOFHASH) i = ULNOOFHASH - 1;
#endif
   for (j = 0; j <= i; j++) {
     h = ccache[j] & hashmask(ULBITS);
     if (!(ULtable[h >> 3] & (1 << (int)(h & 7)))) {
       return res;
     }     
   }
   i++;
   for (; i < ULNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     h = c & hashmask(ULBITS);
     if (!(ULtable[h >> 3] & (1 << (int)(h & 7)))) return res;
   }
   return -1; /* ordet med i undantagsordlistan */
}

INLINE int InFL(const unsigned char *k,        /* the key */
		int length)   /* the length of the key */
{  register int len = length;
   register ub4 a,b,c;
   register ub4 h, olda, oldb;
   register int i;

   /* Set up the internal state */
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = HASHINITVAL;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   olda = a; oldb = b;
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   h = c & hashmask(FLBITS);
   if (!(FLtable[h >> 3] & (1 << (int)(h & 7)))) {
      return 0;
   }
   for (i = 1; i < FLNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     h = c & hashmask(FLBITS);
     if (!(FLtable[h >> 3] & (1 << (int)(h & 7)))) {
        return 0;
     }
   }
   return 1;
}

INLINE int InIL(const unsigned char *k,        /* the key */
		int length)   /* the length of the key */
{  register int len = length;
   register ub4 a,b,c;
   register ub4 h, olda, oldb;
   register int i;

   /* Set up the internal state */
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = HASHINITVAL;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   olda = a; oldb = b;
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   h = c & hashmask(ILBITS);
   if (!(ILtable[h >> 3] & (1 << (int)(h & 7)))) return 0;
   for (i = 1; i < ILNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     h = c & hashmask(ILBITS);
     if (!(ILtable[h >> 3] & (1 << (int)(h & 7)))) return 0;
   }
   return 1;
}

INLINE int InUL(const unsigned char *k,        /* the key */
		int length)   /* the length of the key */
{  register int len = length;
   register ub4 a,b,c;
   register ub4 h, olda, oldb;
   register int i;

   /* Set up the internal state */
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = HASHINITVAL;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   olda = a; oldb = b;
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   h = c & hashmask(ULBITS);
   if (!(ULtable[h >> 3] & (1 << (int)(h & 7)))) return 0;
   for (i = 1; i < ULNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     h = c & hashmask(ULBITS);
     if (!(ULtable[h >> 3] & (1 << (int)(h & 7)))) return 0;
   }
   return 1;
}

INLINE int InXL(const unsigned char *k,        /* the key */
		int length)   /* the length of the key */
{  register int len = length;
   register ub4 a,b,c;
   register ub4 h, olda, oldb;
   register int i;

   /* Set up the internal state */
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = HASHINITVAL;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   olda = a; oldb = b;
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   h = c & hashmask(XLBITS);
   if (!(XLtable[h >> 3] & (1 << (int)(h & 7)))) return 0;
   for (i = 1; i < XLNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     h = c & hashmask(XLBITS);
     if (!(XLtable[h >> 3] & (1 << (int)(h & 7)))) return 0;
   }
   return 1;
}


static INLINE void StoreInEL(const unsigned char *k)
{
   register ub4 a,b,c;
   register ub4 h, olda, oldb;
   register int i;
   register int len = strlen((char *)k), length = len;

   /* Set up the internal state */
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = HASHINITVAL;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   olda = a; oldb = b;
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   h = c & hashmask(ELBITS);
   ELtable[h >> 3] |= (1 << (int)(h & 7));
   for (i = 1; i < ELNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     h = c & hashmask(ELBITS);
     ELtable[h >> 3] |= (1 << (int)(h & 7));
   }
}

static INLINE void StoreInFL(const unsigned char *k)
{
   register ub4 a,b,c;
   register ub4 h, olda, oldb;
   register int i;
   register int len = strlen((char *)k), length = len;

   /* Set up the internal state */
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = HASHINITVAL;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   olda = a; oldb = b;
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   h = c & hashmask(FLBITS);
   FLtable[h >> 3] |= (1 << (int)(h & 7));
   for (i = 1; i < FLNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     h = c & hashmask(FLBITS);
     FLtable[h >> 3] |= (1 << (int)(h & 7));
   }
}

static INLINE void StoreInIL(const unsigned char *k)
{
   register ub4 a,b,c;
   register ub4 h, olda, oldb;
   register int i;
   register int len = strlen((char *)k), length = len;

   /* Set up the internal state */
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = HASHINITVAL;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   olda = a; oldb = b;
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   h = c & hashmask(ILBITS);
   ILtable[h >> 3] |= (1 << (int)(h & 7));
   for (i = 1; i < ILNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     h = c & hashmask(ILBITS);
     ILtable[h >> 3] |= (1 << (int)(h & 7));
   }
}

static INLINE void StoreInUL(const unsigned char *k)
{
   register ub4 a,b,c;
   register ub4 h, olda, oldb;
   register int i;
   register int len = strlen((char *)k), length = len;

   /* Set up the internal state */
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = HASHINITVAL;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   olda = a; oldb = b;
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   h = c & hashmask(ULBITS);
   ULtable[h >> 3] |= (1 << (int)(h & 7));
   for (i = 1; i < ULNOOFHASH; i++) {
     a = olda; b = oldb;
     mix(a,b,c);
     h = c & hashmask(ULBITS);
     ULtable[h >> 3] |= (1 << (int)(h & 7));
   }
}

static void InitieraBokstavsTabeller(void)
{ int i;
  int low = 0, upp = 0, del = 0;
  switch (x8bitar) {
   case 0:
    bokstavsTabell = ASCII_intern;
    tillISOTabell = intern_ISO;
    if (xTex) bokstavsTabell['/'] = '/';
    break;
   case MACCODE:
    bokstavsTabell = MAC_intern;
    tillISOTabell = MAC_ISO;
    if (xTex) bokstavsTabell['\\'] = '/';
    break;
   case DOSCODE:
    bokstavsTabell = DOS_intern;
    tillISOTabell = DOS_ISO;
    if (xTex) bokstavsTabell['\\'] = '/';
    break;
   case ISOCODE:
   default:
    bokstavsTabell = ISO_intern;
    tillISOTabell = ISO_ISO;
    if (xTex) bokstavsTabell['\\'] = '/';
    break;
  }
  ISO_intern[(unsigned char) ' '] = 0;
  /* fyll i 0-f�lt med standardv�rde i bokstavstabellen till ISO */
  for (i = 0; i < 256; i++) {
    if (tillISOTabell[i] == 0) tillISOTabell[i] = i;
    if (intern_ISO[i] == 0) intern_ISO[i] = i;
    isLowerCase[i] = isUpperCase[i] = isVowel[i] = isDelim[i] = 0;
    toLowerCase[i] = toUpperCase[i] = 0;
  }
  for (i = 0; i < 256; i++) {
    if (intern_p[i]) {
      if (intern_p[i] >= 'a') isLowerCase[i] = 1;
      else if (intern_p[i] >= 'A') isUpperCase[i] = 1;
      if (intern_p[i] == DELIMP) { 
	isDelim[i] = 1;
	del++;
      }
    }
  }
  for (i = 0; i < 256; i++) {
    if (isLowerCase[i]) {
      if (!isConsonant[i]) isVowel[i] = 1;
      toUpperCase[i] = i - 32;
      toLowerCase[i] = i;
      low++;
    } else if (isUpperCase[i]) {
      if (!isConsonant[i]) isVowel[i] = 1;
      toUpperCase[i] = i;
      toLowerCase[i] = i + 32;
      upp++;
    }
  }
  lowerCaseLetters = malloc(low + 1);
  upperCaseLetters = malloc(upp + 1);
  delimiters = malloc(del + 1);
  low = upp = del = 0;
  for (i = 0; i < 256; i++) {
    if (isLowerCase[i])
      lowerCaseLetters[low++] = i;
    else if (isUpperCase[i])
      upperCaseLetters[upp++] = i;
    else if (isDelim[i]) 
      delimiters[del++] = i;
  }
  lowerCaseLetters[low] = '\0';
  upperCaseLetters[upp] = '\0';
  delimiters[del] = '\0';
}

static INLINE int SkippaRestenAvOrdet(void)
{ int t;
  while ((t = get(ordf)) != ENDOFFILE) {
    if (bokstavsTabell[t]) continue;
    if (t == '-') continue;
    if (xTex && t == '/') {
      t = get(ordf);
      if (t == '\'' || t == '`' || t == '^' || t == '"' || t == '=' || 
	  t == '.' || t == '~') continue;
    }
    return 1;
  }
  return 0;
}

static INLINE int SkippaRestenAvEpostadressen(void)
{ int t;
  while ((t = get(ordf)) != ENDOFFILE) {
    if (bokstavsTabell[t]) continue;
    if (isdigit(t) || t == '-' || t == '.') continue;
    return 1;
  }
  return 0;
}

/* SkippaInledandeVariabel hoppar �ver blanka, ev citattecken och ev
   variabelnamn som inleds med dollartecken */
static void SkippaInledandeVariabel(void)
{ int u;
  u = get(ordf);
  while (u == ' ' || u == 10) u = get(ordf);
  if (u == '"') u = get(ordf);
  if (u == '$') {
    u = get(ordf);
    while (u >= 'A') u = get(ordf);
    return;
  }
  unget(u, ordf);
}

/* SkippaTill skippar MHTML-kommandon fram till angivet tecken */
static int SkippaTill(int c)
{ int u;
  u = get(ordf);
  if (c == ']' && u == 't') {
    u = get(ordf);
    if (u == 'y' &&
        (u = get(ordf)) == 'p') {
      u = get(ordf);
      while (u == ' ' || u == 10) u = get(ordf);
      if (u == '"') SkippaTill('"');
      else SkippaTill(' ');
      SkippaInledandeVariabel();
      return 0;
    } else if (u == 'e' &&
               (u = get(ordf)) == 'x' &&
               (u = get(ordf)) == 't') {
      SkippaInledandeVariabel();
      return 0;
    }
  }
  while (1) {
    if (u == ENDOFFILE || u == '\n') return 0;
    else if (u == '\\' && get(ordf) == ENDOFFILE) return 0;
    else if (u == c) return 1;
    else if (u == '[') if (SkippaTill(']') == 0) return 0;
    u = get(ordf);
  }
}

static INLINE int CheckLatin1Entity(void)
{ unsigned char entity[LANGD+1];
  int u, i = 0;
  int lo, hi, m;
  while (1) {
    u = get(ordf);
    if (u == ENDOFFILE) return ENDOFFILE;
    if (u == '\n' || u == ';' || u == ' ') break;
    if (i < LANGD) entity[i++] = u;
  }
  entity[i] = '\0';
  if (isdigit(*entity)) {
    sscanf((char *) entity, "%d", &u);
    return u;
  }
  lo = 0; hi = NOOFENTITIES - 1;
  while (lo < hi) {
    m = (hi + lo) / 2;
    i = strcmp((char *)latin1Entities[m].entity, (char *)entity);
    if (i == 0) return latin1Entities[m].letter;
    if (i < 0) lo = m + 1; else hi = m - 1;
  }
  if (lo == hi && strcmp((char *)latin1Entities[lo].entity, (char *)entity) == 0)
    return latin1Entities[lo].letter;
  return 0;
}

/* TagOrd reads the next word from the file ordf and stores it in urord.
   The word in Stava's internal format is stored in s.
   0 is returned if there is no more word (EOF), and 1 otherwise. */
static
int TagOrd(unsigned char *s, unsigned char *urord)
{ int t, u, i, nyrad;
 start:
  do {
    i = 0;
    bindestreck = 0;
    do {
      u = get(ordf);
      if (u == ENDOFFILE) return 0;
      if (xHtml) {
	if (u == '&') {
	  u = CheckLatin1Entity();
	  if (u == ENDOFFILE) return 0;
	} else
	  if (u == '<') {
	    while (1) {
	      u = get(ordf);
	      if (u == ENDOFFILE) return 0;
	      if (u == '\n' || u == '>') break;
	    }
	  } else
	    if (u == '[' && x8bitar) SkippaTill(']');
      }
    } while (!(t = bokstavsTabell[u]) || t == '-');

    while (1) {
      if (t == '-' || (xTex && t == '/')) {
	/* I Tex behandlas /- precis som bara - */
	if (t == '/') if ((u = get(ordf)) != '-') {
	  if (u == '\'' || u == '`' || u == '^' || u == '~' || u == '"') {
	    unsigned char uprev = u;
	    u = get(ordf);
	    if (u != ENDOFFILE) {
	      if (uprev == '\'') {
		if (u == 'e') {
		  t = ISO_intern[(unsigned char)(u = '�')]; continue;
		} else if (u == 'E') {
		  t = ISO_intern[(unsigned char)(u = '�')]; continue;
		}
	      } else if (uprev == '"') {
		unsigned char newc;
		switch (u) {
		case 'a': newc = '�'; break;
		case 'o': newc = '�'; break;
		case 'A': newc = '�'; break;
		case 'O': newc = '�'; break;
		default: goto skipControl;
		}
		u = newc;
		t = ISO_intern[newc]; 
		continue;
	      }
	      skipControl:
	      if ((t = bokstavsTabell[u])) continue;
            }
	  }
	  unget(u, ordf);
	  goto ordSlut;
	}
	u = get(ordf);
	if (u == ' ' || u == '\t' || u == '\n') {
	  nyrad = (u == '\n');
	  while (1) {
	    if ((u = get(ordf)) == ENDOFFILE) goto ordSlut;
	    if (u == '\n') nyrad = 1;
	    else if (u != ' ' && u != '\t') break;
	  }
	  if (!nyrad) {
	    if (i > 0) { 
	      s[i] = urord[i] = '-';
	      i++;
	      bindestreck++;
	    }
	    unget(u, ordf);
	    goto ordSlut;
	  }
	}
	if (u == '&' && xHtml) {
	  u = CheckLatin1Entity();
	  if (u == ENDOFFILE) goto ordSlut;
	}
	if ((t = bokstavsTabell[u])) {
	  if (t == '-' || (xTex && t == '/')) goto ordSlut;
	  if (i > 0) { 
	    s[i] = urord[i] = '-';
	    if (++i >= LANGD) {
	      if (!SkippaRestenAvOrdet()) return 0;
	      goto start;
	    }
	    bindestreck++;
	  }
	} else goto ordSlut;
      }
      s[i] = t;
      urord[i] = u;
      if (++i >= LANGD) {
	if (!SkippaRestenAvOrdet()) return 0;
	goto start;
      }
      if ((u = get(ordf)) == ENDOFFILE) break;
      if (u == '&' && xHtml) {
	u = CheckLatin1Entity();
	if (u == ENDOFFILE) goto ordSlut;
      }
      if (!(t = bokstavsTabell[u])) break;
    }
    if (xHtml) {
      if (u == '<' || (u == '[' && x8bitar)) unget(u, ordf);
    }
   ordSlut: ;
  } while (i < ORDMIN);
  if (u == '@') {
    if (!SkippaRestenAvEpostadressen()) return 0;
    goto start;
  }
  s[i] = urord[i] = '\0';
  return 1;
}

/* TagOrdStr reads the next word from the string str and stores it in urord.
   NULL is returned if there is no more word, and a pointer to the next
   unused character otherwise. */
static unsigned char *TagOrdStr(unsigned char *str, unsigned char *urord)
{ int t, u, i, nyrad;
 start:
  do {
    i = 0;
    bindestreck = 0;
    do {
      u = *str++;
      if (u == '\0') return NULL;
      if (xHtml) {
	if (u == '&') {
	  u = CheckLatin1Entity();
	  if (u == '\0') return NULL;
	} else
	  if (u == '<') {
	    while (1) {
	      u = *str++;
	      if (u == '\0') return NULL;
	      if (u == '\n' || u == '>') break;
	    }
	  } else
	    if (u == '[' && x8bitar) SkippaTill(']');
      }
    } while (!(t = bokstavsTabell[u]) || t == '-');

    while (1) {
      if (t == '-' || (xTex && t == '/')) {
	/* I Tex behandlas /- precis som bara - */
	if (t == '/') if ((u = *str++) != '-') {
	  if (u == '\'' || u == '`' || u == '^' || u == '~' || u == '"') {
	    unsigned char uprev = u;
	    u = *str++;
	    if (u != '\0') {
	      if (uprev == '\'') {
		if (u == 'e') {
		  t = ISO_intern[(unsigned char)(u = '�')]; continue;
		} else if (u == 'E') {
		  t = ISO_intern[(unsigned char)(u = '�')]; continue;
		}
	      } else if (uprev == '"') {
		unsigned char newc;
		switch (u) {
		case 'a': newc = '�'; break;
		case 'o': newc = '�'; break;
		case 'A': newc = '�'; break;
		case 'O': newc = '�'; break;
		default: goto skipControl;
		}
		u = newc;
		t = ISO_intern[newc]; 
		continue;
	      }
	      skipControl:
	      if ((t = bokstavsTabell[u])) continue;
            }
	  }
	  str--;
	  goto ordSlut;
	}
	u = *str++;
	if (u == ' ' || u == '\t' || u == '\n') {
	  nyrad = (u == '\n');
	  while (1) {
	    if ((u = *str) == '\0') goto ordSlut;
	    str++;
	    if (u == '\n') nyrad = 1;
	    else if (u != ' ' && u != '\t') break;
	  }
	  if (!nyrad) {
	    if (i > 0) { 
	      urord[i] = '-';
	      i++;
	      bindestreck++;
	    }
	    str--;
	    goto ordSlut;
	  }
	}
	if (u == '&' && xHtml) {
	  u = CheckLatin1Entity();
	  if (u == '\0') goto ordSlut;
	}
	if ((t = bokstavsTabell[u])) {
	  if (t == '-' || (xTex && t == '/')) goto ordSlut;
	  if (i > 0) { 
	    urord[i] = '-';
	    if (++i >= LANGD) {
	      if (!SkippaRestenAvOrdet()) return NULL;
	      goto start;
	    }
	    bindestreck++;
	  }
	} else goto ordSlut;
      }
      urord[i] = u;
      if (++i >= LANGD) {
	if (!SkippaRestenAvOrdet()) return NULL;
	goto start;
      }
      if ((u = *str) == '\0') goto ordSlut;
      str++;
      if (u == '&' && xHtml) {
	u = CheckLatin1Entity();
	if (u == '\0') goto ordSlut;
      }
      if (!(t = bokstavsTabell[u])) break;
    }
    if (xHtml) {
      if (u == '<' || (u == '[' && x8bitar)) str--;
    }
   ordSlut: ;
  } while (i < ORDMIN);
  urord[i] = '\0';
  return str;
}

wwwstatic INLINE void SuddaBindestreck(const unsigned char *ordin, unsigned char *ordut)
{
  if (xSammansatta) if (ordin[1] == '-')
    ordin += 2; /* G�r om t ex c-uppgiften till uppgiften */
  while (*ordin)
    if (*ordin == '-') ordin++;
    else *ordut++ = *ordin++;
  *ordut = '\0';
}

/* Initiera initierar diverse tabeller och returnerar 1 om  allt g�r bra
   och 0 annars. */
static int Initiera(void)
{
  InitieraBokstavsTabeller();
  if (xAndelser) {
    if (InitSuf(SLfilename)) {
      PrintErrorWithText("Fel vid initiering av �ndelsetabellen %s\n", SLfilename);
      return 0;
    }
  }
  return 1;
}

INLINE int InFLSuffix(const unsigned char *ord, int len)
{
  if (xAndelser && len >= 5) {
    unsigned char word[LANGD];
    int i;
    if (strcmp((char *)ord + len - 4, "ings") == 0) { /* <V>ings <- ing */
      for (i = len - 5; i >= 0 ; i--)
	if (isVowel[ord[i]]) break;
      if (i >= 0) { /* det finns en vokal f�re "ings" */
	strncpy((char *)word, (char *)ord, len - 1);
	word[len - 1] = '\0';
	if (InEL(word, len - 1)) return 1;
      }
    } else
    if (strcmp((char *)ord + len - 2, "ar") == 0) { /* ar <- are, aren */
      strncpy((char *)word, (char *)ord, len);
      word[len] = 'e';
      word[len + 1] = '\0';
      if (InEL(word, len + 1)) {
	word[len + 1] = 'n';
	word[len + 2] = '\0';
	if (InEL(word, len + 2)) return 1;
      }
    }
  }
  return InFL(ord, len);
}


static int AddCompound(const char *breaks, unsigned char *word)
{ int noofbreaks = 0, i, j;
  float len, compval;
  if (noofcompounds >= MAXNOOFCOMPOUNDS) return 0;
  for (i = 0; breaks[i]; i++) if (breaks[i] != ' ') noofbreaks++;
  len = i;
  for (i--; i >= 0 && breaks[i] == ' '; i--);
  len -= i;
  if (i < 0 || breaks[i] == 's') { len--; i++; }
#ifdef MoveSToFirstPartIfPossible
  /* Prefer kvarts-ur to kvart-sur. This gains very little. */
  if (i > 1 &&word[i-1] == 's' && bindebokstav[word[i-2]] == 's')
    if (InEL(word+i-1, strlen((char *)word+i-1)) || 
	  (xAndelser && CheckSuffix(word+i-1, 0))) {
      /*      printf("s-ord: %s %s\n", word, word+i-1); */
      len += 1.1;
    }
#endif
  compval = len - compfactor * (noofbreaks + 1);
  for (i = 0; i < noofcompounds; i++)
    if (compval > breakposlen[i] - compfactor * breakposparts[i]) {
      for (j = noofcompounds; j > i; j--) {
	strcpy(breakpossibilities[j], breakpossibilities[j-1]);
	breakposparts[j] = breakposparts[j-1];
	breakposlen[j] = breakposlen[j-1];
      }
      break;
    }
  strcpy(breakpossibilities[i], breaks);
  breakposparts[i] = noofbreaks + 1;
  breakposlen[i] = (float) len;
  noofcompounds++;
  return 1;
}

/* Kolla om word �r sammansatt som FL* EL. Om xTillatSIFogar
   s� till�t 's' i alla fogar utom mellan 1:a och 2:a delen.
   Om xTillatSIAllaFogar s� till�t 's' i alla fogar. */
static INLINE int IsCompoundHelp(unsigned char *word, int offset, int len)
{
  int end, tmp, firstpos, lastpos;
  char oldval;
    
  if (offset > 0 && 
      (InEL(word, len) || (xAndelser && CheckSuffix(word, 1)))) {
    AddCompound(gBreaks, word - offset);
  }
  lastpos = len - SLUTDELORDMIN;
  firstpos = (offset == 0 ? STARTDELORDMIN : DELORDMIN);
  for (end = firstpos; end <= lastpos; end++) {
    tmp = word[end];
    word[end] = 0;
    if (InFLSuffix(word, end)) {
      word[end] = tmp;
      /* Hantera tex toppolitiker som topp|politiker */
      if (word[end-1] == word[end-2]) {
        if (word[end-1] == tmp) continue;
	oldval = gBreaks[offset+end-1];
	gBreaks[offset+end-1] = '<';                  
        if (IsCompoundHelp(word+end-1, offset+end-1, len-end+1)) {
          return 1;
        }
	gBreaks[offset+end-1] = oldval;
      }
      oldval = gBreaks[offset+end];
      gBreaks[offset+end] = '|';
      if (IsCompoundHelp(word+end, offset+end, len-end)) {
	return 1;
      }
      gBreaks[offset+end] = oldval;

      if (tmp == 's' &&
	  ((xTillatSIFogar && offset) || xTillatSIAllaFogar) &&
          bindebokstav[(unsigned char)word[end-1]] == 's' &&
	  end != lastpos) {
	oldval = gBreaks[offset+end];
	gBreaks[offset+end] = 's';
        if (IsCompoundHelp(word+end+1, offset+end+1, len-end-1)) { 
          return 1;
        }
	gBreaks[offset+end] = oldval;
      }
    }
    else word[end] = tmp;
  }
  if (word[lastpos] == word[lastpos-1]) {
    end = lastpos + 1;
    tmp = word[end];
    if (end >= firstpos && tmp != word[lastpos]) {
      word[end] = 0;
      if (InFLSuffix(word, end)) {
	/* Hantera tex herrum som herr|rum */
	word[end] = tmp;
	if (InEL(word+end-1, len-end+1) || 
	    (xAndelser && CheckSuffix(word+end-1, 1))) {
	  oldval = gBreaks[offset+end-1];
	  gBreaks[offset+end-1] = '<';
	  AddCompound(gBreaks, word-offset);
	  gBreaks[offset+end-1] = oldval;
        }
      }
      else word[end] = tmp;

    }
  }
  return 0;
}

/* IsCompound avg�r om ett ord �r sammansatt (FL* EL) */
static int IsCompound(const unsigned char *word, char *breaks, int len)
{
  gBreaks = breaks;
  return IsCompoundHelp((unsigned char *)word, 0, len);
}

/* Kolla om word �r sammansatt som FL* EL. 
   G�r precis samma som IsCompoundHelp men kolla inte alla 
   sammans�ttningsm�jligheter.
   Om det inte �r en sammans�ttning returneras 0.
   Antalet led i den funna sammans�ttningen returneras annars.
 */
static INLINE int SimpleIsCompoundHelp(unsigned char *word, int offset, int len)
{
  int end, tmp, firstpos, lastpos, res;

  if (offset > 0 && 
      (InEL(word, len) || (xAndelser && CheckSuffix(word, 1)))) {
    return 1;
  }
  lastpos = len - SLUTDELORDMIN;
  firstpos = (offset == 0 ? STARTDELORDMIN : DELORDMIN);
  for (end = firstpos; end <= lastpos; end++) {
    tmp = word[end];
    word[end] = 0;
    if (InFLSuffix(word, end)) {
      word[end] = tmp;
      /* Hantera tex toppolitiker som topp|politiker */
      if (word[end-1] == word[end-2]) {
        if (word[end-1] == tmp) continue;
        if ((res = SimpleIsCompoundHelp(word+end-1, offset+end-1, len-end+1)))
          return res + 1;
      }
      if ((res = SimpleIsCompoundHelp(word+end, offset+end, len-end)))
	return res + 1;

      if (tmp == 's' &&
	  ((xTillatSIFogar && offset) || xTillatSIAllaFogar) &&
          bindebokstav[(unsigned char)word[end-1]] == 's' &&
	  end != lastpos) {
        if ((res = SimpleIsCompoundHelp(word+end+1, offset+end+1, len-end-1)))
          return res + 1;
      }
    }
    else word[end] = tmp;
  }
  if (word[lastpos] == word[lastpos-1]) {
    end = lastpos + 1;
    tmp = word[end];
    if (end >= firstpos && tmp != word[lastpos]) {
      word[end] = 0;
      if (InFLSuffix(word, end)) {
	/* Hantera tex herrum som herr|rum */
	word[end] = tmp;
	if (InEL(word+end-1, len-end+1) || 
	    (xAndelser && CheckSuffix(word+end-1, 1))) {
	  return 1;
        }
      }
      else word[end] = tmp;

    }
  }
  return 0;
}

/* SimpleIsCompound avg�r om ett ord �r sammansatt (FL* EL)
   Om det inte �r en sammans�ttning returneras 0.
   Antalet led i den funna sammans�ttningen returneras annars.
*/
int SimpleIsCompound(const unsigned char *word, int len)
{
  return SimpleIsCompoundHelp((unsigned char *)word, 0, len);
}


/* checklevel = 1 (endast ord), 2 = (+�ndelsekoll), 3 = (+sammans�ttningar) */
int CheckWord(const unsigned char *word, int checkLevel)
{ int len = strlen((char *)word);
  switch (InILorELbutnotUL(word, len)) {
  case -1: return 0;
  case 0: break;
  case 1: return 1;
  }
  if (checkLevel == 1) return 0;
  if (xAndelser && CheckSuffix(word, 1)) return 1;
  if (checkLevel == 2) return 0;
  if (xSammansatta && SimpleIsCompound(word, len)) return 1;
  return 0;
}

/* Finns kollar om ordet word med l�ngden len finns och returnerar
i s� fall 1. Om ordet �r med i undantagsordlista returneras -1,
annars 0. */
static INLINE int Finns(const unsigned char *word, int len)
{
  char breaks[LANGD];
  int i;
  noofcompounds = 0;
  for (i = 0; i < len; i++) breaks[i] = ' ';
  breaks[len] = '\0';
  if (!xIntePetig) {
    int i = FyrKollaHela(word);
    if (i > 0) return 0;
  }
  if (InUL(word, len)) return -1;
  if (xAndelser && CheckSuffix(word, 1)) return 1;
  switch (InILorELbutnotUL(word, len)) {
  case -1: return -1;
  case 0: break;
  case 1: 
    return 1;
  }
  if (xSammansatta) {
    compoundSearch = 1;
    IsCompound(word, breaks, len);
    compoundSearch = 0;
    if (noofcompounds > 0) {
      if (xDebug) {
	WriteISO(word);
	printf(" sammansatt som ");
	WriteCompound(word, breakpossibilities[0]);
	printf("\n");
      }
      return 1;
    }
  } 
  return 0;
}


/* OppnaFiler �ppnar alla filer och returnerar 1 om allt g�r bra och
   0 annars. */
static int OppnaFiler(void)
{
  /* �ppna lexikonfiler: */
  if (!(ELfp = fopen(ELfilename,"rb"))) {
    PrintErrorWithText("Kan inte �ppna filen %s\n", ELfilename);
    return 0;
  }
  if (!(FLfp = fopen(FLfilename,"rb"))) {
    PrintErrorWithText("Kan inte �ppna filen %s\n", FLfilename);
    return 0;
  }
  if (!(ILfp = fopen(ILfilename,"rb"))) {
    PrintErrorWithText("Kan inte �ppna filen %s\n", ILfilename);
    return 0;
  }
  if (!(ULfp = fopen(ULfilename,"rb"))) {
    PrintErrorWithText("Kan inte �ppna filen %s\n", ULfilename);
    return 0;
  }
  return 1;
}


static long TagExtraOrdlista(FILE *fp, char ordlista)
{ long antal = 0;
  unsigned char *s, buf[LANGD + 3];
  switch (ordlista) {
   case 'E':
    while (fgets((char *)buf, LANGD-1, fp)) {
      s = buf;
      while ((*s = dubbelBokstavsTabell[(unsigned char) (*s)])) s++;
      if (*buf) {	
	StoreInEL(buf);
        if (xRattstavningsforslag || !xIntePetig) LagraFyrgram(buf);
        antal++;
      }
    }
    break;
   case 'I':
    while (fgets((char *)buf, LANGD-1, fp)) {
      s = buf;
      while ((*s = dubbelBokstavsTabell[(unsigned char) (*s)])) s++;
      if (*buf) {
	StoreInIL(buf);
        if (xRattstavningsforslag || !xIntePetig) LagraFyrgram(buf);
        antal++;
      }
    }
    break;
   case 'F':
    while (fgets((char *)buf, LANGD-1, fp)) {
      s = buf;
      while ((*s = dubbelBokstavsTabell[(unsigned char) (*s)])) s++;
      if (*buf) {
	StoreInFL(buf);
        if (xRattstavningsforslag || !xIntePetig) LagraFyrgram(buf);
        antal++;
      }
    }
    break;
   case 'U':
    while (fgets((char *)buf, LANGD-1, fp)) {
      s = buf;
      while ((*s = dubbelBokstavsTabell[(unsigned char) (*s)])) s++;
      if (*buf) {
	StoreInUL(buf);
        antal++;
      }
    }
    break;
   default: ;
  }
  fclose(fp);
  return(antal);
}

static void TagStandardOrdlista(const char *name, char wordlist)
{ char fullname[FILENAMELENGTH];
  sprintf(fullname, "%s%s", libpath, name);
  if ((xELfp = fopen(fullname, "r"))) TagExtraOrdlista(xELfp, wordlist);
}

static INLINE long myfread(void *p, size_t elsize, long n, FILE *fp)
{ return fread(p, elsize, n, fp); }

static INLINE long myfwrite(void *p, size_t elsize, long n, FILE *fp)
{ return fwrite(p, elsize, n, fp); }

/* ReadLexicon �ppnar alla lexikon och returnerar 1 om allt g�r bra
   och 0 annars. */
static int ReadLexicon(const unsigned char *separator)
{ unsigned char slask;

  if (myfread(ELtable, sizeof(unsigned char), ELSIZE, ELfp) != ELSIZE
      || fread(&slask, sizeof(char), 1, ELfp) == 1) {
    PrintErrorWithText("%s har fel format f�r att vara en lexikonfil\n",ELfilename);
    fclose(ELfp);
    return 0;
  }
  fclose(ELfp);
  if (myfread(FLtable, sizeof(unsigned char), FLSIZE, FLfp) != FLSIZE
      || fread(&slask, sizeof(char), 1, FLfp) == 1) {
    PrintErrorWithText("%s har fel format f�r att vara en lexikonfil\n",FLfilename);
    fclose(FLfp);
    return 0;
  }
  fclose(FLfp);
  if (myfread(ILtable, sizeof(unsigned char), ILSIZE, ILfp) != ILSIZE
      || fread(&slask, sizeof(char), 1, ILfp) == 1) {
    PrintErrorWithText("%s har fel format f�r att vara en lexikonfil\n",ILfilename);
    fclose(ILfp);
    return 0;
  }
  fclose(ILfp);
  if (myfread(ULtable, sizeof(unsigned char), ULSIZE, ULfp) != ULSIZE
      || fread(&slask, sizeof(char), 1, ULfp) == 1) {
    PrintErrorWithText("%s har fel format f�r att vara en lexikonfil\n",ULfilename);
    fclose(ULfp);
    return 0;
  }
  fclose(ULfp);
  if (xRattstavningsforslag || !xIntePetig) 
    if (!InitRattstava(fyrgramfilename, separator)) return 0;
  if (xRattstavningsforslag) {
    FILE *f = fopen(XLfilename, "rb");
    if (!f) {
      PrintErrorWithText("Kan inte �ppna frekvensfilen %s", XLfilename);
      return 0;
    }
    if (myfread(XLtable, 1, XLSIZE, f) != XLSIZE
        || fread(&slask, 1, 1, f) == 1) {
      PrintErrorWithText("%s har fel format f�r att vara en frekvensfil\n",
              XLfilename);
      fclose(f);
      return 0;
    }
  }
  if (!xKort) { /* KE/KF/KILFILENAME inneh�ller redan f�ljande ordlistor */
    if (xForkortningar) TagStandardOrdlista(XFORKORTNINGAR, 'I');
    if (xNamn) TagStandardOrdlista(XNAMN, 'I');
    if (xDatatermer) {
      TagStandardOrdlista(XDATATERMEREL, 'E');
      TagStandardOrdlista(XDATATERMERFL, 'F');
      TagStandardOrdlista(XDATATERMERIL, 'I');
    }
  }
  if (xTex) TagStandardOrdlista(XTEX, 'I');
  return 1;
}


INLINE void VersalerGemena(register const unsigned char *ordin, register unsigned char *ord,
			   register unsigned char *Ord)
{ register int i;
  int baraGemena, baraVersaler;
  baraGemena = baraVersaler = 1;
  for (i = 0; ordin[i] != '\0'; i++) {
    if (isUpperCase[ordin[i]]) {
      baraGemena = 0;
      ord[i] = toLowerCase[ordin[i]];
    } else {
      baraVersaler = 0;
      ord[i] = ordin[i];
    }
  }
  if (baraGemena) ord[0] = Ord[0] = '\0';
  else {
    ord[i] = '\0';
    if (baraVersaler) {
      Ord[0] = ordin[0];
      strcpy((char *)Ord + 1, (char *)ord + 1);
    } else Ord[0] = '\0';
  }
}

/* Kolla vilken ordlistetyp som angivits, E, I, F, U eller S */
static char KollaOrdlistetyp(char otyp)
{
  switch (otyp) {
   case '\0': return 'E';
   case 'E': return 'E';
   case 'e': return 'E';
   case 'I': return 'I';
   case 'i': return 'I';
   case 'F': return 'F';
   case 'f': return 'F';
   case 'U': return 'U';
   case 'u': return 'U';
   case 'S': return 'S';
   case 's': return 'S';
   default: return 'E'; /* standardval */
  }
}

/* KollaOrd kollar ordet som det �r, med bara sm� bokst�ver och, om det
   bara inneh�ller versaler, med stor begynnelsebokstav */
wwwstatic INLINE int KollaOrd(const unsigned char *ordin)
{ static unsigned char ord[LANGD + 3], Ord[LANGD + 3];
  int len = strlen((char *)ordin);
  switch (Finns(ordin, len)) {
  case -1: return 0;
  case 0: break;
  case 1: return 1;
  }
  VersalerGemena(ordin,ord,Ord);
  if (*ord) switch (Finns(ord, len)) {
  case -1: return 0;
  case 0: break;
  case 1: return 1;
  }
  if (*Ord) { /* bara versaler */
    if (xAcceptCapitalWords) return 1;
    if (Finns(Ord, len) == 1) return 1;
  }
  return 0;
}

/* KollaDelar kollar alla ordets delar som �r avskiljda med bindestreck
   var f�r sej och returnerar sant d� alla finns */
wwwstatic INLINE int KollaDelar(const unsigned char *ordin, unsigned char *ord2)
{ unsigned char *t;
  do {
    t = ord2;
    while (*ordin && *ordin != '-') *t++ = *ordin++;
    *t = '\0';
    if (t - ord2 >= ORDMIN)
      if (!KollaOrd(ord2)) return 0;
  } while (*ordin++);
  return 1;
}


/* StavaVersion returns a string that uniquely identifies the version. */
const char *StavaVersion(void)
{ return VERSION; }

/* StavaReadLexicon must be called before any other function in the API. */
/* Returns 1 if the initialization goes well and 0 otherwise. */
int StavaReadLexicon(const
                     char *libPath, /* path to library directory (ending with /) */
		     int compound, /* 1 to allow compound words */
		     int suffix,   /* 1 to apply suffix rules */
		     int abbrev,   /* 1 to add abbreviation word list */
		     int name,     /* 1 to add name list */
		     int comp,     /* 1 to add list of computer words */
		     int correct,  /* 1 to be able to correct words */
		     const unsigned char *separator) /* separator between corrections */
{
  libpath = libPath;
  x8bitar = ISOCODE;
  angettTeckenkod = 1;
  xSammansatta = compound;
  xAndelser = suffix;
  xForkortningar = abbrev;
  xNamn = name;
  xDatatermer = comp;
  xRattstavningsforslag = correct;
  sprintf(XLfilename, "%s%s", libpath, XLFILENAME);
  sprintf(fyrgramfilename, "%s%s", libpath, XFYRGRAM);
  xKort = xForkortningar && xNamn && xDatatermer;
  xPrintError = 0; /* Skriv inte ut felmeddelanden p� stderr */
  sprintf(ELfilename, "%s%s", libpath, xKort ? KELFILENAME : ELFILENAME);
  sprintf(FLfilename, "%s%s", libpath, xKort ? KFLFILENAME : FLFILENAME);
  sprintf(ILfilename, "%s%s", libpath, xKort ? KILFILENAME : ILFILENAME);
  sprintf(ULfilename, "%s%s", libpath, xKort ? KULFILENAME : ULFILENAME);
  sprintf(SLfilename, "%s%s", libpath, SLFILENAME);
  *stavaerrorbuf = '\0';
  if (!Initiera() || !OppnaFiler() || !ReadLexicon(separator)) return 0;
  return 1;
}

/* StavaAddWord adds a word to one of the word lists of Stava. This means
   that in the future the word will be accepted. There are four types of
   word lists:
   E  - (Ending) for words that may appear alone or as last part of compound
        Examples: medium, fotboll, bl�are
   F  - (First) for words that may appear as first or middle part of compound
        Examples: medie, fotbolls, bl�
   I  - (Individual) for words that may appear only as individual words
        Examples: hej, du
   U  - (exception) for words that should not be accepted
        Examples: parantes, m�ssigt
  Returns 1 if word could be stored and 0 otherwise. */
int StavaAddWord( const
		  unsigned char *word, /* the word to be entered */
                  char type)  /* word list type (E, F, I, or U) */
{ unsigned char buf[LANGD + 3];
  int i;
  int positiveword = 1;
  for (i = 0; i < LANGD; i++)
    if (!(buf[i] = bokstavsTabell[word[i]])) break;
  if (i == LANGD) return 0; /* too long word */
  switch (KollaOrdlistetyp(type)) {
    case 'E': StoreInEL(buf); break;
    case 'F': StoreInFL(buf); break;
    case 'I': StoreInIL(buf); break;
    case 'U': StoreInUL(buf); positiveword = 0; break;
    default: return 0;
  }
  if (positiveword && (xRattstavningsforslag || !xIntePetig)) 
    LagraFyrgram(buf);
  return 1;
}

/* StavaWord checks if a word is correctly spelled.
   Returns 1 if the word is correctly spelled and 0 otherwise. */
int StavaWord(
	      const unsigned char *word)     /* word to be checked */
{ unsigned char buf[LANGD + 3], ord2[LANGD + 3];
  int i, bindestreck = 0;
  for (i = 0; i < LANGD; i++) {
    if (!(buf[i] = bokstavsTabell[word[i]])) break;
    if (buf[i] == '-') bindestreck++;
  }
  if (i == LANGD) return 0; /* too long word */
  if (i < ORDMIN) return 1; /* short words are always accepted */
  if (KollaOrd(buf)) return 1;
  if (bindestreck) {
    if (buf[i - 1] == '-') {
      i--;
      buf[i] = '\0';
      if (InFLSuffix(buf, i)) return 1;
      SuddaBindestreck(buf, ord2);
      return InFLSuffix(ord2, strlen((char *)ord2));
    }
    if (xSammansatta) if (KollaDelar(buf, ord2)) return 1;
    SuddaBindestreck(buf, ord2);
    if (KollaOrd(ord2)) return 1;
  }
  return 0;
}

static unsigned char *corrections = NULL;
static int maxCorrectionLength = 0, currentCorrectionLength = 0;

/* StavaSkrivOrd anropas vid r�ttstavningen f�r utskrift av ett
   r�ttstavningsf�rslag. */
void StavaSkrivOrd(const unsigned char *s)
{ long len = currentCorrectionLength + strlen((char *)s);
  unsigned char *t;
  if (len > maxCorrectionLength) {
    if (maxCorrectionLength == 0) {
      maxCorrectionLength = len + 30;
      corrections = malloc(maxCorrectionLength + 1);
    } else {
      maxCorrectionLength = len + 30;
      corrections = realloc(corrections, maxCorrectionLength + 1);
    }
  }
  t = corrections + currentCorrectionLength;
  while ((*t++ = intern_ISO[*s++]));
  currentCorrectionLength = len;
}

/* StavaSkrivSeparator anropas vid r�ttstavningen f�r att skriva ut 
   wordSeparator mellan tv� r�ttstavningsf�rslag. */
void StavaSkrivSeparator(void)
{ long len = currentCorrectionLength + strlen((char *)wordSeparator);
  if (len > maxCorrectionLength) {
    if (maxCorrectionLength == 0) {
      maxCorrectionLength = len + 30;
      corrections = malloc(maxCorrectionLength + 1);
    } else {
      maxCorrectionLength = len + 30;
      corrections = realloc(corrections, maxCorrectionLength + 1);
    }
  }
  strcpy((char *)corrections + currentCorrectionLength, (char *)wordSeparator);
  currentCorrectionLength = len;
}

static unsigned char *AllocateEmptyString()
{ unsigned char *s = malloc(1);
  *s = '\0';
  return s;
}

/* StavaCorrectWord checks if a word is correctly spelled and returns
   ordered proposals of replacements if not. The most likely word is
   presented first.
   Before StavaCorrectWord is called the first time StavaReadLexicon
   must have been called with the parameter correct=1.

   Returns NULL if the word is correctly spelled and a string of 
   proposed replacements otherwise. If no proposed replacement is
   found the empty string is returned. */
unsigned char *StavaCorrectWord(
	      const unsigned char *word)     /* word to be corrected */
{ unsigned char buf[LANGD + 3], ord2[LANGD + 3];
  int i, bindestreck = 0;
  if (!xRattstavningsforslag) return NULL; /* not correctly initialized */
  for (i = 0; i < LANGD; i++) {
    if (!(buf[i] = bokstavsTabell[word[i]])) break;
    if (buf[i] == '-') bindestreck++;
  }
  if (i == LANGD) return NULL; /* too long word */
  if (i < ORDMIN) return NULL; /* short words are always accepted */
  if (KollaOrd(buf)) return NULL;
  if (bindestreck) {
    if (xSammansatta) if (KollaDelar(buf, ord2)) return NULL;
    SuddaBindestreck(buf, ord2);
    if (KollaOrd(ord2)) return NULL;
  }
  maxCorrectionLength = currentCorrectionLength = 0;
  if (SkrivForslag(buf) == 0) return AllocateEmptyString();
  return corrections;
}

/* StavaCorrectCompound checks if a word is a correctly spelled compound
   and then returns ordered proposals of replacements. The most likely word is
   presented first.
   Before StavaCorrectCompound is called the first time StavaReadLexicon
   must have been called with the parameter correct=1.

   Returns NULL if the word is not a correctly spelled compound and a string 
   of proposed replacements otherwise. If no proposed replacement is
   found the empty string is returned. */
unsigned char *StavaCorrectCompound(
	      const unsigned char *word)     /* word to be corrected */
{ unsigned char buf[LANGD + 3];
  char breaks[LANGD];
  int i;
  if (!xRattstavningsforslag) return NULL; /* not correctly initialized */
  for (i = 0; i < LANGD; i++) {
    if (!(buf[i] = bokstavsTabell[word[i]])) break;
  }
  if (i == LANGD) return NULL; /* too long word */
  if (i < ORDMIN) return NULL; /* short words are always accepted */
  if (InILorELbutnotUL(buf, i) != 0) return NULL;
  if (xAndelser && CheckSuffix(buf, 0)) return NULL;
  if (!IsCompound(buf, breaks, i)) return NULL;
  maxCorrectionLength = currentCorrectionLength = 0;
  if (SimpleCorrections(buf) == 0) return AllocateEmptyString();
  return corrections;
}

/* StavaAnalyzeCompound analyzes a compund. 
   Before StavaAnalyzeCompound is called the first time StavaReadLexicon
   must have been called.

   Returns 0 if the word is not a correctly spelled compound and 1 otherwise.
*/
int StavaAnalyzeCompound(
			 unsigned char *res, /* result will appear here */
			 const unsigned char *word) /* word to be analyzed */
{ unsigned char buf[LANGD + 3], ord[LANGD + 3], Ord[LANGD + 3];
  char breaks[LANGD + 3];
  int i, len, bindestreck = 0;
  strcpy((char *) res, (char *) word);
  for (i = 0; i < LANGD; i++) {
    breaks[i] = ' ';
    if (!(buf[i] = bokstavsTabell[word[i]])) break;
    if (buf[i] == '-') bindestreck = 1;
  }
  breaks[i] = '\0';
  if (i == LANGD) return 0; /* too long word */
  if (i < ORDMIN) return 0; /* short words are always accepted */
  len = i;
  if (InILorELbutnotUL(buf, len) != 0) return bindestreck;
  if (xAndelser && CheckSuffix(buf, 0)) return bindestreck;
  noofcompounds = 0;
  compoundSearch = 1;
  IsCompound(buf, breaks, len);
  if (noofcompounds == 0) {
    VersalerGemena(buf,ord,Ord);
    if (*ord) IsCompound(ord, breaks, len);
    if (*Ord && noofcompounds == 0) IsCompound(Ord, breaks, len);
  }
  if (bindestreck && noofcompounds == 0 ) {
    unsigned char *ordin = buf, *t;
    char totbreaks[LANGD + 3], *b;
    int breakstartpos, ordlen;
    for (i = 0; i < LANGD; i++) totbreaks[i] = ' ';
    totbreaks[i] = '\0';
    do {
      t = ord; b = breaks;
      breakstartpos = ordin - buf;
      while (*ordin && *ordin != '-') {
	*t++ = *ordin++;
	*b++ = ' ';
      }
      *t = *b = '\0';
      ordlen = strlen((char *) ord);
      if (ordlen >= ORDMIN &&
	  !InILorELbutnotUL(ord, ordlen) &&
	  (!xAndelser || !CheckSuffix(ord, 0))) {
	noofcompounds = 0;
	IsCompound(ord, breaks, ordlen);
	if (noofcompounds > 0) {
	  breakpossibilities[0][ordlen] = '\0';
	  strcpy(totbreaks + breakstartpos, 
		 breakpossibilities[0]);
	  if (*ordin == '-') totbreaks[ordin - buf] = ' ';
	}
      }
    } while (*ordin++);
    noofcompounds = 1;
    totbreaks[len] = '\0';
    strcpy(breakpossibilities[0], totbreaks);
  }
  compoundSearch = 0;
  if (noofcompounds == 0) return 0;
  *res = '\0';
  StringWriteCompound(res, word, breakpossibilities[0]);
  return 1;
}


/* StavaGetWord reads the next word from infile and stores it in word.
   Word has to be allocated (of size at least LANGD+1 (51)) before calling.
   0 is returned if there is no more word (EOF), and 1 otherwise. */
int StavaGetWord(FILE *infile, unsigned char *word)
{ unsigned char buf[LANGD+1];
  ordf = infile;
  return TagOrd(buf, word);
}

/* StavaStringGetWord reads the next word from the string str and stores 
   it in word.
   Word has to be allocated (of size at least LANGD+1 (51)) before calling.
   NULL is returned if there is no more word, and a pointer to the next
   unused character in str otherwise. */
unsigned char *StavaStringGetWord(unsigned char *str, unsigned char *word)
{
  return TagOrdStr(str, word);
}

/* StavaLastErrorMessage returns a message describing the last error message
that occurred. Returns empty string if no error message occurred since last
call to StavaLastErrorMessage. */
const char *StavaLastErrorMessage(void)
{ 
  static char lasterror[400];
  strcpy(lasterror, stavaerrorbuf);
  *stavaerrorbuf = '\0';
  return lasterror;
}


