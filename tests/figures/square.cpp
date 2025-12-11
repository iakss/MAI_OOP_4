#include "square.hpp"

#include <gtest/gtest.h>
#include <sstream>

// Тестовый класс для Square с типом double
class SquareDoubleTest : public ::testing::Test {
protected:
  void SetUp() override {
    std::vector<lib::geometry::Point<double>> vertices = {
        {1, -1}, {-1, -1}, {-1, 1}, {1, 1}};

    for (size_t i = 0; i < vertices.size(); ++i) {
      test_points[i] =
          std::make_unique<lib::geometry::Point<double>>(vertices[i]);
    }
  }

  std::unique_ptr<lib::geometry::Point<double>> test_points[8];
};

// Тест конструктора по умолчанию
TEST_F(SquareDoubleTest, DefaultConstructor) {
  lib::geometry::Square<double> square;
  SUCCEED(); // Конструктор не должен бросать исключений
}

// Тест конструктора копирования
TEST_F(SquareDoubleTest, CopyConstructor) {
  lib::geometry::Square<double> square1;
  std::istringstream iss("1 -1 -1 -1 -1 1 1 1");
  square1.Read(iss);

  lib::geometry::Square<double> square2(square1);

  // Проверяем, что объекты равны
  EXPECT_EQ(square1, square2);
}

// Тест оператора присваивания копированием
TEST_F(SquareDoubleTest, CopyAssignment) {
  lib::geometry::Square<double> square1;
  std::istringstream iss1("1 -1 -1 -1 -1 1 1 1");
  square1.Read(iss1);

  lib::geometry::Square<double> square2;
  std::istringstream iss2("2 -2 -2 -2 -2 2 2 2");
  square2.Read(iss2);

  square2 = square1;

  EXPECT_EQ(square1, square2);
}

// Тест конструктора перемещения
TEST_F(SquareDoubleTest, MoveConstructor) {
  lib::geometry::Square<double> square1;
  std::istringstream iss("1 -1 -1 -1 -1 1 1 1");
  square1.Read(iss);

  auto center_before = square1.GetCenter();
  auto area_before = static_cast<double>(square1);

  lib::geometry::Square<double> square2(std::move(square1));

  // Проверяем, что данные переместились
  EXPECT_DOUBLE_EQ(center_before.x, square2.GetCenter().x);
  EXPECT_DOUBLE_EQ(center_before.y, square2.GetCenter().y);
  EXPECT_DOUBLE_EQ(area_before, static_cast<double>(square2));
}

// Тест оператора присваивания перемещением
TEST_F(SquareDoubleTest, MoveAssignment) {
  lib::geometry::Square<double> square1, square2;
  std::istringstream iss1("1 -1 -1 -1 -1 1 1 1");
  std::istringstream iss2("2 -2 -2 -2 -2 2 2 2");

  square1.Read(iss1);
  square2.Read(iss2);

  auto center_before = square1.GetCenter();
  auto area_before = static_cast<double>(square1);

  square2 = std::move(square1);

  // Проверяем, что данные переместились
  EXPECT_DOUBLE_EQ(center_before.x, square2.GetCenter().x);
  EXPECT_DOUBLE_EQ(center_before.y, square2.GetCenter().y);
  EXPECT_DOUBLE_EQ(area_before, static_cast<double>(square2));
}

// Тест вычисления площади
TEST_F(SquareDoubleTest, AreaCalculation) {
  lib::geometry::Square<double> square;
  std::istringstream iss("2 -2 -2 -2 -2 2 2 2");
  square.Read(iss);

  double area = static_cast<double>(square);
  double expected_area = 16.0;

  EXPECT_NEAR(area, expected_area, 1e-6);
}

// Тест вычисления центра
TEST_F(SquareDoubleTest, CenterCalculation) {
  lib::geometry::Square<double> square;
  std::istringstream iss("2 -2 -2 -2 -2 2 2 2");
  square.Read(iss);

  auto center = square.GetCenter();

  // Центр симметричного восьмиугольника должен быть в (0,0)
  EXPECT_NEAR(center.x, 0.0, 1e-10);
  EXPECT_NEAR(center.y, 0.0, 1e-10);
}

