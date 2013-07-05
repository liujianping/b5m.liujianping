/**
 * @file  strutil.h
 * @brief Definition of the strutil interfaces
 */
#ifndef STRUTIL_H
#define	STRUTIL_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>  
using namespace std;

/**
 * namespace strutil
 * @brief A string utility collection
 */
namespace strutil
{

/**
* @brief trim the string
*/
string trim(const string& str)
{
    string::size_type pos = str.find_first_not_of(' ');
    if (pos == string::npos)
    {
        return str;
    }
    string::size_type pos2 = str.find_last_not_of(' ');
    if (pos2 != string::npos)
    {
        return str.substr(pos, pos2 - pos + 1);
    }
    return str.substr(pos);
}

/**
* @brief split the string by the delimeter
*/
int split(const string& str, vector<string>& ret_, string sep = ",")
{
    if (str.empty())
    {
        return 0;
    }

    string tmp;
    string::size_type pos_begin = str.find_first_not_of(sep);
    string::size_type comma_pos = 0;

    while (pos_begin != string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        //if (!tmp.empty())
        //{
            ret_.push_back(tmp);
            tmp.clear();
        //}
    }
    return 0;
}

}


#endif	/* STRUTIL_H */

