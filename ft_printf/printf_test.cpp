#include <gtest/gtest.h>
#include <fstream>
#include <fcntl.h>
#include <climits>

extern "C" {
#include "ft_clib.h"
#include "ft_printf.h"
}

constexpr auto tmp_out_filename = "/tmp/tmp_out.txt";
constexpr auto tmp_err_filename = "/tmp/tmp_err.txt";
constexpr auto tmp1_filename = "/tmp/tmp1.txt";
constexpr auto tmp2_filename = "/tmp/tmp2.txt";

class output_redirect : public ::testing::Test {
protected:
    int _orig_out{-1};
    int _orig_err{-1};
    int _tmp_out_file{-1};
    int _tmp_err_file{-1};
    int _file1{-1};
    FILE* _file2{};

    void SetUp() override {
        _tmp_out_file = open(tmp_out_filename, O_CREAT | O_RDWR, 0777);
        _tmp_err_file = open(tmp_err_filename, O_CREAT | O_RDWR, 0777);
        _file1 = open(tmp1_filename, O_CREAT | O_RDWR, 0777);
        _file2 = fopen(tmp2_filename, "w+");
        if (_tmp_out_file == -1 || _tmp_err_file == -1 || _file1 == -1 || _file2 == nullptr) {
            ERROR("files didn't open correctly");
            abort();
        }
        _orig_out = dup(STDOUT_FILENO);
        _orig_err = dup(STDERR_FILENO);
        dup2(_tmp_out_file, STDOUT_FILENO);
        dup2(_tmp_err_file, STDERR_FILENO);
    }

    void TearDown() override {
        dup2(_orig_out, STDOUT_FILENO);
        dup2(_orig_err, STDERR_FILENO);
        close(_orig_out);
        close(_orig_err);
        close(_tmp_out_file);
        close(_tmp_err_file);
        close(_file1);
        fclose(_file2);
        std::remove(tmp_out_filename);
        std::remove(tmp_err_filename);
        std::remove(tmp1_filename);
        std::remove(tmp2_filename);
    }

    static std::string file_content(const std::string& filename) {
        std::ifstream ifs(filename);
        std::stringstream ss;
        ss << ifs.rdbuf();
        return ss.str();
    }

    static std::string stdout_content() {
        return file_content(tmp_out_filename);
    }

    static std::string stderr_content() {
        return file_content(tmp_err_filename);
    }

    static std::string file1_content() {
        return file_content(tmp1_filename);

    }

    static std::string file2_content() {
        return file_content(tmp2_filename);

    }

    void reset_file1() {
        close(_file1);
        std::remove(tmp1_filename);
        _file1 = open(tmp1_filename, O_CREAT | O_RDWR, 0777);
        if (_file1 == -1) {
            ERROR("files didn't open correctly");
            abort();
        }
    }
};

TEST_F(output_redirect, fd_no_format) {
    ft_printf("test");
    ASSERT_EQ(stdout_content(), "test");

    ft_dprintf(_file1, "asdf");
    ASSERT_EQ(file1_content(), "asdf");

    ft_fprintf(_file2, "1234");
    ASSERT_EQ(file2_content(), "1234");
}

TEST(printf, string_no_format_with_returns) {
    char buf[20];
    ft_sprintf(buf, "hoi");
    ASSERT_STREQ(buf, "hoi");

    ASSERT_EQ(ft_snprintf(buf, 3, "1234567890"), 10);
    ASSERT_STREQ(buf, "12");

    ASSERT_EQ(ft_snprintf(buf, 6, "123456789 123456789 1234567890"), 30);
    ASSERT_STREQ(buf, "12345");
}

TEST_F(output_redirect, return_values) {
    ASSERT_EQ(ft_printf("test"), 4);

    ASSERT_EQ(ft_dprintf(_file1, "asdfg"), 5);

    ASSERT_EQ(ft_fprintf(_file2, "123"), 3);

    ASSERT_EQ(ft_dprintf(-1, "abc"), -1);

    FILE* f{};
    ASSERT_EQ(ft_fprintf(f, "123"), -1);
}

