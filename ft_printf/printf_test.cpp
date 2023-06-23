#include <gtest/gtest.h>
#include <fstream>
#include <fcntl.h>
#include <cstdio>

extern "C" {
#include "ft_clib.h"
#include "ft_printf.h"
}

#define BREAK ASSERT_TRUE(false)

constexpr auto tmp_filename = "/tmp/tmp.txt";

class output_redirect : public ::testing::Test {
protected:
    int _fd_file;
    FILE* _stream;

    void SetUp() override {
        _fd_file = open(tmp_filename, O_CREAT | O_RDWR, 0777);
        _stream = fdopen(_fd_file, "r+");
    }

    void TearDown() override {
        fclose(_stream);
        close(_fd_file);
        std::remove(tmp_filename);
        std::remove("/tmp/gtest_captured_stream*");
    }

    std::string stdout() {
        return {};
    }

    std::string stderr() {
        return {};
    }

    std::string tmpfile() {
        std::ifstream t(tmp_filename);
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }
};

TEST_F(output_redirect, fd_no_format) {
    ASSERT_EQ(_stream->_file, _fd_file);
    ASSERT_EQ(fprintf(_stream, "hoi doei\n"), 9);
    system("echo HIER && cat /tmp/tmp.txt && echo DONE");
    ASSERT_EQ(tmpfile(), "hoi doei\n");
}

TEST(printf, string_no_format) {
    char buf[20];
    ft_bzero(buf, 20);
    ASSERT_EQ(ft_sprintf(buf, "hoi"), 3);
    ASSERT_STREQ(buf, "hoi");

    ASSERT_EQ(ft_snprintf(buf, 3, "1234567890"), 10);
    ASSERT_STREQ(buf, "12");

    ASSERT_EQ(ft_snprintf(buf, 6, "123456789 123456789 1234567890"), 30);
    ASSERT_STREQ(buf, "12345");
}