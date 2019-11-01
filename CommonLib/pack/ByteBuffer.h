#pragma once
#include<vector>
#include<assert.h>
#include<typedef.h>
using namespace SurrealTypes;

/**///////////////////////////////////////////////////////////////////////////
/// 字节流缓冲类，可以进行序列化和解序列化操作，并且可以缓冲字节流数据。
//////////////////////////////////////////////////////////////////////////
class ByteBuffer
{
public:
    const static size_t DEFAULT_SIZE = 0x2000;

    ByteBuffer()
        : mReadPos(0)
        , mWritePos(0)
    {
        mStorage.reserve(DEFAULT_SIZE);
    }

    ByteBuffer(size_t res)
        : mReadPos(0)
        , mWritePos(0)
    {
        mStorage.reserve(res);
    }

    ByteBuffer(const ByteBuffer &buf) 
        : mReadPos(buf.mReadPos)
        , mWritePos(buf.mWritePos)
        , mStorage(buf.mStorage)
    {}

	//析构函数
	virtual ~ByteBuffer()
	{
		clear();
	}

    /**///////////////////////////////////////////////////////////////////////////
public:
    void clear()
    {
        mStorage.clear();
        mReadPos = mWritePos = 0;
    }

	//末尾插入数据
    template <typename T> void append(T value)
    {
        append((STu8*)&value, sizeof(value));
    }
    void append(const STu8 *src, size_t cnt)
    {
        if (!cnt) return;

        assert(size() < 10000000);

        if (mStorage.size() < mWritePos + cnt)
        {
            mStorage.resize(mWritePos + cnt);
        }
        memcpy(&mStorage[mWritePos], src, cnt);
        mWritePos += cnt;
    }

	/*apend特化函数*********************************************/
	template <> void append<std::string>(std::string value)
    {
        append(value);
    }
	template <> void append<ByteBuffer>(ByteBuffer value)
    {
        append(value);
    }
	/*apend特化函数*********************************************/

	//固定位置存入数据，原有数据被覆盖,用于修正数据
    template <typename T> void put(size_t pos, T value)
    {
        put(pos, (STu8*)&value, sizeof(value));
    }
	//固定位置存入数据，覆盖原有数据
	void put(size_t pos, const STu8 *src, size_t cnt)
	{
		assert(pos + cnt <= size() || PrintPosError(true, pos, cnt));
		memcpy(&mStorage[pos], src, cnt);
	}

