#include "String.h"
#include <assert.h>
#include <memory>
#include <iostream>
#include <cctype>

using namespace std;

//define a conversion from c-string to String
//converting constructor
String::String(const char* ctr):elements(nullptr), first_free(nullptr), cap(nullptr){
    const char* pe = ctr;
    while(*pe != '\0'){
        ++pe;
    }
    auto data = AllocAndCopy(ctr, pe);
    elements = data.first;
    cap = first_free = data.second;
}

//copy constructor
String::String(const String &s){
    auto data = AllocAndCopy(s.begin(), s.end());
    elements  = data.first;
    cap = first_free = data.second;
}

//copy assignment
String& String::operator=(const String &s){
    auto data = AllocAndCopy(s.begin(), s.end());
    Free();
    elements = data.first;
    cap = first_free = data.second;
    return *this;
}

//move constructor
String::String(String &&s)noexcept{
    auto data = m_allocator.allocate(s.Size());
    auto old_head = s.begin();
    auto new_first_free = data; 
    while(old_head != s.end()){
        m_allocator.construct(new_first_free++, std::move(*old_head++));
    }

    elements = data;
    first_free = new_first_free;
    cap = data + s.Size();
}

//move assignment
String& String::operator=(String &&s)noexcept{
    auto data = m_allocator.allocate(s.Size());
    auto old_head = s.begin();
    auto new_first_free = data; 
    while(old_head != s.end()){
        m_allocator.construct(new_first_free++, std::move(*old_head++));
    }
    Free();
    elements = data;
    first_free = new_first_free;
    cap = data + s.Size();
    return *this;
}

void String::Clear(){
    if(elements){
        auto last = first_free;
        while(last != elements){
            m_allocator.destroy(--last);
        }
        first_free = elements;
    }
}
void String::push_back(const char &c){
    //what if c is '\0'
    CheckAndAlloc();
    *first_free++ = c;
}

// //return c-string [TODO]: how?? 
// char* String::c_str()const{
//     char cstr[Size()+1];
//     for(int i = 0; i < Size(); ++i){
//         cstr[i] = *(elements + i);
//     }
//     cstr[Size()] = '\0';
//     return &cstr[0];
// }


/*
 *    overloaded operator
 */

bool operator==(const String &a, const String &b){
    if(a.Size() == b.Size()){
        for(auto a_begin = a.begin(), b_begin = b.begin(); a_begin != a.end(); ++ a_begin, ++b_begin){
            if(*a_begin != *b_begin){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}

bool operator!=(const String &a, const String &b){
    return !(a==b);
}

ostream& operator<<(ostream &os, const String &s){
    for(auto beg = s.begin(), end = s.end(); beg != end; ++beg){
        os << *beg;
    }
    return os;
}

istream& operator>>(istream &is, String &s){
    string temp;
    is>>temp;
    if(is){
        s.Clear();
        for(auto beg = temp.begin(), end = temp.end(); beg != end; ++beg){
            s.push_back(*beg);
        }
    }
    //?what of IO error happened
    //TODO[Finn]: try to read char by char but it didnt work cuz the spaces are ignore
    return is;
}

String operator+(const String &a, const String &b){
    String s = a;
    s += b;//very useful trick
    return s;
}

String& String::operator+=(const String&s){
    for(auto beg = s.begin(), end = s.end(); beg != end; ++beg){
        this->push_back(*beg);
    }
    return *this;
}

char& String::operator[](int index){
    assert(index >= 0);
    assert(index < Size());
    return *(elements + index);
}

const char& String::operator[](int index)const{
    assert(index >= 0);
    assert(index < Size());
    return *(elements + index);
}

//alphabetical order
bool operator<(const String &a, const String &b){
    auto ab = a.begin();
    auto bb = b.begin();
    auto ae = a.end();
    auto be = b.end();

    for( ;ab != ae && bb != be; ++ab, ++bb){
        if(*ab != *bb){
            return *ab < *bb;
        }
    }
    if(ab == ae && bb == be){
        return false;//a == b
    }else{
        return ab == ae;
    }
}

bool operator<=(const String &a, const String &b){
    return a == b || a < b;
}

bool operator>(const String &a, const String &b){
    return !(a <= b);
}

bool operator>=(const String &a, const String &b){
    return !(a < b);
}

/*
 *    private util function
 */

//enlarge the capacity as twice as size()
void String::Reallocate(){
    auto new_cap = (Size()==0)?1:2*Size();
    auto data = m_allocator.allocate(new_cap);
    //copy the old data to new data
    auto old_head = elements;
    auto new_first_free = data; 
    while(old_head != first_free){
        m_allocator.construct(new_first_free++, std::move(*old_head++));
    }
    Free();//free the old data

    elements = data;
    first_free = new_first_free;
    cap = data + new_cap;
}

//precondition e >= b
std::pair<char*, char*>  String::AllocAndCopy(const char *b, const char *e){
    auto data = m_allocator.allocate(e - b);
    auto end = uninitialized_copy(b, e, data);
    return {data, end};
}

//free the rss we allocate
void String::Free(){
    if(elements){
        auto last = first_free;
        while(last != elements){
            m_allocator.destroy(--last);
        }
        m_allocator.deallocate(elements, cap - elements);
    }
}
