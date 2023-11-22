#include "Vector.h"
#include <string>
using std::pair;
using std::string;
using std::make_pair;

enum Status
{
    EMPTY,
    OCUPIED,
    DELETE
};

template <class K, class T>
class HashNode
{
public:
    pair<K, T> kt;
    Status status;

    HashNode()
    {
        status = EMPTY;
    }

    HashNode(const HashNode& tmp)
    : kt(tmp.kt), status(tmp.status) 
    {
        
    }
    
    HashNode& operator =(const HashNode& rhs)
    {
        kt = rhs.kt;
        status = rhs.status;
        return *this;
    }
};

template<class K>
class Hash
{
public:
    size_t operator () (const K& key)
    {
        return 1ll * key * 131;
    }
};

template<>
class Hash<string>
{
public:
    size_t operator () (const string& key)
    {
        size_t k = 0;
        for(auto i : key)
        {
            k += i;
            k *= 131;
        }
        k = k*131;
        return k;
    }
};


template <class K, class T, class Hash = Hash<K> >
class Unordered_Map
{
public:
    Hash hash;
    Unordered_Map() = default;
    Unordered_Map(int size)
    {
        v.reserve(size);
    }

    Unordered_Map(const Unordered_Map &tmp)
    {
        v = tmp.v;
        siz = tmp.siz;
    }

    bool insert(pair<K, T> kt)
    {
        if (find(kt.first))
        {
            return false;
        }
        if (v.siz() == 0 || 1.0 * siz / v.siz() >= 0.75)
        {
            size_t newSize = v.siz() == 0 ? 10 : v.siz() * 2;
            Unordered_Map<K, T, Hash> newMP;
            newMP.v.resize(newSize);
            for (auto i : v)
            {
                if (i.status == OCUPIED)
                {
                    newMP.insert(i.kt);
                }
            }
            v = std::move(newMP.v);
        }
   
        size_t index = hash(kt.first) % v.siz();
        while (v[index].status == OCUPIED)
        {
            index++;
            index %= v.siz();
        }
        v[index].kt = kt;
        v[index].status = OCUPIED;
        siz++;
        return true;
    }

    HashNode<K, T> *find(const K &key)
    {
        if (v.siz() == 0)
        {
            return nullptr;
        }
        size_t start = hash(key) % v.siz();
        size_t index = start;

        while (v[index].status != EMPTY)
        {
            if (v[index].kt.first == key && v[index].status == OCUPIED)
            {
                return &v[index];
            }
            else
            {
                index++;
                index %= v.siz();
            }
        }
        return nullptr;
    }

    bool erase(const K &key)
    {
        HashNode<K, T> *pos = find(key);
        if (pos == nullptr)
        {
            return false;
        }
        else
        {
            pos->status = DELETE;
            siz--;
            return true;
        }
    }

    T &operator[](const K& key)
    {
        HashNode<K,T>* pos = find(key);
        if(pos == nullptr)
        {
            insert(make_pair(key,T()));
            HashNode<K,T>* pos = find(key);
            return pos -> kt.second;
        }
        else
        {
            return pos -> kt.second;
        }
    }

private: 
    Vector<HashNode<K, T> > v;
    size_t siz = 0;
};



int main()
{
    Unordered_Map<int , string> mp;
    string s = "12";
    mp[1]=s;
    cout<<mp[1];
    return 0;
}