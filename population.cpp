// population.cpp : A simple solution to the following problem:
//
// Given a list of people with their birth and end years (all between 1900 and 2000), find the year 
// with the most number of people alive.
//
// Dataset = contains 500 names using ';' as key delimiter
//  Last, First I.; Birt date ; Date of death
// 
// NOTE: Dates are always formatted as follows: Feburary 17th, 1924. 
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
    typedef struct tDate
    {
        int month, day, year;
    } tDate;

    tDate  _birth, _death;
    string name, birth, death;

} tEntry;

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

const int firstYear = 1900;
const int lastYear  = 2000;

int main(int argc, char* argv[])
{
    std::string nextline;
    std::vector<tEntry> dataSet;

    std::ifstream data;
    data.open ("names_");
    if (data.is_open())
    {
        vector<int> populations(lastYear-firstYear + 1, 0);
        int mostPopular = 0;

        while (std::getline(data, nextline))
        {
            tEntry next;

            vector<string> line = tokenize(nextline.c_str(), ';');
            next.name  = line[0];
            next.birth = line[1];
            next.death = line[2];
            
            sscanf(next.birth.c_str(), "%d/%d/%d", &next._birth.month,&next._birth.day,&next._birth.year );
            sscanf(next.death.c_str(), "%d/%d/%d", &next._death.month,&next._death.day,&next._death.year );

            for (int age = next._birth.year; age <= next._death.year; age++)
            {
                populations[age - firstYear]++;

                if (populations[age - firstYear] > mostPopular)
                {
                    mostPopular = populations[age - firstYear];
                }
            }

            dataSet.push_back(next);
        }

        printf("The year(s) with the most people were alive: \n\t");
        for (int yr=firstYear; yr<=lastYear; yr++)
        {
            //printf("%d: %d\n ", yr, populations[yr-firstYear]);
            if ( populations[yr-firstYear] == mostPopular)
                printf("%d ", yr);
        }

        printf("\n\nThe population: %d persons\n", mostPopular);

    }

    data.close();

	return 0;
}

