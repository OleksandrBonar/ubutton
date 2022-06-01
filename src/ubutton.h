#ifndef UBUTTON_H
#define UBUTTON_H

#define COUNT_FALLING 0
#define COUNT_RISING  1
#define COUNT_BOTH    2

class uButton
{
	private:
		int pinNum;
		unsigned long debounceTime;
		unsigned long count;
		int countMode;

		int previousSteadyState;
		int lastSteadyState;
		int lastFlickerableState;

		unsigned long lastDebounceTime;

	public:
		uButton(int pinNum);
		uButton(int pinNum, int mode);

		void setDebounceTime(unsigned long time);

		int getState(void);
		int getStateRaw(void);

		bool isPressed(void);
		bool isReleased(void);

		void setCountMode(int mode);
		unsigned long getCount(void);
		void resetCount(void);

		void loop(void);
};

#endif
