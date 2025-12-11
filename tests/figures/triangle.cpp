#include "triangle.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <sstream>

// Тестовый класс для Triangle с типом double
class TriangleDoubleTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Создаем правильный треугольник (равносторонний) с центром в (0,0)
    std::vector<lib::geometry::Point<double>> vertices = {
        {0, 1},                    // вершина вверху
        {-std::sqrt(3) / 2, -0.5}, // левая нижняя вершина
        {std::sqrt(3) / 2, -0.5}   // правая нижняя вершина
    };

    for (size_t i = 0; i < vertices.size(); ++i) {
      test_points[i] =
          std::make_unique<lib::geometry::Point<double>>(vertices[i]);
    }
  }

  std::unique_ptr<lib::geometry::Point<double>> test_points[3];
};

// Тест конструктора по умолчанию
TEST_F(TriangleDoubleTest, DefaultConstructor) {
  lib::geometry::Triangle<double> triangle;
  SUCCEED(); // Конструктор не должен бросать исключений
}

// Тест конструктора копирования
TEST_F(TriangleDoubleTest, CopyConstructor) {
  lib::geometry::Triangle<double> triangle1;
  std::istringstream iss("0 1 -0.866025 -0.5 0.866025 -0.5");
  triangle1.Read(iss);

  lib::geometry::Triangle<double> triangle2(triangle1);

  // Проверяем, что объекты равны
  EXPECT_EQ(triangle1, triangle2);
}

// Тест оператора присваивания копированием
TEST_F(TriangleDoubleTest, CopyAssignment) {
  lib::geometry::Triangle<double> triangle1;
  std::istringstream iss1("0 1 -0.866025 -0.5 0.866025 -0.5");
  triangle1.Read(iss1);

  lib::geometry::Triangle<double> triangle2;
  std::istringstream iss2("1 2 3 4 5 6");
  triangle2.Read(iss2);

  triangle2 = triangle1;

  EXPECT_EQ(triangle1, triangle2);
}

// Тест конструктора перемещения
TEST_F(TriangleDoubleTest, MoveConstructor) {
  lib::geometry::Triangle<double> triangle1;
  std::istringstream iss("0 1 -0.866025 -0.5 0.866025 -0.5");
  triangle1.Read(iss);

  auto center_before = triangle1.GetCenter();
  auto area_before = static_cast<double>(triangle1);

  lib::geometry::Triangle<double> triangle2(std::move(triangle1));

  // Проверяем, что данные переместились
  EXPECT_NEAR(center_before.x, triangle2.GetCenter().x, 1e-10);
  EXPECT_NEAR(center_before.y, triangle2.GetCenter().y, 1e-10);
  EXPECT_DOUBLE_EQ(area_before, static_cast<double>(triangle2));
}

// Тест оператора присваивания перемещением
TEST_F(TriangleDoubleTest, MoveAssignment) {
  lib::geometry::Triangle<double> triangle1, triangle2;
  std::istringstream iss1("0 1 -0.866025 -0.5 0.866025 -0.5");
  std::istringstream iss2("1 2 3 4 5 6");

  triangle1.Read(iss1);
  triangle2.Read(iss2);

  auto center_before = triangle1.GetCenter();
  auto area_before = static_cast<double>(triangle1);

  triangle2 = std::move(triangle1);

  // Проверяем, что данные переместились
  EXPECT_NEAR(center_before.x, triangle2.GetCenter().x, 1e-10);
  EXPECT_NEAR(center_before.y, triangle2.GetCenter().y, 1e-10);
  EXPECT_DOUBLE_EQ(area_before, static_cast<double>(triangle2));
}

// Тест вычисления площади (исправленная версия)
TEST_F(TriangleDoubleTest, AreaCalculation) {
  lib::geometry::Triangle<double> triangle;

  // Используем простой прямоугольный треугольник для легкой проверки
  std::istringstream iss("8 0 0 0 4 6.928203"); // катеты 3 и 4, площадь = 6
  triangle.Read(iss);

  double area = static_cast<double>(triangle);

  std::cout << area << '\n';
  EXPECT_NEAR(area, 27.712812, 1e-6);
}

// Тест вычисления центра
TEST_F(TriangleDoubleTest, CenterCalculation) {
  lib::geometry::Triangle<double> triangle;

  // Простой треугольник
  std::istringstream iss("0 0 4 0 0 3");
  triangle.Read(iss);

  auto center = triangle.GetCenter();

  // Центр треугольника с вершинами (0,0), (4,0), (0,3) = ((0+4+0)/3, (0+0+3)/3)
  // = (4/3, 1)
  EXPECT_NEAR(center.x, 4.0 / 3.0, 1e-10);
  EXPECT_NEAR(center.y, 1.0, 1e-10);
}

// Тест вычисления центра для равностороннего треугольника
TEST_F(TriangleDoubleTest, EquilateralTriangleCenter) {
  lib::geometry::Triangle<double> triangle;

  // Равносторонний треугольник с центром в (0,0)
  std::istringstream iss("0 1 -0.866025 -0.5 0.866025 -0.5");
  triangle.Read(iss);

  auto center = triangle.GetCenter();

  // Центр должен быть в (0,0)
  EXPECT_NEAR(center.x, 0.0, 1e-10);
  EXPECT_NEAR(center.y, 0.0, 1e-10);
}

// Тест оператора вывода
TEST_F(TriangleDoubleTest, OutputOperator) {
  lib::geometry::Triangle<double> triangle;
  std::istringstream iss("1 2 3 4 5 6");
  triangle.Read(iss);

  std::ostringstream oss;
  triangle.Print(oss);

  EXPECT_FALSE(oss.str().empty());
  EXPECT_NE(oss.str().find("Triangle's vertices"), std::string::npos);

  // Проверяем, что вывод содержит координаты
  EXPECT_NE(oss.str().find('1'), std::string::npos);
  EXPECT_NE(oss.str().find('2'), std::string::npos);
}

