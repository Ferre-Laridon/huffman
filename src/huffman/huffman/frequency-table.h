#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#include <iostream>
#include <map>
#include <vector>


namespace data
{

	template<typename T>
	class FrequencyTable
	{
		std::map<T, unsigned long> freqtable;

	public:
		void increment(const T& value)
		{
			freqtable[value]++;
		}

		const unsigned long operator [](const T& value) const
		{
			if (freqtable.find(value) != freqtable.end())
			{
				return freqtable.at(value);
			}
			else
			{
				return 0;
			}
		}

		std::vector<T> values() const
		{
			std::vector<T> values;
			for (auto it = freqtable.begin(); it != freqtable.end(); it++)
			{
				values.push_back(it->first);
			}

			return values;
		}
	};

	template<typename T>
	FrequencyTable<T> count_frequencies(std::vector<T> values)
	{
		FrequencyTable<T> result;

		for (auto it = values.begin(); it != values.end(); ++it)
		{
			result.increment(*it);
		}

		return result;
	}

}

#endif