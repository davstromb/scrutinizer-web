/* R�ttstavningsprogram. Version 2.60 2004-09-05
   Copyright (C) 1990-2004
   Joachim Hollman och Viggo Kann
   joachim@algoritmica.se viggo@nada.kth.se
*/

/* wordSeparator �r den str�ng som skrivs ut mellan tv� r�ttelsef�rslag. */
const extern unsigned char *wordSeparator;

/* rattstava.h - gr�nssnitt till rattstava.c */
/* InitRattstava �ppnar fyrgramsfilen och initierar hj�lpstrukturer.
   separator �r den str�ng som skrivs ut mellan tv� r�ttelsef�rslag. */
extern int InitRattstava(const char *fyrgramfilename, 
			 const unsigned char *separator);
/* LagraFyrgram ser till att ett ords alla fyrgram �r till�tna */
INLINE extern void LagraFyrgram(const unsigned char *ord);
/* FyrKollaHela kollar om ett ords alla fyrgram �r till�tna */
INLINE extern int FyrKollaHela(const unsigned char *ord);

/* SimpleCorrections genererar r�ttelser p� avst�nd 1 i EL och IL fr�n 
   ett potentiellt riktigt stavat ord. Returnerar 0 om inget f�rslag kunde
   genereras och 1 annars. */
extern int SimpleCorrections(unsigned char *word);
/* SkrivForslag genererar r�ttstavningsf�rslag f�r ett ord och skriver 
   ut dom med SkrivOrd(). Returnerar 0 om inget f�rslag kunde
   genereras och 1 annars. */
extern int SkrivForslag(unsigned char *ordin);
