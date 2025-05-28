#ifndef ITOOL_H
#define ITOOL_H

class ITool
{
   public:
	ITool()						   = default;
	virtual ~ITool()			   = default;
	ITool(const ITool&)			   = default;
	ITool& operator=(const ITool&) = default;
	ITool(ITool&&)				   = default;
	ITool& operator=(ITool&&)	   = default;

	[[nodiscard]] virtual bool isActive() const = 0;
};

#endif	// ITOOL_H