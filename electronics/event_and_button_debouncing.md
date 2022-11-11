This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples  
2013\~2022


# Status: WORK-IN-PROGRESS (WIP)


# Related
1. https://www.electricrcaircraftguy.com/2014/01/the-power-of-arduino.html  


# TODO
1. [ ] Post this whole document as an article on my website here: https://gabrielstaples.com/
1. [ ] Also search this document for "todo" and address all todos herein.


# Reading events or buttons, and event or button debouncing


## See also:
1. My other works here:
    1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_EventReader
        1. [Debouncing info: update readme with an explanation of debouncing](https://github.com/ElectricRCAircraftGuy/eRCaGuy_EventReader/issues/2)
        1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_EventReader/blob/1d0e58bed0649cb3d283264fece3377977f4ba34/eRCaGuy_EventReader.cpp#L101-L160
    1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_ButtonReader
1. https://learn.adafruit.com/debouncer-library-python-circuitpython-buttons-sensors?view=all - Adafruit debouncing background, explanation, and a code library called `adafruit_debouncer`


## Button debouncing

_How to debounce reading a button to obtain its `ButtonDebouncedState`:_

### Background

I love debouncing buttons. I think it's a lot of fun, and requires an understanding of interesting concepts and the electrical and mechanical properties of physical devices such as buttons. Knowing how debouncing works is part of what makes me an _engineer_ and not just a software developer. Having and using this knowledge (ie: being an engineer) is a core part of who I am and how I identify myself. 

Note that if anyone says "but I have a low-pass filter via a resistor and capacitor circuit to debounce the button in hardware, so we don't need debouncing in software", they are _wrong._ Hardware debouncing can significantly help, but is _not_ foolproof. Software debouncing _is_ foolproof when done right. Add the software logic to also debounce in software anyway. It's not that hard, and that's the whole point of my `eRCaGuy_EventReader` library above: it's a debounce library used to obtain the **current state** (ex: `pressed` or `not_pressed`) and the **most recent action** (ex: `state_just_changed_low_to_high`, `state_just_changed_high_to_low`, or `no_change`) of anything, including buttons. 

### Basic concept

Here is an image of a bouncing button plot from an oscilloscope (or similar), which I obtained from [Adafruit's article here](https://learn.adafruit.com/debouncer-library-python-circuitpython-buttons-sensors?view=all), and then labelled myself:

TODO: redo this plot to make it better; see also here: https://github.com/ElectricRCAircraftGuy/eRCaGuy_EventReader/issues/2  

![bouncing button oscilloscope plot](https://user-images.githubusercontent.com/6842199/195956489-61bd4b7a-88b6-47db-8c79-cc5014ee516f.jpg)

TODO: explain how it works

### Debounce code example

Here is some debounce logic I wrote in 2016. That was before I was as good at coding, so please don't judge me too harshly. So, despite any software architecture or syntax issues, the debounce logic itself is sound: https://github.com/ElectricRCAircraftGuy/eRCaGuy_EventReader/blob/master/eRCaGuy_EventReader.cpp#L101-L160. 

The output of this is the ability to read the latest **"debounced action"** and the latest **"debounced state"** of the button or other event-producing device, via `getDebouncedAction()` and `getDebouncedState()`, respectively. 

`readEvent()` should be called continuously in an infinite loop in your `main()` function (or inside the `loop()` function, generally, in Arduino code), and passed the latest boolean state of the event, which is simply a `LOW` (`0`) or `HIGH` (`1`) value for a button. `readEvent()` then debounces this state and updates the `_debouncedState` and `_debouncedAction` internal variables which you can then read at any time. 

```cpp
//------------------------------------------------------------------------------------------------------
//readEvent
//-Description below COPIED FROM THE .h FILE 
/*
Read the latest eventState, debounce it, and update _debouncedAction and _debouncedState as necessary
-The event state can be 0 or 1
-_debouncedAction indicates what just happened to the event: 
  0 = NO_ACTION: no change in true, debounced event state since last time interpreting the event, or debounceDelay time not yet elapsed <--*perhaps* in the future, output a 3 to indicate debounceDelay time not yet elapsed
  1 = ACTION_OCCURRED: a new event just occurred (debounceDelay had elapsed)
 -1 = ACTION_UNOCCURRED: event just "un-occurred" by going back to its resting state (debounceDelay had elapsed)
*/
//------------------------------------------------------------------------------------------------------
void eRCaGuy_EventReader::readEvent(bool eventState)
{ 
  //0) Update _lastBounceTime each time a bounce occurs
  if (eventState != _eventStateOld) //check to see if the *bouncing* event state has changed
  {
    _eventStateOld = eventState; //update
    _lastBounceTime = millis(); //ms; update 
  }
  //1) Only conclude that the eventState is at its actual (not bouncing) state if the debounceDelay has elapsed, as this means that the event state is now resting in its final, NOT bouncing condition.
  if (millis() - _lastBounceTime > _debounceDelay) //if the debounce time has elapsed
  {
    //since the debounceDelay has elapsed, this means the eventState is no longer changing, which means bouncing is no longer occurring,
    //which means that the current eventState is the actual, new, NOT bouncing event state
    _debouncedState = eventState; //store the actual, NOT bouncing even state
    //2) Check to see if the *actual, NOT bouncing* event state has CHANGED
    if (_debouncedState != _debouncedStateOld) //if the actual, NOT bouncing event state has changed
    {
      //3) Since we know that the event is real (debounced), and not noise (since the debounceDelay has occurred), and since we know the event state has CHANGED, meaning that the event isn't just sitting constant in an _EVENT_OCCURRING or _EVENT_NOT_OCCURRING *state*, let's check to see if the event _debouncedAction is ACTION_OCCURRED or ACTION_UNOCCURRED, then the user can act on the side of the _debouncedAction that he/she sees fit
      if (_debouncedState==_EVENT_OCCURRING)
      {
        _debouncedAction = ACTION_OCCURRED; //event action just took place (and debounceDelay had elapsed)
      }
      else //_debouncedState==_EVENT_NOT_OCCURRING
      {
        _debouncedAction = ACTION_UNOCCURRED; //event just went back to its normal, resting condition (and debounceDelay had elapsed)
      }
    } //end of checking to see if the button state has CHANGED
    _debouncedStateOld = _debouncedState; //update the old button state
  } //end of Button debouncing
}

//------------------------------------------------------------------------------------------------------
//getDebouncedAction
//------------------------------------------------------------------------------------------------------
int8_t eRCaGuy_EventReader::getDebouncedAction()
{
  int8_t action = _debouncedAction;
  _debouncedAction = NO_ACTION; //reset, now that the most recent action is being read and acted upon 
  return action;
}

//------------------------------------------------------------------------------------------------------
//getDebouncedState
//------------------------------------------------------------------------------------------------------
bool eRCaGuy_EventReader::getDebouncedState()
{
  return _debouncedState;
}
```


## Layers of interpretation: progress from lowest level first to higher, more-abstract levels of understanding last:

**You will have to write functions and mapping to go from the lower levels first to the higher levels last as you progress down the page here. I present the lowest levels of the button reading _first_.**

Buttons generally have 2 raw instantaneous voltage levels: `LOW` or `HIGH`:
```cpp
enum class ButtonRawVoltageLevel
{
    LOW = 0,  // Ex: 0V
    HIGH,     // Ex: 3.3V or 5.0V, depending on the logic level for your mcu 
};
```

These raw voltage levels get mapped to raw instantaneous states:
```cpp
enum class ButtonRawState
{
    NOT_PRESSED = 0,
    PRESSED,
};
```

<!--
```cpp
// /// The button's current **raw** state. 
// /// Obtained by monitoring the changes of the button
// enum class ButtonVoltageLevel
// {
//     LOW = 0,
//     HIGH = 1,

//     // /// Button is in a pressed (held down) state (after debouncing)
//     // PRESSED = 0,

//     // /// Button is in a NOT pressed (NOT held down) state (after debouncing)
//     // NOT_PRESSED,
// };

enum class ButtonRawState
{
    // voltage level

    LOW = 0,
    HIGH = 1,

    // Raw state: assign the voltage levels to the states here according to 
    // the button type; ex: a button wired to a pull-up resistor is HIGH
    // when not pressed, and a button wired to a pull-down resistor is LOW
    // when not pressed. Pull-up resistors are generally more common, since 
    // many microcontrollers have these built into the GPIO pins internally.

    NOT_PRESSED = HIGH,
    PRESSED = LOW,
};
```
-->

These raw states get debounced in software to ensure they are no longer rapidly changing, or bouncing due to the mechanical springiness in the mechanical switches. Here are the debounced states:
```cpp
/// The button's current **debounced** state. 
/// Obtained by monitoring the changes of the button
enum class ButtonDebouncedState
{
    /// Button is in a NOT pressed (NOT held down) state (after debouncing)
    NOT_PRESSED = 0,

    /// Button is in a pressed (held down) state (after debouncing)
    PRESSED,
};
```

...and the 3 most-recent debounced actions, to indicate if a state change just occurred (button just pressed, just released, etc.):
```cpp
/// The button's most-recent **debounced** state **change**, defined and 
/// reported as an "action"
enum class ButtonAction
{
    /// No debounced state change since the last time we read the button
    NO_CHANGE = 0,

    /// The debounced button state just changed from `NOT_PRESSED` to 
    /// `PRESSED` since the last time we read its debounced state
    JUST_PRESSED,

    /// The debounced button state just changed from `PRESSED` to 
    /// `NOT_PRESSED` since the last time we read its debounced state
    JUST_RELEASED,
};
```

When an action occurs, such as when a button is released, you can complete the time measurement to see how long it was held down. This allows you to detect long presses, short presses, etc. You can also count the number of presses and releases. Interpreting the "bigger picture" of events like this is used to identify button "gestures". 

You can have _any number_ of gestures. Ex:
```cpp
enum class ButtonGesture
{
    NONE = 0,

    // -------------------------------------------------------------------------
    // 1. based on time **durations** between `ButtonAction`
    // - single presses
    // -------------------------------------------------------------------------

    /// `ButtonAction` became `JUST_PRESSED` for < 1 sec, then it became 
    /// `JUST_RELEASED`
    SHORT_PRESS,

    /// `ButtonAction` became `JUST_PRESSED` 1-5 sec, then it became 
    /// `JUST_RELEASED`
    LONG_PRESS,

    /// `ButtonAction` became `JUST_PRESSED` for 5-15 sec, then it became 
    /// `JUST_RELEASED`
    ULTRA_LONG_PRESS,

    /// `ButtonAction` became `JUST_PRESSED` for 30+ sec, and it **never**
    ///  became `JUST_RELEASED`
    STUCK,

    /// `ButtonGesture` was `STUCK` and then the `ButtonAction` became
    /// `JUST_RELEASED`.
    UNSTUCK,

    // -------------------------------------------------------------------------
    // 2. based on time **quantities** of interaction
    // - multi-presses
    // -------------------------------------------------------------------------

    SINGLE_PRESS = SHORT_PRESS,

    DOUBLE_PRESS,

    TRIPLE_PRESS,

    QUADRUPLE_PRESS
};
```

Gestures can then be mapped to "meanings", which you then read to call actions (function calls). 

I prefer to just call the function action directly once a particular gesture is read. 

Sample mapping of gestures to actions:
```cpp
// Example of what some of the gestures above **might** mean if you were using
// a single button to control a menu selector on a GUI display, for instance.
enum class GestureMeaning
{
    GO_LEFT = 0,
    GO_RIGHT,
    GO_UP,
    GO_DOWN,
    ENTER,
    RESET,
};
```

Sample action functions you can just call directly when a particular gesture is read or meaning is interpreted. 
```cpp
// Gesture meanings:
// Ex: imagine you are using a single button to control a menu selector 
// on a display. Here are some possible mappings from `ButtonGesture`s to
// functions to call:

typedef void (*GestureMeaningFunc)(void);

/// Move the menu selector left one element. 
/// - Call this function when you have a `SHORT_PRESS` (`SINGLE_PRESS`). 
void goLeft();

/// Move the menu selector right one element. 
/// - Call this function when you have a `DOUBLE_PRESS`. 
void goRight();

/// - For `TRIPLE_PRESS`.
void goUp();

/// - For `QUADRUPLE_PRESS`
void goDown();

/// - For `LONG_PRESS`
void enter();

/// - For `ULTRA_LONG_RESS`
void reset();
```

As you map from one level of meaning to the next, you may want to carry around the button status in a struct `Button` object, like this:
```cpp
// TODO: Possibly update the `readEvent()` func to return a `Button`, and
// to accept a function ptr which obtains a new raw button state reading--ex:
// pass `readEvent()` a ptr to the `readButton()` func, or just pass it a
// boolean with the latest `ButtonRawVoltageLevel`!
//
// EVEN BETTER: just make a `Button` variable an in-out variable, passed
// by ptr! See my prototype for `readButton()` below.

enum class ButtonType
{
    /// Button voltage is `LOW` when `PRESSED`. This is the case, for instance,
    /// when it has a pull-up resistor which pulls it `HIGH` when not pressed,
    /// and pressing the button connects it to GND.
    /// - ATMega328 mcus (Arduino Uno, Nano, etc.) have internal pull-up 
    /// resistors, so this is the most-common button configuration.
    ACTIVE_LOW = 0,

    /// Button voltage is `HIGH` when `PRESSED`. This is the case, for instance,
    /// when it has a pull-down resistor which pulls it `LOW` when not pressed, 
    /// and pressing the button connects it to V_IN (ex: 5.0V or 3.3V).
    ACTIVE_HIGH,
};

/// A button object carrying around its entire state, including all of the 
/// information above. 
///
/// TODO: for C, write supporting functions to use this object. 
/// For C++, add class member functions and make anything private that you 
/// want to be private.
struct Button
{
    char buttonName[20] = "no name";

    // Potential low-level info. needed for reading a button on a
    // microcontroller
    uint8_t pinNum = 0;
    ButtonType buttonType = ButtonType::ACTIVE_LOW;

    // Other info. needed for the mappings described above

    ButtonRawVoltageLevel buttonRawVoltageLevel = ButtonRawVoltageLevel::LOW;
    ButtonRawState buttonRawState = ButtonRawState::NOT_PRESSED;
    ButtonDebouncedState buttonDebouncedState = ButtonDebouncedState::NOT_PRESSED;
    
    ButtonAction buttonAction = ButtonAction::NO_CHANGE;
    ButtonGesture buttonGesture = ButtonGesture::NONE;

    // Reset this to `nullptr` whenever `ButtonGesture` is `NONE`.
    GestureMeaningFunc gestureMeaningFunc = nullptr;

    // Function to call to get a new reading for this button

};

typedef ButtonRawVoltageLevel (*ReadRawButtonStateFunc)();

// TODO: write a `readButtons()` func too to handle many buttons. Write it for
// Arduino/embedded safety-critical mcus. So, no using std C++ library
// containers since they have dynamic memory allocation under-the-hood.


// void readButton(Button *button, ButtonRawState brandNewRawStateReading)
// {
//     // Fill this in with the logic from `readEvent()` earlier, above, plus
//     // additional logic as necessary to obtain and update all other state
//     // information as stored in the `Button` struct returned by this
//     // function.
// }


/// \brief      Take a new instantaneous button state reading, interpret it, 
///             and update all variables inside the `Button` in/out 
///             object.
/// \param[in,out]  button    All information about the button.
/// \return     None
/// Todo:  return an error status enum instead of void.
void readButton(Button* button) 
{
    // take a new instantaneous button state reading and update all variables
    // inside the `button` object
}
```

Example usage:

```cpp
Button button1;

// Initialize constant or constant-like things.
// TODO: make these things actual constants in a future version.
strncpy(button1.buttonName, "Power button", sizeof(button1.buttonName));
button1.pinNum = 7;
button1.buttonType = ButtonType::ACTIVE_LOW;

// Now read a new button raw voltage level and have it update all internal 
// state info, including the debounced state, button action, button gesture, 
// gesture meaning function, etc.
readButton(&button1);
// Now, act according to whatever the button input gesture means!:
if (button1.gestureMeaningFunc != nullptr)
{
    button1.gestureMeaningFunc = nullptr;   // reset it
    button1.gestureMeaningFunc();           // call the function!
}

// TODO: wrap the whole `if` block above up into its own method. This
// `callGestureMeaningFunc()` method will contain the `if` block above. Ex:

// In C:
readButton(&button1);
callGestureMeaningFunc(&button1);

// Or, in C++:
button1.readButton();
button1.callGestureMeaningFunc(); 
```
