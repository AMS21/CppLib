#ifndef INCG_CPPLIB_STREAMSCOPEGUARD_HPP
#define INCG_CPPLIB_STREAMSCOPEGUARD_HPP

#include <iostream>

namespace cpp
{
    template <typename CharT, typename Traits>
    class StreamScopeGuard
    {
    public:
        StreamScopeGuard(std::basic_ostream<CharT, Traits>& os)
            : mOS(os)
            , mFlags(mOS.flags())
            , mWidth(mOS.width())
            , mPrecision(mOS.precision())
        {
            mOS.width(0);
            mOS.precision(0);
        }

        ~StreamScopeGuard()
        {
            mOS.flags(mFlags);
            mOS.width(mWidth);
            mOS.precision(mPrecision);
        }

    private:
        std::basic_ostream<CharT, Traits>& mOS;
        const std::ios_base::fmtflags      mFlags;
        const std::streamsize              mWidth;
        const std::streamsize              mPrecision;
    };
} // namespace cpp

#endif // INCG_CPPLIB_STREAMSCOPEGUARD_HPP
