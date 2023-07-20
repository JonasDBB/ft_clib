#include <gtest/gtest.h>
#include <fstream>
#include <fcntl.h>
#include <cstdio>

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
    bzero(buf, 20);
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

    bzero(buf, 20);
    ft_sprintf(buf, "%s", "string");
    ASSERT_STREQ(buf, "string");

    bzero(buf, 20);
    ft_sprintf(buf, "%8s", "string");
    ASSERT_STREQ(buf, "  string");

    bzero(buf, 20);
    ft_sprintf(buf, "%-8s", "string");
    ASSERT_STREQ(buf, "string  ");

    bzero(buf, 20);
    ft_sprintf(buf, "%1s", "string");
    ASSERT_STREQ(buf, "string");

    bzero(buf, 20);
    ft_sprintf(buf, "%.2s", "string");
    ASSERT_STREQ(buf, "st");

    bzero(buf, 20);
    ft_sprintf(buf, "%5.2s", "string");
    ASSERT_STREQ(buf, "   st");

    bzero(buf, 20);
    ft_sprintf(buf, "%4.0s", "string");
    ASSERT_STREQ(buf, "    ");

    bzero(buf, 20);
    ft_sprintf(buf, "%5.8s", "string");
    ASSERT_STREQ(buf, "string");
}
