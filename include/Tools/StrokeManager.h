#ifndef STROKEMANAGER_H
#define STROKEMANAGER_H

#include "IStrokeManager.h"

class StrokeManager : public IStrokeManager
{
   public:
	StrokeManager();
	~StrokeManager() override;
	void addStroke(std::shared_ptr<IStroke> stroke) override;
	[[nodiscard]] const std::vector<std::shared_ptr<IStroke>>& getStrokes() const override;
	void													   clear() override;

   private:
	std::vector<std::shared_ptr<IStroke>> strokes_;
};

#endif	// STROKEMANAGER_H