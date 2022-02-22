// SMALLBERG GRADER
#include "Map.h"
#include "OurType.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

int OurType::m_count = 0;
int OurType::m_asstcopycount = 0;

inline int itemcount()
{
	return OurType::m_count;
}

inline int nasstcopys()
{
	return OurType::m_asstcopycount;
}

const KeyType SOMEKEY = OurType(123);
const KeyType DEFAULT = KeyType();
const KeyType ARRAY[6] = {
	OurType(10), OurType(20), OurType(30),
	OurType(40), OurType(50), OurType(60)};

const ValueType SOMEVALUE = "junk";
const ValueType DEFAULTV = ValueType();
const ValueType ARRAYV[6] = {
	"alfa", "baker", "charlie", "delta", "echo", "foxtrot"};

struct PairType
{
	PairType() : k(SOMEKEY), v(SOMEVALUE) {}
	PairType(const KeyType &kk, const ValueType &vv) : k(kk), v(vv) {}
	KeyType k;
	ValueType v;
};

bool isPermutation(const Map &m, const KeyType ka[], const ValueType va[], int n)
{
	if (m.size() != n)
		return false;
	vector<PairType> a(n);
	for (int i = 0; i < n; i++)
		m.get(i, a[i].k, a[i].v);
	for (int j = 0; j < n; j++)
	{
		int i;
		for (i = j; i < n; i++)
		{
			if (ka[j] == a[i].k && va[j] == a[i].v)
			{
				PairType t = a[j];
				a[j] = a[i];
				a[i] = t;
				break;
			}
		}
		if (i == n)
			return false;
	}
	return true;
}

bool has(const Map &m, const KeyType &k, const ValueType &v)
{
	ValueType v2 = DEFAULTV;
	m.get(k, v2);
	ValueType v3 = SOMEVALUE;
	m.get(k, v3);
	return v2 == v && v3 == v;
}

void fillMap(Map &m, const vector<PairType> &pairs)
{
	for (int k = 0; k != pairs.size(); k++)
		m.insert(pairs[k].k, pairs[k].v);
}

bool isReassignment(const Map &m, const vector<PairType> &pairs)
{
	// Assumes pairs has no duplicate keys
	if (m.size() != pairs.size())
		return false;
	set<KeyType> keysFromPairs;
	set<KeyType> keysFromMap;
	map<ValueType, set<KeyType>> valuesFromPairs;
	map<ValueType, set<KeyType>> valuesFromMap;
	for (int i = 0; i < m.size(); i++)
	{
		keysFromPairs.insert(pairs[i].k);
		valuesFromPairs[pairs[i].v].insert(pairs[i].k);
		KeyType k;
		ValueType v;
		m.get(i, k, v);
		keysFromMap.insert(k);
		valuesFromMap[v].insert(k);
	}
	if (keysFromPairs != keysFromMap ||
		valuesFromPairs.size() != valuesFromMap.size())
		return false;
	if (!equal(begin(valuesFromPairs), end(valuesFromPairs),
			   begin(valuesFromMap), [](const auto &lhs, const auto &rhs)
			   { return lhs.first == rhs.first &&
						lhs.second.size() == rhs.second.size(); }))
		return false;
	if (pairs.size() <= 1)
		return true;
	auto pp(begin(valuesFromPairs));
	auto mp(begin(valuesFromMap));
	for (; pp != end(valuesFromPairs); pp++, mp++)
	{
		auto &pset(pp->second);
		auto &mset(mp->second);
		if (pset.size() == 1 && pset == mset) // no partner change
			return false;
	}
	return true;
}

const int SPEC_MAX = 260;

bool get2type(bool (Map::*)(const KeyType &, ValueType &) const) { return true; }
bool get2type(bool (Map::*)(const KeyType &, ValueType &)) { return false; }
bool get2type(...) { return false; }
bool get3type(bool (Map::*)(int, KeyType &, ValueType &) const) { return true; }
bool get3type(bool (Map::*)(int, KeyType &, ValueType &)) { return false; }
bool get3type(...) { return false; }

