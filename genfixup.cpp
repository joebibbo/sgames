// genfixup.cpp : A program to fixup some generated data that will be used by the population program, see
// readme.txt for more details.
//
//

#include "stdio.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

typedef struct tEntry
{
    string name, birth, death;
    int    age;
} tEntry;

// tokenize a string using a delimiter. Result is returned as a vector of strings.
vector<string> tokenize(const char *str, char c = ' ')
{
    vector<string> result;

    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (0 != *str++);

    return result;
}

// Death date must be greater than birth and can't exceed the year 2000. Our dataset generator didn't allow us to put constraints,
// so we might end up with some backwards ages.
void santizeDeath(tEntry& item)
{

    typedef struct tDate
    {
        int day, month, year;
    } tDate;

    tDate birth, death;  
     
    sscanf(item.birth.c_str(), "%d/%d/%d", &birth.month,&birth.day,&birth.year );
    sscanf(item.death.c_str(), "%d/%d/%d", &death.month,&death.day,&death.year );

    if ((birth.year * 365 + birth.month * 12 + birth.day) >= (death.year * 365 + death.month * 12 + death.day))
    {
       string temp = item.birth;
       item.birth  = item.death;
       item.death  = temp;
    }
}

int main(int argc, char* argv[])
{
    std::string nextline;
    std::vector<tEntry> dataSet;

    printf("\nsanitizing..." );

    // Read generated dataset.
    std::ifstream data;
    data.open ("names");
    if (data.is_open())
    {
        while (std::getline(data, nextline))
        {
            tEntry next;

            vector<string> line = tokenize(nextline.c_str(), ';');
            next.name  = line[0];
            next.birth = line[1];
            next.death = line[2];

            // sanitize by making sure the birth and death dates make sense.
            santizeDeath( next );

            dataSet.push_back(next);
        }
    }

    data.close();

    // write out the fixed up dataset to be used by population program.
    std::ofstream output;
    output.open("names_");
    for (auto next : dataSet)
    {
        output << next.name << ";" << next.birth << ";" << next.death << std::endl;
    }
    output.close();

    printf("%d valid entries in dataset: 'names_'\n", (int) dataSet.size() );

	return 0;
}

