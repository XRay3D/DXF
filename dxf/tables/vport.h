#pragma once
#include "tableitem.h"

struct VPORT : TableItem {
public:
    VPORT(SectionParser* sp);
    // TableItem interface
public:
    void parse(CodeData& code) override;
    Type type() const override { return TableItem::VPORT; };
};
