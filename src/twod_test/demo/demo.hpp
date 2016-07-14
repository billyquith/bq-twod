
#pragma once

class Demo
{
public:
    virtual ~Demo() {}
    
    virtual void init() {}
    virtual void update() {}
    virtual void cleanUp() {}
};


/*
#include "demo/demo.hpp"

void Demo::init()
{    
}

void Demo::cleanUp()
{   
}

void Demo::update()
{   
}
*/