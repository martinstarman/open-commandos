#include "mission.h"

Mission::Mission()
{
}

Mission::~Mission()
{
  delete misFile;
  delete secFile;
  delete volFile;
}

void Mission::Load(const std::string &name)
{
  misFile = new MisFile("DATOS/MISIONES/MAPA" + name + ".MIS");
  misFile->Parse();

  std::string volFileName = misFile->GetRoot()
                                ->GetNode(".FASE" + name)
                                ->GetNode(".DATOSFICHEROSMISION")
                                ->GetNode(".VOLUMENES")
                                ->GetString();

  volFile = new VolFile("DATOS/MISIONES/" + volFileName);
  volFile->Parse();

  std::string secFileName = misFile->GetRoot()
                                ->GetNode(".FASE" + name)
                                ->GetNode(".DATOSFICHEROSMISION")
                                ->GetNode(".SECTORES")
                                ->GetString();

  secFile = new SecFile("DATOS/MISIONES/" + secFileName);
  secFile->Parse();

  // for (const auto &polygon : volFile->GetPolygons())
  // {
  //   for (const auto &tile : polygon.GetTiles())
  //   {
  //     TraceLog(LOG_INFO, tile.GetSpriteName().c_str());
  //   }
  // }
}
