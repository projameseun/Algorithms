#include <iostream>

//#pragma once
//
//template<typename T>
//class ArrayList
//{
//private:
//    T* m_data;         // ������ ���� ������
//    int m_size;        // ���� ������ ����
//    int m_capacity;    // ���� capacity
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
    T* m_data;      // �������� ���� ������
    T* m_lastData;  // ���� ������ ��(���� ��ġ) ������
    T* m_endData;   // �Ҵ�� �޸��� �� ������

public:
    ArrayList() : m_data(nullptr), m_lastData(nullptr), m_endData(nullptr) {}

    ~ArrayList()
    {
        delete[] m_data;
    }
    // ���� ������
    ArrayList(const ArrayList& other)
    {
        size_t sz = other.size();
        size_t cap = other.capacity();
        m_data = (cap > 0) ? new T[cap] : nullptr;

        for (size_t i = 0; i < sz; ++i)
        {
            m_data[i] = other.m_data[i];

        }

        m_lastData = m_data + sz;
        m_endData = m_data + cap;
    }

    // �̵� ������
    ArrayList(ArrayList&& other) noexcept
        : m_data(other.m_data),
        m_lastData(other.m_lastData),
        m_endData(other.m_endData)
    {
        other.m_data = nullptr;
        other.m_lastData = nullptr;
        other.m_endData = nullptr;
    }


    // ���� ���� ������ (���� ����)
    ArrayList& operator=(const ArrayList& other)
    {
        if (this == &other)
            return *this;


        size_t sz = other.size();
        size_t cap = other.capacity();
        T* newData = (cap > 0) ? new T[cap] : nullptr;
        for (size_t i = 0; i < sz; ++i)
        {

            newData[i] = other.m_data[i];
        }
        
        delete[] m_data;
        m_data = newData;
        m_lastData = m_data + sz;
        m_endData = m_data + cap;
        return *this;
    }

    //�̵� ���Կ�����
    ArrayList& operator =(ArrayList&& other)noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] m_data;
        m_data = other.m_data; //�Ȱ����� std::move(other.m_data);
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
    T& operator[](int idx) { return m_data[idx]; }
    const T& operator[](int idx) const { return m_data[idx]; }

    bool operator!=(const ArrayList& other)const
    {
        return !(*this == other);
    }
};

template<typename T>
inline void ArrayList<T>::push_back(const T& value)
{
    if (m_lastData == m_endData)
    {
        
        size_t newCapacity = (capacity() == 0) ? 1 : capacity() * 2;    //ù��° ���µ����Ͱ��ƴ϶�� 2�辿�ø���
        resize(newCapacity);
       
    }

   *m_lastData++ = value;       //�����Ϳ���

}

template<typename T>
inline void ArrayList<T>::resize(size_t newCapacity)
{
    size_t oldSize = size();
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < oldSize; ++i)
    {
        newData[i] = m_data[i];
    }
    delete[] m_data;
    m_data = newData;
    m_lastData = m_data + oldSize;  //���������� �� ��ġ�� ����Ű�Ը���  //�����Ϳ���
    m_endData = m_data + newCapacity;  // //�����Ϳ���
}

template<typename T>
inline size_t ArrayList<T>::capacity() const
{
    return static_cast<size_t>(m_endData - m_data); //�Ҵ�ȸ޸𸮳��ּ� - �����ּ�
}

template<typename T>
inline size_t ArrayList<T>::size() const
{
    return static_cast<size_t>(m_lastData - m_data); //������ ���� - �����ּ�
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
