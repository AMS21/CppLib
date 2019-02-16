#pragma once

#include "Assert.hpp"
#include <cstddef>

// TODO: No discard?

namespace cpp
{
    /*!
    * \brief Retrieves a reference to the element at position 'index' in the
    *        C-Array 'arr'.
    * \param arr The C-Array to access.
    * \param index The index of the element in 'arr' to get a reference to.
    * \return A reference to the element at position 'index' in 'arr'.
    * \throws std::out_of_range if 'index' is out of bounds.
    **/
    template <typename Type, std::size_t Size>
    constexpr Type& at(Type(&arr)[Size], std::size_t index)
    {
        CPP_DBG_CHECK_BOUNDS(index, 0, Size - 1);

        return arr[index];
    }

    /*!
    * \brief Retrieves a reference to the element at position 'index' in the
    *        container 'container'.
    * \param container The container to access.
    * \param index The index of the element in 'container' to get a reference to.
    * \return A reference to the element at position 'index' in 'container'.
    * \throws std::out_of_range if 'index' is out of bounds.
    **/
    template <typename Container>
    constexpr auto at(Container& container, std::size_t index)
        -> decltype(container[container.size()])
    {
        CPP_DBG_CHECK_BOUNDS(index, 0, container.size() - 1);

        return container[index];
    }

    /*!
    * \brief Retrieves a copy of the element at position 'index' in the
    *        std::initializer_list 'il'.
    * \param il The initializer_list to access.
    * \param index The index of the element to get a copy of.
    * \return A copy of the element at position 'index'.
    * \throws std::out_of_range if 'index' is out of bounds.
    **/
    template <typename Type>
    constexpr Type at(std::initializer_list<Type> il, std::size_t index)
    {
        CPP_DBG_CHECK_BOUNDS(index, 0, il.size() - 1);

        return *(il.begin() + index);
    }
}
