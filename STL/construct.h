#pragma once

#include<new>
#include "iterator.h"


/*
���ļ���������ȫ�ֺ���
construct��������󹹽�
destroy��������������
*/
namespace mystl {


	//����Ĭ�Ϲ��캯������
	template <class Ty>
	void construct(Ty* ptr) {
		::new ((void*)ptr) Ty();
	}

	//һ��Ҫ��const������,�˰汾��Ĭ�Ϲ��캯������������һ����ͬ���͵Ŀ������캯��
	template <class Ty1, class Ty2>
	void construct(Ty1* ptr, const Ty2& value) {
		::new ((void*)ptr) Ty1(value);
	}

	//destroy����

	//�������������޺��ģ����Կ��Բ��õ��ý�ʡ��Դ���ڴ���ͷ�destroy������
	template <class Ty>
	void _destroy_one(Ty* ptr, std::true_type) {}

	//�˺��������������к��ģ����Ա�����ø����͵����������ͷ���Դ
	template <class Ty>
	void _destroy_one(Ty* ptr, std::false_type) {
		ptr->~Ty();
	}

	template <class Forwarditerator>
	void _destroy_cat(Forwarditerator first, Forwarditerator last, std::true_type) {}

	template <class Forwarditerator>
	void _destroy_cat(Forwarditerator first, Forwarditerator last, std::false_type) {
		//�� �Ƿ����destroy����������++
		//��Ϊ��destroy��ͬ��erase��Ԫ��λ�ò������䶯�����ҵ���������������������Ӧ���ǿ��Ե�
		for (; first != last; ++first) {
			destroy(&*first);
		}
	}

	template <class Ty>
	void destroy(Ty* ptr) {
		_destroy_one(ptr, std::is_trivially_destructible<Ty>());
	}

	template <class Forwarditerator>
	void destroy(Forwarditerator first, Forwarditerator last) {
		_destroy_cat(first, last, std::is_trivially_destructible<
			value_type(Forwarditerator)>());
	}


}