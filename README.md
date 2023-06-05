# CS205 S23 Group 11 Final Project

> Create a multi-modal communication tool backed by a database with both web and standing applications for communication, monitoring, and administration of a US based collective of fish enthusiasts. (On OSX, Linux, Windows; and tablets would be nice too!)

> Respecting our Finned Friends and Tentacled Pals

## Info

**Authors:**  
Peter Fabens  
James Boateng  
Cale King

## Development Resources

### GTest Template

Barebones GTest test suite.

```
#include <iostream>

#include "gtest/gtest.h"

class MyTest : public ::testing::Test {
protected:

    MyTest() {
        // test constructor
    }

    virtual ~MyTest() {
        // test deconstructor
    }
};

TEST_F(MyTest, LOG) {
    // test
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```