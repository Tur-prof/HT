#pragma once
#include <string>
#include "SHA1.h"

enum PairStatus { empty, engaged, deleted };

struct Pair
{
	PairStatus status;
	char* key;
	uint* value;

	Pair()noexcept;
};

class HashTable final
{
private:
	size_t _capacity;
	size_t _size;
	Pair* _array;

	size_t hash(const char*, const size_t)const noexcept;
	void resize();

public:
	HashTable(const size_t = 10);
	~HashTable();

	void add(const char*, const uint*);
	uint* find(const char*)const noexcept;
	void remove(const char*);
	size_t size()const noexcept;
};
