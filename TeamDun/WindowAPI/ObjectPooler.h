#pragma once

#include <stack>
#include <mutex>

typedef std::lock_guard<std::recursive_mutex> MutexLocker;

template<typename T>
class objectPool
{

	// 오브젝트 풀러는 가장 최근에 넣은걸 그냥 빼다가 가져 쓰기때문에, 후입선출 [STACK]을 사용한다.

private:
	std::recursive_mutex	_mt;
	std::stack<T*>			_objects;	// 오브젝트들을 미리 생성해 저장해두는 오브젝트 STACK
	int						_maxSize;	// 최대 배열 크기

public:
	objectPool();
	~objectPool();
	T* PopObject();
	void SetSize(int size);
	void Expand();
	void ReturnObject(T* object);
	int ReturnSize();
};

template<typename T>
objectPool<T>::objectPool() {}

// 오브젝트풀러를 비운다. (실질적인 RELEASE)
template<typename T>
objectPool<T>::~objectPool()
{
	MutexLocker locker(_mt);
	while (!_objects.empty()) {
		T* object = _objects.top();
		_objects.pop();
		delete object;
	}

	_maxSize = 0;
}

// 오브젝트풀러의 사이즈를 지정한다
template<typename T>
void objectPool<T>::SetSize(int size) {
	_maxSize = size;

	for (int i = 0; i < _maxSize; ++i) { // _maxSize만큼 오브젝트를 만들어둔다
		T* newObject = new T();
		_objects.push(newObject);
	}
}

// 오브젝트를 꺼낸다
template<typename T>
T* objectPool<T>::PopObject()
{
	MutexLocker locker(_mt);

	// 오브젝트가 없다면 확장한다
	if (_objects.empty()) {
		Expand();
	}

	T* retVal = _objects.top();
	_objects.pop();
	return retVal;
}

// 현재 크기만큼 새로운 오브젝트를 넣어 확장한다
template<typename T>
void objectPool<T>::Expand() {
	MutexLocker locker(_mt);

	for (int i = 0; i < _maxSize; ++i)
	{
		T* newObject = new T();
		_objects.push(newObject); // 새로운 오브젝트를 만들어 오브젝트 풀러에 넣는다
	}

	_maxSize += _maxSize;
}

// 오브젝트를 수거한다.
template<typename T>
void objectPool<T>::ReturnObject(T* object)
{
	MutexLocker locker(_mt);
	_objects.push(object); // 받아온 오브젝트를 다시 오브젝트 풀러에 넣어준다.
}

template<typename T>
int objectPool<T>::ReturnSize()
{
	return _objects.size();
}