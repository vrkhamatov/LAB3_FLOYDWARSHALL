#ifndef LAB_3_ITERATOR_H
#define LAB_3_ITERATOR_H

template <class T>
class Iterator
{
public:
    virtual T next() = 0;

    virtual bool has_next() = 0;

    virtual ~Iterator() {};
};

#endif //LAB_3_ITERATOR_H
