// unique_ptr, shared_ptr experiments
//
#include <cstring>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>


void shared_pointer( void );
void unique_pointer( void );
void unique_pointer_array( void );
void unique_pointer_array_malloc( void );

class Thing {
public:
    Thing(int n) {
        m_x = n;
        std::cout << "+Thing(" << m_x << ")" << std::endl;
    }
    ~Thing() {
        std::cout << "-Thing(" << m_x << ")" << std::endl;
    }
    void Increment() {
        m_x++;
    }
    int GetX() {
        return m_x;
    }
private:
    int m_x;
};

int main( int argc, char** argv )
{
    shared_pointer();
    unique_pointer();
    unique_pointer_array();
    unique_pointer_array_malloc();
    return 0;
}


std::shared_ptr<Thing> fs( std::shared_ptr<Thing> x, int n )
{
    for ( int i = 0; i < n; i++ ) {
        x->Increment();
    }
    return x;
}

void shared_pointer( void )
{
    std::cout << __FUNCTION__ << std::endl;

    std::shared_ptr<Thing> p1( new Thing( 200 ) );
    std::cout << p1->GetX() << std::endl;
    std::shared_ptr<Thing> p2 = fs( p1, 5 );
    // p1 is still valid ater copy into fs()
    std::cout << (p1.get())->GetX() << std::endl;
    std::cout << p2->GetX() << std::endl;

}

std::unique_ptr<Thing> fu( std::unique_ptr<Thing> x, int n )
{
    for ( int i = 0; i < n; i++ ) {
        x->Increment();
    }
    return x;
}

void unique_pointer( void )
{
    std::cout << __FUNCTION__ << std::endl;

    std::unique_ptr<Thing> p1( new Thing( 300 ) );
    std::cout << p1->GetX() << std::endl;
//    std::unique_ptr<Thing> p2 = fu( p1, 5 );
    // p1 is no longer valid ater copy into fu()
    //std::cout << (p1.get())->GetX() << std::endl;
//    std::cout << p2->GetX() << std::endl;
}

void unique_pointer_array( void )
{
    std::cout << __FUNCTION__ << std::endl;

    const int N = 10;
    std::unique_ptr<int[]> ip( new int[N] );

    for ( int i = 0; i < N; i++ )
        ip[i] = i * i;

    for ( int i = 0; i < N; i++ )
        std::cout << ' ' << ip[i];
    std::cout << std::endl;
}

// Deleter for malloc'd memory
class free_delete
{
public:
    free_delete() {}
    void operator()(int *ptr) const {
        std::cout << "free_delete()" << std::endl;
        if (ptr != nullptr)
            free(ptr);
    }
};

void unique_pointer_array_malloc( void )
{
    std::cout << __FUNCTION__ << std::endl;

    const int N = 10;
    std::unique_ptr<int, free_delete> up(
            static_cast<int *>(malloc( N * sizeof(int) ) ) );
    int *x = up.get();

    for ( int i = 0; i < N; i++ )
        x[i] = i * i;

    for ( int i = 0; i < N; i++ )
        std::cout << ' ' << x[i];
    std::cout << std::endl;
}

