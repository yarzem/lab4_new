// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <iostream>
#include <boost/filesystem.hpp>
#include <string.h>
#include <map>
 #include <string>
using boost::filesystem::path;
using boost::filesystem::directory_entry;
using std::map;
struct characteristics
{
    std::string _owner;
    std::string _date;
    int _count;
    characteristics()
    {}
    characteristics(std::string owner , std::string date , int count):
    _owner(owner) , _date(date) , _count(count)
    {}
};
static  map <std::string, struct characteristics> checker{};
static  map<std::string , int > base{};
class otchet
{
public:
    std::string _account = "";
    std::string _date;
    std::string _owner;
    path _start{"/home/sergei/Desktop/testdir"};
    bool check_for_delimiter(char str)
    {
        if (str != '_')
        {return false;}
        return true;
    }
    bool check_for_num(char str)
    {
        if ((str >= '0') && (str <= '9'))
        {return true;}
        else
        {return false;}
    }
    bool check_extension(const std::string& str)
    {
        if (str ==".txt")
        {
            return true;
        }
        return false;
    }
    bool check_day(const std::string& str)
    {
        if (str >= "01" && str <= "31"){ return true;}
        return false;
    }
    bool check_year(const std::string& str)
    {
        if (str >= "1000" && str <= "2019"){return true;}
        return false;
    }
    bool check_month(const std::string& str)
    {
        if ((str >= "01") && (str <= "12")){ return true;}
        return false;
    }

    bool check_format(const std::string& str)
    {
        if (str.find("balance_") != 0)
        {
            return false;
        } else {
            int counter = str.find("balance_") + strlen("balance_");
            if (check_for_delimiter(str[counter-1]) == false)
            {
                return false;
            }
            for (int i = 0; i < 8; ++i)
            {
                if (check_for_num(str[counter+i]) == false){ return false;}
                _account += str[counter+i];
            }
            counter += 9;
            if (check_for_delimiter(str[counter-1]) == false)
            {
                return false;
            }
            if (check_year(str.substr(counter , 4)) == false)
            {
                return false;
            }
            counter += 4;
            if (check_month(str.substr(counter , 2)) == false)
            {
                return false;
            }
            counter += 2;
            if (check_day(str.substr(counter , 2)) == false)
            {
                return false;
            }
            counter += 2;
            if (check_extension(str.substr(counter , 4)) == false)
            {
                return false;
            }
            counter += 4;
            if (str.find(".txt") != (str.length() - 4))
            {
                return false;
            }
            return true;
        }
    }

    void read_dir(const path& p1)
    {
        for (const directory_entry& x : directory_iterator{p1})
        {
            if (is_directory(x) == true)
            {
                std::string str = boost::filesystem::path(x.path()).string();
                read_dir(x.path());
            }
            if (is_symlink(x))
            {
                path tmp = read_symlink(x);
            }
            if (is_regular_file(x) == true)
            {
                if (check_format(boost::filesystem::basename
                (x.path().filename())
                + boost::filesystem::extension
                (x.path().extension()))
                == true)
                {
                    _owner =
                    boost::filesystem::path
                    (x.path().string()).parent_path().filename().string();
                    if (checker.find(_account) != checker.end())
                    {
                        ++checker[_account]._count;
                        if (checker[_account]._date < _date)
                        {
                            checker[_account]._date = _date;
                            checker[_account]._owner = _owner;
                        }
                    } else {
                        struct characteristics a(_owner , _date , 1);
                        checker.insert({_account , a});
                    }
                    std::cout <<
                              x.path() <<
                              " " <<
                              _account<<
                              " "<<
                              checker[_account]._owner<<
                              " "<<
                              checker[_account]._date<<
                              " "<<
                              checker[_account]._count<<
                              std::endl;
                    _account = "";
                }
            }
        }
    }
};

#endif // INCLUDE_HEADER_HPP_