void testone(int n)
{
	if (n <= 5)
	{
		switch (n)
		{
		default:
		{
			cout << "Bad argument" << endl;
		}
		break;
		case 1:
		{
			assert((is_same<decltype(&Map::empty), bool (Map::*)() const>::value));
		}
		break;
		case 2:
		{
			assert((is_same<decltype(&Map::size), int (Map::*)() const>::value));
		}
		break;
		case 3:
		{
			assert((is_same<decltype(&Map::contains), bool (Map::*)(const KeyType &) const>::value));
		}
		break;
		case 4:
		{
			assert(get2type(&Map::get));
		}
		break;
		case 5:
		{
			assert(get3type(&Map::get));
		}
		}
		return;
	}
	Map m;
	switch (n)
	{
	default:
	{
		cout << "Bad argument" << endl;
	}
	break;
	case 1:
	{
		assert((is_same<decltype(&Map::empty), bool (Map::*)() const>::value));
	}
	break;
	case 2:
	{
		assert((is_same<decltype(&Map::size), int (Map::*)() const>::value));
	}
	break;
	case 3:
	{
		assert((is_same<decltype(&Map::contains), bool (Map::*)(const KeyType &) const>::value));
	}
	break;
	case 4:
	{
		assert(get2type(&Map::get));
	}
	break;
	case 5:
	{
		assert(get3type(&Map::get));
	}
	break;
	case 6:
	{
		assert(m.empty());
	}
	break;
	case 7:
	{
		assert(m.size() == 0);
	}
	break;
	case 8:
	{
		assert(!m.update(DEFAULT, SOMEVALUE) && m.size() == 0);
	}
	break;
	case 9:
	{
		assert(!m.erase(DEFAULT) && m.size() == 0);
	}
	break;
	case 10:
	{
		assert(!m.contains(DEFAULT));
	}
	break;
	case 11:
	{
		ValueType v = SOMEVALUE;
		assert(!m.get(DEFAULT, v) && v == SOMEVALUE);
	}
	break;
	case 12:
	{
		KeyType k = DEFAULT;
		ValueType v = SOMEVALUE;
		assert(!m.get(0, k, v) && k == DEFAULT && v == SOMEVALUE);
	}
	break;
	case 13:
	{
		assert(m.insert(SOMEKEY, SOMEVALUE));
	}
	break;
	case 14:
	{
		m.insert(SOMEKEY, SOMEVALUE);
		assert(!m.empty());
	}
	break;
	case 15:
	{
		m.insert(SOMEKEY, SOMEVALUE);
		assert(m.size() == 1);
	}
	break;
	case 16:
	{
		m.insert(SOMEKEY, SOMEVALUE);
		assert(m.contains(SOMEKEY));
	}
	break;
	case 17:
	{
		m.insert(SOMEKEY, SOMEVALUE);
		ValueType v = DEFAULTV;
		assert(m.get(SOMEKEY, v));
	}
	break;
	case 18:
	{
		m.insert(SOMEKEY, SOMEVALUE);
		ValueType v = DEFAULTV;
		m.get(SOMEKEY, v);
		assert(v == SOMEVALUE);
	}
	break;
	case 19:
	{
		m.insert(ARRAY[1], SOMEVALUE);
		ValueType v = DEFAULTV;
		assert(!m.get(ARRAY[0], v) && !m.get(ARRAY[2], v));
	}
	break;
	case 20:
	{
		m.insert(ARRAY[1], ARRAYV[1]);
		ValueType v = SOMEVALUE;
		m.get(ARRAY[0], v);
		assert(v == SOMEVALUE);
		m.get(ARRAY[2], v);
		assert(v == SOMEVALUE);
	}
	break;
	case 21:
	{
		m.insert(SOMEKEY, SOMEVALUE);
		KeyType k = DEFAULT;
		ValueType v = DEFAULTV;
		assert(m.get(0, k, v));
	}
	break;
	case 22:
	{
		m.insert(SOMEKEY, SOMEVALUE);
		KeyType k = DEFAULT;
		ValueType v = DEFAULTV;
		m.get(0, k, v);
		assert(k == SOMEKEY && v == SOMEVALUE);
	}
	break;
	case 23:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(!m.empty() && m.size() == 2);
	}
	break;
	case 24:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(m.contains(ARRAY[0]) && m.contains(ARRAY[1]));
	}
	break;
	case 25:
	{
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], ARRAYV[1]));
	}
	break;
	case 26:
	{
		m.insert(ARRAY[0], SOMEVALUE);
		m.insert(ARRAY[1], SOMEVALUE);
		assert(has(m, ARRAY[0], SOMEVALUE) && has(m, ARRAY[1], SOMEVALUE));
	}
	break;
	case 27:
	{
		assert(m.insert(ARRAY[1], ARRAYV[1]));
		assert(m.insert(ARRAY[0], ARRAYV[0]));
	}
	break;
	case 28:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[2]);
		assert(m.size() == 2);
	}
	break;
	case 29:
	{
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[2]);
		assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], ARRAYV[1]));
	}
	break;
	case 30:
	{
		assert(m.insert(ARRAY[0], ARRAYV[0]));
		assert(m.insert(ARRAY[1], ARRAYV[1]));
		assert(!m.insert(ARRAY[0], ARRAYV[2]));
	}
	break;
	case 31:
	{
		assert(m.insert(ARRAY[1], ARRAYV[1]));
		assert(m.insert(ARRAY[0], ARRAYV[0]));
		assert(!m.insert(ARRAY[1], ARRAYV[1]));
	}
	break;
	case 32:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		m.update(ARRAY[1], SOMEVALUE);
		assert(m.size() == 3 && m.contains(ARRAY[0]) &&
			   m.contains(ARRAY[1]) && m.contains(ARRAY[2]));
	}
	break;
	case 33:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		m.update(ARRAY[1], SOMEVALUE);
		assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], SOMEVALUE) &&
			   has(m, ARRAY[2], ARRAYV[2]));
	}
	break;
	case 34:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		assert(m.update(ARRAY[1], SOMEVALUE));
	}
	break;
	case 35:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.update(ARRAY[2], ARRAYV[0]);
		assert(m.size() == 2 && has(m, ARRAY[0], ARRAYV[0]) &&
			   has(m, ARRAY[1], ARRAYV[1]) && !m.contains(ARRAY[2]));
	}
	break;
	case 36:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(!m.update(ARRAY[2], ARRAYV[2]) && !m.update(ARRAY[3], ARRAYV[0]));
	}
	break;
	case 37:
	{
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insertOrUpdate(ARRAY[0], ARRAYV[0]);
		assert(!m.empty() && m.size() == 2);
	}
	break;
	case 38:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
		assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], ARRAYV[1]));
	}
	break;
	case 39:
	{
		m.insert(ARRAY[0], SOMEVALUE);
		m.insertOrUpdate(ARRAY[1], SOMEVALUE);
		assert(has(m, ARRAY[0], SOMEVALUE) && has(m, ARRAY[1], SOMEVALUE));
	}
	break;
	case 40:
	{
		assert(m.insert(ARRAY[1], ARRAYV[1]));
		assert(m.insertOrUpdate(ARRAY[0], ARRAYV[0]));
	}
	break;
	case 41:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insertOrUpdate(ARRAY[0], ARRAYV[2]);
		assert(m.size() == 2 && has(m, ARRAY[0], ARRAYV[2]) &&
			   has(m, ARRAY[1], ARRAYV[1]));
	}
	break;
	case 42:
	{
		assert(m.insert(ARRAY[0], ARRAYV[0]));
		assert(m.insert(ARRAY[1], ARRAYV[1]));
		assert(m.insertOrUpdate(ARRAY[0], ARRAYV[2]));
	}
	break;
	case 43:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		m.insertOrUpdate(ARRAY[1], SOMEVALUE);
		assert(m.size() == 3 && has(m, ARRAY[0], ARRAYV[0]) &&
			   has(m, ARRAY[1], SOMEVALUE) && has(m, ARRAY[2], ARRAYV[2]));
	}
	break;
	case 44:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		assert(m.insertOrUpdate(ARRAY[1], SOMEVALUE));
	}
	break;
	case 45:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insertOrUpdate(ARRAY[2], ARRAYV[0]);
		assert(m.size() == 3 && has(m, ARRAY[0], ARRAYV[0]) &&
			   has(m, ARRAY[1], ARRAYV[1]) && has(m, ARRAY[2], ARRAYV[0]));
	}
	break;
	case 46:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(m.insertOrUpdate(ARRAY[2], ARRAYV[2]));
	}
	break;
	case 47:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(m.erase(ARRAY[1]));
	}
	break;
	case 48:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.erase(ARRAY[1]);
		assert(!m.empty() && m.size() == 1 && has(m, ARRAY[0], ARRAYV[0]) &&
			   !m.contains(ARRAY[1]));
	}
	break;
	case 49:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.erase(ARRAY[0]);
		assert(!m.empty() && m.size() == 1 && has(m, ARRAY[1], ARRAYV[1]) &&
			   !m.contains(ARRAY[0]));
	}
	break;
	case 50:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.erase(ARRAY[0]);
		m.erase(ARRAY[1]);
		assert(m.size() == 0);
	}
	break;
	case 51:
	{
		m.insert(ARRAY[3], ARRAYV[3]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[4], ARRAYV[4]);
		m.erase(ARRAY[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.erase(ARRAY[4]);
		m.insert(ARRAY[5], ARRAYV[5]);
		m.erase(ARRAY[3]);
		m.insert(ARRAY[2], ARRAYV[2]);
		assert(m.size() == 3 && has(m, ARRAY[1], ARRAYV[1]) &&
			   has(m, ARRAY[2], ARRAYV[2]) && has(m, ARRAY[5], ARRAYV[5]) &&
			   !m.contains(ARRAY[0]) && !m.contains(ARRAY[3]) &&
			   !m.contains(ARRAY[4]));
	}
	break;
	case 52:
	{
		m.insert(ARRAY[3], ARRAYV[3]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[3], ARRAYV[3]);
		m.insert(ARRAY[4], ARRAYV[4]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[4], ARRAYV[4]);
		m.erase(ARRAY[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.erase(ARRAY[4]);
		m.insert(ARRAY[5], ARRAYV[5]);
		m.erase(ARRAY[3]);
		m.insert(ARRAY[2], ARRAYV[2]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(m.size() == 3 && has(m, ARRAY[1], ARRAYV[1]) &&
			   has(m, ARRAY[2], ARRAYV[2]) && has(m, ARRAY[5], ARRAYV[5]) &&
			   !m.contains(ARRAY[0]) && !m.contains(ARRAY[3]) &&
			   !m.contains(ARRAY[4]));
	}
	break;
	case 53:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(!m.erase(ARRAY[2]) && m.size() == 2);
	}
	break;
	case 54:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		KeyType k;
		ValueType v;
		assert(!m.get(-1, k, v));
	}
	break;
	case 55:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		KeyType k = SOMEKEY;
		ValueType v = SOMEVALUE;
		m.get(-1, k, v);
		assert(k == SOMEKEY && v == SOMEVALUE);
	}
	break;
	case 56:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		KeyType k;
		ValueType v;
		assert(!m.get(2, k, v));
	}
	break;
	case 57:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		KeyType k = SOMEKEY;
		ValueType v = SOMEVALUE;
		m.get(2, k, v);
		assert(k == SOMEKEY && v == SOMEVALUE);
	}
	break;
	case 58:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		KeyType k = SOMEKEY;
		ValueType v = SOMEVALUE;
		m.get(0, k, v);
		assert(k == ARRAY[0]);
	}
	break;
	case 59:
	{
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		KeyType k = SOMEKEY;
		ValueType v = SOMEVALUE;
		m.get(0, k, v);
		assert(k == ARRAY[0]);
	}
	break;
	case 60:
	{
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		KeyType k0 = SOMEKEY;
		ValueType v0 = SOMEVALUE;
		m.get(0, k0, v0);
		KeyType k1 = SOMEKEY;
		ValueType v1 = SOMEVALUE;
		m.get(1, k1, v1);
		assert(k0 == ARRAY[0] && v0 == ARRAYV[0] && k1 == ARRAY[1] && v1 == ARRAYV[1]);
	}
	break;
	case 61:
	{
		m.insert(ARRAY[3], ARRAYV[3]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[4], ARRAYV[4]);
		m.insert(ARRAY[2], ARRAYV[2]);
		assert(m.size() == 5);
		KeyType k;
		ValueType v;
		for (int i = 0; i < 5; i++)
		{
			m.get(i, k, v);
			assert(k == ARRAY[i]);
		}
	}
	break;
	case 62:
	{
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		assert(m.size() == 2);
		KeyType k;
		ValueType v;
		for (int i = 0; i < 2; i++)
		{
			m.get(i, k, v);
			assert(k == ARRAY[i]);
		}
	}
	break;
	case 63:
	{
		m.insert(DEFAULT, SOMEVALUE);
		assert(m.size() == 1 && has(m, DEFAULT, SOMEVALUE));
	}
	break;
	case 64:
	{
		m.update(DEFAULT, SOMEVALUE);
		assert(m.size() == 0 && !m.contains(DEFAULT));
	}
	break;
	case 65:
	{
		m.insertOrUpdate(DEFAULT, SOMEVALUE);
		assert(m.size() == 1 && has(m, DEFAULT, SOMEVALUE));
	}
	break;
	case 66:
	{
		m.insert(DEFAULT, SOMEVALUE);
		m.erase(DEFAULT);
		assert(m.size() == 0 && !m.contains(DEFAULT));
	}
	break;
	case 67:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[2], ARRAYV[2]);
			m2.insert(ARRAY[3], ARRAYV[3]);
			m.swap(m2);
			assert(m.size() == 2 && m2.size() == 2);
			for (int k = 0; k < 2; k++)
			{
				assert(!has(m, ARRAY[k], ARRAYV[k]));
				assert(has(m2, ARRAY[k], ARRAYV[k]));
			}
			for (int k = 2; k < 4; k++)
			{
				assert(has(m, ARRAY[k], ARRAYV[k]));
				assert(!has(m2, ARRAY[k], ARRAYV[k]));
			}
		}
	}
	break;
	case 68:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		{
			Map m2;
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
			m.swap(m2);
			assert(m.size() == 2 && m2.size() == 3);
		}
	}
	break;
	case 69:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		{
			Map m2;
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
			m.swap(m2);
			for (int k = 0; k < 3; k++)
			{
				assert(!has(m, ARRAY[k], ARRAYV[k]));
				assert(has(m2, ARRAY[k], ARRAYV[k]));
			}
			for (int k = 3; k < 5; k++)
			{
				assert(has(m, ARRAY[k], ARRAYV[k]));
				assert(!has(m2, ARRAY[k], ARRAYV[k]));
			}
		}
	}
	break;
	case 70:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		{
			Map m2;
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
			m2.swap(m);
			for (int k = 0; k < 3; k++)
			{
				assert(!has(m, ARRAY[k], ARRAYV[k]));
				assert(has(m2, ARRAY[k], ARRAYV[k]));
			}
			for (int k = 3; k < 5; k++)
			{
				assert(has(m, ARRAY[k], ARRAYV[k]));
				assert(!has(m2, ARRAY[k], ARRAYV[k]));
			}
		}
	}
	break;
	case 71:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		m.insert(ARRAY[3], ARRAYV[3]);
		m.insert(ARRAY[4], ARRAYV[4]);
		{
			Map m2;
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
			m2.insert(ARRAY[0], ARRAYV[0]);
			int n = nasstcopys();
			m.swap(m2);
			int n2 = nasstcopys();
			assert(n2 < n + 3);
		}
	}
	break;
	case 72:
	{
		int before = itemcount();
		{
			Map m2;
			m2.insert(ARRAY[0], ARRAYV[0]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			assert(itemcount() > before);
		}
		assert(itemcount() == before);
	}
	break;
	case 73:
	{
		{
			Map m2;
			m2.insert(ARRAY[0], ARRAYV[0]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m2.insert(ARRAY[2], ARRAYV[2]);
			m2.erase(ARRAY[1]);
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.erase(ARRAY[2]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m2.erase(ARRAY[0]);
			m2.erase(ARRAY[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
		}
		assert(true); // no corruption so bad that destruction failed
	}
	break;
	case 74:
	{
		{
			Map m2;
			m2.insert(ARRAY[0], ARRAYV[0]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			Map m3(m2);
			m3.insert(ARRAY[2], ARRAYV[2]);
			m3.erase(ARRAY[1]);
			m3.insert(ARRAY[3], ARRAYV[3]);
			m3.erase(ARRAY[2]);
			m3.insert(ARRAY[1], ARRAYV[1]);
			m3.erase(ARRAY[0]);
			m3.erase(ARRAY[3]);
			m3.insert(ARRAY[4], ARRAYV[4]);
		}
		assert(true); // no corruption so bad that destruction failed
	}
	break;
	case 75:
	{
		int before = itemcount();
		{
			Map m2;
			m2.insert(ARRAY[0], ARRAYV[0]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m2.insert(ARRAY[2], ARRAYV[2]);
			int mid = itemcount();
			Map m3(m2);
			assert(m3.size() == 3);
			assert(itemcount() - mid == mid - before);
		}
		assert(itemcount() == before);
	}
	break;
	case 76:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		{
			Map m2(m);
			m2.insert(ARRAY[3], ARRAYV[3]);
			assert(m2.size() == m.size() + 1);
		}
	}
	break;
	case 77:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		{
			Map m2(m);
			m2.insert(ARRAY[3], ARRAYV[3]);
			assert(isPermutation(m2, ARRAY, ARRAYV, 4));
		}
	}
	break;
	case 78:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		{
			Map m2(m);
			m2.insert(ARRAY[3], ARRAYV[3]);
			assert(isPermutation(m, ARRAY, ARRAYV, 3));
		}
	}
	break;
	case 79:
	{
		{
			Map m2;
			Map m3(m2);
			assert(m2.size() == 0 && m3.size() == 0);
			m2.insert(ARRAY[0], ARRAYV[0]);
			m3.insert(ARRAY[1], ARRAYV[1]);
			assert(m2.size() == 1 && m3.size() == 1);
			KeyType k;
			ValueType v;
			m2.get(0, k, v);
			assert(k == ARRAY[0]);
			m3.get(0, k, v);
			assert(k == ARRAY[1]);
		}
	}
	break;
	case 80:
	{
		int before = itemcount();
		{
			Map m2;
			Map m3;
			int mid = itemcount();
			m3.insert(ARRAY[0], ARRAYV[0]);
			m3.insert(ARRAY[1], ARRAYV[1]);
			m3 = m2;
			assert(m3.size() == 0);
			assert(itemcount() == mid);
		}
		assert(itemcount() == before);
	}
	break;
	case 81:
	{
		{
			Map m2;
			Map m3;
			m3.insert(ARRAY[0], ARRAYV[0]);
			m3.insert(ARRAY[1], ARRAYV[1]);
			m3 = m2;
			m2.insert(ARRAY[2], ARRAYV[2]);
			m3.insert(ARRAY[3], ARRAYV[3]);
			assert(m2.size() == 1 && m3.size() == 1);
			KeyType k;
			ValueType v;
			m2.get(0, k, v);
			assert(k == ARRAY[2]);
			m3.get(0, k, v);
			assert(k == ARRAY[3]);
		}
	}
	break;
	case 82:
	{
		int before = itemcount();
		{
			Map m2;
			Map m3;
			m3.insert(ARRAY[0], ARRAYV[0]);
			m3.insert(ARRAY[1], ARRAYV[1]);
			assert(m3.size() == 2);
			m2 = m3;
			assert(m2.size() == 2 && m3.size() == 2);
			m2.insert(ARRAY[2], ARRAYV[2]);
			m3.insert(ARRAY[3], ARRAYV[3]);
			assert(m2.size() == 3 && m3.size() == 3);
			assert(isPermutation(m2, ARRAY, ARRAYV, 3));
			KeyType ka[3] = {ARRAY[0], ARRAY[1], ARRAY[3]};
			ValueType va[3] = {ARRAYV[0], ARRAYV[1], ARRAYV[3]};
			assert(isPermutation(m3, ka, va, 3));
		}
		assert(itemcount() == before);
	}
	break;
	case 83:
	{
		{
			Map m2;
			m2.insert(ARRAY[0], ARRAYV[0]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			Map m3;
			m3.insert(ARRAY[3], ARRAYV[3]);
			m3.insert(ARRAY[4], ARRAYV[4]);
			m3 = m2;
			m3.insert(ARRAY[2], ARRAYV[2]);
			m3.erase(ARRAY[1]);
			m3.insert(ARRAY[3], ARRAYV[3]);
			m3.erase(ARRAY[2]);
			m3.insert(ARRAY[1], ARRAYV[1]);
			m3.erase(ARRAY[0]);
		}
		assert(true); // no corruption so bad that destruction failed
	}
	break;
	case 84:
	{
		int before = itemcount();
		{
			Map m2;
			m2.insert(ARRAY[0], ARRAYV[0]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m2.insert(ARRAY[2], ARRAYV[2]);
			int mid = itemcount();
			Map m3;
			m3.insert(ARRAY[4], ARRAYV[4]);
			m3.insert(ARRAY[5], ARRAYV[5]);
			m3 = m2;
			assert(itemcount() - mid == mid - before);
		}
	}
	break;
	case 85:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[2], ARRAYV[2]);
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
			m2 = m;
			m2.insert(ARRAY[5], ARRAYV[5]);
			assert(m2.size() == m.size() + 1);
		}
	}
	break;
	case 86:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
			m2.insert(ARRAY[5], ARRAYV[5]);
			m2 = m;
			m2.insert(ARRAY[2], ARRAYV[2]);
			assert(isPermutation(m2, ARRAY, ARRAYV, 3));
		}
	}
	break;
	case 87:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
			m2.insert(ARRAY[5], ARRAYV[5]);
			m2 = m;
			m2.insert(ARRAY[2], ARRAYV[2]);
			assert(isPermutation(m, ARRAY, ARRAYV, 2));
		}
	}
	break;
	case 88:
	{
		{
			Map m2;
			m2.insert(ARRAY[0], ARRAYV[0]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m2.insert(ARRAY[2], ARRAYV[2]);
			int n2 = itemcount();
			m2 = m2;
			assert(itemcount() == n2);
		}
		assert(true); // no corruption so bad that destruction failed
	}
	break;
	case 89:
	{
		{
			Map m2;
			m2.insert(ARRAY[0], ARRAYV[0]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m2.insert(ARRAY[2], ARRAYV[2]);
			m2 = m2;
			m2.insert(ARRAY[3], ARRAYV[3]);
			assert(isPermutation(m2, ARRAY, ARRAYV, 4));
		}
	}
	break;
	case 90:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		Map m2;
		Map m3;
		merge(m, m2, m3);
		assert(isPermutation(m3, ARRAY, ARRAYV, 3));
	}
	break;
	case 91:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		Map m2;
		Map m3;
		merge(m2, m, m3);
		assert(isPermutation(m3, ARRAY, ARRAYV, 3));
	}
	break;
	case 92:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
		Map m3;
		merge(m, m2, m3);
		assert(isPermutation(m3, ARRAY, ARRAYV, 5));
	}
	break;
	case 93:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
		Map m3;
		assert(merge(m, m2, m3));
	}
	break;
	case 94:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
		Map m3;
		m3.insert(ARRAY[2], ARRAYV[5]);
		merge(m, m2, m3);
		assert(isPermutation(m3, ARRAY, ARRAYV, 5));
	}
	break;
	case 95:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
		Map m3;
		m3.insert(ARRAY[2], ARRAYV[5]);
		assert(merge(m, m2, m3));
	}
	break;
	case 96:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[2], ARRAYV[2]);
		Map m3;
		merge(m, m2, m3);
		assert(isPermutation(m3, ARRAY, ARRAYV, 4));
	}
	break;
	case 97:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[2], ARRAYV[2]);
		Map m3;
		assert(merge(m, m2, m3));
	}
	break;
	case 98:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[3], ARRAYV[3]);
		Map m2;
		m2.insert(ARRAY[2], ARRAYV[2]);
		m2.insert(ARRAY[3], ARRAYV[4]);
		Map m3;
		merge(m, m2, m3);
		assert(isPermutation(m3, ARRAY, ARRAYV, 3));
	}
	break;
	case 99:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[3], ARRAYV[3]);
		Map m2;
		m2.insert(ARRAY[2], ARRAYV[2]);
		m2.insert(ARRAY[3], ARRAYV[4]);
		Map m3;
		assert(!merge(m, m2, m3));
	}
	break;
	case 100:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
		merge(m, m2, m);
		assert(isPermutation(m, ARRAY, ARRAYV, 5));
	}
	break;
	case 101:
	{
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
		merge(m, m2, m2);
		assert(isPermutation(m2, ARRAY, ARRAYV, 5));
	}
	break;
	case 102:
	{
		vector<PairType> pairs = {};
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 103:
	{
		vector<PairType> pairs = {
			{ARRAY[0], ARRAYV[0]},
		};
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 104:
	{
		vector<PairType> pairs = {
			{ARRAY[0], ARRAYV[0]},
			{ARRAY[1], ARRAYV[1]},
		};
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 105:
	{
		vector<PairType> pairs = {
			{ARRAY[0], ARRAYV[0]},
			{ARRAY[1], ARRAYV[0]},
		};
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 106:
	{
		vector<PairType> pairs = {
			{ARRAY[0], ARRAYV[0]},
			{ARRAY[3], ARRAYV[3]},
			{ARRAY[1], ARRAYV[1]},
			{ARRAY[4], ARRAYV[4]},
			{ARRAY[2], ARRAYV[2]},
		};
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 107:
	{
		vector<PairType> pairs = {
			{ARRAY[0], ARRAYV[0]},
			{ARRAY[1], ARRAYV[0]},
			{ARRAY[2], ARRAYV[1]},
		};
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 108:
	{
		vector<PairType> pairs = {
			{ARRAY[0], ARRAYV[0]},
			{ARRAY[1], ARRAYV[1]},
			{ARRAY[2], ARRAYV[0]},
		};
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 109:
	{
		vector<PairType> pairs = {
			{ARRAY[0], ARRAYV[0]},
			{ARRAY[1], ARRAYV[1]},
			{ARRAY[2], ARRAYV[1]},
		};
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 110:
	{
		vector<PairType> pairs = {
			{ARRAY[0], ARRAYV[0]},
			{ARRAY[1], ARRAYV[0]},
			{ARRAY[2], ARRAYV[0]},
		};
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 111:
	{
		const int NITEMS = 100;
		vector<PairType> pairs;
		pairs.reserve(NITEMS);
		ValueType v = ValueType();
		for (int k = 0; k < NITEMS; k++)
		{
			pairs.push_back({OurType(k), v});
			v += 'x';
		}
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 112:
	{
		const int NITEMS = 101;
		vector<PairType> pairs;
		pairs.reserve(NITEMS);
		ValueType v = ValueType();
		for (int k = 0; k < NITEMS; k++)
		{
			pairs.push_back({OurType(k), v});
			v += 'x';
		}
		fillMap(m, pairs);
		Map m2;
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 113:
	{
		vector<PairType> pairs = {
			{ARRAY[0], ARRAYV[0]},
			{ARRAY[1], ARRAYV[1]},
			{ARRAY[2], ARRAYV[2]},
			{ARRAY[3], ARRAYV[3]},
		};
		fillMap(m, pairs);
		Map m2;
		fillMap(m2, {{ARRAY[0], ARRAYV[0]},
					 {ARRAY[4], ARRAYV[4]},
					 {ARRAY[2], ARRAYV[5]},
					 {ARRAY[5], ARRAYV[3]}});
		reassign(m, m2);
		assert(isReassignment(m2, pairs));
	}
	break;
	case 114:
	{
		vector<PairType> pairs = {
			{ARRAY[0], ARRAYV[0]},
			{ARRAY[1], ARRAYV[1]},
			{ARRAY[2], ARRAYV[2]},
			{ARRAY[3], ARRAYV[3]},
		};
		fillMap(m, pairs);
		reassign(m, m);
		assert(isReassignment(m, pairs));
	}
	break;
	case 115:
	{
		const int NITEMS = 2 * SPEC_MAX;
		for (int k = 0; k < NITEMS; k++)
			assert(m.insert(OurType(k), SOMEVALUE));
		assert(m.size() == NITEMS);
	}
	}
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	if (n < 1 || n > 115)
	{
		cout << "Bad test number" << endl;
		return 1;
	}
	testone(n);
	cout << "Passed" << endl;
}
