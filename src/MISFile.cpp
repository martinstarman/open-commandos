#include "MISFile.h"

#include "Utils.h"

#include <iostream> // noskipws
#include <SDL.h>

namespace GreenBeret
{
    MISFile::MISFile(const std::string &path)
        : volFileName(""),
          secFileName("")
    {
        file.open(path, std::ifstream::in);
    }

    MISFile::~MISFile()
    {
        file.close();
    }

    void MISFile::Parse()
    {
        char c;

        while (file >> std::noskipws >> c)
        {
            // keyword
            if (c == '.')
            {
                std::string keyword = ReadUntil(' ');
                //SDL_Log("Parsed MIS file keyword: %s", keyword.c_str());

                if (keyword.find(".FASE") == 0) // mission name
                {
                    ReadUntil('.'); // skip everything until first real token
                }
                else if (keyword == "DATOSFICHEROSMISION")
                {
                    std::string data = ReadUntil(']');
                    ParseMissionFiles(data);
                }
                // TODO: parse remaining data
            }
        }
    }

    std::string MISFile::ReadUntil(char c)
    {
        char curr;
        std::string s;

        do
        {
            file >> std::noskipws >> curr;
            s += curr;
        } while (curr != c);

        return trim(s);
    }

    void MISFile::ParseMissionFiles(std::string &data)
    {
        data = replace(data, "[\\[\\]]", "");
        data = replace(data, "\\n", " ");
        data = trim(data);

        auto values = split(data, ' ');

        for (int i = 0; i < values.size(); i += 2)
        {
            if (values[i] == ".VOLUMENES")
            {
                volFileName = values[i + 1];
            }
            else if (values[i] == ".SECTORES")
            {
                secFileName = values[i + 1];
            }
            // TODO: parse all files
        }
    }
}