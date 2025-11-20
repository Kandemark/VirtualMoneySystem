#include "sqlite3.h"
// Placeholder for sqlite3.c
int sqlite3_open(const char *filename, sqlite3 **ppDb) { return SQLITE_OK; }
int sqlite3_close(sqlite3*) { return SQLITE_OK; }
int sqlite3_exec(sqlite3*, const char *sql, int (*callback)(void*,int,char**,char**), void *, char **errmsg) { return SQLITE_OK; }
void sqlite3_free(void*) {}
const char *sqlite3_errmsg(sqlite3*) { return "Placeholder error"; }
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nByte, sqlite3_stmt **ppStmt, const char **pzTail) { return SQLITE_OK; }
int sqlite3_step(sqlite3_stmt*) { return SQLITE_DONE; }
int sqlite3_finalize(sqlite3_stmt *pStmt) { return SQLITE_OK; }
int sqlite3_bind_text(sqlite3_stmt*, int, const char*, int, void(*)(void*)) { return SQLITE_OK; }
int sqlite3_bind_double(sqlite3_stmt*, int, double) { return SQLITE_OK; }
const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol) { return (const unsigned char*)""; }
double sqlite3_column_double(sqlite3_stmt*, int iCol) { return 0.0; }
int sqlite3_changes(sqlite3*) { return 1; }
