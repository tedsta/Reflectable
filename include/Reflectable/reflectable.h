#ifndef REFLECTABLE_REFLECTABLE_H_INCLUDED
#define REFLECTABLE_REFLECTABLE_H_INCLUDED

#include "Reflectable/tagged_tuple.h"
#include "Reflectable/for_each.h"

template <typename ...Args>
class Reflectable : public tagged_tuple<Args...>
{
    public:
        template <typename FuncT>
        void iterate(const FuncT& f)
        {
            for_each(*this, f);
        }
};

#endif // REFLECTABLE_REFLECTABLE_H_INCLUDED
