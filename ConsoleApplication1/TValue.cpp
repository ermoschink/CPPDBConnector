#include "stdafx.h"
#include "TValue.h"

template<class T>
TValue<T>::TValue(T field, T val)
{
}

template<class T>
T TValue<T>::getField() {
	return this->field;
}

template<class T>
T TValue<T>::getValue() {
	return this->value;
}