	//任意位置插入数据
	template <typename T> void insert(size_t pos,T value)
    {
		insert(pos,(STu8*)&value,sizeof(value));
    }
	void insert(int pos,const STu8 *src, size_t cnt)
	{
		if (!cnt) return;

        assert(size() < 10000000);

		std::vector<STu8>::iterator it=mStorage.begin();
		unsigned int i = cnt;
		for(;i>0;i--)
		{
			mStorage.insert(mStorage.begin(), *((STu8*)src + i-1));
		}
        mWritePos += cnt;
	}
	//模板的特化
	template <> void insert<std::string>(size_t pos,std::string value)
    {
        insert(pos,value);
    }
	template <> void insert<ByteBuffer>(size_t pos,ByteBuffer value)
    {
        insert(pos,value);
    }
    /**///////////////////////////////////////////////////////////////////////////
private:
    //ByteBuffer& operator<<(STbool value)
    //{
    //    append<STbool>((STbool)value);
    //    return *this;
    //}
    ByteBuffer& operator<<(STs8 value)
    {
        append<STs8>(value);
        return *this;
    }
    ByteBuffer& operator<<(STs16 value)
    {
        append<STs16>(value);
        return *this;
    }
    ByteBuffer& operator<<(STs32 value)
    {
        append<STs32>(value);
        return *this;
    }
    ByteBuffer& operator<<(STs64 value)
    {
        append<STs64>(value);
        return *this;
    }
    ByteBuffer& operator<<(STu8 value)
    {
        append<STu8>(value);
        return *this;
    }
    ByteBuffer& operator<<(STu16 value)
    {
        append<STu16>(value);
        return *this;
    }
    ByteBuffer& operator<<(STu32 value)
    {
        append<STu32>(value);
        return *this;
    }
    ByteBuffer& operator<<(STu64 value)
    {
        append<STu64>(value);
        return *this;
    }
    ByteBuffer& operator<<(STfp32 value)
    {
        append<STfp32>(value);
        return *this;
    }
    ByteBuffer& operator<<(STfp64 value)
    {
        append<STfp64>(value);
        return *this;
    }
    //ByteBuffer& operator<<(time_t value)
    //{
    //    append<time_t>(value);
    //    return *this;
    //}
    ByteBuffer& operator<<(const std::string& value)
    {
        append((STu8 const *)value.c_str(), value.length());
        append((STu8)0);
        return *this;
    }
    ByteBuffer& operator<<(const char* str)
    {
        append( (STu8 const *)str, str ? strlen(str) : 0);
        append((STu8)0);
        return *this;
    }
    /**///////////////////////////////////////////////////////////////////////////

private:
    //ByteBuffer& operator>>(STbool& value)
    //{
    //    value = read<STbool>() > 0 ? 1 : 0;
    //    return *this;
    //}
    ByteBuffer& operator>>(STs8& value)
    {
        value = read<STs8>();
        return *this;
    }
    ByteBuffer& operator>>(STs16& value)
    {
        value = read<STs16>();
        return *this;
    }
    ByteBuffer& operator>>(STs32& value)
    {
        value = read<STs32>();
        return *this;
    }
    ByteBuffer& operator>>(STs64& value)
    {
        value = read<STs64>();
        return *this;
    }
    ByteBuffer& operator>>(STu8& value)
    {
        value = read<STu8>();
        return *this;
    }
    ByteBuffer& operator>>(STu16& value)
    {
        value = read<STu16>();
        return *this;
    }
    ByteBuffer& operator>>(STu32& value)
    {
        value = read<STu32>();
        return *this;
    }
    ByteBuffer& operator>>(STu64& value)
    {
        value = read<STu64>();
        return *this;
    }
    ByteBuffer& operator>>(STfp32 &value)
    {
        value = read<STfp32>();
        return *this;
    }
    ByteBuffer& operator>>(STfp64 &value)
    {
        value = read<STfp64>();
        return *this;
    }
    //ByteBuffer& operator>>(time_t& value)
    //{
    //    value = read<time_t>();
    //    return *this;
    //}
    ByteBuffer& operator>>(std::string& value)
    {
        value.clear();
        while (rpos() < size())
        {
            char c = read<char>();
            if (c == 0)
            {
                break;
            }
            value += c;
        }
        return *this;
    }
    ByteBuffer& operator>>(const STs8 value[])
    {
        std::string strValue;
        strValue.clear();
        while (rpos() < size())
        {
			STs8 c = read<STs8>();
            if (c == 0)
            {
                break;
            }
            strValue += c;
        }
        strncpy_s((char*)value, strlen((char*)value),strValue.c_str(), strValue.size());
        return *this;
    }
    /**///////////////////////////////////////////////////////////////////////////
public:
    STu8 operator[](size_t pos)
    {
        return read<STu8>(pos);
    }
    size_t rpos() const
    {
        return mReadPos;
    };
    size_t rpos(size_t rpos_)
    {
        mReadPos = rpos_;
        return mReadPos;
    };
	size_t mpos(size_t mpos_)
    {
		if((mReadPos + mpos_)>size())
		{
			mReadPos=size();
			return mReadPos;
		}
        mReadPos += mpos_;
        return mReadPos;
    };
    size_t wpos() const
    {
        return mWritePos;
    }
    size_t wpos(size_t wpos_)
    {
        mWritePos = wpos_;
        return mWritePos;
    }
	bool btail()
	{
		return mReadPos==mWritePos;
	}

    template <typename T> T read()
    {
        T r = read<T>(mReadPos);
        mReadPos += sizeof(T);
        return r;
    };
    template <typename T> T read(size_t pos) const
    {
        assert(pos + sizeof(T) <= size() || PrintPosError(false,pos,sizeof(T)));
        return *((T const*)&mStorage[pos]);
    }
    void read(STu8 *dest, size_t len)
    {
        assert(mReadPos  + len  <= size() || PrintPosError(false, mReadPos,len));
        memcpy(dest, &mStorage[mReadPos], len);
        mReadPos += len;
    }
    const STu8* contents() const { if(mReadPos==mWritePos) return NULL; return &mStorage[mReadPos]; }
    size_t size() const { return mStorage.size(); }
    bool empty() const { return mStorage.empty(); }
    void resize(size_t _NewSize)
    {
        mStorage.resize(_NewSize);
        mReadPos = 0;
        mWritePos = size();
    };
    void reserve(size_t _Size)
    {
        if (_Size > size()) mStorage.reserve(_Size);
    };

