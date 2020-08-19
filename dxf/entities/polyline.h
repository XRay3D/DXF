#pragma once
#include "entity.h"
struct POLYLINE final : Entity {
    POLYLINE();

    // Entity interface
public:
    void draw() const override;
    void parse(CodeData& code) override;
};
