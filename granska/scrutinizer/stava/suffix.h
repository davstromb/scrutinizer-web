/* R�ttstavningsprogram. Version 2.55 2001-10-29
   Copyright (C) 1990-2001
   Joachim Hollman och Viggo Kann
   joachim@nada.kth.se viggo@nada.kth.se
*/


/* InitSuf initierar suffixtabellen och returnerar 0 om det gick bra. */
extern int InitSuf(const char *SLfilename);
/* CheckSuffix kollar om word inneh�ller suffix i suffixtabellen. F�r varje
rad i suffixtabellen som st�mmer �verens kollas att ordet finns i ordlistan
om suffixet byts ut mot alla kollsuffix i s� fall returneras 1. Annars
returneras 0. */
extern int CheckSuffix(const unsigned char *word, int tryallrules);