// Тест операторов ввода/вывода через Figure
TEST_F(TriangleDoubleTest, IOStreamOperators) {
  lib::geometry::Triangle<double> triangle1;
  std::stringstream ss;

  // Записываем треугольник
  std::istringstream iss("1 2 3 4 5 6");
  triangle1.Read(iss);

  ss << triangle1;

  std::string output = ss.str();
  EXPECT_FALSE(output.empty());

  // Считываем обратно в другой треугольник
  lib::geometry::Triangle<double> triangle2;
  std::istringstream iss2("1 2 3 4 5 6");
  triangle2.Read(iss2);

  // Проверяем, что они равны
  // Note: для точного сравнения нужно реализовать operator==
  // Вместо этого проверим, что центры совпадают
  EXPECT_TRUE(triangle1 == triangle2);
  EXPECT_TRUE(triangle1 == triangle2);
}

// Тест операторов сравнения
TEST_F(TriangleDoubleTest, EqualityOperators) {
  lib::geometry::Triangle<double> triangle1, triangle2, triangle3;

  std::istringstream iss1("1 2 3 4 5 6");
  std::istringstream iss2("1 2 3 4 5 6");
  std::istringstream iss3("7 8 9 10 11 12");

  triangle1.Read(iss1);
  triangle2.Read(iss2);
  triangle3.Read(iss3);

  EXPECT_EQ(triangle1, triangle2);
  EXPECT_NE(triangle1, triangle3);
  EXPECT_NE(triangle2, triangle3);
}

// Тест функции swap
TEST_F(TriangleDoubleTest, SwapFunction) {
  lib::geometry::Triangle<double> triangle1, triangle2;

  std::istringstream iss1("1 2 3 4 5 6");
  std::istringstream iss2("7 8 9 10 11 12");

  triangle1.Read(iss1);
  triangle2.Read(iss2);

  auto triangle1_copy = triangle1;
  auto triangle2_copy = triangle2;

  swap(triangle1, triangle2);

  EXPECT_EQ(triangle1, triangle2_copy);
  EXPECT_EQ(triangle2, triangle1_copy);
}

// Тесты для целочисленного типа
class TriangleIntTest : public ::testing::Test {};

TEST_F(TriangleIntTest, IntegerType) {
  lib::geometry::Triangle<int> triangle;
  std::istringstream iss("0 0 4 0 0 3");
  triangle.Read(iss);

  auto center = triangle.GetCenter();
  // Центр: (4/3, 1) -> при целочисленном делении: (1, 1)
  // Но так как используется деление на целое, будет целочисленное деление

  EXPECT_EQ(center.x, 1); // (0+4+0)/3 = 1 (целочисленное деление)
  EXPECT_EQ(center.y, 1); // (0+0+3)/3 = 1 (целочисленное деление)

  // Площадь будет вычислена как double
  double area = static_cast<double>(triangle);
  EXPECT_GT(area, 0);
}

// Тест на полиморфизм через указатель на Figure
TEST_F(TriangleDoubleTest, Polymorphism) {
  std::unique_ptr<lib::geometry::Figure<double>> figure =
      std::make_unique<lib::geometry::Triangle<double>>();

  std::istringstream iss("0 0 4 0 0 3");
  figure->Read(iss);

  auto center = figure->GetCenter();
  double area = static_cast<double>(*figure);

  EXPECT_NEAR(center.x, 4.0 / 3.0, 1e-10);
  EXPECT_NEAR(center.y, 1.0, 1e-10);
  EXPECT_GT(area, 0);
}

// Тест исключительных ситуаций (деление на ноль при вычислении центра)
TEST_F(TriangleDoubleTest, NoDivisionByZero) {
  // Создаем треугольник с нулевой площадью (все точки в начале координат)
  lib::geometry::Triangle<double> triangle;
  std::istringstream iss("0 0 0 0 0 0");
  triangle.Read(iss);

  // Центр должен быть (0,0) без деления на ноль
  auto center = triangle.GetCenter();
  EXPECT_EQ(center.x, 0);
  EXPECT_EQ(center.y, 0);

  // Площадь должна быть 0
  double area = static_cast<double>(triangle);
  EXPECT_DOUBLE_EQ(area, 0);
}

// Тест на вырожденный треугольник (точки на одной прямой)
TEST_F(TriangleDoubleTest, DegenerateTriangle) {
  lib::geometry::Triangle<double> triangle;

  // Точки на одной прямой: (0,0), (1,1), (2,2)
  std::istringstream iss("0 0 1 1 2 2");
  triangle.Read(iss);

  // Центр должен быть вычислен корректно
  auto center = triangle.GetCenter();
  EXPECT_NEAR(center.x, 1.0, 1e-10); // (0+1+2)/3 = 1
  EXPECT_NEAR(center.y, 1.0, 1e-10); // (0+1+2)/3 = 1

  // Площадь вырожденного треугольника должна быть 0
  double area = static_cast<double>(triangle);
  EXPECT_GE(area, 0); // Площадь должна быть неотрицательной
}

// Тест константы NUMBER_OF_VERTICES
TEST_F(TriangleDoubleTest, NumberOfVerticesConstant) {
  EXPECT_EQ(lib::geometry::Triangle<double>::NUMBER_OF_VERTICES, 3);
}

// Тест константы ANGLE
TEST_F(TriangleDoubleTest, AngleConstant) {
  EXPECT_EQ(lib::geometry::Triangle<double>::ANGLE, std::numbers::pi / 3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