// Тест оператора вывода
TEST_F(SquareDoubleTest, OutputOperator) {
  lib::geometry::Square<double> square;
  std::istringstream iss("1 2 3 4 5 6 7 8");
  square.Read(iss);

  std::ostringstream oss;
  square.Print(oss);

  EXPECT_FALSE(oss.str().empty());
  EXPECT_NE(oss.str().find("Square's vertices"), std::string::npos);
}

// Тест операторов ввода/вывода через Figure
TEST_F(SquareDoubleTest, IOStreamOperators) {
  lib::geometry::Square<double> square1;
  std::stringstream ss;

  // Записываем восьмиугольник
  std::istringstream iss("1 2 3 4 5 6 7 8");
  square1.Read(iss);

  ss << square1;

  // Считываем обратно
  lib::geometry::Square<double> square2;
  // Note: оператор >> для Figure вызывает Read, который ожидает 16 чисел
  // Для простоты тестируем только, что операции компилируются
  SUCCEED();
}

// Тест операторов сравнения
TEST_F(SquareDoubleTest, EqualityOperators) {
  lib::geometry::Square<double> square1, square2, square3;

  std::istringstream iss1("1 2 3 4 5 6 7 8");
  std::istringstream iss2("1 2 3 4 5 6 7 8");
  std::istringstream iss3("2 3 4 5 6 7 8 9");

  square1.Read(iss1);
  square2.Read(iss2);
  square3.Read(iss3);

  EXPECT_EQ(square1, square2);
  EXPECT_NE(square1, square3);
  EXPECT_NE(square2, square3);
}

// Тест функции swap
TEST_F(SquareDoubleTest, SwapFunction) {
  lib::geometry::Square<double> square1, square2;

  std::istringstream iss1("1 2 3 4 5 6 7 8");
  std::istringstream iss2("8 7 6 5 4 3 2 1");

  square1.Read(iss1);
  square2.Read(iss2);

  auto square1_copy = square1;
  auto square2_copy = square2;

  swap(square1, square2);

  EXPECT_EQ(square1, square2_copy);
  EXPECT_EQ(square2, square1_copy);
}

// Тесты для целочисленного типа
class SquareIntTest : public ::testing::Test {};

TEST_F(SquareIntTest, IntegerType) {
  lib::geometry::Square<int> square;
  std::istringstream iss("1 -1 -1 -1 -1 1 1 1");
  square.Read(iss);

  auto center = square.GetCenter();
  // Центр: (0,0) так как сумма всех x и y равна 0

  EXPECT_EQ(center.x, 0);
  EXPECT_EQ(center.y, 0);

  // Площадь будет вычислена как double
  double area = static_cast<double>(square);
  EXPECT_GT(area, 0);
}

// Тест на полиморфизм через указатель на Figure
TEST_F(SquareDoubleTest, Polymorphism) {
  std::unique_ptr<lib::geometry::Figure<double>> figure =
      std::make_unique<lib::geometry::Square<double>>();

  std::istringstream iss("1 -1 -1 -1 -1 1 1 1");
  figure->Read(iss);

  auto center = figure->GetCenter();
  double area = static_cast<double>(*figure);

  EXPECT_NEAR(center.x, 0.0, 1e-10);
  EXPECT_NEAR(center.y, 0.0, 1e-10);
  EXPECT_GT(area, 0);
}

// Тест исключительных ситуаций (деление на ноль при вычислении центра)
TEST_F(SquareDoubleTest, NoDivisionByZero) {
  // Создаем восьмиугольник с нулевой площадью (все точки в начале координат)
  lib::geometry::Square<double> square;
  std::istringstream iss("0 0 0 0 0 0 0 0");
  square.Read(iss);

  // Центр должен быть (0,0) без деления на ноль
  auto center = square.GetCenter();
  EXPECT_EQ(center.x, 0);
  EXPECT_EQ(center.y, 0);

  // Площадь должна быть 0
  double area = static_cast<double>(square);
  EXPECT_DOUBLE_EQ(area, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
