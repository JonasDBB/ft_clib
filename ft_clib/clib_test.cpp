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
    ASSERT_EQ(ft_strlen(
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"),
              100);
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
    for (const char& c: arr) {
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
    for (const char& c: arr) {
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

TEST(clib, strchr) {
    char s[6] = "hello";
    ASSERT_EQ(ft_strchr(s, 'l'), s + 2);
    ASSERT_EQ(ft_strchr(s, 'k'), nullptr);
    ASSERT_EQ(ft_strchr(s, 0), s + 5);
}

TEST(clib, strrchr) {
    char s[6] = "hello";
    ASSERT_EQ(ft_strrchr(s, 'l'), s + 3);
    ASSERT_EQ(ft_strrchr(s, 'k'), nullptr);
    ASSERT_EQ(ft_strrchr(s, 0), s + 5);
}

TEST(clib, memcmp) {
    char s1[4] = "abc";
    char s2[4] = "abd";
    char s3[4] = "aba";
    char s4[4] = "aba";
    ASSERT_EQ(ft_memcmp(s3, s4, 3), 0);
    ASSERT_LT(ft_memcmp(s1, s2, 3), 0);
    ASSERT_GT(ft_memcmp(s1, s3, 3), 0);
    ft_bzero(s1, 3);
    ft_bzero(s2, 3);
    s1[1] = 'a';
    s2[1] = 'a';
    ASSERT_EQ(ft_memcmp(s1, s2, 3), 0);
}

TEST(clib, strcmp) {
    char s1[4] = "abc";
    char s2[4] = "abd";
    char s3[4] = "aba";
    char s4[4] = "aba";
    char s5[5] = "abcd";
    char s6[1] = "";
    ASSERT_EQ(ft_strcmp(s3, s4), 0);
    ASSERT_LT(ft_strcmp(s1, s2), 0);
    ASSERT_GT(ft_strcmp(s1, s3), 0);
    ASSERT_GT(ft_strcmp(s5, s1), 0);
    ASSERT_LT(ft_strcmp(s1, s5), 0);
    ASSERT_GT(ft_strcmp(s1, s6), 0);
    ASSERT_LT(ft_strcmp(s6, s1), 0);
}

TEST(clib, strncmp) {
    char s1[4] = "abc";
    char s2[4] = "abd";
    char s3[4] = "aba";
    char s4[4] = "aba";
    char s5[5] = "abcd";
    char s6[1] = "";
    ASSERT_EQ(ft_strncmp(s3, s4, 0), 0);
    ASSERT_EQ(ft_strncmp(s3, s4, 3), 0);
    ASSERT_EQ(ft_strncmp(s3, s4, 10), 0);
    ASSERT_EQ(ft_strncmp(s3, s4, 1), 0);
    ASSERT_LT(ft_strncmp(s1, s2, 3), 0);
    ASSERT_LT(ft_strncmp(s1, s2, 10), 0);
    ASSERT_GT(ft_strncmp(s1, s3, 3), 0);
    ASSERT_GT(ft_strncmp(s5, s1, 3), 0);
    ASSERT_LT(ft_strncmp(s1, s5, 3), 0);
    ASSERT_GT(ft_strncmp(s1, s6, 3), 0);
    ASSERT_LT(ft_strncmp(s6, s1, 3), 0);
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

TEST(clib, toupper) {
    ASSERT_EQ(ft_toupper('a'), 'A');
    ASSERT_EQ(ft_toupper('z'), 'Z');
    for (unsigned char c = 0; c < 128; ++c) {
        if (c >= 'a' && c <= 'z') {
            ASSERT_EQ(ft_toupper(c), (char)(c + ('A' - 'a')));
        } else {
            ASSERT_EQ(ft_toupper(c), c);
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
    char* p = nullptr;
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
    ASSERT_EQ(ft_strtol("9223372036854775807", nullptr, 0), LONG_MAX);
    ASSERT_EQ(errno, 0);
    ASSERT_EQ(ft_strtol("9223372036854775808", nullptr, 0), LONG_MAX);
    ASSERT_EQ(errno, ERANGE);
    errno = 0;
    ASSERT_EQ(ft_strtol("-9223372036854775808", nullptr, 0), LONG_MIN);
    ASSERT_EQ(errno, 0);
    ASSERT_EQ(ft_strtol("-9223372036854775809", nullptr, 0), LONG_MIN);
    ASSERT_EQ(errno, ERANGE);
    errno = 0;

    // endptr tests
    char* endptr;
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

TEST(clib, lltoa_base) {
    char buf[21];
    ASSERT_STREQ(ft_lltoa_base(1, buf, 10), "1");
    ASSERT_STREQ(ft_lltoa_base(-1, buf, 10), "-1");
    ASSERT_STREQ(ft_lltoa_base(1234, buf, 10), "1234");
    ASSERT_STREQ(ft_lltoa_base(-4321, buf, 10), "-4321");
    ASSERT_STREQ(ft_lltoa_base(0, buf, 10), "0");
    ASSERT_STREQ(ft_lltoa_base(LONG_LONG_MIN, buf, 10), "-9223372036854775808");
    ASSERT_STREQ(ft_lltoa_base(LONG_LONG_MAX, buf, 10), "9223372036854775807");

    ASSERT_EQ(ft_lltoa_base(1234, buf, 1), nullptr);
    ASSERT_EQ(ft_lltoa_base(1234, buf, 37), nullptr);
    ASSERT_EQ(ft_lltoa_base(1234, nullptr, 10), nullptr);

    ASSERT_STREQ(ft_lltoa_base(0x76a53, buf, 16), "76a53");
    ASSERT_STREQ(ft_lltoa_base(07653, buf, 8), "7653");
    ASSERT_STREQ(ft_lltoa_base(60466175, buf, 36), "zzzzz");
    ASSERT_STREQ(ft_lltoa_base(3656158440062975, buf, 36), "zzzzzzzzzz");
}

TEST(clib, ulltoa_base) {
    char buf[21];
    ASSERT_STREQ(ft_ulltoa_base(1, buf, 10), "1");
    ASSERT_STREQ(ft_ulltoa_base(-1, buf, 10), "18446744073709551615");
    ASSERT_STREQ(ft_ulltoa_base(1234, buf, 10), "1234");
    ASSERT_STREQ(ft_ulltoa_base(-4321, buf, 10), "18446744073709547295");
    ASSERT_STREQ(ft_ulltoa_base(0, buf, 10), "0");
    ASSERT_STREQ(ft_ulltoa_base(ULONG_LONG_MAX, buf, 10), "18446744073709551615");

    ASSERT_EQ(ft_ulltoa_base(1234, buf, 1), nullptr);
    ASSERT_EQ(ft_ulltoa_base(1234, buf, 37), nullptr);
    ASSERT_EQ(ft_ulltoa_base(1234, nullptr, 10), nullptr);

    ASSERT_STREQ(ft_ulltoa_base(0x76a53, buf, 16), "76a53");
    ASSERT_STREQ(ft_ulltoa_base(07653, buf, 8), "7653");
    ASSERT_STREQ(ft_ulltoa_base(60466175, buf, 36), "zzzzz");
    ASSERT_STREQ(ft_ulltoa_base(3656158440062975, buf, 36), "zzzzzzzzzz");
}
