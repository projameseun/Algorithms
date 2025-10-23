#include <iostream>

//#pragma once
//
//template<typename T>
//class ArrayList
//{
//private:
//    T* m_data;         // 데이터 시작 포인터
//    int m_size;        // 현재 데이터 개수
//    int m_capacity;    // 현재 capacity
//
//public:
//    ArrayList() : m_data(nullptr), m_size(0), m_capacity(0) {}
//
//    void push_back(const T& value);
//    void resize(int newCapacity);
//    int capacity() const { return m_capacity; }
//    int size() const { return m_size; }
//
//    T& operator[](int idx) { return m_data[idx]; }
//    const T& operator[](int idx) const { return m_data[idx]; }
//};
//
//template<typename T>
//inline void ArrayList<T>::push_back(const T& value)
//{
//    if (m_size == m_capacity)
//    {
//        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
//        resize(newCapacity);
//    }
//    m_data[m_size++] = value;
//}
//
//template<typename T>
//inline void ArrayList<T>::resize(int newCapacity)
//{
//    T* newData = new T[newCapacity];
//    for (int i = 0; i < m_size; ++i)
//    {
//        newData[i] = m_data[i];
//    }
//    delete[] m_data;
//    m_data = newData;
//    m_capacity = newCapacity;
//}


#pragma once

template<typename T>
class ArrayList
{
private:
    T* m_data;      // 데이터의 시작 포인터
    T* m_lastData;  // 현재 데이터 끝(다음 위치) 포인터
    T* m_endData;   // 할당된 메모리의 끝 포인터
    //const int iconst = 20;

public:
    //★★★★이니셜라이저를 쓰는이유 중요 ★★★★★
    /*
      1.직접 초기화 vs 대입의차이
        이니셜 라이저 리스트는 멤버 변수를 생성과 동시에 원하는값으로 초기화가능 
        함수본문에 대입(m_data = other.m_data;)는 먼저 멤버가 "기본값"(기본생성자)를 생성한후 다시 값을 대입(할당)한다.
      2.효율성
        포인터 같은 단순타입은 차이가 크게 없지만
        멤버가 클래서 타입(vector,string...등)이라면
        이니셜 라이저 리스트로 초기화하면 불필요한 기본생성 + 대입이 일어나지 않아 효율적
      3.const 멤버 참조멤버
        const멤버나 참조 멤버는 반드시 이니셜 리스트로만 초기화 가능
      4.c++ 표준컨벤션
        c++에서는 생성자에서 멤버를 초기화 할때 이니셜라이져 리스트를 사용하는것이 표준적이 권장되는 방식이다.
    */
    ArrayList() : m_data(nullptr), m_lastData(nullptr), m_endData(nullptr) 
    {
        
    }

    ~ArrayList()
    {
        delete[] m_data;
    }
    // 복사 생성자
    ArrayList(const ArrayList& other)
    {
        size_t sz = other.size();
        size_t cap = other.capacity();
        try 
        {
            m_data = (cap > 0) ? new T[cap] : nullptr;

            for (size_t i = 0; i < sz; ++i)
            {
                m_data[i] = other.m_data[i];

            }

            m_lastData = m_data + sz;
            m_endData = m_data + cap;
        }
        catch (...)
        {
            delete[] m_data;
            m_data = nullptr;
            m_lastData = nullptr;
            m_endData = nullptr;
            throw;
        }
    }

    // 이동 생성자
    ArrayList(ArrayList&& other) noexcept
        : m_data(std::move(other.m_data)),
        m_lastData(other.m_lastData),
        m_endData(other.m_endData)
    {
        other.m_data = nullptr;
        other.m_lastData = nullptr;
        other.m_endData = nullptr;
    }


    // 복사 대입 연산자 (깊은 복사)
    ArrayList& operator=(const ArrayList& other)
    {
        if (this == &other)
            return *this;


        size_t sz = other.size();
        size_t cap = other.capacity();
        T* newData = (cap > 0) ? new T[cap] : nullptr;

        try 
        {
            for (size_t i = 0; i < sz; ++i)
            {

                newData[i] = other.m_data[i];
            }
        }
        catch (...)
        {
            delete[] newData;
            throw;
        }
        
        delete[] m_data;
        m_data = newData;
        m_lastData = m_data + sz;
        m_endData = m_data + cap;
        return *this;
    }

