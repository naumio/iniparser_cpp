#include <string>
#include <stdio.h>
#include "../src/inip.hpp"

int main(int argc, const char **argv)
{
    iniFile ini;
    std::string fileName = "";

    if(argc < 2)
    {
        printf("Please give input file!\n");
        return -1;
    }

    fileName = argv[1];

    if (ini.Open(fileName) == ERR)
    {
        printf("Could not open file! (%s)\n", fileName.c_str());
        return -1;
    }

    for (int i = 0; i < (int)ini.sections.size(); i++)
    {
        printf("Name: %s\n", ini.sections[i].name.c_str());

        printf("Keys:\n");
        for (int j = 0; j < (int)ini.sections[i].values.size(); j++)
        {
            printf("    %s: %s\n", ini.sections[i].values[j].key.c_str(), ini.sections[i].values[j].value.c_str());
        }

        printf("\n");
    }


    return 0;
}