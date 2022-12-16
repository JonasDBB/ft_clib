#include <gtest/gtest.h>
#include <cerrno>
#include <climits>
extern "C" {
#include "ft_clib.h"
}

TEST(clib, errnames) {
    ASSERT_STREQ(errno_name(EPERM), "EPERM");
    ASSERT_STREQ(errno_name(ENOENT), "ENOENT");
    ASSERT_STREQ(errno_name(ESRCH), "ESRCH");
    ASSERT_STREQ(errno_name(EINTR), "EINTR");
    ASSERT_STREQ(errno_name(EIO), "EIO");
    ASSERT_STREQ(errno_name(ENXIO), "ENXIO");
    ASSERT_STREQ(errno_name(E2BIG), "E2BIG");
    ASSERT_STREQ(errno_name(ECHILD), "ECHILD");
    ASSERT_STREQ(errno_name(EAGAIN), "EAGAIN");
    ASSERT_STREQ(errno_name(ENOMEM), "ENOMEM");
    ASSERT_STREQ(errno_name(EACCES), "EACCES");
    ASSERT_STREQ(errno_name(EFAULT), "EFAULT");
    ASSERT_STREQ(errno_name(ENOTBLK), "ENOTBLK");
    ASSERT_STREQ(errno_name(EBUSY), "EBUSY");
    ASSERT_STREQ(errno_name(EEXIST), "EEXIST");
    ASSERT_STREQ(errno_name(EXDEV), "EXDEV");
    ASSERT_STREQ(errno_name(ENODEV), "ENODEV");
    ASSERT_STREQ(errno_name(ENOTDIR), "ENOTDIR");
    ASSERT_STREQ(errno_name(EISDIR), "EISDIR");
    ASSERT_STREQ(errno_name(EINVAL), "EINVAL");
    ASSERT_STREQ(errno_name(ENFILE), "ENFILE");
    ASSERT_STREQ(errno_name(EMFILE), "EMFILE");
    ASSERT_STREQ(errno_name(ENOTTY), "ENOTTY");
    ASSERT_STREQ(errno_name(ETXTBSY), "ETXTBSY");
    ASSERT_STREQ(errno_name(EFBIG), "EFBIG");
    ASSERT_STREQ(errno_name(ENOSPC), "ENOSPC");
    ASSERT_STREQ(errno_name(ESPIPE), "ESPIPE");
    ASSERT_STREQ(errno_name(EROFS), "EROFS");
    ASSERT_STREQ(errno_name(EMLINK), "EMLINK");
    ASSERT_STREQ(errno_name(EPIPE), "EPIPE");
    ASSERT_STREQ(errno_name(EDOM), "EDOM");
    ASSERT_STREQ(errno_name(ERANGE), "ERANGE");
}

TEST(clib, strlen) {
    ASSERT_EQ(ft_strlen(nullptr), 0);
    ASSERT_EQ(ft_strlen("abc"), 3);
    ASSERT_EQ(ft_strlen("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"), 100);
    char str[4];
    str[0] = 'a';
    str[1] = 'b';
    str[2] = 0;
    str[3] = 0;
    ASSERT_EQ(ft_strlen(str), 2);
}

TEST(clib, memset) {
    char arr[100];

    ASSERT_EQ(ft_memset(nullptr, 50, 50), nullptr);

    ASSERT_EQ(ft_memset(arr, 0, 100), arr);
    for (const char& c : arr) {
        ASSERT_EQ(c, 0);
    }

    ASSERT_EQ(ft_memset(arr, 'a', 10), arr);
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(arr[i], 'a');
    }
    ASSERT_EQ(arr[10], 0);

    ASSERT_EQ(ft_memset(arr + 10, 'b', 10), arr + 10);
    for (int i = 10; i < 20; ++i) {
        ASSERT_EQ(arr[i], 'b');
    }
    ASSERT_EQ(arr[9], 'a');
    ASSERT_EQ(arr[20], 0);
}

