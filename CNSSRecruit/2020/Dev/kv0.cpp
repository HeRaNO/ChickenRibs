#include <string>
#include <unordered_map>

// Potential risk on hash function
std::unordered_map <std::string, std::string> mp;

bool get(std::string key, std::string *value) {
	auto it = mp.find(key);
	if (it == mp.end()) {
		*value = "";
		return false;
	}
	*value = it -> second;
	return true;
}

bool set(std::string key, std::string value) {
	mp[key] = value;
	return true;
}
