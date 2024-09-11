#include "Example_library/rubiks_cube/rubiks_cube.hpp"
#include <gtest/gtest.h>
#include <random>

bool verify_positions(rubiks_cube cube)
{
  bool correct = true;

  for (char z = -1; z < 2; ++z)
    for (char y = -1; y < 2; ++y)
      for (char x = -1; x < 2; ++x)
      {
        glm::i8vec3 position(x, y, z);
        glm::i8vec3 target_position = cube.get_cubie(x, y, z)[3];

        if (position != target_position)
          correct = false;
      }
  return correct;
}

void test_one_rotation(char axis, char slice_idx, bool counterclockwise)
{
  rubiks_cube cube;
  cube.rotate(rubiks_cube::AXIS_X, 1, false);
  bool correct_positions = verify_positions(cube);
  EXPECT_TRUE(correct_positions);
}

TEST(Rubiks_cube, one_rotation_step_in_all_directions)
{
  EXPECT_TRUE(true);
  for (char axis = 0; axis < 3; ++axis)
    for (char slice = 0; slice <= 3; ++slice)
    {
      test_one_rotation(axis, slice, true);
      test_one_rotation(axis, slice, false);
    }
}

TEST(Rubiks_cube, all_positions_correct_during_many_random_directions)
{
  std::mt19937 rng;
  std::uniform_int_distribution<uint32_t> axis(0, 2);
  std::uniform_int_distribution<uint32_t> slice(0, 2);
  std::uniform_int_distribution<uint32_t> direction(0, 1);

  rubiks_cube cube;

  for (int i = 0; i < 100000; i++)
    test_one_rotation(axis(rng), slice(rng), direction(rng));
}