TEST(clib, bzero) {
    char arr[100];

    ft_bzero(arr, 100);
    for (const char& c : arr) {
        ASSERT_EQ(c, 0);
    }

    ft_memset(arr, 'a', 100);
    ft_bzero(arr + 10, 10);
    ASSERT_EQ(arr[9], 'a');
    for (int i = 10; i < 20; ++i) {
        ASSERT_EQ(arr[i], 0);
    }
    ASSERT_EQ(arr[20], 'a');
}

TEST(clib, memcpy) {
    char arr[1024];

    ft_bzero(arr, 1024);
    ft_memset(arr, 'j', 20);

    ft_memcpy(arr + 100, arr, 5);
    ASSERT_EQ(arr[99], 0);
    ASSERT_EQ(arr[100], 'j');
    ASSERT_EQ(arr[104], 'j');
    ASSERT_EQ(arr[105], 0);

    ft_memcpy(arr + 200, arr + 99, 10);
    ASSERT_EQ(arr[200], 0);
    ASSERT_EQ(arr[201], 'j');
    ASSERT_EQ(arr[205], 'j');
    ASSERT_EQ(arr[206], 0);
}

TEST(clib, strstr) {
    char s[6] = "hello";
    ASSERT_EQ(ft_strchr(s, 'l'), s + 2);
    ASSERT_EQ(ft_strchr(s, 'k'), nullptr);
    ASSERT_EQ(ft_strchr(s, 0), s + 5);
}

TEST(clib, strrstr) {
    char s[6] = "hello";
    ASSERT_EQ(ft_strrchr(s, 'l'), s + 3);
    ASSERT_EQ(ft_strrchr(s, 'k'), nullptr);
    ASSERT_EQ(ft_strrchr(s, 0), s + 5);
}

TEST(clib, isnum) {
    for (unsigned char c = 0; c < 128; ++c) {
        if (c >= '0' && c <= '9') {
            ASSERT_TRUE(ft_isnum(c));
        } else {
            ASSERT_FALSE(ft_isnum(c));
        }
    }
}

TEST(clib, isalpha) {
    for (unsigned char c = 0; c < 128; ++c) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            ASSERT_TRUE(ft_isalpha(c));
        } else {
            ASSERT_FALSE(ft_isalpha(c));
        }
    }
}

TEST(clib, tolower) {
    ASSERT_EQ(ft_tolower('A'), 'a');
    ASSERT_EQ(ft_tolower('Z'), 'z');
    for (unsigned char c = 0; c < 128; ++c) {
        if (c >= 'A' && c <= 'Z') {
            ASSERT_EQ(ft_tolower(c), (char)(c - ('A' - 'a')));
        } else {
            ASSERT_EQ(ft_tolower(c), c);
        }
    }
}

TEST(clib, isspace) {
    for (unsigned char c = 0; c < 128; ++c) {
        if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ') {
            ASSERT_TRUE(ft_isspace(c));
        } else {
            ASSERT_FALSE(ft_isspace(c));
        }
    }
}

