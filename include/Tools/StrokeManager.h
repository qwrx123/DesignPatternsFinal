#ifndef STROKEMANAGER_H
#define STROKEMANAGER_H

#include "IStrokeManager.h"
#include "Stroke.h"

class StrokeManager : public IStrokeManager {
public:
 StrokeManager();
 ~StrokeManager() override;
 void addStroke(std::shared_ptr<IStroke> stroke) override;
 const std::vector<std::shared_ptr<IStroke>>& getStrokes() const override;
 void clear() override;
 void replaceStrokes(std::vector<std::shared_ptr<IStroke>> new_strokes);
 void splitEraseWithPath(const std::shared_ptr<IStroke>& eraser_path, float eraser_radius);

private:
    std::vector<std::shared_ptr<IStroke>> strokes_;
};

#endif // STROKEMANAGER_H