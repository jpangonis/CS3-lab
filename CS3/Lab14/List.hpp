#ifndef LIST_HPP_
#define LIST_HPP_

#include <iostream>
#include <memory>

using std::weak_ptr; using std::shared_ptr;

template <typename T>
class node {
public:
    node(const T& data) : data_(data), next_(nullptr), prev_() {}

    T getData() const { return data_; }
    void setData(const T& data) { data_ = data; }

    shared_ptr<node<T>> getNext() const { return next_; }
    void setNext(const shared_ptr<node<T>>& next) {next_ = next;}

    weak_ptr<node<T>> getPrev() const { return prev_; }
    void setPrev(const shared_ptr<node<T>>& prev) {prev_ = prev;}

private:
    T data_;
    weak_ptr<node<T>> prev_;
    shared_ptr<node<T>> next_;
};



#endif // LIST_HPP_
