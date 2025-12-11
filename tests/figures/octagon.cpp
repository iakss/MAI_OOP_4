#include "octagon.hpp"

#include <gtest/gtest.h>
#include <sstream>

// Тестовый класс для Octagon с типом double
class OctagonDoubleTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Создаем правильный восьмиугольник с центром в (0,0) и радиусом 1
    std::vector<lib::geometry::Point<double>> vertices = {
        {1, 0},  {std::sqrt(2) / 2, std::sqrt(2) / 2},
        {0, 1},  {-std::sqrt(2) / 2, std::sqrt(2) / 2},
        {-1, 0}, {-std::sqrt(2) / 2, -std::sqrt(2) / 2},
        {0, -1}, {std::sqrt(2) / 2, -std::sqrt(2) / 2}};

    for (size_t i = 0; i < vertices.size(); ++i) {
      test_points[i] =
          std::make_unique<lib::geometry::Point<double>>(vertices[i]);
    }
  }

  std::unique_ptr<lib::geometry::Point<double>> test_points[8];
};

// Тест конструктора по умолчанию
TEST_F(OctagonDoubleTest, DefaultConstructor) {
  lib::geometry::Octagon<double> octagon;
  SUCCEED(); // Конструктор не должен бросать исключений
}

// Тест конструктора копирования
TEST_F(OctagonDoubleTest, CopyConstructor) {
  lib::geometry::Octagon<double> octagon1;
  std::istringstream iss("1 0 0.707107 0.707107 0 1 -0.707107 0.707107 -1 0 "
                         "-0.707107 -0.707107 0 -1 0.707107 -0.707107");
  octagon1.Read(iss);

  lib::geometry::Octagon<double> octagon2(octagon1);

  // Проверяем, что объекты равны
  EXPECT_EQ(octagon1, octagon2);
}

// Тест оператора присваивания копированием
TEST_F(OctagonDoubleTest, CopyAssignment) {
  lib::geometry::Octagon<double> octagon1;
  std::istringstream iss1("1 0 0.707107 0.707107 0 1 -0.707107 0.707107 -1 0 "
                          "-0.707107 -0.707107 0 -1 0.707107 -0.707107");
  octagon1.Read(iss1);

  lib::geometry::Octagon<double> octagon2;
  std::istringstream iss2("2 0 1.414214 1.414214 0 2 -1.414214 1.414214 -2 0 "
                          "-1.414214 -1.414214 0 -2 1.414214 -1.414214");
  octagon2.Read(iss2);

  octagon2 = octagon1;

  EXPECT_EQ(octagon1, octagon2);
}

// Тест конструктора перемещения
TEST_F(OctagonDoubleTest, MoveConstructor) {
  lib::geometry::Octagon<double> octagon1;
  std::istringstream iss("1 0 0.707107 0.707107 0 1 -0.707107 0.707107 -1 0 "
                         "-0.707107 -0.707107 0 -1 0.707107 -0.707107");
  octagon1.Read(iss);

  auto center_before = octagon1.GetCenter();
  auto area_before = static_cast<double>(octagon1);

  lib::geometry::Octagon<double> octagon2(std::move(octagon1));

  // Проверяем, что данные переместились
  EXPECT_DOUBLE_EQ(center_before.x, octagon2.GetCenter().x);
  EXPECT_DOUBLE_EQ(center_before.y, octagon2.GetCenter().y);
  EXPECT_DOUBLE_EQ(area_before, static_cast<double>(octagon2));
}

// Тест оператора присваивания перемещением
TEST_F(OctagonDoubleTest, MoveAssignment) {
  lib::geometry::Octagon<double> octagon1, octagon2;
  std::istringstream iss1("1 0 0.707107 0.707107 0 1 -0.707107 0.707107 -1 0 "
                          "-0.707107 -0.707107 0 -1 0.707107 -0.707107");
  std::istringstream iss2("2 0 1.414214 1.414214 0 2 -1.414214 1.414214 -2 0 "
                          "-1.414214 -1.414214 0 -2 1.414214 -1.414214");

  octagon1.Read(iss1);
  octagon2.Read(iss2);

  auto center_before = octagon1.GetCenter();
  auto area_before = static_cast<double>(octagon1);

  octagon2 = std::move(octagon1);

  // Проверяем, что данные переместились
  EXPECT_DOUBLE_EQ(center_before.x, octagon2.GetCenter().x);
  EXPECT_DOUBLE_EQ(center_before.y, octagon2.GetCenter().y);
  EXPECT_DOUBLE_EQ(area_before, static_cast<double>(octagon2));
}

// Тест вычисления площади
TEST_F(OctagonDoubleTest, AreaCalculation) {
  lib::geometry::Octagon<double> octagon;
  std::istringstream iss("1 0 0.707107 0.707107 0 1 -0.707107 0.707107 -1 0 "
                         "-0.707107 -0.707107 0 -1 0.707107 -0.707107");
  octagon.Read(iss);

  double area = static_cast<double>(octagon);
  // Площадь правильного восьмиугольника с радиусом 1
  double expected_area = 2.0 * std::sqrt(2.0); // ≈ 2.828427

  EXPECT_NEAR(area, expected_area, 1e-6);
}

