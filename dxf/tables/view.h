#pragma once
#include "tableitem.h"

struct VIEW : TableItem {
public:
    VIEW(SectionParser* sp);
    // TableItem interface
public:
    void parse(CodeData& code) override;
    Type type() const override { return TableItem::VIEW; };
};