TEST(clib, strtol) {
    errno = 0;
    // tests and base 10
    ASSERT_EQ(ft_strtol("1234", nullptr, 10), 1234);
    ASSERT_EQ(ft_strtol("+1234", nullptr, 10), 1234);
    ASSERT_EQ(ft_strtol("-1234", nullptr, 10), -1234);
    ASSERT_EQ(errno, 0);

    // no conversions
    errno = 0;
    ASSERT_EQ(ft_strtol("++1234", nullptr, 10), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    ASSERT_EQ(ft_strtol("--1234", nullptr, 10), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    ASSERT_EQ(ft_strtol("abc", nullptr, 10), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    ASSERT_EQ(ft_strtol("-abc", nullptr, 10), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    ASSERT_EQ(ft_strtol("+abc", nullptr, 10), 0);
    char *p = nullptr;
    ASSERT_EQ(ft_strtol(p, nullptr, 10), 0); // to pass NULL while first arg requiring nonnull
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    ASSERT_EQ(ft_strtol("-", nullptr, 10), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    ASSERT_EQ(ft_strtol("+", nullptr, 10), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    ASSERT_EQ(ft_strtol("", nullptr, 10), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;

    // part conversion
    ASSERT_EQ(ft_strtol("123abc4", nullptr, 10), 123);
    ASSERT_EQ(ft_strtol("123+4", nullptr, 10), 123);

    // tests base 16
    ASSERT_EQ(ft_strtol("1234", nullptr, 16), 0x1234);
    ASSERT_EQ(ft_strtol("0x1234", nullptr, 16), 0x1234);
    ASSERT_EQ(ft_strtol("+0x1234", nullptr, 16), 0x1234);
    ASSERT_EQ(ft_strtol("+1234", nullptr, 16), 0x1234);
    ASSERT_EQ(ft_strtol("-0x1234", nullptr, 16), -0x1234);
    ASSERT_EQ(ft_strtol("-1234", nullptr, 16), -0x1234);
    ASSERT_EQ(ft_strtol("0x120x1234", nullptr, 16), 0x120);
    ASSERT_EQ(ft_strtol("0x120x1234", nullptr, 16), 0x120);
    ASSERT_EQ(errno, 0); // check if errno still 0
    ASSERT_EQ(ft_strtol("0xx1234", nullptr, 16), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;

    ASSERT_EQ(ft_strtol("aBcD1234", nullptr, 16), 0xABCD1234);
    ASSERT_EQ(ft_strtol("abcdef", nullptr, 16), 0xabcdef);
    ASSERT_EQ(ft_strtol("abcgdef", nullptr, 16), 0xabc); // stop at g which is not in base

    // tests base 8
    ASSERT_NE(ft_strtol("1234", nullptr, 8), 1234); // not equal to 1234 base 10
    ASSERT_EQ(ft_strtol("1234", nullptr, 8), 01234);
    ASSERT_EQ(ft_strtol("01234", nullptr, 8), 01234);
    ASSERT_EQ(ft_strtol("012347", nullptr, 8), 012347);
    ASSERT_EQ(ft_strtol("0123847", nullptr, 8), 0123); // stop at 8 which is not in base

    // check if errno still 0
    ASSERT_EQ(errno, 0);

    // tests with wrong bases
    ASSERT_EQ(ft_strtol("1234", nullptr, 1), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    ASSERT_EQ(ft_strtol("1234", nullptr, -1), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    ASSERT_EQ(ft_strtol("1234", nullptr, 37), 0);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;

    // test base 36
    ASSERT_EQ(ft_strtol("jonas", nullptr, 36), 33062644);
    ASSERT_EQ(ft_strtol("aA34Zz", nullptr, 36), 621604367);
    ASSERT_EQ(ft_strtol("aA34*Zz", nullptr, 36), 479632);

    // tests special base 0
    ASSERT_NE(ft_strtol("01234", nullptr, 0), 1234); // not equal to 1234 base 10
    ASSERT_EQ(ft_strtol("01234", nullptr, 0), 01234);
    ASSERT_EQ(ft_strtol("012834", nullptr, 0), 012); // stop at 8
    ASSERT_EQ(ft_strtol("1234", nullptr, 0), 1234);
    ASSERT_EQ(ft_strtol("0x1234", nullptr, 0), 0x1234);
    ASSERT_EQ(ft_strtol("0x12fg34", nullptr, 0), 0x12f); // stop at g

    // limit tests
    ASSERT_EQ(errno, 0);
    ASSERT_EQ(ft_strtol("zzzzzzzzzzzzz", nullptr, 36), LONG_MAX);
    ASSERT_EQ(errno, ERANGE);
    errno = 0;
    ASSERT_EQ(ft_strtol("-zzzzzzzzzzzzz", nullptr, 36), LONG_MIN);
    ASSERT_EQ(errno, ERANGE);
    errno = 0;

    // endptr tests
    char *endptr;
    std::string s = "1234";
    ft_strtol(s.c_str(), &endptr, 10);
    ASSERT_EQ(endptr, s.c_str() + 4);

    s = "12a34";
    ft_strtol(s.c_str(), &endptr, 10);
    ASSERT_EQ(endptr, s.c_str() + 2);

    s = "a1234";
    ft_strtol(s.c_str(), &endptr, 10);
    ASSERT_EQ(endptr, s.c_str());
}

// TODO: write test for ft_write_nr_base
