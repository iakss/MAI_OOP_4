#include "vector.hpp"

#include <gtest/gtest.h>
#include <string>

namespace tests::vector {

// Тесты для конструкторов
TEST(VectorTest, DefaultConstructor) {
  lib::vector::Vector<int> v;
  EXPECT_EQ(v.Size(), 0);
  EXPECT_EQ(v.Capacity(), 0);
  EXPECT_TRUE(v.Empty());
}

TEST(VectorTest, ConstructorWithCount) {
  lib::vector::Vector<int> v(5);
  EXPECT_EQ(v.Size(), 5);
  EXPECT_GE(v.Capacity(), 5);
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], int{});
  }
}

TEST(VectorTest, ConstructorWithCountAndValue) {
  lib::vector::Vector<int> v(5, 42);
  EXPECT_EQ(v.Size(), 5);
  EXPECT_GE(v.Capacity(), 5);
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], 42);
  }
}

TEST(VectorTest, ConstructorWithInitializerList) {
  lib::vector::Vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.Size(), 5);
  EXPECT_GE(v.Capacity(), 10);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], i + 1);
  }
}

// Тесты копирования и перемещения
TEST(VectorTest, CopyConstructor) {
  lib::vector::Vector<int> original{1, 2, 3};
  lib::vector::Vector<int> copy(original);
  EXPECT_EQ(copy.Size(), original.Size());
  for (size_t i = 0; i < original.Size(); ++i) {
    EXPECT_EQ(copy[i], original[i]);
  }
}

TEST(VectorTest, CopyAssignment) {
  lib::vector::Vector<int> original{1, 2, 3};
  lib::vector::Vector<int> copy;
  copy = original;
  EXPECT_EQ(copy.Size(), original.Size());
  for (size_t i = 0; i < original.Size(); ++i) {
    EXPECT_EQ(copy[i], original[i]);
  }
}

TEST(VectorTest, MoveConstructor) {
  lib::vector::Vector<int> original{1, 2, 3};
  lib::vector::Vector<int> moved(std::move(original));
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(original.Size(), 0);
  EXPECT_EQ(original.Capacity(), 0);
  EXPECT_EQ(original.Data(), nullptr);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(moved[i], i + 1);
  }
}

TEST(VectorTest, MoveAssignment) {
  lib::vector::Vector<int> original{1, 2, 3};
  lib::vector::Vector<int> moved;
  moved = std::move(original);
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(original.Size(), 0);
  EXPECT_EQ(original.Capacity(), 0);
  EXPECT_EQ(original.Data(), nullptr);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(moved[i], i + 1);
  }
}

// Тесты доступа к элементам
TEST(VectorTest, ElementAccess) {
  lib::vector::Vector<int> v{10, 20, 30};
  EXPECT_EQ(v.Front(), 10);
  EXPECT_EQ(v.Back(), 30);
  EXPECT_EQ(v[1], 20);
  v[1] = 25;
  EXPECT_EQ(v[1], 25);
  EXPECT_EQ(v.Data()[2], 30);
}

TEST(VectorTest, ConstElementAccess) {
  const lib::vector::Vector<int> v{10, 20, 30};
  EXPECT_EQ(v.Front(), 10);
  EXPECT_EQ(v.Back(), 30);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v.Data()[2], 30);
}

// Тесты модификации
TEST(VectorTest, PushBack) {
  lib::vector::Vector<int> v;
  v.PushBack(1);
  v.PushBack(2);
  v.PushBack(3);
  EXPECT_EQ(v.Size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, EmplaceBack) {
  lib::vector::Vector<std::string> v;
  v.EmplaceBack(5, 'a');
  v.EmplaceBack("hello");
  EXPECT_EQ(v.Size(), 2);
  EXPECT_EQ(v[0], "aaaaa");
  EXPECT_EQ(v[1], "hello");
}

TEST(VectorTest, PopBack) {
  lib::vector::Vector<int> v{1, 2, 3};
  v.PopBack();
  EXPECT_EQ(v.Size(), 2);
  EXPECT_EQ(v.Back(), 2);
  v.PopBack();
  EXPECT_EQ(v.Back(), 1);
}

TEST(VectorTest, Insert) {
  lib::vector::Vector<int> v{1, 2, 4};
  v.Insert(2, 3); // вставляем 3 на позицию 2
  EXPECT_EQ(v.Size(), 4);
  int expected[] = {1, 2, 3, 4};
  for (size_t i = 0; i < v.Size(); ++i) {
    EXPECT_EQ(v[i], expected[i]);
  }
}

TEST(VectorTest, Erase) {
  lib::vector::Vector<int> v{1, 2, 3, 4, 5};
  v.Erase(2); // удаляем элемент с индексом 2 (значение 3)
  EXPECT_EQ(v.Size(), 4);
  int expected[] = {1, 2, 4, 5};
  for (size_t i = 0; i < v.Size(); ++i) {
    EXPECT_EQ(v[i], expected[i]);
  }
}

TEST(VectorTest, Clear) {
  lib::vector::Vector<int> v{1, 2, 3};
  v.Clear();
  EXPECT_EQ(v.Size(), 0);
  EXPECT_TRUE(v.Empty());
}

// Тесты управления памятью
TEST(VectorTest, Reserve) {
  lib::vector::Vector<int> v;
  EXPECT_EQ(v.Capacity(), 0);
  v.Reserve(100);
  EXPECT_GE(v.Capacity(), 100);
  EXPECT_EQ(v.Size(), 0);
  EXPECT_TRUE(v.Empty());
}

TEST(VectorTest, ReserveDoesNotShrink) {
  lib::vector::Vector<int> v(50);
  size_t old_cap = v.Capacity();
  v.Reserve(10);
  EXPECT_EQ(v.Capacity(), old_cap); // емкость не уменьшается
}

// Тест swap
TEST(VectorTest, Swap) {
  lib::vector::Vector<int> a{1, 2, 3};
  lib::vector::Vector<int> b{4, 5};
  a.Swap(b);
  EXPECT_EQ(a.Size(), 2);
  EXPECT_EQ(b.Size(), 3);
  EXPECT_EQ(a[0], 4);
  EXPECT_EQ(b[0], 1);
}

// Тест с нетривиальным типом (std::string)
TEST(VectorTest, NonTrivialType) {
  lib::vector::Vector<std::string> v;
  v.PushBack("first");
  v.EmplaceBack(3, 'x'); // "xxx"
  v.Insert(1, "second");
  EXPECT_EQ(v.Size(), 3);
  EXPECT_EQ(v[0], "first");
  EXPECT_EQ(v[1], "second");
  EXPECT_EQ(v[2], "xxx");
  v.Erase(0);
  EXPECT_EQ(v.Size(), 2);
  EXPECT_EQ(v.Front(), "second");
}

// Крайние случаи и корректность
TEST(VectorTest, SelfAssignment) {
  lib::vector::Vector<int> v{1, 2, 3};
  v = v;
  EXPECT_EQ(v.Size(), 3);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, MoveSelfAssignment) {
  lib::vector::Vector<int> v{1, 2, 3};
  v = std::move(v);
  // после перемещения в себя состояние должно остаться валидным
  EXPECT_EQ(v.Size(), 3);
}

} // namespace tests::vector

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
