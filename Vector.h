#ifndef __VECTOR_H
#define __VECTOR_H
#include<memory>

namespace cc
{
        //申明
    template<typename T>
    class Vector;

    template<typename T>
    bool operator==(const Vector<T> &, const Vector<T> &);

    template<typename T>
    bool operator!=(const Vector<T> &, const Vector<T> &);

    template<typename T>
    class Vector {
        friend bool operator==<>(const Vector<T> &, const Vector<T> &);

        friend bool operator!=<>(const Vector<T> &, const Vector<T> &);

    public:
        //member type
        typedef T value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T *iterator;
        typedef const T *const_iterator;
        typedef std::reverse_iterator<T *> reverse_iterator;
        typedef std::reverse_iterator<const T *> const_reverse_iterator;
    private:
        std::allocator<T> alloc; //分配器

        iterator m_first; //首地址

        iterator m_last;    //尾地址

        iterator m_end; //最大地址

        void check();//检查是否满了,并扩容

        void destory(iterator beg, iterator end);

        void reserve_aux(size_t newsize);//将元素拷贝至变动后的地址

        void erase_at_end(iterator pos) { m_last = pos; }//将m_last 设为 pos

    public:
        //constructor
        //explicit Vector(size_type count);

        explicit Vector(const Vector &other);

        explicit Vector(size_type count,
                        const T &value = T());

        explicit Vector() { m_last = m_first = m_end = nullptr; };

        Vector(std::initializer_list<T> init);

        template<typename InputIterator>
        explicit Vector(InputIterator first, InputIterator last);

        Vector& operator=(const Vector&);
        ~Vector() {
            clear();
            alloc.deallocate(m_first, capacity());
        }//析构

        //modifiers
        void push_back(const T &t);

        iterator insert(iterator it, const T &t);

        template<typename InputIterator>
        iterator insert(iterator it, InputIterator begin, InputIterator end);

        template<class... Args>
        void emplace(iterator pos, Args &&... args);

        void pop_back();

        void resize(size_type count, T value = T());//若当前大小小于count则追加元素，否则将大小调整为count

        void clear();//清除所有元素,但容量不变

        void swap(Vector &other);//交换m_first,m_last,m_end

        iterator erase(iterator pos);//并不实际删除元素

        iterator erase(const_iterator pos);

        iterator erase(iterator firstx, iterator last);

        iterator erase(const_iterator first, const_iterator last);

        void shrink_to_fit();//递归的缩小

        //capacity
        bool empty() const { return m_first == m_last; };

        size_type size() const { return m_last - m_first; };

        void reserve(size_t newsize);

        size_type capacity() const { return m_end - m_first; };

        //itrator
        iterator begin() const { return m_first; };

        iterator end() const { return m_last; };

        const_iterator cbegin() const { return m_first; };

        const_iterator cend() const { return m_end; };

        const_reverse_iterator crbegin() const { return std::reverse_iterator<const T *>(m_first); };


        const_reverse_iterator crend() const { return std::reverse_iterator<const T *>(m_end); };

        //element access
        reference at(size_type index);

        const_reference at(size_type index) const;

        reference front() { return *m_first; };

        const_reference front() const { return *m_first; }

        reference back() { return *(m_last - 1); }

        const_reference back() const { return *(m_last - 1); }

        const_reference operator[](size_type pos) const;

        reference operator[](size_type pos);

    };
  


};


#endif