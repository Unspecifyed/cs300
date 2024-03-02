#ifndef HASHMAP_H
#define HASHMAP_H

#include <cstddef>
#include <functional>
#include <list>
#include <utility>
#include <vector>
/**
 * Hashes the given key using std::hash.
 *
 * @param key the key to be hashed
 *
 * @return the hash value of the key
 */
template <typename KeyType> struct SimpleHash {
  size_t operator()(const KeyType &key) const {
    return std::hash<KeyType>{}(key);
  }
};

template <typename KeyType, typename ValueType>
struct HashEntry : public std::pair<KeyType, ValueType> {
  using std::pair<KeyType, ValueType>::pair;
};

template <typename KeyType, typename ValueType,
          typename Hash = SimpleHash<KeyType>>
class HashMap {
private:
  using Entry = HashEntry<KeyType, ValueType>;
  using Bucket = std::list<Entry>;
  std::vector<Bucket> buckets;
  Hash hashFunction;

public:
  using Iterator = typename Bucket::iterator;
  using ConstIterator = typename Bucket::const_iterator;

  HashMap(size_t size = 100) : buckets(size) {}
  /**
   * Inserts a key-value pair into the data structure.
   *
   * @param key the key to be inserted
   * @param value the value to be inserted
   *
   * @return void
   */
   void insert(const KeyType &key, const ValueType &value) {
    size_t index = hashFunction(key) % buckets.size();
    for (auto &entry : buckets[index]) {
      if (entry.first == key) {
        entry.second = value;
        return;
      }
    }
    buckets[index].emplace_back(key, value);
  }

  ValueType &operator[](const KeyType &key) {
    size_t index = hashFunction(key) % buckets.size();
    for (auto &entry : buckets[index]) {
      if (entry.first == key) {
        return entry.second;
      }
    }
    buckets[index].emplace_back(key, ValueType());
    return buckets[index].back().second;
  }

  const ValueType &operator[](const KeyType &key) const {
    size_t index = hashFunction(key) % buckets.size();
    for (const auto &entry : buckets[index]) {
      if (entry.first == key) {
        return entry.second;
      }
    }
    static ValueType defaultValue;
    return defaultValue;
  }
  /**
   * Checks if the given key is present in the data structure.
   *
   * @param key the key to check for
   *
   * @return true if the key is present, false otherwise
   *
   * @throws None
   */
  bool contains(const KeyType &key) const {
    size_t index = hashFunction(key) % buckets.size();
    for (const auto &entry : buckets[index]) {
      if (entry.first == key) {
        return true;
      }
    }
    return false;
  }
  /**
   * Returns the size of the data structure.
   *
   * @return the size of the data structure
   */
  size_t size() const {
    size_t size = 0;
    for (const auto &bucket : buckets) {
      size += bucket.size();
    }
    return size;
  }

  ConstIterator begin() const { return buckets.front().begin(); }

  ConstIterator end() const { return buckets.back().end(); }
};

#endif // HASHMAP_H