    //이동 대입연산자
    //이동연산은 예외가 발생하지 않도록 noexcept를 설정하는이유
    //1.이동연산자는 자원의 소유권만 단순히 포인터 복사로 넘겨준다
    //실제로 메모리 할당 복사 복잡한 연산이 없으므로 예외가 발생할 일이 없다
    //예외가 발생할수 있는 코드는 new,복사,컨테이네 내부 값 복사등인데 , 이동연산자는 그런작업을 하지않는다
    ArrayList& operator =(ArrayList&& other)noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] m_data;
        m_data = other.m_data; //똑같은말 std::move(other.m_data);
        other.m_data = nullptr;
        other.m_lastData = nullptr;
        other.m_endData = nullptr;
        return *this;
    }

    void push_back(const T& value);
    void resize(size_t newCapacity);
    size_t capacity() const;
    size_t size() const;
    void clear();
    bool empty() const;
    void swap(ArrayList& other) noexcept;


public:
    T& operator[](int idx) { 
    
        if (idx >= size())
        {
            throw::out_of_range("ArrayList: index out of range");
        }
        
        return m_data[idx]; 
    }
    const T& operator[](int idx) const 
    { 
        if (idx >= size())
        {
            throw::out_of_range("ArrayList: index out of range");
        }
        return m_data[idx];
    }

    bool operator!=(const ArrayList& other)const
    {
        return !(*this == other);
    }
};

/*
    1. ODR(One Definition Rule) 위반 방지
    ?	템플릿 함수/클래스의 구현은 헤더 파일에 작성해야 합니다.
    ?	여러 소스 파일에서 같은 헤더가 포함되면
    동일한 함수 정의가 여러 번 컴파일됩니다.
    ?	이때 inline을 붙이면
    링커가 중복 정의를 하나로 간주하여
    링크 에러(ODR 위반)를 방지할 수 있습니다.
    ---
    2. 함수가 여러 번 정의되어도 안전
    ?	inline이 붙은 함수는
    여러 번 정의되어도 하나로 취급됩니다.
    ?	템플릿 멤버 함수는
    헤더에 구현할 때 반드시 inline을 붙이는 것이 안전합니다.
*/

template<typename T>
inline void ArrayList<T>::push_back(const T& value)
{
    if (m_lastData == m_endData)
    {
        
        size_t newCapacity = (capacity() == 0) ? 1 : capacity() * 2;    //첫번째 들어온데이터가아니라면 2배씩늘린다
        resize(newCapacity);
       
    }

   *m_lastData++ = value;       //포인터연산

}

template<typename T>
inline void ArrayList<T>::resize(size_t newCapacity)
{
    size_t oldSize = size();
    T* newData = nullptr;

    try
    {
       newData = new T[newCapacity];
       for (size_t i = 0; i < oldSize; ++i)
       {
           newData[i] = m_data[i];
       }
    }
    catch (...)
    {
        delete[] m_data;
        throw;
    }
    delete[] m_data;
    m_data = newData;
    m_lastData = m_data + oldSize;  //다음데이터 들어갈 위치를 가리키게만듬  //포인터연산
    m_endData = m_data + newCapacity;  // //포인터연산
}

template<typename T>
inline size_t ArrayList<T>::capacity() const
{
    return static_cast<size_t>(m_endData - m_data); //할당된메모리끝주소 - 현재주소
}

template<typename T>
inline size_t ArrayList<T>::size() const
{
    return static_cast<size_t>(m_lastData - m_data); //마지막 다음 - 현재주소
}
template<typename T>
inline void ArrayList<T>::clear()
{
  
        delete[] m_data;
        m_data = nullptr;
        m_lastData = nullptr;
        m_endData = nullptr;
    
}

template<typename T>
inline bool ArrayList<T>::empty() const
{
    return size() == 0;
}

template<typename T>
inline void ArrayList<T>::swap(ArrayList& other) noexcept
{
    std::swap(m_data, other.m_data);
    std::swap(m_lastData, other.m_lastData);
    std::swap(m_endData, other.m_endData);
}
