/**
 * @file    DateTimeTest.h
 * @author  ggomdyu
 * @since   08/02/2019
 */

#pragma once
#include <cassert>

#include "String/FixedString.h"
#include "Diagnostics/Debug.h"

#include "../Test.h"

namespace tgon
{

class FixedStringTest :
    public Test
{
/**@section Method */
public:
    virtual void Evaluate() override
    {
        //abcdefabc
        //
    
        FixedString256 a = "abc";
        assert(a.Capacity() == 256);
        assert(a.Length() == 3);

        a += "defabc";
        assert(a.Length() == 9);
        assert(a[3] == 'd');
        assert(a.IndexOf('a') == 0);
        assert(a.IndexOf('a', 1) == 6);
        assert(a.IndexOf('c') == 2);
        assert(a.IndexOf('a', 0) == 0);
        assert(a.IndexOf('c', 3) == 8);
        assert(a.IndexOfAny([](char ch) { return ch == 'a' || ch == 'b'; }) == 0);
        assert(a.IndexOfAny([](char ch) { return ch == 'a' || ch == 'b'; }, 2) == 6);
        assert(a.LastIndexOf('c') == 8);
        assert(a.LastIndexOf('c', 0) == -1);
        assert(a.LastIndexOf('c', 3) == 2);
        assert(a.LastIndexOf('c', 8) == 8);
        assert(a.LastIndexOfAny([](char ch) { return ch == 'a' || ch == 'b'; }) == 7);
        assert(a.LastIndexOfAny([](char ch) { return ch == 'd' || ch == 'c'; }, 4) == 3);
        assert(a.LastIndexOfAny([](char ch) { return ch == 'a'; }) == 6);
        assert(a.LastIndexOfAny([](char ch) { return ch == 'a'; }, 0) == -1);
        assert(a.LastIndexOfAny([](char ch) { return ch == 'a'; }, 1) == 0);
        assert(a.LastIndexOfAny([](char ch) { return ch == 'f'; }) == 5);

        assert(a == std::string_view("abcdefabc"));
        assert(a != std::string_view("abcdefab"));
        assert(a != std::string_view("abcdefabcg"));
        assert(a == FixedString256("abcdefabc"));
        assert(a != FixedString256("abcdefab"));
        assert(a != FixedString256("abcdefabcg"));

//        FixedString16 b = "abcdefab";
//        assert(a.CompareTo(b) == 1);
//        b += "c";
//        assert(a.CompareTo(b) == 0);
//        b += "h";
//        assert(a.CompareTo(b) == -1);
        
    }

private:

};

} /* namespace tgon */
