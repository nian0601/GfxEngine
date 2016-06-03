#pragma once

#include <algorithm>

namespace Murmur
{
	//**********************************
	//** MURMUR SPECIFIC CODE, LET IT BE
	//**********************************
	typedef unsigned int       uint32_t;
	typedef unsigned char      uint8_t;

	__forceinline uint32_t getblock32(const uint32_t * p, int i)
	{
		return p[i];
	}

	__forceinline uint32_t fmix32(uint32_t h)
	{
		h ^= h >> 16;
		h *= 0x85ebca6b;
		h ^= h >> 13;
		h *= 0xc2b2ae35;
		h ^= h >> 16;

		return h;
	}

#define ROTL32(x,y)     _rotl(x,y)
	//**********************************
	//** MURMUR SPECIFIC CODE, LET IT BE
	//**********************************

	inline unsigned int Hash(const char* aKey)
	{
		const uint8_t * data = (const uint8_t*)aKey;
		const int nblocks = strlen(aKey) / 4;

		uint32_t h1 = 0;

		const uint32_t c1 = 0xcc9e2d51;
		const uint32_t c2 = 0x1b873593;

		//----------
		// body

		const uint32_t * blocks = (const uint32_t *)(data + nblocks * 4);

		for (int i = -nblocks; i; i++)
		{
			uint32_t k1 = getblock32(blocks, i);

			k1 *= c1;
			k1 = ROTL32(k1, 15);
			k1 *= c2;

			h1 ^= k1;
			h1 = ROTL32(h1, 13);
			h1 = h1 * 5 + 0xe6546b64;
		}

		//----------
		// tail

		const uint8_t * tail = (const uint8_t*)(data + nblocks * 4);

		uint32_t k1 = 0;

		switch (strlen(aKey) & 3)
		{
		case 3: k1 ^= tail[2] << 16;
		case 2: k1 ^= tail[1] << 8;
		case 1: k1 ^= tail[0];
			k1 *= c1; k1 = ROTL32(k1, 15); k1 *= c2; h1 ^= k1;
		};

		//----------
		// finalization

		h1 ^= strlen(aKey);

		h1 = fmix32(h1);


		return (uint32_t)h1;
	}
}