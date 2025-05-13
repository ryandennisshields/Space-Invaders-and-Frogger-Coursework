#pragma once

struct ScreenBuffer {
public:
    ScreenBuffer() {};

    ScreenBuffer(int x, int y) : row(x), col(y) {
        m_buffer = new char* [row];
        for (int i = 0; i < row; ++i) {
            m_buffer[i] = new char[col];
        }
    };

    ~ScreenBuffer() {
        for (int i = 0; i < row; ++i) {
            delete[] m_buffer[i];
        }
        delete[] m_buffer;
    }

    ScreenBuffer(ScreenBuffer&& other) noexcept
        : row(other.row), col(other.col), m_buffer(other.m_buffer)
    {
        other.row = 0;
        other.col = 0;
        other.m_buffer = nullptr;
    }

    ScreenBuffer& operator=(ScreenBuffer&& other) noexcept
    {
        if (this != &other) {
            for (int i = 0; i < row; ++i) {
                delete[] m_buffer[i];
            }
            delete[] m_buffer;

            row = other.row;
            col = other.col;
            m_buffer = other.m_buffer;

            other.row = 0;
            other.col = 0;
            other.m_buffer = nullptr;
        }
        return *this;
    }

    ScreenBuffer(const ScreenBuffer& other) : row(other.row), col(other.col)
    {
        m_buffer = new char* [row];
        for (int i = 0; i < row; ++i) {
            m_buffer[i] = new char[col];
        }

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                m_buffer[i][j] = other.m_buffer[i][j];
            }
        }
    }

    ScreenBuffer& operator=(const ScreenBuffer& other)
    {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < row; ++i) {
            delete[] m_buffer[i];
        }
        delete[] m_buffer;

        row = other.row;
        col = other.col;
        m_buffer = new char* [row];
        for (int i = 0; i < row; ++i) {
            m_buffer[i] = new char[col];
        }

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                m_buffer[i][j] = other.m_buffer[i][j];
            }
        }
        return *this;
    }

    char& getChar(int row, int col) {
        return m_buffer[row][col];
    }

    void setChar(int row, int col, char value) {
        m_buffer[row][col] = value;
    }

private:
    int row;
    int col;
    char** m_buffer;
};
