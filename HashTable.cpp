#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include "HashTable.h"
#include "SHA1.h"

Pair::Pair()noexcept :status(empty), key(nullptr), value(nullptr)
{
}

HashTable::HashTable(const size_t size) :_capacity(size), _size(0)
{
	_array = new Pair[size];
}

HashTable::~HashTable()
{
	for (size_t i = 0; i < _capacity; ++i)
	{
		if ((_array + i)->status == engaged)
		{
			delete[](_array + i)->key;
			delete[](_array + i)->value;
		}
	}

	delete[] _array;
}

size_t HashTable::hash(const char* key, const size_t offset)const noexcept
{
	size_t product = 1;
	while (*key)
	{
		product *= *(key++);
	}

	return (product % _capacity + offset * offset) % _capacity;
}

void HashTable::resize()
{
	size_t oldCapacity = _capacity;
	Pair* oldArray = _array;
	_capacity *= 2;
	_size = 0;

	_array = new Pair[_capacity];

	for (size_t i = 0; i < oldCapacity; ++i)
	{
		if ((oldArray + i)->status == engaged)
		{
			add((oldArray + i)->key, (oldArray + i)->value);
			delete[](oldArray + i)->key;
			delete[](oldArray + i)->value;
		}
	}

	delete[] oldArray;
}

void HashTable::add(const char* key, const uint* value)
{
	for (size_t i = 0; i < _capacity; ++i)
	{
		size_t index = hash(key, i);

		if ((_array + index)->status != engaged)
		{
			(_array + index)->status = engaged;
			(_array + index)->key = new char[strlen(key) + 1];
			strcpy((_array + index)->key, key);
			(_array + index)->value = new uint[SHA1HASHLENGTHUINTS];
			memcpy((_array + index)->value, value, SHA1HASHLENGTHBYTES);
			++_size;
			return;
		}
	}

	resize();
	add(key, value);
}

uint* HashTable::find(const char* key)const noexcept
{
	for (size_t i = 0; i < _capacity; ++i)
	{
		size_t index = hash(key, i);

		if ((_array + index)->status == empty)
		{
			return nullptr;
		}

		if ((_array + index)->status == engaged && !strcmp(key, (_array + index)->key))
		{
			return (_array + index)->value;
		}
	}
	return nullptr;
}

void HashTable::remove(const char* key)
{
	for (size_t i = 0; i < _capacity; ++i)
	{
		size_t index = hash(key, i);

		if ((_array + index)->status == empty)
		{
			return;
		}

		if ((_array + index)->status == engaged && !strcmp(key, (_array + index)->key))
		{
			delete[](_array + index)->key;
			delete[](_array + index)->value;
			(_array + index)->status = deleted;
			--_size;
		}
	}
}

size_t HashTable::size()const noexcept
{
	return _size;
}
