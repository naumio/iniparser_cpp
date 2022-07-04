#include "inip.hpp"
extern "C"{
    #include "iniparser.h"
}

INI_ERROR iniFile::Open(std::string& fileName)
{
    dictionary *dict;
    int nsec;
    int nkeys;
    const char **secKeys;

    // Clear previous sections
    for (int i = 0; i < (int)this->sections.size(); i++)
        this->sections[i].values.clear();

    this->sections.clear();

    // Open ini file 
    dict = iniparser_load(fileName.c_str());

    if (dict == 0)
        return ERR;

    // Get number of sections
    nsec = iniparser_getnsec(dict);

    // Add sections to list 
    this->sections.resize(nsec);
    for (int i = 0; i < nsec; i++) 
    {
        // Set section name 
        this->sections[i].name = iniparser_getsecname(dict, i);

        // Get number of key-value pairs in section, resize list
        nkeys = (int)iniparser_getsecnkeys(dict, this->sections[i].name.c_str());
        this->sections[i].values.resize(nkeys);

        // Allocate memory for key strings, required by iniparser library
        secKeys = (const char**)malloc(sizeof(const char*) * nkeys);

        // Get key strings
        if (iniparser_getseckeys(dict, this->sections[i].name.c_str(), secKeys) == NULL)
        {
            free(secKeys);
            break;
        }

        // Copy key-value pairs to list
        for (int key = 0; key < nkeys; key++)
        {
            SecKey2Key(secKeys[key], this->sections[i].values[key].key);
            this->sections[i].values[key].value.assign(iniparser_getstring(dict, secKeys[key], ""));
        }

        free(secKeys);

    }

    iniparser_freedict(dict);

    return OK;
}


// Converts a section key string to key string
void iniFile::SecKey2Key(const char *secKey, std::string& key)
{
    std::string str_secKey;

    str_secKey.assign(secKey);

    key = str_secKey.substr(str_secKey.find(":") + 1);
}


iniFile::iniFile()
{
}

iniFile::~iniFile()
{
}
