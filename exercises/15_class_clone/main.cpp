#include "../exercise.h"
int globalvar = 20;
// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]{0 , 1}), cached(2) {
    }

    // TODO: 实现复制构造器
    DynFibonacci(DynFibonacci const & fib_) {
        this->cache = new size_t[fib_.cached];
        for (int i = 0; i < fib_.cached;i ++ ) {
            this->cache[i] = fib_.cache[i];
        }
        this->cached = fib_.cached;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        if(cache != NULL)
            delete cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int& foo() {
	int globalvar = 2;
    return globalvar;
}

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    std::cout << fib_.get(10) << '\n';
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned")
    return 0;
}