TEST_F(output_redirect, char) {
    ft_dprintf(_file1, "%c", 'a');
    ASSERT_EQ(file1_content(), "a");
    reset_file1();

    ft_dprintf(_file1, "%c", '\n');
    ASSERT_EQ(file1_content(), "\n");
    reset_file1();

    ft_dprintf(_file1, "%c", 42);
    ASSERT_EQ(file1_content(), "*");
    reset_file1();

    ft_dprintf(_file1, "%%");
    ASSERT_EQ(file1_content(), "%");
}

TEST(printf, string) {
    char buf[20];
    char* nulp = nullptr;

    ft_sprintf(buf, "%s", "string");
    ASSERT_STREQ(buf, "string");

    ft_sprintf(buf, "%8s", "string");
    ASSERT_STREQ(buf, "  string");

    ft_sprintf(buf, "%-8s", "string");
    ASSERT_STREQ(buf, "string  ");

    ft_sprintf(buf, "%1s", "string");
    ASSERT_STREQ(buf, "string");

    ft_sprintf(buf, "%.2s", "string");
    ASSERT_STREQ(buf, "st");

    ft_sprintf(buf, "%5.2s", "string");
    ASSERT_STREQ(buf, "   st");

    ft_sprintf(buf, "%4.0s", "string");
    ASSERT_STREQ(buf, "    ");

    ft_sprintf(buf, "%5.8s", "string");
    ASSERT_STREQ(buf, "string");

    ft_sprintf(buf, "%s", nulp);
    ASSERT_STREQ(buf, "(null)");

    ft_sprintf(buf, "%.2s", nulp);
    ASSERT_STREQ(buf, "(n");

    ft_sprintf(buf, "%-7s", nulp);
    ASSERT_STREQ(buf, "(null) ");

    ft_snprintf(buf, 3, "%s", nulp);
    ASSERT_STREQ(buf, "(n");
}

TEST(printf, pointer) {
    char buf[30];
    char control[30];
    void* p = nullptr;

    ft_sprintf(buf, "%p", &p);
    ft_sprintf(control, "%p", &p);
    ASSERT_STREQ(buf, control);

    ft_sprintf(buf, "%p", p);
    ASSERT_STREQ(buf, "0x0");

    ft_sprintf(buf, "%20p", &p);
    ft_sprintf(control, "%20p", &p);
    ASSERT_STREQ(buf, control);

    ft_sprintf(buf, "%-20p", &p);
    ft_sprintf(control, "%-20p", &p);
    ASSERT_STREQ(buf, control);
}

TEST(printf, signed_decimal) {
    char buf[30];

    ft_sprintf(buf, "%i", 5);
    ASSERT_STREQ(buf, "5");

    ft_sprintf(buf, "%d", -98);
    ASSERT_STREQ(buf, "-98");

    ft_sprintf(buf, "%d", INT_MAX);
    ASSERT_STREQ(buf, "2147483647");

    ft_sprintf(buf, "%lld", LONG_LONG_MIN);
    ASSERT_STREQ(buf, "-9223372036854775808");

    // overflow short short (char)
    ft_sprintf(buf, "%hhd", 130);
    ASSERT_STREQ(buf, "-126");

    ft_sprintf(buf, "a% d", 123);
    ASSERT_STREQ(buf, "a 123");

    ft_sprintf(buf, "a% d", -123);
    ASSERT_STREQ(buf, "a-123");

    ft_sprintf(buf, "%+d", 123);
    ASSERT_STREQ(buf, "+123");

    ft_sprintf(buf, "%+d", -123);
    ASSERT_STREQ(buf, "-123");

    ft_sprintf(buf, "a% +d", 123);
    ASSERT_STREQ(buf, "a+123");

    ft_sprintf(buf, "%05d", 123);
    ASSERT_STREQ(buf, "00123");

    ft_sprintf(buf, "%-5d", 123);
    ASSERT_STREQ(buf, "123  ");

    ft_sprintf(buf, "%-05d", 123);
    ASSERT_STREQ(buf, "123  ");

    ft_sprintf(buf, "%.6d", 123);
    ASSERT_STREQ(buf, "000123");

    ft_sprintf(buf, "%10.5d", 123);
    ASSERT_STREQ(buf, "     00123");

    ft_sprintf(buf, "%-10.5d", 123);
    ASSERT_STREQ(buf, "00123     ");

    ft_sprintf(buf, "%10.5d", -123);
    ASSERT_STREQ(buf, "    -00123");

    ft_sprintf(buf, "%-10.5d", -123);
    ASSERT_STREQ(buf, "-00123    ");

    ft_sprintf(buf, "%-+10.5d", 123);
    ASSERT_STREQ(buf, "+00123    ");

    ft_sprintf(buf, "%-+10.5d", 123);
    ASSERT_STREQ(buf, "+00123    ");

    ft_sprintf(buf, "%*.*d", 10, 5, 123);
    ASSERT_STREQ(buf, "     00123");
}

