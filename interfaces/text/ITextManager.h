#ifndef ITEXTMANAGER_H
#define ITEXTMANAGER_H

#include <vector>
#include <memory>
#include "IText.h"

class ITextManager {
public:
    virtual ~ITextManager() = default;

    virtual void                        addText(std::shared_ptr<IText> text) = 0;
    virtual void                        removeText(std::shared_ptr<IText> text) = 0;

    virtual const std::vector<std::shared_ptr<IText>>& getTexts() const = 0;

    virtual std::shared_ptr<IText>     getTextAt(double x, double y) const = 0;
    virtual void                       clearAll() = 0;
};

#endif // ITEXTMANAGER_H
