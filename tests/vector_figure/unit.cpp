#include "octagon.hpp"
#include "square.hpp"
#include "triangle.hpp"
#include "vector_figure.hpp"

#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

namespace tests::geometry {

// Вспомогательные функции для создания фигур

// Тесты для указателей на конкретные фигуры
template <lib::concepts::Scalar T> void TestPrintCentersWithSquarePointers() {
  std::cout << "  Testing PrintCenters with Square<T>*" << std::endl;

  lib::vector::Vector<lib::geometry::Square<T> *> squares;

  // Создаем и добавляем квадраты
  auto *square1 = new lib::geometry::Square<T>();
  std::stringstream ss1;
  ss1 << "0 0 2 0 2 2 0 2"; // Квадрат с центром в (1,1)
  ss1 >> *square1;
  squares.PushBack(square1);

  auto *square2 = new lib::geometry::Square<T>();
  std::stringstream ss2;
  ss2 << "1 1 4 1 4 4 1 4"; // Квадрат с центром в (2.5,2.5)
  ss2 >> *square2;
  squares.PushBack(square2);

  std::stringstream output;
  lib::geometry::PrintCenters<T>(output, squares);

  std::string result = output.str();
  assert(!result.empty());
  assert(result.find("Centers") != std::string::npos);
  assert(result.find("Figure 0:") != std::string::npos);
  assert(result.find("Figure 1:") != std::string::npos);

  // Очищаем память
  for (size_t i = 0; i < squares.Size(); ++i) {
    delete squares[i];
  }

  std::cout << "    ✓ Passed" << std::endl;
}

template <lib::concepts::Scalar T> void TestPrintCentersWithTrianglePointers() {
  std::cout << "  Testing PrintCenters with Triangle<T>*" << std::endl;

  lib::vector::Vector<lib::geometry::Triangle<T> *> triangles;

  // Создаем и добавляем треугольники
  auto *triangle1 = new lib::geometry::Triangle<T>();
  std::stringstream ss1;
  ss1 << "0 0 4 0 2 3"; // Треугольник с центром в (2,1)
  ss1 >> *triangle1;
  triangles.PushBack(triangle1);

  std::stringstream output;
  lib::geometry::PrintCenters<T>(output, triangles);

  std::string result = output.str();
  assert(!result.empty());
  assert(result.find("Centers") != std::string::npos);
  assert(result.find("Figure 0:") != std::string::npos);

  // Очищаем память
  for (size_t i = 0; i < triangles.Size(); ++i) {
    delete triangles[i];
  }

  std::cout << "    ✓ Passed" << std::endl;
}

template <lib::concepts::Scalar T> void TestPrintCentersWithSquareObjects() {
  std::cout << "  Testing PrintCenters with Square<T> objects" << std::endl;

  lib::vector::Vector<lib::geometry::Square<T>> squares;

  // Создаем и добавляем квадраты как объекты
  lib::geometry::Square<T> square1;
  std::stringstream ss1;
  ss1 << "0 0 3 0 3 3 0 3"; // Квадрат с центром в (1.5,1.5)
  ss1 >> square1;
  squares.PushBack(std::move(square1));

  lib::geometry::Square<T> square2;
  std::stringstream ss2;
  ss2 << "2 2 5 2 5 5 2 5"; // Квадрат с центром в (3.5,3.5)
  ss2 >> square2;
  squares.PushBack(std::move(square2));

  std::stringstream output;
  lib::geometry::PrintCenters<T>(output, squares);

  std::string result = output.str();
  assert(!result.empty());
  assert(result.find("Centers") != std::string::npos);
  assert(result.find("Figure 0:") != std::string::npos);
  assert(result.find("Figure 1:") != std::string::npos);

  std::cout << "    ✓ Passed" << std::endl;
}

template <lib::concepts::Scalar T> void TestPrintCentersWithTriangleObjects() {
  std::cout << "  Testing PrintCenters with Triangle<T> objects" << std::endl;

  lib::vector::Vector<lib::geometry::Triangle<T>> triangles;

  // Создаем и добавляем треугольники как объекты
  lib::geometry::Triangle<T> triangle1;
  std::stringstream ss1;
  ss1 << "0 0 5 0 2.5 4"; // Треугольник
  ss1 >> triangle1;
  triangles.PushBack(std::move(triangle1));

  std::stringstream output;
  lib::geometry::PrintCenters<T>(output, triangles);

  std::string result = output.str();
  assert(!result.empty());
  assert(result.find("Centers") != std::string::npos);
  assert(result.find("Figure 0:") != std::string::npos);

  std::cout << "    ✓ Passed" << std::endl;
}

template <lib::concepts::Scalar T> void TestPrintAreasWithSquarePointers() {
  std::cout << "  Testing PrintAreas with Square<T>*" << std::endl;

  lib::vector::Vector<lib::geometry::Square<T> *> squares;

  auto *square1 = new lib::geometry::Square<T>();
  std::stringstream ss1;
  ss1 << "0 0 2 0 2 2 0 2"; // Площадь = 4
  ss1 >> *square1;
  squares.PushBack(square1);

  std::stringstream output;
  lib::geometry::PrintAreas<T>(output, squares);

  std::string result = output.str();
  assert(!result.empty());
  assert(result.find("Areas") != std::string::npos);
  assert(result.find("Figure 0:") != std::string::npos);

  // Очищаем память
  for (size_t i = 0; i < squares.Size(); ++i) {
    delete squares[i];
  }

  std::cout << "    ✓ Passed" << std::endl;
}

template <lib::concepts::Scalar T> void TestPrintAreasWithSquareObjects() {
  std::cout << "  Testing PrintAreas with Square<T> objects" << std::endl;

  lib::vector::Vector<lib::geometry::Square<T>> squares;

  lib::geometry::Square<T> square1;
  std::stringstream ss1;
  ss1 << "0 0 3 0 3 3 0 3"; // Площадь = 9
  ss1 >> square1;
  squares.PushBack(std::move(square1));

  std::stringstream output;
  lib::geometry::PrintAreas<T>(output, squares);

  std::string result = output.str();
  assert(!result.empty());
  assert(result.find("Areas") != std::string::npos);
  assert(result.find("Figure 0:") != std::string::npos);

  std::cout << "    ✓ Passed" << std::endl;
}

template <lib::concepts::Scalar T> void TestGetTotalAreaWithSquarePointers() {
  std::cout << "  Testing GetTotalArea with Square<T>*" << std::endl;

  lib::vector::Vector<lib::geometry::Square<T> *> squares;

  auto *square1 = new lib::geometry::Square<T>();
  std::stringstream ss1;
  ss1 << "0 0 2 0 2 2 0 2"; // Площадь = 4
  ss1 >> *square1;
  squares.PushBack(square1);

  auto *square2 = new lib::geometry::Square<T>();
  std::stringstream ss2;
  ss2 << "0 0 3 0 3 3 0 3"; // Площадь = 9
  ss2 >> *square2;
  squares.PushBack(square2);

  double total_area = lib::geometry::GetTotalArea<T>(squares);

  // Проверяем, что суммарная площадь вычислена правильно
  if constexpr (std::is_integral_v<T>) {
    assert(total_area == 13.0);
  } else {
    assert(total_area > 12.9 && total_area < 13.1);
  }

  // Очищаем память
  for (size_t i = 0; i < squares.Size(); ++i) {
    delete squares[i];
  }

  std::cout << "    ✓ Passed (total area: " << total_area << ")" << std::endl;
}

template <lib::concepts::Scalar T> void TestGetTotalAreaWithSquareObjects() {
  std::cout << "  Testing GetTotalArea with Square<T> objects" << std::endl;

  lib::vector::Vector<lib::geometry::Square<T>> squares;

  lib::geometry::Square<T> square1;
  std::stringstream ss1;
  ss1 << "0 0 2 0 2 2 0 2"; // Площадь = 4
  ss1 >> square1;
  squares.PushBack(std::move(square1));

  lib::geometry::Square<T> square2;
  std::stringstream ss2;
  ss2 << "0 0 3 0 3 3 0 3"; // Площадь = 9
  ss2 >> square2;
  squares.PushBack(std::move(square2));

  double total_area = lib::geometry::GetTotalArea<T>(squares);

  if constexpr (std::is_integral_v<T>) {
    assert(total_area == 13.0);
  } else {
    assert(total_area > 12.9 && total_area < 13.1);
  }

  std::cout << "    ✓ Passed (total area: " << total_area << ")" << std::endl;
}

template <lib::concepts::Scalar T> void TestEmptyVector() {
  std::cout << "  Testing empty vector" << std::endl;

  // Test with pointers
  {
    lib::vector::Vector<lib::geometry::Square<T> *> empty_ptr;
    std::stringstream output1;
    lib::geometry::PrintCenters<T>(output1, empty_ptr);
    assert(output1.str().find("Centers") != std::string::npos);

    std::stringstream output2;
    lib::geometry::PrintAreas<T>(output2, empty_ptr);
    assert(output2.str().find("Areas") != std::string::npos);

    double total_area = lib::geometry::GetTotalArea<T>(empty_ptr);
    assert(total_area == 0.0);
  }

  // Test with objects
  {
    lib::vector::Vector<lib::geometry::Square<T>> empty_obj;
    std::stringstream output1;
    lib::geometry::PrintCenters<T>(output1, empty_obj);
    assert(output1.str().find("Centers") != std::string::npos);

    std::stringstream output2;
    lib::geometry::PrintAreas<T>(output2, empty_obj);
    assert(output2.str().find("Areas") != std::string::npos);

    double total_area = lib::geometry::GetTotalArea<T>(empty_obj);
    assert(total_area == 0.0);
  }

  std::cout << "    ✓ Passed" << std::endl;
}

// Тесты для float/double (восьмиугольники только для плавающей точки)
template <lib::concepts::Scalar T> void TestOctagonPointers() {
  if constexpr (std::is_floating_point_v<T>) {
    std::cout << "  Testing with Octagon<T>*" << std::endl;

    lib::vector::Vector<lib::geometry::Octagon<T> *> octagons;

    auto *octagon = new lib::geometry::Octagon<T>();
    std::stringstream ss;
    // Простой восьмиугольник
    ss << "0 0 1 0 2 1 2 2 1 2 0 1 -1 2 -2 1";
    ss >> *octagon;
    octagons.PushBack(octagon);

    std::stringstream output1;
    lib::geometry::PrintCenters<T>(output1, octagons);
    assert(!output1.str().empty());

    std::stringstream output2;
    lib::geometry::PrintAreas<T>(output2, octagons);
    assert(!output2.str().empty());

    double area = lib::geometry::GetTotalArea<T>(octagons);
    assert(area > 0);

    for (size_t i = 0; i < octagons.Size(); ++i) {
      delete octagons[i];
    }

    std::cout << "    ✓ Passed" << std::endl;
  }
}

// Основные тестовые функции
template <lib::concepts::Scalar T> void RunTestsForType() {
  std::cout << "\n=== Running tests for type: " << typeid(T).name()
            << " ===" << std::endl;

  // Test PrintCenters
  std::cout << "\nTesting PrintCenters:" << std::endl;
  TestPrintCentersWithSquarePointers<T>();
  TestPrintCentersWithTrianglePointers<T>();
  TestPrintCentersWithSquareObjects<T>();
  TestPrintCentersWithTriangleObjects<T>();

  // Test PrintAreas
  std::cout << "\nTesting PrintAreas:" << std::endl;
  TestPrintAreasWithSquarePointers<T>();
  TestPrintAreasWithSquareObjects<T>();

  // Test GetTotalArea
  std::cout << "\nTesting GetTotalArea:" << std::endl;
  TestGetTotalAreaWithSquarePointers<T>();
  TestGetTotalAreaWithSquareObjects<T>();

  // Test Octagon (only for floating point)
  if constexpr (std::is_floating_point_v<T>) {
    std::cout << "\nTesting Octagon:" << std::endl;
    TestOctagonPointers<T>();
  }

  // Test empty vectors
  std::cout << "\nTesting empty vectors:" << std::endl;
  TestEmptyVector<T>();

  std::cout << "\n✓ All tests passed for type: " << typeid(T).name()
            << std::endl;
}

// Основная функция для запуска всех тестов
void RunAllTests() {
  std::cout << "========== Running Vector Figure Tests ==========\n";

  try {
    // Тесты с double
    RunTestsForType<double>();

    // Тесты с int
    RunTestsForType<int>();

    // Тесты с float
    RunTestsForType<float>();

    std::cout << "\n========== All Vector Figure Tests Passed! ==========\n";
  } catch (const std::exception &e) {
    std::cerr << "Test failed with exception: " << e.what() << std::endl;
    std::exit(1);
  } catch (...) {
    std::cerr << "Test failed with unknown exception" << std::endl;
    std::exit(1);
  }
}

} // namespace tests::geometry

int main() {
  tests::geometry::RunAllTests();
  return 0;
}
