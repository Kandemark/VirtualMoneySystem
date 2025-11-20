#ifndef SQLITE3_H
#define SQLITE3_H
// Placeholder for sqlite3.h
typedef struct sqlite3 sqlite3;
typedef struct sqlite3_stmt sqlite3_stmt;
#define SQLITE_OK 0
#define SQLITE_ROW 100
#define SQLITE_DONE 101
#define SQLITE_STATIC ((void(*)(void *))0)
int sqlite3_open(const char *filename, sqlite3 **ppDb);
int sqlite3_close(sqlite3*);
int sqlite3_exec(sqlite3*, const char *sql, int (*callback)(void*,int,char**,char**), void *, char **errmsg);
void sqlite3_free(void*);
const char *sqlite3_errmsg(sqlite3*);
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nByte, sqlite3_stmt **ppStmt, const char **pzTail);
int sqlite3_step(sqlite3_stmt*);
int sqlite3_finalize(sqlite3_stmt *pStmt);
int sqlite3_bind_text(sqlite3_stmt*, int, const char*, int, void(*)(void*));
int sqlite3_bind_double(sqlite3_stmt*, int, double);
const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol);
double sqlite3_column_double(sqlite3_stmt*, int iCol);
int sqlite3_changes(sqlite3*);
#endif
