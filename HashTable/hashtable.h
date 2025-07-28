#pragma once

#include<vector>
#include<string>
#include<optional>

template<typename Key>
class HashTraits {
	static size_t hash(const Key& key, const size_t capacity);
};

template<>
class HashTraits<int> {
	static size_t hash(const int& key, const size_t capacity);
};

template<>
class HashTraits<std::string> {
	static size_t hash(const std::string& key, const size_t capacity);
};

template <typename Key, typename Value>
class HashTable {
public:

	HashTable(size_t capacity);
	~HashTable() = default;

	void insert(const Key& key, const Value& value);
	std::optional<Value> find(const Key& key) const;
	std::optional<Value> erase(const Key& key);

	size_t size() const;
	size_t capacity() const;
	bool empty() const;
	bool is_full() const;

private:

	size_t hashFunction(const Key& key) const;  // return HashTraits<Key>::hash(key, buckets.size());

	class Node {
	public:

		Node(const Key& key, const Value& value, Node* next) : key_(key), value_(value), next_(next) {}

	private:

		Key key_;
		Value value_;
		Node* next_;
	};

	std::vector<Node*> buckets;
	size_t size_;
	size_t capacity_;
};