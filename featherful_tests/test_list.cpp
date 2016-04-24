

#include "test_list.hpp"

#include "../featherful.hpp"

using featherful::test_results;
using featherful::list;


bool test_list()
{
    test_results list_tests("all list tests");
    list_tests.result(test_basic());
    list_tests.result(test_map());
    list_tests.result(test_filter());

    list_tests.finish();
    return list_tests.is_successful();
}


bool test_basic()
{

    test_results results("basic list tests");

    list<int> list1;
    list1.push(new int(5));
    list1.push(new int(15));
    list1.push(new int(25));

    TEST(results, list1.length() == 3);
    TEST(results, list1.pop() == 25);
    TEST(results, list1.shift() == 5);
    TEST(results, list1.shift() == 15);
    TEST(results, list1.length() == 0);


    list<int> list2;
    list2.push(new int(5));
    list2.push(new int(15));
    list2.push(new int(25));

    list<int>::iterator iter = list2.begin();
    TEST(results, *(iter++) == 5);
    TEST(results, *(iter++) == 15);
    TEST(results, *(iter--) == 25);
    TEST(results, *(iter--) == 15);
    TEST(results, *(iter--) == 5);

    TEST(results, *(list2.begin() + 1) == 15);
    TEST(results, *(list2.begin() + 2) == 25);
    TEST(results, list2[1] == 15);
    TEST(results, list2[2] == 25);
    TEST(results, list2[0] == 5);
    TEST(results, list2[-1] == 25);
    TEST(results, list2[-2] == 15);
    TEST(results, list2[-3] == 5);
    TEST_THROW(results, list2[-4] == 0, featherful::range_exception);
    TEST_THROW(results, list2[3] == 0, featherful::range_exception);


    results.finish();

    return results.is_successful();
}





int* decrease_int(const int& val)
{
    return new int(val - 5);
}

class int_decreaser : public featherful::list_mapper<int, int>
{
public:
    int_decreaser(int amount) : amount(amount)
    {}
    int* map(const int& val)
    {
        return new int(val - this->amount);
    }
private:
    const int amount;
};

class int_selector : public featherful::list_filterer<int>
{
public:
    int_selector(int amount) : amount(amount)
    {}
    bool filter(const int& val)
    {
        return val > this->amount;
    }
private:
    const int amount;
};

bool test_map()
{
    test_results results("list mapping tests");

    list<int> list1;
    list1.push(new int(10));
    list1.push(new int(20));
    list1.push(new int(30));

    list<int> list1mapped = list1.map(decrease_int);
    TEST(results, list1mapped[0] == 5);
    TEST(results, list1mapped[1] == 15);
    TEST(results, list1mapped[2] == 25);
    TEST(results, list1[0] == 10);
    TEST(results, list1[1] == 20);
    TEST(results, list1[2] == 30);


    list1mapped = list1.map(int_decreaser(6));
    TEST(results, list1mapped[0] == 4);
    TEST(results, list1mapped[1] == 14);
    TEST(results, list1mapped[2] == 24);
    TEST(results, list1[0] == 10);
    TEST(results, list1[1] == 20);
    TEST(results, list1[2] == 30);

    list1.map_inplace(int_decreaser(7));
    TEST(results, list1[0] == 3);
    TEST(results, list1[1] == 13);
    TEST(results, list1[2] == 23);

    list1.map_inplace(int_decreaser(3));
    TEST(results, list1[0] == 0);
    TEST(results, list1[1] == 10);
    TEST(results, list1[2] == 20);

    results.finish();

    return results.is_successful();
}


bool test_filter()
{
    test_results results("list filtering tests");

    list<int> list1;
    list1.push(new int(10));
    list1.push(new int(20));
    list1.push(new int(30));
    list1.push(new int(40));
    list1.push(new int(45));

    TEST(results, list1.all(int_selector(5)));
    TEST(results, ! list1.all(int_selector(55)));
    TEST(results, list1.notall(int_selector(15)));
    TEST(results, ! list1.notall(int_selector(0)));
    TEST(results, list1.none(int_selector(60)));
    TEST(results, ! list1.none(int_selector(43)));
    TEST(results, list1.any(int_selector(42)));
    TEST(results, ! list1.any(int_selector(60)));

    list<int> filtered = list1.filter(int_selector(25));
    TEST(results, filtered.length() == 3);
    TEST(results, filtered[0] == 30);
    TEST(results, filtered[1] == 40);
    TEST(results, filtered[2] == 45);
    TEST(results, list1.length() == 5);

    list1.filter_inplace(int_selector(35));
    TEST(results, list1.length() == 2);
    TEST(results, list1[0] == 40);
    TEST(results, list1[1] == 45);

    results.finish();

    return results.is_successful();
}





