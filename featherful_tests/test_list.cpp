

#include "test_list.hpp"

#include "../featherful.hpp"

using featherful::test_results;
using featherful::list;


bool test_list()
{
    test_results list_tests("all list tests");
    list_tests.result(test_basic());

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

