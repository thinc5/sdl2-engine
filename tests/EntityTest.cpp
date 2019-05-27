#include <gtest/gtest.h>
#include <SDL2/SDL.h>

#include <stdio.h>

#include "../include/entities/entity.h"

// The fixture for testing class Foo.
class EntityTest : public ::testing::Test {
    protected:
        EntityTest() {
            // You can do set-up work for each test here.
        }

        ~EntityTest() override {
    
        }

        void SetUp() override {
  
        }

        void TearDown() override {
        
        }

        Entity dumb;

};


TEST_F(EntityTest, EntityBasic) {
    printf("Address: %lu\n", &dumb.components[0].call);
    ASSERT_TRUE(dumb.components[0].call == NULL);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}