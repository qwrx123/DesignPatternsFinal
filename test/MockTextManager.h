#ifndef MOCKTEXTMANAGER_H
#define MOCKTEXTMANAGER_H

#include "ITextManager.h"

class MockTextManager : public ITextManager {
public:
    void setTextToolActive() override {}
    void setTextToolInactive() override {}
    bool isTextToolActive() const override { return false; }
    const std::vector<std::shared_ptr<IText>>& getTexts() const override { return {}; }
};

#endif