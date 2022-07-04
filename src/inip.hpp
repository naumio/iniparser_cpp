#ifndef INIP_HPP
#define INIP_HPP

#include <string>
#include <vector>

//*****************************************************************************
// Enums
//*****************************************************************************
typedef enum
{
    OK  = 0,
    ERR = -1
} INI_ERROR; 

//*****************************************************************************
// Types
//*****************************************************************************
typedef struct
{
    std::string key;
    std::string value;
} STR_INI_KEYVAL;

typedef struct
{
    std::string name;
    std::vector<STR_INI_KEYVAL> values;
} STR_INI_SECTION;

//*****************************************************************************
// Classes
//*****************************************************************************
class iniFile
{
private:
    void SecKey2Key(const char *secKey, std::string& key);
public:
    std::vector<STR_INI_SECTION> sections;

    INI_ERROR Open(std::string& fileName);

    iniFile();
    ~iniFile();
};



#endif // INIP_HPP