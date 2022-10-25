#pragma once

#include <unordered_map>
#include <vector>

#include <cstdint>

namespace Alpha {

	template <typename key, typename type>
	class DenseMap {
		using MapType = std::pair<key, type>;
	public:

		MapType& insert_or_do_nothing(key Key, type& item) {
			if (map.find(Key) != map.end()) {
				return stored[map[Key]];
			}
			MapType data(Key, item);
			map[Key] = last_index++;
			stored.push_back(data);
			return data;
		}

		MapType& insert_or_replace(key Key, type& item) {
			MapType data = { Key, item };
			map[Key] = last_index++;
			stored.push_back(data);
			return data;
		}

		key& preserve(key Key) {
			if (map.find(Key) != map.end()) {
				return Key;
			}
			MapType data = { Key, {} };
			map[Key] = last_index++;
			stored.push_back(data);
			return Key;
		}

		bool contain(key Key) {
			return map.find(Key) != map.end();
		}

		auto find(key Key) {
			return begin() + map.find(Key);
		}

		size_t size() {
			return stored.size();
		}

		void clear() {
			stored.clear();
			map.clear();
		}

		void erase(key Key) {
			if (!contain(Key))
				return;
			stored.erase(begin() + map[Key]);
			map.erase(Key);
			last_index--;
		}

		type& operator [](key Key) {
			return stored[map[Key]].second;
		}

		typename std::vector<MapType>::iterator begin() { return stored.begin(); }

		typename std::vector<MapType>::iterator end() { return stored.end(); }


	private:

		std::vector<MapType> stored;
		std::unordered_map<key, uint32_t> map;
		uint32_t last_index = 0;
	};
}