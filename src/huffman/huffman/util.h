#ifndef UTIL_H
#define UTIL_H

#include <cstdint>
#include <iostream>

typedef uint64_t u64;
typedef uint64_t Datum;

constexpr unsigned bits_needed(u64 domain_size)
{
	unsigned counter = 0;
	domain_size--;

	if (domain_size == 1)
	{
		return 1;
	}

	while (domain_size != 0)
	{
		counter++;
		domain_size >>= 1;
	}

	return counter;
}

constexpr unsigned bytes_needed(u64 domain_size)
{
	unsigned counter = bits_needed(domain_size);

	if (counter % 8 == 0)
	{
		return counter / 8;
	}
	else
	{
		return counter / 8 + 1;
	}
}

template<unsigned NBITS> struct SelectIntegerTypeByBytes;

template<> struct SelectIntegerTypeByBytes<1> { typedef uint8_t type; };
template<> struct SelectIntegerTypeByBytes<2> { typedef uint16_t type; };
template<> struct SelectIntegerTypeByBytes<3> { typedef uint32_t type; };
template<> struct SelectIntegerTypeByBytes<4> { typedef uint32_t type; };
template<> struct SelectIntegerTypeByBytes<5> { typedef uint64_t type; };
template<> struct SelectIntegerTypeByBytes<6> { typedef uint64_t type; };
template<> struct SelectIntegerTypeByBytes<7> { typedef uint64_t type; };
template<> struct SelectIntegerTypeByBytes<8> { typedef uint64_t type; };

template<u64 DOMAIN_SIZE> struct SelectIntegerTypeByDomainSize
{
	typedef typename SelectIntegerTypeByBytes<bytes_needed(DOMAIN_SIZE)>::type type;
};

#endif // !UTIL_H
