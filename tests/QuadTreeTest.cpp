#include <gtest/gtest.h>
#include <SDL2/SDL.h>

#include <stdio.h>

#include "../include/managers/entitymanager.h"
#include "../include/managers/quadtree.h"
#include "../include/entities/entity.h"

// Testing QuadTree.
class QuadTreeTest : public ::testing::Test {
    protected:
        QuadTreeTest() {
            // You can do set-up work for each test here.
        }

        ~QuadTreeTest() override {
    
        }

        void SetUp() override {
  
        }

        void TearDown() override {
        
        }

        QuadTree quadtree;

};

// Test the QuadTree
TEST_F(QuadTreeTest, QuadTree) {
    
}


// Run the tests!
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

