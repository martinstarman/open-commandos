#include "dat_file.h"

DatFile::DatFile(const std::string &path)
    : BracketFile(path)
{
  TraceLog(LOG_INFO, ("FILE: Opening .dat file " + path).c_str());
}

DatFile::~DatFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .dat file");
}
