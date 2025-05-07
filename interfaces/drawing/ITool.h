#ifndef ITOOL_H
#define ITOOL_H

class ITool
{
   public:
	ITool()			 = default;
	virtual ~ITool() = default;

	virtual bool isActive() const = 0;
};

#endif	// ITOOL_H