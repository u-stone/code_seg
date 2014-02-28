/*
Author: Liu Guoyuan  
mail:   lgy-047@163.com
Date:   2014/2/28
*/

#ifndef NEWHANDLER_H
#define NEWHANDLER_H

class newhandlerholder{//raii idiom, for hold new_handler func
public:
	explicit newhandlerholder(std::new_handler ph):m_ph(ph){
		
	}
	~newhandlerholder(){
		std::set_new_handler(m_ph);
	}
private:
	newhandlerholder(newhandlerholder const& rhs){}
	newhandlerholder operator=(newhandlerholder const& rhs){}
private:
	std::new_handler  m_ph;
};

template <typename T>
class INewSpec{//spectialize new operator behave
public:
	static std::new_handler set_new_handler(std::new_handler p)throw();
	static void* operator new(std::size_t size)throw(std::bad_alloc);
private:
	static std::new_handler s_nh;
};

template<typename T>
std::new_handler INewSpec<T>::s_nh = 0;

template<typename T>
std::new_handler INewSpec<T>::set_new_handler(std::new_handler p)throw(){
	std::new_handler oldnh = std::set_new_handler(p);
	s_nh = p;
	return oldnh;
}

template<typename T>
void* INewSpec<T>::operator new(std::size_t size) throw (std::bad_alloc){
	newhandlerholder h(std::set_new_handler(s_nh));
	return ::operator new(size);//during this call, s_nh will be called if any exception was throw
}


#endif