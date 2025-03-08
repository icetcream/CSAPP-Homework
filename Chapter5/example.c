long count = 0;
inline long f(){
    return count ++;
}

long func1(){
    return f()+f()+f()+f();
}

long f1(){
    return ++count ;
}