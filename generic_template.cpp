#include <stdio.h>
#include <typeinfo> // typeid()
#include <cxxabi.h> // Demangle typeid().name() crap
#include <assert.h> // assert()

// Generic Template
// ------------------------------------------------------------------------
template <typename T,size_t N>
    class Array
    {
        T* _pArray;

    public:
        size_t _nLength;

        Array()
        {
            // More C++ shit -- typeid( T ).name() does NOT return a human readable name
            // but a C++ mangled one
            int         nStatus;
            const char* pParam = typeid(T).name() ;
            const char* pName  = abi::__cxa_demangle( pParam, NULL, NULL, &nStatus );
            printf( "\nGeneric Template: %s\n", pName );

            _nLength  = N;
            _pArray = new T[ N ];

            size_t size = &_pArray[ N ] - &_pArray[ 0 ];
            printf( "Elements: %lu,  Element Size (bits): %u,  Array Size: %u\n"
                , N, (unsigned) sizeof(T) * 8, (unsigned) size
            );
        }

        // non-const object
        T& operator []( const size_t i ) {
            assert( i < _nLength ); // DEBUG

            return _pArray[ i ];
        }

        // const object
        const T& operator []( const size_t i ) const {
            assert( i < _nLength ); // DEBUG

            return _pArray[ i ];
        }
    };

// ========================================================================
int main()
{
    Array<char,4096> foo;
    foo[ 1 ] = 123;

    Array<bool,4096> bar;
    bar[ 1 ] = 1;

    return 0;
}

