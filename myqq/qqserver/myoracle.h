#ifndef MYORACLE_H_
#define MYORACLE_H_

typedef void * sql_context;

class myoraclce
{
public:
  myoracle();
  ~myoracle();
  int sql_connect(const char *Hostname, const char *User, const char *Password, const char *DBName);
  int sql_open(const char *DySQL);
  void sql_disconnect();

private:
  void sql_error();
  void sql_init();
  int sql_free();

  sql_context m_pContext;
  long SQLCODE;
};

#endif
