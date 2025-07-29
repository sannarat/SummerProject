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
	~HashTable();

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
	
	void relocate();

	std::vector<Node*> buckets;
	size_t size_;
	size_t capacity_;
};

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t capacity) : buckets(capacity, nullptr), size_(0), capacity_(capacity) {}

template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable() {
	for (Node* node : buckets) {
		Node* delete_ = node;
		node = node->next_;
		delete delete_;
	}
}

template<typename Key, typename Value>
void HashTable<Key, Value>::insert(const Key& key, const Value& value)
{
	while (size_ >= capacity_ * 0.75) relocate();

	int index = hashFunction(key) % size_;

	Node* current_item = buckets[index];

	if (current_item != nullptr && current_item->key_ == key) {
		current_item->value_ = value;
		return;
	}

	while (current_item != nullptr) {
		if (current_item->key_ == key) {
			current_item->value_ = value;
			return;
		}
		current_item = current_item->next_;
	}
	
	buckets[index] = new Node(key, value, buckets[index]);
	size_++;
	
}

template<typename Key, typename Value>
inline size_t HashTable<Key, Value>::size() const
{
	return size_;
}

template<typename Key, typename Value>
inline size_t HashTable<Key, Value>::capacity() const
{
	return capacity_;
}

template<typename Key, typename Value>
inline bool HashTable<Key, Value>::empty() const
{
	return (size_ == 0);
}

template<typename Key, typename Value>
inline bool HashTable<Key, Value>::is_full() const
{
	return (size_ == capacity_);
}
