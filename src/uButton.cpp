#include <uButton.h>

uButton::uButton(unsigned short pin): uButton(pin, INPUT_PULLUP) {}

uButton::uButton(unsigned short pin, int mode)
{
	pinNum = pin;
	debounceTime = 0;
	count = 0;
	countMode = COUNT_FALLING;

	pinMode(pinNum, mode);

	previousSteadyState = digitalRead(btnPin);
	lastSteadyState = previousSteadyState;
	lastFlickerableState = previousSteadyState;

	lastDebounceTime = 0;
}

void uButton::setDebounceTime(unsigned long time)
{
	debounceTime = time;
}

int uButton::getState(void)
{
	return lastSteadyState;
}

int uButton::getStateRaw(void)
{
	return digitalRead(pinNum);
}

bool uButton::isPressed(void)
{
  return previousSteadyState == HIGH && lastSteadyState == LOW;
}

bool uButton::isReleased(void)
{
	return previousSteadyState == LOW && lastSteadyState == HIGH;
}

bool uButton::isChanged(void)
{
  return isPressed() || isReleased();
}

void uButton::setCountMode(int mode)
{
	countMode = mode;
}

unsigned long uButton::getCount(void)
{
	return count;
}

void uButton::resetCount(void)
{
	count = 0;
}

void uButton::loop(void)
{
	int currentState = digitalRead(pinNum);
	unsigned long currentTime = millis();

	// If the switch/button changed, due to noise or pressing:
	if (currentState != lastFlickerableState) {
		// reset the debouncing timer
		lastDebounceTime = currentTime;
		// save the the last flickerable state
		lastFlickerableState = currentState;
	}

	if ((currentTime - lastDebounceTime) >= debounceTime) {
		// whatever the reading is at, it's been there for longer than the debounce
		// delay, so take it as the actual current state:

		// save the the steady state
		previousSteadyState = lastSteadyState;
		lastSteadyState = currentState;
	}

	if (previousSteadyState != lastSteadyState) {
		if (countMode == COUNT_BOTH) {
			count++;
    } else if (countMode == COUNT_FALLING) {
			if (previousSteadyState == HIGH && lastSteadyState == LOW) {
				count++;
      }
		} else if (countMode == COUNT_RISING) {
			if (previousSteadyState == LOW && lastSteadyState == HIGH) {
				count++;
      }
		}
	}
}
