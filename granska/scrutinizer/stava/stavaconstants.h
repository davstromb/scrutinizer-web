/* R�ttstavningsprogram. Version 2.55  2001-09-26
   Copyright (C) 1990-2001
   Joachim Hollman och Viggo Kann
   joachim@nada.kth.se viggo@nada.kth.se
*/

unsigned char ISO_intern[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
' ',0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
'P','Q','R','S','T','U','V','W','X','Y','Z',0,0,0,0,0,
0,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w','x','y','z',0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
'A','A','A','A','[',']','[','C','E',94,'E','E','I','I','I','I',
'D','N','O','O','O','O','\\',0,'\\','U','U','U','Y','Y',0,0,
'a','a','a','a','{','}','{','c','e',126,'e','e','i','i','i','i',
'd','n','o','o','o','o','|',0,'|','u','u','u','y','y',0,'y'};

unsigned char transform_diacritics[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
' ',0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
'P','Q','R','S','T','U','V','W','X','Y','Z',0,0,0,0,0,
0,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w','x','y','z',0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
'A','A','A','A',(unsigned char) '�',(unsigned char) '�',(unsigned char) '�','C','E',(unsigned char) '�','E','E','I','I','I','I',
'D','N','O','O','O','O',(unsigned char) '�',0,(unsigned char) '�','U','U','U','Y','Y',0,0,
'a','a','a','a',(unsigned char) '�',(unsigned char) '�',(unsigned char) '�','c','e',(unsigned char) '�','e','e','i','i','i','i',
'd','n','o','o','o','o',(unsigned char) '�',0,(unsigned char) '�','u','u','u','y','y',0,'y'};

