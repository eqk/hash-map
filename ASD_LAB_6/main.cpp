#include "HashMap.h"
#include <string>
#include <cassert>

void test()
{
	HashMap<int, std::string> hmap;
	for (int i = 0; i < TABLE_SIZE / 2; ++i)
	{
		hmap.put(i, std::to_string(rand() % 100));
	}
}

int main()
{
	HashMap<int, std::string> hmap;

	hmap.put(1, "val1");
	hmap.put(2, "val2");
	hmap.put(3, "val3");

	std::string s;

	assert(hmap.get(3, s));
	assert(s == "val3");
	assert(!hmap.get(5, s));

	test();
}