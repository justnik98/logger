//
// Created by justnik on 21.07.22.
//

#ifndef LOGGER_BUFFER_HPP
#define LOGGER_BUFFER_HPP

#include <array>
#include <string>

class Buffer {
private:
    std::array<char, 1024> buf{0};
    size_t size = 0;
public:
    template<typename T>
    Buffer &operator<<(T &value) {
        if constexpr (std::is_constructible_v<std::string_view, T>) {
            // noexcept if the conversion is noexcept
            *this << std::string_view{value};
        } else if constexpr (std::is_signed_v<T>) {
            using LongLong = long long;
            *this << LongLong{value};
        } else if constexpr (std::is_unsigned_v<T>) {
            using UnsignedLongLong = unsigned long long;
            *this << UnsignedLongLong{value};
        } else if constexpr (std::is_base_of_v<std::exception, T>) {
            *this << static_cast<const std::exception &>(value);
        } else {
            static_assert(!sizeof(T),
                          "Please implement logging for your type: "
                          "logging::Buffer& operator<<(logging::Buffer& lh, "
                          "const T& value)");
        }

        return *this;
    }

    Buffer &operator<<(char value) noexcept;

    Buffer &operator<<(std::string_view value) noexcept;

//    Buffer& operator<<(float value) noexcept;
//    Buffer& operator<<(double value) noexcept;
//    Buffer& operator<<(long double value) noexcept;
//    Buffer& operator<<(unsigned long long value) noexcept;
//    Buffer& operator<<(long long value) noexcept;
//    Buffer& operator<<(bool value) noexcept;
//    Buffer& operator<<(const std::exception& value) noexcept;
    friend std::ostream &operator<<(std::ostream &of, Buffer &b);
    void flush(){
        buf = std::array<char,1024>{0};
    }

};

inline std::ostream &operator<<(std::ostream &of, Buffer &b) {
    of << std::string_view(b.buf.data());;
    return of;
}

inline Buffer &Buffer::operator<<(char value) noexcept {
    buf[size++] = value;
    return *this;
}

inline Buffer &Buffer::operator<<(std::string_view value) noexcept {
    for (auto &&c: value) {
        buf[size++] = c;
    }
    return *this;
}


#endif //LOGGER_BUFFER_HPP
