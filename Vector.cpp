#include"Vector.h"

namespace cc
{
    template<typename T>
    Vector<T>::Vector(const Vector&other){
        m_last = m_first = alloc.allocate(other.size());
        m_end = m_first+other.size();
        std::uninitialized_copy(other.cbegin(),other.cend(),m_first);
        //uninitialized_copy调用输入序列中每个元素的构造函数，以将该元素“复制”到目标中。
    }
      template<typename T>
     Vector<T>::Vector(size_type count, const T &value) {
        m_first = alloc.allocate(count);
        m_last = m_end = m_first + count;
        uninitialized_fill_n(m_first, count, value);
    }

    template<typename T>
    Vector<T>::Vector(std::initializer_list<T> init):Vector(init.begin(),init.begin()){

    }
    template<typename T>
    template<typename InputIterator>
    Vector<T>::Vector(InputIterator first, InputIterator last)
    {
        m_first = alloc.allocate(last-first);
        m_last = m_end = m_first+(last-first);
        std::uninitialized_copy(first,last,m_first);
    }

    template<typename T>
    inline void Vector<T>::push_back(const T&t){
        check();
        alloc.construct(m_last++,t);
    }

    template<typename T>
    inline void Vector<T>::check(){
        if(m_last==m_end){  //满
            size_t new_size = size()?size()*2:1;//扩容
            reserve_aux(new_size);    //将原来的elements复制到新的空间

        }
    }

    template<typename T>
    void Vector<T>::reserve(size_t newsize){
        if(newsize>capacity){
            reserve_aux(newsize);
        }
    }

    template<typename T>
    void Vector<T>::reserve_aux(size_t newsize){
        iterator first = m_first;
        iterator last = m_last;
        m_first = alloc.allocate(newsize);

        std::uninitialized_copy(first,last,m_first);

        m_end = m_first+newsize;
        m_last = m_first+(last-first);

        destory(first,last);        //销毁原来的、
        alloc.deallocate(first,last-first);
    }

    template<typename T>
    void Vector<T>::destory(iterator beg,iterator end){
        for(iterator it = beg;it!=end;it++){
            alloc.destroy(beg);
        } 
    }

    template<typename T>
    typename Vector<T>::iterator Vector<T>::insert(iterator it,const T&t){
        if(it==end()){      //尾插直接push_back
            push_back(t);
            return end()-1;
        }

        iterator first = m_first;
        check();
        it = m_first+(it-first);        //重新分配了空间
        alloc.construct(m_last,*(m_last-1));    //拷贝最后一个元素到下一个位置
        std::copy_backward(it,m_last-1,m_last); //移动
        m_last++;
        T temp = t;
        *(it) = temp;
        return it;
    }

    template<typename T>
    template<typename InputIterator>
    typename Vector<T>::iterator Vector<T>::insert(iterator it, InputIterator begin, InputIterator end){
        iterator first = m_first;
        ptrdiff_t diff  = end-begin;
        size_t reserved_size = size()+diff;

        it = m_first+(it-first);   
        size_t inserted_size = end - begin;
        size_t elem_after = m_last - it;
        if(inserted_size<=elem_after){
            std::uninitialized_copy(m_last-diff,m_last,m_last);
            auto sz = capacity();
            std::copy_backward(it,m_last-diff,m_last);
            std::copy(begin,end,it);
        }else{
            std::uninitialized_copy(it,m_last,m_end-elem_after);

            std::uninitialized_fill(m_last,m_end-elem_after,T());
            copy(begin,end,it);
        }
        m_last +=diff;
        return it;
    }

    template<typename T>
    inline bool operator==(const Vector<T>&lhs,const Vector<T>&rhs){
        return std::equal(lhs.begin(),lhs.end(),rhs.begin());

    }
     template<typename T>
    inline bool operator!=(const Vector<T> &lhs, const Vector<T> &rhs) {
        return !std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<typename T>
    inline typename Vector<T>::reference Vector<T>::operator[](size_type index){
        return *(m_first+index);
    }

    template<typename T>
    inline typename Vector<T>::const_reference Vector<T>::operator[](size_type index) const {
        return *(m_first + index);
    }

    template<typename T>
    template<class... Args>
    inline void Vector<T>::emplace(iterator pos, Args &&... args) {
        insert(pos, T(args...));
    }


    template<typename T>
    inline void Vector<T>::pop_back() {
        alloc.destroy(--m_last);//销毁最后一个元素
        //shrink_to_fit();
    }

    template<typename T>
    void Vector<T>::resize(size_type count,T value){
        int diff = count-size();
        if(diff<0){
            destory(m_last+diff,m_last);
            m_last = m_last+diff;

            shrink_to_fit();
        }else{
            reserve(count);
            std::uninitialized_fill_n(m_last,diff,value);
            m_last +=count;
        }
    }

    template<typename T>
    inline void Vector<T>::shrink_to_fit(){
        if(capacity()&&size()<0.5*capacity()){
            size_t newsize = size()/2;
            reserve_aux(newsize);

            shrink_to_fit();       //递归
        }
    }

    template<typename T>
    inline void Vector<T>::clear(){
        destory(m_first,m_last);
        m_last = m_first;
    }

    template<typename T>
    inline void Vector<T>::swap(Vector&other){
        std::swap(m_first,other.m_first);
        std::swap(m_last,other.m_last);
        std::swap(m_end,other.m_end);
    }


    template<typename T>
    inline typename Vector<T>::iterator Vector<T>::erase(iterator pos){
        copy(pos+1,m_last,pos);//后面的元素往前移动一个
        erase_at_end(m_last-1);
        return pos;
    }
    template<typename T>
    inline typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last) {
        copy(last, m_last, first);
        erase_at_end(m_last - (last - first));
        return first;
    }

    template<typename T>
    inline typename Vector<T>::const_reference Vector<T>::at(size_type index) const {
        if (index >= size()) {
           std::__throw_out_of_range(__N("vector::_M_range_check"));
           
        }
        return (*this)[index];
    }

    template<typename T>
    inline typename Vector<T>::reference Vector<T>::at(size_type index) {
        if (index >= size()) {
            std::__throw_out_of_range(__N("vector::_M_range_check"));
        }
        return (*this)[index];
    }

    template<typename T>
    Vector<T>& Vector<T>::operator=(const Vector &other) {
        if (this == &other)
            return *this;
        clear();
        alloc.deallocate(m_first, capacity());
        m_first = alloc.allocate(other.capacity());
        m_end = m_first + other.capacity();
        uninitialized_copy(other.begin(), other.end(), m_first);
        m_last = m_first + other.size();
    }

}