#include "utmatrix.h"
#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(5);
    m[0][0] = 42; // ������������� �������� � ������������ �������
    TDynamicMatrix<int> m1(m); // �������� �������
    EXPECT_EQ(m[0][0], m1[0][0]); // ���������, ��� �������� �����
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(5);
    m[0][0] = 42; // ������������� �������� � ������������ �������
    TDynamicMatrix<int> m1(m); // �������� �������
    m[0][0] = 100; // ������ �������� � ������������ �������
    EXPECT_NE(m[0][0], m1[0][0]); // ���������, ��� �������� �� �����
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(5);
    EXPECT_EQ(m.rows(), 5); // ��������, ���� � ��� ���� ����� ��� ��������� ����� �����
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(5);
    m[0][0] = 42; // ������������� ��������
    EXPECT_EQ(m[0][0], 42); // ���������, ��� �������� ���������
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(5);
    ASSERT_ANY_THROW(m[-1][0] = 10); // ��������� ������������� ������
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(5);
    ASSERT_ANY_THROW(m[5][0] = 10); // ��������� ������� ������� ������
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(m = m); // ��������� ���������� ����� ����
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(5);
    m1[0][0] = 1;
    ASSERT_NO_THROW(m2 = m1); // ��������� ����������
    EXPECT_EQ(m2[0][0], 1); // ���������, ��� �������� ��������� �����������
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(3);
    m1 = m2; // ���������, ��� ������� ����� �����������
    EXPECT_EQ(m1.rows(), 3); // ��������, ���� � ��� ���� ����� ��� ��������� ����� �����
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(3);
    ASSERT_NO_THROW(m1 = m2); // ��������� ����������
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(5);
    m1[0][0] = 1;
    m2[0][0] = 1;
    EXPECT_TRUE(m1 == m2); // ��������� ���������
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(5);
    EXPECT_TRUE(m == m); // ���������, ��� ������� ����� ���� ����
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(3);
    EXPECT_FALSE(m1 == m2); // ���������, ��� ������� ������ �������� �� �����
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(5);
    m1[0][0] = 1;
    m2[0][0] = 2;
    auto m3 = m1 + m2; // ����������
    EXPECT_EQ(m3[0][0], 3); // ��������� ���������
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(3);
    ASSERT_ANY_THROW(m1 + m2); // ��������� �������� ������ ������� �������
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(5);
    m1[0][0] = 5;
    m2[0][0] = 2;
    auto m3 = m1 - m2; // ��������
    EXPECT_EQ(m3[0][0], 3); // ��������� ���������
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(3);
    ASSERT_ANY_THROW(m1 - m2); // ��������� ��������� ������ ������� �������
}
