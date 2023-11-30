#include <algorithm>
#include <string>
#include <malloc.h>
#include <iostream>
#include <time.h>
#include <vector>
using std::cout;
using std::string;

template <class T>
class Vector
{
private:
    T *head;
    int length;
    size_t size;
    T *_end;

public:
    typedef T *iterator;
    Vector()
    {
        head = nullptr;
        length = size = 0;
        _end = nullptr;
    }

    Vector(int _size)
    {
        size = _size;
        length = 0;
        head = (T *)malloc(sizeof(T) * size);
        _end = head;
    }

    Vector(const Vector &vec)
    {
        if (this == &vec)
            return;
        if (head != nullptr)
            free(head);
        head = (T *)malloc(sizeof(T) * vec.size);
        _end = head;
        for (int i = 0; i < vec.size; i++)
        {
            head[i] = vec.head[i];
            _end++;
        }
        length = vec.length;
        size = vec.size;
    }

    Vector(Vector<T> &&vec)
    {
        if (head == vec.head)
            return;
        if (head != nullptr)
            free(head);
        head = vec.head;
        size = vec.size;
        length = vec.length;
        _end = vec._end;
        vec.~Vector();
    }

    Vector(int _size, T obj)
    {
        size = _size;
        length = _size;
        head = (T *)malloc(sizeof(T) * size);
        _end = head;
        for (int i = 0; i < size; i++)
        {
            head[i] = obj;
            _end++;
        }
    }

    Vector(std::initializer_list<T> l)
    {
        length = size = 0;
        head = nullptr;
        _end = head;
        for (auto it = l.begin(); it != l.end(); it++)
        {
            push_back(*it);
        }
    }

    ~Vector()
    {
        free(head);
        head = nullptr;
        _end = nullptr;
    }

    T &operator[](const int x)
    {
        return head[x];
    }

    Vector<T> &operator=(Vector<T> &&vec)
    {
        if (vec.head == head)
            return *this;
        if (head != nullptr)
            free(head);
        head = vec.head;
        length = vec.length;
        size = vec.length;
        _end = vec._end;
        vec.~Vector();
        return *this;
    }

    void push_back(const T x)
    {
        if (length == size)
        {
            size = (size == 0) ? 1 : size_t(size * 2);
            T *new_head = (T *)malloc(sizeof(T) * size);

            memcpy(new_head, head, length * sizeof(T));
            free(head);
            head = new_head;
            _end = head;
            for (int i = 0; i < length; i++)
            {
                _end++;
            }

            new_head = nullptr;
        }
        head[length++] = x;
        _end++;
        return void();
    }

    void pop_back()
    {
        length--;
        _end--;
        if (length <= (size >> 2))
        {
            size >>= 1;
            T *new_head = (T *)malloc(sizeof(T) * size);
            memcpy(new_head, head, sizeof(T) * length);
            free(head);
            head = new_head;
            _end = head;
            for (int i = 0; i < length; i++)
            {
                _end++;
            }
            new_head = nullptr;
        }
        return void();
    }

    int capacity()
    {
        return size - length;
    }

    size_t siz()
    {
        return size;
    }

    int len()
    {
        return length;
    }

    void reserve(const int n)
    {
        if (n <= capacity())
            return void();
        size += n - capacity();
        T *new_head = (T *)malloc(sizeof(T) * size);
        memcpy(new_head, head, sizeof(T) * length);
        free(head);
        head = new_head;
        _end = head;
        for (int i = 0; i < length; i++)
        {
            _end++;
        }
        new_head = nullptr;
        return void();
    }

    void resize(const int n, T obj = T())
    {
        if (n < length)
        {
            for (int i = n; i < length; i++)
            {
                pop_back();
            }
            length = n;
        }
        else if (n > length)
        {
            int lim = n - length;
            for (int i = 1; i <= lim; i++)
            {
                push_back(obj);
            }
        }
    }

    T *begin()
    {
        return head;
    }

    T *end()
    {
        return _end;
    }

    T *rbegin()
    {
        T *tmp = _end;
        tmp--;
        return tmp;
    }

    T &front()
    {
        return *head;
    }

    T &back()
    {
        return *rbegin();
    }

    T *find(T *__begin, T *__end, T value)
    {
        if (__begin < head || __begin >= _end || __end < head || __end >= _end)
        {
            return _end;
        }
        for (iterator it = __begin; it <= __end; it++)
        {
            if (*it == value)
            {
                return it;
            }
        }
        return _end;
    }

    T *erase(int position)
    {
        for (int i = position; i < length - 1; i++)
        {
            std::swap(head[i], head[i + 1]);
        }
        _end--;
        return head + position;
    }

    void clear()
    {
        free(head);
        head = (T *)malloc(sizeof(T) * size);
        _end = head;
        length = 0;
    }
};

int main()
{
    std::thread t([](){
        std::cout << "hello world." << std::endl;
    });
    t.join();
    return 0;
}