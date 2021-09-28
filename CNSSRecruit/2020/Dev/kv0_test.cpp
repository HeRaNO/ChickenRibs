#include <string>
#include <cassert>

bool get(std::string key, std::string *value);
bool set(std::string key, std::string value);

int main(int argc, char const *argv[]) {
	set("key1", "value1");
	set("key2", "value2");

	std::string res;
	assert(get("key1", &res) == true);
	assert(res == "value1");

	assert(get("key3", &res) == false);
	assert(res == "");

	set("key2", "123");
	assert(get("key1", &res) == true);
	assert(res == "value1");
	assert(get("key2", &res) == true);
	assert(res == "123");

	set("key3", "114514");
	assert(get("key3", &res) == true);
	assert(res == "114514");
	return 0;
}