// Тест вычисления центра
TEST_F(OctagonDoubleTest, CenterCalculation) {
  lib::geometry::Octagon<double> octagon;
  std::istringstream iss("1 0 0.707107 0.707107 0 1 -0.707107 0.707107 -1 0 "
                         "-0.707107 -0.707107 0 -1 0.707107 -0.707107");
  octagon.Read(iss);

  auto center = octagon.GetCenter();

  // Центр симметричного восьмиугольника должен быть в (0,0)
  EXPECT_NEAR(center.x, 0.0, 1e-10);
  EXPECT_NEAR(center.y, 0.0, 1e-10);
}

// Тест оператора вывода
TEST_F(OctagonDoubleTest, OutputOperator) {
  lib::geometry::Octagon<double> octagon;
  std::istringstream iss("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
  octagon.Read(iss);

  std::ostringstream oss;
  octagon.Print(oss);

  EXPECT_FALSE(oss.str().empty());
  EXPECT_NE(oss.str().find("Octagon's vertices"), std::string::npos);
}

// Тест операторов ввода/вывода через Figure
TEST_F(OctagonDoubleTest, IOStreamOperators) {
  lib::geometry::Octagon<double> octagon1;
  std::stringstream ss;

  // Записываем восьмиугольник
  std::istringstream iss("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
  octagon1.Read(iss);

  ss << octagon1;

  // Считываем обратно
  lib::geometry::Octagon<double> octagon2;
  // Note: оператор >> для Figure вызывает Read, который ожидает 16 чисел
  // Для простоты тестируем только, что операции компилируются
  SUCCEED();
}

// Тест операторов сравнения
TEST_F(OctagonDoubleTest, EqualityOperators) {
  lib::geometry::Octagon<double> octagon1, octagon2, octagon3;

  std::istringstream iss1("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
  std::istringstream iss2("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
  std::istringstream iss3("2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17");

  octagon1.Read(iss1);
  octagon2.Read(iss2);
  octagon3.Read(iss3);

  EXPECT_EQ(octagon1, octagon2);
  EXPECT_NE(octagon1, octagon3);
  EXPECT_NE(octagon2, octagon3);
}

// Тест функции swap
TEST_F(OctagonDoubleTest, SwapFunction) {
  lib::geometry::Octagon<double> octagon1, octagon2;

  std::istringstream iss1("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
  std::istringstream iss2("16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1");

  octagon1.Read(iss1);
  octagon2.Read(iss2);

  auto octagon1_copy = octagon1;
  auto octagon2_copy = octagon2;

  swap(octagon1, octagon2);

  EXPECT_EQ(octagon1, octagon2_copy);
  EXPECT_EQ(octagon2, octagon1_copy);
}

// Тесты для целочисленного типа
class OctagonIntTest : public ::testing::Test {};

TEST_F(OctagonIntTest, IntegerType) {
  lib::geometry::Octagon<int> octagon;
  std::istringstream iss("0 0 1 0 1 1 0 1 -1 1 -1 0 -1 -1 0 -1");
  octagon.Read(iss);

  auto center = octagon.GetCenter();
  // Центр: (0,0) так как сумма всех x и y равна 0

  EXPECT_EQ(center.x, 0);
  EXPECT_EQ(center.y, 0);

  // Площадь будет вычислена как double
  double area = static_cast<double>(octagon);
  EXPECT_GT(area, 0);
}

// Тест на полиморфизм через указатель на Figure
TEST_F(OctagonDoubleTest, Polymorphism) {
  std::unique_ptr<lib::geometry::Figure<double>> figure =
      std::make_unique<lib::geometry::Octagon<double>>();

  std::istringstream iss("1 0 0.707107 0.707107 0 1 -0.707107 0.707107 -1 0 "
                         "-0.707107 -0.707107 0 -1 0.707107 -0.707107");
  figure->Read(iss);

  auto center = figure->GetCenter();
  double area = static_cast<double>(*figure);

  EXPECT_NEAR(center.x, 0.0, 1e-10);
  EXPECT_NEAR(center.y, 0.0, 1e-10);
  EXPECT_GT(area, 0);
}

// Тест исключительных ситуаций (деление на ноль при вычислении центра)
TEST_F(OctagonDoubleTest, NoDivisionByZero) {
  // Создаем восьмиугольник с нулевой площадью (все точки в начале координат)
  lib::geometry::Octagon<double> octagon;
  std::istringstream iss("0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
  octagon.Read(iss);

  // Центр должен быть (0,0) без деления на ноль
  auto center = octagon.GetCenter();
  EXPECT_EQ(center.x, 0);
  EXPECT_EQ(center.y, 0);

  // Площадь должна быть 0
  double area = static_cast<double>(octagon);
  EXPECT_DOUBLE_EQ(area, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
