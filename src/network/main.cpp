#include "Network.h"
#include <iostream>
#include <cassert>
#include "json.hpp"

int main()
{
    Network net;
    net.updateFile("test", "test1", "data.json");

    assert(net.readJson()["test"] == "test1");

    net.deleteFromFile("test");

    assert(net.readJson()["test"] != "test1");

    net.updateFile("test", "test2", "data.json");

    json A = net.readJson("data.json");

    json B = net.readJson("data.json");

    assert(A == B);

    net.putbraks("data2.json");

    net.updateFile("test", "test3", "data2.json");

    net.deleteFromFile("test");

    net.mergeJson("data2.json", "data.json");

    json C = net.readJson("data.json");

    json D = net.readJson("data2.json");

    assert(A == B);

    return 0;
}
