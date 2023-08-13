#pragma once

#include "config.h"
#include "log.h"

#include <cassert>
#include <cstdint>

template<typename Func>
void set_vfunc(std::size_t address, Func func) {
    (*bit_cast<std::uint32_t *>(address)) = (bit_cast<std::uint32_t>(func));
}

template<typename Func>
void REDIRECT(std::ptrdiff_t addr, Func my_func) {
    *bit_cast<uint8_t *>(addr) = 0xE8; //CALL
    *bit_cast<uint32_t *>(
        bit_cast<uint8_t *>(addr + 1)) = (bit_cast<uint32_t>(my_func)) - addr - 5;
    //sp_log("Patched address %08X with %s", addr, #my_func);
}

template<typename Func>
void SET_JUMP(std::ptrdiff_t addr, Func my_func) {
    *bit_cast<uint8_t *>(addr) = 0xE9; //JUMP

    *bit_cast<uint32_t *>(bit_cast<uint8_t *>(addr + 1)) = (bit_cast<uint32_t>(my_func)) - addr - 5;

    *bit_cast<uint8_t *>(addr + 0x5) = 0xC3; //RET
};

template<typename Func, typename = typename std::enable_if_t<std::is_member_function_pointer_v<Func>>>
void *func_address(Func func) {
    auto result = reinterpret_cast<void *&>(func);

    return result;
}

#define FUNC_ADDRESS(address, func) [[maybe_unused]] void *address = func_address(func)

#ifdef NDEBUG
inline void error(const char *, ...) {}
#else

inline void error(const char *format, ...) {
    va_list args;
    va_start(args, format);

    vprintf(format, args);
    printf("\n");
    va_end(args);

    assert(0);
}
#endif
