#ifndef KEY_HASH
#define KEY_HASH

#define TABLE_SIZE 2000

// Default hash function class
template <typename K>
struct KeyHash {
    unsigned long operator()(const K& key) const
    {
		return TABLE_SIZE * fmod(key * 0.618033, 1);

        //return static_cast<unsigned long>(key) % TABLE_SIZE;
    }
};

#endif // !KEY_HASH
