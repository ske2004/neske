/* debugging util */
#pragma once

#include "Basics.H"
#include <cstdio>
#include <cstdarg>
#include <cstdlib>

#define DBGt_INFO  0 // normal log
#define DBGt_FAIL  1 // fatal error
#define DBGt_ERR   2 // error
#define DBGt_WARN  3 // warning

namespace Dbg
{

void XFmtV(U64 dbgt, const char *msg, va_list args)
{
  CStr pfx = "";
  switch (dbgt) {
    case DBGt_INFO: pfx = "\x1b[34mINFO";   break;
    case DBGt_FAIL: pfx = "\x1b[31mFAIL";   break;
    case DBGt_ERR:  pfx = "\x1b[31mAAAA";   break;
    case DBGt_WARN: pfx = "\x1b[33mWARN";   break;
    default:        pfx = "\x1b[33m\?\?\?\?"; break; // stupid trigraphs v_v
  }

  fprintf(stderr, "%s \x1b[37m", pfx);
  vfprintf(stderr, msg, args);
  fprintf(stderr, "\x1b[0m\n");
}

[[noreturn]]
void Fail(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  XFmtV(DBGt_FAIL, msg, args);
  va_end(args);
  exit(1);
}

void Err(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  XFmtV(DBGt_ERR, msg, args);
  va_end(args);
}

void Warn(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  XFmtV(DBGt_WARN, msg, args);
  va_end(args);
}

void Info(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  XFmtV(DBGt_INFO, msg, args);
  va_end(args);
}

}
