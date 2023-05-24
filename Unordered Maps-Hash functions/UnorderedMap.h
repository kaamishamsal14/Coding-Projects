#include <cstddef>    // size_t
#include <functional> // std::hash
#include <ios>
#include <utility>    // std::pair
#include <iostream>

#include "primes.h"



template <typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class UnorderedMap {
    public:

    using key_type = Key;
    using mapped_type = T;
    using const_mapped_type = const T;
    using hasher = Hash;
    using key_equal = Pred;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    private:

    struct HashNode {
        HashNode *next;
        value_type val;

        HashNode(HashNode *next = nullptr) : next{next} {}
        HashNode(const value_type & val, HashNode * next = nullptr) : next { next }, val { val } { }
        HashNode(value_type && val, HashNode * next = nullptr) : next { next }, val { std::move(val) } { }
    };

    size_type _bucket_count;
    HashNode **_buckets;

    HashNode * _head;
    size_type _size;

    Hash _hash;
    key_equal _equal;

    static size_type _range_hash(size_type hash_code, size_type bucket_count) {
        return hash_code % bucket_count;
    }

    public:

    template <typename pointer_type, typename reference_type, typename _value_type>
    class basic_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = _value_type;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        const UnorderedMap * _map;
        HashNode * _ptr;

        explicit basic_iterator(UnorderedMap const * map, HashNode *ptr) noexcept : _map{map}, _ptr{ptr} {  }

    public:
        basic_iterator() { _ptr = nullptr; _map = nullptr; }

        basic_iterator(const basic_iterator &) = default;
        basic_iterator(basic_iterator &&) = default;
        ~basic_iterator() = default;
        basic_iterator &operator=(const basic_iterator &) = default;
        basic_iterator &operator=(basic_iterator &&) = default;
        reference operator*() const { return _ptr->val; }
        pointer operator->() const { return &_ptr->val; }
        basic_iterator &operator++() { 
            if(_ptr->next){
                _ptr = _ptr->next;
            }
            else{
                size_t bucket = _map->_bucket(_ptr->val);
                while(++bucket < _map->_bucket_count){
                    _ptr = _map-> _buckets[bucket];
                    if(_ptr){return *this;}
                }
                _ptr = nullptr;
            }
            return *this;
         }
        basic_iterator operator++(int) { 
            basic_iterator _old = *this; 
            ++(*this); 
            return _old; }
        bool operator==(const basic_iterator &other) const noexcept { return other._ptr == _ptr; }
        bool operator!=(const basic_iterator &other) const noexcept { return !(other == *this); }
    };

    using iterator = basic_iterator<pointer, reference, value_type>;
    using const_iterator = basic_iterator<const_pointer, const_reference, const value_type>;

    class local_iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = std::pair<const key_type, mapped_type>;
            using difference_type = ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

        private:
            friend class UnorderedMap<Key, T, Hash, key_equal>;
            using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

            HashNode * _node;

            explicit local_iterator( HashNode * node ) noexcept : _node(node) {  }

        public:
            local_iterator() { _node = nullptr; }

            local_iterator(const local_iterator &) = default;
            local_iterator(local_iterator &&) = default;
            ~local_iterator() = default;
            local_iterator &operator=(const local_iterator &) = default;
            local_iterator &operator=(local_iterator &&) = default;
            reference operator*() const { return _node->val; }
            pointer operator->() const { return &_node->val; }
            local_iterator & operator++() { 
                _node = _node->next;
                return *this;
             }
            local_iterator operator++(int) { 
                local_iterator _old = *this; 
                ++(*this); 
                return _old; }

            bool operator==(const local_iterator &other) const noexcept { return other._node == _node; }
            bool operator!=(const local_iterator &other) const noexcept { return !(other == *this); }
    };

private:

    size_type _bucket(size_t code) const { return (code%_bucket_count); }
    size_type _bucket(const Key & key) const { return _bucket(_hash(key)); }
    size_type _bucket(const value_type & val) const { return _bucket(val.first); }

    HashNode*& _find(size_type code, size_type bucket, const Key & key) { 
        if(_buckets[bucket] == nullptr){
            return _buckets[bucket];
        }
        HashNode** curr = &(_buckets[bucket]);

        while(*curr != nullptr){
            if((_equal((*curr)->val.first, key))){
                return *curr;  
            }
           curr = &((*curr)->next);
        }
        return *curr;
     }

    HashNode*& _find(const Key & key) { 
        return _find(_hash(key), bucket(key), key);
     }

    HashNode * _insert_into_bucket(size_type bucket, value_type && value) { 
        HashNode* curr = _buckets[bucket];
        HashNode* newcurr = new HashNode(std::move(value), curr);
        _buckets[bucket] = newcurr;
        if(_head==nullptr){
            _head=newcurr;
        }
        if(bucket<=_bucket(_head->val)){
            _head = newcurr;
        }
        
        _size++;
        return newcurr;
     }

    void _move_content(UnorderedMap & src, UnorderedMap & dst) { /* TODO */ }

