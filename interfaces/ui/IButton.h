class IButton
{
   public:
	IButton()			 = default;
	virtual ~IButton()	 = default;
	virtual void click() = 0;
};