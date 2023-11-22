#include <iostream>
using std::cout;

template <class T>
class my_share_ptr
{
private:
    T *ptr;
    

public:
    unsigned *share_ptr_count;

    my_share_ptr() : ptr(nullptr), share_ptr_count(new unsigned(1)){};

    my_share_ptr(T *rhs)
    {
        ptr = rhs;
        share_ptr_count = new unsigned(1);
    }

    my_share_ptr(T* rhs_ptr , unsigned* rhs_count)
    {
        ptr = rhs_ptr;
        share_ptr_count = rhs_count;
        (*share_ptr_count)++;
    }

    my_share_ptr(my_share_ptr &rhs)
    {
        share_ptr_count = rhs.share_ptr_count;
        ptr = rhs.ptr;
        (*share_ptr_count)++;
    }

    my_share_ptr &operator=(my_share_ptr &rhs)
    {
        ptr = rhs.ptr;
        share_ptr_count = rhs.share_ptr_count;
        (*share_ptr_count)++;
        return *this;
    }

    my_share_ptr(my_share_ptr &&rhs)
    {
        ptr = rhs.ptr;
        share_ptr_count = rhs.share_ptr_count;
        rhs.ptr = nullptr;
        rhs.share_ptr_count = nullptr;
    }

    my_share_ptr &operator=(my_share_ptr &&rhs)
    {
        ptr = rhs.ptr;
        share_ptr_count = rhs.share_ptr_count;
        rhs.ptr = nullptr;
        rhs.share_ptr_count = nullptr;
        return *this;
    }

    ~my_share_ptr()
    {
        if (share_ptr_count != nullptr && --(*share_ptr_count) == 0 && ptr != nullptr)
        {
            delete ptr;
            delete share_ptr_count;
        }
        ptr = nullptr;
        share_ptr_count = nullptr;
    }

    auto use_count()
    {
        return *share_ptr_count;
    }

    T &operator*()
    {
        return *ptr;
    }

    T *operator->()
    {
        return ptr;
    }

    void reset()
    {
        this->~my_share_ptr();
    }

    T *get()
    {
        return ptr;
    }
};

template <class T, class... Args>
decltype(auto) make_share_ptr(Args &&...args)
{
    return my_share_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
class my_weak_ptr
{
private:
   T* ptr;
   unsigned* count;

public:
    my_weak_ptr() {};

    my_weak_ptr(my_weak_ptr<T>& rhs)
    {
        ptr = rhs.ptr;
        count = rhs.count;
    }

    my_weak_ptr operator = (my_weak_ptr<T>&  rhs)
    {
        ptr = rhs.ptr;
        count = rhs.count;
        return *this;
    }

    my_weak_ptr(my_weak_ptr<T>&& rhs)
    {
        ptr = rhs.ptr;
        count = rhs.count;
        rhs.count = nullptr;
        rhs.ptr = nullptr;
    }

    my_weak_ptr operator = (my_weak_ptr<T>&& rhs)
    {
        ptr = rhs.ptr;
        count = rhs.count;
        rhs.count = nullptr;
        rhs.ptr = nullptr;
        return *this;
    }

    my_weak_ptr(my_share_ptr<T>& rhs)
    {
       ptr = rhs.get();
       count = rhs.share_ptr_count;
    }

    my_weak_ptr<T> &operator=(my_share_ptr<T>& rhs)
    {
        ptr = rhs.get();
        count = rhs.share_ptr_count;
        return *this;
    }

    bool expired()
    {
        if(count == nullptr || (*count) == 0)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    auto use_count()
    {
        if(count != nullptr)
        {
            return *count;
        }
        else
        {
            return 0;
        }
    }

    auto lock()
    {
        if(expired())
        {
            return my_share_ptr<T>();
        }
        else
        {
            return std::move(my_share_ptr<T>(ptr,count));
        }
    }

};

class B;

class A
{
public:
    my_weak_ptr<B> p;

    A()
    {
        cout << "create\n";
    }

    ~A()
    {
        cout << "A delete\n";
    }
};

class B
{
public:
    my_share_ptr<A> p;

    ~B()
    {
        cout << "B delete\n";
    }
};

int main()
{
    // auto p1 = make_share_ptr<A>();
    // auto p2 = make_share_ptr<B>();
    // p1->p = p2;
    // p2->p = p1;
    auto p =make_share_ptr<std::string>("123");
    auto p1 =static_cast<my_weak_ptr<std::string> > (p);
    return 0;
}
