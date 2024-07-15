#include "unique_ptr.h"


template <class T>
UniquePtr<T>::UniquePtr(T*&& ptr) : _p(ptr){}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr&& ptr){
    _p = ptr._p;
    ptr._p = nullptr;
}

template <class T>
UniquePtr<T>::UniquePtr(){
    _p = nullptr;
}

template <class T>
UniquePtr<T>::~UniquePtr(){
    if(_p != nullptr){
        delete _p;
        _p = nullptr;
    }
}

template <class T>
T* UniquePtr<T>::get() const{
    return _p;
}

template <class T>
T& UniquePtr<T>::operator*() const{
    return *_p;
}

template <class T>
T* UniquePtr<T>::operator->() const{
    return _p;
}
template <class T>
void UniquePtr<T>::reset(){
    if(_p != nullptr){
        delete _p;
        _p = nullptr;
    }
}

template <class T>
void UniquePtr<T>::reset(UniquePtr&& ptr){
    if(_p != nullptr){
        delete _p;
    }
    _p = ptr._p;
    ptr._p = nullptr;
}

template <class T>
T* UniquePtr<T>::release(){
    auto cur_ptr = _p;
    _p = nullptr;
    return cur_ptr;
}

template <class U>
UniquePtr<U> make_unique(U obj){
    return UniquePtr<U>(new U(obj));
}

template <class T>
UniquePtr<T>::operator bool() const{
    return _p != nullptr;
}