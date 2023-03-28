// сырые указатели и забытый delete - это плохо!

// либо мы забудем delete, либо вылетим из блока из-за исключения

//пример №1

#include <vector>

#include <iostream>

void unsafe_function() {

	if (rand() % 2) {		throw std::runtime_error("Исключение!");

	}

}

void do_something() {

	std::vector<int>* vec = new std::vector<int>();

	unsafe_function;

	delete vec; //До сюда не дойдем, если выкинет исключение 

}

int main() {

	try {

		do_something();

	}

	catch (const std::runtime_error& exception) {

		std::cout << exception.what() << std::endl;

	}//придется писать много трайев для отлова исключений - много кода и очень муторно

}

//решение есть - создадим класс, который за нас будет владеть указателем, как неким ресурсом

//и будет его удалять этот ресурс по взову деструктора - умный указатель

// смарт поинтер №1: std::auto_ptr

//в C++11 уже  был устаревшим, в 17 ремувнули (проблема при копировании: происходило перемещение,

// и могли быть неявные ошибки вроде nullptr

//смарт поинтер №2: std::unique_ptr

// когда он выходит из области видимости, утечки памяти не происходит,

//вызывает delete для объекта на который ссылается, освобождает память

//вот из этого кода. где ошибки при исключении, и при выполнении func2();

X* ptr = new X();

if (func()) {

	func2();

	return;

}

delete ptr;

//перепишем:

std::unique_ptr<X> ptr(new X()); // или auto ptr = std::make_unique<X>();

if (func()) {                    // так не юзаем new/delete вовсе

	func2();

	return;

}

//есть перегрузки операторов для использования как простые указатели:

T& operator*() {

	return *ptr;

}

T* operator->() {

	return ptr;

}

std::unique_ptr <ptr[]> a(new int[10000]); //когда переданнный шаблонный тип является типом-массивом

// можно юзать кастомные делитеры

//смарт поинтер №2: std::shared_ptr

//для использования ресурса в разных местах

//unique_ptr + счетчик указателей, когда он ноль - делит

#include <iostream>

struct logger {

	logger() {

		std::cout << "логгер построен тут" << this << std::endl;

	}

	~logger() {

		std::cout << "логгер удален тут" << this << std::endl;

	}

};

template <typename vt>

class shared_ptr {

	struct control_block {

		vt* ptr;

		size_t use_count;

	};

};

struct user {

	explicit user(const std::shared_ptr<vt>& ptr): _ptr(ptr) {}

private:

	std::shared_ptr<vt> _ptr;

};

int main() {

	std::shared_ptr<logger> ptr(new logger);

	user<logger> first(ptr);

	user<logger> second(ptr);

}

//в след примере показано, как может быть утечка памяти для shared_ptr:

struct second;

struct first { std::shared_ptr<second> ptr; };

struct second { std::shared_ptr<first ptr; }; //меняем на weak

int main() {

	std::shared_ptr<first> a(new first);

	std::shared_ptr<second> b(new second);

	a->ptr = b;

	b->ptr = a;

}

//std::weak_ptr - тоже, что и shared, только не влыдеет данными

//позволяет узнать, жив ли объект и создать shared_ptr если да

//проверка:

bool expired();

//создание поинтера на объект:

std::shared_ptr<T> lock();

//Чтобы дать возможность пользователю вашего класса 

//получать shared_ptr на него же, нужно унаследовать ваш класс от std::enable_shared_from_this:
