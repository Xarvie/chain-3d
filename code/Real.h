#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "OCDFAInspection"
#pragma ide diagnostic ignored "google-explicit-constructor"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
//
// Created by caspase on 9/15/2020.
//

//
// MSVC has no built-in int128, wait for the new version of VS to replace it https://github.com/zhanhb/int128
// some mathfunction
#ifndef UNTITLED_REAL_H
#define UNTITLED_REAL_H

#ifdef __GNUC__
#pragma GCC push_options
#pragma GCC optimize("O3")
#elif __clang__
#pragma CLANG push_options
#pragma CLANG optimize("O3") #TODO
#elif _MSC_VER
#pragma optimize( "gt", on )
#endif


#ifdef __GNUC__
#define _REAL_CONSTEXPR constexpr
#elif __clang__
#define _REAL_CONSTEXPR constexpr
#elif _MSC_VER
#define _REAL_CONSTEXPR
#endif

#if _MSC_VER
#pragma warning( push , 1)
#pragma warning( disable: 4146)
#endif

//#ifdef __GNUC__
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Winherited-variadic-ctor"
//#endif

#include <cstdint>
#include <cassert>
#include <cmath>
#include <cstdio>

#ifdef _MSC_VER
#include <cinttypes>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <locale>
#include <string>
#include <type_traits>

#define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__

#ifndef __BYTE_ORDER__
#error __BYTE_ORDER__ not defined
#endif

namespace large_int {
    template<class, class>
    class int128_base;

    typedef int128_base<int64_t, uint64_t> int128_t;
    typedef int128_base<uint64_t, uint64_t> uint128_t;

    template<class _Tp>
    struct half_mask : std::integral_constant<_Tp, (_Tp(1) << (4 * sizeof(_Tp))) - _Tp(1)> {
    };

    template<bool = true>
    struct detail_delegate;

    _REAL_CONSTEXPR bool operator<(int128_t, int128_t);

    _REAL_CONSTEXPR bool operator<(uint128_t, uint128_t);

    _REAL_CONSTEXPR uint128_t operator>>(uint128_t, int);

    _REAL_CONSTEXPR int128_t operator>>(int128_t, int);

    _REAL_CONSTEXPR int128_t operator*(int128_t, int128_t);

    _REAL_CONSTEXPR uint128_t operator*(uint128_t, uint128_t);

    _REAL_CONSTEXPR uint128_t operator<<(uint128_t, int);

    _REAL_CONSTEXPR int128_t operator<<(int128_t, int);

    inline uint128_t operator/(uint128_t, uint128_t);

    inline int128_t operator/(int128_t, int128_t);

    inline uint128_t operator%(uint128_t, uint128_t);

    inline int128_t operator%(int128_t, int128_t);

    template<class _Hi, class _Low>
    class alignas(sizeof(_Hi) * 2) int128_base final {
        static_assert(sizeof(_Hi) == sizeof(_Low), "low type, high type should have same size");

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        _Low low_{};
        _Hi high_{};

        _REAL_CONSTEXPR int128_base(_Hi high, _Low low) : low_(low), high_(high) {}

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        _Hi high_{};
        _Low low_{};

        _REAL_CONSTEXPR int128_base(_Hi high, _Low low) : high_(high), low_(low) {}

#else
#error endian not support
#endif

        struct integral_tag {
        };
        struct signed_integral_tag : integral_tag {
        };
        struct unsigned_integral_tag : integral_tag {
        };
        struct float_tag {
        };
        template<size_t>
        struct size_constant {
        };

    private:
        template<class _Tp>
        _REAL_CONSTEXPR int128_base(_Tp value_, signed_integral_tag, size_constant<8>) :
            int128_base(-(value_ < 0), value_) {}

        template<class _Tp>
        _REAL_CONSTEXPR int128_base(_Tp value_, unsigned_integral_tag, size_constant<8>) : int128_base(0, _Low(value_)) {}

        template<class _Tp>
        _REAL_CONSTEXPR int128_base(_Tp value_, integral_tag, size_constant<16>) : // NOLINT explicit
            int128_base(_Hi(value_ >> 64U), _Low(value_)) {} // NOLINT signed shift

    public:

        _REAL_CONSTEXPR int128_base() noexcept = default;

        _REAL_CONSTEXPR int128_base(const int128_base&) noexcept = default;

        _REAL_CONSTEXPR int128_base(int128_base&&) noexcept = default;

        int128_base& operator=(const int128_base&) noexcept = default;

        int128_base& operator=(int128_base&&) noexcept = default;

        template<class _Tp>
        _REAL_CONSTEXPR explicit int128_base(int128_base<_Tp, _Low> val_) : int128_base(val_.high_, val_.low_) {}

        template<class _Tp>
        _REAL_CONSTEXPR int128_base(_Tp val_, float_tag) :
            int128_base(_Hi(std::ldexp(val_, -64)) - (val_ < 0), _Low(val_)) {}

        _REAL_CONSTEXPR explicit int128_base(float val_) : int128_base(val_, float_tag()) {}

        _REAL_CONSTEXPR explicit int128_base(double val_) : int128_base(val_, float_tag()) {}

        _REAL_CONSTEXPR explicit int128_base(long double val_) : int128_base(val_, float_tag()) {}

        _REAL_CONSTEXPR int128_base(long long val_) : // NOLINT explicit
            int128_base(val_, signed_integral_tag(), size_constant<sizeof(val_)>()) {}

        _REAL_CONSTEXPR int128_base(long val_) : int128_base(static_cast<long long>(val_)) {} // NOLINT explicit

        _REAL_CONSTEXPR int128_base(int val_) : int128_base(long(val_)) {} // NOLINT explicit

        _REAL_CONSTEXPR int128_base(unsigned long long val_) : // NOLINT explicit
            int128_base(val_, unsigned_integral_tag(), size_constant<sizeof(val_)>()) {}

        _REAL_CONSTEXPR int128_base(unsigned long val_) : // NOLINT explicit
            int128_base(static_cast<unsigned long long>(val_)) {}

        _REAL_CONSTEXPR int128_base(unsigned val_) : int128_base(static_cast<unsigned long>(val_)) {} // NOLINT explicit

        _REAL_CONSTEXPR explicit operator bool() const { return high_ || low_; }

        _REAL_CONSTEXPR explicit operator char() const { return char(low_); }

        _REAL_CONSTEXPR explicit operator signed char() const { return static_cast<signed char>(low_); }

        _REAL_CONSTEXPR explicit operator unsigned char() const { return static_cast<unsigned char>(low_); }

        _REAL_CONSTEXPR explicit operator short() const { return short(low_); }

        _REAL_CONSTEXPR explicit operator unsigned short() const { return static_cast<unsigned short>(low_); }

        _REAL_CONSTEXPR explicit operator int() const { return int(low_); }

        _REAL_CONSTEXPR explicit operator unsigned() const { return unsigned(low_); }

        _REAL_CONSTEXPR explicit operator long() const { return long(low_); }

        _REAL_CONSTEXPR explicit operator unsigned long() const { return static_cast<unsigned long>(low_); }

        _REAL_CONSTEXPR explicit operator long long() const { return static_cast<long long>(low_); }

        _REAL_CONSTEXPR explicit operator unsigned long long() const { return static_cast<unsigned long long>(low_); }

        _REAL_CONSTEXPR explicit operator wchar_t() const { return wchar_t(low_); }

        _REAL_CONSTEXPR explicit operator char16_t() const { return char16_t(low_); }

        _REAL_CONSTEXPR explicit operator char32_t() const { return char32_t(low_); }

#if __SIZEOF_INT128__ == 16

        _REAL_CONSTEXPR explicit int128_base(__int128 val_) :
            int128_base(val_, signed_integral_tag(), size_constant<sizeof(val_)>()) {}

        _REAL_CONSTEXPR explicit int128_base(unsigned __int128 val_) :
            int128_base(val_, unsigned_integral_tag(), size_constant<sizeof(val_)>()) {}

        _REAL_CONSTEXPR explicit operator unsigned __int128() const {
            return static_cast<unsigned __int128>(high_) << 64U | static_cast<unsigned __int128>(low_);
        }

        _REAL_CONSTEXPR explicit operator __int128() const {
            return static_cast<__int128>(static_cast<unsigned __int128>(*this));
        }

#endif

    private:
        template<class _Tp>
        _REAL_CONSTEXPR _Tp cast_to_float() const;

    public:
        _REAL_CONSTEXPR explicit operator float() const { return cast_to_float<float>(); }

        _REAL_CONSTEXPR explicit operator double() const { return cast_to_float<double>(); }

        _REAL_CONSTEXPR explicit operator long double() const { return cast_to_float<long double>(); }

        _REAL_CONSTEXPR int128_base operator+() const { return *this; }

        _REAL_CONSTEXPR int128_base operator-() const { long long si = low_; return int128_base(-high_ - (low_ != 0), -low_); }

        _REAL_CONSTEXPR int128_base operator~() const { return int128_base(~high_, ~low_); }

        _REAL_CONSTEXPR bool operator!() const { return !high_ && !low_; }

        // avoid self plus on rvalue
        int128_base& operator++()& { return *this = *this + int128_base(1); }

        int128_base& operator--()& { return *this = *this - int128_base(1); }

        int128_base operator++(int)& { // NOLINT returns non constant
            int128_base tmp = *this;
            ++* this;
            return tmp;
        }

        int128_base operator--(int)& { // NOLINT returns non constant
            int128_base tmp = *this;
            --* this;
            return tmp;
        }

        friend _REAL_CONSTEXPR int128_base operator+(int128_base lhs_, int128_base rhs_) {
            // no worry for unsigned type, won't be optimized if overflow
            return { _Hi(lhs_.high_ + rhs_.high_ + (lhs_.low_ + rhs_.low_ < lhs_.low_)), lhs_.low_ + rhs_.low_ };
        }

        friend _REAL_CONSTEXPR int128_base operator-(int128_base lhs_, int128_base rhs_) {
            return { _Hi(lhs_.high_ - rhs_.high_ - (lhs_.low_ < rhs_.low_)), lhs_.low_ - rhs_.low_ };
        }

        friend _REAL_CONSTEXPR int128_base operator&(int128_base lhs_, int128_base rhs_) {
            return { lhs_.high_ & rhs_.high_, lhs_.low_ & rhs_.low_ };
        }

        friend _REAL_CONSTEXPR int128_base operator|(int128_base lhs_, int128_base rhs_) {
            return { lhs_.high_ | rhs_.high_, lhs_.low_ | rhs_.low_ };
        }

        friend _REAL_CONSTEXPR int128_base operator^(int128_base lhs_, int128_base rhs_) {
            return { lhs_.high_ ^ rhs_.high_, lhs_.low_ ^ rhs_.low_ };
        }

        friend _REAL_CONSTEXPR bool operator==(int128_base lhs_, int128_base rhs_) {
            return lhs_.high_ == rhs_.high_ && lhs_.low_ == rhs_.low_;
        }

        friend _REAL_CONSTEXPR bool operator>(int128_base lhs_, int128_base rhs_) { return rhs_ < lhs_; }

        friend _REAL_CONSTEXPR bool operator>=(int128_base lhs_, int128_base rhs_) { return !(lhs_ < rhs_); }

        friend _REAL_CONSTEXPR bool operator<=(int128_base lhs_, int128_base rhs_) { return !(rhs_ < lhs_); }

        friend _REAL_CONSTEXPR bool operator!=(int128_base lhs_, int128_base rhs_) { return !(lhs_ == rhs_); }

        friend _REAL_CONSTEXPR int128_base operator<<(int128_base lhs_, int128_base rhs_) { return lhs_ << (int)rhs_.low_; }

        friend _REAL_CONSTEXPR int128_base operator>>(int128_base lhs_, int128_base rhs_) { return lhs_ >> (int)rhs_.low_; }

        int128_base& operator+=(int128_base rhs_)& { return *this = *this + rhs_; }

        int128_base& operator-=(int128_base rhs_)& { return *this = *this - rhs_; }

        int128_base& operator*=(int128_base rhs_)& { return *this = *this * rhs_; }

        int128_base& operator/=(int128_base rhs_)& { return *this = *this / rhs_; }

        int128_base& operator%=(int128_base rhs_)& { return *this = *this % rhs_; }

        int128_base& operator<<=(int128_base rhs_)& { return *this = *this << rhs_; }

        int128_base& operator>>=(int128_base rhs_)& { return *this = *this >> rhs_; }

        int128_base& operator<<=(int rhs_)& { return *this = *this << rhs_; }

        int128_base& operator>>=(int rhs_)& { return *this = *this >> rhs_; }

        int128_base& operator&=(int128_base rhs_)& { return *this = *this & rhs_; }

        int128_base& operator|=(int128_base rhs_)& { return *this = *this | rhs_; }

        int128_base& operator^=(int128_base rhs_)& { return *this = *this ^ rhs_; }

        template<class, class>
        friend
            class int128_base;

        template<class>
        friend
            struct clz_helper;

        template<bool>
        friend
            struct detail_delegate;
    };

    inline namespace literals {
        namespace impl_ {
            template<char _Ch, int _Rad>
            struct static_digit : std::integral_constant<int,
                '0' <= _Ch && _Ch <= '9' ? _Ch - '0' :
                'a' <= _Ch && _Ch <= 'z' ? _Ch - 'a' + 10 :
                'A' <= _Ch && _Ch <= 'Z' ? _Ch - 'A' + 10 : _Rad> {
                static_assert(_Rad > static_digit::value, "character not a digit");
            };

            template<class, int, char ...>
            struct int128_literal_radix;

            template<class _Tp, int _Rad, char _Ch>
            struct int128_literal_radix<_Tp, _Rad, _Ch> {
                _REAL_CONSTEXPR operator _Tp() const { return _Tp(static_digit<_Ch, _Rad>::value); } // NOLINT explicit

                _REAL_CONSTEXPR _Tp operator()(_Tp v) const { return v * _Tp(_Rad) + *this; }
            };

            template<class _Tp, int _Rad, char _Ch, char ..._Args>
            struct int128_literal_radix<_Tp, _Rad, _Ch, _Args...> {
                int128_literal_radix<_Tp, _Rad, _Ch> _Cur;
                int128_literal_radix<_Tp, _Rad, _Args...> _Tgt;

                _REAL_CONSTEXPR operator _Tp() const { return _Tgt(_Cur); }; // NOLINT explicit

                _REAL_CONSTEXPR _Tp operator()(_Tp v) const { return _Tgt(_Cur(v)); };
            };

            template<class _Tp, char ..._Args>
            struct int128_literal : int128_literal_radix<_Tp, 10, _Args...> {
            };
            template<class _Tp>
            struct int128_literal<_Tp, '0'> : int128_literal_radix<_Tp, 10, '0'> {
            };
            template<class _Tp, char ..._Args>
            struct int128_literal<_Tp, '0', _Args...> : int128_literal_radix<_Tp, 8, _Args...> {
            };
            template<class _Tp, char ..._Args>
            struct int128_literal<_Tp, '0', 'x', _Args...> : int128_literal_radix<_Tp, 16, _Args...> {
            };
            template<class _Tp, char ..._Args>
            struct int128_literal<_Tp, '0', 'X', _Args...> : int128_literal_radix<_Tp, 16, _Args...> {
            };
            template<class _Tp, char ..._Args>
            struct int128_literal<_Tp, '0', 'b', _Args...> : int128_literal_radix<_Tp, 2, _Args...> {
            };
            template<class _Tp, char ..._Args>
            struct int128_literal<_Tp, '0', 'B', _Args...> : int128_literal_radix<_Tp, 2, _Args...> {
            };
        }

        template<char ..._Args>
        _REAL_CONSTEXPR uint128_t operator "" _u128() { return impl_::int128_literal<uint128_t, _Args...>(); }

        template<char ..._Args>
        _REAL_CONSTEXPR int128_t operator "" _l128() { return impl_::int128_literal<int128_t, _Args...>(); }

        template<char ..._Args>
        _REAL_CONSTEXPR uint128_t operator "" _U128() { return impl_::int128_literal<uint128_t, _Args...>(); }

        template<char ..._Args>
        _REAL_CONSTEXPR int128_t operator "" _L128() { return impl_::int128_literal<int128_t, _Args...>(); }
    }


    static _REAL_CONSTEXPR unsigned clz_generic32(uint32_t x) noexcept
    {
        unsigned n = 32;
        for (int i = 4; i >= 0; --i)
        {
            const auto s = unsigned{ 1 } << i;
            const auto hi = x >> s;
            if (hi != 0)
            {
                n -= s;
                x = hi;
            }
        }
        return n - x;
    }

    static _REAL_CONSTEXPR unsigned clz_generic(uint64_t x) noexcept
    {
        unsigned n = 64;
        for (int i = 5; i >= 0; --i)
        {
            const auto s = unsigned{ 1 } << i;
            const auto hi = x >> s;
            if (hi != 0)
            {
                n -= s;
                x = hi;
            }
        }
        return n - static_cast<unsigned>(x);
    }


    template<class>
    struct clz_helper;

    template<>
    struct clz_helper<unsigned long> {
        static _REAL_CONSTEXPR int clz(unsigned long val_)
        {

#ifdef _MSC_VER
            return clz_generic32(val_);
#else
            return __builtin_clzl(val_);
#endif

        }
    };

    template<>
    struct clz_helper<unsigned long long> {
        static _REAL_CONSTEXPR int clz(unsigned long long val_)
        {
#ifdef _MSC_VER
            return clz_generic(val_);
#else
            return __builtin_clzll(val_);
#endif

        }
    };

    template<class _High, class _Low>
    struct clz_helper<int128_base<_High, _Low> > {
        static _REAL_CONSTEXPR int clz(int128_base<_High, _Low> val_) {
            return val_.high_ ? clz_helper<_Low>::clz(val_.high_) : 4 * sizeof(val_) + clz_helper<_Low>::clz(val_.low_);
        }
    };

    template<bool>
    struct detail_delegate {
        template<class _Hi, class _Low>
        static _REAL_CONSTEXPR bool cmp(int128_base<_Hi, _Low> lhs_, int128_base<_Hi, _Low> rhs_) {
            return lhs_.high_ < rhs_.high_ || (lhs_.high_ == rhs_.high_ && lhs_.low_ < rhs_.low_);
        }

        static _REAL_CONSTEXPR uint128_t shr(uint128_t lhs_, unsigned rhs_) {
            return rhs_ & 64U ? uint128_t(0, lhs_.high_ >> (rhs_ & 63U)) :
                rhs_ & 63U ? uint128_t(lhs_.high_ >> (rhs_ & 63U),
                    (lhs_.high_ << (64 - (rhs_ & 63U)) | (lhs_.low_ >> (rhs_ & 63U)))) : lhs_;
        }

        static _REAL_CONSTEXPR int128_t sar(int128_t lhs_, unsigned rhs_) {
            return rhs_ & 64U ? int128_t(-(lhs_.high_ < 0), uint64_t(lhs_.high_ >> (rhs_ & 63U))) : // NOLINT
                rhs_ & 63U ? int128_t(
                    lhs_.high_ >> (rhs_ & 63U), // NOLINT signed shift
                    (uint64_t(lhs_.high_) << (64 - (rhs_ & 63U)) | (lhs_.low_ >> (rhs_ & 63U)))) : lhs_;
        }

        template<class _Hi, class _Low>
        static _REAL_CONSTEXPR int128_base<_Hi, _Low> imul(int128_base<_Hi, _Low> lhs_, int128_base<_Hi, _Low> rhs_) {
            return int128_base<_Hi, _Low>(
                _Hi(lhs_.low_ * rhs_.high_ + rhs_.low_ * lhs_.high_) + (lhs_.low_ >> 32U) * (rhs_.low_ >> 32U),
                (lhs_.low_ & half_mask<_Low>::value) * (rhs_.low_ & half_mask<_Low>::value))
                + (int128_base<_Hi, _Low>((lhs_.low_ >> 32U) * (rhs_.low_ & half_mask<_Low>::value)) << 32U)
                + (int128_base<_Hi, _Low>((rhs_.low_ >> 32U) * (lhs_.low_ & half_mask<_Low>::value)) << 32U);
        }

        template<class _Hi, class _Low>
        static _REAL_CONSTEXPR int128_base<_Hi, _Low> shl(int128_base<_Hi, _Low> lhs_, unsigned rhs_) {
            // [64,127], 64 {low_ << 0, 0}
            return rhs_ & 64U ? int128_base<_Hi, _Low>(_Hi(lhs_.low_ << (rhs_ & 63U)), _Low(0)) :
                rhs_ & 63U ? int128_base<_Hi, _Low>(
                    _Hi((_Low(lhs_.high_) << (rhs_ & 63U)) | (lhs_.low_ >> (64U - (rhs_ & 63U)))),
                    lhs_.low_ << (rhs_ & 63U)) : lhs_;
        }

        static uint128_t& slow_div_(uint128_t& dividend_, uint128_t divisor_, uint128_t& quot_) {
            // assert(divisor != uint128_t(0));
            quot_ = uint128_t(0);
            if (cmp(dividend_, divisor_)) return dividend_;
            if (dividend_.high_ == 0) { // (0,x) / ???
                quot_.low_ = dividend_.low_ / divisor_.low_;
                dividend_.low_ %= divisor_.low_;
                return dividend_;
            }
            auto zend_ = clz_helper<uint128_t>::clz(dividend_), zsor_ = clz_helper<uint128_t>::clz(divisor_);
            if (zend_ > zsor_) return dividend_;
            for (zsor_ -= zend_, divisor_ <<= zsor_;; divisor_ >>= 1, quot_ <<= 1) {
                if (dividend_ >= divisor_) {
                    dividend_ -= divisor_;
                    quot_ |= uint128_t(1);
                }
                if (!zsor_--) return dividend_;
            }
        }

        static uint128_t div(uint128_t dividend_, uint128_t divisor_) {
            if (!divisor_) return { !!dividend_ / !!divisor_ }; // raise signal SIGFPE
            uint128_t quot_(0);
            slow_div_(dividend_, divisor_, quot_);
            return quot_;
        }

        static int128_t div(int128_t dividend_, int128_t divisor_) {
            bool nneg_ = dividend_.high_ < 0, dneg_ = divisor_.high_ < 0;
            auto res_ = div(uint128_t(nneg_ ? -dividend_ : dividend_), uint128_t(dneg_ ? -divisor_ : divisor_));
            return int128_t(nneg_ ^ dneg_ ? -res_ : res_);
        }

        static uint128_t mod(uint128_t dividend_, uint128_t divisor_) {
            if (!divisor_) return { !!dividend_ % !!divisor_ }; // raise signal SIGFPE
            uint128_t quot_(0);
            return slow_div_(dividend_, divisor_, quot_);
        }

        static int128_t mod(int128_t dividend_, int128_t divisor_) {
            bool neg_ = dividend_.high_ < 0;
            auto res_ = mod(uint128_t(neg_ ? -dividend_ : dividend_),
                uint128_t(divisor_.high_ < 0 ? -divisor_ : divisor_));
            return int128_t(neg_ ? -res_ : res_);
        }

        static void part_div(uint128_t value_, uint64_t div_, uint64_t& high_, uint64_t& mid_, uint64_t& low_) {
            uint128_t hh_(0), md_(0);
            low_ = static_cast<uint64_t>(slow_div_(value_, div_, md_));
            mid_ = static_cast<uint64_t>(slow_div_(md_, div_, hh_));
            high_ = static_cast<uint64_t>(hh_);
        }

        template<class _Tp>
        _REAL_CONSTEXPR static _Tp cast_to_float(uint128_t val_) { return std::ldexp(_Tp(val_.high_), 64) + _Tp(val_.low_); }

        template<class _Tp>
        _REAL_CONSTEXPR static _Tp cast_to_float(int128_t val_) {
            return val_.high_ < 0 ? -cast_to_float<_Tp>(uint128_t(-val_)) : cast_to_float<_Tp>(uint128_t(val_));
        }
    };

#if __SIZEOF_INT128__ == 16

    template<>
    struct detail_delegate<true> {
        typedef __int128 ti_int_;
        typedef unsigned __int128 tu_int_;

        static _REAL_CONSTEXPR ti_int_ to_native(int128_t val_) { return static_cast<ti_int_>(val_); }

        static _REAL_CONSTEXPR tu_int_ to_native(uint128_t val_) { return static_cast<tu_int_>(val_); }

        static _REAL_CONSTEXPR int128_t from_native(ti_int_ val_) { return int128_t(val_); }

        static _REAL_CONSTEXPR uint128_t from_native(tu_int_ val_) { return uint128_t(val_); }

        template<class _Hi, class _Low>
        static _REAL_CONSTEXPR bool cmp(int128_base<_Hi, _Low> lhs_, int128_base<_Hi, _Low> rhs_) {
            return to_native(lhs_) < to_native(rhs_);
        }

        static _REAL_CONSTEXPR uint128_t shr(uint128_t lhs_, unsigned rhs_) {
            return from_native(to_native(lhs_) >> static_cast<decltype(to_native(lhs_))>(rhs_));
        }

        static _REAL_CONSTEXPR int128_t sar(int128_t lhs_, unsigned rhs_) {
            return from_native(to_native(lhs_) >> static_cast<decltype(to_native(lhs_))>(rhs_)); // NOLINT signed shift
        }

        template<class _Hi, class _Low>
        static _REAL_CONSTEXPR int128_base<_Hi, _Low> imul(int128_base<_Hi, _Low> lhs_, int128_base<_Hi, _Low> rhs_) {
            return from_native(to_native(lhs_) * to_native(rhs_));
        }

        template<class _Hi, class _Low>
        static _REAL_CONSTEXPR int128_base<_Hi, _Low> shl(int128_base<_Hi, _Low> lhs_, unsigned rhs_) {
            return from_native(to_native(lhs_) << static_cast<decltype(to_native(lhs_))>(rhs_)); // NOLINT signed shift
        }

        template<class _Hi, class _Low>
        static _REAL_CONSTEXPR int128_base<_Hi, _Low> div(int128_base<_Hi, _Low> lhs_, int128_base<_Hi, _Low> rhs_) {
            return from_native(to_native(lhs_) / to_native(rhs_));
        }

        template<class _Hi, class _Low>
        static _REAL_CONSTEXPR int128_base<_Hi, _Low> mod(int128_base<_Hi, _Low> lhs_, int128_base<_Hi, _Low> rhs_) {
            return from_native(to_native(lhs_) % to_native(rhs_));
        }

        static void part_div(uint128_t value_, uint64_t div_, uint64_t& high_, uint64_t& mid_, uint64_t& low_) {
            // on some cpu, compiler won't do optimize for us
            auto vv_ = to_native(value_);
            auto rest_ = vv_ / div_;
            low_ = static_cast<uint64_t>(vv_) - div_ * static_cast<uint64_t>(rest_);
            high_ = static_cast<uint64_t>(rest_ / div_);
            mid_ = static_cast<uint64_t>(rest_) - div_ * high_;
        }

        template<class _Tp, class _Hi, class _Low>
        static _REAL_CONSTEXPR _Tp cast_to_float(int128_base<_Hi, _Low> value_) {
            return static_cast<_Tp>(to_native(value_));
        };

    };

#endif

    _REAL_CONSTEXPR bool operator<(int128_t lhs_, int128_t rhs_) { return detail_delegate<>::cmp(lhs_, rhs_); }

    _REAL_CONSTEXPR bool operator<(uint128_t lhs_, uint128_t rhs_) { return detail_delegate<>::cmp(lhs_, rhs_); }

    _REAL_CONSTEXPR uint128_t operator>>(uint128_t lhs_, int rhs_) {
        return detail_delegate<>::shr(lhs_, static_cast<unsigned>(rhs_));
    }

    _REAL_CONSTEXPR int128_t operator>>(int128_t lhs_, int rhs_) {
        return detail_delegate<>::sar(lhs_, static_cast<unsigned>(rhs_));
    }

    _REAL_CONSTEXPR int128_t operator*(int128_t lhs_, int128_t rhs_) { return detail_delegate<>::imul(lhs_, rhs_); }

    _REAL_CONSTEXPR uint128_t operator*(uint128_t lhs_, uint128_t rhs_) { return detail_delegate<>::imul(lhs_, rhs_); }

    _REAL_CONSTEXPR uint128_t operator<<(uint128_t lhs_, int rhs_) {
        return detail_delegate<>::shl(lhs_, static_cast<unsigned>(rhs_));
    }

    _REAL_CONSTEXPR int128_t operator<<(int128_t lhs_, int rhs_) {
        return detail_delegate<>::shl(lhs_, static_cast<unsigned>(rhs_));
    }

    inline uint128_t operator/(uint128_t lhs_, uint128_t rhs_) { return detail_delegate<>::div(lhs_, rhs_); };

    inline int128_t operator/(int128_t lhs_, int128_t rhs_) { return detail_delegate<>::div(lhs_, rhs_); };

    inline uint128_t operator%(uint128_t lhs_, uint128_t rhs_) { return detail_delegate<>::mod(lhs_, rhs_); };

    inline int128_t operator%(int128_t lhs_, int128_t rhs_) { return detail_delegate<>::mod(lhs_, rhs_); }

    template<class _Hi, class _Low>
    template<class _Tp>
    _REAL_CONSTEXPR _Tp int128_base<_Hi, _Low>::cast_to_float() const {
        return detail_delegate<>::cast_to_float<_Tp>(*this);
    }

    template<class _CharT, class _Traits>
    inline std::basic_ostream<_CharT, _Traits>&
        print_value(std::basic_ostream<_CharT, _Traits>& out_, bool signed_integral_, uint128_t value_) {
        _REAL_CONSTEXPR std::size_t buf_size_ = 45;

        typename std::basic_ostream<_CharT, _Traits>::sentry sentry_(out_);
        if (!sentry_) return out_;
        auto flags_ = out_.flags(), base_flag_ = flags_ & std::ios::basefield;
        auto adjust_field_ = flags_ & std::ios::adjustfield;
        auto show_base_ = bool(flags_ & std::ios::showbase); // work not dec
        auto show_pos_ = bool(flags_ & std::ios::showpos); // work only dec
        auto upper_case_ = bool(flags_ & std::ios::uppercase); // work only hex
        auto ns_ = out_.width(0);
        auto fl_ = out_.fill();

        char buf_[buf_size_];
        char const* prefix_ = nullptr;
        int offset_ = 0;

        switch (base_flag_) {
        case std::ios::hex: {
            if (show_base_ && value_) prefix_ = upper_case_ ? "0X" : "0x";
            if (value_ >> 64) {
                offset_ = snprintf(buf_, buf_size_,
                    upper_case_ ? "%" PRIX64 "%016" PRIX64 : "%" PRIx64 "%016" PRIx64,
                    (uint64_t)(value_ >> 64), (uint64_t)value_);
            }
            else {
                offset_ = snprintf(buf_, buf_size_,
                    upper_case_ ? "%" PRIX64 : "%" PRIx64, (uint64_t)value_);
            }
            break;
        }
        case std::ios::oct: {
            _REAL_CONSTEXPR uint64_t mask_ = (UINT64_C(1) << 63U) - 1;
            if (show_base_ && value_) buf_[offset_++] = '0';
            auto x_ = (uint64_t)(value_ >> 126U);
            auto y_ = (uint64_t)(value_ >> 63U) & mask_;
            auto z_ = (uint64_t)(value_)&mask_;
            if (x_) {
                offset_ += snprintf(buf_ + offset_, buf_size_ - offset_, "%" PRIo64 "%021" PRIo64 "%021" PRIo64,
                    x_, y_, z_);
            }
            else if (y_) {
                offset_ += snprintf(buf_ + offset_, buf_size_ - offset_, "%" PRIo64 "%021" PRIo64, y_, z_);
            }
            else {
                offset_ += snprintf(buf_ + offset_, buf_size_ - offset_, "%" PRIo64, z_);
            }
            break;
        }
        default: {
            if (signed_integral_) {
                if (value_ >> 127) { // negative
                    prefix_ = "-";
                    value_ = -value_;
                }
                else if (show_pos_) {
                    prefix_ = "+";
                }
            }
            uint64_t high_, mid_, low_;
            detail_delegate<>::part_div(value_, UINT64_C(10000000000000000000), high_, mid_, low_);
            if (high_) {
                offset_ = snprintf(buf_, buf_size_, "%" PRIu64 "%019" PRIu64 "%019" PRIu64,
                    high_, mid_, low_);
            }
            else if (mid_) {
                offset_ = snprintf(buf_, buf_size_, "%" PRIu64 "%019" PRIu64,
                    mid_, low_);
            }
            else {
                offset_ = snprintf(buf_, buf_size_, "%" PRIu64, low_);
            }
            break;
        }
        }

        _CharT o_[2 * buf_size_ - 3];
        _CharT* os_;
        _CharT* op_;  // prefix here
        _CharT* oe_ = o_ + (sizeof(o_) / sizeof(o_[0]));  // end of output

        auto loc_ = out_.getloc();
        auto& ct_ = std::use_facet<std::ctype<_CharT> >(loc_);
        auto& npt_ = std::use_facet<std::numpunct<_CharT> >(loc_);
        std::string grouping_ = npt_.grouping();

        // no worry group is not empty
        auto limit_ = grouping_.size();
        if (limit_ == 0) {
            op_ = oe_ - offset_;
            ct_.widen(buf_, buf_ + offset_, op_);
        }
        else {
            auto thousands_sep_ = npt_.thousands_sep();
            size_t dg_ = size_t(0);
            auto cnt_ = static_cast<unsigned char>(grouping_[dg_]);
            unsigned char dc_ = 0;
            --limit_;
            op_ = oe_;
            for (char* p_ = buf_ + offset_; p_ != buf_; ++dc_) {
                if (cnt_ > 0 && dc_ == cnt_) {
                    *--op_ = thousands_sep_;
                    dc_ = 0;
                    if (dg_ < limit_) cnt_ = static_cast<unsigned char>(grouping_[++dg_]);
                }
                *--op_ = ct_.widen(*--p_);
            }
        }

        if (prefix_) {
            auto prefix_len_ = strlen(prefix_);
            os_ = op_ - prefix_len_;
            ct_.widen(prefix_, prefix_ + prefix_len_, os_);
        }
        else {
            os_ = op_;
        }

        auto sz_ = static_cast<std::streamsize>(oe_ - os_);
        // assert(sz_ <= (sizeof(o_) / sizeof(o_[0])));

        if (ns_ > sz_) {
            ns_ -= sz_;
            std::basic_string<_CharT, _Traits> sp_(ns_, fl_);
            switch (adjust_field_) {
            case std::ios::left:
                return out_.write(os_, sz_).write(sp_.data(), ns_);
            case std::ios::internal:
                return out_.write(os_, static_cast<std::streamsize>(op_ - os_))
                    .write(sp_.data(), ns_)
                    .write(op_, static_cast<std::streamsize>(oe_ - op_));
            default:
                return out_.write(sp_.data(), ns_).write(os_, sz_);
            }
        }
        return out_.write(os_, sz_);
    }

    template<class _CharT, class _Traits>
    inline std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& out, uint128_t _Val) {
        return print_value(out, false, _Val);
    }

    template<class _CharT, class _Traits>
    inline std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& out, int128_t _Val) {
        return print_value(out, true, uint128_t(_Val));
    }
}

#ifdef INT128_SPECIALIZATION
namespace std {
#pragma push_macro("MAKE_TYPE")
#define MAKE_TYPE(outter, inner, parent) \
template<> struct outter<large_int::inner> : std::parent {}; \
template<> struct outter<const large_int::inner> : std::parent {}; \
template<> struct outter<volatile large_int::inner> : std::parent {}; \
template<> struct outter<const volatile large_int::inner> : std::parent {};
    MAKE_TYPE(is_integral, uint128_t, true_type)
        MAKE_TYPE(is_integral, int128_t, true_type)
        MAKE_TYPE(is_signed, uint128_t, false_type)
        MAKE_TYPE(is_signed, int128_t, true_type)
#undef MAKE_TYPE
#define MAKE_TYPE(outter, inner, target) \
template<> struct outter<large_int::inner> { typedef large_int::target type; }; \
template<> struct outter<const large_int::inner> { typedef const large_int::target type; }; \
template<> struct outter<volatile large_int::inner> { typedef volatile large_int::target type; }; \
template<> struct outter<const volatile large_int::inner> { typedef const volatile large_int::target type; };
        MAKE_TYPE(make_signed, uint128_t, int128_t)
        MAKE_TYPE(make_unsigned, int128_t, uint128_t)
#pragma pop_macro("MAKE_TYPE")

        template<class _Hi, class _Low>
    struct numeric_limits<large_int::int128_base<_Hi, _Low> > {
    private:
        typedef large_int::int128_base<_Hi, _Low> _Tp;
    public:
        static _REAL_CONSTEXPR const bool is_specialized = true;
        static _REAL_CONSTEXPR const bool is_signed = numeric_limits<_Hi>::is_signed;
        static _REAL_CONSTEXPR const bool is_integer = true;
        static _REAL_CONSTEXPR const bool is_exact = true;
        static _REAL_CONSTEXPR const bool has_infinity = false;
        static _REAL_CONSTEXPR const bool has_quiet_NaN = false;
        static _REAL_CONSTEXPR const bool has_signaling_NaN = false;
        static _REAL_CONSTEXPR const std::float_denorm_style has_denorm = std::denorm_absent;
        static _REAL_CONSTEXPR const bool has_denorm_loss = false;
        static _REAL_CONSTEXPR const std::float_round_style round_style = std::round_toward_zero;
        static _REAL_CONSTEXPR const bool is_iec559 = false;
        static _REAL_CONSTEXPR const bool is_bounded = true;
        static _REAL_CONSTEXPR const bool is_modulo = numeric_limits<_Hi>::is_modulo;
        static _REAL_CONSTEXPR const int digits = static_cast<int>(sizeof(_Tp) * 8 - is_signed);
        static _REAL_CONSTEXPR const int digits10 = digits * 3 / 10;
        static _REAL_CONSTEXPR const int max_digits10 = 0;
        static _REAL_CONSTEXPR const int radix = 2;
        static _REAL_CONSTEXPR const int min_exponent = 0;
        static _REAL_CONSTEXPR const int min_exponent10 = 0;
        static _REAL_CONSTEXPR const int max_exponent = 0;
        static _REAL_CONSTEXPR const int max_exponent10 = 0;
        static _REAL_CONSTEXPR const bool traps = numeric_limits<_Hi>::traps;
        static _REAL_CONSTEXPR const bool tinyness_before = false;

        static _REAL_CONSTEXPR _Tp min() { return is_signed ? _Tp(1) << digits : _Tp(0); }

        static _REAL_CONSTEXPR _Tp lowest() { return min(); }

        static _REAL_CONSTEXPR _Tp max() { return ~min(); }

        static _REAL_CONSTEXPR _Tp epsilon() { return _Tp(0); }

        static _REAL_CONSTEXPR _Tp round_error() { return _Tp(0); }

        static _REAL_CONSTEXPR _Tp infinity() { return _Tp(0); }

        static _REAL_CONSTEXPR _Tp quiet_NaN() { return _Tp(0); }

        static _REAL_CONSTEXPR _Tp signaling_NaN() { return _Tp(0); }

        static _REAL_CONSTEXPR _Tp denorm_min() { return _Tp(0); }
    };
}
#endif

#ifndef INT128_NO_EXPORT
#define INT128_C(val) val##_L128
#define UINT128_C(val) val##_U128
// add space between ‘""’ and suffix identifier, or may compile failed
using namespace large_int::literals;
using large_int::uint128_t;
using large_int::int128_t;
#endif

#else
typedef __int128_t int128_t;

#endif


class Real;

extern _REAL_CONSTEXPR Real operator "" _r(const char *v, size_t n);

extern _REAL_CONSTEXPR Real operator "" _r(unsigned long long v);

class Real {
public:
    static_assert(sizeof(void *) == 8, "compiler must set to 64bit");
    typedef int64_t T;
    typedef uint64_t UT;
    static const unsigned int Cf = 32;
    static const int TBS = sizeof(T) * 8;
    typedef T data_t;
    typedef UT udata_t;
    static const data_t f_mask = (data_t) (uint64_t(-1) >> (TBS - Cf));

    [[maybe_unused]] static const data_t i_mask = (data_t) (~f_mask);

    static const data_t f_range = f_mask + 1;

    _REAL_CONSTEXPR Real() = default;

    _REAL_CONSTEXPR Real(int intVal) {

        mRaw = (data_t(intVal) << Cf);
    }

    static _REAL_CONSTEXPR Real rawToReal(const data_t raw) {

        Real r;
        r.mRaw = raw;
        return r;
    }

    _REAL_CONSTEXPR Real &operator=(int intVal) {
        mRaw = data_t(intVal) << Cf;
        return *this;
    }


    _REAL_CONSTEXPR Real &operator=(const Real &intVal) = default;

    [[nodiscard]] _REAL_CONSTEXPR data_t data() const {
        return mRaw;
    }

    _REAL_CONSTEXPR Real operator+(const Real &b) const {
        Real r(0);
        r.mRaw = (mRaw + b.mRaw);
        return r;
    }

    _REAL_CONSTEXPR Real operator-(const Real &b) const {
        Real r(0);
        r.mRaw = (mRaw - b.mRaw);
        return r;
    }

    _REAL_CONSTEXPR Real operator*(const Real &b) const {
        Real r(0);
        r.mRaw = (data_t) ((int128_t(mRaw) * b.mRaw) >> Cf);
        return r;
    }

    _REAL_CONSTEXPR Real operator/(const Real &b) const {
        Real r(0);
        r.mRaw = (data_t) ((int128_t(mRaw) << Cf) / b.mRaw);
        return r;
    }

    _REAL_CONSTEXPR Real operator-() const {
        Real r;
        r.mRaw = -mRaw;
        return r;
    }

    _REAL_CONSTEXPR Real &operator+=(const Real &a) {
        mRaw += a.mRaw;
        return *this;
    }

    _REAL_CONSTEXPR Real &operator-=(const Real &a) {
        mRaw -= a.mRaw;
        return *this;
    }

    _REAL_CONSTEXPR Real &operator*=(const Real &a) {
        *this = *this * a;
        return *this;
    }

    _REAL_CONSTEXPR Real &operator*=(int i) {
        return *this *= Real(i);
    }

    _REAL_CONSTEXPR Real &operator*=(double) = delete;

    _REAL_CONSTEXPR Real &operator/=(const Real &a) {
        *this = *this / a;
        return *this;
    }

    _REAL_CONSTEXPR Real &operator=(double) = delete;


    _REAL_CONSTEXPR bool operator==(const Real &b) const {
        return mRaw == b.mRaw;
    }

    _REAL_CONSTEXPR bool operator!=(const Real &b) const {
        return mRaw != b.mRaw;
    }

    _REAL_CONSTEXPR bool operator<(const Real &b) const {
        return mRaw < b.mRaw;
    }

    _REAL_CONSTEXPR bool operator>(const Real &b) const {
        return mRaw > b.mRaw;
    }

    _REAL_CONSTEXPR bool operator<=(const Real &b) const {
        return mRaw <= b.mRaw;
    }

    _REAL_CONSTEXPR bool operator>=(const Real &b) const {
        return mRaw >= b.mRaw;
    }

    _REAL_CONSTEXPR explicit operator double() const {
        return (double) ((mRaw >> Cf)) + double(mRaw & f_mask) / (double) f_range;
    }

    static _REAL_CONSTEXPR data_t doubleToData(double f) {
        return f * (data_t) (udata_t(1u) << Cf);
    }

    static _REAL_CONSTEXPR bool IS0T9(char a) {
        return ((a) >= '0' && (a) <= '9');
    }

    static _REAL_CONSTEXPR bool IS1T9(char a) {
        return ((a) >= '1' && (a) <= '9');
    }

    static _REAL_CONSTEXPR double constPown(double x, int y) {
        if (y == 0)
            return 1;
        if (y == 1)
            return x;
        double r = x;
        if (y < 0) {
            for (int i = 0; i < -y - 1; i++) {
                r *= x;
            }
            return 1 / r;

        } else {
            for (int i = 0; i < y - 1; i++) {
                r *= x;
            }
            return r;
        }

    }


    static _REAL_CONSTEXPR Real strToReal(const char *str, int len) {
        _REAL_CONSTEXPR int CONFIG_ZERO_FIRST = 0;
        int pos = 1;
        char beginch = str[0];
        char ch = beginch;
        int sig = 1;
        int64_t ir = 0;
        int f1 = 0;
        int en = 0;
        int es = 1;
        int flen = 0;
        int ilen = 0;
        if (beginch == '-') {
            ch = str[pos++];
            sig = -1;
        }

        if ('0' == ch && !CONFIG_ZERO_FIRST) {}
        else if (IS0T9(ch)) {
            ir = (ch - '0');
            ilen++;
            for (char wch = str[pos]; IS0T9(wch); wch = str[pos]) {
                ch = str[pos++];
                ir = ir * 10 + (ch - '0');
                ilen++;
            }

        } else {
            if (beginch == '-')
                assert(0 && "Negative sign must be followed by a number");
            assert(0 && "unknown char");
        }

        char wch = str[pos];

        if (wch == '.') {
            int zeroNum = 0;
            ch = str[pos++];
            ch = str[pos++];

            if (!IS0T9(ch))
                assert(0 && "The decimal point must be followed by a number");
            if (ch == '0') {
                zeroNum++;
            } else {
                f1 = f1 * 10 + (ch - '0');
                ir = ir * 10 + (ch - '0');
                flen++;
            }


            for (wch = str[pos]; IS0T9(wch); wch = str[pos]) {
                ch = str[pos++];
                if (ch == '0') {

                    zeroNum++;
                } else {
                    if (zeroNum > 0) {

                        for (int i = 0; i < zeroNum; i++) {
                            f1 = f1 * 10 + ('0' - '0');
                            ir = ir * 10 + ('0' - '0');
                            flen++;
                        }
                        zeroNum = 0;
                    }

                    f1 = f1 * 10 + (ch - '0');
                    ir = ir * 10 + (ch - '0');
                    flen++;
                }
            }

        }
        if (wch == 'e' || wch == 'E') {
            ch = str[pos++];
            ch = str[pos++];

            if (ch == '+' || ch == '-') {
                if (ch == '-')
                    es = -1;
                ch = str[pos++];
            }

            if (!IS0T9(ch))
                assert(0 && "E must be followed by a plus sign, a minus sign, or a number");
            en = (ch - '0');
            for (char wch = str[pos]; IS0T9(wch); wch = str[pos]) {
                ch = str[pos++];
                en = en * 10 + (ch - '0');
            }

        }
        if (pos < len - 1) {

            assert(0 && "unknown char");
        }

        int128_t retx = int128_t(ir) << Cf;
        {
            Real a = 0;
            a.mRaw = (data_t) retx;

        }

        int128_t mRaw = ((int128_t(retx) << Cf) / ((int128_t) constPown(10, flen) << Cf));
        Real a = 0;
        a.mRaw = (data_t) mRaw;
        a *= sig;

        if (es > 0) {
            a *= (int) constPown(10, en);

        } else {
            a /= (int) constPown(10, en);
        }

        return a;
    }

    static _REAL_CONSTEXPR Real PI() {
        Real r = "3.1415926535897932"_r;
        return r;
    }

    static _REAL_CONSTEXPR Real HALF_PI() { return PI() / 2_r; }

    static _REAL_CONSTEXPR Real TWO_PI() { return PI() * 2_r; }

    static _REAL_CONSTEXPR Real E() {

        Real r = "2.7182818284590452"_r;
        return r;
    }

    static _REAL_CONSTEXPR Real fmod(const Real &a, const Real &b) {
        Real r;
        r.mRaw = a.mRaw % b.mRaw;
        return r;
    }

    static _REAL_CONSTEXPR Real abs(const Real &a) {
        Real r = (a >= 0_r) ? a : -a;
        return r;
    }

    static _REAL_CONSTEXPR Real sin(const Real a) {
        Real x = Real::fmod(a, Real::TWO_PI());
        x = x / Real::HALF_PI();
        if (x < 0_r)
            x += 4_r;
        int sign = +1;
        if (x > 2_r) {
            sign = -1;
            x -= 2_r;
        }

        if (x > 1_r) {
            x = 2_r - x;
        }

        Real bb = Real(sign) * x * (Real::PI() - x * x * (Real::TWO_PI() - 5_r - x * x * (Real::PI() - 3_r))) / 2_r;
        return bb;
    }

    static _REAL_CONSTEXPR Real cos(const Real &a) {
        return sin(Real::HALF_PI() + a);
    }

    static _REAL_CONSTEXPR Real tan(const Real &a) {
        Real cx = cos(a);
        Real c2 = abs(cx);
        assert(c2.mRaw > 1);
        return sin(a) / cx;
    }

    _REAL_CONSTEXPR static unsigned int highestBit(uint64_t v) {
        return sizeof(v) * 8 - 1 - countLeadingZeros64(v);
    }

    _REAL_CONSTEXPR static unsigned int countLeadingZeros64(uint64_t n) {
#if defined(__GNUC__)//TODO clang
        static_assert(sizeof(unsigned long long) == sizeof(n),
                      "arg must 64bit");
        return n == 0 ? 64 : __builtin_clzll(n);
#elif defined(_MSC_VER) && defined(_M_X64)
        unsigned long result;
        if (_BitScanReverse64(&result, n)) {
            return 63 - result;
        }
        return 64;
#else
        int zeroes = 60;
        if (n >> 32) zeroes -= 32, n >>= 32;
        if (n >> 16) zeroes -= 16, n >>= 16;
        if (n >> 8) zeroes -= 8, n >>= 8;
        if (n >> 4) zeroes -= 4, n >>= 4;
        return "\4\3\2\2\1\1\1\1\0\0\0\0\0\0\0\0"[n] + zeroes;
#endif
    }


    static void remcoeff(double a, double b, double *p, int n, double eps, double (*f)(double)) {
        int i, j, k, m;
        const int cnt = 20;
        double x[cnt + 1], g[cnt + 1], d, t, u, s, xx, x0, h, yy;
        if (n > cnt)n = cnt;
        m = n + 1;
        d = 1.0e+35;
        for (k = 0; k <= n; k++) {
            t = ::cos((n - k) * 3.1415926535898 / (1.0 * n));
            x[k] = (b + a + (b - a) * t) / 2.0;
        }

        while (1 == 1) {
            u = 1.0;
            for (i = 0; i <= m - 1; i++) {
                p[i] = (*f)(x[i]);
                g[i] = -u;
                u = -u;
            }

            for (j = 0; j <= n - 1; j++) {
                k = m;
                s = p[k - 1];
                xx = g[k - 1];
                for (i = j; i <= n - 1; i++) {
                    t = p[n - i + j - 1];
                    x0 = g[n - i + j - 1];
                    p[k - 1] = (s - t) / (x[k - 1] - x[m - i - 2]);
                    g[k - 1] = (xx - x0) / (x[k - 1] - x[m - i - 2]);
                    k = n - i + j;
                    s = t;
                    xx = x0;
                }
            }

            u = -p[m - 1] / g[m - 1];

            for (i = 0; i <= m - 1; i++) {
                p[i] += g[i] * u;
            }

            for (j = 1; j <= n - 1; j++) {
                k = n - j;
                h = x[k - 1];
                s = p[k - 1];
                for (i = m - j; i <= n; i++) {
                    t = p[i - 1];
                    p[k - 1] = s - h * t;
                    s = t;
                    k = i;
                }
            }

            p[m - 1] = fabs(u);
            u = p[m - 1];

            if (fabs(u - d) <= eps)return;

            d = u;
            h = 0.1 * (b - a) / (1.0 * n);
            xx = a;
            x0 = a;

            while (x0 <= b) {
                s = (*f)(x0);
                t = p[n - 1];
                for (i = n - 2; i >= 0; i--)
                    t = t * x0 + p[i];
                s = fabs(s - t);
                if (s > u) {
                    u = s;
                    xx = x0;
                }

                x0 = x0 + h;
            }

            s = (*f)(xx);
            t = p[n - 1];

            for (i = n - 2; i >= 0; i--)
                t = t * xx + p[i];

            yy = s - t;
            i = 1;
            j = n + 1;

            while ((j - i) != 1) {
                k = (i + j) / 2;
                if (xx < x[k - 1])j = k;
                else i = k;
            }

            if (xx < x[0]) {
                s = (*f)(x[0]);
                t = p[n - 1];
                for (k = n - 2; k >= 0; k--)
                    t = t * x[0] + p[k];
                s = s - t;

                if (s * yy > 0.0)x[0] = xx;
                else {
                    for (k = n - 1; k >= 0; k--)
                        x[k + 1] = x[k];
                    x[0] = xx;
                }
            } else {
                if (xx > x[n]) {
                    s = (*f)(x[n]);
                    t = p[n - 1];
                    for (k = n - 2; k >= 0; k--)
                        t = t * x[n] + p[k];
                    s = s - t;

                    if (s * yy > 0.0)x[n] = xx;
                    else {
                        for (k = 0; k <= n - 1; k++)
                            x[k] = x[k + 1];
                        x[n] = xx;
                    }
                } else {
                    i = i - 1;
                    j = j - 1;
                    s = (*f)(x[i]);
                    t = p[n - 1];
                    for (k = n - 2; k >= 0; k--)
                        t = t * x[i] + p[k];
                    s = s - t;

                    if (s * yy > 0.0)x[i] = xx;
                    else x[j] = xx;
                }
            }
        }
    }

    static void coeff_gen_exp() {
        {
#define __REAL_CONST_INT_CNT 4
#define __REAL_CONST_INT_CNT_STR(R)  #R
#define __REAL_CONST_INT_CNT_STR2(R)  __REAL_CONST_INT_CNT_STR(R)
            const int cnt = __REAL_CONST_INT_CNT;
            double a, b, eps;
            double c, d;
            a = 0;
            b = 1;

            eps = 1.0e-10;
            const int cnt2 = 10;
            double o[cnt2][cnt + 2] = {};
            printf("//THIS CODE generate by Real::%s function:\n", __func__);
            printf("Real coeffSet[][" __REAL_CONST_INT_CNT_STR2(__REAL_CONST_INT_CNT + 1) "] = {\n");
            for (int i1 = 0; i1 < cnt2; i1++) {
                c = a + i1 * 1.0 / cnt2;
                d = b + i1 * 1.0 / cnt2 + 1.0 / cnt2;
                remcoeff(c, d, o[i1], cnt + 1, eps, ::exp);
                printf("\t{");
                for (int i = 0; i < cnt + 1; i++) {
                    printf("Real::rawToReal(%lldll), ", doubleToReal(o[i1][i]).mRaw);

                }
                printf("},\n");
            }
            printf("};\n");
        }
    }

    static void coeff_gen_log2() {
        {
#define __REAL_CONST_INT_CNT 4
#define __REAL_CONST_INT_CNT_STR(R)  #R
#define __REAL_CONST_INT_CNT_STR2(R)  __REAL_CONST_INT_CNT_STR(R)
            const int cnt = __REAL_CONST_INT_CNT;
            double a, b, eps;
            double c, d;
            a = 1;
            b = 2;

            eps = 1.0e-10;
            const int cnt2 = 10;
            double o[cnt2][cnt + 2] = {};
            printf("//THIS CODE generate by Real::%s function:\n", __func__);
            printf("_REAL_CONSTEXPR Real coeffSet[][" __REAL_CONST_INT_CNT_STR2(__REAL_CONST_INT_CNT + 1) "] = {\n");
            for (int i1 = 0; i1 < cnt2; i1++) {
                c = a + i1 * 1.0 / cnt2;
                d = b + i1 * 1.0 / cnt2 + 1.0 / cnt2;
                remcoeff(c, d, o[i1], cnt + 1, eps, ::log2);
                printf("\t{");
                for (int i = 0; i < cnt + 1; i++) {
                    printf("Real::rawToReal(%lldll), ", doubleToReal(o[i1][i]).mRaw);

                }
                printf("},\n");
            }
            printf("};\n");
        }
    }

    static void coeff_gen_exp2() {
        {
#define __REAL_CONST_INT_CNT 4
#define __REAL_CONST_INT_CNT_STR(R)  #R
#define __REAL_CONST_INT_CNT_STR2(R)  __REAL_CONST_INT_CNT_STR(R)
            const int cnt = __REAL_CONST_INT_CNT;
            double a, b, eps;
            double c, d;
            a = 0;
            b = 1;

            eps = 1.0e-10;
            const int cnt2 = 10;
            double o[cnt2][cnt + 2] = {};
            printf("//THIS CODE generate by Real::%s function:\n", __func__);
            printf("_REAL_CONSTEXPR Real coeffSet[][" __REAL_CONST_INT_CNT_STR2(__REAL_CONST_INT_CNT + 1) "] = {\n");
            for (int i1 = 0; i1 < cnt2; i1++) {
                c = a + i1 * 1.0 / cnt2;
                d = b + i1 * 1.0 / cnt2 + 1.0 / cnt2;
                remcoeff(c, d, o[i1], cnt + 1, eps, ::exp2);
                printf("\t{");
                for (int i = 0; i < cnt + 1; i++) {
                    printf("Real::rawToReal(%lldll), ", doubleToReal(o[i1][i]).mRaw);

                }
                printf("},\n");
            }
            printf("};\n");
        }
    }

    static void coeff_gen_atan() {
        {
#define __REAL_CONST_INT_CNT 4
#define __REAL_CONST_INT_CNT_STR(R)  #R
#define __REAL_CONST_INT_CNT_STR2(R)  __REAL_CONST_INT_CNT_STR(R)
            const int cnt = __REAL_CONST_INT_CNT;
            double a, b, eps, p[cnt + 2];
            double c, d;
            a = 0;
            b = 1;

            eps = 1.0e-10;
            const int cnt2 = 10;
            double o[cnt2][cnt + 2] = {};
            printf("//THIS CODE generate by Real::%s function:\n", __func__);
            printf("_REAL_CONSTEXPR Real coeffSet[][" __REAL_CONST_INT_CNT_STR2(__REAL_CONST_INT_CNT + 1) "] = {\n");
            for (int i1 = 0; i1 < cnt2; i1++) {
                c = a + i1 * 1.0 / cnt2;
                d = b + i1 * 1.0 / cnt2 + 1.0 / cnt2;
                remcoeff(c, d, o[i1], cnt + 1, eps, ::atan);
                printf("\t{");
                for (int i = 0; i < cnt + 1; i++) {
                    printf("Real::rawToReal(%lldll), ", doubleToReal(o[i1][i]).mRaw);

                }
                printf("},\n");
            }
            printf("};\n");
        }
    }

    static _REAL_CONSTEXPR Real copysign(const Real &r, const Real &y) noexcept {
        Real x = r;
        return x = abs(x), (y >= 0_r) ? x : -x;
    }

    static _REAL_CONSTEXPR Real asin(const Real &x) {
        assert(x >= -1_r && x <= 1_r);
        const auto yy = 1_r - x * x;
        if (yy == 0_r) {
            return copysign(HALF_PI(), x);
        }
        return atan(x / sqrt(yy));
    }

    static _REAL_CONSTEXPR Real atan(const Real &x) {
        if (x < 0_r) {
            return -atan(-x);
        }
        if (x > 1_r) {
            return Real::HALF_PI() - atan(1_r / x);
        }
        assert(x >= 0_r && x < 1_r);
        const int cnt2 = 10;
        const int firstN = int(((x.mRaw & Real::f_mask) * cnt2) >> Cf);

        //THIS CODE generate by Real::coeff_gen_atan() function
        _REAL_CONSTEXPR Real coeffSet[][4 + 1] = {
                {Real::rawToReal(-791733ll),    Real::rawToReal(4323565863ll), Real::rawToReal(
                        -145955402ll),  Real::rawToReal(
                        -1333910181ll), Real::rawToReal(529560005ll),},
                {Real::rawToReal(-7511619ll),   Real::rawToReal(4394650585ll), Real::rawToReal(
                        -374943011ll),  Real::rawToReal(
                        -1050188161ll), Real::rawToReal(410924654ll),},
                {Real::rawToReal(-24981624ll),  Real::rawToReal(4529082684ll), Real::rawToReal(
                        -717919045ll),  Real::rawToReal(
                        -697338479ll),  Real::rawToReal(284881398ll),},
                {Real::rawToReal(-56134852ll),  Real::rawToReal(4721550976ll), Real::rawToReal(
                        -1128191211ll), Real::rawToReal(
                        -335089704ll),  Real::rawToReal(171785748ll),},
                {Real::rawToReal(-99754773ll),  Real::rawToReal(4948933758ll), Real::rawToReal(
                        -1546480173ll), Real::rawToReal(
                        -10970323ll),   Real::rawToReal(81879073ll),},
                {Real::rawToReal(-150773567ll), Real::rawToReal(5180260196ll), Real::rawToReal(
                        -1921875826ll), Real::rawToReal(
                        248546229ll),   Real::rawToReal(17089000ll),},
                {Real::rawToReal(-202101520ll), Real::rawToReal(5386789904ll), Real::rawToReal(
                        -2222115584ll), Real::rawToReal(
                        435968316ll),   Real::rawToReal(-25437604ll),},
                {Real::rawToReal(-246404091ll), Real::rawToReal(5547323784ll), Real::rawToReal(
                        -2433697162ll), Real::rawToReal(
                        556412294ll),   Real::rawToReal(-50482074ll),},
                {Real::rawToReal(-278019537ll), Real::rawToReal(5651562822ll), Real::rawToReal(
                        -2559306030ll), Real::rawToReal(
                        622070688ll),   Real::rawToReal(-63066478ll),},
                {Real::rawToReal(-295163618ll), Real::rawToReal(5703396255ll), Real::rawToReal(
                        -2616753828ll), Real::rawToReal(
                        649762348ll),   Real::rawToReal(-67971705ll),},
        };

        return ((((coeffSet[firstN][4] * x + coeffSet[firstN][3]) * x +
                  coeffSet[firstN][2]) * x + coeffSet[firstN][1]) * x +
                coeffSet[firstN][0]);

    }

    static _REAL_CONSTEXPR Real acos(const Real &x) {
        assert(x >= -1_r && x <= 1_r);
        if (x == 1_r)
            return Real::PI();
        const auto yy = 1_r - x * x;
        return 2_r * atan(sqrt(yy) / (1_r + x));
    }

    static _REAL_CONSTEXPR Real atan2(const Real &x, const Real &y) {
        if (x == 0_r) {
            assert(y != 0_r);
            return (y > 0_r) ? Real::HALF_PI() : -Real::HALF_PI();
        }
        auto ret = atan(y / x);
        if (x < 0_r) {
            return (y >= 0_r) ? ret + Real::PI() : ret - Real::PI();
        }
        return ret;
    }

    static _REAL_CONSTEXPR Real pownf(const Real &base, int exp) noexcept {
        if (base == 0_r) {
            assert(exp > 0);
            return 0_r;
        }

        Real result{1};
        if (exp < 0) {
            for (Real i = base; exp != 0; exp /= 2, i *= i) {
                if ((exp % 2) != 0) {
                    result /= i;
                }
            }
        } else {
            for (Real i = base; exp != 0; exp /= 2, i *= i) {
                if ((exp % 2) != 0) {
                    result *= i;
                }
            }
        }
        return result;
    }

    static _REAL_CONSTEXPR Real pow(const Real &base, const Real &exp) noexcept {
        if (base == 0_r) {
            assert(exp > 0_r);
            return 0_r;
        }
        if (exp < 0_r)
            return 1_r / pow(base, -exp);

        _REAL_CONSTEXPR data_t FRAC = udata_t(1) << Cf;
        if (exp.mRaw % FRAC == 0)
            return pownf(base, exp.mRaw / FRAC);

        assert(base > 0_r);
        return exp2(log2(base) * exp);
    }

    static _REAL_CONSTEXPR Real exp(const Real &r) noexcept {
        Real x = r;
        if (x < 0_r) {
            return 1_r / exp(-x);
        }
        _REAL_CONSTEXPR data_t FRAC = udata_t(1) << Cf;
        const data_t x_int = x.mRaw / FRAC;
        x -= Real((int) x_int);//TODO (int)x_int
        assert(x >= 0_r && x < 1_r);

        const int cnt2 = 10;
        const int firstN = int(((x.mRaw & Real::f_mask) * cnt2) >> Cf);

        //THIS CODE generate by Real::coeff_gen_exp function:
        _REAL_CONSTEXPR Real coeffSet[][4 + 1] = {
                {Real::rawToReal(4295165143ll), Real::rawToReal(4286286023ll), Real::rawToReal(
                        2208155444ll), Real::rawToReal(
                        569835864ll),   Real::rawToReal(315687169ll),},
                {Real::rawToReal(4296992753ll), Real::rawToReal(4266498251ll), Real::rawToReal(
                        2272392669ll), Real::rawToReal(
                        490210713ll),   Real::rawToReal(348888278ll),},
                {Real::rawToReal(4302001061ll), Real::rawToReal(4227644005ll), Real::rawToReal(
                        2371987175ll), Real::rawToReal(
                        387534152ll),   Real::rawToReal(385581179ll),},
                {Real::rawToReal(4313048376ll), Real::rawToReal(4159123169ll), Real::rawToReal(
                        2518531788ll), Real::rawToReal(
                        257838232ll),   Real::rawToReal(426133105ll),},
                {Real::rawToReal(4334597657ll), Real::rawToReal(4046525213ll), Real::rawToReal(
                        2726178488ll), Real::rawToReal(
                        96575350ll),    Real::rawToReal(470949915ll),},
                {Real::rawToReal(4373335321ll), Real::rawToReal(3870643396ll), Real::rawToReal(
                        3012102311ll), Real::rawToReal(
                        -101459791ll),  Real::rawToReal(520480150ll),},
                {Real::rawToReal(4438969292ll), Real::rawToReal(3606280149ll), Real::rawToReal(
                        3397040172ll), Real::rawToReal(
                        -342218221ll),  Real::rawToReal(575219526ll),},
                {Real::rawToReal(4545249054ll), Real::rawToReal(3220804790ll), Real::rawToReal(
                        3905915847ll), Real::rawToReal(
                        -632495982ll),  Real::rawToReal(635715891ll),},
                {Real::rawToReal(4711259411ll), Real::rawToReal(2672418083ll), Real::rawToReal(
                        4568563935ll), Real::rawToReal(
                        -980046052ll),  Real::rawToReal(702574715ll),},
                {Real::rawToReal(4963050219ll), Real::rawToReal(1908070534ll), Real::rawToReal(
                        5420567425ll), Real::rawToReal(
                        -1393704452ll), Real::rawToReal(776465143ll),},
        };
        return pow(Real::E(), Real((int) x_int)) *
               ((((coeffSet[firstN][4] * x + coeffSet[firstN][3]) * x +
                  coeffSet[firstN][2]) * x + coeffSet[firstN][1]) * x +
                coeffSet[firstN][0]);

    }

    static _REAL_CONSTEXPR Real exp2(const Real &r) noexcept {
        Real x = r;
        if (x < 0_r) {
            return 1_r / exp2(-x);
        }
        _REAL_CONSTEXPR data_t FRAC = udata_t(1) << Cf;
        const data_t x_int = x.mRaw / FRAC;
        x -= Real((int) x_int);
        assert(x >= 0_r && x < 1_r);

        Real r2 = int(udata_t(1) << x_int);


        const int cnt2 = 10;
        const int firstN = int(((x.mRaw & Real::f_mask) * cnt2) >> Cf);

        //THIS CODE generate by Real::coeff_gen_exp2 function:
        _REAL_CONSTEXPR Real coeffSet[][4 + 1] = {
                {Real::rawToReal(4294993839ll), Real::rawToReal(2975867107ll), Real::rawToReal(
                        1040092047ll), Real::rawToReal(
                        218012411ll), Real::rawToReal(60995726ll),},
                {Real::rawToReal(4295235187ll), Real::rawToReal(2973255085ll), Real::rawToReal(
                        1048567496ll), Real::rawToReal(
                        207510476ll), Real::rawToReal(65373600ll),},
                {Real::rawToReal(4295876369ll), Real::rawToReal(2968282399ll), Real::rawToReal(
                        1061309490ll), Real::rawToReal(
                        194377945ll), Real::rawToReal(70065690ll),},
                {Real::rawToReal(4297247674ll), Real::rawToReal(2959779130ll), Real::rawToReal(
                        1079490283ll), Real::rawToReal(
                        178291305ll), Real::rawToReal(75094547ll),},
                {Real::rawToReal(4299841398ll), Real::rawToReal(2946229618ll), Real::rawToReal(
                        1104471732ll), Real::rawToReal(
                        158894152ll), Real::rawToReal(80484343ll),},
                {Real::rawToReal(4304362594ll), Real::rawToReal(2925705933ll), Real::rawToReal(
                        1137829591ll), Real::rawToReal(
                        135794142ll), Real::rawToReal(86260983ll),},
                {Real::rawToReal(4311790863ll), Real::rawToReal(2895791274ll), Real::rawToReal(
                        1181380527ll), Real::rawToReal(
                        108559665ll), Real::rawToReal(92452232ll),},
                {Real::rawToReal(4323455080ll), Real::rawToReal(2853491970ll), Real::rawToReal(
                        1237212159ll), Real::rawToReal(
                        76716228ll),  Real::rawToReal(99087849ll),},
                {Real::rawToReal(4341123233ll), Real::rawToReal(2795136611ll), Real::rawToReal(
                        1307716417ll), Real::rawToReal(
                        39742526ll),  Real::rawToReal(106199727ll),},
                {Real::rawToReal(4367109899ll), Real::rawToReal(2716260655ll), Real::rawToReal(
                        1395626580ll), Real::rawToReal(
                        -2933834ll),  Real::rawToReal(113822049ll),},
        };

        return r2 *
               ((((coeffSet[firstN][4] * x + coeffSet[firstN][3]) * x +
                  coeffSet[firstN][2]) * x + coeffSet[firstN][1]) * x +
                coeffSet[firstN][0]);

    }

    static _REAL_CONSTEXPR Real expm1(const Real &x) noexcept {
        return exp(x) - 1_r;
    }

    static _REAL_CONSTEXPR Real log2(const Real &r) noexcept {
        Real x = r;
        assert(x > 0_r);

        data_t value = x.mRaw;
        int highest = highestBit(value);
        if (highest >= Cf) {
            value = value >> (highest - Cf);
        } else {
            value <<= (Cf - highest);
        }
        x.mRaw = (value);
        assert(x >= 1_r && x < 2_r);

        Real r2 = int(highest - Cf);

        const int cnt2 = 10;
        const int firstN = ((x.mRaw & x.f_mask) * cnt2) >> Cf;

        //THIS CODE generate by Real::coeff_gen_log2 function:
        _REAL_CONSTEXPR Real coeffSet[][4 + 1] = {
                {Real::rawToReal(-10646106503ll), Real::rawToReal(17053298287ll), Real::rawToReal(
                        -8648888818ll), Real::rawToReal(
                        2555626550ll), Real::rawToReal(-313404182ll),},
                {Real::rawToReal(-10202061282ll), Real::rawToReal(15891743044ll), Real::rawToReal(
                        -7527467469ll), Real::rawToReal(
                        2081791329ll), Real::rawToReal(-239420967ll),},
                {Real::rawToReal(-9790941967ll),  Real::rawToReal(14885120345ll), Real::rawToReal(
                        -6615999773ll), Real::rawToReal(
                        1719921420ll), Real::rawToReal(-186240618ll),},
                {Real::rawToReal(-9407882968ll),  Real::rawToReal(14003328174ll), Real::rawToReal(
                        -5864120956ll), Real::rawToReal(
                        1438385625ll), Real::rawToReal(-147163260ll),},
                {Real::rawToReal(-9049124857ll),  Real::rawToReal(13223912027ll), Real::rawToReal(
                        -5236054578ll), Real::rawToReal(
                        1215847025ll), Real::rawToReal(-117899287ll),},
                {Real::rawToReal(-8711594341ll),  Real::rawToReal(12529514232ll), Real::rawToReal(
                        -4705578204ll), Real::rawToReal(
                        1037461220ll), Real::rawToReal(-95613541ll),},
                {Real::rawToReal(-8392827686ll),  Real::rawToReal(11906656385ll), Real::rawToReal(
                        -4253214972ll), Real::rawToReal(
                        892708798ll),  Real::rawToReal(-78390150ll),},
                {Real::rawToReal(-8090770136ll),  Real::rawToReal(11344596906ll), Real::rawToReal(
                        -3864154488ll), Real::rawToReal(
                        773957209ll),  Real::rawToReal(-64902198ll),},
                {Real::rawToReal(-7803609967ll),  Real::rawToReal(10834526296ll), Real::rawToReal(
                        -3526875588ll), Real::rawToReal(
                        675547921ll),  Real::rawToReal(-54210315ll),},
                {Real::rawToReal(-7529882642ll),  Real::rawToReal(10369399487ll), Real::rawToReal(
                        -3232468908ll), Real::rawToReal(
                        593271691ll),  Real::rawToReal(-45643414ll),},
        };
        return r2 + ((((coeffSet[firstN][4] * x + coeffSet[firstN][3]) * x +
                       coeffSet[firstN][2]) * x + coeffSet[firstN][1]) * x +
                     coeffSet[firstN][0]);

    }

    static _REAL_CONSTEXPR Real log(const Real &x) noexcept {
        return log2(x) / log2(Real::E());
    }

    static _REAL_CONSTEXPR Real log10(const Real &x) noexcept {
        return log2(x) / log2(10_r);
    }

    static _REAL_CONSTEXPR Real log1p(const Real &x) noexcept {
        return log(1_r + x);
    }

#ifdef _MSC_VER
    static _REAL_CONSTEXPR Real sqrt(const Real& x) noexcept
    {

        assert(x >= 0_r);
        if (x == 0_r)
        {
            return x;
        }

        using namespace large_int;
        int128_t  tmp = x.mRaw;

        int128_t num = tmp << Cf;
        int128_t res = 0;
        int128_t gg = 1;

        int128_t ze = 0;
        int lbit = (int)((highestBit((unsigned long long)x.mRaw) + Cf) / 2 * 2);
        int128_t bit = gg << lbit;
        for (; bit != ze; bit = bit >> 2)
        {
            const int128_t val = res + bit;
            res = res >> 1;
            if (num >= val)
            {
                num -= val;
                res = res + bit;
            }
        }

        if (num > res)
        {
            res = res + 1;
        }

        Real r;
        r.mRaw = static_cast<long long>(res);
        return r;
    }
#else

    static _REAL_CONSTEXPR Real sqrt(const Real &x) noexcept {
        assert(x >= 0_r);
        if (x == 0_r) {
            return x;
        }

        int128_t num = int128_t{x.mRaw} << Cf;
        int128_t res = 0;

        int cbit = ((highestBit(x.mRaw) + Cf) / 2 * 2);
        for (int128_t bit = int128_t(1) << cbit; bit != 0; bit >>= 2) {
            const int128_t val = res + bit;
            res >>= 1;
            if (num >= val) {
                num -= val;
                res += bit;
            }
        }

        if (num > res) {
            res++;
        }

        Real r;
        r.mRaw = static_cast<data_t>(res);
        return r;
    }

#endif
private:
    static _REAL_CONSTEXPR Real doubleToReal(const double f) {
        Real r;

        r.mRaw = doubleToData(f);
        return r;
    }

    data_t mRaw = 0;
};

_REAL_CONSTEXPR Real operator "" _r(const char *v, size_t n) {
    Real a;
    a = Real::strToReal(v, n);
    return a;
}

_REAL_CONSTEXPR Real operator "" _r(unsigned long long v) {
    return Real((int) v);
}

#ifdef __GNUC__
#pragma GCC pop_options
#elif __clang__
#pragma CLANG pop_options
#elif _MSC_VER
#pragma optimize( "", on )
#endif

#endif //UNTITLED_REAL_H
#if _MSC_VER
#pragma warning( pop)
#endif

#pragma clang diagnostic pop