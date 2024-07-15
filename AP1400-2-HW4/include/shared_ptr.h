#ifndef SHARED_PTR
#define SHARED_PTR
#include <iostream>
template<class T>
class SharedPtr{
private:
    T* _p;
    size_t* count;
public:
    SharedPtr(T*&& ptr);
    SharedPtr(SharedPtr&& ptr);
    SharedPtr(SharedPtr& ptr);
    SharedPtr();
    ~SharedPtr();
    T* get() const;
    SharedPtr& operator=(SharedPtr& ptr);
    size_t use_count() const;
    T& operator*() const;
    T* operator->()const;
    void reset();
    void reset(SharedPtr& ptr);
    void reset(SharedPtr&& ptr);
    operator bool() const;
    template<class U>
    friend SharedPtr<U> make_shared(U obj);
};

#include "shared_ptr.hpp"

#endif //SHARED_PTR