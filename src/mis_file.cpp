#include "mis_file.h"

MisFile::MisFile(const std::string &path)
    : BracketFile(path)
{
  TraceLog(LOG_INFO, ("FILE: Opening .mis file " + path).c_str());
}

MisFile::~MisFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .mis file");
}
