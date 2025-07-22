#pragma once
class Component {
public:
    virtual ~Component() = default;
    virtual void initialize() = 0;
    virtual void update() = 0;
};
