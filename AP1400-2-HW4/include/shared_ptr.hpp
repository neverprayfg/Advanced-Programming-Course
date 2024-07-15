#include "shared_ptr.h"

template <class T>
SharedPtr<T>::SharedPtr(T*&& ptr) : _p(ptr){
    count = new size_t{1};
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr&& ptr){
    (*ptr.count)++;
    count = ptr.count;
    _p = ptr._p;
}

template <class T>
SharedPtr<T>::SharedPtr(){
    _p = nullptr;
    count = nullptr;
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr& ptr){
    (*ptr.count)++;
    count = ptr.count;
    _p = ptr._p;
}

template <class T>
SharedPtr<T>::~SharedPtr(){
    if(_p != nullptr){
        (*count)--;
        if(*count == 0){
            delete _p;
            delete count;
        }
        _p = nullptr;
        count = nullptr;
    }
}

template <class T>
T* SharedPtr<T>::get() const{
    return _p;
}

template <class T>
T& SharedPtr<T>::operator*() const{
    return *_p;
}

template <class T>
T* SharedPtr<T>::operator->() const{
    return _p;
}

template <class T>
void SharedPtr<T>::reset(){
    if(_p != nullptr){
        (*count)--;
        if(*count == 0){
            delete _p;
            delete count;
        }
        _p = nullptr;
        count = nullptr;
    }
}

template <class T>
void SharedPtr<T>::reset(SharedPtr& ptr){
    *this = ptr;
}

template <class T>
void SharedPtr<T>::reset(SharedPtr&& ptr){
    *this = ptr;
}

template <class U>
SharedPtr<U> make_shared(U obj){
    return SharedPtr<U>(new U(obj));
}

template <class T>
SharedPtr<T>::operator bool() const{
    return _p != nullptr;
}
template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr& ptr){
    if(_p == ptr._p)
    {
        return *this;
    }
    if(_p != nullptr){
        (*count)--;
        if(*count == 0){
            delete _p;
            delete count;
        }
    }
    _p = ptr._p;
    (*ptr.count)++;
    count = ptr.count;
    return *this;
}

template <class T>
size_t SharedPtr<T>::use_count() const{
    if(count == nullptr) return 0;
    return *count;
}
