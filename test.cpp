#include <cassert>       // for assert
#include <iostream>      // for std::cout (optional logging)
#include <algorithm>     // for std::find_if
#include <vector>
#include "include/CircularContainer.hpp"

/**
 * A simple struct to test non-trivial objects in CircularContainer.
 */
struct Person {
    std::string name;
    int age;

    // For demonstration: define a simple operator<
    bool operator<(const Person &other) const {
        return this->age < other.age;
    }

    // Possibly define == for tests
    bool operator==(const Person &other) const {
        return (this->name == other.name) && (this->age == other.age);
    }
};

int main()
{
    using namespace vfc;

    // 1) Test with basic int container
    constexpr std::size_t CAP = 5;
    CircularContainer<int, CAP> c;
    assert(c.size() == 0);
    assert(c.capacity() == CAP);
    assert(c.empty());

    // push_back some elements
    c.push_back(10);
    assert(c.size() == 1 && !c.empty());
    c.push_back(20);
    c.push_back(30);
    c.push_back(40);
    c.push_back(50);
    // container is now full => size=5
    assert(c.size() == 5);
    assert(c.full());

    // Overfill => the logic in push_back overwrites oldest
    c.push_back(60);
    // size remains 5, but the "front" is now 20 (10 overwritten)
    assert(c.size() == 5);
    assert(c.front() == 20);
    // back() is the last inserted => 60
    assert(c.back() == 60);

    // pop_front => remove front (20)
    c.pop_front();
    assert(c.size() == 4 && !c.empty());
    assert(c.front() == 30);

    // 2) Insert at begin (with container partially full)
    // c: front=30, contains [30,40,50,60], size=4
    c.insert(c.begin(), 99);
    // If container wasn't full => size is now 5
    assert(c.size() == 5);
    // The new front is 99
    assert(c.front() == 99);

    // 3) Test forward iteration
    {
        int count = 0;
        for (auto it = c.begin(); it != c.end(); ++it) {
            count++;
        }
        assert(count == 5);
    }

    // 4) Test reverse iteration
    {
        int count = 0;
        for (auto it = c.rbegin(); it != c.rend(); ++it) {
            count++;
        }
        assert(count == 5);
    }
    // Test const_reverse_iterator
    {
        vfc::CircularContainer<int, 5> c2;
        c2.push_back(1);
        c2.push_back(2);
        c2.push_back(3);
        c2.push_back(4);
        c2.push_back(5);

        const auto &rc2 = c2;
        int count = 0;
        for (auto crit = rc2.crbegin(); crit != rc2.crend(); ++crit) {
            count++;
        }
        assert(count == 5);
    }

    // 5) Clear
    c.clear();
    assert(c.size() == 0 && c.empty());

    // 6) Test pushing up to capacity again
    for (int i = 1; i <= 5; ++i) {
        c.push_back(i * 10);
    }
    // c: [10,20,30,40,50], size=5, front=10, back=50
    assert(c.full());
    // remove 2
    c.pop_front();
    c.pop_front(); // now c: [30,40,50], size=3

    // 7) Insert in the middle
    // container [30,40,50], let's insert 99 before '50'
    auto itPos = ++(c.begin()); // points to 40
    ++itPos;                    // now points to 50
    c.insert(itPos, 99);
    // c => [30,40,99,50], size=4
    assert(c.size() == 4);

    // 8) Range-based for iteration
    {
        int sum = 0;
        for (auto &val : c) {
            sum += val;
        }
        // c has [30,40,99,50] => sum=219
        assert(sum == 219);
    }

    // 9) Test with a custom struct
    CircularContainer<Person, 3> people;
    // fill
    people.push_back(Person{"Alice", 30});
    people.push_back(Person{"Bob",   25});
    people.push_back(Person{"Cara",  40});
    assert(people.size() == 3 && people.full());
    // Overfill => push back "Dan", oldest ("Alice") is overwritten
    people.push_back(Person{"Dan", 35});
    assert(people.size() == 3);
    // front => was "Bob" after overwriting "Alice"
    assert(people.front().name == "Bob");

    // pop_front => remove "Bob"
    people.pop_front();
    assert(people.size() == 2);
    assert(people.front().name == "Cara"); // next oldest

    // check iteration
    {
        int cnt = 0;
        for (auto &p : people) {
            cnt++;
            // we can read & mutate as needed
        }
        assert(cnt == 2);
    }

    // 10) Use brace-initialization
    // e.g. CircularContainer<int,3> x{1,2,3} etc.
    CircularContainer<int,5> c2{1,2,3,4,5};
    assert(c2.size() == 5);
    // Overfill => push_back(6) overwrites oldest
    c2.push_back(6);
    // size still 5, front is 2, back is 6
    assert(c2.front() == 2);
    assert(c2.back() == 6);

    // 11) Check cbegin(), cend()
    {
        const auto &rc2 = c2;
        int count = 0;
        for (auto cit = rc2.cbegin(); cit != rc2.cend(); ++cit) {
            count++;
        }
        assert(count == 5);
    }

    // 12) Find an element with std::find_if
    {
        // c2 has [2,3,4,5,6] in some ring arrangement
        // let's look for "4"
        auto found = std::find_if(c2.begin(), c2.end(), [](int x){ return x == 4; });
        assert(found != c2.end() && "Should find 4 in the container");
        assert(*found == 4);
    }

    // Additional test cases
    {
        // Test insert at the end
        CircularContainer<int, 5> c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(3);
        c.insert(c.end(), 99);
        assert(c.size() == 4);
        assert(c.back() == 99);
    }

    {
        // Test insert into an empty container
        CircularContainer<int, 5> c;
        c.insert(c.begin(), 99);
        assert(c.size() == 1);
        assert(c.front() == 99);
        assert(c.back() == 99);
    }

    {
        // Test insert into a full container
        CircularContainer<int, 3> c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(3);
        c.insert(c.begin(), 99);
        assert(c.size() == 3);
        assert(*c.begin() == 99);
        assert(c.front() == 99);
        assert(c.back() == 2);
    }

    {
        // Test pop_front on an empty container
        CircularContainer<int, 5> c;
        c.pop_front();
        assert(c.size() == 0);
        assert(c.empty());
    }

    {
        // Test front and back on an empty container
        CircularContainer<int, 5> c;
        try {
            c.front();
            assert(false && "front() on empty container should throw!");
        } catch (const std::out_of_range& e) {
            // Expected behavior
        }

        try {
            c.back();
            assert(false && "back() on empty container should throw!");
        } catch (const std::out_of_range& e) {
            // Expected behavior
        }
    }

    {
        // Test emplace_back with move semantics
        CircularContainer<std::string, 3> c;
        std::string s1 = "Hello";
        std::string s2 = "World";
        c.emplace_back(std::move(s1));
        c.emplace_back(std::move(s2));
        assert(c.size() == 2);
        assert(c.front() == "Hello");
        assert(c.back() == "World");
        assert(s1.empty());
        assert(s2.empty());
    }

    {
        // Test clear on a full container
        CircularContainer<int, 3> c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(3);
        c.clear();
        assert(c.size() == 0);
        assert(c.empty());
    }

    {
        // Test operator== and operator!= for iterators
        CircularContainer<int, 5> c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(3);
        auto it1 = c.begin();
        auto it2 = c.begin();
        assert(it1 == it2);
        ++it2;
        assert(it1 != it2);
    }

    {
        // Test operator-- on iterators
        CircularContainer<int, 5> c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(3);
        auto it = c.end();
        --it;
        assert(*it == 3);
        --it;
        assert(*it == 2);
        --it;
        assert(*it == 1);
    }

    {
        // Test operator++ on reverse iterators
        CircularContainer<int, 5> c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(3);
        auto rit = c.rbegin();
        assert(*rit == 3);
        ++rit;
        assert(*rit == 2);
        ++rit;
        assert(*rit == 1);
    }

    {
        // Test operator-- on reverse iterators
        CircularContainer<int, 5> c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(3);
        auto rit = c.rend();
        --rit;
        assert(*rit == 1);
        --rit;
        assert(*rit == 2);
        --rit;
        assert(*rit == 3);
    }

    {
        // Test std::sort with iterators
//        CircularContainer<int, 5> c;
//        c.push_back(3);
//        c.push_back(1);
//        c.push_back(2);
//        std::sort(c.begin(), c.end());
//        assert(c.front() == 1);
//        assert(c.back() == 3);
    }

    {
        // Test std::find with iterators
        CircularContainer<int, 5> c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(3);
        auto found = std::find(c.begin(), c.end(), 2);
        assert(found != c.end());
        assert(*found == 2);
    }

    {
        // Test std::copy with iterators
        CircularContainer<int, 5> c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(3);
        std::vector<int> v;
        std::copy(c.begin(), c.end(), std::back_inserter(v));
        assert(v.size() == 3);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 3);
    }
    std::cout << "All tests passed!\n";
    return 0;
}
