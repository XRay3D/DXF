#pragma once
#include "tableitem.h"

struct DIMSTYLE final : TableItem {
public:
    DIMSTYLE(SectionParser* sp);

    // TableItem interface
public:
    void parse(CodeData& code) override;
    Type type() const override { return TableItem::DIMSTYLE; }
};
