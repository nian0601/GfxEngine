#pragma once

#include "GrowingArray.h"
#include <string>
#include "CommonHelper.h"

namespace CU
{
	template<typename Key, typename Value, int StartSize = 67, int BucketSize = 3>
	class Map
	{
	public:
		Map();
		~Map();

		void Insert(const Key &aKey, const Value &aValue);
		Value& Get(const Key &aKey); //Assert om key inte finns
		void Delete(const Key &aKey); //Assert om key inte finns
		bool KeyExists(const Key &aKey);
		Value& operator[](const Key &aKey);

	private:
		struct KeyValuePair
		{
			Key myKey;
			Value myValue;
		};

		int Hash(const Key &aKey);
		CU::GrowingArray<CU::GrowingArray<KeyValuePair, int>, int> myBuckets;
	};


	//----- CONSTRUCTOR -----
	//------------------------
	template<typename Key, typename Value, int StartSize = 67, int BucketSize = 3>
	Map<Key, Value, StartSize, BucketSize>::Map()
	{
		myBuckets.Reserve(StartSize);

		for (int i = 0; i < myBuckets.Size(); ++i)
		{
			myBuckets[i].Init(BucketSize);
		}
	}


	//----- DECONSTRUCTOR ----
	//------------------------
	template<typename Key, typename Value, int StartSize = 67, int BucketSize = 3>
	Map<Key, Value, StartSize, BucketSize>::~Map()
	{

	}


	//----- INSERT -----
	//------------------
	template<typename Key, typename Value, int StartSize = 67, int BucketSize = 3>
	void Map<Key, Value, StartSize, BucketSize>::Insert(const Key &aKey, const Value &aValue)
	{
		if (KeyExists(aKey) == true)
		{
			operator[](aKey) = aValue;
			return;
		}

		int index = Hash(aKey);

		KeyValuePair pair;
		pair.myKey = aKey;
		pair.myValue = aValue;

		myBuckets[index].Add(pair);
	}


	//----- GET -----
	//---------------
	template<typename Key, typename Value, int StartSize = 67, int BucketSize = 3>
	Value& Map<Key, Value, StartSize, BucketSize>::Get(const Key &aKey)//Assert om key inte finns
	{
		assert(KeyExists(aKey) == true && "[CUMap]: Tried to get an nonexisting Key.");

		int index = Hash(aKey);
		for (int i = 0; i < myBuckets[index].Size(); ++i)
		{
			if (myBuckets[index][i].myKey == aKey)
				return myBuckets[index][i].myValue;
		}

		assert(false && "[CUMap]: Get() failed to find a Key, should NEVER happen...");
		return myBuckets[0][0].myValue;
	}


	//----- DELETE -----
	//------------------

	template<typename Key, typename Value, int StartSize = 67, int BucketSize = 3>
	void Map<Key, Value, StartSize, BucketSize>::Delete(const Key &aKey) //Assert om key inte finns
	{
		assert(KeyExists(aKey) == true && "[CUMap]: Tried to delete an nonexisting Key.");

		int index = Hash(aKey);

		for (int i = 0; i < myBuckets[index].Size(); ++i)
		{
			if (myBuckets[index][i].myKey == aKey)
			{
				myBuckets[index].RemoveCyclicAtIndex(i);
				return;
			}
		}
	}


	//----- KEY_EXISTS -----
	//---------------------
	template<typename Key, typename Value, int StartSize = 67, int BucketSize = 3>
	bool Map<Key, Value, StartSize, BucketSize>::KeyExists(const Key &aKey)
	{
		int index = Hash(aKey);

		for (int i = 0; i < myBuckets[index].Size(); ++i)
		{
			if (myBuckets[index][i].myKey == aKey)
				return true;
		}

		return false;
	}


	//----- SUBSCRIPT_OPERATOR -----
	//------------------------------
	template<typename Key, typename Value, int StartSize = 67, int BucketSize = 3>
	Value& Map<Key, Value, StartSize, BucketSize>::operator[](const Key &aKey)
	{
		if (KeyExists(aKey) == false)
		{
			Value newVal;
			Insert(aKey, newVal);
		}

		return Get(aKey);
	}


	//----- HASH -----
	//----------------
	template<typename Key, typename Value, int StartSize = 67, int BucketSize = 3>
	int Map<Key, Value, StartSize, BucketSize>::Hash(const Key &aKey)
	{
		return Murmur::Hash(aKey.c_str()) % StartSize;
	}
}