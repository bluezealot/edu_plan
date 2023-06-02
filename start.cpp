#include<iostream>
#include <list>
#include <iterator>

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
    {}

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

    void add_course(course* one)
    {
        courses.push_back(one);
        points += one->get_points();
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
    void add_course(term* one)
    {
        terms.push_back(one);
    }
};

int main()
{
    cout << "hello my dear";
}