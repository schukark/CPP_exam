// назначение: для особых случаев в коде, для которых функция , метод или код не будет работать
// sample
double calc(const double x){
    if(x < 0.){
        throw "nelya vizvat";
    }
}
// программа выдаст просто ошибку сам вердикт выведен не будет для них надо пистаь try catch
int main(){
    int x;
    x = 1;
    try{
        std::cout << calc(x) << endl;
    }
    catch(const char* const str){
        std::cout << "calc except" << str << endl; // чтобы выдать именно то что нам надо то есть массив чаров
    }
 
}
try{
    throw son{};
}
catch(const granny& g){
    std::cout << "grann" << endl;
}
catch(const mom& g){
std::cout << "mom" << endl;
}
catch(const son& g){
std::cout << "son" << endl;
}
// здесь выведется grann, если написать catch son, то выведется son
try{
    f();
}
catch (...){
    std::cout << "error" << endl;
}
// ловит все ошибки
 
try{
    try{
        catch(...){
            cout << "error" << endl;
            throw; // позволяет продолжить ловить исключения
        }
    }
    catch(...){
        cout << "error" << endl;
    }
}
// выходит из первого кэча и позволяет ловить их во втором
 
try{
    logger l;
    cout << &l << endl;
    // неверно throw l;
    // верно throw logger();
  //создается еще одна копия  поэтому нельзя делать throw l
}
catch(const logger& l){
    std::cout << &l << endl;
}
 
try{
    derived d;
    base& b = d;
    throw b;
}
catch(const base& b ){
    cout << "base";
}
catch(const derived& b ){
cout << "derived";
}
// тут дважды будет выведено base, потому что будет обрезание наследника
 
 
 
struct ugly{
    ugly() : _arr(new  int[100]){
        std::cout << "mem alloc";
        throw 123;
    }
    ~ugly(){
        throw 123;
    }
};
 
try {
    ugly u;
}
catch(...){
    std::cout << "except caught" << endl;
}
// деструктор не будет вызван, поэтому будет утечка памяти
try{
    ugly u;
    trhow 456;
}
catch(...){
    cout << "except caught" << endl;
}
// сначала выпадет 456, а 123 не будет обработано поэтому выдаст ошибку.
 
 
struct my_exception : std::exception{
    my_exception(const char* description): _description(description){}
    const char* what() const noexcept override{
        return _description;
    }
private:
    const char* _description;
};
// свое exception