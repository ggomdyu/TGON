/**
 * @file    DelegateTest.h
 * @author  ggomdyu
 * @since   03/17/2020
 */

#pragma once
#include <cassert>
#include <memory>

#include "Core/Delegate.h"

#include "../Test.h"

namespace tgon
{

class DelegateTest :
    public Test
{
/**@section Method */
public:
    void Evaluate() override
    {
        std::shared_ptr<int> p;
        std::shared_ptr<int> p2;
        std::shared_ptr<int> p3;
        std::shared_ptr<int> p4;
        std::shared_ptr<int> p5;
        std::shared_ptr<int> p6;

        {
            auto temp = tgon::Delegate([p, p2, p3, p4, p5, p6]() { return 1; });
            auto temp2 = tgon::Delegate([p, p2, p3, p4, p5, p6]() { return 2; });
            auto temp3 = temp;
            assert(temp() == 1);
            assert(temp2() == 2);
            assert(temp3() == 1);
            temp = temp2;
            assert(temp() == 2);
            temp2 = std::move(temp3);
            assert(temp2() == 1);
        }
        {
            auto temp = tgon::Delegate([]() { return 1; });
            auto temp2 = tgon::Delegate([]() { return 2; });
            auto temp3 = temp;
            assert(temp() == 1);
            assert(temp2() == 2);
            assert(temp3() == 1);
            temp = temp2;
            assert(temp() == 2);
            temp2 = std::move(temp3);
            assert(temp2() == 1);
        }
        {
            auto temp = tgon::Delegate([]() { return 1; });
            auto temp2 = tgon::Delegate([p, p2, p3, p4, p5, p6]() { return 2; });
            auto temp3 = temp;
            assert(temp() == 1);
            assert(temp2() == 2);
            assert(temp3() == 1);
            temp = temp2;
            assert(temp() == 2);
            temp2 = std::move(temp3);
            assert(temp2() == 1);
        }
        {
          /*  auto temp = tgon::Delegate([p, p2, p3, p4, p5, p6]() { return 1; });
            auto temp2 = tgon::Delegate([]() { return 2; });
            auto temp3 = temp;
            assert(temp() == 1);
            assert(temp2() == 2);
            assert(temp3() == 1);
            temp = temp2;
            assert(temp() == 2);
            temp2 = std::move(temp3);
            assert(temp2() == 1);*/
        }
    }
};

} /* namespace tgon */
