#include "include/types.hpp"

bool db_init(const char* inpMode);
bool db_shutdown();
void db_refresh();
int db_store(char *word);
bool db_sync();

void db_lowercase();

unsigned face_init();
// returns the std::list of suggestions, each item has phrase and weight members
vp_t face_query(const char* iline, unsigned num);

