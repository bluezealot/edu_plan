#include <iostream>
#include <list>
#include <iterator>
#include <map>
#include <fstream>

using namespace std;

class course
{
    private:
    string identity;
    int points;
    list<course*> predecessors;

    public:
    int get_points()
    {
        return points;
    }

    string get_id()
    {
        return identity;
    }
    void add_pre(course* aCourse)
    {
        predecessors.push_back(aCourse);
    }

    int get_pre_count()
    {
        return predecessors.size();
    }

    course* get_pre_at(int index)
    {
        auto l_front = predecessors.begin();
        std::advance(l_front, index);
        return *l_front;
    }

    void remove_pre(course* aCourse)
    {
        predecessors.remove(aCourse);
    }

    course(string paramId, int paramP)
    {
        identity = paramId;
        points = paramP;
    }

    ~course()
    {
        
    }

    list<course*> getPre()
    {
        return predecessors;
    }

};

class term
{
    private:
    list<course*> courses;
    int points;
    int point_limit;
    int avg_course_count;

    public:
    term(int param_plimit, int param_acc)
    {
        points = 0;
        point_limit = param_plimit;
        avg_course_count = param_acc;
    }

    ~term()
    {
        for(course* c1 : courses)
        {
            delete c1;
        }
    }

    bool add_course(course* one)
    {
        courses.push_back(one);
        points += one->get_points();
        return true;
    }

    int sum_points()
    {
        int ret = 0;
        for(course* c1 : courses)
        {
            ret += c1->get_points();
        }
        return ret;
    }
};

class plan
{
    private:
    list<term*> terms;

    public:
    void add_term(term* one)
    {
        terms.push_back(one);
    }

    list<term*> GetTerms()
    {
        return terms;
    }
};

// for string delimiter
std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

bool doplan(int term_count, int max_point, int mode, map<string, course*> courseMap)
{
    plan p;
    for(int i = 0; i < term_count; i ++)
    {
        int acc = 0;
        if(mode == 2)
        {
            acc = -1;
        }
        else
        {
            acc = courseMap.size()/term_count;
        }
        term* tm = new term(max_point, acc);
        p.add_term(tm);
    }
    list<course*> arrangedList;
    
    for(term* aTerm:p.GetTerms())
    {
        term* currentTerm = aTerm;
        for (auto const& [key, val] : courseMap)
        {
            if(val->get_pre_count() == 0)
            {
                
            }
        }
    }
    return true;
}

bool IsArranged(list<course*> arrangedList, list<course*> testTarget)
{
    bool arranged = true;
    for(course* aTest:testTarget)
    {
        arranged = arranged && (std::find(arrangedList.begin(), arrangedList.end(), aTest) != arrangedList.end());
    }
    return arranged;
}

course* GetNextAddable(list<course*> arrangedList, map<string, course*> courseMap)
{
    course* result = NULL;
    for (auto const& [key, val] : courseMap)
    {
        bool arranged = (std::find(arrangedList.begin(), arrangedList.end(), val) != arrangedList.end());
        if(!arranged)
        {
            if(IsArranged(arrangedList, val->getPre()))
            {
                result = val;
                break;
            }
        }
    }
    return result;
}

void loadtestparam()
{
    ifstream infile("test.txt");
    string term_count_line;
    getline(infile, term_count_line);
    int term_count = stoi(term_count_line);

    string max_points_line;
    getline(infile, max_points_line);
    int max_points= stoi(max_points_line);

    string mode_line;
    getline(infile, mode_line);
    int mode= stoi(mode_line);
    map<string, course*> courseMap;
    std::map<string, course*>::iterator it = courseMap.begin();
    while(true)
    {
        string courseNo;
        getline(infile, courseNo);
        if(courseNo=="#")
        {
            break;
        }

        string points_line;
        getline(infile, points_line);
        int points = stoi(points_line);

        string strPredecessors;
        getline(infile, strPredecessors);

        course* aCourse = new course(courseNo, points);
        if(strPredecessors.length() > 0)
        {
            vector<std::string> parents = split(strPredecessors, ",");
            bool inCorrectPredecessor = false;
            for(string p : parents)
            {
                cout << "Looking for " << p << endl;
                if(courseMap.count(p) <= 0)
                {
                    //Not exist
                    inCorrectPredecessor = true;
                    cout << "Cannot set not exsit course as predecessor. Course number:" << p << endl;
                    break;
                }
                else
                {
                    aCourse->add_pre(courseMap[p]);
                }
            }
            if(inCorrectPredecessor)
            {
                continue;
            }
        }
        cout << "insert " << courseNo << endl;
        courseMap.insert(it, pair<string, course*>(courseNo,aCourse));
    }
    doplan(term_count, max_points, mode, courseMap);
}

int main()
{
    loadtestparam();
    // int term_count;
    // int max_points;
    // int mode;
    // cout << "Hello, welcome to term plan system." << endl;
    // cout << "Please input term count:" << endl;
    // cin >> term_count;
    // cout << "Please input the maximum point per term:" << endl;
    // cin >> max_points;
    // cout << "Please input the plan mode:" << endl;
    // cin >> mode;
    // cout << "From now on, please input the course information. After you finish the input please type # as the course number to end this procedure." << endl;
    // map<string, course*> courseMap;
    // std::map<string, course*>::iterator it = courseMap.begin();
    // while(true)
    // {
    //     string courseNo;
    //     int points;
    //     string strPredecessors;
    //     string predecessors;
    //     cout << "Please input the course number:" << endl;
    //     cin >> courseNo;
    //     cout << "Please input the course points:" << endl;
    //     cin >> points;
    //     cout << "Please input the course predecessors' number (if no predecessor push enter to skip, if it has multi predecessors split them by comma.):" << endl;
    //     cin >> strPredecessors;
    //     course aCourse(courseNo, points);
    //     if(strPredecessors.length() > 0)
    //     {
    //         vector<std::string> parents = split(strPredecessors, ",");
    //         bool inCorrectPredecessor = false;
    //         for(string p : parents)
    //         {
    //             if(courseMap.find(p) == courseMap.end())
    //             {
    //                 //Not exist
    //                 inCorrectPredecessor = true;
    //                 cout << "Cannot set not exsit course as predecessor. Course number:" << p << endl;
    //                 break;
    //             }
    //             else
    //             {
    //                 aCourse.add_pre(courseMap[p]);
    //             }
    //         }
    //         if(inCorrectPredecessor)
    //         {
    //             continue;
    //         }
    //     }
    //     courseMap.insert(it, pair<string, course*>(courseNo,&aCourse));
    // }// end of input
    // cout << "Term count:" << term_count << " Maximum points:" << max_points;
}