TEST(printf, unsigned_decimal) {
    char buf[30];

    ft_sprintf(buf, "%u", 5);
    ASSERT_STREQ(buf, "5");

    ft_sprintf(buf, "%u", UINT_MAX);
    ASSERT_STREQ(buf, "4294967295");

    ft_sprintf(buf, "%llu", ULONG_LONG_MAX);
    ASSERT_STREQ(buf, "18446744073709551615");

    // overflow short short (char)
    ft_sprintf(buf, "%hhu", 257);
    ASSERT_STREQ(buf, "1");

    ft_sprintf(buf, "a% u", 123);
    ASSERT_STREQ(buf, "a123");

    ft_sprintf(buf, "%+u", 123);
    ASSERT_STREQ(buf, "123");

    ft_sprintf(buf, "%05u", 123);
    ASSERT_STREQ(buf, "00123");

    ft_sprintf(buf, "%-5u", 123);
    ASSERT_STREQ(buf, "123  ");

    ft_sprintf(buf, "%-05u", 123);
    ASSERT_STREQ(buf, "123  ");

    ft_sprintf(buf, "%.6u", 123);
    ASSERT_STREQ(buf, "000123");

    ft_sprintf(buf, "%10.5u", 123);
    ASSERT_STREQ(buf, "     00123");

    ft_sprintf(buf, "%-10.5u", 123);
    ASSERT_STREQ(buf, "00123     ");

    ft_sprintf(buf, "%-10.5u", 123);
    ASSERT_STREQ(buf, "00123     ");

    ft_sprintf(buf, "%zu", SIZE_MAX);
    ASSERT_STREQ(buf, "18446744073709551615");
}