public:
    explicit UnorderedMap(size_type bucket_count, const Hash & hash = Hash { },
                const key_equal & equal = key_equal { }) { 
                    _bucket_count = next_greater_prime(bucket_count);
                    _buckets = new HashNode*[_bucket_count]();
                    _head = nullptr;
                    _size = 0;
                    _equal = equal;
                    _hash = hash;
                 }

    ~UnorderedMap() { clear();
     }

    UnorderedMap(const UnorderedMap & other)  { 
        _size=0; 
        _head={};
        _hash=other._hash;
        _equal=other._equal;
        _bucket_count=other._bucket_count;
        _buckets = new HashNode*[_bucket_count]();
        auto ite = other.cbegin();
        while(ite != other.cend()){
            insert(*ite);
            ite++;
        }
     }

    UnorderedMap(UnorderedMap && other) { 
        _size = other._size;
        _head = other._head;
        _hash = other._hash;
        _equal = other._equal;
        _buckets = other._buckets;
        _bucket_count = other._bucket_count;
        other._size = 0;
        other._head = nullptr;
        other._buckets = new HashNode*[other._bucket_count]();
     }

    UnorderedMap & operator=(const UnorderedMap & other) { 
        if(this == &other){
            return *this;
        }
        clear();
        delete[] _buckets;
        _size = 0;
        _head = nullptr;
        _bucket_count = other._bucket_count;
        _buckets = new HashNode*[_bucket_count]();
        auto ite = other.cbegin();
        while(ite != other.cend()){
            insert(*ite);
            ite ++;
        }
        return *this;
     }

    UnorderedMap & operator=(UnorderedMap && other) { 
        if(this == &other){
            return *this;
        }
        clear();
        delete[] _buckets;
        _size = other._size;
        _head = other._head;
        _hash = other._hash;
        _equal = other._equal;
        _buckets = other._buckets;
        _bucket_count = other._bucket_count;
        other._size = 0;
        other._head = nullptr;
        other._buckets = new HashNode*[other._bucket_count]();
        return *this;
     }

    void clear() noexcept { 
         while(_size != 0){
             erase(begin());
         }
     }

    size_type size() const noexcept { return _size; }

    bool empty() const noexcept { return (_size == 0); }

    size_type bucket_count() const noexcept { return _bucket_count; }

    iterator begin() { return iterator(this, _head); }
    iterator end() { return iterator(this, nullptr); }

    const_iterator cbegin() const { return const_iterator(this, _head); };
    const_iterator cend() const { return const_iterator(this, nullptr); };

    local_iterator begin(size_type n) { return local_iterator(_buckets[n]); }
    local_iterator end(size_type n) { return local_iterator(nullptr); }

    size_type bucket_size(size_type n) { 
        local_iterator ite = begin(n);
        size_type a = 0;
        while(ite != end(n)){
            ++ite;
            ++a;
        }
        return a;
     }

    float load_factor() const { return ((float)_size)/((float)_bucket_count); }

    size_type bucket(const Key & key) const { return (_hash(key)%_bucket_count); }

    std::pair<iterator, bool> insert(value_type && value) { 
        auto temp = _find(value.first);

        if(temp != nullptr){
            return std::pair<iterator, bool>(iterator(this, temp), false);
        } else{
            size_type h = _hash(value.first);
            size_type b = _bucket(h);

            HashNode* _insert = _insert_into_bucket(b, std::move(value));
            return std::pair<iterator, bool>(iterator(this, _insert), true);
        }
    }

    std::pair<iterator, bool> insert(const value_type & value) { 
        auto temp = _find(value.first);

        value_type _val = value;

        if(temp != nullptr){
            return std::pair<iterator, bool>(iterator(this, temp), false);
        } else{
            size_type h = _hash(value.first);
            size_type b = _bucket(h);

            HashNode* _insert = _insert_into_bucket(b, std::move(_val));
            return std::pair<iterator, bool>(iterator(this, _insert), true);
        }
     }

    iterator find(const Key & key) { return iterator(this, _find(key)); }

    T& operator[](const Key & key) { 
        HashNode* current=_find(key);
        HashNode* findcurrent;
        if(current!=nullptr){
            return current->val.second;
        }
        auto createpair=std::make_pair(key,mapped_type{});
        insert(createpair);
        findcurrent=_find(key);
        return findcurrent->val.second;
    }


    iterator erase(iterator pos) { 
        HashNode* &findpos=_find(pos->first);
        HashNode* savepos=findpos;
        if(findpos == nullptr){
            return end();
        }
       iterator i(this,findpos);
       i++;
       if(_head==findpos){
        _head=i._ptr;
       }
        findpos=findpos->next;
        delete savepos;
        _size--;
       
        return i;
     }

    size_type erase(const Key & key) { 
        HashNode* &curr=_find(key);
        iterator ite(this, curr);
        if(curr != nullptr){
            erase(ite);
            return 1;
        }
        return 0;
     }

    template<typename KK, typename VV>
    friend void print_map(const UnorderedMap<KK, VV> & map, std::ostream & os);
};

template<typename K, typename V>
void print_map(const UnorderedMap<K, V> & map, std::ostream & os = std::cout) {
    using size_type = typename UnorderedMap<K, V>::size_type;
    using HashNode = typename UnorderedMap<K, V>::HashNode;

    for(size_type bucket = 0; bucket < map.bucket_count(); bucket++) {
        os << bucket << ": ";

        HashNode const * node = map._buckets[bucket];

        while(node) {
            os << "(" << node->val.first << ", " << node->val.second << ") ";
            node = node->next;
        }

        os << std::endl;
    }
}