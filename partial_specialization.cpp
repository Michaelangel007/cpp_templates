#include <stdio.h>
#include <typeinfo> // typeid()
#include <cxxabi.h> // GCC/Clang: Demangle typeid().name() crap

// Generic Template
// ------------------------------------------------------------------------
template <typename T,size_t N>
    class Array
    {
        T* _pArray;

    public:
        size_t length;

        Array()
        {
            // More C++ shit -- typeid( T ).name() does NOT return a human readable name
            // but a C++ mangled one
            int         nStatus;
            const char* pParam = typeid(T).name() ;
            const char* pName  = abi::__cxa_demangle( pParam, NULL, NULL, &nStatus );
            printf( "\nGeneric Template: %s\n", pName );

            length  = N;
            _pArray = new T[ N ];

            size_t size = &_pArray[ N ] - &_pArray[ 0 ];
            printf( "Elements: %lu,  Element Size (bits): %u,  Array Size: %u\n"
                , N, (unsigned) sizeof(T) * 8, (unsigned) size );
        }

        T& operator []( const size_t i ) {
            return _pArray[ i ];
        }
    };

// Partial Template Specialization
// ------------------------------------------------------------------------
template <size_t N>
    class Array<bool,N>
    {
        typedef char S;
        S* _pArray;

    public:
        size_t length;

        Array()
        {
            // More C++ shit -- typeid( T ).name() does NOT return a human readable name
            // but a C++ mangled one
            int         nStatus;
            const char* pParam = typeid(bool).name(); // NOTE: typename T == bool
            const char* pName  = abi::__cxa_demangle( pParam, NULL, NULL, &nStatus );
            printf( "\nPartial Template Specialization: %s\n", pName );

            const size_t len = (N + 7) / 8; // align(N,8);
            length  = len;
            _pArray = new S[ len ];

            size_t size = &_pArray[ len ] - &_pArray[ 0 ];

            printf( "Elements: %lu,  Element Size (bits): %u,  Array Size: %u\n"
                , N, (unsigned) sizeof(S), (unsigned) size ); // sizeof()_bytes * 8_bits/byte / 8_bits/element
            printf( "Saved bytes: %lu\n", N - size );
        }

        S& operator []( const size_t i ) {
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