TEST(printf, hex_lower) {
    char buf[30];

    ft_sprintf(buf, "%x", 5);
    ASSERT_STREQ(buf, "5");

    ft_sprintf(buf, "%x", 0xa5);
    ASSERT_STREQ(buf, "a5");

    ft_sprintf(buf, "%#x", 0xabcdef);
    ASSERT_STREQ(buf, "0xabcdef");

    ft_sprintf(buf, "%#x", 5);
    ASSERT_STREQ(buf, "0x5");

    ft_sprintf(buf, "%x", UINT_MAX);
    ASSERT_STREQ(buf, "ffffffff");

    ft_sprintf(buf, "%10x", 0xabc12);
    ASSERT_STREQ(buf, "     abc12");

    ft_sprintf(buf, "%010x", 0xabc12);
    ASSERT_STREQ(buf, "00000abc12");

    ft_sprintf(buf, "%0#10x", 0xabc12);
    ASSERT_STREQ(buf, "0x000abc12");

    ft_sprintf(buf, "%#10.7x", 0xabc12);
    ASSERT_STREQ(buf, " 0x00abc12");

    ft_sprintf(buf, "%#-10x", 0xabc12);
    ASSERT_STREQ(buf, "0xabc12   ");

    ft_sprintf(buf, "%#-10.7x", 0xabc12);
    ASSERT_STREQ(buf, "0x00abc12 ");

    ft_sprintf(buf, "%#x", 0xabc12);
    ASSERT_STREQ(buf, "0xabc12");
}
TEST(printf, hex_upper) {
    char buf[30];

    ft_sprintf(buf, "%X", 5);
    ASSERT_STREQ(buf, "5");

    ft_sprintf(buf, "%X", 0xa5);
    ASSERT_STREQ(buf, "A5");

    ft_sprintf(buf, "%#X", 0xabcdef);
    ASSERT_STREQ(buf, "0XABCDEF");

    ft_sprintf(buf, "%#X", 5);
    ASSERT_STREQ(buf, "0X5");

    ft_sprintf(buf, "%X", UINT_MAX);
    ASSERT_STREQ(buf, "FFFFFFFF");

    ft_sprintf(buf, "%10X", 0xabc12);
    ASSERT_STREQ(buf, "     ABC12");

    ft_sprintf(buf, "%010X", 0xabc12);
    ASSERT_STREQ(buf, "00000ABC12");

    ft_sprintf(buf, "%0#10X", 0xabc12);
    ASSERT_STREQ(buf, "0X000ABC12");

    ft_sprintf(buf, "%#10.7X", 0xabc12);
    ASSERT_STREQ(buf, " 0X00ABC12");

    ft_sprintf(buf, "%#-10X", 0xabc12);
    ASSERT_STREQ(buf, "0XABC12   ");

    ft_sprintf(buf, "%#-10.7X", 0xabc12);
    ASSERT_STREQ(buf, "0X00ABC12 ");

    ft_sprintf(buf, "%#X", 0xabc12);
    ASSERT_STREQ(buf, "0XABC12");
}

TEST(printf, octal) {
    char buf[30];

    ft_sprintf(buf, "%o", 5);
    ASSERT_STREQ(buf, "5");

    ft_sprintf(buf, "%o", 10);
    ASSERT_STREQ(buf, "12");

    ft_sprintf(buf, "%o", 010);
    ASSERT_STREQ(buf, "10");

    ft_sprintf(buf, "%o", 06452);
    ASSERT_STREQ(buf, "6452");

    ft_sprintf(buf, "%#o", 5);
    ASSERT_STREQ(buf, "05");

    ft_sprintf(buf, "%#8o", 0123);
    ASSERT_STREQ(buf, "    0123");

    ft_sprintf(buf, "%#08o", 0123);
    ASSERT_STREQ(buf, "00000123");

    ft_sprintf(buf, "%#-8o", 0123);
    ASSERT_STREQ(buf, "0123    ");

    ft_sprintf(buf, "%#-8.5o", 0123);
    ASSERT_STREQ(buf, "00123   ");

    ft_sprintf(buf, "%#-8.o", 0123);
    ASSERT_STREQ(buf, "0123    ");
}

TEST(printf, zeros) {
    char buf[30];

    ft_sprintf(buf, "%d", 0);
    ASSERT_STREQ(buf, "0");

    ft_sprintf(buf, "%3d", 0);
    ASSERT_STREQ(buf, "  0");

    ft_sprintf(buf, "%.0d", 0);
    ASSERT_STREQ(buf, "");

    ft_sprintf(buf, "%2.0d", 0);
    ASSERT_STREQ(buf, "  ");

    ft_sprintf(buf, "%o", 0);
    ASSERT_STREQ(buf, "0");

    ft_sprintf(buf, "%3o", 0);
    ASSERT_STREQ(buf, "  0");

    ft_sprintf(buf, "%.0o", 0);
    ASSERT_STREQ(buf, "");

    ft_sprintf(buf, "%#o", 0);
    ASSERT_STREQ(buf, "0");

    ft_sprintf(buf, "%#.0o", 0);
    ASSERT_STREQ(buf, "0");

    ft_sprintf(buf, "%x", 0);
    ASSERT_STREQ(buf, "0");

    ft_sprintf(buf, "%.0x", 0);
    ASSERT_STREQ(buf, "");

    ft_sprintf(buf, "%#x", 0);
    ASSERT_STREQ(buf, "0");

    ft_sprintf(buf, "%#.0x", 0);
    ASSERT_STREQ(buf, "");
}
