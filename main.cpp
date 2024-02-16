#include <iostream> 
#include <fstream>
#include <cassert>
#include <thread>
#include <mutex>
using namespace std;

ofstream outfile; //Global output file stream
int nextVal     = 1;
int primesCount = 0;
int count1      = 0;
int count2      = 0;
int count3      = 0;
int count4      = 0;
mutex primeCountGuard;

bool is_prime(int value) {

    for (int i = 2; i <= (value / 2); ++i) {
        if (value % i == 0) {
            return false;
        }
    }
    return true;
}

void update(int value) {        
    lock_guard<mutex> lock(primeCountGuard); 
    ++primesCount;
    outfile.open("primes.dat", std::ios::app);
    outfile << value << endl;
    outfile.close();
}

void Thread1() {
    for (int i = 2; i <= 500'000; ++i) {
        if (is_prime(i)) {
            update(i);
            ++count1;
        }
    }
    cout << "Thread 1" << endl;
}

void Thread2() {
    for (int i = 500'001; i <= 750'000; ++i) {
        if (is_prime(i)) {
            update(i);
            ++count2;
        }
    }
    cout << "Thread 2" << endl;
}

void Thread3() {
    for (int i = 750'001; i <= 900'000; ++i) {
        if (is_prime(i)) {
            update(i);
            ++count3;
        }
    }
    cout << "Thread 3" << endl;
}

void Thread4() {
    for (int i = 900'001; i <= 1'000'000; ++i) {
        if (is_prime(i)) {
            update(i);
            ++count4;
        }
    }
    cout << "Thread 4" << endl;
}

int main() {
    thread t1(Thread1);
    thread t2(Thread2);
    thread t3(Thread3);
    thread t4(Thread4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    cout << "REPORT:" << endl << endl;
    cout << "Thread 1 found " << count1 << " prime numbers" << endl;
    cout << "Thread 2 found " << count2 << " prime numbers" << endl;
    cout << "Thread 3 found " << count3 << " prime numbers" << endl;
    cout << "Thread 4 found " << count4 << " prime numbers" << endl;
    cout << "Total prime numbers found: " << primesCount;
}   
