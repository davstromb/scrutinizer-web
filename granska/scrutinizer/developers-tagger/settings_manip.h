/* settings_manip.h
   functions for reading and writing tagger settings
   Jonas Sj�bergh, 011211
   all code is copy-pasted read/writesettings from obsolete settings.cc
*/
bool ReadSettings(const char *dir, const char *file);
bool WriteSettings(const char *dir, const char *file, int result);

