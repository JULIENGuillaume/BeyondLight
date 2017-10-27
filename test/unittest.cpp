/*
** unittest.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/unittest.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Thu Oct 26 16:03:23 2017 Guillaume Julien
** Last update Thu Oct 26 16:03:23 2017 Guillaume Julien
*/

#include "gtest/gtest.h"

TEST(SimpleAdd, Diff) {
	EXPECT_NE(1, 0 + 2);
}

TEST(SimpleAdd, NoDiff) {
	EXPECT_EQ(2, 0 + 2);
}

TEST(ComplexeAdd, NoDiff) {
	EXPECT_EQ(123, 100 + 20 + 3);
}