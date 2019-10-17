// HashSet.hpp
//
// ICS 46 Winter 2019
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to use a dynamically-
// allocated array and your own linked list implemenation; the linked list
// doesn't have to be its own class, though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename ElementType>
class HashSet : public Set<ElementType>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction is a function that takes a reference to a const
    // ElementType and returns an unsigned int.
    using HashFunction = std::function<unsigned int(const ElementType&)>;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    explicit HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet() noexcept;

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s) noexcept;

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const noexcept override;


    // elementsAtIndex() returns the number of elements that hashed to a
    // particular index in the array.  If the index is out of the boundaries
    // of the array, this function returns 0.
    unsigned int elementsAtIndex(unsigned int index) const;


    // isElementAtIndex() returns true if the given element hashed to a
    // particular index in the array, false otherwise.  If the index is
    // out of the boundaries of the array, this functions returns 0.
    bool isElementAtIndex(const ElementType& element, unsigned int index) const;


private:
    HashFunction hashFunction;
    struct Node
    {
        ElementType element;
        Node* next = nullptr;
    };
    Node** hash;
    int hCapacity;
    int hSize;
    void destroy(Node* node);
};



namespace impl_
{
    template <typename ElementType>
    unsigned int HashSet__undefinedHashFunction(const ElementType& element)
    {
        return 0;
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    hCapacity = DEFAULT_CAPACITY;
    hash = new Node*[hCapacity];
    hSize = 0;
    for(int i = 0; i < hCapacity; i++){
        hash[i] = nullptr;
    }
}


template <typename ElementType>
HashSet<ElementType>::~HashSet() noexcept
{
    for(int i = 0; i < hCapacity; i++){
        destroy(hash[i]);
    }
    delete[] hash;
}

template <typename ElementType>
void HashSet<ElementType>::destroy(Node* node){
    if(node != nullptr){
        destroy(node->next);
        delete node;
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(const HashSet& s)
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    hCapacity = s.hCapacity;
    hash = new Node*[hCapacity];
    for(int i = 0; i < hCapacity; i++){
        if(s.hash[i] != nullptr){
            Node* walker = s.hash[i];
            Node* copy = nullptr;
            copy = new Node{walker->element};
            while(walker->next != nullptr){
                walker = walker->next;
                copy->next = new Node{walker->element};
                copy = copy->next;
            }
            hash[i] = copy;
        }else{
            hash[i] = nullptr;
        }
    }
    hSize = s.hSize;
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashSet&& s) noexcept
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    //hash = nullptr;
    //std::swap(hash, s.hash);
    //std::swap(hSize, s.hSize);
    //std::swap(hCapacity, s.hCapacity);
    //std::swap(hashFunction, s.hashFunction);
    hash = s.hash;
    s.hash = nullptr;
    hCapacity = s.hCapacity;
    hSize = s.hSize;
    s.hCapacity = 0;
    s.hSize = 0;
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(const HashSet& s)
{
    if(this != &s){
        for(int i = 0; i < hCapacity; i++){
            destroy(hash[i]);
        }
        delete[] hash;
        hCapacity = s.hCapacity;
        hash = new Node*[hCapacity];
        for(int i = 0; i < hCapacity; i++){
            if(s.hash[i] != nullptr){
                Node* walker = s.hash[i];
                Node* copy = nullptr;
                copy = new Node{walker->element};
                while(walker->next != nullptr){
                    walker = walker->next;
                    copy->next = new Node{walker->element};
                    copy = copy->next;
                }
                hash[i] = copy;
            }else{
                hash[i] = nullptr;
            }
        }
        hSize = s.hSize;
    
    }
    return *this;
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(HashSet&& s) noexcept
{
    //std::swap(hash, s.hash);
    //std::swap(hashFunction, s.hashFunction);
    hash = s.hash;
    s.hash = nullptr;
    hCapacity = s.hCapacity;
    hSize = s.hSize;
    s.hCapacity = 0;
    s.hSize = 0;
    return *this;
}


template <typename ElementType>
bool HashSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void HashSet<ElementType>::add(const ElementType& element)
{
    if(!contains(element)){
        if((double)hSize/(double)hCapacity < 0.8){
            if(elementsAtIndex((hashFunction(element))%hCapacity) == 0){
                hash[(hashFunction(element))%hCapacity] = new Node{element};
            }else{
                Node* walker = hash[(hashFunction(element))%hCapacity];
                while(walker->next != nullptr){
                    walker = walker->next;
                }
                walker->next = new Node{element};
            }
            hSize++;
        }else{
            int oldCapacity = hCapacity;
            hCapacity = hCapacity*2;
            Node** oldHash = hash;
            //for(int i = 0; i < oldCapacity; i++){
            //destroy(hash[i]);
            //}
            //delete[] hash;
            hash = new Node*[hCapacity];
            for(int i = 0; i < hCapacity; i++){
            hash[i] = nullptr;
            }
            for(int i = 0; i < oldCapacity; i++){
                if(oldHash[i] != nullptr){
                    Node* walker = oldHash[i];
                    while(walker != nullptr){
                        if(elementsAtIndex((hashFunction(walker->element))%hCapacity) == 0){
                            hash[(hashFunction(walker->element))%hCapacity] = new Node{walker->element};
                        }else{
                            Node* adder = hash[(hashFunction(walker->element)%hCapacity)];
                            while(adder->next != nullptr){
                                adder = adder->next;
                            }
                            adder->next = new Node{walker->element};
                        }
                        
                        walker = walker->next;
                    }
                }
            }
            if(elementsAtIndex((hashFunction(element))%hCapacity) == 0){
                hash[(hashFunction(element))%hCapacity] = new Node{element};
            }else{
                Node* walker = hash[(hashFunction(element))%hCapacity];
                while(walker->next != nullptr){
                    walker = walker->next;
                }
                walker->next = new Node{element};
            }
            hSize++;
        }
    }
}


template <typename ElementType>
bool HashSet<ElementType>::contains(const ElementType& element) const
{
    bool isFound = false;
    Node* walker = hash[hashFunction(element) % hCapacity];
    while(walker != nullptr){
        if(walker->element == element){
            isFound = true;
            return isFound;
        }
        walker = walker->next;
    }
    return isFound;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::size() const noexcept
{
    return hSize;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::elementsAtIndex(unsigned int index) const
{
    if(index >= hCapacity){
        return 0;
    }else{
        int numElement = 0;
        Node* walker = hash[index];
        while(walker != nullptr){
            numElement++;
            walker = walker->next;
        }
        return numElement++;
    }
}


template <typename ElementType>
bool HashSet<ElementType>::isElementAtIndex(const ElementType& element, unsigned int index) const
{   
    if(index >= hCapacity){
        return 0;
    }else{
        bool isFound = false;
        Node* walker = hash[index];
        while(walker != nullptr){
            if(walker->element == element){
                isFound = true;
                return isFound;
            }
            walker = walker->next;
        }
        return isFound;
    }
}



#endif // HASHSET_HPP

