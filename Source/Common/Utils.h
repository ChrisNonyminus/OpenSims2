#pragma once
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <cstring>

typedef signed char        s8;
typedef signed short       s16;
typedef signed int         s32;
typedef signed long long   s64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

#ifdef _DEBUG
	#define debugBreak() _asm { int 3 }
    #define ASSERT(x) if (!(x)) { printf("Assertion failed: %s\n", #x); debugBreak(); }
#else
    #define ASSERT(x)
#endif

namespace Common
{
    struct FileStream
    {
        FILE *f;
        int size, pos;

        FileStream(const char* name) : pos(0)
        {
            f = fopen(name, "rb");
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            fseek(f, 0, SEEK_SET);
        }
        
        ~FileStream()
        {
            fclose(f);
        }

        void SetPosition(int _pos)
        {
            pos = _pos;
            fseek(f, pos, SEEK_SET);
        }

        void Seek(int offset)
        {
            fseek(f, offset, SEEK_CUR);
            pos += offset;
        }

        int Read(void *data, int size)
        {
            pos += size;
            return fread(data, 1, size, f);
        }

        template <typename T>
        T& read(T &x)
        {
            read(&x, sizeof(T));
            return x;
        }

        template <typename T>
        T* ReadArray(int count)
        {
            if (!count)
                return NULL;
            T* ret = new T[count];
            read (ret, count * sizeof(T));
            return ret;
        }
    };
}