	//分别对short，int，long long类型数据进行翻转
	template <typename T> T reverse(const T value)
	{
		T ret=0;
		switch(sizeof(T))
		{
		case 2:
			{
				T a=value&0x00FF;
				T b=(value>>8)&0xFF;
				ret=(a<<8)|b;
			}break;
		case 4:
			{
				T a=value&0xFF;
				T b=(value>>0x8)&0xFF;
				T c=(value>>0x10)&0xFF;
				T d=(value>>0x18)&0xFF;
				ret=(a<<0x18)|(b<<0x10)|(c<<0x8)|d;
			}break;
		case 8:
			{
				T a=value&0xFF;
				T b=(value>>0x8)&0xFF;
				T c=(value>>0x10)&0xFF;
				T d=(value>>0x18)&0xFF;
				T e=(value>>0x20)&0xFF;
				T f=(value>>0x28)&0xFF;
				T h=(value>>0x30)&0xFF;
				T i=(value>>0x38)&0xFF;
				ret=(a<<0x38)|(b<<0x30)|(c<<0x28)|(d<<0x20)|(e<<0x18)|(f<<0x10)|(h<<0x8)|i;
			}break;
		case 1:
		default:
			{
				ret=value;
			}
		}
		return ret;
	}

	//末尾添加数据
private:
    void append(const std::string& str)
    {
        append((STu8 const*)str.c_str(), str.size() + 1);
    }
    void append(const ByteBuffer& buffer)
    {
        if (buffer.size()) append(buffer.contents(),buffer.size());
    }
	
	//任意位置插入数据
private:
	void insert(const std::string &str)
	{
	}
	void insert(const ByteBuffer &buffer)
	{
	}
    /**///////////////////////////////////////////////////////////////////////////
public:
    void print_storage()
    {
    }

    void textlike()
    {
    }

    void hexlike()
    {
    }

    bool PrintPosError(bool add, size_t pos, size_t esize) const
    {
        printf("ERROR: Attempt %s in ByteBuffer (pos: %u size: %u) value with size: %u",(add ? "put" : "get"), pos, size(), esize);
        return false;
    }

protected:
    size_t                mReadPos;
    size_t                mWritePos;
    std::vector<STu8>    mStorage;
};


/**///////////////////////////////////////////////////////////////////////////
// std::vector
/**///////////////////////////////////////////////////////////////////////////
#ifdef _VECTOR_
template <typename T>
ByteBuffer& operator<<(ByteBuffer& b, const std::vector<T>& v)
{
    b << (uint32)v.size();

    typename std::vector<T>::const_iterator iter    = v.begin();
    typename std::vector<T>::const_iterator& iEnd    = v.end();
    for (; iter != iEnd; ++iter)
    {
        b << *iter;
    }
    return b;
}

template <typename T>
ByteBuffer& operator>>(ByteBuffer& b, std::vector<T>& v)
{
    uint32 vsize;
    b >> vsize;
    v.clear();
    while (vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}
#endif

/**///////////////////////////////////////////////////////////////////////////
// std::list
/**///////////////////////////////////////////////////////////////////////////
#ifdef _LIST_
template <typename T>
ByteBuffer& operator<<(ByteBuffer& b, const std::list<T>& v)
{
    b << (uint32)v.size();

    typename std::list<T>::const_iterator iter    = v.begin();
    typename std::list<T>::const_iterator& iEnd    = v.end();
    for (; iter != iEnd; ++iter)
    {
        b << *iter;
    }
    return b;
}

template <typename T>
ByteBuffer& operator>>(ByteBuffer& b, std::list<T>& v)
{
    uint32 vsize;
    b >> vsize;
    v.clear();
    while (vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}
#endif

/**///////////////////////////////////////////////////////////////////////////
// std::map
/**///////////////////////////////////////////////////////////////////////////
#ifdef _MAP_
template <typename K, typename V>
ByteBuffer& operator<<(ByteBuffer& b, const std::map<K, V>& m)
{
    b << (uint32)m.size();

    typename std::map<K, V>::const_iterator iter = m.begin();
    typename std::map<K, V>::const_iterator iEnd = m.end();
    for (; iter != iEnd; ++iter)
    {
        b << iter->first << iter->second;
    }
    return b;
}

template <typename K, typename V>
ByteBuffer &operator>>(ByteBuffer& b, std::map<K, V>& m)
{
    uint32 msize;
    b >> msize;
    m.clear();
    while (msize--)
    {
        K k;
        V v;
        b >> k >> v;
        m.insert(std::make_pair(k, v));
    }
    return b;
}
#endif