unsigned char MAC_intern[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
'P','Q','R','S','T','U','V','W','X','Y','Z',0,0,0,0,0,
0,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w','x','y','z',0,0,0,0,0,
'[',']',0,0,0,'\\',0,0,0,0,'{',0,'}',0,0,0,0,0,0,0,0,0,0,0,0,0,'|',0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char DOS_intern[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
'P','Q','R','S','T','U','V','W','X','Y','Z',0,0,0,0,0,
0,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w','x','y','z',0,0,0,0,0,
0,0,0,0,'{',0,'}',0,0,0,0,0,0,0,'[',']',0,0,0,0,'|',0,0,0,0,'\\',0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char intern_ISO[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
' ',0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
'P','Q','R','S','T','U','V','W','X','Y','Z',
0xc4 /* � (AE) */, 0xd6 /* � (OE) */, 0xc5 /* � (AA) */, 0xc9 /* � */,0,
0,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w','x','y','z',
0xe4 /* � (ae) */, 0xf6 /* � (oe) */, 0xe5 /* � (aa) */, 0xe9 /* � */,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char MAC_ISO[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
'P','Q','R','S','T','U','V','W','X','Y','Z',0,0,0,0,0,
0,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w','x','y','z',0,0,0,0,0,
(unsigned char)'�',(unsigned char)'�',0,0,0,(unsigned char)'�',0,0,
0,0,(unsigned char)'�',0,(unsigned char)'�',0,0,0,
0,0,0,0,0,0,0,0,0,0,(unsigned char)'�',0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char DOS_ISO[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
'P','Q','R','S','T','U','V','W','X','Y','Z',0,0,0,0,0,
0,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w','x','y','z',0,0,0,0,0,
0,0,0,0,(unsigned char)'�',0,(unsigned char)'�',0,
0,0,0,0,0,0,(unsigned char)'�',(unsigned char)'�',
0,0,0,0,(unsigned char)'�',0,0,0,0,(unsigned char)'�',0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char ISO_ISO[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char ASCII_intern[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
'-',0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
'P','Q','R','S','T','U','V','W','X','Y','Z','[','\\',']',0,0,
0,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w','x','y','z','{','|','}',0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char dubbelBokstavsTabell[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
'-',0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
'P','Q','R','S','T','U','V','W','X','Y','Z','[','\\',']',0,0,
0,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w','x','y','z','{','|','}',0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
'A','A','A','A','[',']','[','C','E',94,'E','E','I','I','I','I',
'D','N','O','O','O','O','\\',0,'\\','U','U','U','Y','Y',0,0,
'a','a','a','a','{','}','{','c','e',126,'e','e','i','i','i','i',
'd','n','o','o','o','o','|',0,'|','u','u','u','y','y',0,'y'};

unsigned char intern_gram[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,
DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,
DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,
DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,DELIMGRAM,
DELIMGRAM,'A'-'A','B'-'A','C'-'A','D'-'A','E'-'A','F'-'A','G'-'A',
'H'-'A','I'-'A','J'-'A','K'-'A','L'-'A','M'-'A','N'-'A','O'-'A',
'P'-'A','Q'-'A','R'-'A','S'-'A','T'-'A','U'-'A','V'-'A','W'-'A',
'X'-'A','Y'-'A','Z'-'A',91-'A',92-'A',93-'A',94-'A',DELIMGRAM,
DELIMGRAM,'a'-'a','b'-'a','c'-'a','d'-'a','e'-'a','f'-'a','g'-'a',
'h'-'a','i'-'a','j'-'a','k'-'a','l'-'a','m'-'a','n'-'a','o'-'a',
'p'-'a','q'-'a','r'-'a','s'-'a','t'-'a','u'-'a','v'-'a','w'-'a',
'x'-'a','y'-'a','z'-'a',123-'a',124-'a',125-'a',126-'a',DELIMGRAM,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
'A'-'A','A'-'A','A'-'A','A'-'A','['-'A',']'-'A','['-'A','C'-'A',
'E'-'A',94-'A','E'-'A','E'-'A','I'-'A','I'-'A','I'-'A','I'-'A',
'D'-'A','N'-'A','O'-'A','O'-'A','O'-'A','O'-'A','\\'-'A',DELIMGRAM,
'\\'-'A','U'-'A','U'-'A','U'-'A','Y'-'A','Y'-'A',DELIMGRAM,DELIMGRAM,
'a'-'a','a'-'a','a'-'a','a'-'a','{'-'a','}'-'a','{'-'a','c'-'a',
'e'-'a',126-'a','e'-'a','e'-'a','i'-'a','i'-'a','i'-'a','i'-'a',
'd'-'a','n'-'a','o'-'a','o'-'a','o'-'a','o'-'a','|'-'a',DELIMGRAM,
'|'-'a','u'-'a','u'-'a','u'-'a','y'-'a','y'-'a',DELIMGRAM,'y'-'a'};

unsigned char intern_p[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
DELIMP /* space */, DELIMP /* ! */, DELIMP /* " */, 0,
0, 0, DELIMP /* & */, DELIMP /* ' */,
DELIMP /* ( */, DELIMP /* ) */, 0, DELIMP /* + */,
DELIMP /* , */, DELIMP /* - */, DELIMP /* . */, DELIMP /* / */,
DELIMP /* 0 */, DELIMP, DELIMP, DELIMP, DELIMP, DELIMP, DELIMP, DELIMP,
DELIMP /* 8 */, DELIMP /* 9 */, DELIMP /* : */, 0, 0, 0, 0, DELIMP /* ? */,
0,'A','B','C','D','E','F','G',
'H','I','J','K','L','M','N','O',
'P','Q','R','S','T','U','V','W',
'X','Y','Z',91,92,93,94,0,
0,'a','b','c','d','e','f','g',
'h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w',
'x','y','z',123,124,125,126,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
'A','A','A','A','[',']','[','C',
'E',94,'E','E','I','I','I','I',
'D','N','O','O','O','O','\\',0,
'\\','U','U','U','Y','Y',0,0,
'a','a','a','a','{','}','{','c',
'e',126,'e','e','i','i','i','i',
'd','n','o','o','o','o','|',0,
'|','u','u','u','y','y',0,'y'};

unsigned char bindebokstav[128] = {
/* 's' st�r f�r bokst�ver som i sammans�ttningar kan f� s efter sig */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,' ','s','s','s',' ','s','s','s',' ','s','s','s','s','s','s',
's','s','s',' ','s',' ','s','s',' ',' ',' ',' ',' ',' ',' ',0,
0,' ','s','s','s',' ','s','s','s',' ','s','s','s','s','s',' ',
's','s','s',' ','s',' ','s','s',' ',' ',' ',' ',' ',' ',' ',0};

/* isConsonant talar om vilka tecken som �r konsonanter */
unsigned char isConsonant[256] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,'B','C','D',0,'F','G','H',0,'J','K','L','M','N',0,
'P','Q','R','S','T',0,'V','W','X',0,'Z',0,0,0,0,0,
0,0,'b','c','d',0,'f','g','h',0,'j','k','l','m','n',0,
'p','q','r','s','t',0,'v','w','x',0,'z',0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,'C',0,0,0,0,0,0,0,0,
'D','N',0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,'c',0,0,0,0,0,0,0,0,
'd','n',0,0,0,0,0,0,0,0,0,0,0,0,0,0};

struct EntityTable {
  char *entity;
  unsigned char letter;
};
#define NOOFENTITIES 62
/* latin1Entities �vers�tter HTML-&-namn till bokst�ver */
static struct EntityTable latin1Entities[NOOFENTITIES] = {
{"AElig", (unsigned char)'�'}, /* capital AE diphthong (ligature) */
{"Aacute", (unsigned char)'�'}, /* capital A, acute accent */
{"Acirc", (unsigned char)'�'}, /* capital A, circumflex accent */
{"Agrave", (unsigned char)'�'}, /* capital A, grave accent */
{"Aring", (unsigned char)'�'}, /* capital A, ring */
{"Atilde", (unsigned char)'�'}, /* capital A, tilde */
{"Auml", (unsigned char)'�'}, /* capital A, dieresis or umlaut mark */
{"Ccedil", (unsigned char)'�'}, /* capital C, cedilla */
{"ETH", (unsigned char)'�'}, /* capital Eth, Icelandic */
{"Eacute", (unsigned char)'�'}, /* capital E, acute accent */
{"Ecirc", (unsigned char)'�'}, /* capital E, circumflex accent */
{"Egrave", (unsigned char)'�'}, /* capital E, grave accent */
{"Euml", (unsigned char)'�'}, /* capital E, dieresis or umlaut mark */
{"Iacute", (unsigned char)'�'}, /* capital I, acute accent */
{"Icirc", (unsigned char)'�'}, /* capital I, circumflex accent */
{"Igrave", (unsigned char)'�'}, /* capital I, grave accent */
{"Iuml", (unsigned char)'�'}, /* capital I, dieresis or umlaut mark */
{"Ntilde", (unsigned char)'�'}, /* capital N, tilde */
{"Oacute", (unsigned char)'�'}, /* capital O, acute accent */
{"Ocirc", (unsigned char)'�'}, /* capital O, circumflex accent */
{"Ograve", (unsigned char)'�'}, /* capital O, grave accent */
{"Oslash", (unsigned char)'�'}, /* capital O, slash */
{"Otilde", (unsigned char)'�'}, /* capital O, tilde */
{"Ouml", (unsigned char)'�'}, /* capital O, dieresis or umlaut mark */
{"THORN", (unsigned char)'�'}, /* capital THORN, Icelandic */
{"Uacute", (unsigned char)'�'}, /* capital U, acute accent */
{"Ucirc", (unsigned char)'�'}, /* capital U, circumflex accent */
{"Ugrave", (unsigned char)'�'}, /* capital U, grave accent */
{"Uuml", (unsigned char)'�'}, /* capital U, dieresis or umlaut mark */
{"Yacute", (unsigned char)'�'}, /* capital Y, acute accent */
{"aacute", (unsigned char)'�'}, /* small a, acute accent */
{"acirc", (unsigned char)'�'}, /* small a, circumflex accent */
{"aelig", (unsigned char)'�'}, /* small ae diphthong (ligature) */
{"agrave", (unsigned char)'�'}, /* small a, grave accent */
{"aring", (unsigned char)'�'}, /* small a, ring */
{"atilde", (unsigned char)'�'}, /* small a, tilde */
{"auml", (unsigned char)'�'}, /* small a, dieresis or umlaut mark */
{"ccedil", (unsigned char)'�'}, /* small c, cedilla */
{"eacute", (unsigned char)'�'}, /*small e, acute accent */
{"ecirc", (unsigned char)'�'}, /* small e, circumflex accent */
{"egrave", (unsigned char)'�'}, /* small e, grave accent */
{"eth", (unsigned char)'�'}, /* small eth, Icelandic */
{"euml", (unsigned char)'�'}, /* small e, dieresis or umlaut mark */
{"iacute", (unsigned char)'�'}, /* small i, acute accent */
{"icirc", (unsigned char)'�'}, /* small i, circumflex accent */
{"igrave", (unsigned char)'�'}, /* small i, grave accent */
{"iuml", (unsigned char)'�'}, /* small i, dieresis or umlaut mark */
{"ntilde", (unsigned char)'�'}, /* small n, tilde */
{"oacute", (unsigned char)'�'}, /* small o, acute accent */
{"ocirc", (unsigned char)'�'}, /* small o, circumflex accent */
{"ograve", (unsigned char)'�'}, /* small o, grave accent */
{"oslash", (unsigned char)'�'}, /* small o, slash */
{"otilde", (unsigned char)'�'}, /* small o, tilde */
{"ouml", (unsigned char)'�'}, /* small o, dieresis or umlaut mark */
{"szlig", (unsigned char)'�'}, /* small sharp s, German (sz ligature) */
{"thorn", (unsigned char)'�'}, /* small thorn, Icelandic */
{"uacute", (unsigned char)'�'}, /* small u, acute accent */
{"ucirc", (unsigned char)'�'}, /* small u, circumflex accent */
{"ugrave", (unsigned char)'�'}, /* small u, grave accent */
{"uuml", (unsigned char)'�'}, /* small u, dieresis or umlaut mark */
{"yacute", (unsigned char)'�'}, /* small y, acute accent */
{"yuml", (unsigned char)'�'} /* small y, dieresis or umlaut mark */
};
