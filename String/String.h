#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <memory>

class String {
public:
    String():elements(nullptr), first_free(nullptr), cap(nullptr){}
    String(const char*);
    String(const String&);
    String(String &&)noexcept;
    String& operator=(const String &s);
    String& operator=(String &&s)noexcept;
    ~String(){
        Free();
    };

    // typedef String::size_type size_t;

    /*capacity*/
    //resize
    //reserve
    size_t Size()const{return first_free - elements;};
    size_t Capacity()const{return cap - elements;};
    bool Empty()const{return Size()==0;}
    void Clear();
    // void Clear(){first_free = elements;};//error allocator.destory must be call before deallocate
    /*iterator*/
    char* begin(){return elements;};
    char* end(){return first_free;};
    const char* begin()const{return elements;};
    const char* end()const{return first_free;};
    /*Modifiers*/
    void push_back(const char &c);
    //erase
    // String& erase (size_t pos = 0, size_t len = 0);
    // replace
    // swap
    // pop back
    //to c string
    // const char* c_str()const noexcept;
    //operator definition
    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);
    friend bool operator<=(const String&, const String&);
    friend bool operator>=(const String&, const String&);
    friend bool operator<(const String&, const String&);
    friend bool operator>(const String&, const String&);
    friend std::ostream& operator<<(std::ostream &os, const String &);
    friend std::istream& operator>>(std::istream &is, String &);
    friend String operator+(const String &a, const String &b);
    String& operator+=(const String&a);
    char& operator[](int index);
    const char& operator[](int index)const;
private:
    //util function
    void Free();
    void Reallocate();
    void CheckAndAlloc(){if(Size() == Capacity())Reallocate();};
    std::pair<char*, char*> AllocAndCopy(const char*, const char*);

    char* cap;
    char* first_free;
    char* elements;
    std::allocator<char> m_allocator;
};

#endif
