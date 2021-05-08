#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>

const size_t RESERVE = 10;

template <typename T>
class my_allocator
{
public:
	T *allocate(size_t);
	void deallocate(T*);
};

template <typename T, typename Allocator = my_allocator<T>>
class Vector
{
	T *data;
	size_t vec_size;
	size_t allocated_size;
	Allocator vec_alloc;
	
public:

	//  Итераторы
	class base_iterator
	{
	protected:
		T* pointer;
	public:
		base_iterator(T* = nullptr);
		T& operator*();
		bool operator!=(const base_iterator&);
	};
	
	class iterator : public base_iterator
	{
		using base_iterator::base_iterator;
	public:
		iterator& operator++();
	};
	
	class reverse_iterator : public base_iterator
	{
		using base_iterator::base_iterator;
	public:
		reverse_iterator& operator++();
	};
	
	//  Конструкторы
	Vector();
	Vector(const Vector<T>&);
	Vector(size_t, T = T());
	Vector(const std::initializer_list<T>&);
	
	//  Деструктор
	~Vector();
	
	//  Перегруженные опреаторы
	T& operator[](size_t);
	Vector<T>& operator=(const Vector<T>&);
	
	//  Работа с итераторами
	iterator begin() const;
	iterator end() const;
	reverse_iterator rbegin() const;
	reverse_iterator rend() const;
	
	//  Прочее
	void push_back(const T&);
	void emplace_back(const std::initializer_list<T>&);
	void pop_back();
	bool empty() const noexcept;
	size_t size() const noexcept;
	size_t capacity() const noexcept;
	void clear();
	void resize(size_t, T = T());
	void reserve(size_t);
	
	//  Вспомогательное
	size_t get_size() const noexcept;
	void print_data() const noexcept;
};

//  Методы аллокатора

template <typename T>
T *my_allocator<T>::allocate(size_t size)
{
	return new T[size];
}

template <typename T>
void my_allocator<T>::deallocate(T *to_delete)
{
	delete []to_delete;
}

//  Методы итераторов

