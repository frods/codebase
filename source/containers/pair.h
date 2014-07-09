#ifndef PAIR
#define PAIR

template<class Key, class Value>
class Pair
{
public:
	Pair(Key KeyVal, Value ValueVal);

	inline bool operator ==(Key Other);
	inline bool operator ==(Pair *Other);

	inline bool operator <(Key Other);
	inline bool operator >(Key Other);

	inline bool operator <(Pair *Other);
	inline bool operator >(Pair *Other);

	Key m_Key;
	Value m_Value;	
};

template<class Key, class Value>
Pair<Key, Value>::Pair(Key KeyVal, Value ValueVal)
{
	m_Key = KeyVal;
	m_Value = ValueVal;
}

template<class Key, class Value>
inline bool Pair<Key, Value>::operator ==(Key Other)
{
	return Other == m_Key;
}

template<class Key, class Value>
inline bool Pair<Key, Value>::operator ==(Pair *Other)
{
	return Other->m_Key == m_Key;
}

template<class Key, class Value>
inline bool Pair<Key, Value>::operator <(Key Other)
{
	return Other < m_Key;
}

template<class Key, class Value>
inline bool Pair<Key, Value>::operator >(Key Other)
{
	return Other > m_Key;
}

template<class Key, class Value>
inline bool Pair<Key, Value>::operator <(Pair *Other)
{
	return m_Key < Other->m_Key;
}

template<class Key, class Value>
inline bool Pair<Key, Value>::operator >(Pair *Other)
{
	return m_Key > Other->m_Key;
}

#endif