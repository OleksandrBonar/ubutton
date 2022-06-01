#ifndef UBUTTON_H
#define UBUTTON_H

#define COUNT_FALLING 0
#define COUNT_RISING  1
#define COUNT_BOTH    2

class uButton
{
	private:
		int pinNum;
		int pinMode;
	
		unsigned long debounceTime;
		unsigned long count;
		int countMode;

		int previousSteadyState;
		int lastSteadyState;
		int lastFlickerableState;

		unsigned long lastDebounceTime;

	protected:
		int getOnValue(void);
		int getOffValue(void);

	public:
		uButton(int pin);
		uButton(int pin, int mode);

		void setDebounceTime(unsigned long time);

		int getState(void);
		int getStateRaw(void);

		bool isOn(void);
		bool isOff(void);

		bool isPressed(void);
		bool isReleased(void);
		bool isChanged(void);

		void setCountMode(int mode);
		unsigned long getCount(void);
		void resetCount(void);

		void loop(void);
};

#endif