template <typename T, typename Allocator>
Vector<T, Allocator>::base_iterator::base_iterator(T *elem)
{
	pointer = elem;
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::base_iterator::operator*()
{
	return *pointer;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::base_iterator::operator!=(const base_iterator &other)
{
	return this->pointer != other.pointer;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator& Vector<T, Allocator>::iterator::operator++()
{
	this->pointer += 1;
	return *this;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator& Vector<T, Allocator>::reverse_iterator::operator++()
{
	this->pointer -= 1;
	return *this;
}





//  Методы вектора

//  Конструктор по умолчанию
template <typename T, typename Allocator>
Vector<T, Allocator>::Vector()
{
	data = nullptr;
	vec_size = 0;
	allocated_size = 0;
}

//  Конструктор копирования
template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector<T> &other)
{
	vec_size = other.vec_size;
	allocated_size = other.allocated_size;
	data = vec_alloc.allocate(allocated_size);
	for (size_t i = 0; i < vec_size; ++i)
		data[i] = other.data[i];
}

//  Конструктор вектора со значениями по умолчанию
template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_t size, T default_val)
{
	vec_size = size;
	allocated_size = size + RESERVE;
	data = vec_alloc.allocate(allocated_size);
	for (size_t i = 0; i < vec_size; ++i)
		data[i] = default_val;
}

//  Конструктор из списка инициализации
template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const std::initializer_list<T> &values)
{
	vec_size = values.size();
	allocated_size = vec_size + RESERVE;
	data = vec_alloc.allocate(allocated_size);
	auto p = values.begin();
	for (size_t i = 0; i < vec_size; ++i)
	{
		data[i] = *p;
		++p;
	}
}

//  Деструктор
template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector()
{
	//if (data)
	//	delete []data;
	vec_alloc.deallocate(data);
	data = nullptr;
}

//  Перегрузка []
template <typename T, typename Allocator>
T& Vector<T, Allocator>::operator[](size_t index)
{
	if (index < vec_size)
		return data[index];
	else
		throw std::out_of_range("Error: index exceeds vector size");
}

template <typename T, typename Allocator>
Vector<T>& Vector<T, Allocator>::operator=(const Vector<T> &other)
{
	vec_alloc.deallocate(data);
	vec_size = other.vec_size;
	allocated_size = other.allocated_size;
	data = vec_alloc.allocate(allocated_size);
	for (size_t i = 0; i < vec_size; ++i)
		data[i] = other.data[i];
	return *this;
}

//  Итераторные функции
template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::begin() const
{
	return iterator(data);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::end() const
{
	return iterator(data + vec_size);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rbegin() const
{
	return reverse_iterator(data + vec_size - 1);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rend() const
{
	return reverse_iterator(data - 1);
}


//  Добавление элемента в конец вектора
template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(const T &elem)
{
	if (vec_size < allocated_size)
	{
		data[vec_size] = elem;
		vec_size++;
	}
	else
	{
		allocated_size += RESERVE;
		T *new_data = vec_alloc.allocate(allocated_size);
		for (size_t i = 0; i < vec_size; i++)
			new_data[i] = data[i];
		new_data[vec_size] = elem;
		vec_alloc.deallocate(data);
		data = new_data;
		vec_size += 1;
	}
	
}

//  Добавление нескольких элементов в конец вектора
template <typename T, typename Allocator>
void Vector<T, Allocator>::emplace_back(const std::initializer_list <T> &args)
{
	size_t elements = args.size();
	auto p = args.begin();
	if (vec_size + elements <= allocated_size)
	{
		for (size_t i = vec_size; i < vec_size + elements; ++i)
		{
			data[i] = *p;
			++p;
		}
		vec_size += elements;
	}
	else
	{
		allocated_size = vec_size + elements + RESERVE;
		T *new_data = vec_alloc.allocate(allocated_size);
		for (size_t i = 0; i < vec_size; ++i)
			new_data[i] = data[i];
		for (size_t i = vec_size; i < vec_size + elements; ++i)
		{
			new_data[i] = *p;
			++p;
		}
		vec_alloc.deallocate(data);
		data = new_data;
		vec_size += elements;
		
	}
}

//  Удаление элемента в конце вектора
template <typename T, typename Allocator>
void Vector<T, Allocator>::pop_back()
{
	if (vec_size > 0)
		vec_size--;
	else
		throw std::logic_error("Error: attempt to pop_back from an empty vector");
}

//  Проверка на пустоту вектора
template <typename T, typename Allocator>
bool Vector<T, Allocator>::empty() const noexcept
{
	return (vec_size == 0);
}

//  Получение количества элементов в векторе
template <typename T, typename Allocator>
size_t Vector<T, Allocator>::size() const noexcept
{
	return vec_size;
}

//  Получение максимального числа элементов в выделенной памяти вектора
template <typename T, typename Allocator>
size_t Vector<T, Allocator>::capacity() const noexcept
{
	return allocated_size;
}

//  Очистка содержимого вектора (выделенная память остаётся)
template <typename T, typename Allocator>
void Vector<T, Allocator>::clear()
{
	vec_size = 0;
}

//  Изменение размера вектора
template <typename T, typename Allocator>
void Vector<T, Allocator>::resize(size_t new_size, T default_value)
{
	if (new_size <= vec_size)
		vec_size = new_size;
	else if (new_size <= allocated_size)
	{
		for (size_t i = vec_size; i < new_size; i++)
			data[i] = default_value;
		vec_size = new_size;
	}
	else
	{
		allocated_size = new_size + RESERVE;
		T *new_data = vec_alloc.allocate(allocated_size);
		for (size_t i = 0; i < vec_size; i++)
			new_data[i] = data[i];
		for (size_t i = vec_size; i < new_size; i++)
			new_data[i] = default_value;
		vec_alloc.deallocate(data);
		data = new_data;
		vec_size = new_size;
	}
}

//  Выделение резервной памяти для вектора
template <typename T, typename Allocator>
void Vector<T, Allocator>::reserve(size_t new_cap)
{
	if (new_cap > allocated_size)
	{
		allocated_size = new_cap;
		T *new_data = vec_alloc.allocate(allocated_size);
		for (size_t i = 0; i < vec_size; i++)
			new_data[i] = data[i];
		vec_alloc.deallocate(data);
		data = new_data;
	}
}



template <typename T, typename Allocator>
size_t Vector<T, Allocator>::get_size() const noexcept
{
	return vec_size;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::print_data() const noexcept
{
	for (size_t i = 0; i < vec_size; i++)
		std::cout << data[i] << ' ';
	std::cout << std::endl;
}