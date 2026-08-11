#include "sec-file.h"

SecFile::SecFile(const std::string &path)
{
  TraceLog(LOG_INFO, ("FILE: Opening .sec file " + path).c_str());
  Open(path);
}

SecFile::~SecFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .sec file");
  file.close();
}

void SecFile::Parse()
{
  TraceLog(LOG_INFO, "NOT IMPLEMENTED!");
  // TODO: implement me
}
