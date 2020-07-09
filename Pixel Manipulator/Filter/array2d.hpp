#include "array2d.h"

namespace math {

	template <typename T>
	const unsigned int Array2D<T>::getWidth() const {
		return width;
	}

	template <typename T>
	const unsigned int Array2D<T>::getHeight() const {
		return height;
	}

	template <typename T>
	T* Array2D<T>::getRawDataPtr() {
		T* arr = &buffer[0];
		return arr;
	}

	template <typename T>
	void Array2D<T>::setData(const T* const& data_ptr) {
		int size = getWidth() * getHeight();

		std::vector<T>* vec = new std::vector<T>(data_ptr, data_ptr + size);
		this->buffer = *vec;
	}

	template <typename T>
	T& Array2D<T>::operator () (unsigned int x, unsigned int y) {
		
		return buffer[y * width + x];
	}

	template <typename T>
	Array2D<T>::Array2D(unsigned int width, unsigned int height, const T* data_ptr) {
		this->width = width;
		this->height = height;
		this->setData(data_ptr);
	}

	template <typename T>
	Array2D<T>::Array2D(const Array2D& src) {

		this->width = src.getWidth();
		this->height = src.getHeight();
		const T* const arr = &src.buffer[0];
		setData(arr);

	}

	template <typename T>
	Array2D<T>::~Array2D() {}

	template <typename T>
	Array2D<T>& Array2D<T>::operator = (const Array2D& right) {
		this->width = right.getWidth();
		this->height = right.getHeight();
		const T* const arr = &right.buffer[0];
		setData(arr);
		Array2D <T> ref = right;
		return ref;

	}
}