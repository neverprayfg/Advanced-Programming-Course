#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template<class T>
class UniquePtr{
private:
    T* _p;
public:
    UniquePtr(T*&& ptr);
    UniquePtr(UniquePtr&& ptr);
    UniquePtr(const UniquePtr& ptr) = delete;
    UniquePtr();
    ~UniquePtr();
    T* get() const;
    UniquePtr& operator=(const UniquePtr& ptr) = delete;
    T& operator*() const;
    T* operator->()const;
    void reset();
    void reset(UniquePtr&& ptr);
    T* release();
    operator bool() const;
    template<class U>
    friend UniquePtr<U> make_unique(U obj);
};

#include "unique_ptr.hpp"


#endif //UNIQUE_PTR