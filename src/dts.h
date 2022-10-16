#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

// TODO: make allocator class
namespace dts{

char POISON_VAL = 0xAB;

template <typename T, size_t N> class array{
public:

    array(){

        int n_elem = 0;
        try{
            for(; n_elem < N; n_elem++){
                new (data_ + n_elem * sizeof(T)) T();
            }
        }
        catch(const std::bad_alloc& err){
            n_elem--;

            for(; n_elem > -1; n_elem--){
                (*(T*)(data_ + n_elem * sizeof(T))).~T();
            }

            throw err;
        }
    }
    //----------------------------------------------------------------------------------------//
    
    array(const T& obj){

        int n_elem = 0;
        try{
            for(; n_elem < N; n_elem++){
                new (data_ + n_elem * sizeof(T)) T(obj);
            }
        }
        catch(const std::bad_alloc& err){
            n_elem--;

            for(; n_elem > -1; n_elem--){
                (*(T*)(data_ + n_elem * sizeof(T))).~T();
            }

            throw err;
        }
    }
    //----------------------------------------------------------------------------------------//

    array(const array& obj){
        int n_elem = 0;

        try{
            for(; n_elem < N; n_elem++){
                new (data_ + n_elem * sizeof(T)) T(obj[n_elem]);
            }
        }
        catch(const std::bad_alloc& err){
            n_elem--;

            for(; n_elem > -1; n_elem--){
                (*(T*)(data_ + n_elem * sizeof(T))).~T();
            }

            throw err;
        }
    }
    //----------------------------------------------------------------------------------------//

    ~array(){
        for(uint n_elem = 0; n_elem < N; n_elem++){
            (*(T*)(data_ + n_elem * sizeof(T))).~T();
        }
    }
    //----------------------------------------------------------------------------------------//

    array operator=(const array& obj){

        if(&obj = this) return obj;
        
        for(uint n_elem = 0; n_elem < N; n_elem++){
            new (data_ + n_elem * sizeof(T)) T(obj[n_elem]);
        }

        return obj;
    }
    //----------------------------------------------------------------------------------------//

    void dump() const{

        printf("array(%p)\n"
               "\tsize     = %lu\n"
               "\tval_size = %lu\n"
               "memory_dump{\n",
                    this, N, sizeof(T));
        
        for(uint n_byte = 0; n_byte < N * sizeof(T); n_byte++){
            printf("%x ", data_[n_byte]);
        }
        printf("}\n");
    }
    //----------------------------------------------------------------------------------------//
    
    T& operator[](uint n_elem){
        if(n_elem >= N) throw std::out_of_range("");
        return *(T*)(data_ + n_elem * sizeof(T));
    }
    //----------------------------------------------------------------------------------------//

    T operator[](uint n_elem) const{
        if(n_elem >= N) throw std::out_of_range("");
        return *(T*)(data_ + n_elem * sizeof(T));
    }
    //----------------------------------------------------------------------------------------//

    void* operator new(size_t size){
        std::cout << "array new was called\n";

        void* new_ptr = calloc(size, 1);

        if(new_ptr == NULL) throw std::bad_alloc();
        return new_ptr;
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete(void* ptr){
        std::cout << "delete was called\n";
        free(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
    void* operator new[](std::size_t size){
        std::cout << "operator new[] was called\n";

        void* new_ptr = calloc(size, 1);

        if(new_ptr == NULL) throw std::bad_alloc();
        return new_ptr;
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete[](void* ptr){
        std::cout << "operator delete[] was called\n";
        free(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
private:
    char data_[N * sizeof(T)];
};
//----------------------------------------------------------------------------------------//

const uint INCREASE_RATIO   = 2;
const uint REDUCE_RATIO     = 8;
const uint DEFAULT_CAPACITY = 1;

template <typename T> class vector{
public:

    vector():
        size_(0),
        capacity_(DEFAULT_CAPACITY)
    {
        data_ = allocate_mem(DEFAULT_CAPACITY);
    }
    //----------------------------------------------------------------------------------------//

    explicit vector(size_t capacity):
        size_(0),
        capacity_(capacity)
    {
        if(capacity == 0) throw std::bad_alloc();
        data_ = allocate_mem(capacity);
    }
    //----------------------------------------------------------------------------------------//

    vector(size_t size, const T& init_val):
        size_(size),
        capacity_(size)
    {
        if(size == 0) throw std::bad_alloc();
        data_ = allocate_mem(capacity_, init_val);
    }
    //----------------------------------------------------------------------------------------//

    vector(const vector& obj):
        size_(obj.size()),
        capacity_(obj.size())
    {
        data_ = allocate_mem(obj.size(), obj);
    }
    //----------------------------------------------------------------------------------------//

    ~vector(){
        free_alocated_mem();
    }
    //----------------------------------------------------------------------------------------//
    
    void dump() const{

        printf("vector(%p)\n"
               "\tsize     = %lu\n"
               "\tcapacity = %lu\n"
               "\tval_size = %lu\n"
               "\tdata     = %p\n"
               "memory_dump{\n",
                    this, size_, capacity_, sizeof(T), data_);
        
        for(uint n_byte = 0; n_byte < capacity_ * sizeof(T); n_byte++){
            printf("%x ", data_[n_byte]);
        }
        printf("}\n");
    }
    //----------------------------------------------------------------------------------------//
    
    vector operator=(const vector& obj){

        if(&obj == this) return obj;

        free_alocated_mem();

        size_     = obj.size();
        capacity_ = size_;

        data_ = allocate_mem(capacity_, obj);
        
        return obj;
    }
/*
    vector& operator=(const vector& obj)
    {
        this->~vector();
        new (this) vector(obj);
        return *this;
    }
*/
    vector& operator=(vector obj){
        std::swap(obj.size_, size_);
        std::swap(obj.capacity_, capacity_);
        std::swap(obj.data_, data_);
        
        return *this;
    }
    //----------------------------------------------------------------------------------------//

    T& operator[](uint n_elem){

        if(n_elem >= size_) throw std::out_of_range("");

        return *(T*)(data_ + n_elem * sizeof(T));
    }
    //----------------------------------------------------------------------------------------//

    T operator[](uint n_elem) const{

        if(n_elem >= size_) throw std::out_of_range("");

        return *(T*)(data_ + n_elem * sizeof(T));
    }
    //----------------------------------------------------------------------------------------//

    void push_back(const T& val){

        if(size_ + 1 >= capacity_) increase_capacity();

        *(T*)(data_ + (size_++) * sizeof(T)) = val;
    }
    //----------------------------------------------------------------------------------------//
    
    T pop_back(){
        
        if(size_ == 0) throw std::out_of_range("");

        if(size_ > 1 && (size_ - 1) * 8 <= capacity_) reduce_capacity();
        size_--;

        return *(T*)(data_ + (size_) * sizeof(T));
    }
    //----------------------------------------------------------------------------------------//
    
    void resize(size_t new_size){
        
        char* tmp_data = allocate_mem(new_size, *this);        
        free_alocated_mem();

        data_     = tmp_data;
        size_     = new_size;
        capacity_ = size_;
    }
    //----------------------------------------------------------------------------------------//
    
    void* operator new(size_t size){
        std::cout << "vector new was called\n";

        void* p_new_mem = calloc(size, 1);
        if(p_new_mem == NULL)  throw std::bad_alloc();

        return p_new_mem;
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete(void* ptr){
        std::cout << "vector delete was called\n";
        free(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
    void* operator new[](size_t size){
        std::cout << "vector new[] was called\n";
    
        void* p_new_mem = calloc(size, 1);
        if(p_new_mem == NULL)  throw std::bad_alloc();

        return p_new_mem;
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete[](void* ptr){
        std::cout << "vector delete[] was called\n";
        free(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
    constexpr size_t size()  const { return size_; }
    constexpr bool   empty() const { return size_ == 0; }

private:
    char* data_;
    size_t size_, capacity_;

    void free_alocated_mem(){
        for(uint n_elem = 0; n_elem < capacity_; n_elem++){
            (*(T*)(data_ + n_elem * sizeof(T))).~T();
        }
        delete [] data_;
    }
    //----------------------------------------------------------------------------------------//
    
    char* allocate_mem(size_t capacity, const T& def_val){

        char* ptr_data = new char[capacity * sizeof(T)];
        memset(ptr_data, POISON_VAL, capacity * sizeof(T));

        int n_elem = 0;
        try{
            for(; n_elem < capacity; n_elem++){
                new (ptr_data + n_elem * sizeof(T)) T(def_val);
            }
        }
        catch(const std::bad_alloc& err){
            n_elem--;
            for(;n_elem > -1; n_elem--){
                (*(T*)(data_ + n_elem * sizeof(T))).~T();
            }
            delete[] ptr_data;

            throw err;
        }
        return ptr_data;
    }
    //----------------------------------------------------------------------------------------//
    
    char* allocate_mem(size_t capacity){

        char* ptr_data = new char[capacity * sizeof(T)];
        memset(ptr_data, POISON_VAL, capacity * sizeof(T));

        int n_elem = 0;

        try{
            for(; n_elem < capacity; n_elem++){
                new (ptr_data + n_elem * sizeof(T)) T();
            }
        }
        catch(const std::bad_alloc& err){
            n_elem--;
            for(;n_elem > -1; n_elem--){
                (*(T*)(data_ + n_elem * sizeof(T))).~T();
            }
            delete[] ptr_data;

            throw err;
        }

        return ptr_data;
    }
    //----------------------------------------------------------------------------------------//
    
    char* allocate_mem(size_t capacity, const vector& from_mem){

        char* ptr_data = new char[capacity * sizeof(T)];
        memset(ptr_data, POISON_VAL, capacity * sizeof(T));

        size_t active_size = (capacity > from_mem.size()) ? from_mem.size() : capacity;

        int n_elem = 0;

        try{
            for(; n_elem < active_size; n_elem++){
                new (ptr_data + n_elem * sizeof(T)) T(from_mem[n_elem]);
            }
        }
        catch(const std::bad_alloc& err){
            n_elem--;
            for(;n_elem > -1; n_elem--){
                (*(T*)(data_ + n_elem * sizeof(T))).~T();
            }

            delete[] ptr_data;
            throw err;
        }
        return ptr_data;
    }
    //----------------------------------------------------------------------------------------//
    
    void increase_capacity(){

        char* tmp_data = allocate_mem(capacity_ * INCREASE_RATIO, *this);
        free_alocated_mem();

        data_     = tmp_data;
        capacity_ = capacity_ * INCREASE_RATIO;
    }
    //----------------------------------------------------------------------------------------//
    
    void reduce_capacity(){

        uint new_capacity = capacity_ / REDUCE_RATIO;

        char* tmp_data = allocate_mem(new_capacity, *this);
        free_alocated_mem();

        data_     = tmp_data;
        capacity_ = new_capacity;
    }
    //----------------------------------------------------------------------------------------//
};
//----------------------------------------------------------------------------------------//
}
