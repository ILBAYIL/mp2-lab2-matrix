#include "utmatrix.h"
#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
    TDynamicVector<int> v(10);
    ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v(10);
    v[0] = 42; // Устанавливаем значение в оригинальном векторе
    TDynamicVector<int> v1(v); // Копируем вектор
    EXPECT_EQ(v[0], v1[0]); // Проверяем, что значения равны
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(10);
    v[0] = 42; // Устанавливаем значение в оригинальном векторе
    TDynamicVector<int> v1(v); // Копируем вектор
    v[0] = 100; // Меняем значение в оригинальном векторе
    EXPECT_NE(v[0], v1[0]); // Проверяем, что значения не равны
}

TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(4);
    EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
    TDynamicVector<int> v(4);
    v[0] = 4; // Устанавливаем значение

    EXPECT_EQ(4, v[0]); // Проверяем, что значение корректно
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(4);
    ASSERT_ANY_THROW(v[-1] = 10); // Проверяем отрицательный индекс
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(4);
    ASSERT_ANY_THROW(v[4] = 10); // Проверяем слишком большой индекс
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(4);
    ASSERT_NO_THROW(v = v); // Проверяем присвоение самой себе
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);
    v1[0] = 1;
    ASSERT_NO_THROW(v2 = v1); // Проверяем присвоение
    EXPECT_EQ(v2[0], 1); // Проверяем, что значение корректно скопировано
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(2);
    ASSERT_NO_THROW(v1 = v2); // Проверяем присвоение
    EXPECT_EQ(v1.size(), 2); // Проверяем, что размер изменился
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(2);
    ASSERT_NO_THROW(v1 = v2); // Проверяем присвоение
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);
    v1[0] = 1;
    v2[0] = 1;
    EXPECT_TRUE(v1 == v2); // Проверяем равенство
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(4);
    EXPECT_TRUE(v == v); // Проверяем, что вектор равен сам себе
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(2);
    EXPECT_FALSE(v1 == v2); // Проверяем, что векторы разных размеров не равны
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(4);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v = v + 5; // Складываем скаляр
    EXPECT_EQ(v[0], 6); // Проверяем результат
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(4);
    v[0] = 10;
    v[1] = 11;
    v[2] = 12;
    v[3] = 13;
    v = v - 5; // Вычитаем скаляр
    EXPECT_EQ(v[0], 5); // Проверяем результат
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(4);
    v[0] = 2;
    v[1] = 3;
    v[2] = 4;
    v[3] = 5;
    v = v * 3; // Умножаем на скаляр
    EXPECT_EQ(v[0], 6); // Проверяем результат
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);
    v1[0] = 1;
    v2[0] = 2;
    auto v3 = v1 + v2; // Складываем векторы
    EXPECT_EQ(v3[0], 3); // Проверяем результат
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(2);
    ASSERT_ANY_THROW(v1 + v2); // Проверяем сложение векторов разного размера
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);
    v1[0] = 5;
    v2[0] = 2;
    auto v3 = v1 - v2; // Вычитаем векторы
    EXPECT_EQ(v3[0], 3); // Проверяем результат
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(2);
    ASSERT_ANY_THROW(v1 - v2); // Проверяем вычитание векторов разного размера
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);
    v1[0] = 1;
    v2[0] = 2;
    auto result = v1 * v2; // Умножаем векторы
    EXPECT_EQ(result, 2); // Проверяем результат (скалярное произведение)
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(2);
    ASSERT_ANY_THROW(v1 * v2, invalid_argument); // Проверяем умножение векторов разного размера
}
